#if defined _MSC_VER && _MSC_VER>=1400
  #pragma warning(disable : 4996)
#endif

#ifdef _WIN32
#define DIRECTORY_SEPARATOR '\\'
#define file_seek _fseeki64
#define file_tell _ftelli64
#else
#define DIRECTORY_SEPARATOR '/'
#define file_seek fseeko
#define file_tell ftello
#endif

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>