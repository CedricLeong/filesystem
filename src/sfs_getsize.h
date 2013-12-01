#ifndef SFS_GET_SIZE_H_   /** Include guard */
#define SFS_GET_SIZE_H_

/** @file sfs_getsize.h
 * Returns the size of the file
 * Looks up the file by goind down the hierarchy and gets its size from the inode_table
 */

/**
 *
 * @brief: Gets the size of the file
 * @details: Iterates through the pathname making sure each level exists, then finds the target file and returns its size.
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param  *pathname Pointer pathname char type
 * @return Size of the file
 *
 * @copyright GNU Public License.
 *
 */
extern int sfs_getsize(char *pathname);

#endif
