#include <stdio.h>
#include "open_file_table.h"
#include "i_node.h"
int sfs_delete(char *pathname) {
	// deletle pathname
	int fd = get_opened_file(pathname);
	int close;
	char* inumber; 
	while (close != -1)
	 {
	 	close = close_file(fd); 
	 }

	// deletle inumber
    char path[strlen(pathname) + 1];
    strcpy(path, pathname);
    char *tok = strtok(path, "/");

    for (int i=0; i<64; i++) {
        if (strcmp(inode_table[i].name,tok) == 0) {
            inumber = inode_table[i].i_number;
            inode_table[i] = NULL;
        }
    }


    for (int i=0; i<64; i++) {
        if (i_number[i]) == 0) {
			i_number[i] = NULL;
            return 0;
        }
    }

return -1;
}
