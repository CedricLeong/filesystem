#ifndef I_NODE_H_   /* Include guard */
#define I_NODE_H_

extern short int file_blockno[8][64];
extern short int file_pointer[64]; 
extern short int file_refcount[64];
extern short int fd_table[64];
extern char pathname_parse[6][64];


extern int put_inode_table();
extern int get_file_pointer(int i_number,int* file_ptr);
extern int alloc_block_tofile(int i_number, int *allocated_blkno);
extern int parse_pathname(char *path,int i_number);


#endif
