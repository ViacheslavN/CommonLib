#pragma once
#if defined(COMMON_TMP_LIBPREFIX) || defined(COMMON_TMP_LIBSUFFIX_DBG) \
	|| defined(COMMON_TMP_LIBSUFFIX_UNC) || defined(COMMON_TMP_LIBSUFFIX_CRT) \
	||defined(COMMON_TMP_PLATFORM) \
	|| defined(COMMON_TMP_LIBNAME)
# error Required macroses already defined
#endif
#define COMMON_LIB_VER_STRING ""


#if defined(_WIN32_WCE)
# define COMMON_TMP_PLATFORM "_wce"
#elif defined(_WIN64)
# define  COMMON_TMP_PLATFORM "_x64"
#elif defined(_WIN32)
# define  COMMON_TMP_PLATFORM "_Win32"
#else
# error Unknown platform
#endif


#if defined(_DEBUG)
# define COMMON_TMP_LIBSUFFIX_DBG "Debug"
#else
# define COMMON_TMP_LIBSUFFIX_DBG "Release"
#endif

//#if defined(_UNICODE)
//# define COMMON_TMP_LIBSUFFIX_UNC "u"
//#else
# define COMMON_TMP_LIBSUFFIX_UNC ""
//#endif

#if defined(_DLL)
# define COMMON_TMP_LIBSUFFIX_CRT ""
#else
# define COMMON_TMP_LIBSUFFIX_CRT "Static"
#endif

//#if defined (COMMON_STATIC_LIB)
# define COMMON_TMP_LIBPREFIX "Lib"
//#else
//# define COMMON_TMP_LIBPREFIX ""
//#endif

#define COMMON_TMP_LIBNAME \
	"CommonLib" COMMON_TMP_LIBSUFFIX_DBG COMMON_TMP_LIBSUFFIX_CRT COMMON_TMP_PLATFORM".lib"
 

#pragma message ("Automatical linking with " COMMON_TMP_LIBNAME)

#pragma comment(lib, COMMON_TMP_LIBNAME)

#undef COMMON_TMP_LIBPREFIX
#undef COMMON_TMP_LIBSUFFIX_DBG
#undef COMMON_TMP_LIBSUFFIX_UNC
#undef COMMON_TMP_LIBSUFFIX_CRT
//#undef COMMON_TMP_CCVER
#undef COMMON_TMP_PLATFORM
#undef COMMON_TMP_LIBNAME