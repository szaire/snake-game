#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>

// Declarações de valores constantes globais
#define ALTURA 40
#define LARGURA 100
#define VELOCIDADE 50
#define TAMANHO_INICIAL 10

// declaração da matrix global (comporta tanto o campo quanto a "cobrinha" em si)
int matrix[ALTURA][LARGURA] = {0};

// Print de qualquer caractere presente na tela
// coord_x: Coordenadas de X
// coord_y: Coordenadas de Y
// charactere: Caractere de escolha para ser impresso na tela
// cor: Cor do caractere escolhido para ser impresso
void imprimirCaractere(int coord_x, int coord_y, char charactere, int cor) {
	// Definição das Structs (Biblioteca <windows.h>)
	COORD coord;
	HANDLE handle_out;

	// Definição dos valores das structs
	coord.X = coord_x;
	coord.Y = coord_y;
	handle_out = GetStdHandle(STD_OUTPUT_HANDLE);

	// Onde o print do caractere ocorre:
	SetConsoleTextAttribute(handle_out, cor);
	SetConsoleCursorPosition(handle_out, coord);
	printf("%c", charactere);
	SetConsoleTextAttribute(handle_out, 7);
}

// Estrutura de Repetição que imprime o campo (ALTURA x LARGURA) no console
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

// Funções booleanas criadas para checar se:
// 1 - A cobrinha se encontra dentro do eixo X
boolean insideX_axis(int x) {
	return (x > 0 && x < LARGURA-1);
}

// 2 - A cobrinha se encontra dentro do eixo Y
boolean insideY_axis(int y) {
	return (y > 0 && y < ALTURA-1);
}

// 3 - A cobrinha não colide com si mesma (onde há valor numérico 1)
boolean isNotBitingItself(int x, int y) {
	return !matrix[y][x]; // 0 = FALSE; 1 = TRUE
}

void* player(void *args) {
    // Declaração das variáveis principais
	int key_up, key_down, key_left, key_right = 0;

    int x_pos;
    int y_pos;
    int cor;

    int UP;
    int DOWN;
    int LEFT;
    int RIGHT;

    int player = (int) args;

    if (player == 1) {
        x_pos = (int) (0.25*LARGURA);
        y_pos = (int) (0.75*ALTURA);
        cor = FOREGROUND_BLUE|FOREGROUND_INTENSITY;

        UP = VK_UP;
        DOWN = VK_DOWN;
        LEFT = VK_LEFT;
        RIGHT = VK_RIGHT;
    }
    else if (player == 2) {
        x_pos = (int) (0.75*LARGURA);
        y_pos = (int) (0.25*ALTURA);
        cor = FOREGROUND_RED|FOREGROUND_INTENSITY;

        UP = 0x57;
        DOWN = 0x53;
        LEFT = 0x41;
        RIGHT = 0x44;
    }
    else {
        printf("Não há jogador disponível com essa identificação!");
        return (void*) -1;
    }

	// Declaração do buffer da cobrinha e das variáveis de apoio
	int buffer[ALTURA*LARGURA][2] = {0};
	int snakeMovement = 0;
	int x_del, y_del = 0;

	// TODO: Impedir que a cobra se movimente diagonalmente, apenas verticalmente e horizontalmente 
	// Loop principal onde o jogo ocorre:
	while (insideX_axis(x_pos) && insideY_axis(y_pos) && isNotBitingItself(x_pos, y_pos))
	{
		key_up = GetAsyncKeyState(UP);
		key_down = GetAsyncKeyState(DOWN);
		key_left = GetAsyncKeyState(LEFT);
		key_right = GetAsyncKeyState(RIGHT);

		// MOVIMENTO PARA CIMA
		if (key_up) {
			key_left = 0;
			key_right = 0;

			// Enquanto as teclas adjascentes e não-opostas não forem pressionadas,
			// a cobrinha irá avançar infinitamente até colidir com uma parede
			// ou com si mesma
			while ((!key_left && !key_right) && insideX_axis(x_pos) && insideY_axis(y_pos) && isNotBitingItself(x_pos, y_pos))
			{
				// Guarda sempre a última posição em que o cursor se encontra
				buffer[snakeMovement][0] = x_pos;
				buffer[snakeMovement][1] = y_pos;

				// Objetivo dessa estrutura condicional é sempre deletar a ponta da cauda da cobra
				if (snakeMovement >= TAMANHO_INICIAL) {
					x_del = buffer[snakeMovement - TAMANHO_INICIAL][0];
					y_del = buffer[snakeMovement - TAMANHO_INICIAL][1];

					matrix[y_del][x_del] = 0;
					imprimirCaractere(x_del, y_del, 255, 0);

					buffer[snakeMovement - TAMANHO_INICIAL][0] = 0;
					buffer[snakeMovement - TAMANHO_INICIAL][1] = 0;
				}

				// Atualiza a posição, cor e movimento do cursor
				matrix[y_pos][x_pos] = 1;
				imprimirCaractere(x_pos, y_pos, 154, cor);
				Sleep(VELOCIDADE);
				snakeMovement++;
				y_pos--;
				
				// Checa se alguma tecla adjascente e não-oposta à tecla atual foi pressionada 
				key_left = GetAsyncKeyState(LEFT);
				key_right = GetAsyncKeyState(RIGHT);
			}
		}

		// MOVIMENTO PARA BAIXO
		if (key_down) {
			key_left = 0;
			key_right = 0;

			while ((!key_left && !key_right) && insideX_axis(x_pos) && insideY_axis(y_pos) && isNotBitingItself(x_pos, y_pos))
			{
				buffer[snakeMovement][0] = x_pos;
				buffer[snakeMovement][1] = y_pos;

				if (snakeMovement >= TAMANHO_INICIAL) {
					x_del = buffer[snakeMovement - TAMANHO_INICIAL][0];
					y_del = buffer[snakeMovement - TAMANHO_INICIAL][1];

					matrix[y_del][x_del] = 0;
					imprimirCaractere(x_del, y_del, 255, 0);

					buffer[snakeMovement - TAMANHO_INICIAL][0] = 0;
					buffer[snakeMovement - TAMANHO_INICIAL][1] = 0;
				}
				
				matrix[y_pos][x_pos] = 1;
				imprimirCaractere(x_pos, y_pos, 154, cor);
				Sleep(VELOCIDADE);
				snakeMovement++;
				y_pos++;
				
				key_left = GetAsyncKeyState(LEFT);
				key_right = GetAsyncKeyState(RIGHT);
			}
		}

		// MOVIMENTO PARA DIREITA
		if (key_right) {
			key_up = 0;
			key_down = 0;

			while ((!key_up && !key_down) && insideX_axis(x_pos) && insideY_axis(y_pos) && isNotBitingItself(x_pos, y_pos))
			{
				buffer[snakeMovement][0] = x_pos;
				buffer[snakeMovement][1] = y_pos;

				if (snakeMovement >= TAMANHO_INICIAL) {
					x_del = buffer[snakeMovement - TAMANHO_INICIAL][0];
					y_del = buffer[snakeMovement - TAMANHO_INICIAL][1];

					matrix[y_del][x_del] = 0;
					imprimirCaractere(x_del, y_del, 255, 0);

					buffer[snakeMovement - TAMANHO_INICIAL][0] = 0;
					buffer[snakeMovement - TAMANHO_INICIAL][1] = 0;
				}

				matrix[y_pos][x_pos] = 1;
				imprimirCaractere(x_pos, y_pos, 154, cor);
				Sleep(VELOCIDADE);
				snakeMovement++;
				x_pos++;

				key_up = GetAsyncKeyState(UP);
				key_down = GetAsyncKeyState(DOWN);
			}
			
		}

		// MOVIMENTO PARA ESQUERDA
		if (key_left) {
			key_up = 0;
			key_down = 0;

			while ((!key_up && !key_down) && insideX_axis(x_pos) && insideY_axis(y_pos) && isNotBitingItself(x_pos, y_pos))
			{
				buffer[snakeMovement][0] = x_pos;
				buffer[snakeMovement][1] = y_pos;

				if (snakeMovement >= TAMANHO_INICIAL) {
					x_del = buffer[snakeMovement - TAMANHO_INICIAL][0];
					y_del = buffer[snakeMovement - TAMANHO_INICIAL][1];

					matrix[y_del][x_del] = 0;
					imprimirCaractere(x_del, y_del, 255, 0);

					buffer[snakeMovement - TAMANHO_INICIAL][0] = 0;
					buffer[snakeMovement - TAMANHO_INICIAL][1] = 0;
				}

				matrix[y_pos][x_pos] = 1;
				imprimirCaractere(x_pos, y_pos, 154, cor);
				Sleep(VELOCIDADE);
				snakeMovement++;
				x_pos--;

				key_up = GetAsyncKeyState(UP);
				key_down = GetAsyncKeyState(DOWN);
			}
		}
	}
    return NULL;
}

int main() {
	system("cls"); //função do shell do windows que limpa todos os elementos da tela
	imprimirCampo();

	// player((int) LARGURA*0.25, (int) ALTURA*0.75, FOREGROUND_RED|FOREGROUND_INTENSITY);
    // Operadores Usados:
    // &: Endereço de... => Um endereço na memória é onde determinado valor está guardado
    // foo*: Ponteiro de... => Um ponteiro é um tipo de variável que guarda um endereço na memória (int* num -> Ponteiro de inteiro)
    // *foo: Conteúdo de... => O conteúdo de um ponteiro é o valor guardado no espaço de memória por ele referenciado
    pthread_t player1;
    pthread_t player2;

    pthread_create(&player1, NULL, player, (void*) 1);
    pthread_create(&player2, NULL, player, (void*) 2);

    pthread_join(player1, NULL);
    pthread_join(player2, NULL);

	system("pause");
	return 0;
}