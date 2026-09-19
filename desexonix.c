#include "desexonix.h"
#include "format.h"
#include "bmp.h"
#include "exitcode.h"

void show_intro();
void show_message(const char *message);
void show_error(const char *message);
void show_progress(const unsigned long int start,const unsigned long int stop);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
unsigned long int get_file_size(FILE *target);
void read_data(void *data,const size_t length,FILE *input);
void write_data(const void *data,const size_t length,FILE *output);
unsigned long int check_file_size(FILE *target);
void check_memory(const void *memory);
char *get_string_memory(const size_t length);
size_t get_name_without_extension_length(const char *source);
char *get_name_without_extension(const char *name);
char *get_name(const unsigned long int index,const char *name_without_extension,const char *extension);
unsigned char *create_buffer(const size_t length);
void decrypt_data(unsigned char *target,const size_t length);
bitmap_head prepare_head(const unsigned int image_length,const unsigned int palette_length);
bitmap_core prepare_core(const unsigned short int width,const unsigned short int height,const unsigned short int planes,const unsigned short int bits);
void convert_palette(unsigned char *palette,const size_t length,const size_t item);
unsigned char correct_level(const unsigned char level);
void correct_colors(unsigned char *palette);
size_t get_position(const size_t x,const size_t y,const size_t width);
void do_vertical_mirror(const unsigned char *source,unsigned char *target,const size_t width,const size_t height);
void work(const char *target);

int main(int argc, char *argv[])
{
 show_intro();
 switch (argc)
 {
  case 1:
  show_message("You must give a target file name as the command-line argument!");
  exit(COMMAND_LINE_ARGUMENTS_ERROR);
  break;
  case 2:
  show_message("Working...");
  work(argv[1]);
  show_message("The work has been finished");
  break;
  default:
  show_message("You gave too many command-line arguments");
  exit(COMMAND_LINE_ARGUMENTS_ERROR);
  break;
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("Desexonix 1.7");
 puts("Sexonix image extractor by Popov Evgeniy Alekseyevich,2020-2026 years");
 puts("This program is distributed under the GNU GENERAL PUBLIC LICENSE (version 2 or later) terms");
}

void show_message(const char *message)
{
 putchar('\n');
 puts(message);
}

void show_error(const char *message)
{
 fputc('\n',stderr);
 fputs(message,stderr);
 fputc('\n',stderr);
}

void show_progress(const unsigned long int start,const unsigned long int stop)
{
 putchar('\r');
 printf("Amount of the extracted files: %lu from %lu",start,stop);
}

FILE *open_input_file(const char *name)
{
 FILE *target=NULL;
 if (name!=NULL)
 {
  target=fopen(name,"rb");
 }
 if (target==NULL)
 {
  show_error("Can't open the input file");
  exit(OPEN_FILE_ERROR);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target=NULL;
 if (name!=NULL)
 {
  target=fopen(name,"wb");
 }
 if (target==NULL)
 {
  show_error("Can't create the output file");
  exit(CREATE_FILE_ERROR);
 }
 return target;
}

unsigned long int get_file_size(FILE *target)
{
 unsigned long int length=0;
 if (fseek(target,0,SEEK_END)!=0)
 {
  show_error("Can't get the file size!");
  exit(GET_FILE_SIZE_ERROR);
 }
 length=ftell(target);
 rewind(target);
 return length;
}

void read_data(void *data,const size_t length,FILE *input)
{
 if (fread(data,sizeof(char),length,input)<length)
 {
  show_error("Can't read data!");
  exit(READ_DATA_ERROR);
 }

}

void write_data(const void *data,const size_t length,FILE *output)
{
 if (fwrite(data,sizeof(char),length,output)<length)
 {
  show_error("Can't write data!");
  exit(WRITE_DATA_ERROR);
 }

}

unsigned long int check_file_size(FILE *target)
{
 unsigned long int length=0;
 length=get_file_size(target);
 if (length==0)
 {
  show_error("The target file length is invalid");
  exit(CHECK_FILE_SIZE_ERROR);
 }
 if ((length%FULL_IMAGE_LENGTH)!=0)
 {
  show_error("The target file length is invalid");
  exit(CHECK_FILE_SIZE_ERROR);
 }
 return length/FULL_IMAGE_LENGTH;
}

void check_memory(const void *memory)
{
 if (memory==NULL)
 {
  show_error("Can't allocate memory");
  exit(MEMORY_ALLOCATION_ERROR);
 }

}

char *get_string_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length+1,sizeof(char));
 check_memory(memory);
 return memory;
}

size_t get_name_without_extension_length(const char *source)
{
 size_t index=0;
 size_t position=0;
 size_t length=0;
 if (source!=NULL)
 {
  length=strlen(source);
 }
 for (index=length;index>0;--index)
 {
  position=index-1;
  if (source[position]==DIRECTORY_SEPARATOR)
  {
   break;
  }
  if (source[position]=='.')
  {
   if (position>0)
   {
    if ((source[position-1]!=DIRECTORY_SEPARATOR) && (source[position-1]!='.'))
    {
     length=position;
     break;
    }

   }

  }

 }
 return length;
}

char *get_name_without_extension(const char *name)
{
 char *result=NULL;
 size_t length=0;
 length=get_name_without_extension_length(name);
 if (length>0)
 {
  result=get_string_memory(length);
  strncpy(result,name,length);
 }
 return result;
}

char *get_name(const unsigned long int index,const char *name_without_extension,const char *extension)
{
 char *name=NULL;
 size_t length=0;
 if (name_without_extension!=NULL)
 {
  if (extension!=NULL)
  {
   length=strlen(name_without_extension)+strlen(extension)+12;
   name=get_string_memory(length);
   sprintf(name,"%s%lu%s",name_without_extension,index,extension);
  }

 }
 return name;
}

unsigned char *create_buffer(const size_t length)
{
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)malloc(length);
 check_memory(buffer);
 return buffer;
}

void decrypt_data(unsigned char *target,const size_t length)
{
 size_t index=0;
 for (index=0;index<length;++index)
 {
  target[index]^=ENCRYPTION_KEY;
 }

}

bitmap_head prepare_head(const unsigned int image_length,const unsigned int palette_length)
{
 bitmap_head target;
 memset(&target,0,sizeof(bitmap_head));
 target.signature[0]='B';
 target.signature[1]='M';
 target.reversed[0]=0;
 target.reversed[1]=0;
 target.start=sizeof(bitmap_head)+sizeof(bitmap_core);
 target.start+=palette_length;
 target.length=target.start+image_length;
 return target;
}

bitmap_core prepare_core(const unsigned short int width,const unsigned short int height,const unsigned short int planes,const unsigned short int bits)
{
 bitmap_core core;
 memset(&core,0,sizeof(bitmap_core));
 core.length=sizeof(bitmap_core);
 core.width=width;
 core.height=height;
 core.planes=planes;
 core.bits=bits;
 return core;
}

void convert_palette(unsigned char *palette,const size_t length,const size_t item)
{
 size_t index=0;
 unsigned char red=0;
 unsigned char blue=0;
 for (index=0;index<length;index+=item)
 {
  red=palette[index];
  blue=palette[index+2];
  palette[index]=blue;
  palette[index+2]=red;
 }

}

unsigned char correct_level(const unsigned char level)
{
 return (level*4)+(level/16);
}

void correct_colors(unsigned char *palette)
{
 size_t index=0;
 unsigned char level=0;
 for (index=0;index<PALETTE_LENGTH;++index)
 {
  level=correct_level(palette[index]);
  palette[index]=level;
 }

}

size_t get_position(const size_t x,const size_t y,const size_t width)
{
 return x+(y*width);
}

void do_vertical_mirror(const unsigned char *source,unsigned char *target,const size_t width,const size_t height)
{
 size_t index=0;
 size_t position=0;
 size_t x=0;
 size_t y=0;
 for (y=0;y<height;++y)
 {
  for (x=0;x<width;++x)
  {
   position=get_position(x,height-y-1,width);
   target[index]=source[position];
   ++index;
  }

 }

}

void work(const char *target)
{
 unsigned long int index=0;
 unsigned long int amount=0;
 char *name_without_extension=NULL;
 char *name=NULL;
 unsigned char *data=NULL;
 unsigned char *image=NULL;
 unsigned char *palette=NULL;
 FILE *input=NULL;
 FILE *output=NULL;
 bitmap_head head;
 bitmap_core core;
 data=create_buffer(IMAGE_LENGTH);
 image=create_buffer(IMAGE_LENGTH);
 palette=create_buffer(PALETTE_LENGTH);
 head=prepare_head(IMAGE_LENGTH,PALETTE_LENGTH);
 core=prepare_core(IMAGE_WIDTH,IMAGE_HEIGHT,IMAGE_PLANES,COLOR_BITS);
 input=open_input_file(target);
 name_without_extension=get_name_without_extension(target);
 amount=check_file_size(input);
 for (index=0;index<amount;++index)
 {
  show_progress(index+1,amount);
  name=get_name(index+1,name_without_extension,".bmp");
  read_data(palette,PALETTE_LENGTH,input);
  read_data(data,IMAGE_LENGTH,input);
  decrypt_data(palette,PALETTE_LENGTH);
  decrypt_data(data,IMAGE_LENGTH);
  convert_palette(palette,PALETTE_LENGTH,PALETTE_ITEM_SIZE);
  correct_colors(palette);
  do_vertical_mirror(data,image,IMAGE_WIDTH,IMAGE_HEIGHT);
  output=create_output_file(name);
  write_data(&head,sizeof(bitmap_head),output);
  write_data(&core,sizeof(bitmap_core),output);
  write_data(palette,PALETTE_LENGTH,output);
  write_data(image,IMAGE_LENGTH,output);
  free(name);
  fclose(output);
 }
 free(data);
 free(image);
 free(palette);
 free(name_without_extension);
 fclose(input);
}