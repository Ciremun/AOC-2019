#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LINE_LENGTH 7
#define LINES_COUNT 100

void lines_to_numbers(char lines[LINES_COUNT][LINE_LENGTH], long numbers[LINES_COUNT])
{
    int line_pos = 0;
    while (line_pos != LINES_COUNT)
    {
        numbers[line_pos] = strtol(lines[line_pos], NULL, 10);
        line_pos++;
    }
}

void read_file(const char *fp, char lines[LINES_COUNT][LINE_LENGTH])
{
    FILE *fh;
    fh = fopen(fp, "r");

    char buffer[LINES_COUNT];
    int line_pos = 0;

    while (fgets(buffer, LINES_COUNT, fh))
    {
        strcpy(lines[line_pos], buffer);
        line_pos++;
    }

    fclose(fh);
}

void solve(long numbers[LINES_COUNT])
{
    long modules = 0;
    long fuels = 0;

    for (int i = 0; i < LINES_COUNT; i++)
    {
        if (numbers[i] == 0)
        {
            break;
        }
        float module_fuel = floorf(numbers[i] / 3) - 2;
        float fuel_fuel = floorf(module_fuel / 3) - 2;
        float total_fuel_fuel = 0.0f;
        while (fuel_fuel > 0)
        {
            total_fuel_fuel += fuel_fuel;
            fuel_fuel = floorf(fuel_fuel / 3) - 2;
        }
        modules += module_fuel;
        fuels += total_fuel_fuel;
    }

    printf("part 1: %ld\npart 2: %ld\n", modules, modules + fuels);
}

int main()
{
    char lines[LINES_COUNT][LINE_LENGTH] = {"0"};
    read_file("input.txt", lines);

    long numbers[LINES_COUNT];
    lines_to_numbers(lines, numbers);

    solve(numbers);
}
