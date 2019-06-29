#pragma once

namespace Subnetter {

	class IP
	{
	public:
		IP(const std::string&, const unsigned char&);

		std::string GetNetworkAddressString();
		std::string GetGatewayAddressString();
		std::string GetBroadcastAdressString();
		std::string GetSubnetMaskString();

		std::string GetNetworkAddressString(const unsigned int&);

		unsigned int GetNetworkAddress() const;
		unsigned int GetSubnetMask() const;

		unsigned int GetHostsPerNetwork();


	private:
		unsigned int m_Segments;
		unsigned int m_Mask;
		unsigned char m_MaskRaw;
		unsigned int m_NetworkSize;
	};
}

