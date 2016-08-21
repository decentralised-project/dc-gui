#include "p2p_hostmanager.hpp"

namespace dcp2p
{
	p2p_hostmanager::p2p_hostmanager(std::string filePath, std::vector<std::string> dnsSeeds, int defaultPort)
	{
		_filePath = filePath;
		_defaultPort = defaultPort;
		_dnsSeeds = dnsSeeds;
		_hosts = getFromFile();
		isFileExhausted = false;
	}

	p2p_host p2p_hostmanager::GetNextHost()
	{
		if (_hosts.size() == 0)
		{
			if (!isFileExhausted)
			{
				isFileExhausted = true;

				_hosts = getFromDnsSeeds();
				if (_hosts.size() == 0)
					return p2p_host(); // none left, return empty
			}
			else
				return p2p_host(); // none left, return empty
		}

		srand(time(NULL));
		int chosenIndex = rand() % _hosts.size();
		p2p_host chosen = _hosts[chosenIndex];
		_hosts.erase(_hosts.begin() + chosenIndex);

		return chosen;
	}

	std::vector<p2p_host> p2p_hostmanager::getFromFile()
	{
		std::vector<p2p_host> hosts;

		return hosts;
	}

	std::vector<p2p_host> p2p_hostmanager::getFromDnsSeeds()
	{
		std::vector<p2p_host> hosts;
		for (std::vector<std::string>::iterator it = _dnsSeeds.begin(); it != _dnsSeeds.end(); ++it) {

			boost::asio::io_service io_service;
			boost::asio::ip::tcp::resolver resolver(io_service);
			boost::asio::ip::tcp::resolver::query query(it->c_str(), "");
			for (boost::asio::ip::tcp::resolver::iterator i = resolver.resolve(query);
				i != boost::asio::ip::tcp::resolver::iterator();
				++i)
			{
				boost::asio::ip::tcp::endpoint end = *i;

				bool ipExists = false;
				for (int j = 0; j < hosts.size(); ++j)
				{
					if (hosts[j].GetIp() == end.address().to_string())
					{
						ipExists = true;
						break;
					}
				}
				if (!ipExists)
				{
					p2p_host host(end.address().to_string(), _defaultPort, 0);
					hosts.push_back(host);
				}
			}
		}

		return hosts;
	}
}