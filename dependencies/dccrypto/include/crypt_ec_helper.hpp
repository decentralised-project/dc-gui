#ifndef __CRYPT_EC_HELPER_H_INCLUDED__
#define __CRYPT_EC_HELPER_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
using std::unique_ptr;

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/ecdsa.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>

namespace dccrypto
{
	class crypt_ec_helper
	{
	public:
		crypt_ec_helper();
		~crypt_ec_helper();

		EC_KEY* generate_key_pair();
		std::string get_public_key(EC_KEY *keypair);
		void save_key_pair(std::string path, EC_KEY *keypair);

	private:
	};
}

#endif