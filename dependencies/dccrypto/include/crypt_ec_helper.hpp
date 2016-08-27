#ifndef __CRYPT_EC_HELPER_H_INCLUDED__
#define __CRYPT_EC_HELPER_H_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include <openssl/bn.h>
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/ecdsa.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace dccrypto
{
	class crypt_ec_helper : public boost::enable_shared_from_this<crypt_ec_helper>
	{
	public:
		typedef boost::shared_ptr<crypt_ec_helper> pointer;

		static pointer Create()
		{
			return pointer(new crypt_ec_helper(), [=](crypt_ec_helper* inst)
			{
				inst->shutdown();
			});
		}

		EC_KEY* generate_key_pair();
		EC_KEY* get_key_pair();
		std::string get_public_key(EC_KEY *keypair);
		void save_key_pair(std::string path, EC_KEY *keypair);
		EC_KEY* load_key_pair(std::string path);
		unsigned char *ecdh(size_t *secret_len);
		void shutdown();

	private:
		crypt_ec_helper();

		char* base58(const uint8_t *bytes, size_t len);
		void reverse(uint8_t *dst, size_t len);

		EC_KEY *eckey;
		uint8_t *public_key;
	};
}

#endif