#include <stdio.h>
#include "initialization.h"
#include "blockio.h"
#include "super_block.h"
#include <stdint.h>
#include <stdlib.h>

int sfs_initialize(int erase)
{
	if (erase == 1)
	{
		int works = new_filesystem();
		if (works == 1)
		return 1;
	}
	else
		return 0;

	// initialize the superblock 
	super_block superblk = {512,128,0,0};
	put_super_blk();


	// initlialize free blocks list
}
int new_filesystem(){
        /* Create the null block of data */
        unsigned char* buffer = NULL;
        buffer = (unsigned char*) calloc(128, sizeof(unsigned char));

        int retval = 0;

        /* Go block to block setting them to null */
        for (int i = 0; i < 512; i++)
        {
                retval = put_block(i, buffer);
                if (retval != 0)
                {
                        /*
                         * Error occurred writing block to disk.
                         */
                        return 0;
                }
        }
        free(buffer);
        return 1;
}


