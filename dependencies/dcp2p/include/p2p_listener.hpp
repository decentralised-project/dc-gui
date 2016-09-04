#ifndef __P2P_LISTENER_H_INCLUDED__
#define __P2P_LISTENER_H_INCLUDED__

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp> 
#include <string>
#include <algorithm>
#include <vector>
#include <boost/bind.hpp>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "p2p_connection.hpp"

using namespace boost::asio::ip;

namespace dcp2p
{
	class p2p_manager;

	class p2p_listener
	{
	public:

		p2p_listener(int incomingPort, std::string &localId);
		~p2p_listener();

		void ListenForIncoming(boost::shared_ptr<p2p_manager> manager);

	private:
		void handle_accept(p2p_connection::pointer new_connection, const boost::system::error_code& error);

		boost::asio::io_service io_service_;
		tcp::acceptor acceptor_;
		std::string &_localId;
		boost::shared_ptr<p2p_manager> manager_;
	};
}

#endif