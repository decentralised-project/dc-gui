#ifndef __CRYPT_NETWORK_MANAGER_H_INCLUDED__
#define __CRYPT_NETWORK_MANAGER_H_INCLUDED__

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

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "p2p_manager.hpp"

namespace dccrypto
{
	class crypt_network_manager : public boost::enable_shared_from_this<crypt_network_manager>
	{
	public:
		typedef boost::shared_ptr<crypt_network_manager> pointer;

		static pointer Create(std::string dataDirPath)
		{
			return pointer(new crypt_network_manager(dataDirPath));
		}

	private:
		crypt_network_manager(std::string dataDirPath);
	};
}

#endif