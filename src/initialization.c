#include <stdio.h>
#include "initialization.h"
#include "blockio.h"
#include "super_block.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


int sfs_initialize(int erase)
{
	if (erase == 1)
	{
		// new file system
		int works = new_filesystem();
		// new super block
		super_block superblk;
		superblk.size = 512;
		superblk.blocksize = 128;
		superblk.free_blocks = 512;
		superblk.root = 0;
		unsigned char* buffer =NULL;
		buffer = (unsigned char*) calloc(128, sizeof(unsigned char));
		buffer = (unsigned char*) memcpy(buffer,(unsigned char*) &superblk, sizeof(superblk));
		int writesb = put_block(0,buffer);
		printf("superblock made\n");
		// init free blocks 


		

		if (works == 1 && writesb == 1)
		return 1;
	}
	else
		return 0;


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


