#include "i_node.h"
#include "error.h"
#include <stdio.h>
#include <string.h>

int sfs_gettype(char* pathname)
{
    int* type;

    char name[strlen(pathname) + 1];
    strcpy(name, pathname);	// Check if file is there
	if(find_file(name) == 0) {
        char *iname = strtok(pathname, "/");
        get_type(iname, &type);

    }
	else {
        return error(FILE_NOT_FOUND);
	}

    if (type == 0){
        return 0;}
    return 1;

}
