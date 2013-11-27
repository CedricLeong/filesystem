#include <stdio.h>
#include <string.h>
#include "i_node.h"
#include "error.h"
#include "open_file_table.h"

int sfs_write(int fd, int start, int length, char *mem_pointer) {



char *contents = calloc(1024, sizeof(char));
char *tempbuffer = calloc(1024, sizeof(char));
int* type;

    char *pathname = calloc(30, sizeof(char));
    if (get_opened_file(fd, pathname) == 0) {
        char *name = strtok(pathname, "/");
            // Check if the file writing to is a directory file
            get_type(name,&type );
            if (type == 1)
                return error(WRITING_TO_DIR);

        get_file_contents(name, contents);
        if (strcmp(contents, "") != 0) {
            strcpy(tempbuffer, contents);
        }
	    if (start < 0) {
				// concate the mem_pointer to temp buffer
				char *buf = calloc(length, sizeof(char));
                strncpy(buf, mem_pointer, length);
				strcat(tempbuffer, buf);
				// combine the temp buffer and original contents of the file (memmove can make strings overllap another)
				//memmove(tempbuffer+start+length-1, contents+start+length-1,1024-start-length);
				// save it to disk
		        save_file_contents(tempbuffer, name);
		        return 0;
	    } else {
            if ((length + start) <= strlen(tempbuffer)) {
                char *buf = calloc(length, sizeof(char));
                strncpy(buf, mem_pointer, length);

                char *buf_left = calloc(1023, sizeof(char));
                char *buf_right = calloc(1023, sizeof(char));

                strncpy(buf_left, tempbuffer, start);
                strcpy(buf_right, tempbuffer + start + length);
                strcat(buf_left, buf);
                strcat(buf_left, buf_right);
                save_file_contents(buf_left, name);
                return 0;
            } else {
                return error(WRITING_BEYOND_FILE_SIZE);
            }
	    }
    } else {
        return -1;
    }

}
