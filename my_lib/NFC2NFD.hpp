#ifdef __APPLE__
	#if !defined(NFC_2_NFD)
	#define NFC_2_NFD
		#include <string>

		bool isPlainText(const std::string &);
		std::string NFC2NFD(const std::string &);

	#endif	// NFC_2_NFD
#endif
