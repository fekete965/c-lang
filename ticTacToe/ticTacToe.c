#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void resetBoard();
void printBoard();
int shouldContinue(char winner);
int checkFreeSpaces();
int getCoordinate(char *text);
void playerMove();
void computerMove();
char checkWinner();
void playAgain(char *response);
void printWinner(char winner);

const char PLAYER = 'X';
const char COMPUTER = 'O';
const int BOARD_SIZE = 3;
char board[BOARD_SIZE][BOARD_SIZE];

int main()
{
  char winner;
  char response;

  do
  {
    winner = ' ';
    response = ' ';

    resetBoard();

    while (!shouldContinue(winner))
    {
      printBoard();

      playerMove();
      winner = checkWinner();
      if (shouldContinue(winner))
      {
        break;
      }

      computerMove();
      winner = checkWinner();
      if (shouldContinue(winner))
      {
        break;
      }
    }

    printBoard();
    printWinner(winner);
    playAgain(&response);
  } while (response == 'Y');

  printf("\n\nThanks for playing!\n");

  return 0;
}

void resetBoard()
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      board[i][j] = ' ';
    }
  }
}

int shouldContinue(char winner)
{
  return winner != ' ' || checkFreeSpaces() == 0;
}

void printBoard()
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
    printf("\n---|---|---\n");
  }
  printf("\n");
}

int checkFreeSpaces()
{
  int freeSpaces = BOARD_SIZE * BOARD_SIZE;

  for (int i = 0; i < BOARD_SIZE; i++)
  {

    for (int j = 0; j < BOARD_SIZE; j++)
    {
      if (board[i][j] != ' ')
      {
        freeSpaces--;
      }
    }
  }

  return freeSpaces;
}

int getCoordinate(char *text)
{
  int n;

  printf("%s", text);
  scanf("%d", &n);
  fflush(stdin);

  if (n > BOARD_SIZE || n < 1)
  {
    printf("\nInvalid number. Please choose a number between 1 and 3.\n");
    return getCoordinate(text);
  }

  return n - 1;
}

void playerMove()
{
  int x = getCoordinate("Enter row #(1-3): ");
  int y = getCoordinate("Enter column #(1-3): ");

  if (board[x][y] != ' ')
  {
    printf("Invalid move!\n");
    return playerMove();
  }

  board[x][y] = PLAYER;
  return;
}

void computerMove()
{
  srand(time(0));

  int x;
  int y;

  if (checkFreeSpaces() > 0)
  {
    do
    {
      x = rand() % BOARD_SIZE;
      y = rand() % BOARD_SIZE;
    } while (board[x][y] != ' ');

    board[x][y] = COMPUTER;
  }
  else
  {
    printWinner(' ');
  }
}

char checkWinner()
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    // Check rows
    if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
    {
      return board[i][0];
    }
    // Check columns
    if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
    {
      return board[0][i];
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
      return board[0][i];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
      return board[0][2];
    }
  }

  return ' ';
}

void playAgain(char *resp)
{
  printf("\nWould you like to play again? (Y/N) ");
  scanf("%c", resp);
  fflush(stdin);
  *resp = toupper(*resp);

  if (resp[0] == 'Y' || resp[0] == 'N')
  {
    return;
  }

  printf("\nInvalid answer. Please type in Y or N\n");
  return playAgain(resp);
}

void printWinner(char winner)
{
  if (winner == PLAYER)
  {
    printf("You win!");
  }
  else if (winner == COMPUTER)
  {
    printf("You lose!");
  }
  else
  {
    printf("It's a draw!");
  }
}
