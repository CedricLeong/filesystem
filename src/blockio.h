#ifndef BLOCKIO_H_   /* Include guard */
#define BLOCKIO_H_


extern int get_block(int blknum,char *buf);    /* where in memory to put retrieved data */

extern int put_block(int blknum,char *buf);    /* where in memory to get new disk block contents */


#endif