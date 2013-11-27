#include <stdio.h>
#include "error.h"
#include "open_file_table.h"

int sfs_open(char *pathname)
{
    char name[strlen(pathname) + 1];
    strcpy(name, pathname);
	// Check if file is there
    if (strcmp(pathname, "/") == 0) {
    	int fd = add_opened_file(name);
		if(fd >= 0) {
			return fd;
		} else {
			return -1;
		}
    } else if(find_file(name) == 0) {
        int fd = add_opened_file(name);
        if(fd >= 0) {
            return fd;
        } else {
            return -1;
        }

	} else {
        return error(FILE_NOT_FOUND);
	}
}
