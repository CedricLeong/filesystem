#include "open_file_table.h"
#include "error.h"
#include <stdio.h>

int sfs_readdir(int fd) {

	char *pathname = calloc(30, sizeof(char));

	if (get_opened_file(fd, pathname) == 0) {
		int type;
		if (strcmp(pathname, "/") == 0) {
			type = 1;
		} else {
			int type = sfs_gettype(pathname);
		}

		if (type == 0) {
			// Regular file type
			return error(READDIR_REG_FILE);
		} else if (type == 1) {
			// Directory file type

			char *children = calloc(512, sizeof(char));
			dir_get_children(pathname, children);

			if (strlen(children) == 0) {
				printf("%s\n", "The directory file does not contain any files.");
			} else {
				printf("%s", children);
			}
			return 0;
		} else {
			// error getting finding the file in the open file table
			return -1;
		}
	}
}
