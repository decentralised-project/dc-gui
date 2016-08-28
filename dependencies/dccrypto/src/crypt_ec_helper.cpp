#include "crypt_ec_helper.hpp"

namespace dccrypto
{
	static const char* pszBase58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

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

	const EC_POINT* crypt_ec_helper::get_public_key(EC_KEY *keypair)
	{
		const EC_POINT *priv_bn;
		return EC_KEY_get0_public_key(keypair);
	}

	std::string crypt_ec_helper::to_base58(const EC_POINT* public_key)
	{
		unsigned char *ret = new unsigned char[2048];
		EC_GROUP *ecgrp = EC_GROUP_new_by_curve_name(NID_secp256k1);

		size_t len = EC_POINT_point2oct(ecgrp, public_key, POINT_CONVERSION_UNCOMPRESSED, NULL, 0, NULL);
		EC_POINT_point2oct(ecgrp, public_key, POINT_CONVERSION_UNCOMPRESSED, ret, len, NULL);

		unsigned char* pbegin = ret;
		unsigned char* pend = ret + len;

		// Skip & count leading zeroes.
		int zeroes = 0;
		int length = 0;
		while (pbegin != pend && *pbegin == 0) {
			pbegin++;
			zeroes++;
		}
		// Allocate enough space in big-endian base58 representation.
		int size = (pend - pbegin) * 138 / 100 + 1; // log(256) / log(58), rounded up.
		std::vector<unsigned char> b58(size);
		// Process the bytes.
		while (pbegin != pend) {
			int carry = *pbegin;
			int i = 0;
			// Apply "b58 = b58 * 256 + ch".
			for (std::vector<unsigned char>::reverse_iterator it = b58.rbegin(); (carry != 0 || i < length) && (it != b58.rend()); it++, i++) {
				carry += 256 * (*it);
				*it = carry % 58;
				carry /= 58;
			}

			assert(carry == 0);
			length = i;
			pbegin++;
		}
		// Skip leading zeroes in base58 result.
		std::vector<unsigned char>::iterator it = b58.begin() + (size - length);
		while (it != b58.end() && *it == 0)
			it++;
		// Translate the result into a string.
		std::string str;
		str.reserve(zeroes + (b58.end() - it));
		str.assign(zeroes, '1');
		while (it != b58.end())
			str += pszBase58[*(it++)];

		free(ret);
		EC_GROUP_free(ecgrp);

		return str;
	}

	const EC_POINT* crypt_ec_helper::from_base58(std::string base58)
	{
		const char* psz = base58.c_str();
		std::vector<unsigned char> vch;

		// Skip leading spaces.
		while (*psz && isspace(*psz))
			psz++;
		// Skip and count leading '1's.
		int zeroes = 0;
		while (*psz == '1') {
			zeroes++;
			psz++;
		}
		// Allocate enough space in big-endian base256 representation.
		std::vector<unsigned char> b256(strlen(psz) * 733 / 1000 + 1); // log(58) / log(256), rounded up.
		// Process the characters.
		while (*psz && !isspace(*psz)) {
			// Decode base58 character
			const char* ch = strchr(pszBase58, *psz);
			if (ch == NULL)
				return false;
			// Apply "b256 = b256 * 58 + ch".
			int carry = ch - pszBase58;
			for (std::vector<unsigned char>::reverse_iterator it = b256.rbegin(); it != b256.rend(); it++) {
				carry += 58 * (*it);
				*it = carry % 256;
				carry /= 256;
			}
			assert(carry == 0);
			psz++;
		}
		// Skip trailing spaces.
		while (isspace(*psz))
			psz++;
		if (*psz != 0)
			return false;
		// Skip leading zeroes in b256.
		std::vector<unsigned char>::iterator it = b256.begin();
		while (it != b256.end() && *it == 0)
			it++;
		// Copy result into output vector.
		vch.reserve(zeroes + (b256.end() - it));
		vch.assign(zeroes, 0x00);
		while (it != b256.end())
			vch.push_back(*(it++));

		EC_GROUP *ecgrp = EC_GROUP_new_by_curve_name(NID_secp256k1);
		EC_POINT *pub = EC_POINT_new(ecgrp);

		size_t len = EC_POINT_oct2point(ecgrp, pub, vch.data(), vch.size(), NULL);
		
		EC_GROUP_free(ecgrp);

		return pub;
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

	EC_KEY* crypt_ec_helper::load_key_pair(std::string path)
	{
		BIO *in;
		int i;
		FILE* infile;
		EVP_PKEY *pkey = NULL;

		ERR_load_BIO_strings();
		ERR_load_crypto_strings();

		pkey = EVP_PKEY_new();

		EC_GROUP *ecgroup = EC_GROUP_new_by_curve_name(NID_secp256k1);

		infile = fopen(path.c_str(), "r");

		in = BIO_new(BIO_s_file());
		in = BIO_new_fp(infile, BIO_NOCLOSE);

		PEM_read_bio_PrivateKey(in, &pkey, NULL, NULL);

		fclose(infile);

		eckey = EVP_PKEY_get1_EC_KEY(pkey);

		EVP_PKEY_free(pkey);
		BIO_free_all(in);

		return eckey;
	}

	int crypt_ec_helper::ecdh(unsigned char **secret, EC_KEY *key, const EC_POINT *pPub)
	{
		int secretLen;

		secretLen = EC_GROUP_get_degree(EC_KEY_get0_group(key));
		secretLen = (secretLen + 7) / 8;

		*secret = (unsigned char*)malloc(secretLen);
		if (!(*secret))
		{
			fflush(stderr);
			free(*secret);
			throw std::runtime_error("Failed to allocate memory for secret.\n");
		}
		secretLen = ECDH_compute_key(*secret, secretLen, pPub, key, NULL);

		return secretLen;
	}

	// Credit: https://github.com/keeshux
	// ↓↓↓↓ Based on code from https://github.com/keeshux/basic-blockchain-programming/blob/master/base58.h

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