#include "desexonix.h"
#include "format.h"
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
  exit(COMMAND_LINE_ARGUMENTS_ERROR);
 }
 else
 {
  show_message("Working...");
  work(argv[1]);
  show_message("The work has been finished");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("Desexonix. Version 1.3.9");
 puts("Sexonix image extractor by Popov Evgeniy Alekseyevich,2020-2026 years");
 puts("This program is distributed under the GNU GENERAL PUBLIC LICENSE");
 puts("Some code was taken from XXX Games tools by the CTPAX-X team");
 puts("It was relicensed with the permission of the author");
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
 if(memory==NULL)
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

tga_head prepare_head()
{
 tga_head target;
 memset(&target,0,sizeof(tga_head));
 target.x_offset=0;
 target.y_offset=0;
 target.id=TGA_ID;
 target.descriptor=TOP_LEFT;
 target.map_start=MAP_START;
 target.map_type=MAP_TYPE;
 target.map_length=MAP_LENGTH;
 target.map_depth=MAP_DEPTH;
 target.depth=COLOR_BITS;
 target.width=IMAGE_WIDTH;
 target.height=IMAGE_HEIGHT;
 target.image_type=IMAGE_TYPE;
 return target;
}

void convert_palette(unsigned char *palette)
{
 size_t index=0;
 unsigned char red=0;
 unsigned char blue=0;
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
 size_t index=0;
 unsigned char level=0;
 for (index=0;index<PALETTE_LENGTH;++index)
 {
  level=correct_level(palette[index]);
  palette[index]=level;
 }

}

void work(const char *target)
{
 unsigned long int index=0;
 unsigned long int amount=0;
 char *name_without_extension=NULL;
 char *name=NULL;
 unsigned char *data=NULL;
 unsigned char *palette=NULL;
 FILE *input=NULL;
 FILE *output=NULL;
 tga_head image_head;
 data=create_buffer(IMAGE_LENGTH);
 palette=create_buffer(PALETTE_LENGTH);
 image_head=prepare_head();
 input=open_input_file(target);
 name_without_extension=get_name_without_extension(target);
 amount=check_file_size(input);
 for (index=0;index<amount;++index)
 {
  show_progress(index+1,amount);
  name=get_name(index+1,name_without_extension,".tga");
  read_data(palette,PALETTE_LENGTH,input);
  read_data(data,IMAGE_LENGTH,input);
  decrypt_data(palette,PALETTE_LENGTH);
  decrypt_data(data,IMAGE_LENGTH);
  convert_palette(palette);
  correct_colors(palette);
  output=create_output_file(name);
  write_data(&image_head,sizeof(tga_head),output);
  write_data(palette,PALETTE_LENGTH,output);
  write_data(data,IMAGE_LENGTH,output);
  free(name);
  fclose(output);
 }
 free(data);
 free(palette);
 free(name_without_extension);
 fclose(input);
}