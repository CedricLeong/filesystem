#include <stdio.h>
#include <string.h>
#include <time.h>
#include "i_node.h"
#include "super_block.h"
#include "error.h"

int sfs_create(char *pathname, int type) {
    if (strlen(pathname) != 0) {
        char name[strlen(pathname) + 1];
        strcpy(name, pathname);
        char *tok = strtok(name, "/");

        //TODO: loop through each token to get the name of file being created (folder hierarchy)

        // Check if a file with the same name already exists
        if(find_file(pathname) != 0) {

            // Create new inode for the file
            inode new_inode;
            strcpy(new_inode.name, tok);

            new_inode.file_size = 0;

            char *i_number = calloc(2, sizeof(int));
            get_next_i_number(i_number);
            new_inode.i_number = i_number;

            int free_blk_no = calloc(2, sizeof(int));
            get_empty_blk(&free_blk_no);
            new_inode.index_blk_location = free_blk_no;

            time_t currentTime = time(NULL);
            char *time = asctime(localtime(&currentTime));
            new_inode.time_created = time;
            new_inode.time_last_accessed = time;
            new_inode.time_last_modified = time;

            new_inode.type = type;
            new_inode.file_size = 0;

            //TODO: Add the inode to i_node table and save it to disk
            add_new_inode(&new_inode);

            error(SUCCESSFULLY_CREATED_FILE);
            return 0;
        } else {
            error(FILE_WITH_NAME_EXISTS);
            return -1;
        }
    } else {
        error(NO_FILE_NAME_ENTERED);
        return -1;
    }
}
