#include <stdio.h>
#include <string.h>
#include "i_node.h"

int sfs_getsize(char *pathname) {

    char name[strlen(pathname) + 1];
    strcpy(name, pathname);

    char *tok = strtok(name, "/");
    get_size(tok);
}
