#ifndef SFS_WRITE_H_   /** Include guard */
#define SFS_WRITE_H_

/** @file sfs_write.h
 * Writes a literal string to a file
 * Writes a literal string to a file witha start location on the disk.
 */

/**
 *
 * @brief Writes the buffer to the file and save it to the disc
 * @details It checks the size before writing then writes and saves them to the disc while increasing the size if needed. Also in order to write the file need to be opened
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param fd File descriptor of the file in the open file table
 * @param start Start location to write at (-1) if the file is empty and/or to append to the end
 * @param length The length of the buffer to write (in bytes)
 * @param *mem_pointer The input the user provided to write to the file
 * @return 0 if succedd
 * @return -1 if failure
 *
 * @copyright GNU Public License.
 *
 */
int sfs_write(int fd, int start, int length, char *mem_pointer);


#endif

