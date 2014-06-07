#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char* ngram_read_file(char *infile)
{
  char *str;
  uint32_t file_size;
  
  // get file size
  FILE *input_file = fopen(infile, "rb");
  fseek(input_file, 0, SEEK_END);
  file_size = ftell(input_file);
  
  rewind(input_file);
  str = malloc(file_size * (sizeof(char)));
  
  // read
  fread(str, sizeof(char), file_size, input_file);
  fclose(input_file);
  
  return str;
}
