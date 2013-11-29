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
extern int get_file_contents(char *name, char *parent, char *contents);
extern int get_size(char *name);
extern int save_file_contents(char *contents, char *name, char *parent);
extern int get_i_number(char *name, char *parent, char *i_number);
extern int find_file(char *pathname, char *parent);
extern int get_type(char *name, char *parent, int* type);


/***************************************************************************
 *
 * @brief: Reads the inode_table and returns a directory's children.
 * @details: Looks up the file in the open_file_table by its fd, checks the file type. If it's a folder - outputs the file names of the files that have this directory as a parent.
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param pathname Pathname of the dir file to read
 * @param children List of children to be returned
 * @return 0 to indicate the operation is over.
 *
 * @copyright GNU Public License.
 *
 ***************************************************************************/
extern int dir_get_children(char *pathname, char *children);


/***************************************************************************
 *
 * @brief: Saves the inode_table from memory into the disk
 * @details: Converts the inode table into a string literal and stores it on to the disk blocks 2-10
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @return 0 to indicate the operation is over.
 *
 * @copyright GNU Public License.
 *
 ***************************************************************************/
int save_inode_table(void);



/***************************************************************************
 *
 * @brief: Removes the inode with the specified i_number from the inode_table
 * @details: Removes the appropriate inode from the inode_table and re-writes the disk
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @return 0 to indicate the operation is over.
 *
 * @copyright GNU Public License.
 *
 ***************************************************************************/
extern int delete_inode(int i_num);

#endif
