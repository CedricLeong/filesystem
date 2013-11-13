#include "error.h"

int error(ERROR error) {
    switch(error) {
        case SUCCESSFULLY_CREATED_FILE:
            printf("%s\n", "File was created successfully\nReturn value: 0");
            return 0;
        case NO_FILE_NAME_ENTERED:
            printf("%s\n", "No name for the file was provided\nReturn value: -1");
            return -1;
    }
}
