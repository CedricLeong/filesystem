#ifndef SFS_CREATE_H_   /* Include guard */
#define SFS_CREATE_H_


/***************************************************************************
 *
 * @brief File function to create files
 * @details This function will create a new file along with its inode
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param *pathname The absolute pathname of the file to be created
 * @param type The type of the file to be created (0=regular file, 1=folder)
 *
 * @copyright GNU Public License.
 *
 ***************************************************************************/
extern int sfs_create(char *pathname, int type);


#endif
