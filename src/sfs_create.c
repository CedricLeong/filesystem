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

        int depth = 0;
        char *hierarchy[8];
        while(tok != NULL) {
        	hierarchy[depth] = tok;

        	depth++;
        	tok = strtok(0, "/");
        }

        char *parent_i_number = calloc(2, sizeof(char));
        for(int i=0; i<depth; i++) {
        	int found = find_file(hierarchy[i]);
        	if(found == 0 && i == depth-1) {
        		return error(FILE_WITH_NAME_EXISTS);
        	} else if (found == 0) {
        		get_i_number(hierarchy[i], parent_i_number);
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

				int free_blk_no = calloc(2, sizeof(int));
				get_empty_blk(&free_blk_no);
				new_inode.index_blk_location = free_blk_no;

				new_inode.type = type;

				if (depth > 1) {
					new_inode.parent_i_number = parent_i_number;
				} else {
					new_inode.parent_i_number = "00";
				}

				//TODO: Add the inode to i_node table and save it to disk
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
}
