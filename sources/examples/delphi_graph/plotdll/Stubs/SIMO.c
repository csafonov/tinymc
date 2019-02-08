// For MSVC compilation

// for x64
#ifdef WIN_x64
#ifdef _DEBUG
#pragma comment(lib,"tmcrtvc8d_x64.lib")
//#pragma comment(lib,"SIMOLib.lib")
#else
#pragma comment(lib,"tmcrtvc8_x64.lib")
//#pragma comment(lib,"SIMOLibR.lib")
#endif

#else // x86

#ifdef _DEBUG
#pragma comment(lib,"tmcrtvc8d.lib")
//#pragma comment(lib,"SIMOLib.lib")
#else
#pragma comment(lib,"tmcrtvc8.lib")
//#pragma comment(lib,"SIMOLibR.lib")
#endif

#endif
