#include "stdafx.h"
#include "VfsIO.h"
#include "SqliteVfs.h"
#include "../db/sqlite3.h"
#include "../../../CryptoData.h"

#define INIT_PAGE_SIZE 8192
#define SQLITE_DEFAULT_PAGE_SIZE 4096
#define SQLITE_MAX_PAGE_SIZE 65536

namespace CommonLib
{
	namespace sqlite
	{
		namespace impl
		{
		
			CVfsIO::CVfsIO(ICryptoContextPtr ptrCryptoContext) : m_ptrCryptoContext(ptrCryptoContext)
			{
				m_buffer.resize(SQLITE_DEFAULT_PAGE_SIZE);
			}

			CVfsIO::~CVfsIO()
			{

			}

			int CVfsIO::ValidatePwd(sqlite3En_file *pFile)
			{
				sqlite3_int64 fileSize = 0;
				int retVal = SQLITE_OK;
				retVal = IoFileSize(pFile, &fileSize);
				if (retVal != SQLITE_OK)
					return retVal;

				if (fileSize == 0)
				{
					retVal = CreateInitPage(pFile);
					if (retVal != SQLITE_OK)
						return retVal;
				}
				else
				{
					retVal = CheckInitPage( pFile);
					if (retVal != SQLITE_OK)
						return retVal;
				}
				return retVal;
			}

			int CVfsIO::CreateInitPage(sqlite3En_file* pFile)
			{
				size_t size =  m_ptrCryptoContext->GetInitBlockSize();
				crypto::crypto_vector vecBuffer(size);
				m_ptrCryptoContext->CreateInitBlock(vecBuffer.data(), vecBuffer.size());
				m_ptrXTSDataCipher = m_ptrCryptoContext->GetXTSDataCipher();
				
				int rc = REALFILE(pFile)->pMethods->xWrite(REALFILE(pFile), vecBuffer.data(), (int)vecBuffer.size(), 0);
				pFile->offset = size;

				return rc;
			}


			int CVfsIO::CheckInitPage(sqlite3En_file* pFile)
			{
				size_t size = m_ptrCryptoContext->GetInitBlockSize();
				crypto::crypto_vector vecBuffer(size);

				int rc = REALFILE(pFile)->pMethods->xRead(REALFILE(pFile), vecBuffer.data(), (int)vecBuffer.size(), 0);
				pFile->offset = size;

				if (!m_ptrCryptoContext->ValidateInitBlock(vecBuffer.data(), vecBuffer.size()))
					return SQLITE_AUTH;

				m_ptrXTSDataCipher = m_ptrCryptoContext->GetXTSDataCipher();
				
				return rc;
			}

			int CVfsIO::IoClose(sqlite3En_file *pFile)
			{
				return REALFILE(pFile)->pMethods->xClose(REALFILE(pFile));
			}

			int CVfsIO::IoRead(sqlite3En_file* pFile, void* pBuf, int iAmt, sqlite3_int64 iOfst)
			{				

				const int pageOffset = iOfst % SQLITE_DEFAULT_PAGE_SIZE;
				const int deltaOffset = iAmt % SQLITE_DEFAULT_PAGE_SIZE;
				int rc = SQLITE_OK;
				if (pageOffset || deltaOffset)
				{
					const sqlite3_int64 prevOffset = iOfst - pageOffset;
					rc = REALFILE(pFile)->pMethods->xRead(REALFILE(pFile), m_buffer.data(), (int)m_buffer.size(), prevOffset + pFile->offset);
					if (rc == SQLITE_IOERR_SHORT_READ)
					{
						return rc;
					}

					sqlite3_int64 pageNo = (prevOffset / SQLITE_DEFAULT_PAGE_SIZE) + 1;
					m_ptrXTSDataCipher->Decrypt(pageNo, m_buffer.data(), (int)m_buffer.size());

					memcpy(pBuf, m_buffer.data() + deltaOffset, iAmt);

				}
				else
				{
					int rc = REALFILE(pFile)->pMethods->xRead(REALFILE(pFile), pBuf, iAmt, iOfst + pFile->offset);
					if (rc == SQLITE_IOERR_SHORT_READ)
					{
						return rc;
					}

					byte_t* data = (byte_t*)pBuf;
					int pageNo = (int)(iOfst / SQLITE_DEFAULT_PAGE_SIZE) + 1;
					int nPages = iAmt / SQLITE_DEFAULT_PAGE_SIZE;
					int iPage;
					for (iPage = 0; iPage < nPages; ++iPage)
					{
						m_ptrXTSDataCipher->Decrypt(pageNo, data, SQLITE_DEFAULT_PAGE_SIZE);
						data += SQLITE_DEFAULT_PAGE_SIZE;
						iAmt += SQLITE_DEFAULT_PAGE_SIZE;
						++pageNo;
					}
				}			 

				return rc;
			}

			int CVfsIO::IoWrite(sqlite3En_file* pFile, const void* pBuf, int iAmt, sqlite3_int64 iOfst)
			{
 
				const int deltaOffset = iOfst % SQLITE_DEFAULT_PAGE_SIZE;
				const int deltaCount = iAmt % SQLITE_DEFAULT_PAGE_SIZE;
				int rc = SQLITE_OK;

				if (deltaOffset || deltaCount)
				{
					rc = REALFILE(pFile)->pMethods->xWrite(REALFILE(pFile), pBuf, iAmt, iOfst + pFile->offset);
				}
				else
				{
					/*
					** Write full page(s)
					**
					** In fact, SQLite writes only one database page at a time.
					** This would allow to remove the page loop below.
					*/
					byte_t* data = (byte_t*)pBuf;
					int pageNo = iOfst / SQLITE_DEFAULT_PAGE_SIZE + 1;
					int nPages = iAmt / SQLITE_DEFAULT_PAGE_SIZE;
					int iPage;
					for (iPage = 0; iPage < nPages; ++iPage)
					{
						m_ptrXTSDataCipher->Encrypt(pageNo, data, SQLITE_DEFAULT_PAGE_SIZE, m_buffer.data());
						rc = REALFILE(pFile)->pMethods->xWrite(REALFILE(pFile), m_buffer.data(), SQLITE_DEFAULT_PAGE_SIZE, iOfst + pFile->offset);
						if (rc != SQLITE_OK)
							return rc;

						data += SQLITE_DEFAULT_PAGE_SIZE;
						iOfst += SQLITE_DEFAULT_PAGE_SIZE;
						++pageNo;
					}
				}

				return rc;
			}
			
			int CVfsIO::IoTruncate(sqlite3En_file* pFile, sqlite3_int64 size)
			{
				return REALFILE(pFile)->pMethods->xTruncate(REALFILE(pFile), size);
			}

			int CVfsIO::IoSync(sqlite3En_file* pFile, int flags)
			{
				return REALFILE(pFile)->pMethods->xSync(REALFILE(pFile), flags);
			}

			int CVfsIO::IoFileSize(sqlite3En_file* pFile, sqlite3_int64* pSize)
			{
				int retVal  =  REALFILE(pFile)->pMethods->xFileSize(REALFILE(pFile), pSize);
				if (retVal == SQLITE_OK)
				{
					*pSize -= pFile->offset;
				}

				return retVal;
			}

			int CVfsIO::IoLock(sqlite3En_file* pFile, int lock)
			{
				return REALFILE(pFile)->pMethods->xLock(REALFILE(pFile), lock);
			}

			int CVfsIO::IoUnlock(sqlite3En_file* pFile, int lock)
			{
				return REALFILE(pFile)->pMethods->xUnlock(REALFILE(pFile), lock);
			}

			int CVfsIO::IoCheckReservedLock(sqlite3En_file* pFile, int *pResOut)
			{
				return REALFILE(pFile)->pMethods->xCheckReservedLock(REALFILE(pFile), pResOut);
			}

			int CVfsIO::IoFileControl(sqlite3En_file* pFile, int op, void *pArg)
			{
				return REALFILE(pFile)->pMethods->xFileControl(REALFILE(pFile), op, pArg);
			}

			int CVfsIO::IoSectorSize(sqlite3En_file* pFile)
			{
				return REALFILE(pFile)->pMethods->xSectorSize(REALFILE(pFile));
			}

			int CVfsIO::IoDeviceCharacteristics(sqlite3En_file* pFile)
			{
				return REALFILE(pFile)->pMethods->xDeviceCharacteristics(REALFILE(pFile));
			}

			int CVfsIO::IoShmMap(sqlite3En_file* pFile, int iPg, int pgsz, int map, void volatile** p)
			{
				return REALFILE(pFile)->pMethods->xShmMap(REALFILE(pFile), iPg, pgsz, map, p);
			}

			int CVfsIO::IoShmLock(sqlite3En_file* pFile, int offset, int n, int flags)
			{
				return REALFILE(pFile)->pMethods->xShmLock(REALFILE(pFile), offset, n, flags);
			}

			void CVfsIO::IoShmBarrier(sqlite3En_file* pFile)
			{
				REALFILE(pFile)->pMethods->xShmBarrier(REALFILE(pFile));
			}

			int CVfsIO::IoShmUnmap(sqlite3En_file* pFile, int deleteFlag)
			{
				return REALFILE(pFile)->pMethods->xShmUnmap(REALFILE(pFile), deleteFlag);
			}

			int CVfsIO::IoFetch(sqlite3En_file* pFile, sqlite3_int64 iOfst, int iAmt, void** pp)
			{
				return REALFILE(pFile)->pMethods->xFetch(REALFILE(pFile), iOfst, iAmt, pp);
			}

			int CVfsIO::IoUnfetch(sqlite3En_file* pFile, sqlite3_int64 iOfst, void* p)
			{
				return REALFILE(pFile)->pMethods->xUnfetch(REALFILE(pFile), iOfst, p);
			}
		}
	}
}