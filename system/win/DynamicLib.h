#pragma once

namespace CommonLib
{
	namespace system
	{

		class IDynamicLibrary 
		{
		public:
			IDynamicLibrary(){}
			virtual ~IDynamicLibrary(){}

			IDynamicLibrary(const IDynamicLibrary&) = delete;
			IDynamicLibrary& operator=(const IDynamicLibrary&) = delete;

			virtual void LoadLibrary(const astr& path) = 0;
			virtual void FreeLibrary() = 0;

 
		};




	}
}