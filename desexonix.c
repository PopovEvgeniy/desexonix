#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "desexonix.h"

void show_start_message();
void show_end_message();
void show_intro();
void command_line_help();
void show_progress(const unsigned long int start,const unsigned long int stop);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
unsigned long int get_file_size(FILE *file);
unsigned long int check_file_size(FILE *target);
void check_memory(const void *memory);
char *get_string_memory(const size_t length);
unsigned char *get_memory(const size_t length);
size_t get_extension_position(const char *source);
char *get_short_name(const char *name);
char *get_name(const unsigned long int index,const char *short_name,const char *extension);
unsigned char *create_buffer(const size_t length);
void decrypt_data(unsigned char *target,const size_t length);
tga_head prepare_head();
void convert_palette(unsigned char *palette);
unsigned char correct_level(const unsigned short int level);
void correct_colors(unsigned char *palette);
void write_head(FILE *output,tga_head target);
void read_data(FILE *input,unsigned char *buffer,const size_t length);
void write_data(FILE *output,unsigned char *buffer,const size_t length);
void work(const char *target);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<2)
 {
  command_line_help();
 }
 else
 {
  show_start_message();
  work(argv[1]);
  show_end_message();
 }
 return 0;
}

void show_start_message()
{
 putchar('\n');
 puts("Extracting a graphics... Please wait");
}

void show_end_message()
{
 putchar('\n');
 puts("Work finish");
}

void show_progress(const unsigned long int start,const unsigned long int stop)
{
 unsigned long int progress;
 progress=start+1;
 progress*=100;
 progress/=stop;
 putchar('\r');
 printf("Amount of extracted files: %lu from %lu.Progress:%lu%%",start+1,stop,progress);
}

void show_intro()
{
 putchar('\n');
 puts("Desexonix. Version 0.5.1");
 puts("Sexonix image extractor by Popov Evgeniy Alekseyevich,2020 year");
 puts("This program distributed under GNU GENERAL PUBLIC LICENSE");
 puts("Some code is based on XXX Games tools sources by CTPAX-X team");
 puts("It relicensed with permission from the author");
}

void command_line_help()
{
 putchar('\n');
 puts("You must give a target file name as command line argument!");
}

FILE *open_input_file(const char *name)
{
 FILE *target;
 target=fopen(name,"rb");
 if (target==NULL)
 {
  putchar('\n');
  puts("Can't open input file");
  exit(1);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target;
 target=fopen(name,"wb");
 if (target==NULL)
 {
  putchar('\n');
  puts("Can't create ouput file");
  exit(2);
 }
 return target;
}

unsigned long int get_file_size(FILE *file)
{
 unsigned long int length;
 fseek(file,0,SEEK_END);
 length=ftell(file);
 rewind(file);
 return length;
}

unsigned long int check_file_size(FILE *target)
{
 unsigned long int length;
 length=get_file_size(target);
 if (length<(IMAGE_LENGTH+PALETTE_LENGTH))
 {
  putchar('\n');
  puts("Invalid target file size");
  exit(3);
 }
 return length/(IMAGE_LENGTH+PALETTE_LENGTH);
}

void check_memory(const void *memory)
{
 if(memory==NULL)
 {
  putchar('\n');
  puts("Can't allocate memory");
  exit(4);
 }

}

char *get_string_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length+1,sizeof(char));
 check_memory(memory);
 return memory;
}

unsigned char *get_memory(const size_t length)
{
 unsigned char *memory=NULL;
 memory=(unsigned char*)calloc(length,sizeof(unsigned char));
 check_memory(memory);
 return memory;
}

size_t get_extension_position(const char *source)
{
 size_t index;
 for(index=strlen(source);index>0;--index)
 {
  if(source[index]=='.')
  {
   break;
  }

 }
 if (index==0) index=strlen(source);
 return index;
}

char *get_short_name(const char *name)
{
 size_t length;
 char *result=NULL;
 length=get_extension_position(name);
 result=get_string_memory(length);
 strncpy(result,name,length);
 return result;
}

char *get_name(const unsigned long int index,const char *short_name,const char *extension)
{
 char *name=NULL;
 size_t length;
 length=strlen(short_name)+strlen(extension)+12;
 name=get_string_memory(length);
 sprintf(name,"%s%lu%s",short_name,index,extension);
 return name;
}

unsigned char *create_buffer(const size_t length)
{
 unsigned char *buffer;
 buffer=(unsigned char *)calloc(length,sizeof(unsigned char));
 check_memory(buffer);
 return buffer;
}

void decrypt_data(unsigned char *target,const size_t length)
{
 size_t index;
 for (index=0;index<length;++index)
 {
  target[index]^=0x55;
 }

}

tga_head prepare_head()
{
 /*
 This code is based on XXX Games tools sources by CTPAX-X team(http://www.ctpax-x.org/?goto=files&show=21).
 It relicensed with permission from the author.
 */
 tga_head target;
 target.id=0;
 target.x_offset=0;
 target.y_offset=0;
 target.map_start=0;
 target.descriptor=TOP_LEFT;
 target.map_length=256;
 target.map_depth=24;
 target.depth=8;
 target.width=320;
 target.height=200;
 target.map_type=1;
 target.image_type=1;
 return target;
}

void convert_palette(unsigned char *palette)
{
 size_t index;
 unsigned char red,blue;
 for (index=0;index<PALETTE_LENGTH;index+=3)
 {
  red=palette[index];
  blue=palette[index+2];
  palette[index]=blue;
  palette[index+2]=red;
 }

}

unsigned char correct_level(const unsigned short int level)
{
 unsigned short int result;
 result=(level*255)/63;
 return result;
}

void correct_colors(unsigned char *palette)
{
 size_t index;
 unsigned char level;
 for (index=0;index<PALETTE_LENGTH;++index)
 {
  level=correct_level(palette[index]);
  palette[index]=level;
 }

}

void write_head(FILE *output,tga_head target)
{
 fwrite(&target,TGA_HEAD_LENGTH,sizeof(unsigned char),output);
}

void read_data(FILE *input,unsigned char *buffer,const size_t length)
{
 fread(buffer,sizeof(unsigned char),length,input);
}

void write_data(FILE *output,unsigned char *buffer,const size_t length)
{
 fwrite(buffer,sizeof(unsigned char),length,output);
}

void work(const char *target)
{
 unsigned long int index,amount;
 char *short_name;
 char *name;
 unsigned char *data;
 unsigned char *palette;
 FILE *input;
 FILE *output;
 tga_head image_head;
 data=create_buffer(IMAGE_LENGTH);
 palette=create_buffer(PALETTE_LENGTH);
 image_head=prepare_head();
 input=open_input_file(target);
 short_name=get_short_name(target);
 amount=check_file_size(input);
 for (index=0;index<amount;++index)
 {
  show_progress(index,amount);
  name=get_name(index+1,short_name,".tga");
  output=create_output_file(name);
  read_data(input,palette,PALETTE_LENGTH);
  read_data(input,data,IMAGE_LENGTH);
  decrypt_data(palette,PALETTE_LENGTH);
  decrypt_data(data,IMAGE_LENGTH);
  convert_palette(palette);
  correct_colors(palette);
  write_head(output,image_head);
  write_data(output,palette,PALETTE_LENGTH);
  write_data(output,data,IMAGE_LENGTH);
  free(name);
  fclose(output);
 }
 free(data);
 free(palette);
 free(short_name);
 fclose(input);
}