#include <stdio.h>
#include "error.h"
#include "open_file_table.h"

int sfs_open(char *pathname)
{
    char name[strlen(pathname) + 1];
    strcpy(name, pathname);
	// Check if file is there
	if(find_file(name) == 0) {
        int fd = add_opened_file(name);
        if(fd >= 0) {
            printf("%s%d\n", "The file was opened with fd: ", fd);
            return 0;
        } else {
            return -1;
        }

	} else {
        error(FILE_NOT_FOUND);
        return -1;
	}
}
