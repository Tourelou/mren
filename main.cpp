#include <iostream>	// cout ...
#include <sstream>	// Pour stringStream : fonction récursive : Capturer cout
#include <vector>	// dname, fname
#include <unistd.h> // chdir(), getcwd()
#include <regex>	// ...
#include <dirent.h>	// Pour récupérer le contenu d'un répertoire
#include <sys/stat.h>	// Récupère les info d'un fichier/dir
#include <cctype>	// std::tolower
#include "argparse.hpp"	// Parse la ligne de commande

#ifdef __APPLE__
	#include "minNFC2NFD.hpp"
#endif

#include "my_lib/global.h"
#include "my_lib/help-erreur.hpp"
#include "my_lib/dos.hpp"
#include "my_lib/trouveMatch.hpp"

// Pour compiler: g++ -std=c++11 mren.cpp -o mren

struct flags fl;
std::string ptrn;
std::string repl;

std::regex_constants::syntax_option_type regexOptionI = std::regex_constants::ECMAScript;

#ifdef __APPLE__
	std::string ptrn_NFD;
#endif

int main(int argc, char *argv[])
{
	char basePath [ PATH_MAX ];
	std::string currObject;

	if ( getcwd(basePath, PATH_MAX) == 0) exit(1); // Si tu peux pas connaître ton cwd: ça va mal

	// Set les éléments pour parser avec argparse.hpp
	argparse arg({.version = message_version, .description = message_description, 
									.usage = message_usage, .helpMsg = message_aide});

	if (! arg.addOption({.varPtr = &fl.f_flag, .shortOption = "-f", .varType = def::BOOL})) return 1;
	if (! arg.addOption({.varPtr = &fl.d_flag, .shortOption = "-d", .varType = def::BOOL})) return 1;
	if (! arg.addOption({.varPtr = &fl.r_flag, .shortOption = "-r", .longOption = "--recursive", .varType = def::BOOL})) return 1;
	if (! arg.addOption({.varPtr = &fl.i_flag, .shortOption = "-i", .longOption = "--include", .varType = def::BOOL})) return 1;
	if (! arg.addOption({.varPtr = &fl.I_flag, .shortOption = "-I", .longOption = "--ignoreCase", .varType = def::BOOL})) return 1;
	if (! arg.addOption({.varPtr = &fl.n_flag, .shortOption = "-n", .longOption = "--simulate", .varType = def::BOOL})) return 1;
	if (! arg.addOption({.varPtr = &fl.v_flag, .shortOption = "-v", .longOption = "--verbose", .varType = def::BOOL})) return 1;

	int ret = arg.parse(argc, argv);
	if (ret == retcode::ERROR) return 1;
	if (ret == retcode::HELP_VERSION) return 0;

	if (arg.argPos_c < 2) { prt_message(message_erreur); return 1; }

	// On ajuste les flags f_flag et d_flag pour être cohérent
	if ((fl.f_flag == false) && (fl.d_flag == false)) fl.f_flag = fl.d_flag = true;
	else if ((fl.f_flag == true) && (fl.d_flag == true)) {
		prt_message(message_exclude);
		return 1;
	}

	if (fl.n_flag == true) fl.v_flag = true; // Verbose si une simulation
	if (fl.I_flag == true) regexOptionI = regexOptionI | std::regex_constants::icase;

	// Le premier sera toujours ptrn et le deuxième repl.
	ptrn = arg.argPos_v[0];

#ifdef __APPLE__
	ptrn_NFD = ptrn;
	if (! isPlainText(ptrn))
	{
		ptrn_NFD = minNFC2NFD(ptrn);
	}
#endif
	repl = arg.argPos_v[1];

	if (arg.argPos_c < 3) { arg.argPos_v.push_back("./"); arg.argPos_c++; }
	// Si nous avons que 2 argPos_v, on force le troisième au current dir.

	for (int i = 2; i < arg.argPos_c; i++) // À partir du troisième ce sont des dirs.
	{
		struct stat sb; // Teste pour un répertoire valide
		if (!(stat(arg.argPos_v[i].c_str(), &sb) == 0 && (sb.st_mode & S_IFDIR))) {
			std::cout << "✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦" << std::endl;
			std::cout << coul.FGROUGE << arg.argPos_v[i] << coul.RESET 
						<< " n'est pas un répertoire valide." << std::endl;
			continue;
		}
		// À partir d'ici nous avons un répertoire valide.
		char fullPath [ PATH_MAX ];
		realpath(arg.argPos_v[i].c_str(), fullPath);
		currObject = fullPath;

		if (fl.v_flag) {
			if (i > 2) std::cout << "✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦" << std::endl;
			std::cout << "À partir du répertoire: "
						<< coul.FGBLEU << currObject << coul.RESET << "\n"
						<< "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
		}
		if (fl.i_flag && fl.d_flag) { // Si on a le flag -i, inclure le rep source.
			std::string baseName = currObject.substr(currObject.find_last_of("/\\") + 1);
			std::string pathName = currObject.substr(0, currObject.find_last_of("/\\"));

			// lambda function pour éviter la répétition de code
			auto find_rename = [&] (std::regex& sr) {
			//                  ^         ^ Argument passé en référence à lambda
			//                  | pour récupérer les variable du bloc parent
				std::string new_baseName = std::regex_replace(baseName, sr, repl);
				if (baseName != new_baseName) {
					if ( ! chdir(pathName.c_str()) ) {
						if (renomme(baseName, new_baseName, "⨀ ")) {
							// currObject a changé de nom.
							currObject = pathName + "/" + new_baseName;
						}
						std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
					}
				}
			};

//	BLOC QUI S'EXÉCUTE QUAND IL N'Y A PAS DE CARACTÈRES SPÉCIAUX
			std::regex self_replace(ptrn, regexOptionI);
			find_rename(self_replace);
//	FIN DU BLOC
#ifdef __APPLE__
//	BLOC QUI S'EXÉCUTE QUAND IL Y A DES CARACTÈRES SPÉCIAUX
			if (ptrn != ptrn_NFD) {
				std::regex self_replace(ptrn_NFD, regexOptionI);
				find_rename(self_replace);
			}
//	FIN DU BLOC
#endif

		}
		if ( ! chdir(currObject.c_str()) ) {
			if (! trouveMatch()) std::cout << "Pas de correspondance pour ce répertoire ..." << std::endl;
			chdir(basePath); // À cause de la boucle, toujours revenir au dossier de base
		}
		else {
			std::cout << "Impossible de travailler avec le répertoire "
					  << coul.FGROUGE << arg.argPos_v[i] << coul.RESET << std::endl;
			continue;
		}
	}
}
