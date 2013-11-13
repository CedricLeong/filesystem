#ifndef OPEN_FILE_TABLE_H_   /* Include guard */
#define OPEN_FILE_TABLE_H_


typedef struct {

    char *pathname;
    int opened;
    int fd;

} openfile;

extern openfile all_opened_files[64];
extern int all_fd[64];

/***************************************************************************
 *
 * @brief Adds a file to the open-file table
 * @details This function will add a new file specified by its pathname to the open-file table
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param *pathname The absolute pathname of the file to add
 * @return The fd of the file added
 *
 * @copyright GNU Public License.
 *
 ***************************************************************************/
extern int add_opened_file(char *pathname);

/***************************************************************************
 *
 * @brief Removes a file from the open-file table
 * @details This function will remove the file specified by its fd from the open-file table
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param fd The fd of the file to close
 * @return 0 for success -1 for failure
 *
 * @copyright GNU Public License.
 *
 ***************************************************************************/
extern int close_file(int fd);



/***************************************************************************
 *
 * @brief Returns opened file's pathname
 * @details This function will return the file's pathname
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param fd The fd of the file to search for
 * @param pathname The char pointer where the files pathname will be saved to
 * @return 0 for success -1 for failure
 *
 * @copyright GNU Public License.
 *
 ***************************************************************************/
int get_opened_file(int fd, int *pathname);



#endif
