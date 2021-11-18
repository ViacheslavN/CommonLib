#include "stdafx.h"
#include "VfsIO.h"
#include "SqliteVfs.h"
#include "../db/sqlite3.h"

namespace CommonLib
{
	namespace sqlite
	{
		namespace impl
		{
		
			CVfsIO::CVfsIO(ICryptoContextPtr ptrCryptoContext) : m_ptrCryptoContext(ptrCryptoContext)
			{

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

				std::vector<byte_t> data(8192);
				if (fileSize == 0)
				{
	
					retVal = IoWrite(pFile, &data[0], data.size(), 0);
					if (retVal != SQLITE_OK)
						return retVal;
					//Init salt
				}
				else
				{
					retVal = IoRead(pFile, &data[0], data.size(), 0);
					if (retVal != SQLITE_OK)
						return retVal;
				}

				pFile->offset = 8192;
				//retVal = SQLITE_AUTH;
				return retVal;

			}

			int CVfsIO::IoClose(sqlite3En_file *pFile)
			{
				return REALFILE(pFile)->pMethods->xClose(REALFILE(pFile));
			}

			int CVfsIO::IoRead(sqlite3En_file* pFile, void* pBuf, int iAmt, sqlite3_int64 iOfst)
			{
				return REALFILE(pFile)->pMethods->xRead(REALFILE(pFile), pBuf, iAmt, iOfst + pFile->offset);
			}

			int CVfsIO::IoWrite(sqlite3En_file* pFile, const void* pBuf, int iAmt, sqlite3_int64 iOfst)
			{
				return REALFILE(pFile)->pMethods->xWrite(REALFILE(pFile), pBuf, iAmt, iOfst + pFile->offset);
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