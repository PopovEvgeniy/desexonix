#define IMAGE_LENGTH 64000
#define PALETTE_LENGTH 768
#define TGA_HEAD_LENGTH 18
#define TOP_LEFT 0x20

/*
This code is based on XXX Games tools sources by CTPAX-X team(http://www.ctpax-x.org/?goto=files&show=21).
It relicensed with permission from the author.
*/

#pragma pack(push, 1)
typedef struct
{
 unsigned char id:8;
 unsigned char map_type:8;
 unsigned char image_type:8;
 unsigned short int map_start:16;
 unsigned short int map_length:16;
 unsigned char map_depth:8;
 unsigned short int x_offset:16;
 unsigned short int y_offset:16;
 unsigned short int width:16;
 unsigned short int height:16;
 unsigned char depth:8;
 unsigned char descriptor:8;
} tga_head;
#pragma pack(pop)