#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ALTURA 40
#define LARGURA 100

int matrix[ALTURA][LARGURA] = {0};

void imprimirCaractere(int coord_x, int coord_y, char charactere, int color)
{
	COORD coord;
	HANDLE handle_out;
	
	coord.X = coord_x;
	coord.Y = coord_y;
	handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(handle_out, color);
	SetConsoleCursorPosition(handle_out, coord);
	printf("%c", charactere);
	SetConsoleTextAttribute(handle_out, 7); // retorna a cor do caractere à cor de fundo 
}

void imprimirCampo() {
	// Imprimindo as paredes horizontais
	for (int i = 0; i < ALTURA; i++)
	{
		imprimirCaractere(0, i, 176, 7);
		imprimirCaractere(LARGURA-1, i, 176, 7);
	}
	for (int i = 0; i < LARGURA; i++)
	{
		imprimirCaractere(i, 0, 176, 7);
		imprimirCaractere(i, ALTURA-1, 176, 7);
	}
}

// Debug:
void imprimirMatrix() {
	for (int i = 0; i < ALTURA; i++)
	{
		for (int j = 0; j < LARGURA; j++)
		{
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	system("cls");

	imprimirCampo();

	int x0 = (int) (0.75*ALTURA);
	int y0 = (int) (0.25*LARGURA);

	int y_pos = x0;
	int x_pos = y0;

	// Enquanto as coordenadas geradas estiverem dentro dos limites do
	// campo, o jogo irá continuar normalmente.
	while((x_pos > 1 && x_pos < LARGURA-1) && (y_pos > 1 && y_pos < ALTURA-1)) {
		matrix[y_pos][x_pos] = 1;
		imprimirCaractere(x_pos, y_pos, 154, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
		Sleep(50);
		x_pos++;
	}

  	return 0;
}
