#pragma once

namespace CommonLib
{
	namespace network
	{
		class CSocketUtil
		{
		public:

			static void CheckSocketExc(SOCKET socket);
			static SOCKET GetInvalidSocket();
			static int GetSocketLastError();
			static bool IsEINTR(int error);
			static bool IsSocketError(int retVal);
			static bool IsBlockingError(int error);
			static bool IsConnectAborted(int error);

		};

	
	}
}