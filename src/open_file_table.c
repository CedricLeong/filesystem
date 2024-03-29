#include <stdio.h>
#include "error.h"
#include "open_file_table.h"

openfile all_opened_files[64];
int all_fd[64] = {0};

int add_opened_file(char *pathname) {

    // Check if the file is already opened
    for (int i=0; i<64; i++) {
        if (all_opened_files[i].pathname != NULL) {
            if (strcmp(all_opened_files[i].pathname,pathname) == 0) {

                // Make sure the file is not opened 4 times
                if (all_opened_files[i].opened != 4) {
                    all_opened_files[i].opened++;
                    return i;
                } else {
                    return error(FILE_OPENED_LIMIT_HAS_BEEN_REACHED);
                }
            }
        }
    }

    // The file is not opened yet so add it to the table
    openfile file;
    file.pathname = calloc(30, sizeof(char));
    strcpy(file.pathname, pathname);
    file.opened = 1;

    // Find fd for the file
    for (int i=0; i<64; i++) {
        if (all_fd[i] != 1) {
            file.fd = i;
            all_fd[i] = 1;
            all_opened_files[i] = file;
            return file.fd;
        }
    }
}

int close_file(int fd) {
    for (int i=0; i<64; i++) {
        if (fd == all_opened_files[i].fd) {

            // Check if the file was opened multiple times
            if (all_opened_files[i].opened > 1) {
                all_opened_files[i].opened--;
                return 0;
            } else {
                all_fd[i] = 0;
                return 0;
            }
        }
    }

    // The file was not found in the table
    error(FILE_NOT_FOUND_IN_OPEN_TABLE);
    return -1;
}

int get_opened_file(int fd, char *pathname) {
    for(int i=0; i<64; i++) {
        if(fd == all_opened_files[i].fd && all_opened_files[i].pathname != NULL) {
            strcpy(pathname, all_opened_files[i].pathname);
            return 0;
        }
    }

    // File was not found
    error(FILE_NOT_FOUND_IN_OPEN_TABLE);
    return -1;
}

int get_opened_file_fd(char *pathname) {
    for(int i=0; i<64; i++) {
        if(strcmp(all_opened_files[i].pathname, pathname) == 0) {
            return all_opened_files[i].fd;
        }
    }

    // File was not found
    error(FILE_NOT_FOUND_IN_OPEN_TABLE);
    return -1;
}
