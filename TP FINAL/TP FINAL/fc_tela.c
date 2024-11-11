#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*---------- FUNC�ES PRA DEIXAR BONITINHO ----------*/
// Remove a quebra de linha de uma string
void RemoveQuebraLinha	(char dado[]) {
	int tamanho = strlen(dado);
	if ((tamanho > 0) && (dado[tamanho - 1] == '\n'))
	{
		dado[tamanho - 1] = '\0';
	}
}
// limpa a tela do sistema inteiro
void LimparTela			() {
	system("cls || clear");
}
// limpa a tela e c'	oloca o titulo
void LimpaTelaTitulo	(char titulo[], char subtitulo[], bool limpatela){

	if(limpatela) LimparTela();
	printf("---- %s ----\n\n_ %s _\n", titulo, subtitulo);
}
/* ------------------------------------------------ */
