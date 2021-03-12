#include <stdio.h>
#include <stdlib.h>

#define LAYER_SIZE 25 * 6

typedef struct
{
  char *data;
  size_t length;
} String;

String read_file_as_str(const char *fp)
{
  FILE *f = fopen(fp, "r");
  if (f == NULL)
  {
    printf("error opening file %s\n", fp);
    exit(1);
  }
  int c;
  size_t nch = 0;
  size_t size = 1024;
  char *buf = malloc(size);
  if (buf == NULL)
  {
    fprintf(stderr, "error: memory allocation failed\n");
    exit(1);
  }
  while ((c = getc(f)) != EOF)
  {
    if (nch >= size - 1)
    {
      size *= 2;
      buf = realloc(buf, size);
      if (buf == NULL)
      {
        fprintf(stderr, "error: memory allocation failed\n");
        exit(1);
      }
    }
    buf[nch++] = c;
  }
  buf[nch++] = 0;
  fclose(f);
  return (String){.data = buf, .length = nch};
}

void part_1(String *input)
{
  input->length--;
  input->data[input->length] = 0;
  int lowest = LAYER_SIZE;
  int acc = 0;
  int layer_cursor = 0;
  long long result = 0;
  for (size_t i = 0; i < input->length; i++)
  {
    layer_cursor++;
    if (input->data[i] == '0')
    {
      acc++;
    }
    if (layer_cursor == LAYER_SIZE)
    {
      if (acc < lowest)
      {
        int ones = 0;
        int twos = 0;
        size_t start = i - LAYER_SIZE + 1;
        for (size_t j = start; j < start + LAYER_SIZE; j++)
        {
          switch (input->data[j])
          {
          case '1':
            ones++;
            break;
          case '2':
            twos++;
            break;
          }
        }
        result = ones * twos;
        lowest = acc;
      }
      layer_cursor = 0;
      acc = 0;
    }
  }
  printf("result: %lld\n", result);
}

int main(void)
{
  String input = read_file_as_str("input.txt");
  part_1(&input);
}
