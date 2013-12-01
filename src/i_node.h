#ifndef I_NODE_H_   /** Include guard */
#define I_NODE_H_

/** @file i_node.h
 * Connects the lower level functions with the higher level and deal with the inode table
 * Contains most of the file functions regarding deleting, changing file information, writing, etc.
 */

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


/**
 *
 * @brief: Adds an inode to the inode_table and writes it to disk.
 * @details: Inserts provided inode into the inode_table array and then rewrites the information back to the disk.
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param  *new_inode Reference to the inode to add into the table
 * @return 0 indicating successful operation
 *
 * @copyright GNU Public License.
 *
 */
extern int add_new_inode(inode *new_inode);


/**
 *
 * @brief Creates the initial inode_table and writes it to disk
 * @details Initiates the root inode and writes it to disk separating every parameter with a ":" delimiter and "_" indicating end of the inode
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 *
 * @copyright GNU Public License.
 *
 */
extern int put_inode_table(void);


/**
 *
 * @brief Gets the smallest available i_number.
 * @details Gets the smallest available i_number and marks is taken (1), and saves the value to the provided parameter making sure it has two digits.
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param *i_number Pointer to char to save the i_number to
 * @return 0 success
 * @return -1 failure
 *
 * @copyright GNU Public License.
 *
 */
extern int get_next_i_number(char *i_number);


/**
 *
 * @brief Gets the inode table from the disk.
 * @details Reads inode table from the disk and loads it into memory by creating new inode structs and putting them into the inode_table array
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @return 0 indicating success
 *
 * @copyright GNU Public License.
 *
 */
extern int get_inode_table_from_disk(void);


/**
 *
 * @brief Saves the file contents to disk
 * @details Saves the contents of the file by dynamically allocating new blocks on the disk if needed. Writes the contents to the disk and then write the index block table containing the blocks used up.
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param *contents Contents of the file to save to disk
 * @param *name Name of the file to save
 * @param *parent File's parent's i_number
 *
 * @return 0 indicating successful operation
 *
 * @copyright GNU Public License.
 *
 */
extern int save_file_contents(char *contents, char *name, char *parent);



/**
 *
 * @brief Retrieves the file contents from the disk
 * @details This function gets the name of the file, parent's i_number, and pointer to contents to save the contents of the file to.
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param  *name Name of the file to get the contents of
 * @param  *parent The file's parent's i_number
 * @param  *contents Contents of the file to save to
 * @return  0 if successful
 * @return -1 if error occurs
 *
 * @copyright GNU Public License.
 *
 */
extern int get_file_contents(char *name, char *parent, char *contents);


/**
 *
 * @brief Gets the size of the file
 * @details Iterates through the path to get the size of the target file
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param  *pathname Pointer to the pathname of the file to get the size of
 *
 * @return The file size
 * @return -1 indicating failure
 *
 * @copyright GNU Public License.
 *
 */
extern int get_size(char *pathname);


/**
 *
 * @brief Returns the i_number of the file
 * @details Finds the correct file by using the name provided and the parent's i_number and returns the file's i_number
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param *name Pointer to the name of the file to get the i_number of
 * @param *parent File's parent's i_number
 * @param *i_number The reference to the file's i_number to save the information to
 *
 * @return 0 indicating success
 * @return -1 indicating failure
 *
 * @copyright GNU Public License.
 *
 */
extern int get_i_number(char *name, char *parent, char *i_number);


/**
 *
 * @brief Return true or false (0 or -1) of whether the file is found
 * @details Finds the correct file by using the name provided and the parent's i_number and returns success flag if the operation is successful
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param *name Pointer to the name of the file to get the i_number of
 * @param *parent File's parent's i_number
 *
 * @return 0 indicating success
 * @return -1 indicating failure
 *
 * @copyright GNU Public License.
 *
 */
extern int find_file(char *name, char *parent);


/**
 *
 * @brief Finds the appropriate file and saves its type to the pointer provided
 * @details Finds the correct file by using the name provided and the parent's i_number and saves the file's type to the provided pointer type
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param *name Pointer to the name of the file to get the i_number of
 * @param *parent File's parent's i_number
 * @param *type The reference to the file's type to save the information to
 *
 * @return 0 indicating success
 * @return -1 indicating failure
 *
 * @copyright GNU Public License.
 *
 */
extern int get_type(char *name, char *parent, int* type);


/**
 *
 * @brief Reads the inode_table and returns a directory's children.
 * @details Looks up the file in the open_file_table by its fd, checks the file type. If it's a folder - outputs the file names of the files that have this directory as a parent.
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
 */
extern int dir_get_children(char *pathname, char *children);


/**
 *
 * @brief Saves the inode_table from memory into the disk
 * @details Converts the inode table into a string literal and stores it on to the disk blocks 2-10
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @return 0 to indicate the operation is over.
 *
 * @copyright GNU Public License.
 *
 */
int save_inode_table(void);



/**
 *
 * @brief Removes the inode with the specified i_number from the inode_table
 * @details Removes the appropriate inode from the inode_table and re-writes the disk
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @return 0 to indicate the operation is over.
 *
 * @copyright GNU Public License.
 *
 */
extern int delete_inode(int i_num);

#endif
