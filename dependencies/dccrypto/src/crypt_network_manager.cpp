#include "crypt_network_manager.hpp"

namespace dccrypto
{
	crypt_network_manager::crypt_network_manager(std::string dataDirPath)
	{
		data_path = dataDirPath;
	}

	void crypt_network_manager::Run(int incomingPort)
	{
		manager = dcp2p::p2p_manager::Create(data_path);
		manager->Log.connect(boost::bind(&crypt_network_manager::on_log_recieved, this, _1));
		manager->NodeConnected.connect(boost::bind(&crypt_network_manager::on_node_connected, this, _1, _2, _3));
		manager->DataReceived.connect(boost::bind(&crypt_network_manager::on_data_recieved, this, _1, _2));
		manager->NodeDisconnected.connect(boost::bind(&crypt_network_manager::on_node_disconnected, this, _1));
		manager->Run(incomingPort);
	}

	void crypt_network_manager::Shutdown()
	{
		if (manager)
			manager->Shutdown();	
	}

	void crypt_network_manager::on_log_recieved(std::string msg)
	{
		Log(msg);
	}

	void crypt_network_manager::on_node_connected(bool isIncoming, dcp2p::p2p_connection::pointer connection, boost::uuids::uuid remoteId)
	{
		NodeConnected(isIncoming, connection, remoteId);
	}

	void crypt_network_manager::on_data_recieved(dcp2p::p2p_connection::pointer connection, dcp2p::p2p_packet packet)
	{
		DataReceived(connection, packet);
	}

	void crypt_network_manager::on_node_disconnected(boost::uuids::uuid remoteId)
	{
		NodeDisconnected(remoteId);
	}
}