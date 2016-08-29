#ifndef __CRYPT_NETWORK_MANAGER_H_INCLUDED__
#define __CRYPT_NETWORK_MANAGER_H_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/ecdsa.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/evp.h>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "p2p_manager.hpp"
#include "p2p_connection.hpp"
#include "p2p_packet.hpp"
#include "crypt_ec_helper.hpp"
#include "crypt_connection.hpp"

namespace dccrypto
{
	class crypt_network_manager : public boost::enable_shared_from_this<crypt_network_manager>
	{
	public:
		typedef boost::shared_ptr<crypt_network_manager> pointer;

		static pointer Create(std::string dataDirPath)
		{
			return pointer(new crypt_network_manager(dataDirPath));
		}

		boost::signals2::signal<void(std::string)>													Log;
		boost::signals2::signal<void(bool, dcp2p::p2p_connection::pointer, std::string)>			NodeConnected;
		boost::signals2::signal<void(dcp2p::p2p_connection::pointer, dcp2p::p2p_packet)>			DataReceived;
		boost::signals2::signal<void(std::string)>													NodeDisconnected;

		void Run(int incomingPort, std::string username);
		void Send(unsigned char* data);
		void Shutdown();

	private:
		crypt_network_manager(std::string dataDirPath);

		void on_node_connected(bool isIncoming, dcp2p::p2p_connection::pointer connection, std::string remoteId);
		void on_log_recieved(std::string msg);
		void on_data_recieved(dcp2p::p2p_connection::pointer connection, dcp2p::p2p_packet packet);
		void on_node_disconnected(std::string remoteId);

		dcp2p::p2p_manager::pointer manager;
		crypt_ec_helper::pointer helper;
		std::string data_path;
		EC_KEY* pkey;

		std::vector<crypt_connection::pointer> connections;
	};
}

#endif