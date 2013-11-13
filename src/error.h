#ifndef ERROR_H_   /* Include guard */
#define ERROR_H_

typedef enum {
    SUCCESSFULLY_CREATED_FILE,
    NO_FILE_NAME_ENTERED,
    FULL_FILE,
    PUT_BLOCK_FAIL,
    BLK_ALLOCATED,
    FAIL_ALLOCATE,
    GET_BLOCK_FAIL
} ERROR;
#endif
