#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // incluindo a biblioteca do windows no programa

void imprimir_cor(int coord_x, int coord_y, int color) 
{
	COORD coord;
	HANDLE handle_out;

	coord.X = coord_x;
	coord.Y = coord_y;
	handle_out = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(handle_out, color);
	SetConsoleCursorPosition(handle_out, coord);
	printf("%c", 219);
	SetConsoleTextAttribute(handle_out, 7);
}

int main()
{
	system("cls");

	imprimir_cor(0, 0, FOREGROUND_RED|FOREGROUND_INTENSITY);
	imprimir_cor(0, 1, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	imprimir_cor(1, 1, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	imprimir_cor(1, 10, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	printf("Hello World!"); // teste de hello world XD
	return 0;
}
