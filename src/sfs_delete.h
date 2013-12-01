#ifndef SFS_DELETE_H_INCLUDED
#define SFS_DELETE_H_INCLUDED

/** @file sfs_delete.h
 * File function to delete a file from disk
 * Finds and deletes the file specified along with its contents and the inode.
 */

/**
 *
 * @brief Deletes the file from the disk
 * @details Makes sure the file is not opened and does not contain any children, then deletes its inode and frees up the blocks
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param  *pathname Pointer pathname char type
 * @return 0 if successful
 * @return -1 if failure
 *
 * @copyright GNU Public License.
 *
 */
extern int sfs_delete(char *pathname);

#endif // SFS_DELETE_H_INCLUDED
