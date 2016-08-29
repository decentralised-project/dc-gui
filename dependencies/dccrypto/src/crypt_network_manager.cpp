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

		//ERR_load_crypto_strings();
		//OpenSSL_add_all_algorithms();

		//std::string testMessage = "The quick brown fox jumped over the lazy dog ...";

		//unsigned char *testMessagePtr = (unsigned char*)testMessage.c_str();
		//unsigned char *cipherText = new unsigned char[testMessage.size() + 1024];
		//int cipherTextLen = helper->encrypt(cipherText, testMessagePtr, testMessage.size(), secret, secretLen);
		//std::string cipherStr = std::string(cipherText, cipherText + cipherTextLen);

		//Log(std::string("Test Encrypted: ").append(cipherStr));

		//unsigned char *cipherTextPtr = (unsigned char*)cipherStr.c_str();
		//unsigned char *plainText = new unsigned char[cipherStr.size() + 4096];
		//int plainTextLen = helper->decrypt(cipherText, cipherTextLen, secret, secretLen, plainText);
		//std::string plainStr = std::string(plainText, plainText + plainTextLen);

		//Log(std::string("Test Decrypted: ").append(plainStr));

		//free(cipherText);
		//free(plainText);
		//ERR_free_strings();

		NodeConnected(isIncoming, connection, remoteId);
	}

	void crypt_network_manager::on_data_recieved(dcp2p::p2p_connection::pointer connection, dcp2p::p2p_packet packet)
	{
		DataReceived(connection, packet);
	}

	void crypt_network_manager::on_node_disconnected(std::string remoteId)
	{
		NodeDisconnected(remoteId);
	}
}