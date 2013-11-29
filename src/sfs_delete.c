#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "open_file_table.h"
#include "i_node.h"
#include "error.h"

int sfs_delete(char *pathname) {
	// delete pathname
	if(get_opened_file_fd(pathname) >= 0) {
		return error(ERROR_DELETE_FILE_IS_OPEN);
	}

	char *name = calloc(50, sizeof(char));
	strcpy(name, pathname);

	char *tok = strtok(pathname, "/");

	int depth = 0;
	char *hierarchy[8];

	while(tok != NULL) {
		hierarchy[depth] = calloc(6, sizeof(char));
		strcpy(hierarchy[depth], tok);

		depth++;
		tok = strtok(0, "/");
	}

	char *parent_i_number = calloc(2, sizeof(char));
	for(int i=0; i<depth; i++) {
		int found;

		if (i == 0) {
			parent_i_number = "00";
		}

		found = find_file(hierarchy[i], parent_i_number);

		if(found == 0 && i == depth-1) {

			// found the target file now delete it
			int type;
			get_type(hierarchy[i], parent_i_number, &type);
			if (type == 0) {
				// go ahead and delete it. its a reg file
				char *i_number = calloc(2, sizeof(char));
				get_i_number(hierarchy[i], parent_i_number, i_number);
				delete_inode(atoi(i_number));
				return 0;
			} else {
				// check if it has children
				char *children = calloc(512, sizeof(char));
				dir_get_children(name, children);

				if (strlen(children) == 0) {
					// go ahead and delete it; it has no children
					char *i_number = calloc(2, sizeof(char));
					get_i_number(hierarchy[i], parent_i_number, i_number);
					delete_inode(atoi(i_number));
					return 0;

				} else {
					// through error since it has children
					return error(ERROR_DELETE_DIR_HAS_CHILDREN);
				}
			}



		} else if (found == 0) {
			char *parent = calloc(2, sizeof(char));
			if (i == 0) {
				parent = "00";
			} else {
				strcpy(parent, parent_i_number);
			}
			parent_i_number = calloc(2, sizeof(char));
			get_i_number(hierarchy[i], parent, parent_i_number);
			continue;
		} else if (found !=0 && i == depth-1) {
			return error(FILE_NOT_FOUND);
		} else {
			return error(PATHNAME_ERROR);
		}
	}
	return -1;
}
