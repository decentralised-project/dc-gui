#ifndef __P2P_MANAGER_H_INCLUDED__
#define __P2P_MANAGER_H_INCLUDED__

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp> 
#include <boost/signals2/signal.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "p2p_listener.hpp"
#include "p2p_host.hpp"
#include "p2p_hostmanager.hpp"
#include "p2p_packet.hpp"
#include "p2p_connection.hpp"

namespace dcp2p
{
	class p2p_manager : public boost::enable_shared_from_this<p2p_manager>
	{
	public:
		typedef boost::shared_ptr<p2p_manager> pointer;

		static pointer Create(std::string dataDirPath)
		{
			return pointer(new p2p_manager(dataDirPath));
		}

		boost::signals2::signal<void(std::string)>											Log;
		boost::signals2::signal<void(bool, p2p_connection::pointer, std::string)>			NodeConnected;
		boost::signals2::signal<void(p2p_connection::pointer, p2p_packet)>					DataReceived;
		boost::signals2::signal<void(std::string)>											NodeDisconnected;

		void on_node_connected(bool isIncoming, p2p_connection::pointer connection, std::string remoteId);
		void on_log_recieved(std::string msg);
		void on_data_recieved(p2p_connection::pointer connection, p2p_packet packet);
		void on_node_disconnected(std::string remoteId);

		void Run(int incomingPort, std::string uniqueSessionId);		
		void Shutdown();

	private:
		p2p_manager(std::string dataDirPath);

		void listener_run(int incomingPort);
		void outgoing_run();

		std::vector<boost::shared_ptr<boost::thread>> _threads;
		std::vector<p2p_connection::pointer> _outgoing;
		p2p_listener::pointer _listener;
		p2p_hostmanager::pointer _host_manager;
		std::string _networkId;
		std::string data_dir;
	};
}

#endif