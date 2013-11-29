#include "error.h"

int error(ERROR error) {
    switch(error) {
        case SUCCESSFULLY_CREATED_FILE:
            printf("%s\n", "File was created successfully");
            return 0;
        case NO_FILE_NAME_ENTERED:
            printf("%s\n", "Error: No name for the file was provided");
            return -1;
        case FULL_FILE:
        	printf("%s\n", "Error: The file has the maximum 8 block allocation and is full.");
        	return -1;
        case PUT_BLOCK_FAIL:
        	printf("%s\n", "Error: Error occurred when writing from memory to disk block.");
        	return -1;
        case GET_BLOCK_FAIL:
        	printf("%s\n", "Error: Error occurred when reading from disk to memory.");
        	return -1;
        case BLK_ALLOCATED:
        	printf("%s\n", "A block has been successfully allocated to the file.");
        	return 0;
        case FAIL_ALLOCATE:
        	printf("%s\n", "Error: A block has been unsuccessfully allocated to the file.");
        	return -1;
        case ERROR_WRITING_INODE_TO_DISK:
            printf("%s\n", "Error: Writing inode to disk failed");
            return -1;
        case FILE_OPENED_LIMIT_HAS_BEEN_REACHED:
            printf("%s\n", "Error: Could not open the file since it has been opened 4 times already");
            return -1;
        case FILE_NOT_FOUND_IN_OPEN_TABLE:
            printf("%s\n", "Error: Specified file was not found in the open file table");
            return -1;
        case FILE_NOT_FOUND:
            printf("%s\n", "Error: Specified file was not found.");
            return -1;
        case FILE_WITH_NAME_EXISTS:
            printf("%s\n", "Error: File with the same name already exists.");
            return -1;
        case FILE_IS_EMPTY:
            printf("%s\n", "Error: The file is empty.");
            return -1;
        case INVALID_FILE_NAME:
            printf("%s\n", "Error: The filename is invalid.");
            return -1;
        case FOUND_TYPE:
            printf("%s\n", "The file type is found.");
            return 0;
        case WRITING_TO_DIR:
            printf("%s\n", "Error: You are trying to write to a directory!");
            return -1;
        case READING_FROM_DIR:
            printf("%s\n", "Error: You are trying to read from a directory!");
            return -1;
        case READING_BEYOND_FILE_SIZE:
            printf("%s\n", "Error: Attempt to read addresses beyond the file size.");
            return -1;
        case WRITING_BEYOND_FILE_SIZE:
            printf("%s\n", "Error: Attempt to write addresses beyond the file size.");
            return -1;
        case PATHNAME_ERROR:
        	printf("%s\n", "Error: Pathname is not existed in file system.");
        	return -1;
        case FILE_NAME_TOO_LONG:
        	printf("%s\n", "Error: The file name is too long. It has to be up to 5 characters.");
        	return -1;
        case WRITE_TOO_MANY_CHARS:
        	printf("%s\n", "Error: More characters were entered than the requested number of bytes.");
        	return -1;
        case READDIR_REG_FILE:
        	printf("%s\n", "Error: Cannot sfs_readdir a regular file type.");
        	return -1;
        case ERROR_PARENT_REG_FILE:
        	printf("%s\n", "Error: Cannot create a file with a regular file as a parent.");
        	return -1;
        case ERROR_DIR_SIZE:
        	printf("%s\n", "Error: Cannot get size of a directory file type. Only for regular files.");
			return -1;
        case ERROR_DELETE_FILE_IS_OPEN:
        	printf("%s\n", "Error: The file is open. Cannot delete it.");
        	return -1;
        case ERROR_DELETE_DIR_HAS_CHILDREN:
        	printf("%s\n", "Error: The DIRECTORY type file is not empty. Cannot delete it.");
			return -1;
        case READDIR_FILE_NOT_OPEN:
			printf("%s\n", "Error: The DIRECTORY type file is not empty. Cannot delete it.");
			return -1;
    }
}
