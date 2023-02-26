#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ALTURA 40
#define LARGURA 100
#define VELOCIDADE 100

int matrix[ALTURA][LARGURA] = {{0}};

void imprimirCaractere(int coord_x, int coord_y, char charactere, int cor) {
	COORD coord;
	HANDLE handle_out;

	coord.X = coord_x;
	coord.Y = coord_y;
	handle_out = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(handle_out, cor);
	SetConsoleCursorPosition(handle_out, coord);
	printf("%c", charactere);
	SetConsoleTextAttribute(handle_out, 7);
}

void imprimirCampo() {
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

boolean insideX_axis(int x) {
	return (x > 1 && x < LARGURA-1);
}

boolean insideY_axis(int y) {
	return (y > 1 && y < ALTURA-1);
}

boolean isNotBitingItself(int x, int y) {
	return !(matrix[y][x]);
}

int main() 
{
	system("cls");
	imprimirCampo();

	int key_up, key_down, key_left, key_right = 0;
	int x0 = (int) (0.25*LARGURA);
	int y0 = (int) (0.75*ALTURA);
	int x_pos = x0;
	int y_pos = y0;

	// Enquanto o jogador estiver dentro do campo, faça:
	while (insideX_axis(x_pos) && insideY_axis(y_pos) && isNotBitingItself(x_pos, y_pos))
	{
		// Sistema operacional está checando se a chamada de sistema do teclado está operacional constantemente:
		key_up = GetAsyncKeyState(VK_UP);
		key_down = GetAsyncKeyState(VK_DOWN);
		key_left = GetAsyncKeyState(VK_LEFT);
		key_right = GetAsyncKeyState(VK_RIGHT);

		// DEBUG
		// printf("UP: %d - DOWN: %d - LEFT: %d - RIGHT: %d", key_up, key_down, key_left, key_right);

		if (key_up) {
			key_left = 0;
			key_right = 0;

			while ((!key_left && !key_right) && insideX_axis(x_pos) && insideY_axis(y_pos) && isNotBitingItself(x_pos, y_pos)) {
				matrix[y_pos][x_pos] = 1;
				imprimirCaractere(x_pos, y_pos, 154, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				Sleep(VELOCIDADE);
				y_pos--;

				key_left = GetAsyncKeyState(VK_LEFT);
				key_right = GetAsyncKeyState(VK_RIGHT);
			}
		}
		
		if (key_down) {
			key_left = 0;
			key_right = 0;

			while ((!key_left && !key_right) && insideX_axis(x_pos) && insideY_axis(y_pos) && isNotBitingItself(x_pos, y_pos)) {
				matrix[y_pos][x_pos] = 1;
				imprimirCaractere(x_pos, y_pos, 154, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				Sleep(VELOCIDADE);
				y_pos++;

				key_left = GetAsyncKeyState(VK_LEFT);
				key_right = GetAsyncKeyState(VK_RIGHT);
			}
		}

		if (key_right) {
			key_up = 0;
			key_down = 0;

			while ((!key_up && !key_down) && insideX_axis(x_pos) && insideY_axis(y_pos) && isNotBitingItself(x_pos, y_pos)) {
				matrix[y_pos][x_pos] = 1;
				imprimirCaractere(x_pos, y_pos, 154, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				Sleep(VELOCIDADE);
				x_pos++;

				key_up = GetAsyncKeyState(VK_UP);
				key_down = GetAsyncKeyState(VK_DOWN);
			}
		}	

		if (key_left) {
			key_up = 0;
			key_down = 0;

			while ((!key_up && !key_down) && insideX_axis(x_pos) && insideY_axis(y_pos) && isNotBitingItself(x_pos, y_pos)) {
				matrix[y_pos][x_pos] = 1;
				imprimirCaractere(x_pos, y_pos, 154, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				Sleep(VELOCIDADE);
				x_pos--;

				key_up = GetAsyncKeyState(VK_UP);
				key_down = GetAsyncKeyState(VK_DOWN);
			}
		}
	}

	return 0;
}