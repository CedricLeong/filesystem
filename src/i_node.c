#include "i_node.h"
#include "blockio.h"
#include "error.h"
#include "super_block.h"
#include "i_node.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Global data that should be visible to inode and super block
short int fd_table[64];
short int index_block[8][64];
char pathname_parse[7][64];
int i_numbers[64] = {0};
inode inode_table[64];
int inode_blocks = 0;
/* Creates the index numbers in memory then in the disk itself
Each file gets around 16 bytes so each block can hold 8 inodes*/
int put_inode_table(void)
{
    // Root inode
    inode root;
    root.name = "/";
    root.i_number = "00";
    i_numbers[0] = 1;
    root.type = 1;
    root.file_size = "0";

    inode_table[0] = root;

    char *buf = calloc(128, sizeof(char));
    sprintf(buf, "%d:%s:%s:%d:%s:_:", 0,(char *) root.name, (char *) root.i_number, root.type, root.file_size);

    if (put_block(2, buf) == 0) {
        set_disk_bitmap_busy(2);
        inode_blocks = 1;
    } else {
        error(ERROR_WRITING_INODE_TO_DISK);
        return -1;
    }

    return 0;
}

int add_new_inode(inode *new_inode) {

    int i_number = atoi((*new_inode).i_number);
    inode_table[i_number] = *new_inode;

    return save_inode_table();
}

int save_inode_table(void) {
	char *all_inode_info = calloc(128, sizeof(char));

	for(int i=0; i<64; i++) {
		char *buf = calloc(128, sizeof(char));
		inode current_inode = inode_table[i];

		if (current_inode.name != NULL) {
			if(strlen(current_inode.name) == 0) {
				continue;
			}

			if (strcmp(current_inode.name, "/") == 0) {
				sprintf(buf, "%d:%s:%s:%d:%s:_:", i,(char *) current_inode.name, (char *) current_inode.i_number, current_inode.type, current_inode.file_size);
			} else {
				sprintf(buf, "%d:%s:%s:%d:%s:%s:%d:_:", i,(char *) current_inode.name, (char *) current_inode.i_number, current_inode.type, current_inode.parent_i_number, current_inode.file_size, current_inode.index_blk_location);
			}
			strcat(all_inode_info, buf);
		}
	}
	// Check how many blocks we need
	if (strlen(all_inode_info) > 128) {
		char *buf;
		buf = calloc (128, sizeof(char));
		double parts = ceil((double) strlen(all_inode_info)/(double)128);
		inode_blocks = parts;
		for (int i=0; i<parts; i++) {
			strncpy(buf, all_inode_info+i*128, 128);
			put_block(2+i, buf);
			set_disk_bitmap_busy(2+i);
		}

	} else {
		put_block(2, all_inode_info);
		set_disk_bitmap_busy(2);
	}
	return 0;
}

int delete_inode(int i_num) {

	inode_table[i_num].file_size = calloc(3, sizeof(char));
	inode_table[i_num].i_number = calloc(2, sizeof(char));
	inode_table[i_num].index_blk_location = calloc(3, sizeof(int));
	inode_table[i_num].name = calloc(6, sizeof(char));
	inode_table[i_num].parent_i_number = calloc(2, sizeof(char));
	inode_table[i_num].type = calloc(1, sizeof(int));

	i_numbers[i_num] = 0;

	char *buf_null = calloc(128, sizeof(char));

	// erase the inode table from disk to overwrite it cleanly
	for (int i=0; i<inode_blocks; i++) {
		put_block(2+i, buf_null);
	}

	return save_inode_table();
}

int get_inode_table_from_disk(void) {

     char *all_inode_info = calloc(8192, sizeof(char));

    char *buf;
    for (int i=0; i<10; i++) {
        buf = calloc(128, sizeof(char));
        get_block(2+i, buf);

        if (strlen(buf) == 0) {
        	break;
        }

        strcat(all_inode_info, buf);
	}

    char *tok = strtok(all_inode_info, ":");

    int counter = 0;
    inode i_node;
    int inum;
    while (tok != NULL) {
        if (strcmp(tok, "_") == 0) {
        	counter = 0;
			inode_table[inum] = i_node;
			tok = strtok(0, ":");
        }

        if (tok != NULL) {
			switch(counter) {
				case 0:
					inum = atoi(tok);
					break;
				case 1:
					i_node.name = calloc(6, sizeof(char));
					strcpy(i_node.name, tok);
					break;
				case 2:
					i_node.i_number = calloc(2, sizeof(char));
					strcpy(i_node.i_number, tok);
					break;
				case 3:
					i_node.type = atoi(tok);
					if (strcmp(i_node.name, "/") == 0) {
						counter++;
					}
					break;
				case 4:
					i_node.parent_i_number = calloc(2, sizeof(char));
					strcpy(i_node.parent_i_number, tok);
					break;
				case 5:
					i_node.file_size = calloc(3, sizeof(char));
					strcpy(i_node.file_size, tok);
					if (strcmp(i_node.name, "/") == 0) {
						counter++;
					}
					break;
				case 6:
					i_node.index_blk_location = atoi(tok);
					break;
			}
        }
        counter++;
        tok = strtok(0, ":");
    }
    return 0;
}

int get_next_i_number(char *i_number) {
    for(int i = 0; i<64; i++) {
        if (i_numbers[i] == 0) {
            i_numbers[i] = 1;

            // Make sure the i_number is 2 digits
            sprintf(i_number, "%02d", i);
            return 0;
        }
    }
    return -1;
}

int find_file(char *name, char *parent) {

    for (int i=0; i<64; i++) {
    	if (inode_table[i].name != NULL) {
			if (strcmp(inode_table[i].name, name) == 0 && strcmp(inode_table[i].parent_i_number, parent) == 0) {
				// file exists
				return 0;
			}
    	}
    }

    // file was not found
    return -1;
}

int get_file_contents(char *name, char *parent, char *contents) {
    for (int i=0; i<64; i++) {
    	if (inode_table[i].name != NULL && inode_table[i].parent_i_number != NULL) {
			if(strcmp(inode_table[i].name,name) == 0 && strcmp(inode_table[i].parent_i_number, parent) == 0) {
				int index_block = inode_table[i].index_blk_location;
				char *blocks = calloc(128, sizeof(char));
				get_block(index_block, blocks);
				if (strlen(blocks) == 0) {
					return -1;
				} else {
					// Get each block
					char *tok = strtok(blocks, ":");

					int blk_counter = 0;
					while(tok != NULL && strcmp(tok, "0") != 0) {
						int block_num = atoi(tok);

						char *buf = calloc(128, sizeof(char));
						get_block(block_num, buf);

						if (blk_counter==0) {
							strcpy(contents, buf);
						} else {
							strcat(contents, buf);
						}
						tok = strtok(0, ":");
						blk_counter++;
					}
					return 0;
				}

			}
    	}
    }

    // File was not found in the inode tabel
    return error(FILE_NOT_FOUND);
}

int save_file_contents(char *contents, char *name, char *parent) {

    char *length = calloc(4, sizeof(char));
    sprintf(length, "%d", (int) strlen(contents));


    for (int i=0; i<64; i++) {
    	if (inode_table[i].name != NULL && inode_table[i].parent_i_number != NULL) {
			if(strcmp(inode_table[i].name,name) == 0 && strcmp(inode_table[i].parent_i_number, parent) == 0) {
			   int index_block = inode_table[i].index_blk_location;
				char *blocks = calloc(128, sizeof(char));
				get_block(index_block, blocks);
				int parts = ceil((double) strlen(contents)/(double)128);
				char *tok = strtok(blocks, ":");

				int lengths[8] = {0};

				// Get lengths of every block
				if (parts > 1) {
					for (int l=0; l<parts; l++) {
						if(l<parts-1) {
							lengths[l] = 128;
						} else {
							lengths[l] = length-i*128;
						}
					}
				} else {
					lengths[0] = length;
				}


				int index_blk[8] = {0};
				for (int j=0; j<parts; j++) {
					int blk_num;
					if (tok == NULL || strlen(tok) == 0) {
						get_empty_blk(&blk_num);
					} else {
						blk_num = atoi(tok);
					}

					char *part = calloc(lengths[j], sizeof(char));
					strncpy(part, contents+j*128, lengths[j]);


					if(put_block(blk_num, part) == 0) {

						index_blk[j] = blk_num;
						printf("%s %d %s\n", "Data to block", blk_num, "has been written.");

					}

					tok = strtok(0, ":");
				}

				char *char_index_blk = calloc(128, sizeof(char));
				for (int k=0; k<8; k++) {
					char *buf = calloc(10, sizeof(char));
					if (k==0) {
						sprintf(buf, "%d", index_blk[k]);
					} else {
						sprintf(buf, ":%d", index_blk[k]);
					}

					strcat(char_index_blk, buf);
				}

				if (put_block(index_block, char_index_blk) == 0) {
					// Update the file size
					inode_table[i].file_size = length;

					return save_inode_table();
				}

				return -1;


			}
    	}
    }
    return -1;
}

int change_size(char *pathname, int bytes) {

	char *tok = strtok(pathname, "/");
	char *parent_i_num = calloc(2, sizeof(char));
	char *current_i_num = calloc(2, sizeof(char));

	int depth = 0;
	char *hierarchy[8];
	while(tok != NULL) {
		hierarchy[depth] = tok;

		depth++;
		tok = strtok(0, "/");
	}

	if (depth == 1) {
		parent_i_num = "00";
	} else {
		strcpy(parent_i_num, current_i_num);
	}

	for (int i=0; i<depth; i++) {
		if (get_i_number(hierarchy[i], parent_i_num, current_i_num) < 0) {
			//error looking up the file
			return -1;
		}
	}

	int i_num = atoi(current_i_num);
	inode_table[i_num].file_size = calloc(3, sizeof(char));
	sprintf(inode_table[i_num].file_size, "%d", bytes);
	return 0;
}

int get_size(char *pathname) {

	char *tok = strtok(pathname, "/");
	char *parent_i_num = calloc(2, sizeof(char));
	char *current_i_num = calloc(2, sizeof(char));

	int depth = 0;
	char *hierarchy[8];
	while(tok != NULL) {
		hierarchy[depth] = tok;

		depth++;
		tok = strtok(0, "/");
	}

	for (int i=0; i<depth; i++) {
		if (i == 0) {
			parent_i_num = "00";
		} else {
			parent_i_num = calloc(2, sizeof(char));
			strcpy(parent_i_num, current_i_num);
		}
		if (get_i_number(hierarchy[i], parent_i_num, current_i_num) < 0) {
			//error looking up the file
			return -1;
		}
	}

	int i_num = atoi(current_i_num);
	if (inode_table[i_num].type == 1) {
		return error(ERROR_DIR_SIZE);
	}
	return atoi(inode_table[i_num].file_size);
}

int get_type(char *name, char *parent, int* type) {
    for (int i=0; i<64; i++) {
    	if (inode_table[i].name != NULL && inode_table[i].parent_i_number != NULL) {
			if(strcmp(inode_table[i].name, name) == 0 && strcmp(inode_table[i].parent_i_number, parent) == 0) {
				*type = inode_table[i].type;

				return 0;
			}
    	}
    }

    return error(FILE_NOT_FOUND);
}

int get_i_number(char *name, char *parent, char *i_number) {
	for (int i=0; i<64; i++) {
		if (inode_table[i].name != NULL && inode_table[i].parent_i_number != NULL) {
			if(strcmp(inode_table[i].name, name) == 0 && strcmp(inode_table[i].parent_i_number, parent) == 0) {
				strcpy(i_number, inode_table[i].i_number);
				return 0;
			}
		}
	}
	return error(FILE_NOT_FOUND);
}

int dir_get_children(char *pathname, char *children) {

	char *current_i_num = calloc(2, sizeof(char));

	if(strcmp(pathname, "/") == 0) {
		current_i_num = "00";
	} else {

		char *tok = strtok(pathname, "/");
		char *parent_i_num = calloc(2, sizeof(char));

		int depth = 0;
		char *hierarchy[8];
		while(tok != NULL) {
			hierarchy[depth] = tok;

			depth++;
			tok = strtok(0, "/");
		}

		if (depth == 0) {
			current_i_num = "00";
		}

		for (int i=0; i<depth; i++) {
			if (i == 0) {
				parent_i_num = "00";
			} else {
				parent_i_num = calloc(2, sizeof(char));
				strcpy(parent_i_num, current_i_num);
			}
			get_i_number(hierarchy[i], parent_i_num, current_i_num);
		}
	}

	char *reg_files = calloc(512, sizeof(char));
	char *dir_files = calloc(512, sizeof(char));

	for (int i=1; i<64; i++) {
		if (inode_table[i].name != NULL && strlen(inode_table[i].parent_i_number) != 0) {
			if (strcmp(inode_table[i].parent_i_number, current_i_num) == 0) {
				// Found a child
				inode current_inode = inode_table[i];
				if(current_inode.type == 0) {
					if (strlen(reg_files) == 0) {
						sprintf(reg_files, "%s %s ", "Regular files:", current_inode.name);
					} else {
						char *temp = calloc(512, sizeof(char));
						sprintf(temp, "%s ", current_inode.name);
						strcat(reg_files, temp);
					}
				} else {
					if (strlen(dir_files) == 0) {
						sprintf(dir_files, "%s %s ", "Directory files:", current_inode.name);
					} else {
						char *temp = calloc(512, sizeof(char));
						sprintf(temp, "%s ", current_inode.name);
						strcat(dir_files, temp);
					}
				}
			}
		}
	}

	if (strlen(reg_files) != 0) {
		strcat(children, reg_files);
		strcat(children, "\n");
	}
	if (strlen(dir_files) != 0) {
		strcat(children, dir_files);
		strcat(children, "\n");
	}

	return 0;
}

