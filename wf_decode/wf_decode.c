
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void parse_desc_file(char *desc_filename)
{
}

void parse_input_file(char *input_filename)
{
    FILE *input_file = fopen(input_filename, "rb");
    assert(input_file);

    fseek(input_file, 0L, SEEK_END);
    size_t size = ftell(input_file);
    printf("file size: %ld\n", size);
    fseek(input_file, 0L, SEEK_SET);

    char *buffer = (char *)malloc(size);
    assert(buffer);

    size_t bytes_read = fread(buffer, 1, size, input_file);
    assert(bytes_read == size);

    printf("file %s: %ld bytes read\n", input_filename, bytes_read);

    // Skip "ALL,"
    int offset = 0;
    while(buffer[offset] != '#')
        ++offset;

    // Check that size field is present
    assert(buffer[offset] == '#');
    ++offset;
    assert(buffer[offset] == '9');
    ++offset;

    for(int i=offset; i<offset+9;++i){
        assert(buffer[i] >= '0' && buffer[i] <='9');
    }

    // Extract data size
    char number[10];
    memcpy(number, buffer+offset, 9);
    number[9] = '\0';

    int data_size = atoi(number);
    printf("data size: %d\n", data_size);

    // Check for correct terminator
    offset += 9;
    assert(buffer[offset + data_size]   == 10);
    assert(buffer[offset + data_size+1] == 10);
}

int main(int argc, char **argv)
{
    parse_input_file(argv[1]);
}
