
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
        char convert[4];
        int count = 0;
        int decimal = 0;
        for(int i=0; i < 512; i++) {
                if (count != 4) {
                        convert[count] = disk_bitmap[i];
                        ++count;
                } else {
                        count = 0;
                        decimal = binary_decimal(atoi(convert));
                        // printf("%d\n", decimal);
                        super_blk_buf[i/4] = decimal;
                }
        }

        return decimal;
}

int get_super_blk(void) {
        //get super block from disk

        int bitmap = 0;

        for (int i=0; i<128; i++) {
                int dec = super_blk_buf[i];
                int binary = decimal_binary(dec);

                int count;

                while(binary!=0) {
                        binary/=10;
                        ++count;
                }

                if (count == 0) {
                        count = 1;
                } 

                char buff[4] = "";
                sprintf(buff, "%04d", binary);

                for (int j=0; j<4; j++) {
                        disk_bitmap[bitmap] = buff[j];
                        ++bitmap;
                }
        }
        return 0;
}

int get_empty_blk(int *free_blk_no) {
        for(int i=11; i<512; i++) {
                if (disk_bitmap[i] == 0) {
                        disk_bitmap[i] = 1;
                        return i;
                }
        }
}

int release_block(int release_blk_no) {
        if (release_blk_no > 10) {
                disk_bitmap[release_blk_no] = 0;
        } else {
                return 0;
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