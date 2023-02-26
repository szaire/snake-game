#include <stdio.h>
#include <stdlib.h>

#define ROW 4
#define LINE 4

int main() {
  // TESTE DE INICIALIZAÇÃO DE MATRIZES
  int m[ROW][LINE] = {0};

  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < LINE; j++)
    {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
}