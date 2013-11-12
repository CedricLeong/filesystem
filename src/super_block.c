/* This is the super block which holds information about the disk like the free blocks inside, size of blocks and number of blocks*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "blockio.h"
#include "super_block.h"

short int disk_bitmap[512] = {0};
short int super_blk_buf[128];

int binary_decimal(int n);
int decimal_binary(int n);

int put_super_blk(void) {
	char *convert;
	convert = calloc(4, sizeof(int));
	char *buf;
	buf = calloc(128, sizeof(char));
	int counter = 0;
	int decimal = 0;
	for(int i=0; i < 512; i++) {
		if (counter == 4) {
			counter = 0;
			decimal = binary_decimal(atoi(convert));

			super_blk_buf[i/4 - 1] = decimal;
			buf[i/4 - 1] = (char)(((int)'0')+decimal);
		}

		convert[counter] = (char)(((int)'0')+disk_bitmap[i]);
        ++counter;
	}

	// Write to memory
	int writesb = put_block(0, buf);

	return decimal;
}

int get_super_blk(void) {
	//get super block from disk

	int bitmap = 0;

    char *buf;
	buf = calloc(128, sizeof(char));

	get_block(0, (char *) buf);

	for (int i=0; i<128; i++) {
		int dec = buf[i] - '0';
		super_blk_buf[i] = dec;
		int binary = decimal_binary(dec);

		char full_binary[4] = "";
		sprintf(full_binary, "%04d", binary);

		for (int j=0; j<4; j++) {
			disk_bitmap[bitmap] = full_binary[j] - '0';
			++bitmap;
		}
	}
	return 0;
}

int get_empty_blk(int *free_blk_no) {
	for(int i=11; i<512; i++) {
		if (disk_bitmap[i] == 0) {
			disk_bitmap[i] = 1;
			put_super_blk();

			*free_blk_no = i;
			return 0;
		}
	}
}

int release_block(int release_blk_no) {
	if (release_blk_no > 10) {
		disk_bitmap[release_blk_no] = 0;
		put_super_blk();
		return 0;
	} else {
		return -1;
	}
}

/* Function to convert decimal to binary.*/
int decimal_binary(int n) {
	int rem, i=1, binary=0;
	while (n!=0) {
		rem=n%2;
		n/=2;
		binary+=rem*i;
		i*=10;
	}
	return binary;
}

/* Function to convert binary to decimal.*/
int binary_decimal(int n) {
	int decimal=0, i=0, rem;
	while (n!=0) {
		rem = n%10;
		n/=10;
		decimal += rem*pow(2,i);
		++i;
	}
	return decimal;
}
