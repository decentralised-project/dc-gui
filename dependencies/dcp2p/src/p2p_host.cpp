#include "p2p_host.hpp"

namespace dcp2p
{
	p2p_host::p2p_host()
	{
		_isEmpty = true;
	}

	p2p_host::p2p_host(std::string ip, int port, int rating)
	{
		set(ip, port, rating);
	}

	p2p_host::~p2p_host()
	{
	}

	void p2p_host::set(std::string ip, int port, int rating)
	{
		_isEmpty = false;

		_ip = ip;
		_port = port;
		_rating = rating;
	}

	std::string p2p_host::GetIp()
	{
		return _ip;
	}

	int p2p_host::GetPort()
	{
		return _port;
	}

	int p2p_host::GetRating()
	{
		return _rating;
	}

	bool p2p_host::IsEmpty()
	{
		return _isEmpty;
	}
}