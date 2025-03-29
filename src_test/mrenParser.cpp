#include <iostream>

char **argv_opts;
int argc_opts = 0;
char **argv_params;
int argc_params = 0;
char **argv_dirs;
int argc_dirs = 0;

struct flags // all flags and default values
{
	bool f_flag = true;
	bool d_flag = true;
	bool r_flag = false;
	bool i_flag = false;
	bool I_flag = false;
	bool n_flag = false;
	bool v_flag = false;
};

struct flags fl;

std::string ptrn;
std::string repl;

void aide(int code) {
	std::cout << "Il faut au minimum: <pattern> <remplacement> <répertoire cible>\n";
	std::cout << "en ligne de commande: ex. '.jpg' 'jpeg' 'Desktop'\n";
	std::cout << "Plus les flags de contrôle le cas échéant." << std::endl;
	exit (code);
}

void parseOpts()
{
	// On se réfère à argc_opts et argv_opts
	for (int i = 0; i < argc_opts; i++)
	{
		std::string option = argv_opts[i];
		if ( option[0] == '-') { // Options courtes ex. -f
			if ( option[1] == '-' ) { // Options longues ex. --verbose
				if ( option == "--" ) break;
				else if ( option == "--recursive" ) fl.r_flag = true;
				else if ( option == "--include" ) fl.i_flag = true;
				else if ( option == "--ignoreCase" ) fl.I_flag = true;
				else if ( option == "--simulate" ) fl.n_flag = true;
				else if ( option == "--verbose" ) fl.v_flag = true;
				else {
					std::cout << "L'option " << option << " est invalide" << std::endl;
					exit(1);
				}
				continue;
			}
			for (int i = 1; i < option.length(); i++)
			{
				switch (option[i])
				{
				case 'f':
					fl.d_flag = false;
					break;
				
				case 'd':
					fl.f_flag = false;
					break;
				
				case 'r':
					fl.r_flag = true;
					break;
				
				case 'i':
					fl.i_flag = true;
					break;
				
				case 'I':
					fl.I_flag = true;
					break;
				
				case 'n':
					fl.n_flag = true;
					break;
				
				case 'v':
					fl.v_flag = true;
					break;
				
				default:
					std::cout << "L'option -" << option[i] << " est invalide" << std::endl;
					exit(1);
				}
			}
		}
	}
	std::cout << "f = : " << fl.f_flag << std::endl;
	std::cout << "d = : " << fl.d_flag << std::endl;
	std::cout << "r = : " << fl.r_flag << std::endl;
	std::cout << "i = : " << fl.i_flag << std::endl;
	std::cout << "I = : " << fl.I_flag << std::endl;
	std::cout << "n = : " << fl.n_flag << std::endl;
	std::cout << "v = : " << fl.v_flag << std::endl;
}

void parseCL(int argc, char *argv[])
/*
Ligne de commande: nom_du_prog -f -rv --simulate 'jpeg' 'jpg' 'dir1' 'dir2' 'dir3' ...
                               ^                 ^            ^
                               argv_opts         argv_params  argv_dirs
                               argc_opts         argc_params  argc_dirs
                                   3                 2            3
*/
{
	int offset = 1; // offset pour pattern, replace, dir ...

	if ( argc > 3 ) { // Il faut au moins 3 paramètres en ligne de commande
	// On essai de trouver où sont les params -> offset
		for ( int i = 1; i < argc; i++) {
			if ( argv[i][0] == '-' ) offset++;
			else break;
			if ( std::string(argv[i]) == "--") break;
		}
		argc_params = argc - offset;
		if ( argc_params < 3 ) aide(1);
		argv_params = &argv[offset];

		argc_dirs = argc_params - 2;
		argv_dirs = &argv[offset + 2];

		argc_opts = argc - argc_params - 1;
		if ( argc_opts ) {
			argv_opts = &argv[1];
			parseOpts();
		}
			ptrn =  argv_params[0];
			repl = argv_params[1];
	}
	else aide(1);
}

int main(int argc, char *argv[])
{
	parseCL(argc, argv);
	std::cout << "Pattern: " << ptrn << std::endl;
	std::cout << "Remplacement: " << repl << std::endl;

	for (int i = 0; i < argc_dirs; i++)
	{
		std::cout << "Répertoire: " << argv_dirs[i] << std::endl;
	}
}
