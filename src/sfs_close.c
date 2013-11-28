#include "sfs_close.h"
#include "open_file_table.h"

int sfs_close(int fd) {
	int success = close_file(fd);
		if( success != 0)
		{
			return -1;
		}
		return 0;
}
