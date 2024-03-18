#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define rows 8
#define colm 8
void swappositionsai(char board[rows][colm], int bestvaluei, int bestvaluej, int bestvaluek, int bestvaluel, int check);
int minimax(char board[rows][colm], int depth, int i, int j, int k, int l, int ismax);
void bestmoves(char board[rows][colm]);
int maximum(int a, int b);
int minimum(int a, int b);
int maximum(int a, int b)
{
	return (a > b) ? a : b;
}
int minimum(int a, int b)
{
	return (a < b) ? a : b;
}
int evaluate(char board[rows][colm], int m, int n, int o, int p);
void printboard(char board[rows][colm])
{
	printf(" * * * * * * * * CHECKERS  BOARD * * * * * * * * * * *\n");
	printf(" *       0    1    2    3    4    5    6    7        *\n");
	printf(" *    ------------------------------------------     *\n");
	printf(" *  0 ||   || %c ||   || %c ||   || %c ||   || %c || 0   *\n", board[0][1], board[0][3], board[0][5], board[0][7]);
	printf(" *    ------------------------------------------     *\n");
	printf(" *  1 || %c ||   || %c ||   || %c ||   || %c ||   || 1   *\n", board[1][0], board[1][2], board[1][4], board[1][6]);
	printf(" *    ------------------------------------------     *\n");
	printf(" *  2 ||   || %c ||   || %c ||   || %c ||   || %c || 2   *\n", board[2][1], board[2][3], board[2][5], board[2][7]);
	printf(" *    ------------------------------------------     *\n");
	printf(" *  3 || %c ||   || %c ||   || %c ||   || %c ||   || 3   *\n", board[3][0], board[3][2], board[3][4], board[3][6]);
	printf(" *    ------------------------------------------     *\n");
	printf(" *  4 ||   || %c ||   || %c ||   || %c ||   || %c || 4   *\n", board[4][1], board[4][3], board[4][5], board[4][7]);
	printf(" *    ------------------------------------------     *\n");
	printf(" *  5 || %c ||   || %c ||   || %c ||   || %c ||   || 5   *\n", board[5][0], board[5][2], board[5][4], board[5][6]);
	printf(" *    ------------------------------------------     *\n");
	printf(" *  6 ||   || %c ||   || %c ||   || %c ||   || %c || 6   *\n", board[6][1], board[6][3], board[6][5], board[6][7]);
	printf(" *    ------------------------------------------     *\n");
	printf(" *  7 || %c ||   || %c ||   || %c ||   || %c ||   || 7   *\n", board[7][0], board[7][2], board[7][4], board[7][6]);
	printf(" *    ------------------------------------------     *\n");
	printf(" *       0    1    2    3    4    5    6    7        *\n");
	printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
}
void swappositions(char board[rows][colm], int i, int j, int k, int l)
{
	char temp;
	printf("Moved From: (%d-%d) to (%d-%d)\n", i, j, k, l);
	temp = board[i][j];
	board[i][j] = board[k][l];
	board[k][l] = temp;
}
void swapkings(char board[rows][colm], int i, int j, int k, int l)
{
	char temp;
	if (board[i][j] == 'w')
	{
		board[i][j] = 'W';
	}
	else if (board[i][j] == 'b')
	{
		board[i][j] = 'B';
	}
	temp = board[i][j];
	board[i][j] = board[k][l];
	board[k][l] = temp;
}
int checkforwin(char board[rows][colm])
{
	int flag = 0;
	int flag2 = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < colm; j++)
		{
			if (board[i][j] == 'w' || board[i][j] == 'W')
			{
				flag = 1;
			}
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < colm; j++)
		{
			if (board[i][j] == 'b' || board[i][j] == 'B')
			{
				flag2 = 1;
			}
		}
	}
	if (flag && flag2)
		return 0;
	if (!flag)
		return 2;
	if (!flag2)
		return 1;
}
int playersturn(char board[rows][colm], char str[50], int player, int i, int j, int k, int l)
{
	int jmpr;
	int jmpc;
	if (player == 50)
	{
		printf("%s's move was from (%d-%d) to (%d-%d)\n", str, i, j, k, l);
	}
	else if (player == 100)
	{
		printf("%s's move was from (%d-%d) to (%d-%d)\n", str, i, j, k, l);
	}
	if (i < 0 && rows <= i)
	{
		printf("Row is out of bound\n");
		return -1;
	}
	if (j < 0 && colm <= j)
	{
		printf("Column is out of bound\n");
		return -1;
	}
	if (k < 0 && rows <= k)
	{
		printf("Row is out of bound\n");
		return -1;
	}
	if (l < 0 && colm <= l)
	{
		printf("Column is out of bound\n");
		return -1;
	}
	if (player == 50)
	{
		if (board[i][j] != 'w' && board[i][j] != 'W')
		{
			printf("Move your own piece\n");
			return -1;
		}
	}
	else if (player == 100)
	{
		if (board[i][j] != 'b' && board[i][j] != 'B')
		{
			printf("Move your own piece\n");
			return -1;
		}
	}
	if (board[k][l] != ' ')
	{
		printf("You must move correctly\n");
		return -1;
	}
	if (player == 50)
	{
		if (i >= k && board[i][j] == 'w')
		{
			printf("%s must move down\n", str);
			return -1;
		}
	}
	else
	{
		if (i <= k && board[i][j] == 'b')
		{
			printf("%s must move up\n", str);
		}
	}
	if (i - k == -1 || i - k == 1)
	{
		if ((k == 7 || k == 0) && (l % 2 == 0 || l % 2 != 0) && (board[i][j] == 'w' || board[i][j] == 'b'))
		{
			swapkings(board, i, j, k, l);
			return 0;
		}
		if (j - l == 1 || j - l == -1)
		{
			swappositions(board, i, j, k, l);
			return 0;
		}
	}
	if (i - k == -2 || i - k == 2)
	{
		if (j - l == -2 || j - l == 2)
		{
			if (i < k)
			{
				jmpr = i + 1;
			}
			else
			{
				jmpr = i - 1;
			}
			if (j < l)
			{
				jmpc = j + 1;
			}
			else
			{
				jmpc = j - 1;
			}
			if (player == 50 && board[jmpr][jmpc] != 'b' && board[jmpr][jmpc] != 'B')
			{
				printf("Enemy is not at %d-%d\n", jmpr, jmpc);
				return -1;
			}
			if (player == 100 && board[jmpr][jmpc] != 'w' && board[jmpr][jmpc] != 'W')
			{
				printf("Enemy is not at %d-%d\n", jmpr, jmpc);
				return -1;
			}
			board[jmpr][jmpc] = ' ';
			if ((k == 7 || k == 0) && (l % 2 == 0 || l % 2 != 0) && (board[i][j] == 'w' || board[i][j] == 'b'))
			{
				swapkings(board, i, j, k, l);
				return 0;
			}
			swappositions(board, i, j, k, l);
			return 0;
		}
	}
	printf("You can only move diagonally\n");
	return -1;
}
void swappositionsai(char board[rows][colm], int bestvaluei, int bestvaluej, int bestvaluek, int bestvaluel, int check)
{
	char temp;
	if (check == 0)
	{
		if (board[bestvaluei][bestvaluej] == 'b' || board[bestvaluei][bestvaluej] == 'B')
		{
			if ((bestvaluei - bestvaluek == 1 || bestvaluei - bestvaluek == -1) && (bestvaluej - bestvaluel == 1 || bestvaluej - bestvaluel == -1))
			{
				temp = board[bestvaluei][bestvaluej];
				board[bestvaluei][bestvaluej] = board[bestvaluek][bestvaluel];
				board[bestvaluek][bestvaluel] = temp;
			}
		}
		if (board[bestvaluei][bestvaluej] == 'b' || board[bestvaluei][bestvaluej] == 'B')
		{
			if ((bestvaluei - bestvaluek == -2) && (bestvaluej - bestvaluel == -2))
			{
				board[bestvaluei + 1][bestvaluej + 1] = ' ';
				temp = board[bestvaluei][bestvaluej];
				board[bestvaluei][bestvaluej] = board[bestvaluek][bestvaluel];
				board[bestvaluek][bestvaluel] = temp;
			}
			else if ((bestvaluei - bestvaluek == -2) && (bestvaluej - bestvaluel == 2))
			{
				board[bestvaluei + 1][bestvaluej - 1] = ' ';
				temp = board[bestvaluei][bestvaluej];
				board[bestvaluei][bestvaluej] = board[bestvaluek][bestvaluel];
				board[bestvaluek][bestvaluel] = temp;
			}
			else if ((bestvaluei - bestvaluek == 2) && (bestvaluej - bestvaluel == -2))
			{
				board[bestvaluei - 1][bestvaluej + 1] = ' ';
				temp = board[bestvaluei][bestvaluej];
				board[bestvaluei][bestvaluej] = board[bestvaluek][bestvaluel];
				board[bestvaluek][bestvaluel] = temp;
			}
			else if ((bestvaluei - bestvaluek == 2) && (bestvaluej - bestvaluel == 2))
			{
				board[bestvaluei - 1][bestvaluej - 1] = ' ';
				temp = board[bestvaluei][bestvaluej];
				board[bestvaluei][bestvaluej] = board[bestvaluek][bestvaluel];
				board[bestvaluek][bestvaluel] = temp;
			}
		}
	}
	else if (check == 1)
	{
		if (board[bestvaluei][bestvaluej] == 'b')
		{
			if ((bestvaluei - bestvaluek == 1 || bestvaluei - bestvaluek == -1) && (bestvaluej - bestvaluel == 1 || bestvaluej - bestvaluel == -1))
			{
				board[bestvaluei][bestvaluej] = 'B';
				temp = board[bestvaluei][bestvaluej];
				board[bestvaluei][bestvaluej] = board[bestvaluek][bestvaluel];
				board[bestvaluek][bestvaluel] = temp;
			}
			else if ((bestvaluei - bestvaluek == -2) && (bestvaluej - bestvaluel == -2))
			{
				board[bestvaluei + 1][bestvaluej + 1] = ' ';
				board[bestvaluei][bestvaluej] = 'B';
				temp = board[bestvaluei][bestvaluej];
				board[bestvaluei][bestvaluej] = board[bestvaluek][bestvaluel];
				board[bestvaluek][bestvaluel] = temp;
			}
			else if ((bestvaluei - bestvaluek == -2) && (bestvaluej - bestvaluel == 2))
			{
				board[bestvaluei + 1][bestvaluej - 1] = ' ';
				board[bestvaluei][bestvaluej] = 'B';
				temp = board[bestvaluei][bestvaluej];
				board[bestvaluei][bestvaluej] = board[bestvaluek][bestvaluel];
				board[bestvaluek][bestvaluel] = temp;
			}
			else if ((bestvaluei - bestvaluek == 2) && (bestvaluej - bestvaluel == -2))
			{
				board[bestvaluei - 1][bestvaluej + 1] = ' ';
				board[bestvaluei][bestvaluej] = 'B';
				temp = board[bestvaluei][bestvaluej];
				board[bestvaluei][bestvaluej] = board[bestvaluek][bestvaluel];
				board[bestvaluek][bestvaluel] = temp;
			}
			else if ((bestvaluei - bestvaluek == 2) && (bestvaluej - bestvaluel == 2))
			{
				board[bestvaluei - 1][bestvaluej - 1] = ' ';
				board[bestvaluei][bestvaluej] = 'B';
				temp = board[bestvaluei][bestvaluej];
				board[bestvaluei][bestvaluej] = board[bestvaluek][bestvaluel];
				board[bestvaluek][bestvaluel] = temp;
			}
		}
	}
	return;
}
void bestmoves(char board[rows][colm])
{
	int bestval = INT_MIN;
	int bestvali = -1;
	int bestvalj = -1;
	int bestvalk = -1;
	int bestvall = -1;
	int moveval;
	int check;
	for (int i = rows - 1; i >= 0; i--)
	{
		for (int j = colm - 1; j >= 0; j--)
		{
			if (board[i][j] == 'B' || board[i][j] == 'b')
			{
				if (((i == 2 && j % 2 != 0) && (j < 6) && board[i][j] == 'b') && (board[i - 1][j + 1] == 'W'))
				{
					if (board[i - 2][j + 2] == ' ')
					{
						board[i - 2][j + 2] = 'B';
						board[i - 1][j + 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i - 2, j + 2, 0);
						board[i][j] = 'b';
						board[i - 2][j + 2] = ' ';
						board[i - 1][j + 1] = 'W';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j + 2;
							check = 1;
						}
					}
				}
				if (((i == 2 && j % 2 != 0) && (j < 6) && board[i][j] == 'b') && (board[i - 1][j + 1] == 'w'))
				{
					if (board[i - 2][j + 2] == ' ')
					{
						board[i - 2][j + 2] = 'B';
						board[i - 1][j + 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i - 2, j + 2, 0);
						board[i][j] = 'b';
						board[i - 2][j + 2] = ' ';
						board[i - 1][j + 1] = 'w';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j + 2;
							check = 1;
						}
					}
				}
				if (((i == 2 && j % 2 != 0) && (j > 2) && board[i][j] == 'b') && (board[i - 1][j - 1] == 'w'))
				{
					if (board[i - 2][j - 2] == ' ')
					{
						board[i - 2][j - 2] = 'B';
						board[i - 1][j - 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i - 2, j - 2, 0);
						board[i][j] = 'b';
						board[i - 2][j - 2] = ' ';
						board[i - 1][j - 1] = 'w';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j - 2;
							check = 1;
						}
					}
				}
				if (((i == 2 && j % 2 != 0) && (j > 2) && board[i][j] == 'b') && (board[i - 1][j - 1] == 'W'))
				{
					if (board[i - 2][j - 2] == ' ')
					{
						board[i - 2][j - 2] = 'B';
						board[i - 1][j - 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i - 2, j - 2, 0);
						board[i][j] = 'b';
						board[i - 2][j - 2] = ' ';
						board[i - 1][j - 1] = 'W';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j - 2;
							check = 1;
						}
					}
				}
				if ((i > 1 && (j < colm - 2 && i != 2)) && board[i - 1][j + 1] == 'w' && board[i][j] == 'b')
				{
					if (board[i - 2][j + 2] == ' ')
					{
						board[i - 2][j + 2] = 'b';
						board[i - 1][j + 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i - 2, j + 2, 0);
						board[i - 2][j + 2] = ' ';
						board[i - 1][j + 1] = 'w';
						board[i][j] = 'b';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j + 2;
							check = 0;
						}
					}
				}
				if ((i > 1 && (j > 1 && i != 2)) && board[i - 1][j - 1] == 'w' && board[i][j] == 'b')
				{
					if (board[i - 2][j - 2] == ' ')
					{
						board[i - 2][j - 2] = 'b';
						board[i - 1][j - 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i - 2, j - 2, 0);
						board[i - 2][j - 2] = ' ';
						board[i - 1][j - 1] = 'w';
						board[i][j] = 'b';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j - 2;
							check = 0;
						}
					}
				}
				if ((i > 1 && (j > 1 && i != 2)) && board[i - 1][j - 1] == 'W' && board[i][j] == 'b')
				{
					if (board[i - 2][j - 2] == ' ')
					{
						board[i - 2][j - 2] = 'b';
						board[i - 1][j - 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i - 2, j - 2, 0);
						board[i - 2][j - 2] = ' ';
						board[i - 1][j - 1] = 'W';
						board[i][j] = 'b';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j - 2;
							check = 0;
						}
					}
				}
				if ((i > 1 && (j < colm - 2 && i != 2)) && board[i - 1][j + 1] == 'W' && board[i][j] == 'b')
				{
					if (board[i - 2][j + 2] == ' ')
					{
						board[i - 2][j + 2] = 'b';
						board[i - 1][j + 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i - 2, j + 2, 0);
						board[i - 2][j + 2] = ' ';
						board[i - 1][j + 1] = 'W';
						board[i][j] = 'b';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j + 2;
							check = 0;
						}
					}
				}
				if (((i > 0 && (j < colm - 1 && i != 1)) && board[i - 1][j + 1] == ' ' && board[i][j] == 'b') || (((i == 2 && ((j < colm - 1 && i != 1) && (j % 2 != 0)) && board[i][j] == 'b') && (board[i - 1][j + 1] == ' '))))
				{
					board[i - 1][j + 1] = 'b';
					board[i][j] = ' ';
					moveval = minimax(board, 0, i, j, i - 1, j + 1, 0);
					board[i - 1][j + 1] = ' ';
					board[i][j] = 'b';
					if (moveval > bestval)
					{
						bestval = moveval;
						bestvali = i;
						bestvalj = j;
						bestvalk = i - 1;
						bestvall = j + 1;
						check = 0;
					}
				}
				if (((i > 0 && (j > 0 && i != 1)) && board[i - 1][j - 1] == ' ' && board[i][j] == 'b') || (((i == 2 && j % 2 != 0) && (j > 0) && board[i][j] == 'b') && (board[i - 1][j - 1] == ' ')))
				{
					board[i - 1][j - 1] = 'b';
					board[i][j] = ' ';
					moveval = minimax(board, 0, i, j, i - 1, j - 1, 0);
					board[i - 1][j - 1] = ' ';
					board[i][j] = 'b';
					if (moveval > bestval)
					{
						bestval = moveval;
						bestvali = i;
						bestvalj = j;
						bestvalk = i - 1;
						bestvall = j - 1;
						check = 0;
					}
				}
				if (((i == 1 && j % 2 == 0) && (j < colm - 1) && board[i][j] == 'b'))
				{
					if (board[i - 1][j + 1] == ' ')
					{
						board[i][j] = ' ';
						board[i - 1][j + 1] = 'B';
						moveval = minimax(board, 0, i, j, i - 1, j + 1, 0);
						board[i][j] = 'b';
						board[i - 1][j + 1] = ' ';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 1;
							bestvall = j + 1;
							check = 1;
						}
					}
				}
				if (((i == 1 && j % 2 == 0) && (j > 1) && board[i][j] == 'b'))
				{
					if (board[i - 1][j - 1] == ' ')
					{
						board[i][j] = ' ';
						board[i - 1][j - 1] = 'B';
						moveval = minimax(board, 0, i, j, i - 1, j - 1, 0);
						board[i][j] = 'b';
						board[i - 1][j - 1] = ' ';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 1;
							bestvall = j - 1;
							check = 1;
						}
					}
				}
				if ((i > 1 && j < colm - 2) && board[i - 1][j + 1] == 'w' && board[i][j] == 'B')
				{
					if (board[i - 2][j + 2] == ' ')
					{
						board[i - 2][j + 2] = 'B';
						board[i - 1][j + 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i - 2, j + 2, 0);
						board[i - 2][j + 2] = ' ';
						board[i - 1][j + 1] = 'w';
						board[i][j] = 'B';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j + 2;
							check = 0;
						}
					}
				}
				if ((i > 1 && j > 1) && board[i - 1][j - 1] == 'w' && board[i][j] == 'B')
				{
					if (board[i - 2][j - 2] == ' ')
					{
						board[i - 2][j - 2] = 'B';
						board[i - 1][j - 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i - 2, j - 2, 0);
						board[i - 2][j - 2] = ' ';
						board[i - 1][j - 1] = 'w';
						board[i][j] = 'B';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j - 2;
							check = 0;
						}
					}
				}
				if ((i > 1 && j < colm - 2) && board[i - 1][j + 1] == 'W' && board[i][j] == 'B')
				{
					if (board[i - 2][j + 2] == ' ')
					{
						board[i - 2][j + 2] = 'B';
						board[i - 1][j + 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i - 2, j + 2, 0);
						board[i - 2][j + 2] = ' ';
						board[i - 1][j + 1] = 'W';
						board[i][j] = 'B';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j + 2;
							check = 0;
						}
					}
				}
				if ((i > 1 && j > 1) && board[i - 1][j - 1] == 'W' && board[i][j] == 'B')
				{
					if (board[i - 2][j - 2] == ' ')
					{
						board[i - 2][j - 2] = 'B';
						board[i - 1][j - 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i - 2, j - 2, 0);
						board[i - 2][j - 2] = ' ';
						board[i - 1][j - 1] = 'W';
						board[i][j] = 'B';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j - 2;
							check = 0;
						}
					}
				}
				if ((i < rows - 2 && j < colm - 2) && board[i + 1][j + 1] == 'w' && board[i][j] == 'B')
				{
					if (board[i + 2][j + 2] == ' ')
					{
						board[i + 2][j + 2] = 'B';
						board[i + 1][j + 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i + 2, j + 2, 0);
						board[i + 2][j + 2] = ' ';
						board[i + 1][j + 1] = 'w';
						board[i][j] = 'B';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i + 2;
							bestvall = j + 2;
							check = 0;
						}
					}
				}
				if ((i < rows - 2 && j > 1) && board[i + 1][j - 1] == 'w' && board[i][j] == 'B')
				{
					if (board[i + 2][j - 2] == ' ')
					{
						board[i + 2][j - 2] = 'B';
						board[i + 1][j - 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i + 2, j - 2, 0);
						board[i + 2][j - 2] = ' ';
						board[i + 1][j - 1] = 'w';
						board[i][j] = 'B';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j - 2;
							check = 0;
						}
					}
				}
				if ((i < rows - 2 && j < colm - 2) && board[i + 1][j + 1] == 'W' && board[i][j] == 'B')
				{
					if (board[i + 2][j + 2] == ' ')
					{
						board[i + 2][j + 2] = 'B';
						board[i + 1][j + 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i + 2, j + 2, 0);
						board[i + 2][j + 2] = ' ';
						board[i + 1][j + 1] = 'W';
						board[i][j] = 'B';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i + 2;
							bestvall = j + 2;
							check = 0;
						}
					}
				}
				if ((i < rows - 2 && j > 1) && board[i + 1][j - 1] == 'W' && board[i][j] == 'B')
				{
					if (board[i + 2][j - 2] == ' ')
					{
						board[i + 2][j - 2] = 'B';
						board[i + 1][j - 1] = ' ';
						board[i][j] = ' ';
						moveval = minimax(board, 0, i, j, i + 2, j - 2, 0);
						board[i + 2][j - 2] = ' ';
						board[i + 1][j - 1] = 'W';
						board[i][j] = 'B';
						if (moveval > bestval)
						{
							bestval = moveval;
							bestvali = i;
							bestvalj = j;
							bestvalk = i - 2;
							bestvall = j - 2;
							check = 0;
						}
					}
				}
				if ((i > 0 && j < colm - 1) && board[i - 1][j + 1] == ' ' && board[i][j] == 'B')
				{
					board[i - 1][j + 1] = 'B';
					board[i][j] = ' ';
					moveval = minimax(board, 0, i, j, i - 1, j + 1, 0);
					board[i - 1][j + 1] = ' ';
					board[i][j] = 'B';
					if (moveval > bestval)
					{
						bestval = moveval;
						bestvali = i;
						bestvalj = j;
						bestvalk = i - 1;
						bestvall = j + 1;
						check = 0;
					}
				}
				if ((i > 0 && j > 0) && board[i - 1][j - 1] == ' ' && board[i][j] == 'B')
				{
					board[i - 1][j - 1] = 'B';
					board[i][j] = ' ';
					moveval = minimax(board, 0, i, j, i - 1, j - 1, 0);
					board[i - 1][j - 1] = ' ';
					board[i][j] = 'B';
					if (moveval > bestval)
					{
						bestval = moveval;
						bestvali = i;
						bestvalj = j;
						bestvalk = i - 1;
						bestvall = j - 1;
						check = 0;
					}
				}
				if ((i < rows - 1 && j < colm - 1) && board[i + 1][j + 1] == ' ' && board[i][j] == 'B')
				{
					board[i + 1][j + 1] = 'B';
					board[i][j] = ' ';
					moveval = minimax(board, 0, i, j, i + 1, j + 1, 0);
					board[i + 1][j + 1] = ' ';
					board[i][j] = 'B';
					if (moveval > bestval)
					{
						bestval = moveval;
						bestvali = i;
						bestvalj = j;
						bestvalk = i + 1;
						bestvall = j + 1;
						check = 0;
					}
				}
				if ((i < rows - 1 && j > 0) && board[i + 1][j - 1] == ' ' && board[i][j] == 'B')
				{
					board[i + 1][j - 1] = 'B';
					board[i][j] = ' ';
					moveval = minimax(board, 0, i, j, i + 1, j - 1, 0);
					board[i + 1][j - 1] = ' ';
					board[i][j] = 'B';
					if (moveval > bestval)
					{
						bestval = moveval;
						bestvali = i;
						bestvalj = j;
						bestvalk = i + 1;
						bestvall = j - 1;
						check = 0;
					}
				}
			}
		}
	}
	swappositionsai(board, bestvali, bestvalj, bestvalk, bestvall, check);
}
int main()
{
	// PIECE X (W REPRESENTS KING) represents Player 1 and O (K REPRESENTS KING) represents Player Two
	// For ONE VS BOT X represents Player and O represents BOT
	int i, j, k, l;
	char str[20];
	char str2[20];
	char str3[20];
	int flag;
	char board[rows][colm] = {
		{'E', 'w', 'E', 'w', 'E', 'w', 'E', 'w'},
		{'w', 'E', 'w', 'E', 'w', 'E', 'w', 'E'},
		{'E', 'w', 'E', 'w', 'E', 'w', 'E', 'w'},
		{' ', 'E', ' ', 'E', ' ', 'E', ' ', 'E'},
		{'E', ' ', 'E', ' ', 'E', ' ', 'E', ' '},
		{'b', 'E', 'b', 'E', 'b', 'E', 'b', 'E'},
		{'E', 'b', 'E', 'b', 'E', 'b', 'E', 'b'},
		{'b', 'E', 'b', 'E', 'b', 'E', 'b', 'E'}};
	printf("ENTER 1 FOR TWO PLAYERS\nENTER 2 FOR ONE VS BOT\n");
	scanf("%d", &flag);
	getchar();
	if (flag == 1)
	{
		printf("Enter Player 1 Name\n");
		fgets(str, 20, stdin);
		printf("Enter Player 2 Name\n");
		fgets(str2, 20, stdin);
		printf("PIECE w (W REPRESENTS KING) represents %s\n", str);
		printf("While b (B REPRESENTS KING) represents %s\n", str2);
		while (1)
		{
			if (checkforwin(board) == 2)
			{
				printf("%s WINS\n", str2);
				break;
			}
			printboard(board);
			while (1)
			{
				puts(str);
				printf("Enter Row and column to select piece\n");
				scanf("%d%d", &i, &j);
				printf("MOVE TO:\n");
				printf("Enter Row and column to move piece\n");
				scanf("%d%d", &k, &l);
				if (playersturn(board, str, 50, i, j, k, l) == 0)
					break;
				printf("Invalid Move\n");
			}
			if (checkforwin(board) == 1)
			{
				printf("%s WINS\n", str);
				break;
			}
			printboard(board);
			while (1)
			{
				puts(str2);
				printf("Enter Row and column to select piece\n");
				scanf("%d%d", &i, &j);
				printf("MOVE TO:\n");
				printf("Enter Row and column to move piece\n");
				scanf("%d%d", &k, &l);
				if (playersturn(board, str2, 100, i, j, k, l) == 0)
					break;
				printf("Invalid Move\n");
			}
		}
	}
	else if (flag == 2)
	{
		printf("ENTER PLAYER NAME\n");
		scanf("%[^\n]s", str3);
		while (1)
		{
			if (checkforwin(board) == 2)
			{
				printf("AI WINS\n");
				printboard(board);
				break;
			}
			printboard(board);
			while (1)
			{
				puts(str3);
				printf("Enter Row and column to select white piece\n");
				scanf("%d%d", &i, &j);
				printf("MOVE TO:\n");
				printf("Enter Row and column to move piece\n");
				scanf("%d%d", &k, &l);
				if (playersturn(board, str3, 50, i, j, k, l) == 0)
					break;
				printf("Invalid Move\n");
			}
			if (checkforwin(board) == 1)
			{
				printf("%s WINS\n", str3);
				printboard(board);
				break;
			}
			printboard(board);
			bestmoves(board);
			printf("Ai's MOVE\n");
		}
	}
}
int minimax(char board[rows][colm], int depth, int m, int n, int o, int p, int ismax)
{
	// int ifwin=checkforwin(board);
	// if(ifwin==2){
	// 	return INT_MAX;
	// }
	// if(ifwin==1){
	// 	return INT_MIN;
	// }
	int score = evaluate(board, m, n, o, p);
	if (depth == 4)
		return score;
	if (ismax)
	{
		int best = INT_MIN;
		int bestmove;
		for (int i = rows - 1; i >= 0; i--)
		{
			for (int j = colm - 1; j >= 0; j--)
			{
				if (board[i][j] == 'B' || board[i][j] == 'b')
				{
					if (((i == 2 && j % 2 != 0) && (j < 6) && board[i][j] == 'b') && (board[i - 1][j + 1] == 'W'))
					{
						if (board[i - 2][j + 2] == ' ')
						{
							board[i - 2][j + 2] = 'B';
							board[i - 1][j + 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 2, j + 2, 0));
							board[i][j] = 'b';
							board[i - 2][j + 2] = ' ';
							board[i - 1][j + 1] = 'W';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if (((i == 2 && j % 2 != 0) && (j < 6) && board[i][j] == 'b') && (board[i - 1][j + 1] == 'w'))
					{
						if (board[i - 2][j + 2] == ' ')
						{
							board[i - 2][j + 2] = 'B';
							board[i - 1][j + 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 2, j + 2, 0));
							board[i][j] = 'b';
							board[i - 2][j + 2] = ' ';
							board[i - 1][j + 1] = 'w';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if (((i == 2 && j % 2 != 0) && (j > 2) && board[i][j] == 'b') && (board[i - 1][j - 1] == 'w'))
					{
						if (board[i - 2][j - 2] == ' ')
						{
							board[i - 2][j - 2] = 'B';
							board[i - 1][j - 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 2, j - 2, 0));
							board[i][j] = 'b';
							board[i - 2][j - 2] = ' ';
							board[i - 1][j - 1] = 'w';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if (((i == 2 && j % 2 != 0) && (j > 2) && (board[i][j] == 'b') && (board[i - 1][j - 1] == 'W')))
					{
						if (board[i - 2][j - 2] == ' ')
						{
							board[i - 2][j - 2] = 'B';
							board[i - 1][j - 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 2, j - 2, 0));
							board[i][j] = 'b';
							board[i - 2][j - 2] = ' ';
							board[i - 1][j - 1] = 'W';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 1 && (j < colm - 2 && i != 2)) && (board[i - 1][j + 1] == 'w' && board[i][j] == 'b'))
					{
						if (board[i - 2][j + 2] == ' ')
						{
							board[i - 2][j + 2] = 'b';
							board[i - 1][j + 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 2, j + 2, 0));
							board[i - 2][j + 2] = ' ';
							board[i - 1][j + 1] = 'w';
							board[i][j] = 'b';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 1 && (j > 1 && i != 2)) && board[i - 1][j - 1] == 'w' && board[i][j] == 'b')
					{
						if (board[i - 2][j - 2] == ' ')
						{
							board[i - 2][j - 2] = 'b';
							board[i - 1][j - 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 2, j - 2, 0));
							board[i - 2][j - 2] = ' ';
							board[i - 1][j - 1] = 'w';
							board[i][j] = 'b';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 1 && (j > 1 && i != 2)) && board[i - 1][j - 1] == 'W' && board[i][j] == 'b')
					{
						if (board[i - 2][j - 2] == ' ')
						{
							board[i - 2][j - 2] = 'b';
							board[i - 1][j - 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 2, j - 2, 0));
							board[i - 2][j - 2] = ' ';
							board[i - 1][j - 1] = 'W';
							board[i][j] = 'b';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 1 && (j < colm - 2 && i != 2)) && board[i - 1][j + 1] == 'W' && board[i][j] == 'b')
					{
						if (board[i - 2][j + 2] == ' ')
						{
							board[i - 2][j + 2] = 'b';
							board[i - 1][j + 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 2, j + 2, 0));
							board[i - 2][j + 2] = ' ';
							board[i - 1][j + 1] = 'W';
							board[i][j] = 'b';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if (((i > 0 && (j < colm - 1 && i != 1)) && board[i - 1][j + 1] == ' ' && board[i][j] == 'b') || (((i == 2 && ((j < colm - 1 && i != 1) && (j % 2 != 0) && board[i][j] == 'b')) && (board[i - 1][j + 1] == ' '))))
					{
						board[i - 1][j + 1] = 'b';
						board[i][j] = ' ';
						bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 1, j + 1, 0));
						board[i - 1][j + 1] = ' ';
						board[i][j] = 'b';
						if (bestmove > best)
						{
							best = bestmove;
						}
					}
					if (((i > 0 && (j > 0 && i != 1)) && board[i - 1][j - 1] == ' ' && board[i][j] == 'b') || (((i == 2 && j % 2 != 0) && (j > 0) && board[i][j] == 'b') && (board[i - 1][j - 1] == ' ')))
					{
						board[i - 1][j - 1] = 'b';
						board[i][j] = ' ';
						bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 1, j - 1, 0));
						board[i - 1][j - 1] = ' ';
						board[i][j] = 'b';
						if (bestmove > best)
						{
							best = bestmove;
						}
					}
					if (((i == 1 && j % 2 == 0) && (j < colm - 1) && board[i][j] == 'b'))
					{
						if (board[i - 1][j + 1] == ' ')
						{
							board[i][j] = ' ';
							board[i - 1][j + 1] = 'B';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 1, j + 1, 0));
							board[i][j] = 'b';
							board[i - 1][j + 1] = ' ';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if (((i == 1 && j % 2 == 0) && (j > 1) && board[i][j] == 'b'))
					{
						if (board[i - 1][j - 1] == ' ')
						{
							board[i][j] = ' ';
							board[i - 1][j - 1] = 'B';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 1, j - 1, 0));
							board[i][j] = 'b';
							board[i - 1][j - 1] = ' ';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 1 && j < colm - 2) && board[i - 1][j + 1] == 'w' && board[i][j] == 'B')
					{
						if (board[i - 2][j + 2] == ' ')
						{
							board[i - 2][j + 2] = 'B';
							board[i - 1][j + 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 2, j + 2, 0));
							board[i - 2][j + 2] = ' ';
							board[i - 1][j + 1] = 'w';
							board[i][j] = 'B';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 1 && j > 1) && board[i - 1][j - 1] == 'w' && board[i][j] == 'B')
					{
						if (board[i - 2][j - 2] == ' ')
						{
							board[i - 2][j - 2] = 'B';
							board[i - 1][j - 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 2, j - 2, 0));
							board[i - 2][j - 2] = ' ';
							board[i - 1][j - 1] = 'w';
							board[i][j] = 'B';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 1 && j < colm - 2) && board[i - 1][j + 1] == 'W' && board[i][j] == 'B')
					{
						if (board[i - 2][j + 2] == ' ')
						{
							board[i - 2][j + 2] = 'B';
							board[i - 1][j + 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 2, j + 2, 0));
							board[i - 2][j + 2] = ' ';
							board[i - 1][j + 1] = 'W';
							board[i][j] = 'B';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 1 && j > 1) && board[i - 1][j - 1] == 'W' && board[i][j] == 'B')
					{
						if (board[i - 2][j - 2] == ' ')
						{
							board[i - 2][j - 2] = 'B';
							board[i - 1][j - 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 2, j - 2, 0));
							board[i - 2][j - 2] = ' ';
							board[i - 1][j - 1] = 'W';
							board[i][j] = 'B';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i < rows - 2 && j < colm - 2) && board[i + 1][j + 1] == 'w' && board[i][j] == 'B')
					{
						if (board[i + 2][j + 2] == ' ')
						{
							board[i + 2][j + 2] = 'B';
							board[i + 1][j + 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i + 2, j + 2, 0));
							board[i + 2][j + 2] = ' ';
							board[i + 1][j + 1] = 'w';
							board[i][j] = 'B';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i < rows - 2 && j > 1) && board[i + 1][j - 1] == 'w' && board[i][j] == 'B')
					{
						if (board[i + 2][j - 2] == ' ')
						{
							board[i + 2][j - 2] = 'B';
							board[i + 1][j - 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i + 2, j - 2, 0));
							board[i + 2][j - 2] = ' ';
							board[i + 1][j - 1] = 'w';
							board[i][j] = 'B';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i < rows - 2 && j < colm - 2) && board[i + 1][j + 1] == 'W' && board[i][j] == 'B')
					{
						if (board[i + 2][j + 2] == ' ')
						{
							board[i + 2][j + 2] = 'B';
							board[i + 1][j + 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i + 2, j + 2, 0));
							board[i + 2][j + 2] = ' ';
							board[i + 1][j + 1] = 'W';
							board[i][j] = 'B';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i < rows - 2 && j > 1) && board[i + 1][j - 1] == 'W' && board[i][j] == 'B')
					{
						if (board[i + 2][j - 2] == ' ')
						{
							board[i + 2][j - 2] = 'B';
							board[i + 1][j - 1] = ' ';
							board[i][j] = ' ';
							bestmove = maximum(best, minimax(board, depth + 1, i, j, i + 2, j - 2, 0));
							board[i + 2][j - 2] = ' ';
							board[i + 1][j - 1] = 'W';
							board[i][j] = 'B';
							if (bestmove > best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 0 && j < colm - 1) && board[i - 1][j + 1] == ' ' && board[i][j] == 'B')
					{
						board[i - 1][j + 1] = 'B';
						board[i][j] = ' ';
						bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 1, j + 1, 0));
						board[i - 1][j + 1] = ' ';
						board[i][j] = 'B';
						if (bestmove > best)
						{
							best = bestmove;
						}
					}
					if ((i > 0 && j > 0) && board[i - 1][j - 1] == ' ' && board[i][j] == 'B')
					{
						board[i - 1][j - 1] = 'B';
						board[i][j] = ' ';
						bestmove = maximum(best, minimax(board, depth + 1, i, j, i - 1, j - 1, 0));
						board[i - 1][j - 1] = ' ';
						board[i][j] = 'B';
						if (bestmove > best)
						{
							best = bestmove;
						}
					}
					if ((i < rows - 1 && j < colm - 1) && board[i + 1][j + 1] == ' ' && board[i][j] == 'B')
					{
						board[i + 1][j + 1] = 'B';
						board[i][j] = ' ';
						bestmove = maximum(best, minimax(board, depth + 1, i, j, i + 1, j + 1, 0));
						board[i + 1][j + 1] = ' ';
						board[i][j] = 'B';
						if (bestmove > best)
						{
							best = bestmove;
						}
					}
					if ((i < rows - 1 && j > 0) && board[i + 1][j - 1] == ' ' && board[i][j] == 'B')
					{
						board[i + 1][j - 1] = 'B';
						board[i][j] = ' ';
						bestmove = maximum(best, minimax(board, depth + 1, i, j, i + 1, j - 1, 0));
						board[i + 1][j - 1] = ' ';
						board[i][j] = 'B';
						if (bestmove > best)
						{
							best = bestmove;
						}
					}
				}
			}
		}
		return best;
	}
	else
	{
		int best = INT_MAX;
		int bestmove;
		for (int i = rows - 1; i >= 0; i--)
		{
			for (int j = colm - 1; j >= 0; j--)
			{
				if (board[i][j] == 'W' || board[i][j] == 'w')
				{
					if ((i == 5 && (j % 2 == 0 && j < 5) && board[i + 1][j + 1] == 'b') && board[i + 2][j + 2] == ' ' && board[i][j] == 'w')
					{
						board[i][j] = ' ';
						board[i + 1][j + 1] = ' ';
						board[i + 2][j + 2] = 'W';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 2, j + 2, 1));
						board[i][j] = 'w';
						board[i + 1][j + 1] = 'b';
						board[i + 2][j + 2] = ' ';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if ((i == 5 && (j % 2 == 0 && j > 1) && board[i + 1][j - 1] == 'b') && board[i + 2][j - 2] == ' ' && board[i][j] == 'w')
					{
						board[i][j] = ' ';
						board[i + 1][j - 1] = ' ';
						board[i + 2][j - 2] = 'W';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 2, j - 2, 1));
						board[i][j] = 'w';
						board[i + 1][j - 1] = 'b';
						board[i + 2][j - 2] = ' ';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if ((i == 5 && (j % 2 == 0 && j < 5) && board[i + 1][j + 1] == 'B') && board[i + 2][j + 2] == ' ' && board[i][j] == 'w')
					{
						board[i][j] = ' ';
						board[i + 1][j + 1] = ' ';
						board[i + 2][j + 2] = 'W';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 2, j + 2, 1));
						board[i][j] = 'w';
						board[i + 1][j + 1] = 'B';
						board[i + 2][j + 2] = ' ';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if ((i == 5 && (j % 2 == 0 && j > 1) && board[i + 1][j - 1] == 'B') && board[i + 2][j - 2] == ' ' && board[i][j] == 'w')
					{
						board[i][j] = ' ';
						board[i + 1][j - 1] = ' ';
						board[i + 2][j - 2] = 'W';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 2, j - 2, 1));
						board[i][j] = 'w';
						board[i + 1][j - 1] = 'B';
						board[i + 2][j - 2] = ' ';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if (((i < rows - 2 && j < colm - 2) && (i != 5 && board[i + 1][j + 1] == 'b')) && board[i + 2][j + 2] == ' ' && board[i][j] == 'w')
					{
						board[i][j] = ' ';
						board[i + 1][j + 1] = ' ';
						board[i + 2][j + 2] = 'w';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 2, j + 2, 1));
						board[i][j] = 'w';
						board[i + 1][j + 1] = 'b';
						board[i + 2][j + 2] = ' ';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if (((i < rows - 2 && j > 1) && (i != 5 && board[i + 1][j - 1] == 'b')) && board[i + 2][j - 2] == ' ' && board[i][j] == 'w')
					{
						board[i][j] = ' ';
						board[i + 1][j - 1] = ' ';
						board[i + 2][j - 2] = 'w';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 2, j - 2, 1));
						board[i][j] = 'w';
						board[i + 1][j - 1] = 'b';
						board[i + 2][j - 2] = ' ';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if (((i < rows - 2 && j < colm - 2) && (i != 5 && board[i + 1][j + 1] == 'B')) && board[i + 2][j + 2] == ' ' && board[i][j] == 'w')
					{
						board[i][j] = ' ';
						board[i + 1][j + 1] = ' ';
						board[i + 2][j + 2] = 'w';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 2, j + 2, 1));
						board[i][j] = 'w';
						board[i + 1][j + 1] = 'B';
						board[i + 2][j + 2] = ' ';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if (((i < rows - 2 && j > 1) && (i != 5 && board[i + 1][j - 1] == 'B')) && board[i + 2][j - 2] == ' ' && board[i][j] == 'w')
					{
						board[i][j] = ' ';
						board[i + 1][j - 1] = ' ';
						board[i + 2][j - 2] = 'w';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 2, j - 2, 1));
						board[i][j] = 'w';
						board[i + 1][j - 1] = 'B';
						board[i + 2][j - 2] = ' ';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if (((i < rows - 1 && (j < colm - 1) && i != 6) && board[i + 1][j + 1] == ' ' && board[i][j] == 'w') || ((i == 5 && (j % 2 == 0 && (j < colm - 1) && i != 6) && board[i + 1][j + 1] == ' ') && board[i][j] == 'w'))
					{
						board[i][j] = ' ';
						board[i + 1][j + 1] = 'w';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 1, j + 1, 1));
						board[i][j] = 'w';
						board[i + 1][j + 1] = ' ';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if (((i < rows - 1 && (j > 0) && i != 6) && board[i + 1][j - 1] == ' ' && board[i][j] == 'w') || ((i == 5 && i != 6 && (j % 2 == 0 && j > 0) && board[i + 1][j - 1] == ' ') && board[i][j] == 'w'))
					{
						board[i][j] = ' ';
						board[i + 1][j - 1] = 'w';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 1, j - 1, 1));
						board[i][j] = 'w';
						board[i + 1][j - 1] = ' ';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if ((i == 6 && j % 2 != 0) && board[i + 1][j - 1] == ' ' && board[i][j] == 'w')
					{
						board[i][j] = ' ';
						board[i + 1][j - 1] = 'W';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 1, j - 1, 1));
						board[i][j] = 'w';
						board[i + 1][j - 1] = ' ';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if ((i == 6 && (j % 2 != 0 && j < 6)) && board[i + 1][j + 1] == ' ' && board[i][j] == 'w')
					{
						board[i][j] = ' ';
						board[i + 1][j + 1] = 'W';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 1, j + 1, 1));
						board[i][j] = 'w';
						board[i + 1][j + 1] = ' ';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if ((i > 1 && j < colm - 2) && board[i - 1][j + 1] == 'b' && board[i][j] == 'W')
					{
						if (board[i - 2][j + 2] == ' ')
						{
							board[i - 2][j + 2] = 'W';
							board[i - 1][j + 1] = ' ';
							board[i][j] = ' ';
							bestmove = minimum(best, minimax(board, depth + 1, i, j, i - 2, j + 2, 1));
							board[i - 2][j + 2] = ' ';
							board[i - 1][j + 1] = 'b';
							board[i][j] = 'W';
							if (bestmove < best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 1 && j > 1) && board[i - 1][j - 1] == 'b' && board[i][j] == 'W')
					{
						if (board[i - 2][j - 2] == ' ')
						{
							board[i - 2][j - 2] = 'W';
							board[i - 1][j - 1] = ' ';
							board[i][j] = ' ';
							bestmove = minimum(best, minimax(board, depth + 1, i, j, i - 2, j - 2, 1));
							board[i - 2][j - 2] = ' ';
							board[i - 1][j - 1] = 'b';
							board[i][j] = 'W';
							if (bestmove < best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 1 && j < colm - 2) && board[i - 1][j + 1] == 'B' && board[i][j] == 'W')
					{
						if (board[i - 2][j + 2] == ' ')
						{
							board[i - 2][j + 2] = 'W';
							board[i - 1][j + 1] = ' ';
							board[i][j] = ' ';
							bestmove = minimum(best, minimax(board, depth + 1, i, j, i - 2, j + 2, 1));
							board[i - 2][j + 2] = ' ';
							board[i - 1][j + 1] = 'B';
							board[i][j] = 'W';
							if (bestmove < best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 1 && j > 1) && board[i - 1][j - 1] == 'B' && board[i][j] == 'W')
					{
						if (board[i - 2][j - 2] == ' ')
						{
							board[i - 2][j - 2] = 'W';
							board[i - 1][j - 1] = ' ';
							board[i][j] = ' ';
							bestmove = minimum(best, minimax(board, depth + 1, i, j, i - 2, j - 2, 1));
							board[i - 2][j - 2] = ' ';
							board[i - 1][j - 1] = 'B';
							board[i][j] = 'W';
							if (bestmove < best)
							{
								best = bestmove;
							}
						}
					}
					if ((i < rows - 2 && j < colm - 2) && board[i + 1][j + 1] == 'b' && board[i][j] == 'W')
					{
						if (board[i + 2][j + 2] == ' ')
						{
							board[i + 2][j + 2] = 'W';
							board[i + 1][j + 1] = ' ';
							board[i][j] = ' ';
							bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 2, j + 2, 1));
							board[i + 2][j + 2] = ' ';
							board[i + 1][j + 1] = 'b';
							board[i][j] = 'W';
							if (bestmove < best)
							{
								best = bestmove;
							}
						}
					}
					if ((i < rows - 2 && j > 1) && board[i + 1][j - 1] == 'b' && board[i][j] == 'W')
					{
						if (board[i + 2][j - 2] == ' ')
						{
							board[i + 2][j - 2] = 'W';
							board[i + 1][j - 1] = ' ';
							board[i][j] = ' ';
							bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 2, j - 2, 1));
							board[i + 2][j - 2] = ' ';
							board[i + 1][j - 1] = 'b';
							board[i][j] = 'W';
							if (bestmove < best)
							{
								best = bestmove;
							}
						}
					}
					if ((i < rows - 2 && j < colm - 2) && board[i + 1][j + 1] == 'B' && board[i][j] == 'W')
					{
						if (board[i + 2][j + 2] == ' ')
						{
							board[i + 2][j + 2] = 'W';
							board[i + 1][j + 1] = ' ';
							board[i][j] = ' ';
							bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 2, j + 2, 1));
							board[i + 2][j + 2] = ' ';
							board[i + 1][j + 1] = 'B';
							board[i][j] = 'W';
							if (bestmove < best)
							{
								best = bestmove;
							}
						}
					}
					if ((i < rows - 2 && j > 1) && board[i + 1][j - 1] == 'B' && board[i][j] == 'W')
					{
						if (board[i + 2][j - 2] == ' ')
						{
							board[i + 2][j - 2] = 'W';
							board[i + 1][j - 1] = ' ';
							board[i][j] = ' ';
							bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 2, j - 2, 1));
							board[i + 2][j - 2] = ' ';
							board[i + 1][j - 1] = 'B';
							board[i][j] = 'W';
							if (bestmove < best)
							{
								best = bestmove;
							}
						}
					}
					if ((i > 0 && j < colm - 1) && board[i - 1][j + 1] == ' ' && board[i][j] == 'W')
					{
						board[i - 1][j + 1] = 'W';
						board[i][j] = ' ';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i - 1, j + 1, 1));
						board[i - 1][j + 1] = ' ';
						board[i][j] = 'W';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if ((i > 0 && j > 0) && board[i - 1][j - 1] == ' ' && board[i][j] == 'W')
					{
						board[i - 1][j - 1] = 'W';
						board[i][j] = ' ';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i - 1, j - 1, 1));
						board[i - 1][j - 1] = ' ';
						board[i][j] = 'W';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if ((i < rows - 1 && j < colm - 1) && board[i + 1][j + 1] == ' ' && board[i][j] == 'W')
					{
						board[i + 1][j + 1] = 'W';
						board[i][j] = ' ';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 1, j + 1, 1));
						board[i + 1][j + 1] = ' ';
						board[i][j] = 'W';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
					if ((i < rows - 1 && j > 0) && board[i + 1][j - 1] == ' ' && board[i][j] == 'W')
					{
						board[i + 1][j - 1] = 'W';
						board[i][j] = ' ';
						bestmove = minimum(best, minimax(board, depth + 1, i, j, i + 1, j - 1, 1));
						board[i + 1][j - 1] = ' ';
						board[i][j] = 'W';
						if (bestmove < best)
						{
							best = bestmove;
						}
					}
				}
			}
		}
		return best;
	}
}
int evaluate(char board[rows][colm], int m, int n, int o, int p)
{
	int capture = 0;
	if (board[m][n] == 'w' || board[m][n] == 'W')
	{
		if (((m - o == 2 || m - o == -2) && (n - p == 2 || n - p == -2)))
		{
			capture = -50;
		}
	}
	else if (board[m][n] == 'b' || board[m][n] == 'B')
	{
		if (((m - o == 2 || m - o == -2) && (n - p == 2 || n - p == -2)))
		{
			capture = 50;
		}
	}
	int i, j, k, countb = 0, countw = 0, countB = 0, countW = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < colm; j++)
		{
			if (board[i][j] == 'b')
			{
				countb++;
			}
			else if (board[i][j] == 'B')
			{
				countB++;
			}
			else if (board[i][j] == 'w')
			{
				countw++;
			}
			else if (board[i][j] == 'W')
			{
				countW++;
			}
		}
	}
	int A = countb - countw;
	int B = countb * 10 - countw * 10;
	int C = countB - countW;
	int D = countB * 100 - countW * 100;
	return A + B + C + D + capture;
}
