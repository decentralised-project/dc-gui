#include "crypt_connection.hpp"

namespace dccrypto
{
	crypt_connection::crypt_connection(crypt_ec_helper::pointer helper, 
									   std::string remotePublicKey, 
									   EC_KEY* localKeyPair,
									   dcp2p::p2p_connection::pointer connection) 
		: ec(helper), p2pconnection(connection)
	{
		shared_secret = NULL;
		remote_public_key_base58 = remotePublicKey;
		remote_public_key = helper->from_base58(remotePublicKey);
		shared_secret_len = helper->ecdh(&shared_secret, localKeyPair, remote_public_key);
	}

	const EC_POINT* crypt_connection::GetRemotePublicKey()
	{
		return remote_public_key;
	}

	std::string crypt_connection::GetRemotePublicKeyBase58()
	{
		return remote_public_key_base58;
	}

	int crypt_connection::Encrypt(unsigned char* cipher, unsigned char* data, size_t length)
	{
		return ec->encrypt(cipher, data, length, shared_secret, shared_secret_len);
	}

	dcp2p::p2p_connection::pointer crypt_connection::GetP2PConnection()
	{
		return p2pconnection;
	}
}