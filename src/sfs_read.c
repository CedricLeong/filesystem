#include <stdio.h>
#include "error.h"
#include "i_node.h"
#include "open_file_table.h"

int sfs_read(int fd,int start, int length, char* buffer) {



    int type;


 	char *pathname = calloc(30, sizeof(char));
    if (get_opened_file(fd, pathname) == 0) {
        char *name = strtok(pathname, "/");
        if(name == NULL) {
        	name = "/";
        }
            get_type(name, &type);
            if (type == 1)
                return error(READING_FROM_DIR);

        char *contents = calloc(512, sizeof(char));

        get_file_contents(name, contents);

        if ((start + length) > strlen(contents)) {
            return error(READING_BEYOND_FILE_SIZE);
        }
        strncpy(buffer, contents+start, length);
    } else {
        return error(FILE_NOT_FOUND_IN_OPEN_TABLE);
    }

 	return 0;

}
