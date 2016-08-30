#ifndef __P2P_HOSTMANAGER_H_INCLUDED__
#define __P2P_HOSTMANAGER_H_INCLUDED__

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "p2p_host.hpp"

namespace dcp2p
{
	class p2p_hostmanager : public boost::enable_shared_from_this<p2p_hostmanager>
	{
	public:
		typedef boost::shared_ptr<p2p_hostmanager> pointer;

		static pointer Create(std::string filePath, std::vector<std::string> dnsSeeds, int defaultPort)
		{
			return pointer(new p2p_hostmanager(filePath, dnsSeeds, defaultPort), [=](p2p_hostmanager* inst)
			{
				inst->Shutdown();
			});
		}

		p2p_host GetNextHost();
		void Shutdown();

	private:
		p2p_hostmanager(std::string filePath, std::vector<std::string> dnsSeeds, int defaultPort);

		std::string _filePath;
		std::vector<std::string> _dnsSeeds;
		int _defaultPort;
		std::vector<p2p_host> _hosts;
		bool isFileExhausted;

		std::vector<p2p_host> getFromFile();
		std::vector<p2p_host> getFromDnsSeeds();
	};
}

#endif