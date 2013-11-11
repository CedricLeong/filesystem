#ifndef SUPER_BLOCK_H_   /* Include guard */
#define SUPER_BLOCK_H_

extern int sfs_create(char *pathname, int type);
extern int sfs_open(char *pathname);

extern int sfs_read(int fd,int start, int length, char *mem_pointer);

extern int sfs_write(int fd, int start, int length, char *mem_pointer);

extern int sfs_readdir(int fd, char *mem_pointer);
extern int sfs_close(int fd);

extern int sfs_delete(char *pathname);
#endif