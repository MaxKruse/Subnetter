#pragma once

namespace Subnetter {

	class IP
	{
	public:
		IP(const std::string&, const unsigned char&);

		std::string GetNetworkAddressString();
		std::string GetGatewayAddressString();
		std::string GetBroadcastAddressString();
		std::string GetSubnetMaskString();

		std::string GetNetworkAddressString(const unsigned int&);
		std::string GetBroadcastAddressString(const unsigned int&);
		std::string GetGatewayAddressString(const unsigned int&);

		unsigned int GetNetworkAddress() const;
		unsigned int GetBroadcastAddress() const;
		unsigned int GetSubnetMask() const;

		unsigned int GetHostsPerNetwork();
		unsigned int GetAddress(const unsigned int&);

		static std::string GetAddressString(const unsigned int&, const unsigned int&);


	private:
		unsigned int m_Segments;
		unsigned int m_Mask;
		unsigned char m_MaskRaw;
		unsigned int m_NetworkSize;
	};
}

