#include "crypt_ec_helper.hpp"

namespace dccrypto
{
	crypt_ec_helper::crypt_ec_helper()
	{
	}

	crypt_ec_helper::~crypt_ec_helper()
	{
	}

	EC_KEY* crypt_ec_helper::generate_key_pair()
	{
		EC_KEY *eckey = EC_KEY_new();
		EC_GROUP *ecgroup = EC_GROUP_new_by_curve_name(NID_secp256k1);
		EC_KEY_set_group(eckey, ecgroup);
		EC_KEY_generate_key(eckey);

		return eckey;
	}

	std::string crypt_ec_helper::get_public_key(EC_KEY *keypair)
	{
		//EVP_PKEY *pkey = NULL;
		//pkey = EVP_PKEY_new();
		//EVP_PKEY_assign_EC_KEY(pkey, keypair);
		BIGNUM *x, *y;
		unsigned char *x_char, *y_char, *dgst;
		unsigned int dgstlen;

		BN_CTX* bn = BN_CTX_new();
		x = BN_new();
		y = BN_new();
		x_char = new unsigned char[32];
		y_char = new unsigned char[32];

		const EC_GROUP *group = NULL;
		group = EC_KEY_get0_group(keypair);

		EC_POINT* point = EC_POINT_new(group);

		EC_POINT_get_affine_coordinates_GFp(group, point, x, y, bn);

		BN_bn2bin(x, x_char);
		BN_bn2bin(y, y_char);

		EVP_MD_CTX md_ctx;
		EVP_MD_CTX_init(&md_ctx);
		EVP_DigestInit(&md_ctx, EVP_ripemd160());
		// hdr = 0x04
		EVP_DigestUpdate(&md_ctx, (void*)0x04, 1);
		EVP_DigestUpdate(&md_ctx, x_char, 32);
		EVP_DigestUpdate(&md_ctx, y_char, 32);
		// put message degest into dgst and set length to dgstlen
		EVP_DigestFinal(&md_ctx, dgst, &dgstlen);

		EVP_MD_CTX_cleanup(&md_ctx);
		BN_CTX_free(bn);
		BN_free(x);
		BN_free(y);

		delete x_char;
		delete y_char;

		return std::string(dgst, dgst + dgstlen);
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

		//BIO_printf(out, "ECC Key size: %d bit\n", EVP_PKEY_bits(pkey));
		//BIO_printf(out, "ECC Key type: %s\n", OBJ_nid2sn(EC_GROUP_get_curve_name(ecgroup)));

		i = PEM_write_bio_PrivateKey(out, pkey, NULL, NULL, 0, 0, NULL);
		//i = PEM_write_bio_PUBKEY(out, pkey);

		fclose(outfile);

		EVP_PKEY_free(pkey);
		BIO_free_all(out);
	}
}