#ifndef __CRYPT_EC_HELPER_H_INCLUDED__
#define __CRYPT_EC_HELPER_H_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <memory>

#include <openssl/bn.h>
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/ecdsa.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/ossl_typ.h>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace std;

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
		const EC_POINT* get_public_key(EC_KEY *keypair);
		std::string to_base58(const EC_POINT* public_key);
		const EC_POINT* from_base58(std::string base58);
		void save_key_pair(std::string path, EC_KEY *keypair);
		EC_KEY* load_key_pair(std::string path);
		int ecdh(unsigned char **secret, EC_KEY *key, const EC_POINT *pPub);
		int encrypt(unsigned char* cipherText, unsigned char *message, int messageLength, unsigned char *secret, int secretLength);
		int decrypt(unsigned char* cipherText, int cipherTextLen, unsigned char *secret, int secretLength, unsigned char* plainText);
		void shutdown();

	private:
		crypt_ec_helper();

		EC_KEY *eckey;
		EC_POINT *pub;
	};
}

#endif
