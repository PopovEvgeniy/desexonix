#define MODERN_PALETTE_ITEM_SIZE 4
#define MODERN_PALETTE_LENGTH 1024
#define IMAGE_PLANES 1

#pragma pack(push, 1)
typedef struct
{
 char signature[2];
 unsigned int length;
 unsigned short int reversed[2];
 unsigned int start;
} bitmap_head;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
 unsigned int length;
 int width;
 int height;
 unsigned short int planes;
 unsigned short int bits;
 unsigned int compression;
 unsigned int bitmap_length;
 int horizontal_resolution;
 int vertical_resolution;
 unsigned int color_used;
 unsigned int color_important;
} bitmap_information;
#pragma pack(pop)