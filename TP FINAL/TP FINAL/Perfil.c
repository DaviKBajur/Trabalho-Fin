#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fc_verificacao.h"
#include "estruturas.h"
#include "gera_imagem.h"
#include "Produtos.h"
#include "fc_tela.h"

/* ORDENACAO LEXICOGRAFICA (TABELA ASCII) (ID OU EMAIL OU NOME) DE ACORDO COM UM CRITERIO ( I , E , N ) */
void troca			(Perfil *usuarios, int i, int j) {

    Perfil aux = usuarios[i];
    usuarios[i] = usuarios[j];
    usuarios[j] = aux;
}
int compara			(Perfil *usuarios, int i, int j, char criterio) {

    if (criterio == 'N') {
        return strcmp(usuarios[i].nome, usuarios[j].nome);
    } else if (criterio == 'E') {
        return strcmp(usuarios[i].email, usuarios[j].email);
    } else if (criterio == 'I') {
        return strcmp(usuarios[i].ID, usuarios[j].ID);
    }
    return 0;
}
int particiona		(Perfil *usuarios, int inicio, int fim, char criterio) {

    int pivo_indice = inicio;
    for (int i = inicio; i < fim; i++) {
        if (compara(usuarios, i, fim, criterio) <= 0) {
            troca(usuarios, i, pivo_indice);
            pivo_indice++;
        }
    }
    troca(usuarios, pivo_indice, fim);
    return pivo_indice;
}
void quick_sort		(Perfil *usuarios, int inicio, int fim, char criterio) {

    if (inicio < fim) {
        int pivo_indice = particiona(usuarios, inicio, fim, criterio);
        quick_sort(usuarios, inicio, pivo_indice - 1, criterio);
        quick_sort(usuarios, pivo_indice + 1, fim, criterio);
    }
}
/*------------------------------------------------------------------------------------------------------*/


// Lista os IDs de usuarios (ordenado) ou produtos
void listar_IDS									(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int mostrar_produtos, int mostrar_usuario, int mostrar_qt_produtos, int mostrar_qt_favoritados){
	
	if(mostrar_usuario == 1 && mostrar_produtos == 0){
		quick_sort(Usuario, 0, Quantidade_de_cadastros_feitos - 1, 'I');
		printf("--------- ID DOS USUARIOS ---------\n");
		for (int i = 0; i < Quantidade_de_cadastros_feitos; i++){
			printf("Usuario: %s", Usuario[i].ID); 
			if(mostrar_qt_produtos == 1) printf(" - %d produtos\n", Usuario[i].numero_da_quantidade_de_produtos_publicados); 
			else if ( mostrar_qt_favoritados == 1) printf("%d produtos favoritados\n", Usuario[i].numero_da_quantidade_de_favoritos_de_um_usuario); 
			else printf("%s\n", Usuario[i].nome);
			}
		printf("-----------------------------------\n\n");
	}
	if(mostrar_usuario == 0 && mostrar_produtos == 1){

		printf("--------- ID DOS PRODUTOS ---------\n");
		for (int i = 0; i < Quantidade_de_cadastros_feitos; i++){
			for(int j = 0; j < Usuario[i].Quantidade_de_produtos_cadastrados; j++){
				if(Usuario[i].informacoes[j].produto_publicado){
					printf("Produto[ %s ]: %d avaliacoes\n", Usuario[i].informacoes[j].ID, Usuario[i].informacoes[j].numero_de_avaliacoes);
				}
			}
		}
		printf("-----------------------------------\n\n");
	}
}
// Busca os usuarios de acordo com a escolha do usuario (ID EMAIL NOME) por parte da string
void buscar_usuarios_ordenado 					(Perfil* Usuario, int Quantidade_de_cadastros_feitos, bool Listar_por_ID, bool Listar_por_Email, bool Listar_por_Nome){

	LimparTela();
	char ID_para_busca[MAX_CARACTER_ID];
	char Email_para_busca[MAX_CARACTER_EMAIL];
	char Nome_para_busca[MAX_CARACTER_NOME];

	char usuario_nome_cpy[MAX_CARACTER_NOME];
	char usuario_email_cpy[MAX_CARACTER_EMAIL];

	if      (Listar_por_ID) {

		printf("DIGITE O ID PARA BUSCA: ");
		fgets(ID_para_busca, MAX_CARACTER_ID, stdin);
		RemoveQuebraLinha(ID_para_busca);
		printf("\n");

		printf("--------- LISTAGEM POR ID ---------\n");
		for(int i = 0; i < Quantidade_de_cadastros_feitos; i++) {

			if (strstr(Usuario[i].ID, ID_para_busca) != NULL) {
				printf("Usuario[ %d ]: %s\n", i + 1, Usuario[i].ID);
			}
		}
		printf("-----------------------------------\n\n");

	}
	else if (Listar_por_Nome) { 

	    printf("DIGITE O NOME PARA BUSCA: ");
		fgets(Nome_para_busca, MAX_CARACTER_NOME, stdin);
		RemoveQuebraLinha(Nome_para_busca);
		printf("\n");

		printf("--------- LISTAGEM POR NOME ---------\n");
		for(int i = 0; i < Quantidade_de_cadastros_feitos; i++) {

			for (int j = 0; j < strlen(Usuario[i].nome); j++) {
        		usuario_nome_cpy[j] = toupper(Usuario[i].nome[j]);
				Nome_para_busca[j] = toupper(Nome_para_busca[j]);
    		}
			
			if(strstr(usuario_nome_cpy, Nome_para_busca) != NULL) {
				printf("Usuario[ %d ]: %s\n",i + 1, Usuario[i].nome);
			}
		}
		printf("-----------------------------------\n\n");
		
	}
	else if (Listar_por_Email) {

	 	printf("DIGITE O EMAIL PARA BUSCA: ");
		fgets(Email_para_busca, MAX_CARACTER_EMAIL, stdin);
		RemoveQuebraLinha(Email_para_busca);
		printf("\n");

		printf("--------- LISTAGEM POR EMAIL ---------\n");
		for(int i = 0; i < Quantidade_de_cadastros_feitos; i++) {

			for (int j = 0; j < strlen(Usuario[i].email); j++) {
        		usuario_email_cpy[j] = toupper(Usuario[i].email[j]);
				Email_para_busca[j] = toupper(Email_para_busca[j]);
    		}

			if(strstr(usuario_email_cpy, Email_para_busca) != NULL) {
				printf("Usuario[ %d ]: %s\n",i + 1, Usuario[i].email);
			}
		}
		printf("--------------------------------------\n\n");
	}
}
// Lista os usuario de acordo com a escolha do usuario (ID EMAIL NOME)
void listar_usuarios_ordenado			   	    (Perfil* Usuario, int Quantidade_de_cadastros_feitos, bool Listar_por_ID, bool Listar_por_Email, bool Listar_por_Nome) {

	LimparTela();
	printf("--------- LISTAGEM POR %s ---------\n", (Listar_por_ID? "ID" : (Listar_por_Nome? "NOME" : (Listar_por_Email? "EMAIL" : " "))));
	for (int i = 0; i < Quantidade_de_cadastros_feitos; i++)
	{
		printf("|> Usuario: %s\n", (Listar_por_ID? Usuario[i].ID : (Listar_por_Nome? Usuario[i].nome : (Listar_por_Email? Usuario[i].email : " "))));
	}
	printf("\n\n\n");
}
// Recebe a opcao de escolha do usuario para a listagem nao ordenada
void Opcao_listar_ou_busca_usuarios_cadastrados (Perfil* Usuario, int Quantidade_de_cadastros_feitos, char titulo[], bool listar, bool buscar) {

	LimparTela();
	int opcao_usuario;
	bool opcao_por_id = false;
	bool opcao_por_nome = false;
	bool opcao_por_email = false;
	bool continuar_opcao = true;
	
	/*- RECEBE A OPCAO DE LISTAGEM DO USUARIO -*/ 
	do
	{
		opcao_por_id = false;
		opcao_por_nome = false;
		opcao_por_email = false;

		printf("|>---- OPCOES DE LISTAGEM / BUSCA ----<|\n");
		printf("  1) %s por ID				          \n", titulo);
		printf("  2) %s por Nome			          \n", titulo);
		printf("  3) %s por Email                     \n", titulo);
		printf("  0) Voltar						      \n");
		printf("|>-----------------------------------<|\n");
		printf("Opcao: ");
		(void)scanf("%d%*c", &opcao_usuario);

		switch (opcao_usuario)
		{
		case 1:

			quick_sort(Usuario, 0, Quantidade_de_cadastros_feitos - 1, 'I');
			opcao_por_id = true;
			break;

		case 2:
			quick_sort(Usuario, 0, Quantidade_de_cadastros_feitos - 1, 'N');
			opcao_por_nome = true;
			break;

		case 3:
			quick_sort(Usuario, 0, Quantidade_de_cadastros_feitos - 1, 'E');
			opcao_por_email = true;
			break;

		case 0:
			break;

		default:
			LimparTela();
			printf("Opcao invalida !!!\n\n");
			break;

		}
		if (opcao_usuario != 0)
		{
			if(listar)
			listar_usuarios_ordenado(Usuario, Quantidade_de_cadastros_feitos, opcao_por_id, opcao_por_email, opcao_por_nome);
			else if(buscar)
			buscar_usuarios_ordenado(Usuario, Quantidade_de_cadastros_feitos, opcao_por_id, opcao_por_email, opcao_por_nome);
		}
		else if (opcao_usuario == 0)
		{
			continuar_opcao = false;
			LimparTela();
			printf("O USUARIO VOLTOU !!!\n\n");
		}else{}

	} while (continuar_opcao);
	/*-----------------------------------------*/
}
// Mostra os produtos de um usuario especifico
void visitar_usuario 							(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_do_usuario_logado) {

	LimparTela();
	listar_IDS(Usuario, Quantidade_de_cadastros_feitos, 0, 1, 1, 0);

	char ID_lido_para_visita[MAX_CARACTER_ID];
	int numero_do_usuario = -1;
	bool usuario_nao_achado = true;

	/*--- Area de receber o id para visita ---*/
	LimpaTelaTitulo("VISITAR USUARIO", "DIGITE", false);
	do {
		printf("ID do usuario para visita [ ENTER PARA VOLTAR ]: ");
		fgets(ID_lido_para_visita, MAX_CARACTER_ID, stdin);
		RemoveQuebraLinha(ID_lido_para_visita);
		/* VOLTA DE CASO O USUARIO ENTROU AQUI POR ENGANO */if(strcmp(ID_lido_para_visita,"\0") == 0){
			LimparTela();
			printf("O USUARIO VOLTOU !!!\n\n");
			return;
		}
		usuario_nao_achado = verifica_existencia_ID(Usuario, Quantidade_de_cadastros_feitos, &numero_do_usuario, NULL, ID_lido_para_visita, 1, 0);

	} while (usuario_nao_achado);
	printf("\n\n");
	/*----------------------------------------*/

	/*   USUARIO ENCONTRADO   */if (numero_do_usuario != -1) {

		LimparTela();
		printf("USUARIO ENCONTRADO --- ID: %s !!!", Usuario[numero_do_usuario].ID);

		if (Usuario[numero_do_usuario].numero_da_quantidade_de_produtos_publicados == 0) {
			printf("\nEsse usuario nao possui nenhum produto cadastrado !!!\n\n");
		}
		else {
			printf("\n\n");
			printf("<----------------------------------- PRODUTOS ----------------------------------->\n");
			listar_produtos(IMAGEM_NUMERO_COLUNAS, Usuario, Quantidade_de_cadastros_feitos, true, true, true, true, false, false, 0, 1, 0, numero_do_usuario, 0);
			printf("<-------------------------------------------------------------------------------->\n\n\n\n\n");

			detalhar_um_produto(Usuario, Quantidade_de_cadastros_feitos, numero_do_usuario_logado);
		}
	}
	/* USUARIO NAO ENCONTRADO */else {

		LimparTela();
		printf("VOLTOU AS OPCOES DE USUARIO !!!\n");
		printf("Motivo: Usuario nao encontrado\n\n");
	}
}
