#ifndef I_NODE_H_   /* Include guard */
#define I_NODE_H_

typedef struct {
	int* file_location;
	int date;
	int file_size;
	int index_block;
	char* name; 
} inode;

extern inode* new_inode();

extern inode* get_inode(int location);

extern int get_size(int location);

extern boolean file_exist(int location);

#endif