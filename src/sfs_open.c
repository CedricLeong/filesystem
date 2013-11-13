#include <stdio.h>
#include "error.h"
#include "open_file_table.h"

int sfs_open(char *pathname)
{
	// Check if file is there
	if(find_file(pathname) == 0) {
        int fd = add_opened_file(pathname);
        if(fd >= 0) {
            printf("%s\n", "The file was opened with fd: ", fd);
            return 0;
        } else {
            return -1;
        }

	} else {
        error(FILE_NOT_FOUND);
        return -1;
	}
}
