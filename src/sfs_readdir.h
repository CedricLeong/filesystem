/*
 * sfs_readdir.h
 *
 *  Created on: Nov 28, 2013
 *      Author: yasha
 */

#ifndef SFS_READDIR_H_
#define SFS_READDIR_H_

/***************************************************************************
 *
 * @brief: Reads and returns a directory's children
 * @details: Looks up the file in the open_file_table by its fd, checks the file type. If it's a folder - outputs the file names of the files that have this directory as a parent.
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
 ***************************************************************************/
extern int sfs_readdir(int fd);


#endif /* SFS_READDIR_H_ */
