#include <stdio.h>
#include <string.h>
#include "i_node.h"

int sfs_write(int fd, int start, int length, char *mem_pointer) {

char *contents = calloc(1024, sizeof(char));
char *tempbuffer = calloc(1024, sizeof(char));

    char *pathname = calloc(30, sizeof(char));
    if (get_opened_file(fd, pathname) == 0) {
        char *name = strtok(pathname, "/");

       // assume contents has all of file contents and is size of 1024
	    get_file_contents(contents, name);
	    // move the first start bytes to tempbuffer
		strncpy(tempbuffer, contents, start);
		// concate the mem_pointer to temp buffer
		strcat(tempbuffer, mem_pointer);
		// combine the temp buffer and original contents of the file (memmove can make strings overllap another)
		memmove(tempbuffer+start+length-1, contents+start+length-1,1024-start-length);
		// save it to disk 
        save_file_contents(tempbuffer, name);
    } else {
        return -1;
    }

}
