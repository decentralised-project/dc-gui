#include "crypt_ec_helper.hpp"

namespace dccrypto
{
	crypt_ec_helper::crypt_ec_helper()
	{
		eckey = NULL;
		public_key = NULL;
	}

	void crypt_ec_helper::shutdown()
	{
		if (eckey)
			EC_KEY_free(eckey);

		if (public_key)
			free(public_key);
	}

	EC_KEY* crypt_ec_helper::generate_key_pair()
	{
		eckey = EC_KEY_new();
		EC_GROUP *ecgroup = EC_GROUP_new_by_curve_name(NID_secp256k1);
		EC_KEY_set_group(eckey, ecgroup);
		EC_KEY_generate_key(eckey);

		return eckey;
	}

	EC_KEY* crypt_ec_helper::get_key_pair()
	{
		return eckey;
	}

	std::string crypt_ec_helper::get_public_key(EC_KEY *keypair)
	{
		const EC_POINT *priv_bn;
		priv_bn = EC_KEY_get0_public_key(keypair);

		size_t pub_len;
		uint8_t *pub_copy;

		EC_KEY_set_conv_form(keypair, POINT_CONVERSION_COMPRESSED);

		pub_len = i2o_ECPublicKey(keypair, NULL);
		public_key = (uint8_t*)calloc(pub_len, sizeof(uint8_t));

		/* pub_copy is needed because i2o_ECPublicKey alters the input pointer */
		pub_copy = public_key;
		if (i2o_ECPublicKey(keypair, &pub_copy) != pub_len) {
			puts("Unable to decode public key");
			return "Error";
		}

		return std::string(base58(public_key, pub_len));
	}

	void crypt_ec_helper::save_key_pair(std::string path, EC_KEY *keypair)
	{
		BIO *out;
		int i;
		FILE* outfile;
		EVP_PKEY          *pkey = NULL;

		ERR_load_BIO_strings();
		ERR_load_crypto_strings();

		pkey = EVP_PKEY_new();
		EVP_PKEY_assign_EC_KEY(pkey, keypair);

		EC_GROUP *ecgroup = EC_GROUP_new_by_curve_name(NID_secp256k1);

		outfile = fopen(path.c_str(), "w");

		out = BIO_new(BIO_s_file());
		out = BIO_new_fp(outfile, BIO_NOCLOSE);

		EC_KEY_set_asn1_flag(keypair, OPENSSL_EC_NAMED_CURVE);

		i = PEM_write_bio_PrivateKey(out, pkey, NULL, NULL, 0, 0, NULL);

		fclose(outfile);

		EVP_PKEY_free(pkey);
		BIO_free_all(out);
	}

	// Credit: https://github.com/keeshux
	// Based on code from https://github.com/keeshux/basic-blockchain-programming/blob/master/base58.h

	static const char base58_alphabet[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

	char* crypt_ec_helper::base58(const uint8_t *bytes, size_t len)
	{
		size_t str_len;
		char *str;
		BN_CTX *ctx;
		BIGNUM base, x, r;
		int i, j;

		str_len = len * 138 / 100 + 2;
		str = (char*)calloc(str_len, sizeof(char));

		ctx = BN_CTX_new();
		BN_CTX_start(ctx);

		BN_init(&base);
		BN_init(&x);
		BN_init(&r);
		BN_set_word(&base, 58);
		BN_bin2bn(bytes, len, &x);

		i = 0;
		while (!BN_is_zero(&x)) {
			BN_div(&x, &r, &x, &base, ctx);
			str[i] = base58_alphabet[BN_get_word(&r)];
			++i;
		}
		for (j = 0; j < len; ++j) {
			if (bytes[j] != 0x00) {
				break;
			}
			str[i] = base58_alphabet[0];
			++i;
		}
		reverse((uint8_t *)str, i);

		BN_clear_free(&r);
		BN_clear_free(&x);
		BN_free(&base);
		BN_CTX_end(ctx);
		BN_CTX_free(ctx);

		return str;
	}

	void crypt_ec_helper::reverse(uint8_t *dst, size_t len)
	{
		size_t i;
		const size_t stop = len >> 1;
		for (i = 0; i < stop; ++i) {
			uint8_t *left = dst + i;
			uint8_t *right = dst + len - i - 1;
			const uint8_t tmp = *left;
			*left = *right;
			*right = tmp;
		}
	}
}