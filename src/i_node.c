#include "i_node.h"
#include "blockio.h"
#include "error.h"
#include <math.h>
#include <stddef.h>

// Global data that should be visible to inode and super block
short int file_blockno[21][64];
short int file_pointer[64];
short int file_refcount[64];
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
        char *buf = calloc(400, sizeof(char));
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
        double parts = ceil((double) strlen(all_inode_info)/(double)128);
        inode_blocks = parts;
        for (int i=0; i<parts; i++) {
            strncpy(buf, all_inode_info+i*128, 128);
            put_block(2+i, buf);
            set_disk_bitmap_busy(2+i);
        }

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
        printf("%s\n", tok);
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
}

/* Retrieves the file pointer from memory, it will be changed to disk soon*/
int get_file_pointer(int i_number,int* file_ptr)
{
	file_ptr = file_blockno[2][i_number];
	return 1;
}

/* Allocates the block by retrieving the file pointer from memory
Then looking at the value of the pointer it sees how many blocks
the file has. If it can it will assign a new block to the file*/
int alloc_block_tofile(inode inode)
{
	int numblks;
	int freeblk;
    int indexblock;
    indexblock = inode.index_blk_location;
    char* buffer = calloc(128,sizeof(char));
    printf("%s\n", buffer);
    // This is where it reads the index block
    int success = get_block(indexblock,buffer);
   	if (success == -1)
    	return error(GET_BLOCK_FAIL);
    printf("%s\n", buffer);

    char* pch;
    pch = strchr(buffer,'0');
    // Find a 0 indicating there is free space
    if (pch != NULL)
    {    	char c[2];

    	success = get_empty_blk(&freeblk);
    	sprintf(c, "%d", freeblk);
    	ptrdiff_t idx = pch - buffer;
    	char temp[128];
    	//printf("%s\n",c);
    	strncpy(temp, buffer, idx);

    	printf("%s\n","works!");
    	strcat(temp,"_");
    	strcat(temp,c);
    	while (strlen(temp)!= 128)
    	{
    		strcat(temp,"0");
    	}
		printf("%s\n",temp);
        success = put_block(indexblock,temp);
        if (success == -1)
        	return error(PUT_BLOCK_FAIL);
        return error(BLK_ALLOCATED);
    }
    return error(FAIL_ALLOCATE);
}


/* Saves the path name in an array so it can be used for comparison later.*/
int parse_pathname(char *path,int i_number)
{
	for (int i =0; i < 5; i++)
	{
		pathname_parse[i][i_number] = path[i];
	}
	//ERROR: pathname_parse[5] = '\0';

}


int put_file(int i_number, int file_ptr, int type)
{
	//ERROR: int works = put_block(i, buffer);

}

int get_file(int i_number, int *type, char* buffer)
{
	char* tempbuffer;
	int blk = 0;
	for (int i = 0; i < 7; i ++)
	{
		blk = file_blockno[i][i_number];
		if (blk > 0)
		{
			tempbuffer = (buffer + (i*128));
			int works = get_block(blk, tempbuffer);
			if (works == 0)
				return 1;
		}
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
}
