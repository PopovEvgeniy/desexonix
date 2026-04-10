#define IMAGE_LENGTH 64000
#define PALETTE_LENGTH 768
#define TOP_LEFT 0x20

/*
This code is based on XXX Games tools source codes by the CTPAX-X team (http://www.ctpax-x.org/?goto=files&show=21).
It was relicensed with the permission of the author.
*/

#pragma pack(push, 1)
typedef struct
{
 unsigned char id;
 unsigned char map_type;
 unsigned char image_type;
 unsigned short int map_start;
 unsigned short int map_length;
 unsigned char map_depth;
 unsigned short int x_offset;
 unsigned short int y_offset;
 unsigned short int width;
 unsigned short int height;
 unsigned char depth;
 unsigned char descriptor;
} tga_head;
#pragma pack(pop)