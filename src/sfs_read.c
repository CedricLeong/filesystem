#include <stdio.h>
#include "error.h"
#include "i_node.h"
#include "open_file_table.h"

int sfs_read(int fd,int start, int length, char* buffer) {



    int* type;


 	char *pathname = calloc(30, sizeof(char));
    if (get_opened_file(fd, pathname) == 0) {
        char *name = strtok(pathname, "/");
            get_type(name,&type );
            if (type == 1)
                return error(READING_FROM_DIR);

        char *contents = calloc(512, sizeof(char));

        get_file_contents(name, start, length, contents);
        printf("%s\n", contents);
        buffer = contents;
    } else {
        return -1;
    }

 	return 0;

}
