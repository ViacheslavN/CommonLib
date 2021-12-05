#include "stdafx.h"
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include "OpenSSlLib.h"

namespace CommonLib
{
	namespace crypto
	{
		namespace openssllib
		{
			COpenSSlLIb COpenSSlLIb::inst;

			COpenSSlLIb::COpenSSlLIb()
			{
				OpenSSL_add_all_algorithms();
				ERR_load_crypto_strings();
				RAND_status();
			}

			COpenSSlLIb::~COpenSSlLIb()
			{
				EVP_cleanup();
				ERR_free_strings();
			}

			COpenSSlLIb& COpenSSlLIb::Instance()
			{
				return inst;
			}

		}
	}
}