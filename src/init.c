#include <stdio.h>
#include "super_block.h"
#include "sfs_write.h"
#include "sfs_open.h"
#include "sfs_read.h"
#include "sfs_create.h"
/*This file holds the initalization file that will create the root directory and super block*/

int main(void) {

    clear_disk();
    put_super_blk();
    char *pathname = "/home";
    sfs_create(pathname, 0);
    sfs_open(pathname);
    char *buf = "hello";
    sfs_write(0, 0, 128, buf);

    char *buf1 = calloc(128, sizeof(char));
    sfs_read(0, 0, 128, buf1);


}
