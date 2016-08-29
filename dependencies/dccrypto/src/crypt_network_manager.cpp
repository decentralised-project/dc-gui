#include "crypt_network_manager.hpp"

namespace dccrypto
{
	crypt_network_manager::crypt_network_manager(std::string dataDirPath)
	{
		data_path = dataDirPath;
		pkey = NULL;
		helper = crypt_ec_helper::Create();
	}

	void crypt_network_manager::Run(int incomingPort, std::string name)
	{
		pkey = helper->load_key_pair(std::string(data_path).append("private_keys/").append(name).append(".pem"));
		std::string publickey = helper->to_base58(helper->get_public_key(pkey));

		Log(std::string("Public key is ").append(publickey));

		manager = dcp2p::p2p_manager::Create(data_path);
		manager->Log.connect(boost::bind(&crypt_network_manager::on_log_recieved, this, _1));
		manager->NodeConnected.connect(boost::bind(&crypt_network_manager::on_node_connected, this, _1, _2, _3));
		manager->DataReceived.connect(boost::bind(&crypt_network_manager::on_data_recieved, this, _1, _2));
		manager->NodeDisconnected.connect(boost::bind(&crypt_network_manager::on_node_disconnected, this, _1));
		manager->Run(incomingPort, publickey);
	}

	void crypt_network_manager::Send(std::string remoteId, unsigned char* data, size_t length)
	{
		unsigned char *cipherText = new unsigned char[length + 2048]; // 2k extra extra buffer incase encrypted data is bigger

		for (std::vector<dccrypto::crypt_connection::pointer>::iterator it = connections.begin(); it != connections.end(); ++it) {
			if ((*it)->GetRemotePublicKeyBase58() == remoteId)
			{
				int cipherTextLength = (*it)->Encrypt(cipherText, data, length);
				(*it)->GetP2PConnection()->Send(cipherText, cipherTextLength);
				break;
			}
		}
		free(cipherText);
	}

	void crypt_network_manager::Send(unsigned char* data, size_t length)
	{
		unsigned char *cipherText = new unsigned char[length + 2048]; // 2k extra extra buffer incase encrypted data is bigger

		for (std::vector<dccrypto::crypt_connection::pointer>::iterator it = connections.begin(); it != connections.end(); ++it) {
			int cipherTextLength = (*it)->Encrypt(cipherText, data, length);
			(*it)->GetP2PConnection()->Send(cipherText, cipherTextLength);
		}
		free(cipherText);
	}

	void crypt_network_manager::Shutdown()
	{
		if (manager)
			manager->Shutdown();	

		if (pkey)
			EC_KEY_free(pkey);
	}

	void crypt_network_manager::on_log_recieved(std::string msg)
	{
		Log(msg);
	}

	void crypt_network_manager::on_node_connected(bool isIncoming, dcp2p::p2p_connection::pointer connection, std::string remoteId)
	{
		dccrypto::crypt_connection::pointer cnt = dccrypto::crypt_connection::Create(helper, remoteId, pkey, connection);
		connections.push_back(cnt);

		NodeConnected(isIncoming, connection, remoteId);
	}

	void crypt_network_manager::on_data_recieved(dcp2p::p2p_connection::pointer connection, dcp2p::p2p_packet packet)
	{
		unsigned char *plainText = new unsigned char[packet.body_length() + 2048]; // 2k extra extra buffer incase decrypted data is bigger
		int plainTextLength;

		for (std::vector<dccrypto::crypt_connection::pointer>::iterator it = connections.begin(); it != connections.end(); ++it) {
			if ((*it)->GetRemotePublicKeyBase58() == connection->GetRemoteId())
			{
				plainTextLength = (*it)->Decrypt(plainText, (unsigned char*)packet.body(), packet.body_length());
				packet.body_length(plainTextLength);
				memcpy(packet.body(), plainText, plainTextLength);
				break;
			}
		}
		free(plainText);

		DataReceived(connection, packet);
	}

	void crypt_network_manager::on_node_disconnected(std::string remoteId)
	{
		NodeDisconnected(remoteId);
	}
}