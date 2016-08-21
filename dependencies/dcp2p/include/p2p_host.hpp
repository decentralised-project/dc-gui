#ifndef __P2P_HOST_H_INCLUDED__
#define __P2P_HOST_H_INCLUDED__

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <iostream>

namespace dcp2p
{
	class p2p_host
	{
	public:
		p2p_host();
		p2p_host(std::string ip, int port, int rating);
		~p2p_host();

		void set(std::string ip, int port, int rating);

		bool IsEmpty();
		std::string GetIp();
		int GetPort();
		int GetRating();

	private:

		bool _isEmpty;
		std::string _ip;
		int _port;
		int _rating;
	};
}

#endif