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
        	return 0;
        case FAIL_ALLOCATE:
        	printf("%s\n", "A block has been unsuccessfully allocated to the file.\nReturn value: -1");
        	return -1;
        case ERROR_WRITING_INODE_TO_DISK:
            printf("%s\n", "Writing inode to disk failed\nReturn value: -1");
            return -1;
        case FILE_OPENED_LIMIT_HAS_BEEN_REACHED:
            printf("%s\n", "Could not open the file since it has been opened 4 times already\nReturn value: -1");
            return -1;
        case FILE_NOT_FOUND_IN_OPEN_TABLE:
            printf("%s\n", "Specified file was not found in the open file table\nReturn value: -1");
            return -1;
        case FILE_NOT_FOUND:
            printf("%s\n", "Specified file was not found.\nReturn value: -1");
            return -1;
        case FILE_WITH_NAME_EXISTS:
            printf("%s\n", "File with the same name already exists.\nReturn value: -1");
            return -1;
        case FILE_IS_EMPTY:
            printf("%s\n", "The file is empty.\nReturn value: -1");
            return -1;
    }
}
