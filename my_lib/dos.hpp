#if !defined(MY_DOS)
#define MY_DOS

	#include <string>

	std::string get_working_path();
	void setRenommeLocale();
	bool renomme(std::string, std::string, std::string);

#endif // MY_DOS
