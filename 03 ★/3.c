#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define LINES_COUNT 2
#define LINE_LENGTH 2048
#define MAX_NUM_SIZE 4
#define MAX_OP_COUNT 512
#define MAX_INTERSECT_COUNT 512
#define GRID_SIZE_X 65536
#define GRID_SIZE_Y 65536
#define START 32768

#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'

int calc_manhattan(int p1, int p2, int q1, int q2)
{
    return abs(p1 - q1) + abs(p2 - q2);
}

void fill_2d_arr(int arr[][2], int x, int val)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            arr[i][j] = val;
        }
    }
}

void read_file(const char *fp, char lines[LINES_COUNT][LINE_LENGTH])
{
    FILE *fh;
    fh = fopen(fp, "r");

    char buffer[LINE_LENGTH];
    int line_pos = 0;

    while (fgets(buffer, LINE_LENGTH, fh))
    {
        strcpy(lines[line_pos], buffer);
        line_pos++;
    }

    fclose(fh);
}

void add_intersect(int i[MAX_INTERSECT_COUNT][2], int *ic, int x, int y)
{
    i[*ic][0] = x;
    i[*ic][1] = y;
    (*ic)++;
}

int parse_num(char lines[LINES_COUNT][LINE_LENGTH], int *cursor, int line_pos, char eol)
{
    char num_s[MAX_NUM_SIZE] = {"\0"};
    int num_cursor = 0;
    (*cursor)++;
    while (lines[line_pos][*cursor] != eol && lines[line_pos][*cursor] != ',')
    {
        num_s[num_cursor] = lines[line_pos][*cursor];
        (*cursor)++;
        num_cursor++;
    }
    num_s[num_cursor] = '\0';
    return (int)strtol(num_s, NULL, 10);
}

void part_1(char lines[LINES_COUNT][LINE_LENGTH])
{
    int op_count = 0;
    int path[MAX_OP_COUNT][2];
    fill_2d_arr(path, MAX_OP_COUNT, START);
    bool(*occupied)[GRID_SIZE_Y] = malloc(sizeof(bool) * GRID_SIZE_X * GRID_SIZE_Y);
    for (int cursor = 0; lines[0][cursor] != '\0'; cursor++)
    {
        if (cursor > 0)
        {
            memcpy(path[op_count], path[op_count - 1], sizeof(int) * 2);
        }
        char op = lines[0][cursor];
        int num = parse_num(lines, &cursor, 0, '\n');
        switch (op)
        {
        case UP:
            for (int i = path[op_count][1]; i <= path[op_count][1] + num; i++)
            {
                occupied[path[op_count][0]][i] = true;
            }
            path[op_count][1] += num;
            break;
        case DOWN:
            for (int i = path[op_count][1]; i >= path[op_count][1] - num; i--)
            {
                occupied[path[op_count][0]][i] = true;
            }
            path[op_count][1] -= num;
            break;
        case LEFT:
            for (int i = path[op_count][0]; i >= path[op_count][0] - num; i--)
            {
                occupied[i][path[op_count][1]] = true;
            }
            path[op_count][0] -= num;
            break;
        case RIGHT:
            for (int i = path[op_count][0]; i <= path[op_count][0] + num; i++)
            {
                occupied[i][path[op_count][1]] = true;
            }
            path[op_count][0] += num;
            break;
        default:
            printf("error: unknown operation: %c\n", op);
            exit(1);
        }
        op_count++;
    }

    op_count = 0;
    int path_2[MAX_OP_COUNT][2];
    int intersect[MAX_INTERSECT_COUNT][2];
    int intersect_count = 0;
    fill_2d_arr(path_2, MAX_OP_COUNT, START);
    fill_2d_arr(intersect, MAX_INTERSECT_COUNT, START);

    for (int cursor = 0; lines[1][cursor] != '\0'; cursor++)
    {
        if (cursor > 0)
        {
            memcpy(path_2[op_count], path_2[op_count - 1], sizeof(int) * 2);
        }
        char op = lines[1][cursor];
        int num = parse_num(lines, &cursor, 1, '\0');
        switch (op)
        {
        case UP:
            for (int i = path_2[op_count][1]; i <= path_2[op_count][1] + num; i++)
            {
                if (occupied[path_2[op_count][0]][i])
                {
                    add_intersect(intersect, &intersect_count, path_2[op_count][0], i);
                }
            }
            path_2[op_count][1] += num;
            break;
        case DOWN:
            for (int i = path_2[op_count][1]; i >= path_2[op_count][1] - num; i--)
            {
                if (occupied[path_2[op_count][0]][i])
                {
                    add_intersect(intersect, &intersect_count, path_2[op_count][0], i);
                }
            }
            path_2[op_count][1] -= num;
            break;
        case LEFT:
            for (int i = path_2[op_count][0]; i >= path_2[op_count][0] - num; i--)
            {
                if (occupied[i][path_2[op_count][1]])
                {
                    add_intersect(intersect, &intersect_count, i, path_2[op_count][1]);
                }
            }
            path_2[op_count][0] -= num;
            break;
        case RIGHT:
            for (int i = path_2[op_count][0]; i <= path_2[op_count][0] + num; i++)
            {
                if (occupied[i][path_2[op_count][1]])
                {
                    add_intersect(intersect, &intersect_count, i, path_2[op_count][1]);
                }
            }
            path_2[op_count][0] += num;
            break;
        default:
            printf("error: unknown operation: %c\n", op);
            exit(1);
        }
        op_count++;
    }
    int result = INT_MAX;
    for (int i = 0; i < MAX_INTERSECT_COUNT; i++)
    {
        if (intersect[i][0] == START && intersect[i][1] == START)
        {
            continue;
        }
        int distance = calc_manhattan(START, START, intersect[i][0], intersect[i][1]);
        if (result > distance)
        {
            result = distance;
        }
    }
    printf("part 1: %d\n", result);
}

int main()
{
    char lines[LINES_COUNT][LINE_LENGTH] = {"\0"};
    read_file("input.txt", lines);
    part_1(lines);
}
