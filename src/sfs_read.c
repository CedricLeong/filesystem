#include <stdio.h>
#include "i_node.h"
#include "open_file_table.h"

int sfs_read(int fd,int start, int length, char* buffer) {

 	char *pathname = calloc(30, sizeof(char));
    if (get_opened_file(fd, pathname) == 0) {
        char *name = strtok(pathname, "/");
        char *contents = calloc(1024, sizeof(char));

        get_file_contents(name, contents);
        printf("%s\n", contents);
    } else {
        return -1;
    }

 	return 0;

}
