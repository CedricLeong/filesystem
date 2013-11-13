#include "error.h"

int error(ERROR error) {
    switch(error) {
        case SUCCESSFULLY_CREATED_FILE:
            printf("%s\n", "File was created successfully\nReturn value: 0");
            return 0;
        case NO_FILE_NAME_ENTERED:
            printf("%s\n", "No name for the file was provided\nReturn value: -1");
            return -1;
        case FULL_FILE:
        	printf("%s\n", "The file has the maximum 8 block allocation and is full.\nReturn value: -1");
        	return -1;
        case PUT_BLOCK_FAIL:
        	printf("%s\n", "Error occurred when writing from memory to disk block.\nReturn value: -1");
        	return -1;
        case GET_BLOCK_FAIL:
        	printf("%s\n", "Error occurred when reading from disk to memory.\nReturn value: -1");
        	return -1;
        case BLK_ALLOCATED:
        	printf("%s\n", "A block has been successfully allocated to the file.\nReturn value: 0");
        	return -1;
        case FAIL_ALLOCATE:
        	printf("%s\n", "A block has been unsuccessfully allocated to the file.\nReturn value: -1");
        	return -1;
    }
}
