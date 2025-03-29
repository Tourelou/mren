#ifdef __APPLE__

	#include <string>
	#include <iconv.h>

	std::string NFC2NFD(const std::string& input) {
		// Ouvrir les charsets pour conversion
		iconv_t cd = iconv_open("UTF-8-MAC", "UTF-8");	// to, from
		if (cd == (iconv_t)-1) return input;

		// Préparation des variables pour iconv
		const char* in_buf = input.c_str();
		size_t in_left = input.length();

		const size_t maxOutputSize = in_left * 4; // Allocation pour le pire des cas

		char out_buf[maxOutputSize];
		char* out_ptr = out_buf;
		size_t out_left = maxOutputSize;

		size_t result = iconv(cd, const_cast<char**>(&in_buf), &in_left, &out_ptr, &out_left);
		if (result == (size_t)-1) {
			iconv_close(cd);
			return input;
		}

		// Construction de la chaîne de sortie
		std::string output(out_buf, out_ptr - out_buf);

		iconv_close(cd);

		return output;
	}

	bool isPlainText(const std::string& s) {
		bool plain = true;
		for (int i = 0; i < s.size(); i++)
		{
			unsigned char c = s[i];
			if (c > 127) { plain = false; break; }
		}
		return(plain);
	}
#endif
