#pragma once

#include "../crypto/IDataCipher.h"

namespace CommonLib
{
	namespace sqlite
	{

		typedef std::shared_ptr<class IDatabase> IDatabasePtr;
		typedef std::shared_ptr<class IStatment> IStatmentPtr;
		typedef std::shared_ptr<class IInsertCursor> IInsertCursorPtr;
		typedef std::shared_ptr<class ITransaction> ITransactionPtr;
		typedef std::shared_ptr<class ICryptoContext> ICryptoContextPtr;
		

		enum EDatabaseFlags
		{
			CreateDatabase = 1,
			MultithreadMode = 2,
			ReadOnlyMode = 4,
			WAL = 8
		};

		enum ESqliteFieldType
		{
			SqliteInteger,
			SqliteFloat,
			SqliteText,
			SqliteBlob,
			SqliteNull
		};

		enum EKeyCryptoType
		{
			Unknown = 0,
			MasterKey,
			PwdKey
		};

		class ICryptoContext
		{
		public:
			ICryptoContext() = default;
			virtual ~ICryptoContext() {}
 
			virtual crypto::IXTSDataCipherPtr GetXTSDataCipher() = 0;
			virtual size_t GetInitBlockSize() const = 0;
			virtual void CreateInitBlock(byte_t *pBuf, size_t size) = 0;
			virtual bool ValidateInitBlock(byte_t *pBuf, size_t size) = 0;


			static void AddCryptoContext(const astr& databaseName, ICryptoContextPtr ptrCryptoContex);
			static void RemoveCryptoContext(const astr& databaseName);
		};

		class IDatabase
		{
		public:
			IDatabase() = default;
			virtual ~IDatabase(){}

			virtual IStatmentPtr PrepareQuery(const char *pszQuery) const = 0;
			virtual void Execute(const char *pszQuery) = 0;
			virtual int32_t GetChanges() const noexcept  = 0;
			virtual int64_t GetLastInsertRowID() const noexcept  = 0;
			virtual bool IsReadOnly() const noexcept = 0;
			virtual bool IsTableExists(const char *pszTable) const = 0;
			virtual void SetBusyTimeout(int ms) noexcept = 0;
			
			static IDatabasePtr Create(const char *pszFile, uint32_t flags);

		};

		class ITransaction
		{
		public:
			ITransaction() = default;
			virtual ~ITransaction() {}

			virtual void Begin() = 0;
			virtual void Commit() = 0;
			virtual void Rollback() = 0;

			static ITransactionPtr CreateTransaction(IDatabasePtr ptrDatabase);
		};


		class IStatment
		{
		public:
			IStatment() = default;
			virtual ~IStatment() {}

			virtual bool Next() = 0;
			virtual void Reset() = 0;
			virtual int32_t  ColumnCount() const = 0;
			virtual astr ColumnName(int32_t col) const = 0;
			virtual bool ColumnIsNull(int32_t col) const = 0;
			virtual ESqliteFieldType GetColumnType(int32_t col) const = 0;
			virtual int32_t GetColumnBytes(int32_t col) const = 0;
			
			virtual int16_t ReadInt16(int32_t col) const = 0;
			virtual uint16_t ReadUInt16(int32_t col) const = 0;
			virtual int32_t ReadInt32(int32_t col) const = 0;
			virtual uint32_t ReadUInt32(int32_t col) const = 0;
			virtual int64_t ReadInt64(int32_t col) const = 0;
			virtual uint64_t ReadUInt64(int32_t col) const = 0;
			virtual float ReadFloat(int32_t col) const = 0;
			virtual double ReadDouble(int32_t col) const = 0;
			virtual void ReadText(int32_t col, astr& text) const = 0;
			virtual astr ReadText(int32_t col) const = 0;
			virtual void ReadBlob(int col, byte_t **pBuf, int32_t& size) const = 0;

			virtual void BindInt16(int32_t col, int16_t val) = 0;
			virtual void BindUInt16(int32_t col, uint16_t val) = 0;
			virtual void BindInt32(int32_t col, int32_t val) = 0;
			virtual void BindUInt32(int32_t col, uint32_t val) = 0;
			virtual void BindInt64(int32_t col, int64_t val) = 0;
			virtual void BindUInt64(int32_t col, uint64_t val) = 0;
			virtual void BindFloat(int32_t col, float val)  = 0;
			virtual void BindDouble(int32_t col, double val) = 0;
			virtual void BindText(int32_t col, const astr& text, bool copy) = 0;
			virtual void BindBlob(int32_t col, const byte_t *pBuf, int32_t size, bool copy) = 0;
		};

	}
}
