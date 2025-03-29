#if !defined(HELP_ERREUR)
#define HELP_ERREUR

	#include "global.h"		// Pour récupérer la définition de la variable coul

	std::string message_usage = // option -h
		"usage: mren [-f|-d] [-riInv] <regex pattern> <remplacement> [dirname ...]";

	std::string message_description =
		"Renommage multiple selon un certain modèle";

	std::string message_version = "version 2025-03-01";

	std::string message_aide = // option --help
		message_usage+"\n""\n"+message_description+"\n""\n"
		"Arguments en position:\n"
		"  <regex pattern>   Modèle à chercher: Mettre entre '...'\n"
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
		"  -ver, --version   Renommage multiple à partir d'un modèle\n"
		"  -h, --help        Montre ce message d'aide et termine";

	std::string message_exclude =
		"Pour les flags «f|d», il sont mutuellement exclusif. C'est un ou c'est l'autre.";

	std::string message_erreur =
		coul.FGROUGE+"- - ATTENTION - - ATTENTION - - ATTENTION - - ATTENTION - - ATTENTION - -"+coul.RESET+"\n"
		"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
		"Il faut au minimum: <modèle> <remplacement>\n"
		"en ligne de commande: "+coul.FGROUGE+"ex. '\\.jpeg' '.jpg'"+coul.RESET+"\n"
		"Plus les flags de contrôle le cas échéant.\n"
		"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"+message_aide;

	void prt_message(std::string &);

#endif // HELP_ERREUR
