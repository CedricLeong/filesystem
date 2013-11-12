#include "inode.h"
#include "file_functions.h"

short int next = 0; 

int sfs_create(char *pathname, int type)
{
	if (type == 0)
	{
		//Create new inode

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
    if(pathname = strtok(pathname, DELIMS)) {
        printf(pathname);
    }
    int *index;
    int *i_numb;
	if (compare_component_tobuff(pathname, index, i_numb) == 0) {
        int *file_ptr;
        get_file_pointer(i_numb, file_ptr);
        refcount++;
	} else {
        return 1;
	}
}

int sfs_read(int fd,int start, int length, char* buffer)
{
	char* buffer;
	buffer = calloc(1024, sizeof(char));

 	if (file_refcount[fd_table[fd]]== 4)
 		return 0;
 	else 
 		return 1; 


 	int success = get_file(fd_table[fd],0); 
 		if (success == 0)
 			return 0; 
 	return 1; 

}

int sfs_write(int fd, int start, int length, char *mem_pointer)
{

}

int sfs_readdir(int fd, char *mem_pointer)
{
	char buffer[6];
	for (int i = 0; i < 6; i++)
	{
		buffer[i] = pathname[i][next];
	}
	mem_pointer = buffer;
	next++; 
	return 1; 
}

int sfs_close(int fd)
{
	if ( file_refcount[file_table[fd]] == 0)
		return 0; // file not open
	else
		 file_refcount[file_table[fd]]--;

  return 1; 
}

int sfs_delete(char *pathname)
{
	// deletle pathname
	// deletle inumber
}
