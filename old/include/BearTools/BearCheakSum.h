#pragma once
namespace BearCore
{

	class BEARTOOL_API BearCheckSum
	{
	public:
		static void SHA256(void*data, bsize size, uint8 sha[]);
		static uint32 CRC32(void*data, bsize size);
	};
}