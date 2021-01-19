#include <stdio.h>
#include <stdlib.h>

int adjacent_digits(char *num)
{
    return num[0] == num[1] || num[1] == num[2] || num[2] == num[3] || num[3] == num[4] || num[4] == num[5];
}

// ChomikowyPedziwiatr && gooddoog \ AYAYA /
int adjacent_digits_2(char *num)
{
    char prev = '\0';
    int combo = 0;
    for (int i = 0; num[i] != '\0'; i++)
    {
        if (num[i] == prev)
        {
            combo++;
        }
        else
        {
            if (combo == 2)
            {
                return 1;
            }
            combo = 1;
        }
        prev = num[i];
    }
    return combo == 2;
}

int never_decrease(char *num)
{
    char prev_num = num[0];
    for (int i = 1; num[i] != '\0'; i++)
    {
        if (num[i] < prev_num)
        {
            return 0;
        }
        prev_num = num[i];
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("error: no input\n");
        return 1;
    }
    char *inp = argv[1];
    char start_s[7] = {inp[0], inp[1], inp[2], inp[3], inp[4], inp[5], '\0'};
    char end_s[7] = {inp[7], inp[8], inp[9], inp[10], inp[11], inp[12], '\0'};

    int start = (int)strtol(start_s, NULL, 10);
    int end = (int)strtol(end_s, NULL, 10);

    int p1 = 0;
    int p2 = 0;

    while (start <= end)
    {
        char num[7] = {0};
        sprintf(num, "%d", start);

        if (never_decrease(num))
        {
            if (adjacent_digits(num))
            {
                p1++;
            }
            if (adjacent_digits_2(num))
            {
                p2++;
            }
        }
        start++;
    }

    printf("part 1: %d\npart 2: %d\n", p1, p2);
}