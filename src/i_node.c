#include i_node.h
#include blockio.h

short int file_blockno[8][64];
short int file_pointer[64]; 
short int file_refcount[64];
short int fd_table[64];

int put_inode_table():
{
	int blockno = 0;
	int j = 2;
    // Block Number
	while (j < 10)
	{
		int *buf;
    	int = calloc(64, sizeof(int));
		// Byte numbers
        for(int i=0; i < 64; i++) 
        {
        	buf[i] = blockno;
        	blockno++;

        }
        int writeintable = put_block(j, buf);
    }
    return 1;
}

int get_file_pointer(int i_number,int* file_ptr)
{
	file_ptr = blockno[2][i_number];
	return 1; 
}

int parse_dir_entry(int component_no, char 
*component, int *i_number)
{

}

int alloc_block_tofile(int i_number, int 
*allocated_blkno)
{
	int *buf;
    buf = calloc(128, sizeof(int));
    int load = get_block( i_number +2, buf);
    int numblks = get_file_pointer(i_number);
    if (numblks > 8)
    	return 0;
    allocated_blockno = get_super_blk();
    int load = get_block( 10, buf);
    // add 1 to the entry in block 10; 
    return 1; 
}
