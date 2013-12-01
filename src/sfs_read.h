#ifndef SFS_READ_H_   /** Include guard */
#define SFS_READ_H_

/** @file sfs_read.h
 * Reads the contents of the file if its open and outputs it
 * Checks if the file is open, then reads the contents of it off the disk and outputs it
 */

/**
 *
 * @brief: Reads the contents of the file from the disk and outputs it
 * @details: Reads the file blocks at the given start position and an appropriate length and saves the result to buffer
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param fd File descriptor of the file in the open file table
 * @param start Start location to read at in bytes
 * @param length The length of the buffer to read (in bytes)
 * @param *buffe The pointer to where the content of the file will be saved to
 * @return 0 if succedd
 * @return -1 if failure
 *
 * @copyright GNU Public License.
 *
 */
extern int sfs_read(int fd,int start, int length, char* buffer);


#endif
