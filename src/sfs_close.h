#ifndef SFS_CLOSE_H_
#define SFS_CLOSE_H_

/** @file sfs_close.h
 * File function to close a file
 * Closes the file or its instance (if the file was opened multiple times)
 */

/**
 *
 * @brief File function to close files
 * @details This function will close a file (or its instance) in memory by its file descriptor
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param fd The file descriptor of the file to close
 *
 * @return 0 if success
 * @return -1 if failure
 *
 * @copyright GNU Public License.
 *
 */
extern int sfs_close(int fd);

#endif /** SFS_CLOSE_H_ */
