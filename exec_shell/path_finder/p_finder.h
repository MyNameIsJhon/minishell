#ifndef P_FINDER
#define P_FINDER

#define BUILTINS "./builtins/execs"

int program_finder(char *path, int flag);
char *finder_to_path(char *prog_name);

#endif