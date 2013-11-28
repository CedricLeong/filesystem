#include <stdio.h>
#include <string.h>
#include "open_file_table.h"
#include "i_node.h"
int sfs_delete(char *pathname) {
	// deletle pathname
	int fd = get_opened_file_fd(pathname);
	int close;
	int inumber;
	if (fd != -1){
	while (close != -1)
	 {
	 	close = close_file(fd);
	 }}
	// deletle inumber
    char path[strlen(pathname) + 1];
    strcpy(path, pathname);
    char *tok = strtok(path, "/");

    for (int i=0; i<64; i++) {
        if (strcmp(inode_table[i].name,tok) == 0) {
            // delete contents
            //char* contents = calloc(atoi(inode_table[i].file_size),sizeof(char));
            //save_file_contents(contents, inode_table[i].name);


            // delete from memory
            inumber = atoi(inode_table[i].i_number);
            i_numbers[inumber] = 0;
            inode_table[i].name[0] = '\0';
            strcpy(inode_table[i].i_number, "99");
            inode_table[i].file_size = "0";
            delete_inode_now();

            return 0;

        }
    }
    // deletle inode

return -1;
}
