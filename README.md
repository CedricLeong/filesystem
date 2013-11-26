@TODO
Many operations do not work after restarting filesystem, no loading from disk to memory happens (e.g inode_table is empty). 
Change the inode names such that untokenized strings work with get_type.
Makefile
sfs_readdir
Making a tree structure for dir
Allocating files to a dir



Special Notes: The write function in sartipi's code shows us that we don't have to worry about writing to multiple blocks.
If you try to enter a length over 128 or start + length over 128 it will give you an error. 
Also, do not run the program in code::blocks some functions don't work in xterm. 

Finished work:
sfs_write, sfs_read and sfs_gettype all works for files and dir
