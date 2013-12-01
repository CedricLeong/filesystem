#ifndef SFS_OPEN_H_   /** Include guard */
#define SFS_OPEN_H_

/** @file sfs_open.h
 * File function to open a file and load its file descriptor into memory
 * Finds and and opens the file by assigning a file descriptor in the open-file table.
 */


/**
 *
 * @brief File function to open files
 * @details This function will open a new file by iterating through the path using tokens making sure each level of hierarchy exists
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param *pathname The absolute pathname of the file to be opened
 * @return fd of the file opened
 *
 * @copyright GNU Public License.
 *
 */
extern int sfs_open(char *pathname);


#endif
