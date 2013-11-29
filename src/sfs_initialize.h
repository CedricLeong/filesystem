#ifndef SFS_INITIALIZE_H_   /* Include guard */
#define SFS_INITIALIZE_H_

/***************************************************************************
 *
 * @brief: Initialize the free block list.
 * @details: It creates a new file system, then creates a new super block with size 512 and initialize this free blocks list.
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param erase Flag indicator to erase (1) or not (0)
 * @return 1 if successful and -1 if failure
 *
 * @copyright GNU Public License.
 *
 ***************************************************************************/
extern int sfs_initialize(int erase);

/***************************************************************************
 *
 * @brief: Create a null block of data
 * @details: Allocates 0's to the disk in order to override it
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @return 1 if successful and -1 if failure
 *
 * @copyright GNU Public License.
 *
 ***************************************************************************/
int new_filesystem(void);

#endif
