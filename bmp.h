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
 unsigned short int width;
 unsigned short int height;
 unsigned short int planes;
 unsigned short int bits;
} bitmap_core;
#pragma pack(pop)