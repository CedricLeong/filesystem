#include <stdio.h>
#include "blockio.h"
#include "i_node.h"
#include "super_block.h"

int sfs_initialize(int erase)
{
if (erase == 1)
{
    new_filesystem();
    put_super_blk();
    put_inode_table();

    // open root folder /

    int fd = sfs_open("/");
    if (fd >= 0) {
    	printf("%s %d\n", "Root folder / is opened. File descriptor:", fd);
    }
    return 1;

}
return 0;
}
int new_filesystem(void){
        /* Create the null block of data */
        char* buffer;
        buffer =  calloc(128, sizeof(char));

        int retval = 0;

        for (int i = 0; i < 512; i++) {
                retval = put_block(i, buffer);
                if (retval != 0) {
                        return 0;
                }
        }
        return 1;
}
