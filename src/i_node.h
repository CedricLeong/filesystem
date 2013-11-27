#ifndef I_NODE_H_   /* Include guard */
#define I_NODE_H_

#include <time.h>

#define MAX_NAME_LENGTH 5

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

extern short int fd_table[64];
extern int i_numbers[64];
extern inode inode_table[64];
extern int add_new_inode(inode *new_inode);
extern int alloc_block_tofile(inode *inode);


extern int put_inode_table(void);
extern int get_next_i_number(char *i_number);
extern int get_inode_table_from_disk(void);
extern int get_size(char *name);
extern int save_file_contents(char *contents, char *name);


#endif
