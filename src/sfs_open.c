#include <stdio.h>
#include "error.h"
#include "open_file_table.h"

int sfs_open(char *pathname)
{
	char *path = calloc(strlen(pathname), sizeof(char));
	strcpy(path, pathname);

	if (strcmp(pathname, "/") == 0) {
		int fd = add_opened_file("/");
		if(fd >= 0) {
			return fd;
		} else {
			return -1;
		}
	} else {

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
				found = find_file(hierarchy[i], "00");
			} else {
				found = find_file(hierarchy[i], parent_i_number);
			}

			if(found == 0 && i == depth-1) {

				int fd = add_opened_file(path);
				if(fd >= 0) {
					return fd;
				} else {
					return -1;
				}
			} else if (found == 0) {
				char *parent = calloc(2, sizeof(char));
				if (i == 0) {
					parent = "00";
				} else {
					strcpy(parent, parent_i_number);
				}
				get_i_number(hierarchy[i], parent, parent_i_number);
				continue;
			} else if (found !=0 && i == depth-1) {
				return error(FILE_NOT_FOUND);
			} else {
				return error(PATHNAME_ERROR);
			}
		}
	}

//
//    if (strcmp(pathname, "/") == 0) {
//    	int fd = add_opened_file(tok);
//		if(fd >= 0) {
//			return fd;
//		} else {
//			return -1;
//		}
//    } else if(find_file(tok) == 0) {
//        int fd = add_opened_file(tok);
//        if(fd >= 0) {
//            return fd;
//        } else {
//            return -1;
//        }
//
//	} else {
//        return error(FILE_NOT_FOUND);
//	}
}
