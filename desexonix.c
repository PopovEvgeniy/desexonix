#include "desexonix.h"
#include "format.h"

void show_intro();
void show_message(const char *message);
void show_progress(const unsigned long int start,const unsigned long int stop);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
unsigned long int get_file_size(FILE *file);
unsigned long int check_file_size(FILE *target);
void check_memory(const void *memory);
char *get_string_memory(const size_t length);
size_t get_extension_position(const char *source);
char *get_short_name(const char *name);
char *get_name(const unsigned long int index,const char *short_name,const char *extension);
unsigned char *create_buffer(const size_t length);
void decrypt_data(unsigned char *target,const size_t length);
tga_head prepare_head();
void convert_palette(unsigned char *palette);
unsigned char correct_level(const unsigned char level);
void correct_colors(unsigned char *palette);
void work(const char *target);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<2)
 {
  show_message("You must give a target file name as the command-line argument!");
 }
 else
 {
  show_message("Working...");
  work(argv[1]);
  show_message("The work has been finished");
 }
 return 0;
}

void show_progress(const unsigned long int start,const unsigned long int stop)
{
 unsigned long int progress;
 progress=(start+1)*100;
 progress/=stop;
 putchar('\r');
 printf("Amount of the extracted files: %lu from %lu.The progress:%lu%%",start+1,stop,progress);
}

void show_intro()
{
 putchar('\n');
 puts("Desexonix. Version 0.7");
 puts("Sexonix image extractor by Popov Evgeniy Alekseyevich,2020-2025 years");
 puts("This program is distributed under the GNU GENERAL PUBLIC LICENSE");
 puts("Some code was taken from XXX Games tools by the CTPAX-X team");
 puts("It was relicensed with the permission of the author");
}

void show_message(const char *message)
{
 putchar('\n');
 puts(message);
}

FILE *open_input_file(const char *name)
{
 FILE *target;
 target=fopen(name,"rb");
 if (target==NULL)
 {
  puts("Can't open the input file");
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
  show_message("Can't create the ouput file");
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
  puts("The target file length is invalid");
  exit(3);
 }
 return length/(IMAGE_LENGTH+PALETTE_LENGTH);
}

void check_memory(const void *memory)
{
 if(memory==NULL)
 {
  show_message("Can't allocate memory");
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
 return strncpy(result,name,length);
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
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)malloc(length);
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

unsigned char correct_level(const unsigned char level)
{
 return (level*4)+(level/16);
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
  fread(palette,sizeof(unsigned char),PALETTE_LENGTH,input);
  fread(data,sizeof(unsigned char),IMAGE_LENGTH,input);
  decrypt_data(palette,PALETTE_LENGTH);
  decrypt_data(data,IMAGE_LENGTH);
  convert_palette(palette);
  correct_colors(palette);
  fwrite(&image_head,sizeof(tga_head),sizeof(unsigned char),output);
  fwrite(palette,sizeof(unsigned char),PALETTE_LENGTH,output);
  fwrite(data,sizeof(unsigned char),IMAGE_LENGTH,output);
  free(name);
  fclose(output);
 }
 free(data);
 free(palette);
 free(short_name);
 fclose(input);
}