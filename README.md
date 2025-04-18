## mren - Mutilple files/directories renaming using pattern.

```plaintext
usage: mren [-f|-d] [-riInv] <regex pattern> <remplacement> [dirname ...]

Multiple renaming from a pattern.

Positional arguments:
  <regex pattern>   Pattern to serch: Put into single quote '...'
  <remplacement>    Replacement string. Must follow the pattern.
  [dirname ...]     Path(s) to search.

Options:
  -f                Search only for files.
  -d                Search only for folders.
  -r, --recursive   Recursively works through directories.
  -i, --include     In recursive mode, include the folder pass on the command line.
  -I, --ignoreCase  Self explained.
  -n, --simulate    Simulates the requested operations - Files affected in GREEN.
  -v, --verbose     Gives details of the processed file(s) - Affected files in RED.
  -ver, --version   Multiple renaming from a pattern.
  -h, --help        Show this help message and exit.
```

----
## mren - Renommage mutiple de fichiers/répertoires utilisant un motif.

```plaintext
usage: mren [-f|-d] [-riInv] <motif regex> <remplacement> [dirname ...]

Renommage multiple selon un certain motif.

Arguments en position:
  <motif regex>     Motif à chercher: Mettre entre guillements '...'
  <remplacement>    Chaîne de remplacement. Doit obligatoirement suivre le motif.
  [dirname ...]     Répertoire(s) de recherche.

Options:
  -f                N'agit que sur les fichiers.
  -d                N'agit que sur les répertoires.
  -r, --recursive   Procède de façon récursive sur les répertoires.
  -i, --include     En mode récusif, inclu le dossier en ligne de commande.
  -I, --ignoreCase  Fait une recherche en ignorant la case.
  -n, --simulate    Simule les opérations demandées - Fichiers affectés en VERT.
  -v, --verbose     Donne des détails sur le(s) fichier(s) traité(s) - Fichiers affectés en ROUGE.
  -ver, --version   Renommage multiple à partir d'un motif.
  -h, --help        Montre ce message d'aide et termine.
```
