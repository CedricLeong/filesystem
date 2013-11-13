#include <stdio.h>

int sfs_write(int fd, int start, int length, char *mem_pointer) {

    char *pathname = calloc(30, sizeof(char));
    if (get_opened_file(fd, pathname) == 0) {
        char *name = strtok(pathname, "/");

        // get files index_block
        // get all blocks of the file
        // concat all of them
    } else {
        return -1;
    }

}
