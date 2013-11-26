#include "i_node.h"
#include "blockio.h"
#include "error.h"
#include <math.h>
#include <stddef.h>
#include <string.h>

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
    strcpy(root.name, "/");
    root.i_number = "00";
    i_numbers[0] = 1;
    time_t currentTime  = time(NULL);
    root.time_created = asctime(localtime(&currentTime));
    root.time_last_accessed = root.time_created;
    root.time_last_modified = root.time_created;
    root.type = 1;
    root.file_size = "0";

    inode_table[0] = root;

    char *buf = calloc(128, sizeof(char));
    sprintf(buf, "%d_%s_%s_%d_%s_%s_%s_%s", 0,(char *) root.name, (char *) root.i_number, root.type, (char *) root.time_created, (char *) root.time_last_accessed, (char *) root.time_last_modified, root.file_size, (char *) root.index_blk_location);

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

    char *all_inode_info = calloc(128, sizeof(char));

    for(int i=0; i<64; i++) {
        char *buf = calloc(128, sizeof(char));
        inode current_inode = inode_table[i];
        if(strlen(current_inode.name) == 0) {
            continue;
        }

        sprintf(buf, "%d_%s_%s_%d_%s_%s_%s_%s_%d", i,(char *) current_inode.name, (char *) current_inode.i_number, current_inode.type, (char *) current_inode.time_created, (char *) current_inode.time_last_accessed, (char *) current_inode.time_last_modified, current_inode.file_size, current_inode.index_blk_location);
        strcat(all_inode_info, buf);
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

int get_inode_table_from_disk(void) {

    char *all_inode_info = calloc(8192, sizeof(char));

    char *buf;
    for (int i=0; i<inode_blocks; i++) {
        buf = calloc(128, sizeof(char));
        get_block(2+i, buf);

        strcat(all_inode_info, buf);
        }

    char *tok = strtok(buf, "_");

    int counter = 0;
    inode i_node;
    int inum;
    while (tok != NULL) {
        if (counter == 9) {
            counter = 0;
            inode_table[inum] = i_node;
        }
        switch(counter) {
            case 0:
                inum = atoi(tok);
                break;
            case 1:
                strcpy(i_node.name, tok);
                break;
            case 2:
                i_node.i_number = tok;
                break;
            case 3:
                i_node.type = atoi(tok);
                break;
            case 4:
                i_node.time_created = tok;
                break;
            case 5:
                i_node.time_last_accessed = tok;
                break;
            case 6:
                i_node.time_last_modified = tok;
                break;
            case 7:
                i_node.file_size = tok;
                break;
            case 8:
                i_node.index_blk_location = tok;
        }
        counter++;
        tok = strtok(0, "_");
    }
    return 0;
}

int alloc_block_tofile(inode *inode)
{
    int numblks;
    int freeblk;
    int indexblock;
    indexblock = atoi((*inode).i_number);
    char* buffer = calloc(128,sizeof(char));

    // This is where it reads the index block
    int success = get_block(indexblock,buffer);
           if (success == -1)
            return error(GET_BLOCK_FAIL);

    //Check if there are eight blocks already allocated to the file
    char* check;
    int filecount =0 ;
    check = strchr(buffer,'0');
    while (check!=NULL)
    {
    	check=strchr(check+1,'_');
    	filecount++;
    	if (filecount >= 8)
    		return error(FULL_FILE);
    }

    // add block
    get_empty_blk(&freeblk);
    char str[sizeof(freeblk)];
    sprintf(str, "%d", freeblk);
    strcat(buffer,str);
    strcat(buffer,"_");

    // write to index block if there is space
    success = put_block(indexblock,buffer);
    if (success == -1)
            return error(PUT_BLOCK_FAIL);
    return error(BLK_ALLOCATED);

    return (error(FAIL_ALLOCATE));
}

int alloc_file_todir(inode *inode)
{
    int numblks;
    int freeblk;
    int indexblock;
    indexblock = atoi((*inode).i_number);
    char* buffer = calloc(128,sizeof(char));

    // This is where it reads the index block
    int success = get_block(indexblock,buffer);
           if (success == -1)
            return error(GET_BLOCK_FAIL);

    //Check if there are eight blocks already allocated to the file
    char* check;
    int filecount =0 ;
    check = strchr(buffer,'0');
    while (check!=NULL)
    {
    	check=strchr(check+1,'_');
    	filecount++;
    	if (filecount >= 8)
    		return error(FULL_FILE);
    }

    // add block
    get_empty_blk(&freeblk);
    char str[sizeof(freeblk)];
    sprintf(str, "%d", freeblk);
    strcat(buffer,str);
    strcat(buffer,"_");

    // write to index block if there is space
    success = put_block(indexblock,buffer);
    if (success == -1)
            return error(PUT_BLOCK_FAIL);
    return error(BLK_ALLOCATED);

    return (error(FAIL_ALLOCATE));
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
}

int find_file(char *pathname) {
    char path[strlen(pathname) + 1];
    strcpy(path, pathname);
    char *tok = strtok(path, "/");

    if (tok == NULL)
        return error(INVALID_FILE_NAME);
    for (int i=0; i<64; i++) {
        if (strcmp(inode_table[i].name,tok) == 0) {
            // file exists
            return 0;
        }
    }

    // file was not found
return error(FILE_NOT_FOUND);
}

int get_file_contents(char *name, int start, int length, char *contents) {
    for (int i=0; i<64; i++) {
        if (strcmp(inode_table[i].name,name) == 0) {
            int index_block = inode_table[i].index_blk_location;
            char *blocks = calloc(128, sizeof(char));
            get_block(index_block, blocks);
            if (strlen(blocks) == 0) {
                return error(FILE_IS_EMPTY);
            } else {
                // Get each block
                char *tok = strtok(blocks, "_");

                int blk_counter = 0;
                while(tok != NULL && strcmp(tok, "0") != 0) {
                    int block_num = atoi(tok);

                    char *buf = calloc(128, sizeof(char));
                    get_block(block_num, buf);

                    if (blk_counter==0) {
                        strncpy(contents, buf+start, length);
                    } else {
                        strcat(contents, buf);
                    }
                    tok = strtok(0, "_");
                    blk_counter++;
                }
                return 0;
            }

        }
    }

    // File was not found in the inode tabel
    return error(FILE_NOT_FOUND);
}

int save_file_contents(char *contents, char *name, int start, int length) {


    for (int i=0; i<64; i++) {
        if(strcmp(inode_table[i].name,name) == 0) {
           int index_block = inode_table[i].index_blk_location;
            char *blocks = calloc(128, sizeof(char));
            get_block(index_block, blocks);
            int parts = ceil((double) length/(double)128);
            char *tok = strtok(blocks, "_");
            int lengths[parts];
            if (parts > 1) {
                for (int l=0; l<parts; l++) {
                    if(i<length-1) {
                        lengths[l] = 128;
                    } else {
                        lengths[l] = length-i*128;
                    }
                }
            } else {
                lengths[parts] = length;
            }


            for (int j=0; j<parts; j++) {
                int blk_num;
                if (tok == NULL || strlen(tok) == 0) {
                    get_empty_blk(&blk_num);
                } else {
                    blk_num = atoi(tok);
                }

                char *part = calloc(lengths[j], sizeof(char));
                strncpy(part, contents+j*128, length);

                // TODO: add -1 start

                if(put_block(blk_num, part) == 0) {
                    change_size(name, strlen(part));
                    int index_blk[8] = {0};
                    index_blk[0] = blk_num;
                    char *char_index_blk = calloc(128, sizeof(char));
                    for (int k=0; k<8; k++) {
                        char *buf = calloc(10, sizeof(char));
                        if (k==0) {
                            sprintf(buf, "%d", index_blk[k]);
                        } else {
                            sprintf(buf, "_%d", index_blk[k]);
                        }

                        strcat(char_index_blk, buf);
                    }

                    put_block(index_block, char_index_blk);

                    printf("%s %d %s\n", "Data to block", blk_num, "has been written.");
                }

                tok = strtok(0, "_");
            }
        }
    }
}

int change_size(char *name, int bytes) {
    for (int i=0; i<64; i++) {
        if(strcmp(inode_table[i].name, name) == 0) {
            inode_table[i].file_size = calloc(3, sizeof(char));
            sprintf(inode_table[i].file_size, "%d", bytes);
            return 0;
        }
    }

    return error(FILE_NOT_FOUND);
}

int get_size(char *name) {
    for (int i=0; i<64; i++) {
        if(strcmp(inode_table[i].name, name) == 0) {
            printf("%s %s", "The file size is:", inode_table[i].file_size);
            return 0;
        }
    }

    return error(FILE_NOT_FOUND);
}

int get_type(char *name, int* type) {
    for (int i=0; i<64; i++) {
        if(strcmp(inode_table[i].name, name) == 0) {
            *type = inode_table[i].type;

            return 0;
        }
    }

    return error(FILE_NOT_FOUND);
}


