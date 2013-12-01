#ifndef SFS_GETTYPE_H
#define SFS_GETTYPE_H

/** @file sfs_gettype.h
 * Looks up the file and returns its type
 * Gets the type of the file from the inode_table and returns 0 (REGULAR) or 1 (DIRECTORY).
 */

/**
 *
 * @brief: File function to check the type of the file
 * @details: Iterates over the pathname making sure the path is existent. Then gets the type of the file and returns it
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param *pathname The pathname of the file to get the type of
 * @return 1 if directory
 * @return 0 if regular file
 * @return -1 if failed to get the type
 *
 * @copyright GNU Public License.
 *
 */
extern int sfs_gettype(char *pathname);

#endif // SFS_GETTYPE_H
