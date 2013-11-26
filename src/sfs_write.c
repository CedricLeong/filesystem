#include <stdio.h>
#include <string.h>
#include "i_node.h"
#include "error.h"
#include "open_file_table.h"

int sfs_write(int fd, int start, int length, char *mem_pointer) {



char *contents = calloc(128, sizeof(char));
char *tempbuffer = calloc(1024, sizeof(char));
int* type;

    char *pathname = calloc(30, sizeof(char));
    if (get_opened_file(fd, pathname) == 0) {
        char *name = strtok(pathname, "/");
            // Check if the file writing to is a directory file
            get_type(name,&type );
            if (type == 1)
                return error(WRITING_TO_DIR);


	    if (start < 0) {
		        // assume contents has all of file contents and is size of 1024
			    get_file_contents(name,0,128,contents);
			    // move the first start bytes to tempbuffer
				strncpy(tempbuffer, contents, start);
				// concate the mem_pointer to temp buffer
				strcat(tempbuffer, mem_pointer);
				// combine the temp buffer and original contents of the file (memmove can make strings overllap another)
				memmove(tempbuffer+start+length-1, contents+start+length-1,1024-start-length);
				// save it to disk
		        save_file_contents(tempbuffer, name, start, 0);
		        return 0;
	    } else {
	    	save_file_contents(mem_pointer, name, start, length);
	    	return 0;
	    }
    } else {
        return -1;
    }

}
