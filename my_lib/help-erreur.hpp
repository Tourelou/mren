#if !defined(HELP_ERREUR)
#define HELP_ERREUR

	#include "global.h"		// Pour récupérer la définition de la variable coul

	std::string fr_message_usage = // option -h
		"usage: mren [-f|-d] [-riInv] <motif regex> <remplacement> [dirname ...]";

	std::string fr_message_description = "Renommage multiple selon un certain motif";

	std::string fr_message_aide = // option --help
		fr_message_usage+"\n""\n"+fr_message_description+"\n""\n"
		"Arguments en position:\n"
		"  <motif regex>     Motif à chercher: Mettre entre guillements '...'\n"
		"  <remplacement>    Chaîne de remplacement\n"
		"  [dirname ...]     Répertoire(s) de recherche\n"
		"\n"
		"Options:\n"
		"  -f                N'agit que sur les fichiers\n"
		"  -d                N'agit que sur les répertoires\n"
		"  -r, --recursive   Procède de façon récursive sur les répertoires\n"
		"  -i, --include     En mode récusif, inclu le dossier en ligne de commande\n"
		"  -I, --ignoreCase  Fait une recherche en ignorant la case\n"
		"  -n, --simulate    Simule les opérations demandées - Fichiers affectés en VERT\n"
		"  -v, --verbose     Donne des détails sur le(s) fichier(s) traité(s) - Fichiers affectés en ROUGE\n"
		"  -ver, --version   Renommage multiple à partir d'un motif\n"
		"  -h, --help        Montre ce message d'aide et termine";

	std::string fr_message_exclude =
		"Pour les drapeaux «f|d», il sont mutuellement exclusif. C'est un ou c'est l'autre.";

	std::string fr_message_erreur =
		coul.FGROUGE+"- - ATTENTION - - ATTENTION - - ATTENTION - - ATTENTION - - ATTENTION - -"+coul.RESET+"\n"
		"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
		"Vous devez au moins donner: <motif> <remplacement>\n"
		"en ligne de commande: "+coul.FGROUGE+"ex. mren '\\.jpeg' '.jpg'"+coul.RESET+"\n"
		"Plus les drapeaux de contrôle le cas échéant.\n"
		"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"+fr_message_aide;

// ------------------------------------------------------------------------------

std::string en_message_usage = // option -h
"usage: mren [-f|-d] [-riInv] <regex pattern> <remplacement> [dirname ...]";

std::string en_message_description = "Multiple renaming from a pattern";

std::string en_message_aide = // option --help
en_message_usage+"\n""\n"+en_message_description+"\n""\n"
"Positional arguments:\n"
"  <regex pattern>   Pattern to serch: Put into single quote '...'\n"
"  <remplacement>    Replacement for the found pattern\n"
"  [dirname ...]     Path(s) to search\n"
"\n"
"Options:\n"
"  -f                Search only for files\n"
"  -d                Search only for folders\n"
"  -r, --recursive   Recursively works through directories\n"
"  -i, --include     In recursive mode, include the folder pass on the command line\n"
"  -I, --ignoreCase  Self explained\n"
"  -n, --simulate    Simulates the requested operations - Files affected in GREEN\n"
"  -v, --verbose     Gives details of the processed file(s) - Affected files in RED\n"
"  -ver, --version   Multiple renaming from a pattern\n"
"  -h, --help        Show this help message and exit";

std::string en_message_exclude =
"For the «f|d» flags, they are mutually exclusive. It's one or the other.";

std::string en_message_erreur =
coul.FGROUGE+"-- WARNING - - WARNING - - WARNING - - WARNING - - WARNING - - WARNING --"+coul.RESET+"\n"
"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
"You must at least give: <pattern> <replacement>\n"
"On command line: "+coul.FGROUGE+"ex. mren '\\.jpeg' '.jpg'"+coul.RESET+"\n"
"Plus control flags if needed.\n"
"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"+en_message_aide;

		void prt_message(std::string &);

#endif // HELP_ERREUR
