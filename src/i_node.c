#include i_node.h
#include blockio.h
#include <math.h>

// Global data that should be visible to inode and super block
short int file_blockno[8][64];
short int file_pointer[64]; 
short int file_refcount[64];
short int fd_table[64];
char pathname_parse[6][64];

/* Creates the index numbers in memory then in the disk itself
Each file gets around 16 bytes so each block can hold 8 inodes*/
int put_inode_table():
{
	for (int a = 1; a < 65; a++)
	{
		file_blockno[0][a-1] = a;
	}
	int inum =1; 
	int blockno = 0;
	int j = 2;
    // Block Number
	while (j < 10)
	{
		int *buf;
    	buf = calloc(64, sizeof(int));
		// Byte numbers
        for(int i=1; i < 129; i++) 
        {
        	if ((i % 8) == 0)
        	{
        		buf[i-1]= inum;
        		inum++;
        	}
        	else
        		buf[i-1]= 0;

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
int alloc_block_tofile(int i_number, int *allocated_blkno)
{
    int numblks = get_file_pointer(i_number);
    if (&numblks > 8)
    	return 0;
    allocated_blockno = get_super_blk();
    file_blockno[1][i_number-1]++; 
    return 1; 
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
