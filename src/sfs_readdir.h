#ifndef SFS_READDIR_H_
#define SFS_READDIR_H_

/** @file sfs_readdir.h
 * Reads the contents of a file DIRECTORY type and outputs the result
 * Reads the names of the children of a DIRECTORY type file and outputs the children REGULAR and DIRECTORY type files
 */

/**
 *
 * @brief Reads and returns a directory's children
 * @details Looks up the file in the open_file_table by its fd, checks the file type. If it's a folder - outputs the file names of the files that have this directory as a parent.
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param fd File descriptor of the folder to read the contents of.
 * @return 0 or -1 (success or failure) of the operation
 *
 * @copyright GNU Public License.
 *
 */
extern int sfs_readdir(int fd);


#endif /** SFS_READDIR_H_ */
