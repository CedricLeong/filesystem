#ifndef I_NODE_H_   /* Include guard */
#define I_NODE_H_

#include <time.h>

#define MAX_NAME_LENGTH 5

extern short int file_blockno[8][64];
extern short int file_pointer[64];
extern short int file_refcount[64];
extern short int fd_table[64];
extern char pathname_parse[7][64];
extern int i_numbers[64];
extern int inode_blocks;


extern int put_inode_table(void);
extern int get_file_pointer(int i_number);
extern int alloc_block_tofile(int i_number, int *allocated_blkno);
extern int parse_pathname(char *path,int i_number);
extern int put_file(int i_number, int file_ptr, int type);
extern int get_file(int i_number, int *type, char* buffer);
extern int get_next_i_number(char *i_number);
extern int add_new_inode(inode *new_inode);
extern int get_inode_table_from_disk(void);

typedef struct {
    char name[MAX_NAME_LENGTH];
    char *i_number;
    int type;
    char *time_created;
    char *time_last_accessed;
    char *time_last_modified;
    char *file_size;
    int index_blk_location;
} inode;

extern inode inode_table[64];

#endif
