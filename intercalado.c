#include <stdio.h>
#include <stdlib.h>

void place(int n, int salon[n][n], int b, int c, int *result);
void placeGang(int n, int salon[n][n], int index, int firstGang, int secondGang, int gang, int *result);
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
    {
        placeGang(n, salon, i, firstGang, secondGang, 1, result);
        placeGang(n, salon, i, firstGang, secondGang, 2, result);
    }
}

void placeGang(int n, int salon[n][n], int index, int firstGang, int secondGang, int gang, int *result)
{
    if (index >= n * n)
        return;

    int row = index / n;
    int col = index % n;

    if (!canPlace(n, salon, row, col, gang))
        return;
    else
    {
        salon[row][col] = gang;
        if (gang == 1)
            firstGang -= 1;
        else
            secondGang -= 1;

        if (firstGang == 0 && secondGang == 0 && checkResult(n, salon))
            *result += 1;
    }

    if (firstGang != 0)
    {
        for (int i = index + 1; i < n * n; i++)
            placeGang(n, salon, i, firstGang, secondGang, 1, result);
    }

    if (secondGang != 0)
    {
        for (int i = index + 1; i < n * n; i++)
            placeGang(n, salon, i, firstGang, secondGang, 2, result);
    }

    salon[row][col] = 0;
}

int canPlace(int n, int salon[n][n], int row, int col, int gang)
{
    if (salon[row][col] != 0)
        return 0;

    int oppositeGang = gang == 1 ? 2 : 1;

    for (int i = row - 1; i >= 0; i--)
    {
        if (salon[i][col] == gang)
            return 0;

        if (salon[i][col] == oppositeGang)
            break;
    }

    for (int i = row + 1; i < n; i++)
    {
        if (salon[i][col] == gang)
            return 0;

        if (salon[i][col] == oppositeGang)
            break;
    }

    for (int i = col - 1; i >= 0; i--)
    {
        if (salon[row][i] == gang)
            return 0;

        if (salon[row][i] == oppositeGang)
            break;
    }

    for (int i = col + 1; i < n; i++)
    {
        if (salon[row][i] == gang)
            return 0;

        if (salon[row][i] == oppositeGang)
            break;
    }

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (salon[i][j] == gang)
            return 0;

        if (salon[i][j] == oppositeGang)
            break;
    }

    for (int i = row + 1, j = col + 1; i < n && j < n; i++, j++)
    {
        if (salon[i][j] == gang)
            return 0;

        if (salon[i][j] == oppositeGang)
            break;
    }

    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
    {
        if (salon[i][j] == gang)
            return 0;

        if (salon[i][j] == oppositeGang)
            break;
    }

    for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--)
    {
        if (salon[i][j] == gang)
            return 0;

        if (salon[i][j] == oppositeGang)
            break;
    }

    return 1;
}

int checkResult(int n, int salon[n][n])
{
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (salon[row][col] != 0)
            {
                int gang = salon[row][col];
                int oppositeGang = gang == 1 ? 2 : 1;

                int see = 0;

                for (int i = row - 1; i >= 0; i--)
                {
                    if (salon[i][col] == gang)
                        return 0;

                    if (salon[i][col] == oppositeGang)
                    {
                        see += 1;
                        break;
                    }
                }

                for (int i = row + 1; i < n; i++)
                {
                    if (salon[i][col] == gang)
                        return 0;

                    if (salon[i][col] == oppositeGang)
                    {
                        see += 1;
                        break;
                    }
                }

                for (int i = col - 1; i >= 0; i--)
                {
                    if (salon[row][i] == gang)
                        return 0;

                    if (salon[row][i] == oppositeGang)
                    {
                        see += 1;
                        break;
                    }
                }

                for (int i = col + 1; i < n; i++)
                {
                    if (salon[row][i] == gang)
                        return 0;

                    if (salon[row][i] == oppositeGang)
                    {
                        see += 1;
                        break;
                    }
                }

                for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
                {
                    if (salon[i][j] == gang)
                        return 0;

                    if (salon[i][j] == oppositeGang)
                    {
                        see += 1;
                        break;
                    }
                }

                for (int i = row + 1, j = col + 1; i < n && j < n; i++, j++)
                {
                    if (salon[i][j] == gang)
                        return 0;

                    if (salon[i][j] == oppositeGang)
                    {
                        see += 1;
                        break;
                    }
                }

                for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
                {
                    if (salon[i][j] == gang)
                        return 0;

                    if (salon[i][j] == oppositeGang)
                    {
                        see += 1;
                        break;
                    }
                }

                for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--)
                {
                    if (salon[i][j] == gang)
                        return 0;

                    if (salon[i][j] == oppositeGang)
                    {
                        see += 1;
                        break;
                    }
                }

                if (see < 2)
                    return 0;
            }
        }
    }

    return 1;
}