#include "stdafx.h"
#include "CryptoAlgoritmProvider.h"
#include "../../exception/WinNtExc.h"
namespace CommonLib
{
	namespace crypto
	{
		namespace win
		{
			CBcryptAlgProviderPtr CBcryptAlgProvider::Create(LPCWSTR pszAlgId, ULONG dwFlags)
			{
				try
				{
					BCRYPT_ALG_HANDLE handle;
					NTSTATUS ntStatus = BCryptOpenAlgorithmProvider(&handle, pszAlgId, NULL, dwFlags);
					if (!BCRYPT_SUCCESS(ntStatus))
						throw CWinNtExc(ntStatus);
				}
				catch (std::exception& exc)
				{
					CExcBase::RegenExcT("CNG: Failed to create provider AlgId: %1, Flags: %2", pszAlgId, (uint32_t)dwFlags, exc);
					throw;
				}
			}

			CBcryptAlgProvider::CBcryptAlgProvider(BCRYPT_ALG_HANDLE phAlgorithm) : m_hAlgorithm(phAlgorithm)
			{

			}

			CBcryptAlgProvider::~CBcryptAlgProvider()
			{
				if (m_hAlgorithm)
					::BCryptCloseAlgorithmProvider(&m_hAlgorithm, 0);
			}


			void CBcryptAlgProvider::BCryptDeriveKeyPBKDF2(const crypto_astr& password, const crypto_vector& salt, uint64_t interations, uint32_t keySize, crypto_vector& derivedKey)
			{
				try
				{
					derivedKey.reserve(keySize);
					NTSTATUS ntStatus = ::BCryptDeriveKeyPBKDF2(m_hAlgorithm, (PUCHAR)password.c_str(), (ULONG)password.size(),
						(PUCHAR)salt.data(), (ULONG)salt.size(), interations, (PUCHAR)derivedKey.data(), derivedKey.size(), 0);

					if (!BCRYPT_SUCCESS(ntStatus))
						throw CWinNtExc(ntStatus);
				}
				catch (std::exception& exc)
				{
					CExcBase::RegenExc("CNG: Failed to derive key", exc);
					throw;
				}
			}

			void CBcryptAlgProvider::BCryptGenRandom(crypto_vector& random, uint32_t size, ULONG dwFlags)
			{
				try
				{
					random.reserve(size);
					NTSTATUS ntStatus = ::BCryptGenRandom(m_hAlgorithm, (PUCHAR)random.data(), random.size(), dwFlags);

					if (!BCRYPT_SUCCESS(ntStatus))
						throw CWinNtExc(ntStatus);
				}
				catch (std::exception& exc)
				{
					CExcBase::RegenExc("CNG: Failed get random", exc);
					throw;
				}
			}
		}
	}
}
