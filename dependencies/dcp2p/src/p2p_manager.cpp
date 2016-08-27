#include "p2p_manager.hpp"

namespace dcp2p
{
	p2p_manager::p2p_manager(std::string dataDirPath)
	{
		data_dir = dataDirPath;
	}

	void p2p_manager::Shutdown()
	{
		_listener->Shutdown();

		for (size_t i = 0; i < _outgoing.size(); i++)
		{
			_outgoing[i]->Shutdown();
		}
		_outgoing.clear();

		for (size_t i = 0; i < _threads.size(); i++)
		{
			_threads[i]->interrupt();
			_threads[i]->join();
		}
	}

	void p2p_manager::Run(int incomingPort, std::string uniqueSessionId)
	{
		_networkId = uniqueSessionId;

		// first, start the listener thread
		boost::shared_ptr<boost::thread> listenerThread = boost::shared_ptr<boost::thread>(new boost::thread(&p2p_manager::listener_run, this, incomingPort));
		_threads.push_back(listenerThread);

		// create a vector of dns seeds for the host manager
		const std::string arr[] = { 
			"dnsseed.decentralised-project.org", 
			"dnsseed.evil.center" 
		};
		std::vector<std::string> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

		std::string hosts_path = std::string(data_dir.c_str());
		hosts_path.append("hosts.json");
		_host_manager = p2p_hostmanager::Create(hosts_path, vec, 6453); // default port, not incoming

		//for (int i = 0; i < 5; ++i)
		//{
		
			boost::shared_ptr<boost::thread> workerA = boost::shared_ptr<boost::thread>(new boost::thread(&p2p_manager::outgoing_run, this));
			_threads.push_back(workerA);

			//boost::thread* workerB = new boost::thread(&p2p_manager::outgoing_run, this);
			//_threads.push_back(workerB);
		//}
	}

	void p2p_manager::listener_run(int incomingPort)
	{
		boost::asio::io_service io;
		_listener = p2p_listener::Create(io, incomingPort, _networkId);
		_listener->ListenForIncoming(shared_from_this());

		std::string msg = "Listening on port ";

		std::stringstream ss;
		ss << incomingPort;
		msg.append(ss.str());

		Log(msg);

		io.run();
	}

	void p2p_manager::outgoing_run()
	{
		boost::asio::io_service io;

		p2p_host chosen = _host_manager->GetNextHost();
		if (chosen.IsEmpty())
		{
			Log("Hosts are exhausted. Thread exiting.");
			return;
		}

		std::string msg;
		msg.append("Connecting to ");
		msg.append(chosen.GetIp());
		msg.append(":");

		std::stringstream ss;
		ss << chosen.GetPort();
		msg.append(ss.str());

		Log(msg);

		// outgoing connection
		p2p_connection::pointer new_connection = p2p_connection::Create(io, _networkId);
		new_connection->Log.connect(boost::bind(&p2p_manager::on_log_recieved, this, _1));
		new_connection->NodeConnected.connect(boost::bind(&p2p_manager::on_node_connected, this, _1, _2, _3));
		new_connection->ReceivedData.connect(boost::bind(&p2p_manager::on_data_recieved, this, _1, _2));
		new_connection->NodeDisconnected.connect(boost::bind(&p2p_manager::on_node_disconnected, this, _1));
		new_connection->Connect(chosen.GetIp(), chosen.GetPort());

		_outgoing.push_back(new_connection);

		io.run();
	}

	void p2p_manager::on_node_connected(bool isIncoming, p2p_connection::pointer connection, std::string remoteId)
	{
		NodeConnected(isIncoming, connection, remoteId);
	}

	void p2p_manager::on_log_recieved(std::string msg)
	{
		Log(msg);
	}

	void p2p_manager::on_data_recieved(p2p_connection::pointer connection, p2p_packet packet)
	{
		DataReceived(connection, packet);
	}

	void p2p_manager::on_node_disconnected(std::string remoteId)
	{
		NodeDisconnected(remoteId);
	}
}