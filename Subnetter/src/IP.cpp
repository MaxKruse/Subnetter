#include "pch.h"
#include "IP.h"

namespace Subnetter {

	IP::IP(const std::string& ip, const unsigned char& mask)
		: m_Segments{0}, m_Mask{0}, m_MaskRaw{mask}
	{
		std::stringstream ss(ip);
		std::string item;
		unsigned int toShift = 24;

		while (std::getline(ss, item, '.'))
		{
			m_Segments |= static_cast<unsigned char>(stoi(item)) << toShift; 
			toShift -= 8;
		}

		for (auto i = 31; i > 31 - mask; i--)
		{
			m_Mask |= 1 << i;
		}

		m_NetworkSize = ~m_Mask;
	}

	std::string IP::GetNetworkAddressString()
	{
		std::string s;
		for (auto i = 3; i >= 0; i--)
		{
			unsigned int toShift = i * 8;
			unsigned int shifted = (0xFF << toShift);
			unsigned int mask = m_Mask & shifted;
			unsigned int segmentMasked = m_Segments & mask;

			s += std::to_string(segmentMasked >> toShift);
			if(i != 0)
			{
				s += ".";
			}
		}
		return s;
	}

	std::string IP::GetGatewayAddressString()
	{
		std::string s;
		unsigned int tempSegments = (m_Segments & m_Mask) + 1;
		for (auto i = 3; i >= 0; i--)
		{
			unsigned int toShift = i * 8;
			unsigned int shifted = (0xFF << toShift);
			unsigned int segmentMasked = tempSegments & shifted;

			s += std::to_string(segmentMasked >> toShift);
			if (i != 0)
			{
				s += ".";
			}
		}
		return s;
	}

	std::string IP::GetBroadcastAdressString()
	{
		std::string s;

		unsigned int tempSegments = (m_Segments & m_Mask);
		tempSegments |= ~m_Mask;

		for (auto i = 3; i >= 0; i--)
		{
			unsigned int toShift = i * 8;
			unsigned int shifted = (0xFF << toShift);
			unsigned int segmentMasked = (tempSegments) & (shifted);

			s += std::to_string(segmentMasked >> toShift);
			if (i != 0)
			{
				s += ".";
			}
			
		}
		return s;		
	}

	std::string IP::GetSubnetMaskString()
	{
		std::string s;
		for (auto i = 3; i >= 0; i--)
		{
			unsigned int toShift = i * 8;
			unsigned int shifted = (0xFF << toShift);
			unsigned int mask = m_Mask & shifted;
			s += std::to_string(mask >> toShift);
			if (i != 0)
			{
				s += ".";
			}
		}
		return s;
	}

	std::string IP::GetNetworkAddressString(const unsigned& id)
	{
		unsigned int addSize = (m_NetworkSize + 1) * id;

		const unsigned int trueMaskAmount = [=]
		{
			if(m_MaskRaw >= 24)
			{
				return 24;
			}

			if (m_MaskRaw >= 16)
			{
				return 16;
			}

			return 8;
		}();

 		unsigned int tempSegments{0};

		const auto count = trueMaskAmount / 8;

		for (unsigned int i = count; i > 0; i--)
		{
			const unsigned int toShift = i * 8;
			const unsigned int shifted = (0xFF << toShift);
			const unsigned int mask = m_Mask & shifted;
			const unsigned int segmentMasked = m_Segments & mask;

			tempSegments |= segmentMasked;
		}

		for (unsigned int i = 4 - count; i > 0; i--)
		{
			tempSegments += addSize;
		}

		std::string s;
		for (auto i = 3; i >= 0; i--)
		{
			unsigned int toShift = i * 8;
			unsigned int shifted = (0xFF << toShift);
			unsigned int mask = m_Mask & shifted;
			unsigned int segmentMasked = tempSegments & mask;

			s += std::to_string(segmentMasked >> toShift);
			if (i != 0)
			{
				s += ".";
			}
		}
		return s;
	}

	unsigned int IP::GetNetworkAddress() const
	{
		return m_Segments;
	}

	unsigned int IP::GetSubnetMask() const
	{
		return m_Mask;
	}

	unsigned IP::GetHostsPerNetwork()
	{
		return m_NetworkSize - 1;
	}
}
