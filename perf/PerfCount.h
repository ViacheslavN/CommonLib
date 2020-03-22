#pragma once

namespace CommonLib
{

	class CPerfOp
	{
	public:
		CPerfOp();
		~CPerfOp();

		void StartOperation();
		double StopOperation();
	private:
		uint64_t m_nStartCount{0};
	};

	class CPerfDataOp
	{
	public:
		CPerfDataOp() {}
		~CPerfDataOp() {}	

		void StartDataOperation();
		void StopDataOperation(uint64_t nData);
		double GetTime() const;
		uint64_t  GetProcessedDate() const;
		uint64_t GetCount() const;

	};


}