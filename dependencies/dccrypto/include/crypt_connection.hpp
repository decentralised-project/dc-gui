#ifndef __CRYPT_CONNECTION_H_INCLUDED__
#define __CRYPT_CONNECTION_H_INCLUDED__

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
#include "crypt_ec_helper.hpp"
#include "p2p_connection.hpp"

namespace dccrypto
{
	class crypt_connection : public boost::enable_shared_from_this<crypt_connection>
	{
	public:
		typedef boost::shared_ptr<crypt_connection> pointer;

		static pointer Create(crypt_ec_helper::pointer &helper, 
							  std::string remotePublicKey, 
							  EC_KEY* localKeyPair,
							  dcp2p::p2p_connection::pointer connection)
		{
			return pointer(new crypt_connection(helper, remotePublicKey, localKeyPair, connection));
		}

		const EC_POINT* GetRemotePublicKey();
		std::string GetRemotePublicKeyBase58();

	private:
		crypt_connection(crypt_ec_helper::pointer helper, 
						 std::string remotePublicKey, 
						 EC_KEY* localKeyPair, 
						 dcp2p::p2p_connection::pointer connection);

		unsigned char* shared_secret;
		int shared_secret_len;
		const EC_POINT* remote_public_key;
		std::string remote_public_key_base58;
		dccrypto::crypt_ec_helper::pointer ec;
		dcp2p::p2p_connection::pointer p2pconnection;
	};
}

#endif