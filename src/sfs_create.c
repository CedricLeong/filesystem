#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "i_node.h"
#include "super_block.h"
#include "error.h"

int sfs_create(char *pathname, int type) {
    if (strlen(pathname) != 0) {
        char name[strlen(pathname) + 1];
        strcpy(name, pathname);
        char *tok = strtok(name, "/");

        int depth = 0;
        char *hierarchy[8];
        while(tok != NULL) {
        	hierarchy[depth] = tok;

        	depth++;
        	tok = strtok(0, "/");
        }

        char *current_i_number = calloc(2, sizeof(char));
        for(int i=0; i<depth; i++) {
        	int found;

        	if (i == 0) {
        		found = find_file(hierarchy[i], "00");
        	} else {
        		found = find_file(hierarchy[i], current_i_number);
        	}

        	if(found == 0 && i == depth-1) {
        		return error(FILE_WITH_NAME_EXISTS);
        	} else if (found == 0) {
        		char *parent = calloc(2, sizeof(char));
				if (i == 0) {
					parent = "00";
				} else {
					strcpy(parent, current_i_number);
				}

				// Check if the the file before the file we're creating is a directory type
				if (i == depth-2) {
					int temp_type;
					get_type(hierarchy[i], parent, &temp_type);

					if (temp_type == 0) {
						return error(ERROR_PARENT_REG_FILE);
					}
				}



				get_i_number(hierarchy[i], parent, current_i_number);
        		continue;
        	} else if (found !=0 && i == depth-1) {

        		// Create new inode for the file
				inode new_inode;

				if(strlen(hierarchy[i]) > 5) {
					return error(FILE_NAME_TOO_LONG);
				}
				new_inode.name = calloc(6, sizeof(char));
				strcpy(new_inode.name, hierarchy[i]);

				new_inode.file_size = "0" ;

				char *i_number = calloc(2, sizeof(int));
				get_next_i_number(i_number);
				new_inode.i_number = i_number;

				int free_blk_no;
				get_empty_blk(&free_blk_no);
				new_inode.index_blk_location = free_blk_no;

				new_inode.type = type;

				if (depth > 1) {
					new_inode.parent_i_number = current_i_number;
				} else {
					new_inode.parent_i_number = "00";
				}

				add_new_inode(&new_inode);

				return error(SUCCESSFULLY_CREATED_FILE);
        	} else {
        		return error(PATHNAME_ERROR);
        	}
        }

    } else {
        error(NO_FILE_NAME_ENTERED);
        return -1;
    }
    return -1;
}
