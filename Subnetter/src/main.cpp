#include "pch.h"

#define CP_SINGLE_HEADER
#include "CP.h"

#include "IP.h"

#define APP_NAME "Subnetter.exe"

size_t countDots(std::string ip)
{
	size_t i{0};
	for (const auto& value : ip)
	{
		value == '.' ? i++ : value ;
	}
	return i;
}

int main(int argc, char** args)
{
	auto cmdParser = CP::CommandParser(argc, args);
	cmdParser.RegisterCommand({ "-n", "Network", "Output Network with specified ID", 1 });
	cmdParser.RegisterCommand({ "-a", "All", "Output All Networks"});
	cmdParser.ConsumeFlags();

	if(!cmdParser.RequireParams(1) || cmdParser.GetParam(1).find_first_of('/') == std::string::npos || countDots(cmdParser.GetParam(1)) != 3 )
	{
		cmdParser.PrintUsage({ "ip/mask" });
		printf("Example: %s 192.168.100.5/24", APP_NAME);
		return 1;
	}

	const auto ipWithMaskLength = cmdParser.GetParam(1);
	size_t posOfSlash = ipWithMaskLength.find_first_of('/');

	const std::string ip = ipWithMaskLength.substr(0, posOfSlash);
	const char mask = stoi(ipWithMaskLength.substr(posOfSlash + 1, ipWithMaskLength.size()));

	Subnetter::IP myIp(ip, mask);

	printf("IP: %s\n", ip.c_str());
	printf("SN Bits: %i\n", mask);
	printf("NWA: %s\n", myIp.GetNetworkAddressString().c_str());
	printf("BCA: %s\n", myIp.GetBroadcastAdressString().c_str());
	printf("GATEWAY: %s\n", myIp.GetGatewayAddressString().c_str());
	printf("SN MASK: %s\n\n", myIp.GetSubnetMaskString().c_str());

	if(cmdParser.HasCommand("All"))
	{
		printf("Network Table:\n");
		// Print all Possible Network Addresses
		for (int i = 0; i < 1 << (32 - mask); ++i)
		{
			printf("NWA of Network %i: %s\n", i, myIp.GetNetworkAddressString(i).c_str());
			printf("BCA of Network %i: %s\n", i, myIp.GetBroadcastAdressString().c_str());
			printf("GATEWAY of Network %i: %s\n", i, myIp.GetGatewayAddressString().c_str());
			printf("Hosts per Network: %i\n\n", myIp.GetHostsPerNetwork());
		}
	}
	else if(cmdParser.HasCommand("Network"))
	{
		auto i = stoi(cmdParser.GetCommandParams("Network")->at(0));
		printf("NWA of Network %i: %s\n", i, myIp.GetNetworkAddressString().c_str());
		printf("BCA of Network %i: %s\n", i, myIp.GetBroadcastAdressString().c_str());
		printf("GATEWAY of Network %i: %s\n", i, myIp.GetGatewayAddressString().c_str());
		printf("Hosts per Network: %i\n\n", myIp.GetHostsPerNetwork());
	}
	

	return 0;
}
