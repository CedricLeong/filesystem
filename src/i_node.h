#ifndef I_NODE_H_   /* Include guard */
#define I_NODE_H_

typedef struct {
    char *name;
    char *i_number;
    int type;
    char *parent_i_number;
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
extern int get_i_number(char *name, char *i_number);


#endif
