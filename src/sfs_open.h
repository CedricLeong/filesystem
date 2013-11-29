#ifndef SFS_OPEN_H_   /* Include guard */
#define SFS_OPEN_H_


/***************************************************************************
 *
 * @brief File function to open files
 * @details This function will open a new file
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param *pathname The absolute pathname of the file to be opened
 * @return Returns fd of the file opened
 *
 * @copyright GNU Public License.
 *
 ***************************************************************************/
extern int sfs_open(char *pathname);


#endif
