#ifndef GLOBAL_H
#define GLOBAL_H

	#include <string>
	#include <regex>

	struct couleurTerm
	{
		std::string FGROUGE = "\033[91m\033[40m";
		std::string FGVERT = "\033[92m\033[40m";
		std::string FGJAUNE = "\033[93m\033[40m";
		std::string FGBLEU = "\033[94m";
		std::string FGMAGENTA = "\033[95m\033[40m";
		std::string FGCYAN = "\033[96m\033[40m";
		std::string RESET = "\033[0m";
		std::string GRAS = "\033[1m";
		std::string ITALIQUE = "\033[3m";
		std::string UNDERLINE = "\033[4m";
	};

	static struct couleurTerm coul;	// Une variable globale non-modifiable

	struct flags // all flags and default values
	{
		bool f_flag = false;
		bool d_flag = false;
		bool r_flag = false;
		bool i_flag = false;
		bool I_flag = false;
		bool n_flag = false;
		bool v_flag = false;
	};

	extern struct flags fl;		// Une variable globale modifiable
	extern int iteration;

	extern std::regex_constants::syntax_option_type regexOptionI;
	extern std::string ptrn;
	extern std::string repl;

	#ifdef __APPLE__
		extern std::string ptrn_NFD;
	#endif

#endif
