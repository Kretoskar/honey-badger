#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/Guid.h"

namespace HoneyBadger
{
	HBString GenerateGUID()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 15);  // Hex values are from 0 to 15

		// Generate random 128-bit GUID (16 bytes)
		std::ostringstream guidStream;
		for (int i = 0; i < 16; ++i)
		{
			if (i == 6)
			{
				// Set the version field (4 bits, the version is 4 for UUIDv4)
				guidStream << std::hex << (dis(gen) & 0x0f | 0x40);
			}
			else if (i == 8)
			{
				// Set the variant (2 bits, variant is 10 for UUIDv4)
				guidStream << std::hex << (dis(gen) & 0x3f | 0x80);
			}
			else
			{
				guidStream << std::hex << dis(gen);
			}

			// Add hyphens after certain positions
			if (i == 3 || i == 5 || i == 7 || i == 9)
			{
				guidStream << "-";
			}
		}

		return guidStream.str();
	}
}