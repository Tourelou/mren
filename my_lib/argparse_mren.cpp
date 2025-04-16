#include "argparse_mren.hpp"

int parse(struct argparseBase &Base, int argc, char* argv[]) { // return 0 = OK, 1 = help-version, 2+ erreur
	if (Base.progName == "") {
		std::string s = argv[0];
		Base.progName = s.substr(s.find_last_of("/\\") + 1);
	}
	if (Base.helpMsg == "") {
		Base.helpMsg = Base.progName;
		if (Base.description != "") Base.helpMsg += ": " + Base.description;
		if (Base.version != "") Base.helpMsg += ", " + Base.version;
		if (Base.usage != "") Base.helpMsg += "\n---\n" + Base.usage;
	}
	// Début du parsing
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0) {
			std::cout << Base.usage << std::endl;
			return retcode::HELP_VERSION;
		}
		if (strcmp(argv[i], "--help") == 0) {
			std::cout << Base.helpMsg << std::endl;
			return retcode::HELP_VERSION;
		}
		if (strcmp(argv[i], "-ver") == 0) {
			std::cout << Base.progName << ": ";
			if (Base.version != "") std::cout << Base.version << std::endl;
			else std::cout << "Version nondisponible." << std::endl;
			return retcode::HELP_VERSION;
		}
		if (strcmp(argv[i], "--version") == 0) {
			std::cout << Base.progName << ": ";
			if (Base.description != "") std::cout << Base.description << ", ";
			else std::cout << "Description nondisponible, ";
			if (Base.version != "") std::cout << Base.version << std::endl;
			else std::cout << "Version nondisponible." << std::endl;
			return retcode::HELP_VERSION;
		}

		if (strcmp(argv[i], "--") == 0) { // Tout ce qui suit ne sont plus des flags
			Base.argPos_c = argc - i - 1 + Base.argPos_c;
			for (int j = i + 1; j < argc; j++) Base.argPos_v.push_back(argv[j]);
			return OK;
		}

		if (argv[i][0] == '-') {
			if (argv[i][1] == '-') {	// Argument long: --argument
				if (strcmp(argv[i], "--recursive") == 0) Base.mren_flags->r_flag = true;
				else if (strcmp(argv[i], "--include") == 0) Base.mren_flags->i_flag = true;
				else if (strcmp(argv[i], "--ignoreCase") == 0) Base.mren_flags->I_flag = true;
				else if (strcmp(argv[i], "--simulate") == 0) Base.mren_flags->n_flag = true;
				else if (strcmp(argv[i], "--verbose") == 0) Base.mren_flags->v_flag = true;
				else {
					std::cout << "illégal option " << argv[i] << std::endl;
					return ERROR;
				}
			}
			else {						// Argument court: -a
				std::string option = argv[i];
				for (int c = 1; c < option.length(); c++) {
					switch (option[c]) {
					case 'f':
						Base.mren_flags->f_flag = true;
						break;
					
					case 'd':
						Base.mren_flags->d_flag = true;
						break;
					
					case 'r':
						Base.mren_flags->r_flag = true;
						break;
					
					case 'i':
						Base.mren_flags->i_flag = true;
						break;
					
					case 'I':
						Base.mren_flags->I_flag = true;
						break;
					
					case 'n':
						Base.mren_flags->n_flag = true;
						break;
					
					case 'v':
						Base.mren_flags->v_flag = true;
						break;
					
					default:
						std::cout << "illégal option -" << argv[i][c] << std::endl;
						return ERROR;
						break;
					}
				}
			}
		}
		else {		// Argument en position: Les deux premiers doivent être absolument côte à côte.
			Base.argPos_v.push_back(argv[i]);
			Base.argPos_c++;
			if (Base.argPos_c == 1) {	// Si oui on veut le suivant qui est replacement.
				if ( i < argc - 1 ) {
					i++;
					Base.argPos_v.push_back(argv[i]);
					Base.argPos_c++;
				}
				else return ERROR;
			}
		}
	}
	return retcode::OK;
}
