# mren - Mutilple files/directories renaming using pattern

usage: mren [-f|-d] [-riInv] <regex pattern> <remplacement> [dirname ...]

Multiple renaming from a pattern

Positional arguments:
  <regex pattern>   Pattern to serch: Put into single quote '...'
  <remplacement>    Replacement for the found pattern
  [dirname ...]     Path(s) to search

Options:
  -f                Search only for files
  -d                Search only for folders
  -r, --recursive   Recursively works through directories
  -i, --include     In recursive mode, include the folder pass on the command line
  -I, --ignoreCase  Self explained
  -n, --simulate    Simulates the requested operations - Files affected in GREEN
  -v, --verbose     Gives details of the processed file(s) - Affected files in RED
  -ver, --version   Multiple renaming from a pattern
  -h, --help        Show this help message and exit
