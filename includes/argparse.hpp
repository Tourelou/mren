#ifndef __ARGPARSE__
	#define __ARGPARSE__

	#include <iostream>
	#include <vector>
	#include <cstring>

// Classe pour parser les arguments en ligne de commande.

/*
	En ligne de commande, la valeur suit toujours le flag, sauf pour le bool. ex.: -i 56

	Utilisation:
	1- Créer un objet de la classe argparse.

	argparse arg({.description = "Programme qui fait ceci", .version = "version 1.01" });

	On peut ajouter d'autres information par la suite ...
	arg.Base.usage = "argTest <-i int> [-f|--full] [-d float] [-s|--string string] ...";

	2- Ajouter les options à être parsées.

	if (! arg.addOption({.varPtr = &y, .shortOption = "-i", .varType = def::INT, .required = true})) return 1;

	3- Lancer le parsing.

	int ret = arg.parse(argc, argv);
	if (ret == ERROR) return 1;
	if (ret == HELP_VERSION) return 0;
*/

	struct argparseBase // Base class structure
	{
		std::string progName;		// Si absent, contruit par argv[0]
		std::string version;		// ex.: "version 2024-02-06 Beta"
		std::string description;	// ex.: "Programme qui fait ceci"
		std::string usage;			// ex.: "prg [-fnh] <-i int> ..." - option -h
		std::string helpMsg;		// Si absent, construit avec le 4 autres - option --help
	};

	enum def { BOOL = 1, STRING, INT, FLOAT, DOUBLE};	// Détermine le type du pointeur
												// pour addOption() - Obligatoire.

	struct Option {
		void* varPtr;				// Pointeur de la variable
		std::string shortOption;	// ex.: -r
		std::string longOption;		// ex.: --recursif
		bool required;
		def varType;				// Obligatoire
	};

// ---------------------------------------------------------------------------------------
	class argparse
	{
	public:
		struct argparseBase Base;
		std::vector<struct Option> argOpt_v;	// Ajouté par addOption()
		std::vector<std::string> argPos_v;	// Vecteur d'arguments en position
		int argPos_c = 0;		// Nombre d'argument en position

// Fonctions prototyes
		argparse(struct argparseBase B);
		~argparse();
		// -- -- -- -- -- -- -- -- -- -- --
		bool addOption(struct Option d);
		int parse(int argc, char* argv[]);
	};

// Implémentation
	argparse::argparse(struct argparseBase B)
		: Base(B) // initialisation
	{
//		std::cout << "Constructeur" << std::endl;
	}
	argparse::~argparse()
	{
//		std::cout << "Destructeur" << std::endl;
	}
// ---------------------------------------------------------------------------------------

	bool argparse::addOption(struct Option d) {
		if (d.shortOption == "" && d.longOption == "") {
			std::cout << "Il faudrait au moins une option courte ou une option longue" << std::endl;
			std::cout << "L'option n'a pas été ajoutée au pool" << std::endl;
			return false;
		}
		else if (d.varPtr == 0) {
			std::cout << "Il est impératif d'avoir un pointeur de variable" << std::endl;
			std::cout << "L'option " << d.shortOption << "/" << d.longOption
						<< " n'a pas été ajoutée au pool" << std::endl;
			return false;
		}
		else if (d.varType == 0) {
			std::cout << "Il est impératif d'avoir un type de variable" << std::endl;
			std::cout << "L'option " << d.shortOption << "/" << d.longOption
						<< " n'a pas été ajoutée au pool" << std::endl;
			return false;
		}
		else argOpt_v.push_back(d);
		return true;
	}

// ---------------------------------------------------------------------------------------
// Fonctions utilitaire pour la méthode argparse::parse()

	bool convS2I(std::string s, int &var) {
	// Pour convertir le nombre en ligne de commande vers un int
		for ( int d = 0; d < s.size(); d++) {
			if (!std::isdigit(s[d])) {
				std::cout << "«" << s << "» n'est pas un entier" << std::endl;
				return false;
			}
		}
		var = std::stoi(s);
		return true;
	}

	bool convS2F(std::string s, float &var) {
	// Pour convertir le nombre en ligne de commande vers un float
		for ( int d = 0; d < s.size(); d++) {
			if (!std::isdigit(s[d])) {
				if (s[d] == ',') { s[d] = '.'; continue; }
				if (s[d] == '.') continue;
				std::cout << "«" << s << "» n'est pas un float" << std::endl;
				return false;
			}
		}
		var = std::stof(s);
		return true;
	}

	bool convS2D(std::string s, double &var) {
	// Pour convertir le nombre en ligne de commande vers un float
		for ( int d = 0; d < s.size(); d++) {
			if (!std::isdigit(s[d])) {
				if (s[d] == ',') { s[d] = '.'; continue; }
				if (s[d] == '.') continue;
				std::cout << "«" << s << "» n'est pas un float" << std::endl;
				return false;
			}
		}
		var = std::stod(s);
		return true;
	}

	bool setVar(std::string value, struct Option &opt) {
		if (opt.varType == STRING) {
			*(std::string *)opt.varPtr = value;
			opt.required = false;
		}
		else if (opt.varType == INT) {
			if (! convS2I(value, *(int *)opt.varPtr)) return false;
			opt.required = false;
		}
		else if (opt.varType == FLOAT) {
			if (! convS2F(value, *(float *)opt.varPtr)) return false;
			opt.required = false;
		}
		else if (opt.varType == DOUBLE) {
			if (! convS2D(value, *(double *)opt.varPtr)) return false;
			opt.required = false;
		}
		else {
			std::cout << "Type de variable inconnu" << std::endl;
			return false;
		}
		return true;
	}

	void manqueValeur(std::string mes) {
		std::cout << "Une valeur pour «" << mes << "» serait apprécié ..." << std::endl;
	}

// ---------------------------------------------------------------------------------------

	enum retcode { OK, HELP_VERSION, ERROR};

	int argparse::parse(int argc, char* argv[]) { // return 0 = OK, 1 = help-version, 2+ erreur
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
			bool found = false;
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
			if (strcmp(argv[i], "--") == 0) { // Tout ce qui suit sont des paramètres
				argPos_c = argc - i - 1 + argPos_c;
				for (int j = i + 1; j < argc; j++) argPos_v.push_back(argv[j]);
				break;
			}
			if (argv[i][0] == '-') {
				if (argv[i][1] == '-') { // -- donc longOption
					for (auto &opt : argOpt_v) {
						if (strcmp(argv[i], opt.longOption.c_str()) == 0) {
							found = true;

							if (opt.varType == BOOL) {
								*(bool *)opt.varPtr = true;
								opt.required = false;
								break;
							}
							if (argc - i > 1) {
								i++;
								if (! setVar(argv[i], opt)) return ERROR;
								break;
							}
							else {
								manqueValeur(opt.shortOption);
								return ERROR;
							}
						}
					}
					if (found) continue;
					std::cout << "Option " << argv[i] << " - invalide" << std::endl;
					return retcode::ERROR;
				}
				else { // short option: peuvent être combinées
					std::string option = argv[i];
					for (int Opt_charPos = 1; Opt_charPos < option.length(); Opt_charPos++) {
					// Boucle jusqu'a la fin de toutes les options. ex.: -pvrm
						found = false;
						for (auto &opt : argOpt_v) {
							if (option[Opt_charPos] == opt.shortOption.c_str()[1]) {
								found = true;

								if (opt.varType == BOOL) {
									*(bool *)opt.varPtr = true;
									opt.required = false;
									break;
								}
								if (Opt_charPos == option.length() - 1) {
									if (argc - i > 1) {
										i++;
										if (! setVar(argv[i], opt)) return ERROR;
										break;
									}
									else {
										manqueValeur(opt.shortOption);
										return retcode::ERROR;
									}
								}
								else {
									std::cout << "L'option " << opt.shortOption
										<< " doit être placée en dernier pour précéder la valeur" << std::endl;
									return retcode::ERROR;
								}
							}
						}
						if (found) continue;
						std::cout << "Option «-" << option[Opt_charPos] << "» - invalide" << std::endl;
						return retcode::ERROR;
					}
				}
			}
			else {
				argPos_v.push_back(argv[i]);
				argPos_c++;
			}
		}
		// On fait le tour au cas ou des options manqueraient
		for (auto &v : argOpt_v) {
			if (v.required == true) {
				if (!(v.shortOption == "")) {
					std::cout << "L'option manquant «" << v.shortOption
					<< "» est requise" << std::endl;
				}
				else {
					std::cout << "L'option manquant «" << v.longOption
					<< "» est requise" << std::endl;
				}
				return retcode::ERROR;
			}
		}
		return retcode::OK;
	}
#endif
