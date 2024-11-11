#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "estruturas.h"

// Verifica se o ID do usuario / produto existe
bool verifica_existencia_ID		(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int *Numero_do_usuario, int *Numero_do_produto, char Id_lido[], int verifica_usuario, int veriifica_produto){

	char opcao;

	if(verifica_usuario == 1 && veriifica_produto == 0){
		for (int i = 0; i < Quantidade_de_cadastros_feitos; i++)
		{
			if (strcmp(Id_lido, Usuario[i].ID) == 0)
			{
				*Numero_do_usuario = i;
			}
		}
		if (*Numero_do_usuario == -1)
		{
			printf("\nEsse ID nao corresponde a nenhum usuario !!!\n");
			printf("Deseja tentar novamente [ s / n ]: ");
			(void)scanf("%c%*c", &opcao);
			printf("\n");

			if (opcao == 's' || opcao == 'S')
			{
				return true;
			}
			else
			{
				return false;
			}
			}
		else
		{
			return false;
		}
	}
	if(verifica_usuario == 0 && veriifica_produto == 1){

		for (int i = 0; i < Quantidade_de_cadastros_feitos; i++) {
			for (int j = 0; j < Usuario[i].Quantidade_de_produtos_cadastrados; j++)
			{
				if (strcmp(Id_lido, Usuario[i].informacoes[j].ID) == 0)
				{
					*Numero_do_usuario = i;
					*Numero_do_produto = j;
				}
			}
		}
		if (*Numero_do_produto == -1)
		{
			printf("\nEsse ID nao corresponde a nenhum produto !!!\n");
			printf("Deseja tentar novamente [ s / n ]: ");
			(void)scanf("%c%*c", &opcao);
			
			printf("\n");
			if (opcao == 's' || opcao == 'S')
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true; // o codigo nunca chegara aqui !!!
}
// Verifica se a opcao é realmente um numero para nao dar erro de repeticao
void recebe_numero_valido		(int* numero){

	int verifica_se_n_lido_numero = 0;
	verifica_se_n_lido_numero = scanf("%d%*c", numero);
	if(verifica_se_n_lido_numero == 0){
		(void)scanf("%*c%*c");
		*numero = -1;
	}
}

