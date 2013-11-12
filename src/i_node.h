#ifndef I_NODE_H_   /* Include guard */
#define I_NODE_H_

#include <time.h>

#define MAX_NAME_LENGTH 5

extern short int file_blockno[8][64];
extern short int file_pointer[64];
extern short int file_refcount[64];
extern short int fd_table[64];
extern char pathname_parse[7][64];


extern int put_inode_table();
extern int get_file_pointer(int i_number,int* file_ptr);
extern int alloc_block_tofile(int i_number, int *allocated_blkno);
extern int parse_pathname(char *path,int i_number);
extern int put_file(int i_number, int file_ptr, int type);
extern int get_file(int i_number, int *type, char* buffer);
extern int get_next_i_number(char *i_number);

typedef struct {
    char name[MAX_NAME_LENGTH];
    char *i_number;
    time_t *time_created;
    time_t *time_last_accessed;
    time_t *time_last_modified;
    double file_size;
    int index_blk_location;
} inode;


#endif
