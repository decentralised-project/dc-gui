#include "p2p_connection.hpp"

namespace dcp2p
{
	p2p_connection::p2p_connection(boost::asio::io_service& io_service, std::string &localId)
		: _io_service(io_service), socket_(io_service), _localId(localId)
	{
		_remoteId = "";
		isIncoming_ = false;
	}

	tcp::socket& p2p_connection::Socket()
	{
		return socket_;
	}

	void p2p_connection::Start()
	{
		isIncoming_ = true;

		// incoming cycle
		boost::asio::async_read(socket_,
			boost::asio::buffer(packet_.data(), p2p_packet::header_length),
			boost::bind(
			&p2p_connection::handle_read_header, shared_from_this(),
			boost::asio::placeholders::error));
	}

	void p2p_connection::Shutdown()
	{
		Log("shutting down connection");
		socket_.cancel();
		socket_.shutdown(boost::asio::socket_base::shutdown_type::shutdown_both);
		_io_service.stop();
	}

	void p2p_connection::Connect(std::string host, int port)
	{
		// --- outgoing cycle

		// get the target port number as a string
		std::stringstream portStr;
		portStr << port;

		// get an endpoint to connect to
		tcp::resolver resolver(_io_service);
		tcp::resolver::query query(tcp::v4(), host.c_str(), portStr.str());
		tcp::resolver::iterator iterator = resolver.resolve(query);

		// try to make a connection. This is blocking for up to about 20 secs
		try
		{
			boost::asio::connect(socket_, iterator);
		}
		catch (std::exception const &ex) {

			// there was an error connecting, so log it and exit the method, so we can try again.
			Log(ex.what());
			return;
		}

		// we've connected, so add our public key to the send queue to introduce ourselves.
		Send(_localId);

		// send the packet at the front of the queue.
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_queue_.front().data(),
			write_queue_.front().length()),
			boost::bind(&p2p_connection::handle_write, shared_from_this(),
			boost::asio::placeholders::error));
	}

	void p2p_connection::Send(p2p_packet packet)
	{
		write_queue_.push_back(packet);
	}

	void p2p_connection::Send(unsigned char* data, size_t length)
	{
		packet_.body_length(length);
		memcpy(packet_.body(), data, packet_.body_length());
		packet_.encode_header();

		Send(packet_);
	}

	void p2p_connection::Send(std::string message)
	{
		packet_.body_length(strlen(message.c_str()));
		memcpy(packet_.body(), message.c_str(), packet_.body_length());
		packet_.encode_header();

		Send(packet_);
	}

	void p2p_connection::handle_read_header(const boost::system::error_code& error)
	{
		if (!error && packet_.decode_header())
		{
			boost::asio::async_read(socket_,
				boost::asio::buffer(packet_.body(), packet_.body_length()),
				boost::bind(&p2p_connection::handle_read_body, shared_from_this(),
				boost::asio::placeholders::error));
		}
		else
		{
			// we got disconnected or sumfin
			if (_remoteId != "")
				if (error)
					NodeDisconnected(_remoteId, std::string("(handle_read_header) ").append(error.message()));
				else
					NodeDisconnected(_remoteId, "(handle_read_header) no error");
		}
	}

	std::string p2p_connection::GetRemoteId()
	{
		return _remoteId;
	}

	void p2p_connection::handle_read_body(const boost::system::error_code& error)
	{
		if (!error)
		{
			size_t bodyLength = packet_.body_length();
			// if this is a single byte ping packet, ping back, or just ignore if it's a reply.
			if (bodyLength == 1)
			{
				unsigned char ping = packet_.body()[0];
				if (ping == 0)
				{
					unsigned char ping[1];
					ping[0] = 1;
					Send(ping, 1);
				}
			}
			else
			{
			  if (_remoteId == "")
			  {
				  std::string body(packet_.body(), packet_.body() + bodyLength);
				  _remoteId = body.substr(0, bodyLength);
				  if (_localId != _remoteId)
				  {
					  NodeConnected(isIncoming_, shared_from_this(), _remoteId);

					  std::stringstream id_stream;
					  id_stream << _localId;

					  if (isIncoming_)
						  Send(std::string(id_stream.str()));
				  }
				  else
				  {
					  std::stringstream ss;
					  ss << "Dropped connection to self. " << socket_.remote_endpoint();
					  Log(std::string(ss.str()));

					  //socket_.shutdown(boost::asio::socket_base::shutdown_both);
					  //_io_service.stop();
					  return;
				  }
			  }
			  else
				  ReceivedData(shared_from_this(), packet_);
			}
			
			if (write_queue_.empty())
			{
				// todo: this would be better if it continually checked for 3 secs if theres any queued outgoing,
				// if any appear, it continues, if not, it pings 
				// (or else we have to wait until the next round to send) up to 3 secs of potential lag with thread::sleep method
				boost::this_thread::sleep(boost::posix_time::milliseconds(3000));

				unsigned char ping[1];
				ping[0] = 0;
				Send(ping, 1);
			}

			boost::asio::async_write(socket_,
   									 boost::asio::buffer(write_queue_.front().data(),
									 write_queue_.front().length()),
									 boost::bind(&p2p_connection::handle_write, shared_from_this(),
									 boost::asio::placeholders::error));
		}
		else
		{
			// we got disconnected or sumfin
			if (error)
				NodeDisconnected(_remoteId, std::string("(handle_read_body) ").append(error.message()));
			else
				NodeDisconnected(_remoteId, "(handle_read_body) no error");
		}
	}

	void p2p_connection::handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			write_queue_.pop_front();

			boost::asio::async_read(socket_,
				boost::asio::buffer(packet_.data(), p2p_packet::header_length),
				boost::bind(&p2p_connection::handle_read_header, shared_from_this(),
				boost::asio::placeholders::error));
		}
		else
		{
			// we got disconnected or sumfin
			if (error)
				NodeDisconnected(_remoteId, std::string("(handle_write) ").append(error.message()));
			else
				NodeDisconnected(_remoteId, "(handle_write) no error");
		}
	}
}