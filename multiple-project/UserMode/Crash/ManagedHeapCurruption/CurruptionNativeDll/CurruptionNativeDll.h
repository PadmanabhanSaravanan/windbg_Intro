// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CURRUPTIONNATIVEDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CURRUPTIONNATIVEDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CURRUPTIONNATIVEDLL_EXPORTS
#define CURRUPTIONNATIVEDLL_API __declspec(dllexport)
#else
#define CURRUPTIONNATIVEDLL_API __declspec(dllimport)
#endif

// This class is exported from the CurruptionNativeDll.dll
class CURRUPTIONNATIVEDLL_API CCurruptionNativeDll {
public:
	CCurruptionNativeDll(void);
	// TODO: add your methods here.
};



extern CURRUPTIONNATIVEDLL_API int nCurruptionNativeDll;

CURRUPTIONNATIVEDLL_API int fnCurruptionNativeDll(void);
