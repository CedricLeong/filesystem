#include <stdio.h>
#include "i_node.h"

int sfs_write(int fd, int start, int length, char *mem_pointer) {

    char *pathname = calloc(30, sizeof(char));
    if (get_opened_file(fd, pathname) == 0) {
        char *name = strtok(pathname, "/");

        save_file_contents(mem_pointer, name);
    } else {
        return -1;
    }

}
