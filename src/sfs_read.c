#include <stdio.h>
#include "error.h"
#include "i_node.h"
#include "open_file_table.h"

int sfs_read(int fd,int start, int length, char* buffer) {

    int type;

 	char *pathname = calloc(30, sizeof(char));
    if (get_opened_file(fd, pathname) == 0) {
    	char *hierarchy[8];
    	int depth = 0;
    	char *parent_i_number = calloc(2, sizeof(char));
    	if (strcmp(pathname, "/") == 0) {
    		type = 0;
    	} else {
			char *name = strtok(pathname, "/");

				// Check if the file writing to is a directory file

			while(name != NULL) {
				hierarchy[depth] = name;

				depth++;
				name = strtok(0, "/");
			}

			if(name == NULL) {
				name = "/";
			}

			for (int i=0; i<depth-1; i++) {
				char *parent = calloc(2, sizeof(char));
				if (i == 0) {
					parent = "00";
				} else {
					strcpy(parent, parent_i_number);
				}
				get_i_number(hierarchy[i], parent, parent_i_number);
			}

			if (depth == 1) {
				parent_i_number = "00";
			}


			get_type(hierarchy[depth-1], parent_i_number, &type);
    	}
		if (type == 1)
			return error(READING_FROM_DIR);

        char *contents = calloc(512, sizeof(char));

        get_file_contents(hierarchy[depth-1], parent_i_number, contents);

        if ((start + length) > strlen(contents)) {
            return error(READING_BEYOND_FILE_SIZE);
        }
        strncpy(buffer, contents+start, length);
    } else {
        return error(FILE_NOT_FOUND_IN_OPEN_TABLE);
    }

 	return 0;

}
