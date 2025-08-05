#ifndef __STRINGS_SEL__
	#define __STRINGS_SEL__

	#include <map>
	#include <string>

	#include "global.h"

	std::string get_lang_from_env();
	void set_mren_locale();
	std::string mren_locale(const std::string&);

	const std::map<std::string, std::map<std::string, std::string>> translations = {
		{"message_description", {
			{"en", "Multiple renaming from a pattern"},
			{"fr", "Renommage multiple selon un certain motif"},
			{"es", "Cambio de nombre múltiple según un patrón"}}
		},
		{"message_usage", {
			{"en", "usage: mren [-f|-d] [-riInv] <regex pattern> <remplacement> [dirname ...]"},
			{"fr", "usage: mren [-f|-d] [-riInv] <motif regex> <remplacement> [dirname ...]"},
			{"es", "usage: mren [-f|-d] [-riInv] <patrón regex> <sustitución> [dirname ...]"}}
		},
		{"message_exclude", {
			{"en", "For «f|d» flags, they are mutually exclusive. It's one or the other."},
			{"fr", "Pour les flags «f|d», il sont mutuellement exclusif. C'est un ou c'est l'autre."},
			{"es", "Para los flags «f|d», son mutuamente exclusivos. Es uno o el otro."}}
		},
		{"err_invalid_dir", {
			{"en", " is not a valid folder."},
			{"fr", " n'est pas un répertoire valide."},
			{"es", " no es un directorio válido."}}
		},
		{"verbose_iteration", {
			{"en", "Processing directory: "},
			{"fr", "Traitement du répertoire: "},
			{"es", "Procesando el directorio: "}}
		},
		{"pas_correspondande", {
			{"en", "There is no match for this directory ..."},
			{"fr", "Pas de correspondance pour ce répertoire ..."},
			{"es", "No hay coincidencias para este directorio ..."}}
		},
		{"err_directory", {
			{"en", "Unable to work with directory "},
			{"fr", "Impossible de travailler avec le répertoire "},
			{"es", "No se puede trabajar con el directorio "}}
		},
		{"deviendrait", {
			{"en", " " + coul.FGVERT + " ==> would become ==> " + coul.RESET + " "},
			{"fr", " " + coul.FGVERT + " ==> Deviendrait ==> " + coul.RESET + " "},
			{"es", " " + coul.FGVERT + " ==> Se convertiría en ==> " + coul.RESET + " "}}
		},
		{"est_devenu", {
			{"en", " " + coul.FGROUGE + " ==> became ==> " + coul.RESET + " "},
			{"fr", " " + coul.FGROUGE + " ==> est devenu ==> " + coul.RESET + " "},
			{"es", " " + coul.FGROUGE + " ==> se ha convertido ==> " + coul.RESET + " "}}
		},
		{"renom_impossible", {
			{"en", coul.FGROUGE + " can't rename " + coul.RESET + " %s to %s"},
			{"fr", coul.FGROUGE + " Je ne peux renommer " + coul.RESET + " %s en %s"},
			{"es", coul.FGROUGE + " No puedo cambiar el nombre de  " + coul.RESET + " %s a %s"}}
		},
		{"err_chdir", {
			{"en", coul.FGROUGE + " --- " + coul.RESET + " Can't " + coul.FGROUGE + " «chdir()» " +
					coul.RESET + " to folder " + coul.FGROUGE + " %s ---" + coul.RESET},
			{"fr", coul.FGROUGE + " --- " + coul.RESET + " Je ne peux " + coul.FGROUGE + " «chdir()» " +
					coul.RESET + " vers le répertoire " + coul.FGROUGE + " %s ---" + coul.RESET},
			{"es", coul.FGROUGE + " --- " + coul.RESET + " No puedo hacer un " + coul.FGROUGE + " «chdir()» " +
					coul.RESET + " al directorio " + coul.FGROUGE + " %s ---" + coul.RESET}}
		},
		{"lire_rep_impossible", {
			{"en", "Can't read directory "},
			{"fr", "Ne peut lire le répertoire "},
			{"es", "No puede leer el directorio "}}
		},
		{"message_aide", {
			{"en", "Positional arguments:\n"
					"  <regex pattern>   Pattern to serch: Put into single quote '...'\n"
					"  <remplacement>    Replacement string. Must follow the pattern.\n"
					"  [dirname ...]     Path(s) to search.\n"
					"\n"
					"Options:\n"
					"  -f                  Search only for files.\n"
					"  -d                  Search only for folders.\n"
					"  -r,   --recursive   Recursively works through directories.\n"
					"  -i,   --include     In recursive mode, include the folder pass on the command line.\n"
					"  -I,   --ignoreCase  Self explained.\n"
					"  -n,   --simulate    Simulates the requested operations - Files affected in GREEN.\n"
					"  -v,   --verbose     Gives details of the processed file(s) - Affected files in RED.\n"
					"  -ver, --version     Multiple renaming from a pattern.\n"
					"  -h,   --help        Show this help message and exit."},
			{"fr", "Arguments en position:\n"
					"  <motif regex>     Motif à chercher: Mettre entre guillements '...'\n"
					"  <remplacement>    Chaîne de remplacement. Doit obligatoirement suivre le motif.\n"
					"  [dirname ...]     Répertoire(s) de recherche.\n"
					"\n"
					"Options:\n"
					"  -f                  N'agit que sur les fichiers.\n"
					"  -d                  N'agit que sur les répertoires.\n"
					"  -r,   --recursive   Procède de façon récursive sur les répertoires.\n"
					"  -i,   --include     En mode récusif, inclu le dossier en ligne de commande.\n"
					"  -I,   --ignoreCase  Fait une recherche en ignorant la case.\n"
					"  -n,   --simulate    Simule les opérations demandées - Fichiers affectés en VERT.\n"
					"  -v,   --verbose     Donne des détails sur le(s) fichier(s) traité(s) - Fichiers affectés en ROUGE.\n"
					"  -ver, --version     Renommage multiple à partir d'un motif.\n"
					"  -h,   --help        Montre ce message d'aide et termine."},
			{"es", "Argumentos en posición:\n"
					"  <patrón regex>   Patrón de búsqueda: Poner entre comillas '...'\n"
					"  <reemplazo>   Cadena de reemplazo. Debe seguir el patrón.\n"
					"  [dirname ...]   Directorio(s) de búsqueda.\n"
					"\n"
					"Opciones:\n"
					"  -f                  Solo afecta a los archivos.\n"
					"  -d                  Solo afecta a los directorios.\n"
					"  -r,   --recursive   Recursivo a los directorios.\n"
					"  -i,   --include     En modo recursivo, incluye la carpeta de línea de comandos.\n"
					"  -I,   --ignoreCase  Buscar ignorando la casilla.\n"
					"  -n,   --simulate    Simula las operaciones solicitadas - Archivos asignados en VERDE.\n"
					"  -v,   --verbose     Da detalles sobre el(s) archivo(s) procesado(s) - Archivos asignados en ROJO.\n"
					"  -ver, --version     Cambio de nombre múltiple a partir de un patrón.\n"
					"  -h,   --help        Muestra este mensaje de ayuda y finaliza."}}
			},
		{"message_erreur", {
			{"en", coul.FGROUGE+"-- WARNING - - WARNING - - WARNING - - WARNING - - WARNING - - WARNING --"+coul.RESET+"\n"
					"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
					"You must at least give: <pattern> <replacement>\n"
					"On command line: "+coul.FGROUGE+"ex. mren '\\.jpeg' '.jpg'"+coul.RESET+"\n"
					"Plus control flags if needed.\n"
					"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"},
			{"fr", coul.FGROUGE+"- - ATTENTION - - ATTENTION - - ATTENTION - - ATTENTION - - ATTENTION - -"+coul.RESET+"\n"
					"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
					"Vous devez au moins donner: <motif> <remplacement>\n"
					"en ligne de commande: "+coul.FGROUGE+"ex. mren '\\.jpeg' '.jpg'"+coul.RESET+"\n"
					"Plus les drapeaux de contrôle le cas échéant.\n"
					"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"},
			{"es", coul.FGROUGE+"-- WARNING - - WARNING - - WARNING - - WARNING - - WARNING - - WARNING --"+coul.RESET+"\n"
					"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
					"Al menos debe dar: <Patrón> <reemplazo>\n"
					"en línea de comandos: "+coul.FGROUGE+"ex. mren '\\.jpeg' '.jpg'"+coul.RESET+"\n"
					"Además de las banderas de control si es necesario.\n"
					"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"}}
		}
	};

	#endif	// __STRINGS_SEL__
