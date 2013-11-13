#include i_node.h
#include blockio.h
#include <math.h>

// Global data that should be visible to inode and super block
short int file_blockno[21][64];
short int file_pointer[64]; 
short int file_refcount[64];
short int fd_table[64];
short int index_block[8][64]; 
char pathname_parse[7][64];
/* Creates the index numbers in memory then in the disk itself
Each file gets around 16 bytes so each block can hold 8 inodes*/
int put_inode_table()
{

	int x,y=0; 
	int j = 2;
    // Block Number
	while (j < 10)
	{
		char* buf;
    	buf = calloc(128, sizeof(char));
   		// Byte numbers
        for(int i=1; i < 129; i++) 
        {
        	if (x == 21)
        	{
        		y++;
        		x=0;
        		if (y == 64)
        			return 1;
        	}
        	buff[i-1] = file_blockno[x][y];
        	x++;
        }
        int writeintable = put_block(j, buf);
    }
    return 1;
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
    indexblock = inode->index_blk_location;
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
	pathname_parse[5] = '\0';

}


int put_file(int i_number, int file_ptr, int type)
{
	// 
	int works = put_block(i, buffer);

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
