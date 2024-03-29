#ifndef ERROR_H_   /* Include guard */
#define ERROR_H_

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
    WRITING_BEYOND_FILE_SIZE
} ERROR;

extern int error(ERROR error);
#endif
