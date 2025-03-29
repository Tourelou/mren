#include <iostream>	// cout ...
#include <sstream>	// Pour stringStream : fonction récursive : Capturer cout
#include <vector>	// dname, fname
#include <unistd.h> // chdir(), getcwd()
#include <regex>	// ...
#include <dirent.h>	// Pour récupérer le contenu d'un répertoire
#include <sys/stat.h>	// Récupère les info d'un fichier/dir
#include <cctype>	// std::tolower
#include "argparse.hpp"	// Parse la ligne de commande

/*
	Apple se servait, avec son système de fichier HFS+ du standard NFD
	pour l'encodage des fichiers sur ce filesystem. Depuis 2017, Apple
	sort APFS. Nouveau filesystem qui peut encoder ses noms de fichiers
	aussi bien en NFD qu'en NFC, standard utilisé sur Linux.
*/

#ifdef __APPLE__
	#include "my_lib/NFC2NFD.hpp"
	std::string ptrn_NFD;
#endif

#include "my_lib/global.h"
#include "my_lib/getFrancais.hpp"
#include "my_lib/help-erreur.hpp"
#include "my_lib/dos.hpp"
#include "my_lib/trouveMatch.hpp"

// Pour compiler: g++ -std=c++11 -o mren main.cpp my_lib/*.cpp -liconv

bool langFranc = false;
struct flags fl;
std::string ptrn;
std::string repl;

std::regex_constants::syntax_option_type regexOptionI = std::regex_constants::ECMAScript;

int main(int argc, char *argv[])
{
	char basePath [ PATH_MAX ];
	std::string currObject;

	if ( getcwd(basePath, PATH_MAX) == 0) exit(1); // Si tu peux pas connaître ton cwd: ça va mal

	langFranc = getFrancais();
	setRenommeLocale();

	// Set les éléments pour parser avec argparse.hpp
	argparse arg({.version = message_version});

	if (langFranc) {
		arg.Base.description = fr_message_description;
		arg.Base.usage = fr_message_usage;
		arg.Base.helpMsg = fr_message_aide;
	}
	else {
		arg.Base.description = en_message_description;
		arg.Base.usage = en_message_usage;
		arg.Base.helpMsg = en_message_aide;
	}
	
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

	if (arg.argPos_c < 2) {

		if (langFranc) prt_message(fr_message_erreur);
		else prt_message(en_message_erreur);

		return 1;
	}

	// On ajuste les flags f_flag et d_flag pour être cohérent
	if ((fl.f_flag == false) && (fl.d_flag == false)) fl.f_flag = fl.d_flag = true;
	else if ((fl.f_flag == true) && (fl.d_flag == true)) {
		if (langFranc) prt_message(fr_message_exclude);
		else prt_message(en_message_exclude);

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
		ptrn_NFD = NFC2NFD(ptrn);
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
			if (langFranc) {
				std::cout << coul.FGROUGE << arg.argPos_v[i] << coul.RESET 
						<< " n'est pas un répertoire valide." << std::endl;
			}
			else {
				std::cout << coul.FGROUGE << arg.argPos_v[i] << coul.RESET 
						<< " is not a valid folder." << std::endl;
			}
			continue;
		}
		// À partir d'ici nous avons un répertoire valide.
		char fullPath [ PATH_MAX ];
		realpath(arg.argPos_v[i].c_str(), fullPath);
		currObject = fullPath;

		if (fl.v_flag) {
			if (i > 2) std::cout << "✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦ ✦" << std::endl;
			if (langFranc) {
				std::cout << "À partir du répertoire: "
						<< coul.FGBLEU << currObject << coul.RESET << "\n"
						<< "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
			}
			else {
				std::cout << "From folder: "
						<< coul.FGBLEU << currObject << coul.RESET << "\n"
						<< "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
			}
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
			if (! trouveMatch()) {
				if (langFranc) std::cout << "Pas de correspondance pour ce répertoire ..." << std::endl;
				else std::cout << "There is no match for this directory ..." << std::endl;
			}
			chdir(basePath); // À cause de la boucle, toujours revenir au dossier de base
		}
		else {
			if (langFranc) {
				std::cout << "Impossible de travailler avec le répertoire "
					  << coul.FGROUGE << arg.argPos_v[i] << coul.RESET << std::endl;
			}
			else {
				std::cout << "Unable to work with directory "
					  << coul.FGROUGE << arg.argPos_v[i] << coul.RESET << std::endl;
			}
			continue;
		}
	}
}
