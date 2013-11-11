#include "inode.h"
#include "file_functions.h"


int sfs_create(char *pathname, int type)
{
	if (type == 0)
	{
		//Create new inode
		inode* inode = {free_block.get_free_block,date(NULL),0,free_block.get_free_block, pathname}; 
		// put it in inode table
		put_inodetable = inode; 
		// create new index block
		index_block ib = {};  
	}
}
int sfs_open(char *pathname)
{
	// Check if file is there
	// Open the file
	// return fd
}

int sfs_read(int fd,int start, int length, char *mem_pointer)
{
	//Copy contents of file into buffer
	// read buffer

}

int sfs_write(int fd, int start, int length, char *mem_pointer)
{
	//Copy buffer into file
	// put block
}

int sfs_readdir(int fd, char *mem_pointer)
{
	// list all inodes

}

int sfs_close(int fd)
{
	// Close fd in swoft 

}

int sfs_delete(char *pathname)
{
	// wipe file
}
