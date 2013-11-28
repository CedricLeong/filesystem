#include "i_node.h"
#include "error.h"
#include <stdio.h>
#include <string.h>

int sfs_gettype(char* pathname)
{
    int type;

    char *tok = strtok(pathname, "/");

	int depth = 0;
	char *hierarchy[8];

	while(tok != NULL) {
		hierarchy[depth] = tok;

		depth++;
		tok = strtok(0, "/");
	}

	char *parent_i_number = calloc(2, sizeof(char));
	for(int i=0; i<depth; i++) {
		int found;

		if (i == 0) {
			found = find_file(hierarchy[i], "00");
			parent_i_number = "00";

		} else {
			found = find_file(hierarchy[i], parent_i_number);
		}

		if(found == 0 && i == depth-1) {

			get_type(hierarchy[i], parent_i_number, &type);

			return type;
		} else if (found == 0) {

			char *parent = calloc(2, sizeof(char));
			if (i == 0) {
				parent = "00";
			} else {
				strcpy(parent, parent_i_number);
			}
			parent_i_number = calloc(2, sizeof(char));
			get_i_number(hierarchy[i], parent, parent_i_number);

			get_type(hierarchy[depth-1], parent_i_number, &type);



			continue;
		} else if (found !=0 && i == depth-1) {
			return error(FILE_NOT_FOUND);
		} else {
			return error(PATHNAME_ERROR);
		}
	}

}
