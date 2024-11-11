/* ------- Perfil.c -------
* Funcao do QUICK SORT 
* Lista os IDs, tanto de usuario quanto produto (FUNCAO EXPORTADA)
* Busca usuario por parte do nome, ID ou email 
* Lista os usuarios por email, nome ou ID
* Funcao que recebe a opcao do usuario em busca ou listar (FUNCAO EXPORTADA)
* Visita um usuario (FUNCAO EXPORTADA)
--------------------------*/

/* ------ Produtos.c ------
* Funcao que aloca a avaliacao nova (FUNCAO EXPORTADA)
* Funcao que aloca o novo produto comprado (FUNCAO EXPORTADA)
* Funcao que aloca o novo produto favoritado (FUNCAO EXPORTADA)
* Altera estoque (FUNCAO EXPORTADA)
* imprime os produtos (FUNCAO EXPORTADA)
* Lista os produtos cadastrados (FUNCAO EXPORTADA)
* Detalha um produto (FUNCAO EXPORTADA)
* Favoritar um produto
* Avalia um Produto
* Compra um Produto 
--------------------------*/

/* ------- Fc_tela.c -------
* Funcao que limpa a tela do sistema (FUNCAO EXPORTADA)
* Funcao que limpa a tela e coloca um titulo (FUNCAO EXPORTADA)
* Funcao que remove a quebra de linha de uma string (FUNCAO EXPORTADA)
--------------------------*/

/* ------- Fc_verifificacao.c -------
* Funcao que verifica a existencia de um ID digitado (FUNCAO EXPORTADA)
* Funcao que verifica se uma opcao digitada eh valida para um inteiro (FUNCAO EXPORTADA)
------------------------------------*/

/* ------- Gera_imagem.c -------
* Funcao que carrega a imagem (FUNCAO EXPORTADA)  
* Funcao que imprime a imagem (FUNCAO EXPORTADA)
* Funcao que libera a imagem (FUNCAO EXPORTADA)
------------------------------------*/

/* ------- Estruturas.h -------
* Estrutura do Perfil
* Estrutura do Produto
* Estrutura d Avaliacao
* Estrutura do Favorito
* Estrutura dos Produtos_comprados
------------------------------------*/

/* -------- main.c --------
* Funcao que verifica a validade de um email
* Funcao que verifica a disponibilidade de um email
* Funcao que verifica a disponibilidade de um ID para o usuario
* Funcao que verifica a disponibilidade de um ID para um aproduto
* Funcao que aloca a memoria de um produto novo
* Funcao que aloca a memoria de um usuario novo
* Salva os dados em um arquivo
* Carrega os dados de um arquivo
* Mostra e seleciona a opcao no menu
* Lista os produtos comprados de um usuario
* Lista as avaliacoes de um produto
* Lista os favoritados de um usuario
* Faz o login
* Mostra as opcoes de login
* Desfavorita um produto
* Cadastro de um usuario novo
* Cadastro de um produto novo
---------------------------*/


/*--------- inclusoes ---------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Perfil.h"
#include "estruturas.h"
#include "Produtos.h"
#include "fc_tela.h"
#include "gera_imagem.h"
#include "fc_verificacao.h"
/*-----------------------------*/


/*--------------- Definicoes ---------------*/
#define JOIA 0
/*------------------------------------------*/


/* ---------------------- FUNCOES DE VERIFICACAO PARA CADASTRO ---------------------- */
// Verifica se o email possui as validades de um email ( @ e algo depois)
bool verificacao_de_validade_email 					(char email[]) {

	for (int i = 0; i < strlen(email); i++)
	{
		if (email[0] != '@' && email[i] == '@' && email[i + 1] != '\0')
		{
			return false;
		}
	}
	return true;
}
// Verifica se o email esta disponivel no sistema (unico)
bool verificacao_disponibilidade_email 				(char* email_para_verificacao, Perfil* Usuario, int Quantidade_de_cadastros_feitos, int Usuario_atual_de_cadastro) {

	for (int i = 0; i < Quantidade_de_cadastros_feitos; i++)
	{
		if (i != Usuario_atual_de_cadastro)
		{
			if (strcmp(email_para_verificacao, Usuario[i].email) == 0)
			{
				return true;
			}
		}
	}
	return false;
}
// Verifica se o ID DO USUARIO esta disponivel no sistema (unico)
bool verificacao_disponibilidade_ID_usuario 		(char* id_para_verificacao, Perfil* Usuario, int Quantidade_de_cadastros_feitos, int Usuario_atual_de_cadastro) {

	for (int i = 0; i < Quantidade_de_cadastros_feitos; i++)
	{
		if (i != Usuario_atual_de_cadastro)
		{
			if (strcmp(id_para_verificacao, Usuario[i].ID) == 0)
			{
				return true;
			}
		}
	}
	return false;
}
// Verifica se o ID DO PRODUTO esta disponivel no sistema (unico)
bool verificacao_disponibilidade_ID_produtos 		(Perfil* Usuario, int Quantidade_de_cadastros_feitos, char* id_para_verificacao, int numero_do_usuario) {

	for (int j = 0; j < Quantidade_de_cadastros_feitos; j++)
	{
		for (int i = 0; i < Usuario[j].Quantidade_de_produtos_cadastrados; i++)
		{
			if (j == numero_do_usuario && i == Usuario[numero_do_usuario].Produto_atual_para_cadastro)
			{
				continue;
			}
			if (strcmp(id_para_verificacao, Usuario[j].informacoes[i].ID) == 0)
			{
				return true;
			}
		}
	}
	return false;
}
// Verifica se o novo ID DO PRODUTO esta disponivel no sistema (unico)
bool verificacao_disponibilidade_ID_novo_produtos 	(Perfil* Usuario, int Quantidade_de_cadastros_feitos, char* id_para_verificacao, int numero_do_usuario, int numero_do_produto) {

	for (int j = 0; j < Quantidade_de_cadastros_feitos; j++)
	{
		for (int i = 0; i < Usuario[j].Quantidade_de_produtos_cadastrados; i++)
		{
			if (j == numero_do_usuario && i == numero_do_produto)
			{
				continue;
			}
			if (strcmp(id_para_verificacao, Usuario[j].informacoes[i].ID) == 0)
			{
				return true;
			}
		}
	}
	return false;
}
/* ---------------------------------------------------------------------------------- */


/* --------------------------------- ALOCA��O DE MEM�RIA --------------------------------- */
// Aloca a memoria do usuario novo cadastrado
Perfil* Alocar_memoria_usuario_novo 		   	(Perfil* Usuario, int Quantidade_de_cadastros_feitos) {
	return realloc(Usuario, Quantidade_de_cadastros_feitos * sizeof(Perfil));
}
// Aloca a memoria do produto novo cadastrado
Produtos* Alocar_memoria_produto_novo 		   	(Produtos* Produto, int Quantidade_de_produtos_cadastrados) {
	return realloc(Produto, Quantidade_de_produtos_cadastrados * sizeof(Produtos));
}
/* ----------------------------------------------------------------------------------------- */


/* -------------------------------- SALVAR / CARREGAR DADOS -------------------------------- */
// Salva todos os novos dados em um arquivo
void salvar_dados 								(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int Usuario_atual_de_cadastro, bool produto_cadastrado_no_sistema, FILE* Dados_arquivo) {

	fprintf(Dados_arquivo, "%d\n", Quantidade_de_cadastros_feitos);
	fprintf(Dados_arquivo, "%d\n", Usuario_atual_de_cadastro);
	fprintf(Dados_arquivo, "%d\n", (produto_cadastrado_no_sistema? 1 : 0));

	for (int i = 0; i < Quantidade_de_cadastros_feitos; i++) {

		fprintf(Dados_arquivo, "%s\n", Usuario[i].nome);
		fprintf(Dados_arquivo, "%s\n", Usuario[i].ID);
		fprintf(Dados_arquivo, "%s\n", Usuario[i].email);
		fprintf(Dados_arquivo, "%s\n", Usuario[i].senha);
		fprintf(Dados_arquivo, "%d\n", (Usuario[i].logado ? 1 : 0));

		fprintf(Dados_arquivo, "%d\n", Usuario[i].Quantidade_de_produtos_cadastrados);
		fprintf(Dados_arquivo, "%d\n", Usuario[i].numero_da_quantidade_de_produtos_publicados);
		fprintf(Dados_arquivo, "%d\n", Usuario[i].Produto_atual_para_cadastro);
		for (int j = 0; j < Usuario[i].Quantidade_de_produtos_cadastrados; j++) {

			fprintf(Dados_arquivo, "%d\n", (Usuario[i].informacoes[j].produto_publicado ? 1 : 0));
			fprintf(Dados_arquivo, "%s\n", Usuario[i].informacoes[j].ID);
			fprintf(Dados_arquivo, "%s\n", Usuario[i].informacoes[j].Descricao);

			fprintf(Dados_arquivo, "%d\n", Usuario[i].informacoes[j].quantidade_de_imagens);
			for(int img = 0 ; img < Usuario[i].informacoes[j].quantidade_de_imagens; img++){

				fprintf(Dados_arquivo, "%s\n", Usuario[i].informacoes[j].url[img]);

			}

			fprintf(Dados_arquivo, "%d\n", Usuario[i].informacoes[j].Quantidade);
			fprintf(Dados_arquivo, "%f\n", Usuario[i].informacoes[j].preco);
			fprintf(Dados_arquivo, "%d\n", Usuario[i].informacoes[j].numero_de_avaliacoes);
			fprintf(Dados_arquivo, "%d\n", Usuario[i].informacoes[j].avaliacao_atual);

			for (int t = 0; t < Usuario[i].informacoes[j].numero_de_avaliacoes; t++) {

				fprintf(Dados_arquivo, "%s\n", Usuario[i].informacoes[j].avaliacoes[t].ID_do_usuario);
				fprintf(Dados_arquivo, "%s\n", Usuario[i].informacoes[j].avaliacoes[t].TEXTO);

			}
		}
		
		fprintf(Dados_arquivo, "%d\n", Usuario[i].quantidade_de_produtos_favoritados);
		fprintf(Dados_arquivo, "%d\n", Usuario[i].numero_da_quantidade_de_favoritos_de_um_usuario);
		fprintf(Dados_arquivo, "%d\n", Usuario[i].numero_atual_favoritamento);
		for(int t = 0; t < Usuario[i].quantidade_de_produtos_favoritados; t++){

			fprintf(Dados_arquivo, "%d\n", Usuario[i].favoritos[t].posicao_do_usuario_dono);
			fprintf(Dados_arquivo, "%d\n", Usuario[i].favoritos[t].posicao_do_produto);
			fprintf(Dados_arquivo, "%d\n", (Usuario[i].favoritos[t].favorito? 1 : 0));
		}
	
		fprintf(Dados_arquivo, "%d\n", Usuario[i].quantidade_de_produtos_comprados);
		fprintf(Dados_arquivo, "%d\n", Usuario[i].numero_atual_de_compra);
		for(int b = 0 ; b < Usuario[i].quantidade_de_produtos_comprados; b++){
			fprintf(Dados_arquivo, "%d\n", Usuario[i].produtos_comprados[b].posicao_do_usuario_dono);
			fprintf(Dados_arquivo, "%d\n", Usuario[i].produtos_comprados[b].posicao_do_produto);
		}
	}

}
// Carrega todos os dados salvos no arquivo
Perfil* carregar_dados 							(Perfil* Usuario, int* Quantidade_de_cadastros_feitos, int* Usuario_atual_de_cadastro, bool* produto_cadastrado_no_sistema, FILE* Dados_arquivo, int *numero_do_usuario_logado) {

	int n_lido_logado;
	int n_lido_favorito;
	int n_lido_produto_cadastrado;
	int n_lido_produto_publicado;

	(void)fscanf(Dados_arquivo, "%d\n", Quantidade_de_cadastros_feitos);
	(void)fscanf(Dados_arquivo, "%d\n", Usuario_atual_de_cadastro);
	(void)fscanf(Dados_arquivo, "%d\n", &n_lido_produto_cadastrado);

	*produto_cadastrado_no_sistema = (n_lido_produto_cadastrado == 1? true : false);

	Usuario = NULL;
	Usuario = Alocar_memoria_usuario_novo(Usuario, *Quantidade_de_cadastros_feitos);

	for (int i = 0; i < *Quantidade_de_cadastros_feitos; i++) {

		fgets(Usuario[i].nome, MAX_CARACTER_NOME, Dados_arquivo);
		RemoveQuebraLinha(Usuario[i].nome);

		fgets(Usuario[i].ID, MAX_CARACTER_ID, Dados_arquivo);
		RemoveQuebraLinha(Usuario[i].ID);

		fgets(Usuario[i].email, MAX_CARACTER_EMAIL, Dados_arquivo);
		RemoveQuebraLinha(Usuario[i].email);

		fgets(Usuario[i].senha, MAX_CARACTER_SENHA, Dados_arquivo);
		RemoveQuebraLinha(Usuario[i].senha);

		(void)fscanf(Dados_arquivo, "%d\n", &n_lido_logado);

		Usuario[i].logado = (n_lido_logado == 1 ? true : false);

		(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].Quantidade_de_produtos_cadastrados);
		(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].numero_da_quantidade_de_produtos_publicados);
		(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].Produto_atual_para_cadastro);

		Usuario[i].informacoes = NULL;
		Usuario[i].informacoes = Alocar_memoria_produto_novo(Usuario[i].informacoes, Usuario[i].Quantidade_de_produtos_cadastrados);

		for (int j = 0; j < Usuario[i].Quantidade_de_produtos_cadastrados; j++) {

			(void)fscanf(Dados_arquivo, "%d\n", &n_lido_produto_publicado);
			Usuario[i].informacoes[j].produto_publicado = (n_lido_produto_publicado == 1? true : false);

			fgets(Usuario[i].informacoes[j].ID, MAX_CARACTER_ID, Dados_arquivo);
			RemoveQuebraLinha(Usuario[i].informacoes[j].ID);

			fgets(Usuario[i].informacoes[j].Descricao, MAX_CARACTER_DESCRICAO, Dados_arquivo);
			RemoveQuebraLinha(Usuario[i].informacoes[j].Descricao);

			(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].informacoes[j].quantidade_de_imagens);

			Usuario[i].informacoes[j].url = NULL;
			Usuario[i].informacoes[j].url = realloc(Usuario[i].informacoes[j].url, Usuario[i].informacoes[j].quantidade_de_imagens * sizeof(char*));

			for(int t = 0 ; t < Usuario[i].informacoes[j].quantidade_de_imagens ; t++){	
				Usuario[i].informacoes[j].url[t] = malloc(MAX_CARACTER_URL * sizeof(char));
			}
			
			for(int img = 0 ; img < Usuario[i].informacoes[j].quantidade_de_imagens; img++){

				fgets(Usuario[i].informacoes[j].url[img], MAX_CARACTER_URL, Dados_arquivo);
				RemoveQuebraLinha(Usuario[i].informacoes[j].url[img]);
			}

			(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].informacoes[j].Quantidade);
			(void)fscanf(Dados_arquivo, "%f\n", &Usuario[i].informacoes[j].preco);
			(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].informacoes[j].numero_de_avaliacoes);
			(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].informacoes[j].avaliacao_atual);

			Usuario[i].informacoes[j].avaliacoes = NULL;
			Usuario[i].informacoes[j].avaliacoes = Alocar_memoria_avaliacao_novo(Usuario, i, j);

			for (int t = 0; t < Usuario[i].informacoes[j].numero_de_avaliacoes; t++) {

				fgets(Usuario[i].informacoes[j].avaliacoes[t].ID_do_usuario, MAX_CARACTER_ID, Dados_arquivo);
				RemoveQuebraLinha(Usuario[i].informacoes[j].avaliacoes[t].ID_do_usuario);

				fgets(Usuario[i].informacoes[j].avaliacoes[t].TEXTO, MAX_CARACTER_AVALIACAO, Dados_arquivo);
				RemoveQuebraLinha(Usuario[i].informacoes[j].avaliacoes[t].TEXTO);

			}
		}

		(void)fscanf(Dados_arquivo, "%d ", &Usuario[i].quantidade_de_produtos_favoritados);
		(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].numero_da_quantidade_de_favoritos_de_um_usuario);
		(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].numero_atual_favoritamento);

		Usuario[i].favoritos = NULL;
		Usuario[i].favoritos = Alocar_memoria_favorito_novo(Usuario[i].favoritos, Usuario[i].quantidade_de_produtos_favoritados);

		for(int t = 0; t < Usuario[i].quantidade_de_produtos_favoritados; t++){

			(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].favoritos[t].posicao_do_usuario_dono);
			(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].favoritos[t].posicao_do_produto);
			(void)fscanf(Dados_arquivo, "%d\n", &n_lido_favorito);
			Usuario[i].favoritos[t].favorito = (n_lido_favorito == 1? true : false);
		}
	
		(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].quantidade_de_produtos_comprados);
		(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].numero_atual_de_compra);
		Usuario[i].produtos_comprados = NULL; // nigger
		Usuario[i].produtos_comprados = Alocar_memoria_novo_produto_comprado(Usuario[i].produtos_comprados, Usuario[i].quantidade_de_produtos_comprados);
		
		for(int b = 0 ; b < Usuario[i].quantidade_de_produtos_comprados; b++){
			(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].produtos_comprados[b].posicao_do_usuario_dono);
			(void)fscanf(Dados_arquivo, "%d\n", &Usuario[i].produtos_comprados[b].posicao_do_produto);
		}
	}
	for(int i = 0 ; i < *Quantidade_de_cadastros_feitos; i++){
		if(Usuario[i].logado){
			*numero_do_usuario_logado = i;
		}
	}

	return Usuario;

}
/* ----------------------------------------------------------------------------------------- */


/* -------------------------------------------------- FUNCOES ESPECIFICAS -------------------------------------------------- */
// Opcao do usuario no menu principal
void selecionar_opcao 							(Perfil* usuario, int Quantidade_de_cadastros_feitos, int* opcao, int numero_do_usuario_logado) {

	printf("|---- Usuario logado: %s ----|\n", (numero_do_usuario_logado == -1? "Fazer login" : usuario[numero_do_usuario_logado].nome ));
	printf("|-------------------------------------------------------------------------------------------------|\n");
	printf("|             ___   ___   ___   ___     __  __     _     ___   _  __  ___   _____                 |\n");
	printf("|            | __| | _ \\ | __| | __|   |  \\/  |   /_\\   | _ \\ | |/ / | __| |_   _|                |\n");
	printf("|            | _|  |   / | _|  | _|    | |\\/| |  / _ \\  |   / | ' <  | _|    | |                  |\n");
	printf("|            |_|   |_|_\\ |___| |___|   |_|  |_| /_/ \\_\\ |_|_\\ |_|\\_\\ |___|   |_|                  |\n");
	printf("|                                                                                                 |\n");
	printf("|                                                                                                 |\n");
	printf("|                                 |-----------------------------|                                 |\n");
	printf("|                                 |  1) Area de Usuario         |                                 |\n");
	printf("|                                 |  2) Area de Produto         |                                 |\n");
	printf("|                                 |  3) Area de Avaliacao       |                                 |\n");
	if(numero_do_usuario_logado != -1)
	printf("|                                 |  4) Area de Favoritos       |                                 |\n");
	printf("|                                 |  0) sair                    |                                 |\n");
	printf("|                                 |-----------------------------|                                 |\n");
	printf("|                                                                                                 |\n");
	if(numero_do_usuario_logado == -1)
	printf("|              ALGUMAS FUNCOES APARECERAO DEPOIS QUE UM USUARIO FOR LOGADO NO SISTEMA             |\n");
	else
	printf("|                                                                                                 |\n");
	printf("|-------------------------------------------------------------------------------------------------|\n\n");

	printf("Opcao: ");
	recebe_numero_valido(opcao);
}
// Lista os produtos comprados por um usuario
void listar_produtos_comprados_de_um_usuario    (Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_usuario_logado){

	asciiImg_t* img;

	LimparTela();

	if(Usuario[numero_usuario_logado].quantidade_de_produtos_comprados == 0){
		printf("ESSE USUARIO NAO POSSUI NENHUM PRODUTO COMPRADO !!!\n\n");

	}else{
		
		printf("---------- OS %d PRODUTOS COMPRADOS PELO USUARIO [ %s ]\n\n",Usuario[numero_usuario_logado].quantidade_de_produtos_comprados, Usuario[numero_usuario_logado].ID);

		printf("|----------------------------- PRODUTOS COMPRADOS ----------------------------|\n\n");
		for(int i = 0 ; i < Usuario[numero_usuario_logado].quantidade_de_produtos_comprados; i++){

			int posicao_do_usuario_dono_do_produto_comprado = Usuario[numero_usuario_logado].produtos_comprados[i].posicao_do_usuario_dono;
			int posicao_do_produto_comprado_do_usuario_dono = Usuario[numero_usuario_logado].produtos_comprados[i].posicao_do_produto;

			printf("__ Produto [%d] __\n", i + 1);
			printf("ID.........: %s\n", Usuario[posicao_do_usuario_dono_do_produto_comprado].informacoes[posicao_do_produto_comprado_do_usuario_dono].ID);
			printf("Preco......: %.2f\n", Usuario[posicao_do_usuario_dono_do_produto_comprado].informacoes[posicao_do_produto_comprado_do_usuario_dono].preco);
			printf("Descricao..: %s\n", Usuario[posicao_do_usuario_dono_do_produto_comprado].informacoes[posicao_do_produto_comprado_do_usuario_dono].Descricao);

			/*---------------------------- AREA PARA GERAR A IMAGEM ----------------------------*/
			for(int w = 0 ; w < Usuario[posicao_do_usuario_dono_do_produto_comprado].informacoes[posicao_do_produto_comprado_do_usuario_dono].quantidade_de_imagens; w++){

						img = insta_carregaImagem(Usuario[posicao_do_usuario_dono_do_produto_comprado].informacoes[posicao_do_produto_comprado_do_usuario_dono].url[w], MODO_IMAGEM, IMAGEM_NUMERO_COLUNAS);
						if (img == NULL)
						{
							// Falha ao carregar a imagem
							fprintf(stderr, "Falha ao carregar a imagem da URL %s\n", Usuario[posicao_do_usuario_dono_do_produto_comprado].informacoes[posicao_do_produto_comprado_do_usuario_dono].url[w]);
						}
						insta_imprimeImagem(img);
						insta_liberaImagem(img);
						printf("\n");
				}
			/*----------------------------------------------------------------------------------*/
		}
		printf("|-------------------------------------------------------------------------------|\n\n\n");
	}
}
// Lista todoas as avaliacoes de um produto
void Listar_avaliacoes_de_um_produto 			(Perfil* Usuario, int Quantidade_de_cadastros_feitos) {

	LimparTela();
	listar_IDS(Usuario, Quantidade_de_cadastros_feitos, 1 , 0, 0, 0);

	char ID_Produto_comentarios[MAX_CARACTER_ID];
	int numero_do_usuario_dono = -1;
	int numero_do_produto = -1;
	bool Produto_nao_achado = true;


	/*--- Area de receber o id do produto para mostrar as avaliacoes ---*/
	LimpaTelaTitulo("LISTAR AVALIACOES", "DIGITE", false);
	do {
		printf("ID do Produto para mostrar os suas avaliacoes\n[ ENTER PARA VOLTAR ]: ");
		fgets(ID_Produto_comentarios, MAX_CARACTER_ID, stdin);
		RemoveQuebraLinha(ID_Produto_comentarios);
		/* VOLTA DE CASO O USUARIO ENTROU AQUI POR ENGANO */if(strcmp(ID_Produto_comentarios,"\0") == 0){
			LimparTela();
			printf("O USUARIO VOLTOU !!!\n\n");
			return;
			}
		Produto_nao_achado = verifica_existencia_ID(Usuario, Quantidade_de_cadastros_feitos, &numero_do_usuario_dono, &numero_do_produto, ID_Produto_comentarios, 0 , 1);

	} while (Produto_nao_achado);
	printf("\n\n");
	/*------------------------------------------------------------------*/

	/*   PRODUTO ENCONTRADO   */if (numero_do_produto != -1) {
		LimparTela();
		if(Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].numero_de_avaliacoes == 0){
			printf("Esse produto nao contem nenhuma avaliacao ainda !!!\n\n");

		}else{
			printf("-------- COMENTARIOS DO PRODUTO [ %s ]\n", Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].ID);
			for (int i = 0; i < Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].numero_de_avaliacoes; i++) {

				printf("Comentario do [ %s ]\n: %s\n", Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].avaliacoes[i].ID_do_usuario,
					Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].avaliacoes[i].TEXTO);
			}
			printf("-------------------------------------\n\n\n");
		}
	}
	/* PRODUTO NAO ENCONTRADO */else {

		LimparTela();
		printf("VOLTOU AS OPCOES DE AVALIACAO !!!\n");
		printf("Motivo: Produto nao encontrado\n\n");

	}
}
// Lista todos os produtos favoritados de um usuario
void listar_produtos_favoritados_de_um_usuario  (Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_usuario_logado){

	LimparTela();
	if(Usuario[numero_usuario_logado].numero_da_quantidade_de_favoritos_de_um_usuario == 0){

		printf("ESSE USUARIO NAO POSSIU NENHUM PRODUTO FAVORITADO !!!\n\n");
	}else{
		printf("---------- OS %d PRODUTOS FAVORITADOS PELO USUARIO [ %s ]\n\n",Usuario[numero_usuario_logado].numero_da_quantidade_de_favoritos_de_um_usuario, Usuario[numero_usuario_logado].ID);

		printf("|----------------------------- PRODUTOS FAVORITADOS ----------------------------|\n\n");
		for(int i = 0 ; i < Usuario[numero_usuario_logado].quantidade_de_produtos_favoritados; i++){
			if(Usuario[numero_usuario_logado].favoritos[i].favorito){

				int numero_usuario_dono_produto_favoritado = Usuario[numero_usuario_logado].favoritos[i].posicao_do_usuario_dono;
				int numero_produto_favoritado_do_usuario_dono = Usuario[numero_usuario_logado].favoritos[i].posicao_do_produto;

				printf("__ Produto [%d] __\n", i + 1);
				if(Usuario[numero_usuario_dono_produto_favoritado].informacoes[numero_produto_favoritado_do_usuario_dono].produto_publicado){
					listar_produtos(IMAGEM_NUMERO_COLUNAS, Usuario, Quantidade_de_cadastros_feitos, true, true, true, true, true, true, 0, 1, 1, numero_usuario_dono_produto_favoritado, numero_produto_favoritado_do_usuario_dono);
				}else{
					printf("ESSE PRODUTO NAO EXISTE MAIS !!!\nRemovendo...\n");
					Usuario[numero_usuario_logado].favoritos[i].favorito = false;
					Usuario[numero_usuario_logado].numero_da_quantidade_de_favoritos_de_um_usuario--;
				}
				printf("\n");
			}
		}
		printf("|-------------------------------------------------------------------------------|\n\n\n");
	}
}
// Faz um login de um usuario
void fazer_login 								(Perfil* Usuario, bool login_com_id, bool login_com_email, int Quantidade_de_cadastros_feitos, int * numero_do_usuario_logado) {

	char ID_lido[MAX_CARACTER_ID];
	char email_lido[MAX_CARACTER_EMAIL];
	char senha_lido[MAX_CARACTER_SENHA];
	bool continuar = true;
	char opcao;

	do {
		LimpaTelaTitulo("FAZER LOGIN", "DIGITE O SEU", true);

		if (login_com_email) {
			printf("Email: ");
			fgets(email_lido, MAX_CARACTER_EMAIL, stdin);
			RemoveQuebraLinha(email_lido);
		}
		if (login_com_id) {
			printf("ID: ");
			fgets(ID_lido, MAX_CARACTER_ID, stdin);
			RemoveQuebraLinha(ID_lido);
		}

		printf("Senha: ");
		fgets(senha_lido, MAX_CARACTER_SENHA, stdin);
		RemoveQuebraLinha(senha_lido);


		for (int i = 0; i < Quantidade_de_cadastros_feitos; i++) {

			if (login_com_email) {

				if (strcmp(email_lido, Usuario[i].email) == 0 && strcmp(senha_lido, Usuario[i].senha) == 0) {

					if(Usuario[i].logado){

						LimparTela();
						printf("USUARIO ' %s <-> %s ' JA ESTA LOGADO NO SISTEMA !!!\n\n\n", Usuario[i].ID, Usuario[i].nome);
						continuar = false;

					}else{

						for (int j = 0; j < Quantidade_de_cadastros_feitos; j++) {
							Usuario[j].logado = false;
						}
						Usuario[i].logado = true;
						continuar = false;
						*numero_do_usuario_logado = i;
						LimparTela();
						printf("USUARIO ' %s <-> %s ' LOGADO COM SUCESSO !!!\n", Usuario[i].ID, Usuario[i].nome);
						printf("_ BEM VINDO _\n\n\n");
					}
				}
			}
			if (login_com_id) {

				if (strcmp(ID_lido, Usuario[i].ID) == 0 && strcmp(senha_lido, Usuario[i].senha) == 0) {
					
					if(Usuario[i].logado){

						LimparTela();
						printf("USUARIO ' %s <-> %s ' JA ESTA LOGADO NO SISTEMA !!!\n\n\n", Usuario[i].ID, Usuario[i].nome);
						continuar = false;

					}else{

						for (int j = 0; j < Quantidade_de_cadastros_feitos; j++) {
							Usuario[j].logado = false;
						}

						Usuario[i].logado = true;
						continuar = false;
						*numero_do_usuario_logado = i;

						LimparTela();
						printf("USUARIO ' %s <-> %s ' LOGADO COM SUCESSO !!!\n", Usuario[i].ID, Usuario[i].nome);
						printf("_ BEM VINDO _\n\n\n");

					}
				}
			}
		}

		if (continuar) {

			printf("\n\nEsses dados nao correspondem a nenhum usuario !!!\n");
			printf("Deseja Digitar novamente [ s / n ]: ");
			(void)scanf("%c%*c", &opcao);

			if (opcao == 's' || opcao == 'S') {
				continuar = true;

			}
			else {
				LimparTela();
				continuar = false;
			}

		}

	} while (continuar);
}
// Pega a opcao de login do usuario, por ID ou por EMAIL
void opcao_login_usuario 						(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int *numero_do_usuario_logado) {

	int opcao;
	bool login_com_id = false;
	bool login_com_email = false;
	bool continuar_opcao_de_login = true;

	do{
		printf("|>----- OPCAO DE LOGIN -----<|\n");
		printf("  1) Logar com ID			  \n");
		printf("  2) logar com Email		  \n");
		printf("  0) Voltar para o menu		  \n");
		printf("|>--------------------------<|\n\n");

		printf("Opcao: ");
		(void)scanf("%d%*c", &opcao);

		switch (opcao)
		{
		case 1:
			login_com_id = true;
			login_com_email = false;
			fazer_login(Usuario, login_com_id, login_com_email, Quantidade_de_cadastros_feitos, numero_do_usuario_logado);
			break;

		case 2:
			login_com_email = true;
			login_com_id = false;
			fazer_login(Usuario, login_com_id, login_com_email, Quantidade_de_cadastros_feitos, numero_do_usuario_logado);
			break;

		case 0:
			LimparTela();
			continuar_opcao_de_login = false;
			printf("O USUARIO VOLTOU !!!\n\n");
			break;
		
		default:
			LimparTela();
			printf("OPCAO INVALIDA !!!\n");
		}

	}while(continuar_opcao_de_login);
}
// Edita um produto publicado no sistema
void editar_produto 							(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_usuario_logado){

	LimparTela();
	if(Usuario[numero_usuario_logado].Quantidade_de_produtos_cadastrados == 0){

		printf("ESSE USUARIO NAO POSSIU NENHUM PRODUTO CADASTRADO !!!\n\n");
	}else{

		printf("---------- OS %d PRODUTOS CADASTRADOS PELO USUARIO [ %s ]\n\n",Usuario[numero_usuario_logado].numero_da_quantidade_de_produtos_publicados, Usuario[numero_usuario_logado].ID);

		printf("|----------------------------- PRODUTOS CADASTRADOS ----------------------------|\n\n");
		for(int i = 0 ; i < Usuario[numero_usuario_logado].Quantidade_de_produtos_cadastrados; i++){
			if(Usuario[numero_usuario_logado].informacoes[i].produto_publicado){

				printf("__ Produto [%d] __\n", i + 1);
				listar_produtos((IMAGEM_NUMERO_COLUNAS - 50), Usuario, Quantidade_de_cadastros_feitos, true, true, true, false, false, false, 0, 1, 1, numero_usuario_logado, i);
				printf("\n");
			}
		}
		printf("|--------------------------------------------------------------------------------|\n\n\n");

		char ID_Produto_para_editar[MAX_CARACTER_ID];
		int numero_do_produto = -1;
		int numero_do_usuario = -1;
		bool Produto_nao_achado = true;
		int Opcao;
		bool continuar = true;
		bool ID_indisponivel = true;

		/*--- Area de receber o id do produto a ser editado ---*/
		do {
			printf("ID do Produto para editar [ENTER PARA VOLTAR]: ");
			fgets(ID_Produto_para_editar, MAX_CARACTER_ID, stdin);
			RemoveQuebraLinha(ID_Produto_para_editar);
			/* VOLTA DE CASO O USUARIO ENTROU AQUI POR ENGANO */if(strcmp(ID_Produto_para_editar,"\0") == 0){
				LimparTela();
				printf("O USUARIO VOLTOU !!!\n\n");
				return;
			}
			Produto_nao_achado = verifica_existencia_ID(Usuario, Quantidade_de_cadastros_feitos, &numero_do_usuario, &numero_do_produto, ID_Produto_para_editar, 0, 1);

		} while (Produto_nao_achado);
		printf("\n\n");
		/*-----------------------------------------------------*/

		/* PRODUTO NAO ENCONTRADO */if (numero_do_produto == -1) {
				LimparTela();
				printf("VOLTOU AS OPCOES DE PRODUTO !!!\n");
				printf("Motivo: Produto nao encontrado\n\n");

			}
		/*   PRODUTO ENCONTRADO   */else {

			printf("|>--- MENU DE OPCOES PARA EDITAR ---<|\n");
			printf("  1 - ID							\n");
			printf("  2 - Quantidade					\n");
			printf("  3 - Preco							\n");
			printf("  4 - Descricao						\n");
			printf("  0 - Voltar'						\n");
			printf("|>----------------------------------<|\n\n");

			do {

				printf("Opcao: ");
				recebe_numero_valido(&Opcao);

				switch(Opcao) {
				
					case 1:

						/*--------------- Area do ID --------------*/
						do {

							printf("Digite o novo ID do produto....: ");
							fgets(Usuario[numero_usuario_logado].informacoes[numero_do_produto].ID, MAX_CARACTER_ID, stdin);
							RemoveQuebraLinha(Usuario[numero_usuario_logado].informacoes[numero_do_produto].ID);

							ID_indisponivel = verificacao_disponibilidade_ID_novo_produtos(Usuario, Quantidade_de_cadastros_feitos, Usuario[numero_usuario_logado].informacoes[numero_do_produto].ID, numero_usuario_logado, numero_do_produto);
							
							if (ID_indisponivel)
							{
								printf("\nId indisponivel !!!\nDigite novamente\n");
							}

						} while (ID_indisponivel);
						/*-----------------------------------------*/
	
						continuar = false;
						break;

					case 2:
						continuar = false;
						break;

					case 3:
						continuar = false;
						break;

					case 4:
						continuar = false;
						break;

					case 0:
						printf("\n");
						continuar = false;
						break;

					default:
							printf("Opcao Invalida\n");
						break;
				}

			}while(continuar);
		}
	}
}
// Apaga um produto publicado por um usuario
void apaga_produto_publicado 					(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_usuario_logado){

	LimparTela();
	if(Usuario[numero_usuario_logado].Quantidade_de_produtos_cadastrados == 0){

		printf("ESSE USUARIO NAO POSSIU NENHUM PRODUTO CADASTRADO !!!\n\n");
	}else{

		printf("---------- OS %d PRODUTOS CADASTRADOS PELO USUARIO [ %s ]\n\n",Usuario[numero_usuario_logado].numero_da_quantidade_de_produtos_publicados, Usuario[numero_usuario_logado].ID);

		printf("|----------------------------- PRODUTOS CADASTRADOS ----------------------------|\n\n");
		for(int i = 0 ; i < Usuario[numero_usuario_logado].Quantidade_de_produtos_cadastrados; i++){
			if(Usuario[numero_usuario_logado].informacoes[i].produto_publicado){

				printf("__ Produto [%d] __\n", i + 1);
				listar_produtos((IMAGEM_NUMERO_COLUNAS - 50), Usuario, Quantidade_de_cadastros_feitos, true, true, true, false, false, false, 0, 1, 1, numero_usuario_logado, i);
				printf("\n");
			}
		}
		printf("|--------------------------------------------------------------------------------|\n\n\n");

		char ID_Produto_para_apagar[MAX_CARACTER_ID];
		int numero_do_produto = -1;
		int numero_do_usuario = -1;
		bool Produto_nao_achado = true;

		/*--- Area de receber o id do produto a ser apagado ---*/
		do {
			printf("ID do Produto para apagar [ENTER PARA VOLTAR]: ");
			fgets(ID_Produto_para_apagar, MAX_CARACTER_ID, stdin);
			RemoveQuebraLinha(ID_Produto_para_apagar);
			/* VOLTA DE CASO O USUARIO ENTROU AQUI POR ENGANO */if(strcmp(ID_Produto_para_apagar,"\0") == 0){
				LimparTela();
				printf("O USUARIO VOLTOU !!!\n\n");
				return;
			}
			Produto_nao_achado = verifica_existencia_ID(Usuario, Quantidade_de_cadastros_feitos, &numero_do_usuario, &numero_do_produto, ID_Produto_para_apagar, 0, 1);

		} while (Produto_nao_achado);
		printf("\n\n");
		/*-----------------------------------------------------*/

		/* PRODUTO NAO ENCONTRADO */if (numero_do_produto == -1) {
				LimparTela();
				printf("VOLTOU AS OPCOES DE PRODUTO !!!\n");
				printf("Motivo: Produto nao encontrado\n\n");

			}
		/*   PRODUTO ENCONTRADO   */else {

			Usuario[numero_usuario_logado].informacoes[numero_do_produto].produto_publicado = false;
			Usuario[numero_usuario_logado].numero_da_quantidade_de_produtos_publicados--;
			LimparTela();
			printf("PRODUTO %s APAGADO COM SUCESSO !!!\n\n", Usuario[numero_usuario_logado].informacoes[numero_do_produto].ID);
			strcpy(Usuario[numero_usuario_logado].informacoes[numero_do_produto].ID, "-1");
		}
	}
}
// Desfavorita um produto do usuario logado
void desfavoritar_um_produto					(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_usuario_logado){

	printf("-------------------------------- DESFAVORITAR UM PRODUTO --------------------------------\n\n");
	listar_produtos_favoritados_de_um_usuario(Usuario, Quantidade_de_cadastros_feitos, numero_usuario_logado);

	char ID_Produto_para_desfavoritar[MAX_CARACTER_ID];
	int numero_do_usuario_dono = -1;
	int numero_do_produto = -1;
	bool Produto_nao_achado = true;

	/*--- Area de receber o id do produto a ser desfavoritado ---*/
	do {
			printf("ID do Produto para Desfavoritar: ");
			fgets(ID_Produto_para_desfavoritar, MAX_CARACTER_ID, stdin);
			RemoveQuebraLinha(ID_Produto_para_desfavoritar);
			Produto_nao_achado = verifica_existencia_ID(Usuario, Quantidade_de_cadastros_feitos, &numero_do_usuario_dono, &numero_do_produto, ID_Produto_para_desfavoritar, 0, 1);

	} while (Produto_nao_achado);
	printf("\n\n");
	/*--------------------------------------------------------*/

	/* PRODUTO NAO ENCONTRADO */if (numero_do_produto == -1) {

			LimparTela();
			printf("VOLTOU AS OPCOES DE PRODUTO !!!\n");
			printf("Motivo: Produto nao encontrado\n\n");

		}
	/*   PRODUTO ENCONTRADO   */else {

		for(int i = 0 ; i < Usuario[numero_usuario_logado].quantidade_de_produtos_favoritados; i++){

			int numero_usuario_dono_produto_favoritado = Usuario[numero_usuario_logado].favoritos[i].posicao_do_usuario_dono;
			int numero_produto_favoritado_do_usuario_dono = Usuario[numero_usuario_logado].favoritos[i].posicao_do_produto;

			if(strcmp(ID_Produto_para_desfavoritar, Usuario[numero_usuario_dono_produto_favoritado].informacoes[numero_produto_favoritado_do_usuario_dono].ID) == 0){

				Usuario[numero_usuario_logado].favoritos[i].favorito = false;
				Usuario[numero_usuario_logado].numero_da_quantidade_de_favoritos_de_um_usuario--;
				LimparTela();
				printf("PRODUTO DESFAVORITADO COM SUCESSO !!!\n\n");
			}
		}
	}
}
// Area de cadastro de um NOVO USUARIO no sistema
void cadastrar_usuario_novo 					(Perfil* Usuario_atual, Perfil* Usuario, int Quantidade_de_cadastros_feitos, int Usuario_atual_de_cadastro) {

	bool Email_indisponivel = true;
	bool Email_invalido = true;
	bool ID_indisponivel = true;

	/*--------------- Area do ID --------------*/
	LimpaTelaTitulo("CADASTRAR USUARIO", "DIGITE", true);
	do{
		printf("ID: ");
		fgets(Usuario_atual->ID, MAX_CARACTER_ID, stdin);
		RemoveQuebraLinha(Usuario_atual->ID);

		ID_indisponivel = verificacao_disponibilidade_ID_usuario(Usuario_atual->ID, Usuario, Quantidade_de_cadastros_feitos, Usuario_atual_de_cadastro);

		if (ID_indisponivel){
			LimparTela();
			printf("----- CADASTRAR NOVO USUARIO -----\n\n");
			printf("Id indisponivel !!!\nDigite novamente o ");
		}

	} while (ID_indisponivel);
	/*-----------------------------------------*/

	/*------------- Area de Nome --------------*/
	printf("Nome: ");
	fgets(Usuario_atual->nome, MAX_CARACTER_NOME, stdin);
	RemoveQuebraLinha(Usuario_atual->nome);
	/*-----------------------------------------*/

	/*------------- Area de Email -------------*/
	do{
		printf("Email: ");
		fgets(Usuario_atual->email, MAX_CARACTER_EMAIL, stdin);
		RemoveQuebraLinha(Usuario_atual->email);

		Email_invalido = verificacao_de_validade_email(Usuario_atual->email);
		Email_indisponivel = verificacao_disponibilidade_email(Usuario_atual->email, Usuario, Quantidade_de_cadastros_feitos, Usuario_atual_de_cadastro);

		if (Email_invalido){
			printf("Email invalido !!!\nDigite novamente o ");
		}
		if (Email_indisponivel){
			printf("Email indisponivel !!!\nDigite novamente o ");
		}

	} while (Email_invalido || Email_indisponivel);
	/*-----------------------------------------*/

	/*------------- Area de senha -------------*/
	printf("Senha: ");
	fgets(Usuario_atual->senha, MAX_CARACTER_SENHA, stdin);
	RemoveQuebraLinha(Usuario_atual->senha);
	/*-----------------------------------------*/

	Usuario_atual->logado = false;

	Usuario_atual->informacoes = NULL;
	Usuario_atual->Quantidade_de_produtos_cadastrados = 0;
	Usuario_atual->numero_da_quantidade_de_produtos_publicados = 0;
	Usuario_atual->Produto_atual_para_cadastro = 0;

	Usuario_atual->favoritos = NULL;
	Usuario_atual->numero_atual_favoritamento = 0;
	Usuario_atual->numero_da_quantidade_de_favoritos_de_um_usuario = 0;
	Usuario_atual->quantidade_de_produtos_favoritados = 0;
	
    Usuario_atual->produtos_comprados = NULL;
	Usuario_atual->quantidade_de_produtos_comprados = 0;
	Usuario_atual->numero_atual_de_compra = 0;
	
	LimparTela();
	printf("USUARIO CADASTRADO COM SUCESSO !!!\n\n");
}
// Area de cadastro de um NOVO PRODUTO no sistema
void cadastrar_produto_novo 					(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_usuario_logado) {

	char url_digitada[MAX_CARACTER_URL];

		printf("\n-- CADASTRO DE PRODUTO DO USUARIO ---|> %s - %s <|!!! --\n", Usuario[numero_usuario_logado].ID, Usuario[numero_usuario_logado].nome);

		/*------- Area de alocacao do produto novo -------*/
		Usuario[numero_usuario_logado].Quantidade_de_produtos_cadastrados++;
		Usuario[numero_usuario_logado].numero_da_quantidade_de_produtos_publicados++;
		Usuario[numero_usuario_logado].informacoes = Alocar_memoria_produto_novo(Usuario[numero_usuario_logado].informacoes, Usuario[numero_usuario_logado].Quantidade_de_produtos_cadastrados);
		Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].avaliacoes = NULL;
		Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].url = NULL;
		Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].quantidade_de_imagens = 0;
		Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].numero_de_avaliacoes = 0;
		Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].avaliacao_atual = 0;
		/*-------------------------------------------------*/

		bool ID_indisponivel = true;

		/*--------------- Area do ID --------------*/
		do {

			printf("ID do produto....: ");
			fgets(Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].ID, MAX_CARACTER_ID, stdin);
			RemoveQuebraLinha(Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].ID);

			ID_indisponivel = verificacao_disponibilidade_ID_produtos(Usuario, Quantidade_de_cadastros_feitos, Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].ID, numero_usuario_logado);
			if (ID_indisponivel)
			{
				LimparTela();
				printf("\n-- CADASTRO DE PRODUTO DO USUARIO --- %s - %s !!! --\n", Usuario[numero_usuario_logado].ID, Usuario[numero_usuario_logado].nome);
				printf("Id indisponivel !!!\nDigite novamente o ");
			}

		} while (ID_indisponivel);
		/*-----------------------------------------*/

		/*------------- Area da descricao -------------*/
		printf("Descricao........: ");
		fgets(Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].Descricao, MAX_CARACTER_DESCRICAO, stdin);
		RemoveQuebraLinha(Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].Descricao);
		/*---------------------------------------------*/

		/*------------- Area da quantidade -------------*/
		printf("Quantidade.......: ");
		(void)scanf("%d", &Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].Quantidade);
		/*----------------------------------------------*/

		/*------------- Area da preco -------------*/
		printf("Preco............: ");
		(void)scanf("%f%*c", &Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].preco);
		/*----------------------------------------------*/

		/*---------------- Area da URL ----------------*/
		for(int i = 0 ; ; i ++){

			printf("URL imagem [ %d ]....[ ENTER PARA PARAR ]: ", i + 1);
			fgets(url_digitada, MAX_CARACTER_URL, stdin);
			RemoveQuebraLinha(url_digitada);

			if(strcmp(url_digitada, "\0") == 0){

				printf("\n%d Imagens adicionadas !!!\n\n", i);
				break;
			}else{
			
			Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].quantidade_de_imagens++;
			int quantidade_de_imagens = Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].quantidade_de_imagens;

			/* ---------------------- area de alocacao da imagem nova ---------------------- */
			//realloca a quantidade de imagens desse produto 
			Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].url = (char **)realloc(Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].url, quantidade_de_imagens * sizeof(char*));
			// realloca para essa nova imagem , uma quantidade de caracter para a url
			Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].url[quantidade_de_imagens - 1] = malloc(MAX_CARACTER_URL * sizeof(char));
			/* ----------------------------------------------------------------------------- */

			strcpy(Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].url[i], url_digitada);
			}
		}
		/*---------------------------------------------*/

		Usuario[numero_usuario_logado].informacoes[Usuario[numero_usuario_logado].Produto_atual_para_cadastro].produto_publicado = true;
		Usuario[numero_usuario_logado].Produto_atual_para_cadastro++;
		Usuario[numero_usuario_logado].Produto_atual_para_cadastro++;
		Usuario[numero_usuario_logado].Produto_atual_para_cadastro++;

		LimparTela();
		printf("PRODUTO CADASTRADO COM SUCESSO !!!\n\n");

}
// Menu principal do sistema
void menu () {

	Perfil* Usuario = NULL;
	Perfil * usuario_cpy = NULL;
	int Quantidade_de_cadastros_feitos = 0;
	int Usuario_atual_de_cadastro = 0;
	int numero_do_usuario_logado = -1;
	bool produto_cadastrado_no_sistema = false;
	FILE* Dados_arquivo;

	/*-------- carregar dados --------*/
	Dados_arquivo = fopen("FULL_DADOS.txt", "r");
	if (Dados_arquivo == NULL) {
		printf("Erro ao abrir o arquivo para carregamento de dados !!!\n\n");

	}else{
		Usuario = carregar_dados(Usuario, &Quantidade_de_cadastros_feitos, &Usuario_atual_de_cadastro, &produto_cadastrado_no_sistema, Dados_arquivo, &numero_do_usuario_logado);
		fclose(Dados_arquivo);
	}
	/*--------------------------------*/

	bool continuar_opcao_menu = true;
	bool continuar_opcao_cadastro = true;
	bool continuar_opcao_usuario = true;
	bool continuar_opcao_avaliacao = true;
	bool continuar_opcao_favorito = true;

	int opcao_menu;
	int opcao_usuario;

	do {

		selecionar_opcao(Usuario, Quantidade_de_cadastros_feitos, &opcao_menu, numero_do_usuario_logado);

		switch (opcao_menu) {

		case 1: // OPCOES DE USUARIO

			LimparTela();
			do {

				printf("|>------ OPCOES DE USUARIO ------<|\n");
				if(numero_do_usuario_logado == -1)
				printf("  1) Crie a sua conta	               \n");//
				if(numero_do_usuario_logado == -1)
				printf("  2) Fazer login 				   \n");//
				else
				printf("   Usuario conectado: %s\n|>-------------------------------<|\n", Usuario[numero_do_usuario_logado].nome);
				printf("  3) Listar Usuarios               \n");//
				printf("  4) Buscar usuario				   \n");//
				printf("  5) Visitar Usuario               \n");//
				if(numero_do_usuario_logado != -1)
				printf("  6) Produtos favoritados          \n");//
				if(numero_do_usuario_logado != -1)
				printf("  7) Produtos comprados			   \n");//
				if(numero_do_usuario_logado != -1)
				printf("  8) Deslogar do sistema		   \n");//
				printf("  0) Voltar                        \n");//
				printf("|>-------------------------------<|\n");
				printf("Opcao: ");
				recebe_numero_valido(&opcao_usuario);

				switch (opcao_usuario)
				{

				case 1: // CADASTRO DE UM USUARIO NOVO

					/* NAO POSSUI USUARIO LOGADO */if(numero_do_usuario_logado == -1){
						
						Quantidade_de_cadastros_feitos++;
						Usuario = Alocar_memoria_usuario_novo(Usuario, Quantidade_de_cadastros_feitos);
						cadastrar_usuario_novo(&Usuario[Usuario_atual_de_cadastro], Usuario, Quantidade_de_cadastros_feitos, Usuario_atual_de_cadastro);
						Usuario_atual_de_cadastro++;
						break;
					}
					/*   POSSUI USUARIO LOGADO   */else{

						LimparTela();
						printf("DESLOGUE DO USUARIO ATUAL PARA INICIAR UM NOVO CADASTRO !!!\n\n\n");

					}
					break;

				case 2: // FAZER LOGIN EM USUARIO ESPECIFICO 

					/* NAO POSSUI USUARIO LOGADO */if(numero_do_usuario_logado == -1){

						if (Quantidade_de_cadastros_feitos == 0) {

							LimparTela();
							printf("Nenhum cadastro foi feito !!!\n\n\n");

						}
						else {
						
						LimparTela();
						opcao_login_usuario(Usuario, Quantidade_de_cadastros_feitos, &numero_do_usuario_logado);

					}				
					}
					/*   POSSUI USUARIO LOGADO   */else{

						LimparTela();
						printf("JA EXISTE UM USUARIO LOGADO NESSE SISTEMA !!!\n\n");

					}
					break;

				case 3: // LISTA OS USUARIOS PELA ESCOLHA DE ID OU EMAIL OU NOME

					usuario_cpy = Alocar_memoria_usuario_novo(usuario_cpy, Quantidade_de_cadastros_feitos);

					for(int i = 0 ; i < Quantidade_de_cadastros_feitos ; i ++){
						usuario_cpy[i] = Usuario[i];
					}
					
					if (Quantidade_de_cadastros_feitos == 0){

						LimparTela();

						printf("Nenhum cadastro foi feito !!!\n\n\n");
					}
					else{
						Opcao_listar_ou_busca_usuarios_cadastrados(usuario_cpy, Quantidade_de_cadastros_feitos, "Listar", true, false);
					}
					
					free(usuario_cpy);
					usuario_cpy = NULL;
					break;

				case 4: // BUSCA OS USUARIOS PELA ESCOLHA DE ID OU EMAIL OU NOME, POR SUAS PARTES 
						
					usuario_cpy = Alocar_memoria_usuario_novo(usuario_cpy, Quantidade_de_cadastros_feitos);
					for(int i = 0 ; i < Quantidade_de_cadastros_feitos ; i ++){
						usuario_cpy[i] = Usuario[i];
					}
					
					if (Quantidade_de_cadastros_feitos == 0)
					{

						LimparTela();

						printf("Nenhum cadastro foi feito !!!\n\n\n");
					}
					else
					{
						Opcao_listar_ou_busca_usuarios_cadastrados(Usuario, Quantidade_de_cadastros_feitos, "Buscar", false, true);
					}
					
					free(usuario_cpy);
					usuario_cpy = NULL;
					break;
				
				case 5: // VISITA UM USUARIO ESPECIFICO

					if (Quantidade_de_cadastros_feitos == 0)
					{

						LimparTela();

						printf("Nenhum cadastro foi feito !!!\n\n\n");
					}
					else
					{
						visitar_usuario(Usuario, Quantidade_de_cadastros_feitos, numero_do_usuario_logado);
					}
					break;
				
				case 6: // LISTAR OS PRODUTOS FAVORITADOS DE UM USUARIO

					/*   POSSUI USUARIO LOGADO   */if(numero_do_usuario_logado == -1){

						LimparTela();
						printf("É NECESSARIO FAZER LOGIN PARA ISSO !!!\n\n");
	
					}
					/* NAO POSSUI USUARIO LOGADO */else{

						LimparTela();
						listar_produtos_favoritados_de_um_usuario(Usuario, Quantidade_de_cadastros_feitos, numero_do_usuario_logado);
					}
					break;

				case 7: // LISTA OS PRODUTOS COMPRADOS DE UM USUARIO

					/*   POSSUI USUARIO LOGADO   */if(numero_do_usuario_logado == -1){

						LimparTela();
						printf("É NECESSARIO FAZER LOGIN PARA ISSO !!!\n\n");
	
					}
					/* NAO POSSUI USUARIO LOGADO */else{

						LimparTela();
						listar_produtos_comprados_de_um_usuario(Usuario, Quantidade_de_cadastros_feitos, numero_do_usuario_logado);
					}
					break;
				
				case 8: // DESLOGAR

					/* NAO POSSUI USUARIO LOGADO */if(numero_do_usuario_logado == -1){

						LimparTela();
						printf("NENHUM USUARIO ESTA LOGADO !!!\n\n");

					}
					/*   POSSUI USUARIO LOGADO   */else{

						LimparTela();
						Usuario[numero_do_usuario_logado].logado = false;
						numero_do_usuario_logado = -1;
						printf("USUARIO DESLOGADO COM SUCESSO !!!\n\n");

					}
					break;

				case 0: // VOLTA PARA O MENU PRINCIPAL

					LimparTela();
					printf("O USUARIO VOLTOU !!!\n\n");
					continuar_opcao_cadastro = false;
					break;

				default:
					LimparTela();
					printf("Opcao invalida !!!\n\n");
					break;
				}

			} while (continuar_opcao_cadastro);
			continuar_opcao_cadastro = true;
			break;

		case 2: // OPCOES DE PRODUTO

			LimparTela();
			do {

				printf("|>------- OPCOES DE PRODUTO -------<|\n");
				if(numero_do_usuario_logado != -1)
				printf("  1) Publicar		  	   		     \n");//
				if(numero_do_usuario_logado != -1)
				printf("  2) Apagar publicacao		  	     \n");//
				if(numero_do_usuario_logado != -1)
				printf("  3) Editar publicacao		  	   	 \n");//
				printf("  4) Listar produtos		         \n");//
				if(numero_do_usuario_logado != -1)
				printf("  5) Alterar estoque		         \n");//
				printf("  0) Voltar                          \n");//
				printf("|>---------------------------------<|\n");
				printf("Opcao: ");
				recebe_numero_valido(&opcao_usuario);

				switch (opcao_usuario)
				{

				case 1: // CADASTRA UM PRODUTO NOVO

					/* NAO POSSUI USUARIO LOGADO */if(numero_do_usuario_logado == -1){
						
						LimparTela();
						printf("É NECESSARIO LOGIN PARA CADASTRAR UM NOVO PRODUTO !!!\n\n\n");
					}
					/*   POSSUI USUARIO LOGADO   */else{

						LimparTela();
						cadastrar_produto_novo(Usuario, Quantidade_de_cadastros_feitos, numero_do_usuario_logado);
						produto_cadastrado_no_sistema = true;

					}
					break;

				case 2: // APAGA UM PRODUTO CADASTRADO NO SISTEMA

					/* NAO POSSUI USUARIO LOGADO */if(numero_do_usuario_logado == -1){
						
						LimparTela();
						printf("É NECESSARIO LOGIN PARA CADASTRAR UM NOVO PRODUTO !!!\n\n\n");
					}
					/*   POSSUI USUARIO LOGADO   */else{

						LimparTela();
						apaga_produto_publicado(Usuario, Quantidade_de_cadastros_feitos, numero_do_usuario_logado);
					}
					break;

				case 3: // EDITA UM PRODUTO CADASTRADO

					/* NAO POSSUI USUARIO LOGADO */if(numero_do_usuario_logado == -1){
						
						LimparTela();
						printf("É NECESSARIO LOGIN PARA CADASTRAR UM NOVO PRODUTO !!!\n\n\n");
					}
					/*   POSSUI USUARIO LOGADO   */else{

						LimparTela();
						editar_produto(Usuario, Quantidade_de_cadastros_feitos, numero_do_usuario_logado);
						produto_cadastrado_no_sistema = true;

					}
					break;

				case 4: // LISTA TODOS OS PRODUTOS CADASTRADOS NO SISTEMA

					if (Quantidade_de_cadastros_feitos == 0)
					{
						LimparTela();
						printf("Nenhum cadastro foi feito !!!\n\n\n");

					}else if(produto_cadastrado_no_sistema){

						Listar_produtos_cadastrados(Usuario, Quantidade_de_cadastros_feitos, true, numero_do_usuario_logado);
					}
					else
					{
						LimparTela();
						printf("Nenhum produto cadastrado no sistema !!!\n\n\n");
					}
					break;

				case 5:
					
					/* NAO POSSUI USUARIO LOGADO */if(numero_do_usuario_logado == -1){
						
						LimparTela();
						printf("É NECESSARIO LOGIN PARA ALTERAR O ESTOQUE DE UM PRODUTO !!!\n\n\n");
					}
					/*   POSSUI USUARIO LOGADO   */else{

						LimparTela();
						alterar_estoque(Usuario, Quantidade_de_cadastros_feitos, numero_do_usuario_logado);
					}
					break;

				case 0: // VOLTA AO MENU PRINCIPAL
					LimparTela();
					printf("O USUARIO VOLTOU !!!\n\n");
					continuar_opcao_usuario = false;
					break;

				default:
					LimparTela();
					printf("Opcao invalida !!!\n\n");
					break;
				}

			} while (continuar_opcao_usuario);
			continuar_opcao_usuario = true;
			break;

		case 3: // OPCOES DE AVALIACAO

			LimparTela();
			do {

				printf("|>---------- OPCOES DE AVALIACAO ----------<|\n");
				printf("  1) Listar avaliacoes de um produto	     \n");//
				printf("  0) Voltar                              	 \n");//
				printf("|>-----------------------------------------<|\n");
				printf("Opcao: ");
				recebe_numero_valido(&opcao_usuario);

				switch (opcao_usuario)
				{

				case 1: // LISTA TODAS AS AVALIACOES DE UM PRODUTO ESPECIFICO

					if (Quantidade_de_cadastros_feitos == 0)
					{
						LimparTela();
						printf("Nenhum cadastro foi feito !!!\n\n\n");

					}else if(produto_cadastrado_no_sistema){

						Listar_avaliacoes_de_um_produto(Usuario, Quantidade_de_cadastros_feitos);

					}else
					{
						LimparTela();
						printf("Nenhum produto cadastrado no sistema !!!\n\n\n");
					}
					break;
					
				case 0: // VOLTA AO MENU PRINCIPAL
					LimparTela();
					printf("O USUARIO VOLTOU !!!\n\n");
					continuar_opcao_avaliacao = false;
					break;

				default:
					LimparTela();
					printf("Opcao invalida !!!\n\n");
					break;
				}

			} while (continuar_opcao_avaliacao);
			continuar_opcao_avaliacao = true;
			break;

		case 4: // OPCOES DE FAVORITOS

			/* NAO POSSUI USUARIO LOGADO */if(numero_do_usuario_logado == -1){
				LimparTela();
				printf("NENHUM USUARIO ESTA LOGADO NO SISTEMA !!!\n\n");

			}
			/*   POSSUI USUARIO LOGADO   */else{

				LimparTela();
				do {

					printf("|>---------- OPCOES DE FAVORITAR ----------<|\n");
					printf("  1) Desfavoritar um produto			     \n");//
					printf("  0) Voltar                                  \n");//
					printf("|>-----------------------------------------<|\n");
					printf("Opcao: ");
					recebe_numero_valido(&opcao_usuario);

					switch (opcao_usuario)
					{				

					case 1: // DESFAVORITA UM PRODUTO ESPECIFICO DE UM USUARIO

						/* NAO POSSUI USUARIO LOGADO */if(numero_do_usuario_logado == -1){
							
							LimparTela();
							printf("É NECESSARIO LOGIN PARA DESFAVORITAR UM PRODUTO!!!\n\n\n");
						}
						/*   POSSUI USUARIO LOGADO   */else{

							if(Usuario[numero_do_usuario_logado].numero_da_quantidade_de_favoritos_de_um_usuario != 0){
								LimparTela();
								desfavoritar_um_produto(Usuario, Quantidade_de_cadastros_feitos, numero_do_usuario_logado);
							}
							else
							{
								LimparTela();
								printf("ESSE USUARIO NAO POSSUI NENHUM PRODUTO FAVORITADO !!!\n\n");
							}	
						}
						break;

					case 0: // VOLTA AO MENU PRINCIPAL
						LimparTela();
						printf("O USUARIO VOLTOU !!!\n\n");
						continuar_opcao_favorito = false;
						break;

					default:
						LimparTela();
						printf("Opcao invalida !!!\n\n");
						break;
					}

				} while (continuar_opcao_favorito);
				continuar_opcao_favorito = true;
			}
			break;

		case 0: // SAIR DO PROGRAMA

			LimparTela();
			continuar_opcao_menu = false;
			break;

		default:

			LimparTela();
			printf("Opcao invalida !!!\n\n\n");
			break;
		}

	} while (continuar_opcao_menu);

	/*-------- salvar dados --------*/
	Dados_arquivo = fopen("FULL_DADOS.txt", "w");
	if (Dados_arquivo == NULL) {
		printf("Erro ao abrir o arquivo para salvamento !!!");
		return;
	}
	salvar_dados(Usuario, Quantidade_de_cadastros_feitos, Usuario_atual_de_cadastro, produto_cadastrado_no_sistema, Dados_arquivo);
	fclose(Dados_arquivo);
	/*------------------------------*/

	/*-------- Libera memoria --------*/
	/*     AVALIACOES     */ for (int i = 0; i < Quantidade_de_cadastros_feitos; i++) {
		for (int j = 0; j < Usuario[i].Quantidade_de_produtos_cadastrados; j++) {
			free(Usuario[i].informacoes[j].avaliacoes);
		}
	}
	/*       IMAGENS      */ for(int i = 0 ; i < Quantidade_de_cadastros_feitos ; i++){
		for(int j = 0 ; j < Usuario[i].Quantidade_de_produtos_cadastrados; j++){
			for(int t = 0 ; t < Usuario[i].informacoes[j].quantidade_de_imagens; t++){
				free(Usuario[i].informacoes[j].url[t]);
			}
			free(Usuario[i].informacoes[j].url);
		}
	}
	/*      PRODUTOS      */ for (int i = 0; i < Quantidade_de_cadastros_feitos; i++) {
		free(Usuario[i].informacoes);
	}
	/*      FAVORITOS     */ for (int i = 0; i < Quantidade_de_cadastros_feitos; i++) {
		free(Usuario[i].favoritos);
	}
	/* PRODUTOS COMPRADOS */ for (int i = 0; i < Quantidade_de_cadastros_feitos; i++) {
		free(Usuario[i].produtos_comprados);
	}
	/*      USUARIOS      */ free(Usuario);
	/*--------------------------------*/

	LimparTela();
	printf("Saindo ...\n");
	printf("Volte sempre !!\n\n");
}
/* ------------------------------------------------------------------------------------------------------------------------- */


int main(int argc, char** argv) {

	/* ----------------------------
	* Grupo: Lucas Codama, Sofia Gabriele, Pedro Toledo
	* Turma: 104
	/*----------------------------*/

	LimparTela();
	menu();
	return JOIA;
}