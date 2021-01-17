#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBERS_COUNT 256
#define MAX_NUMBER_SIZE 4

#define ADD 1
#define MULTIPLY 2
#define HALT 99

void parse_numbers(const char *input, long *numbers)
{
    size_t input_length = strlen(input);
    char number_str[MAX_NUMBER_SIZE];
    int char_pos = 0;
    int numbers_count = 0;
    for (size_t i = 0; i < input_length; i++)
    {
        if (input[i] == ',')
        {
            number_str[char_pos] = '\0';
            numbers[numbers_count] = strtol(number_str, NULL, 10);
            memset(number_str, 0, sizeof(char) * MAX_NUMBER_SIZE);
            char_pos = 0;
            numbers_count++;
        }
        else
        {
            number_str[char_pos] = input[i];
            char_pos++;
        }
    }
    number_str[char_pos] = '\0';
    numbers[numbers_count] = strtol(number_str, NULL, 10);
}

long run_program(long *numbers)
{
    for (int cursor = 0; cursor < NUMBERS_COUNT; cursor += 4)
    {
        switch (numbers[cursor])
        {
        case ADD:
            numbers[numbers[cursor+3]] = numbers[numbers[cursor+1]] + numbers[numbers[cursor+2]];
            break;
        case MULTIPLY:
            numbers[numbers[cursor+3]] = numbers[numbers[cursor+1]] * numbers[numbers[cursor+2]];
            break;
        case HALT:
            return numbers[0];
        default:
            printf("error: unknown opcode: %ld\n", numbers[cursor]);
            exit(1);
        }
    }
    printf("error: no halt opcode\n");
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("error: no input\n");
        return 1;
    }
    long init_numbers[NUMBERS_COUNT] = {0};
    parse_numbers(argv[1], init_numbers);
    long numbers[NUMBERS_COUNT];
    memcpy(numbers, init_numbers, sizeof(long) * NUMBERS_COUNT);
    numbers[1] = 12;
    numbers[2] = 2;
    printf("part 1: %ld\n", run_program(numbers));
    memcpy(numbers, init_numbers, sizeof(long) * NUMBERS_COUNT);
    for (int noun = 0; noun <= 99; noun++)
    {
        for (int verb = 0; verb <= 99; verb++)
        {
            numbers[1] = noun;
            numbers[2] = verb;
            if (run_program(numbers) == 19690720)
            {
                printf("part 2: %ld\n", 100 * numbers[1] + numbers[2]);
                return 0;
            }
            memcpy(numbers, init_numbers, sizeof(long) * NUMBERS_COUNT);
        }
    }
    return 1;
}
