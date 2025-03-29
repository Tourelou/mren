#include <string>
#include <sstream>	// Pour stringStream : fonction récursive : Capturer cout
#include <iostream>
#include <vector>
#include <regex>	// ...
#include <unistd.h> // chdir(), getcwd()
#include <dirent.h>	// Pour récupérer le contenu d'un répertoire
#include "global.h"
#include "dos.hpp"

bool trouveMatch()
{
	bool match = false;
	bool recursive_match = false;

	if (iteration > 100) return false;	// Pas normal, on doit être pris dans une boucle

	DIR *dh;
	struct dirent* contents;
	std::string prevPath = get_working_path();
	std::string space = "▶︎ "; // Pour créer une indentation en récursif
	std::string rspace = "◀︎ "; // Pour créer une indentation en récursif

	// Pour créer l'indentation necessaire
	for (int i = 0; i < iteration; i++) {
		space.insert(0, "  ");
		rspace.insert(0, "  ");
	}
	if ( (dh = opendir (".")) != NULL) {
		std::string name;
		std::vector<std::string> fname;	// Un vector pour les fichiers
		std::vector<std::string> dname;	// Un vector pour les répertoires

		// Récupère la liste de tout les fichiers en 2 vector
		// dname: répertoires, fname: les fichiers.
		while ((contents = readdir( dh )) != NULL)
		{
			name = contents->d_name;

			if ((name == ".") || (name == "..")) continue;	// On en veut pas

			if (contents->d_type == DT_DIR) dname.push_back(name);
			else if (contents->d_type == DT_REG) fname.push_back(name);
			else continue;
		}
		closedir (dh);

		// Manipulation pour trier les vectors dname et fname.
		struct {
			bool operator()(std::string a, std::string b) const {
				return std::tolower(a[0]) < std::tolower(b[0]);
			}
		}
		customLess;
		std::sort(fname.begin(), fname.end(), customLess);
		std::sort(dname.begin(), dname.end(), customLess);


		// lambda function pour éviter la répétition de code
		auto find_rename = [&] (std::regex& sr) {
		//                  ^         ^ Argument passé en référence à lambda
		//                  | pour récupérer les variable du bloc parent
			// Scan chaque fichier pour un match.
			if (fl.f_flag) {
				std::string new_f;
				for ( auto &f : fname ) {
					new_f = std::regex_replace(f, sr, repl);
					if (new_f != f) {
						match = true;
						renomme(f, new_f, space);
					}
				}
			}
			// Scan chaque répertoire pour un match.
			if (fl.d_flag) {
				std::string new_d;
				for ( auto &d : dname ) {
					new_d = std::regex_replace(d, sr, repl);
					if (new_d != d) {
						match = true;
						if (renomme(d, new_d, space)) d = new_d;
					}
				}
			}
		};

//	BLOC QUI S'EXÉCUTE QUAND IL N'Y A PAS DE CARACTÈRES SPÉCIAUX
		std::regex self_replace(ptrn, regexOptionI);
		find_rename(self_replace);

//	FIN DU BLOC
#ifdef __APPLE__
//	BLOC QUI S'EXÉCUTE QUAND IL Y A DES CARACTÈRES SPÉCIAUX
		if( ptrn != ptrn_NFD) // Si il ne sont pas pareil refaisont le tour.
		{
			std::regex self_replace(ptrn_NFD, regexOptionI);
			find_rename(self_replace);
		}
//	FIN DU BLOC
#endif
		// Quand on veut y aller récursivement.
		if (fl.r_flag == true) {
			if (! match && dname.empty()) return false;

			for ( auto d : dname ) {
				recursive_match = false;
				iteration++;
				if (chdir(d.c_str()) == 0) {
					if (fl.v_flag) {
						std::stringstream ss;
						ss << space << coul.FGBLEU << d << coul.RESET << " ▶︎" << std::endl;

						auto orig = std::cout.rdbuf(ss.rdbuf());	//Capture le stream de cout
						// Si il n'y a pas de match, je ne veux pas l'afficher
						if (trouveMatch()) recursive_match = true;
						else recursive_match = recursive_match|false;	// Pour passer le match au parent

						ss << rspace << coul.FGBLEU << d << coul.RESET << " ◀︎" << std::endl;

						std::cout.rdbuf(orig);						// Reset le buffer à cout
						if (recursive_match) std::cout << ss.str() << std::flush;
					}
					else {
						if (trouveMatch()) recursive_match = true;
						else recursive_match = recursive_match|false;	// Pour passer le match au parent
					}
					chdir(prevPath.c_str());
				}
				else { std::cout << coul.FGROUGE <<"---" << coul.RESET << " Je ne peux "
								<< coul.FGROUGE << "«chdir()»" << coul.RESET << " vers le répertoire "
								<< coul.FGROUGE << d << " ---" << coul.RESET << std::endl; }
				match = match|recursive_match;
				iteration--;
			}
		}
	}
	else {
		std::cout << "Ne peut lire le répertoire " << get_working_path() << std::endl;
		return false;
	}
	return match|recursive_match;
}
