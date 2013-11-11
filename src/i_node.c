#include i_node.h
#include blockio.h

#define BUFFER 1024

inode* new_inode()
{
	int file_location = 0;
	time_t created = time(NULL);
	int file_size = 0;
	int index_block = 0;
	int UserID = 0;
	int GroupID = 0;
	char name = ""; 
}

inode* get_inode(int location){
char* buf = (char*)calloc(1024, sizeof((char));
int success = get_block(int location, char *buf)
	if (success < 0)
	{
		perror(Error!);
	}

return (inode*) buf;
}

int get_size(int location){
char* buf = (char*)calloc(128, sizeof((char));
int success = get_block(int location, char *buf)
	if (success < 0)
	{
		perror(Error!);
	}

return ((inode*) buf) -> file_size;
}

boolean file_exist(int location){
char* buf = (char*)calloc(128, sizeof((char));
int success = get_block(int location, char *buf)
	if (success < 0)
	{
		return false;
	}

return true;
}
}
