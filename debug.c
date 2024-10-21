#include <stdio.h>
#include <stdlib.h>

void place(int n, int salon[n][n], int b, int c, int *result);
void placeFirstGang(int n, int salon[n][n], int index, int firstGang, int secondGang, int *result);
void placeSecondGang(int n, int salon[n][n], int index, int secondGang, int *result);
int canPlace(int n, int salon[n][n], int row, int col, int gang);
int checkResult(int n, int salon[n][n]);

int main(int argc, char *argv[])
{
    int n = atof(argv[1]); // salon dimensions n x n
    int b = atof(argv[2]); // num bigodudos
    int c = atof(argv[3]); // num capetas

    int salon[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            salon[i][j] = 0;
    }

    int result = 0;

    place(n, salon, b, c, &result);

    printf("%d\n", result);

    return 0;
}

void place(int n, int salon[n][n], int b, int c, int *result)
{
    int firstGang = b < c ? b : c;
    int secondGang = b < c ? c : b;

    for (int i = 0; i < n * n; i++)
        placeFirstGang(n, salon, i, firstGang, secondGang, result);
}

void placeFirstGang(int n, int salon[n][n], int index, int firstGang, int secondGang, int *result)
{
    if (index >= n * n)
        return;

    int row = index / n;
    int col = index % n;

    if (!canPlace(n, salon, row, col, 1))
        return;
    else
    {
        salon[row][col] = 1;
        firstGang -= 1;
        if (firstGang == 0)
        {
            for (int i = 0; i < n * n; i++)
                placeSecondGang(n, salon, i, secondGang, result);
        }
    }

    if (firstGang != 0)
    {
        for (int i = index + 1; i < n * n; i++)
            placeFirstGang(n, salon, i, firstGang, secondGang, result);
    }

    salon[row][col] = 0;
}

void placeSecondGang(int n, int salon[n][n], int index, int secondGang, int *result)
{
    if (index > n * n)
        return;

    int row = index / n;
    int col = index % n;

    if (!canPlace(n, salon, row, col, 2))
        return;
    else
    {
        salon[row][col] = 2;
        secondGang -= 1;

        if (secondGang == 0)
        {
            if (checkResult(n, salon))
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                        printf("%d ", salon[i][j]);
                    printf("\n");
                }
                printf("-----\n");
                *result += 1;
            }
        }
    }

    if (secondGang != 0)
    {
        for (int i = index + 1; i < n * n; i++)
            placeSecondGang(n, salon, i, secondGang, result);
    }

    salon[row][col] = 0;
}

int canPlace(int n, int salon[n][n], int row, int col, int gang)
{
    if (salon[row][col] != 0)
        return 0;

    if (gang == 1)
    {
        if (row - 1 >= 0 && salon[row - 1][col] == 1)
            return 0;

        if (col - 1 >= 0 && salon[row][col - 1] == 1)
            return 0;

        if (row - 1 >= 0 && col - 1 >= 0 && salon[row - 1][col - 1] == 1)
            return 0;

        if (row - 1 >= 0 && col + 1 < n && salon[row - 1][col + 1] == 1)
            return 0;

        if (row + 1 < n && salon[row + 1][col] == 1)
            return 0;

        if (col + 1 < n && salon[row][col + 1] == 1)
            return 0;

        if (row + 1 < n && col + 1 < n && salon[row + 1][col + 1] == 1)
            return 0;

        if (row + 1 < n && col - 1 >= 0 && salon[row + 1][col - 1] == 1)
            return 0;
    }
    else
    {
        int see = 0;

        for (int i = row - 1; i >= 0; i--)
        {
            if (salon[i][col] == 2)
                return 0;

            if (salon[i][col] == 1)
            {
                see += 1;
                break;
            }
        }

        for (int i = row + 1; i < n; i++)
        {
            if (salon[i][col] == 2)
                return 0;

            if (salon[i][col] == 1)
            {
                see += 1;
                break;
            }
        }

        for (int i = col - 1; i >= 0; i--)
        {
            if (salon[row][i] == 2)
                return 0;

            if (salon[row][i] == 1)
            {
                see += 1;
                break;
            }
        }

        for (int i = col + 1; i < n; i++)
        {
            if (salon[row][i] == 2)
                return 0;

            if (salon[row][i] == 1)
            {
                see += 1;
                break;
            }
        }

        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        {
            if (salon[i][j] == 2)
                return 0;

            if (salon[i][j] == 1)
            {
                see += 1;
                break;
            }
        }

        for (int i = row + 1, j = col + 1; i < n && j < n; i++, j++)
        {
            if (salon[i][j] == 2)
                return 0;

            if (salon[i][j] == 1)
            {
                see += 1;
                break;
            }
        }

        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        {
            if (salon[i][j] == 2)
                return 0;

            if (salon[i][j] == 1)
            {
                see += 1;
                break;
            }
        }

        for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--)
        {
            if (salon[i][j] == 2)
                return 0;

            if (salon[i][j] == 1)
            {
                see += 1;
                break;
            }
        }

        if (see < 2)
            return 0;
    }

    return 1;
}

int checkResult(int n, int salon[n][n])
{
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (salon[row][col] == 1)
            {
                for (int i = row - 1; i >= 0; i--)
                {
                    if (salon[i][col] == 1)
                        return 0;

                    if (salon[i][col] == 2)
                        break;
                }

                for (int i = row + 1; i < n; i++)
                {
                    if (salon[i][col] == 1)
                        return 0;

                    if (salon[i][col] == 2)
                        break;
                }

                for (int i = col - 1; i >= 0; i--)
                {
                    if (salon[row][i] == 1)
                        return 0;

                    if (salon[row][i] == 2)
                        break;
                }

                for (int i = col + 1; i < n; i++)
                {
                    if (salon[row][i] == 1)
                        return 0;

                    if (salon[row][i] == 2)
                        break;
                }

                for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
                {
                    if (salon[i][j] == 1)
                        return 0;

                    if (salon[i][j] == 2)
                        break;
                }

                for (int i = row + 1, j = col + 1; i < n && j < n; i++, j++)
                {
                    if (salon[i][j] == 1)
                        return 0;

                    if (salon[i][j] == 2)
                        break;
                }

                for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
                {
                    if (salon[i][j] == 1)
                        return 0;

                    if (salon[i][j] == 2)
                        break;
                }

                for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--)
                {
                    if (salon[i][j] == 1)
                        return 0;

                    if (salon[i][j] == 2)
                        break;
                }
            }
        }
    }

    return 1;
}