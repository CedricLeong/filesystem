#ifndef ERROR_H_   /* Include guard */
#define ERROR_H_

/** @file error.h
 * Error management tool
 * Responds with an error output to predefined error codes.
 */

typedef enum {
    SUCCESSFULLY_CREATED_FILE,
    NO_FILE_NAME_ENTERED,
    FULL_FILE,
    PUT_BLOCK_FAIL,
    BLK_ALLOCATED,
    FAIL_ALLOCATE,
    GET_BLOCK_FAIL,
    ERROR_WRITING_INODE_TO_DISK,
    FILE_OPENED_LIMIT_HAS_BEEN_REACHED,
    FILE_NOT_FOUND_IN_OPEN_TABLE,
    FILE_NOT_FOUND,
    FILE_WITH_NAME_EXISTS,
    FILE_IS_EMPTY,
    INVALID_FILE_NAME,
    FOUND_TYPE,
    WRITING_TO_DIR,
    READING_FROM_DIR,
    READING_BEYOND_FILE_SIZE,
    WRITING_BEYOND_FILE_SIZE,
    PATHNAME_ERROR,
    FILE_NAME_TOO_LONG,
    WRITE_TOO_MANY_CHARS,
    READDIR_REG_FILE,
    ERROR_PARENT_REG_FILE,
    ERROR_DIR_SIZE,
    ERROR_DELETE_FILE_IS_OPEN,
    ERROR_DELETE_DIR_HAS_CHILDREN,
    READDIR_FILE_NOT_OPEN
} ERROR;


/**
 *
 * @brief Basic error handling system that outputs an appropriate error by request
 * @details This function will output an appropriate error according to the ERROR code provided
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param error The error code to handle
 * @return -1 if it's an error
 * @return 0 if it's success
 *
 * @copyright GNU Public License.
 *
 */
extern int error(ERROR error);
#endif
