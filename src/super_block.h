#ifndef SUPER_BLOCK_H_   /** Include guard */
#define SUPER_BLOCK_H_

/** @file super_block.h
 * Stores the information about the disk on the disk
 * Keeps track of the blocks on the disk and write the super block to disk.
 */

typedef struct {
	int size;
	int blocksize;
	int free_blocks;
	int root;
} super_block;


extern short int disk_bitmap[512];
extern short int super_blk_buf[128];

/**
 *
 * @brief Writes the super_block from memory onto the disk
 * @details It takes 4 block statuses (busy/free) from the disk_bitmap and convert it to decimal and then writes the result on to disk
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @return 0 for success 
 *
 * @copyright GNU Public License.
 *
 */
extern int put_super_blk(void);


/**
 *
 * @brief Gets the super block from disk and loads it into memory
 * @details Reads the values from disk and loads them into memory by converting in from decimal into binary to fill up the disk_bitmap arrsay correctly
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @return 0 for success
 *
 * @copyright GNU Public License.
 *
 */
extern int get_super_blk(void);


/**
 *
 * @brief Sets the appropriate location in disk_bitmap to busy (only used for inode table)
 * @details Sets the block to busy and then writes the super block to disk.
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param blk_no Number of the block to set busy
 *
 * @return 0 for success
 *
 * @copyright GNU Public License.
 *
 */
extern int set_disk_bitmap_busy(int blk_no);


/**
 *
 * @brief Gets the first non-busy block from the disk and returns its id
 * @details Reads memory to find the first id of a free block. Then sets it to busy and saves the block_num to the parameter provided.
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param *free_blk_no Pointer to char to save the block number to
 * @return 0 for success
 *
 * @copyright GNU Public License.
 *
 */
extern int get_empty_blk(int *free_blk_no);


/**
 *
 * @brief Marks the block on disk as free
 * @details Looks up the block in disk_bitmap and marks it as free, then recalculates super_blk_buf and writes it to disk. 
 *
 * @author Yasha Prikhodko
 * @author Cedric Leong
 * @author Arezou Mousavi
 *
 * @param *release_blk_no Block number to release
 * @return 0 for success
 *
 * @copyright GNU Public License.
 *
 */
 extern int release_block(int release_blk_no);

#endif
