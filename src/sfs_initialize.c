#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sfs_open.h"
#include "blockio.h"
#include "i_node.h"
#include "super_block.h"
#include "sfs_initialize.h"

int sfs_initialize(int erase)
{
if (erase == 1)
{
    if(new_filesystem() < 0) {
    	//failed
    	return -1;
    }
    put_super_blk();
    put_inode_table();

    // open root folder /

    int fd = sfs_open("/");
    if (fd >= 0) {
    	printf("%s %d\n", "Root folder / is opened. File descriptor:", fd);
    }
    return 1;

} else if (erase == 0) {
	// load the info from disk
	get_super_blk();
	get_inode_table_from_disk();

	// open root folder /

	int fd = sfs_open("/");
	if (fd >= 0) {
		printf("%s %d\n", "Root folder / is opened. File descriptor:", fd);
	}
	return 1;
}
return -1;
}
int new_filesystem(void){
        /* Create the null block of data */
        char* buffer;
        buffer =  calloc(128, sizeof(char));

        int retval = 0;

        for (int i = 0; i < 512; i++) {
                retval = put_block(i, buffer);
                if (retval != 0) {
                        return -1;
                }
        }
        return 1;
}
