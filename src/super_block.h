#ifndef SUPER_BLOCK_H_   /* Include guard */
#define SUPER_BLOCK_H_

typedef struct {
	int size;
	int blocksize;
	int free_blocks; 
	int root;
} super_block;


extern short int disk_bitmap[512];
extern short int super_blk_buf[128];
extern int put_super_blk(void);
extern int get_super_blk(void);

#endif