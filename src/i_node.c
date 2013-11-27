#include "i_node.h"
#include "blockio.h"
#include "error.h"
#include "super_block.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    int *free_blk_no = calloc(3, sizeof(int));
    get_empty_blk(&free_blk_no);
    root.index_blk_location = free_blk_no;
    inode_table[0] = root;

    char *buf = calloc(128, sizeof(char));
    sprintf(buf, "%d_%s_%s_%d_%s_%s_%s_%s_%d", 0,(char *) root.name, (char *) root.i_number, root.type, (char *) root.time_created, (char *) root.time_last_accessed, (char *) root.time_last_modified, root.file_size, root.index_blk_location);
    strcat(buf, "_");
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
            break;
        }

        sprintf(buf, "%d_%s_%s_%d_%s_%s_%s_%s_%d", i,(char *) current_inode.name, (char *) current_inode.i_number, current_inode.type, (char *) current_inode.time_created, (char *) current_inode.time_last_accessed, (char *) current_inode.time_last_modified, current_inode.file_size, current_inode.index_blk_location);
        strcat(buf, "_");
        if(i == 0){
        strcpy(all_inode_info, buf);}
        else{
        strcat(all_inode_info, buf);}
    }
    // Check how many blocks we need
    if (strlen(all_inode_info) > 128) {
        char *buf;
        buf = calloc (128, sizeof(char));
        int parts = (strlen(all_inode_info)+128-1)/128;
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

int delete_inode(char* pathname) {

        char* pch;
        char* pch2;
        char* idxblk = "_";
        char holder[3];

char* inum;
char *iname = strtok(pathname, "/");
int i;
char* buf;
// Find which block the inode is in
 for (i=0; i<9; i++) {
    buf = calloc(128, sizeof(char));
    get_block(2+i, buf);

    char *tok = strtok(buf, "_");

    int counter = 0;
    inode i_node;
    while (tok != NULL) {
        inode_table[0] = i_node;
        if (counter == 9) {
            counter = 0;
            inode_table[atoi(inum)] = i_node;
        }
        switch(counter) {
            case 0:
                inum = tok;
                break;
            case 1:
                strcpy(i_node.name, tok);
                if (strcmp(i_node.name,iname) == 0){
                    goto found;}
                break;
            case 2:
                i_node.i_number = tok;
                i_numbers[atoi(i_node.i_number)]=1;
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
                i_node.index_blk_location = atoi(tok);
                break;
            }
        counter++;
        tok = strtok(0, "_");
        }
    }

    // clear the section in the disk
    found:
        sprintf(holder,"%d",inode_table[i].index_blk_location);

        // add the info in the middle
        strcat(idxblk, holder);
        strcat(idxblk, "_");
        strcat(inum, "_");

        // get the disk information
        buf = calloc(128, sizeof(char));
        get_block(2+i, buf);
        char* placebuf = calloc(128, sizeof(char));

        // Find the index of the inum and the index block
        pch = strstr (buf,inum);
        pch2 = strstr (buf,idxblk);

        // erase the inode
        char *buf_left = calloc(128, sizeof(char));
        char *buf_right = calloc(128, sizeof(char));

        strncpy(buf_left, buf, (int)pch);
        strcpy(buf_right, buf + (int)pch + (ptrdiff_t)(pch2-pch));
        strcat(buf_left, buf_right);
        put_block(2+i,buf_left);
    return 0;
}

int get_inode_table_from_disk(void) {

    int counter = 0;
    int inum = 0;
    char* buf;
    for (int i=0; i<9; i++) {
    buf = calloc(128, sizeof(char));
    get_block(2+i, buf);



    char *tok = strtok(buf, "_");
    inode i_node;
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
                i_numbers[atoi(i_node.i_number)]=1;
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
                i_node.index_blk_location = atoi(tok);
                break;
        }
        counter++;
        tok = strtok(NULL, "_");
    }
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
    check = strchr(buffer,'_');
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

    char* tok;
    if(strcmp(pathname,"/") == 0 && strlen(pathname) == 1){
        tok = pathname;}
    else {
    char path[strlen(pathname) + 1];
    strcpy(path, pathname);
    tok = strtok(path, "/");
    if (tok == NULL)
        return error(INVALID_FILE_NAME);}
    for (int i=0; i<64; i++) {
        if (strcmp(inode_table[i].name,tok) == 0) {
            // file exists
            return 0;
        }
    }

    // file was not found
return error(FILE_NOT_FOUND);
}
int get_file_contents(char *name, char *contents) {
    for (int i=0; i<64; i++) {
        if (strcmp(inode_table[i].name,name) == 0) {
            int index_block = inode_table[i].index_blk_location;
            char *blocks = calloc(128, sizeof(char));
            get_block(index_block, blocks);
            if (strlen(blocks) == 0) {
                return -1;
            } else {
                // Get each block
                char *tok = strtok(blocks, "_");

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


int save_file_contents(char *contents, char *name) {

    char *length = calloc(4, sizeof(char));
    sprintf(length, "%d", strlen(contents));


    for (int i=0; i<64; i++) {
        if(strcmp(inode_table[i].name,name) == 0) {
           int index_block = inode_table[i].index_blk_location;
            char *blocks = calloc(128, sizeof(char));
            get_block(index_block, blocks);
            int parts = ceil((double) strlen(contents)/(double)128);
            char *tok = strtok(blocks, "_");

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
                    //change_size(name, strlen(part));

                    index_blk[j] = blk_num;
                    printf("%s %d %s\n", "Data to block", blk_num, "has been written.");

                }

                tok = strtok(0, "_");
            }

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
            return 0;
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


