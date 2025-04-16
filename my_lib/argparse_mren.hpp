#ifndef __ARGPARSE_MREN__
	#define __ARGPARSE_MREN__

	#include <iostream>
	#include <vector>
	#include <cstring>

	#include "global.h"

	struct argparseBase // Base class structure
	{
		std::string progName;		// Si absent, contruit par argv[0]
		std::string version;		// ex.: "version 2024-02-06 Beta"
		std::string description;	// ex.: "Programme qui fait ceci"
		std::string usage;			// ex.: "prg [-fnh] <-i int> ..." - option -h
		std::string helpMsg;		// Si absent, construit avec le 4 autres - option --help

		int argPos_c;
		std::vector<std::string> argPos_v;
		struct flags* mren_flags;
	};

	int parse(struct argparseBase&, int argc, char* argv[]);

	enum retcode { OK, HELP_VERSION, ERROR};

	#endif
