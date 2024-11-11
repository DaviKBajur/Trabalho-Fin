#include <stdio.h>
#include <stdbool.h>
#include "estruturas.h"
#include "fc_tela.h"
#include "gera_imagem.h"
#include "fc_verificacao.h"

// Aloca a memoria da avaliacao nova de um produto
Dados_avaliacao* Alocar_memoria_avaliacao_novo 				 (Perfil* Usuario, int numero_do_usuario_dono, int numero_do_produto) {
	return realloc(Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].avaliacoes, Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].numero_de_avaliacoes * sizeof(Dados_avaliacao));
}
// Aloca a memoria do novo produto comprado de um usuario
Dados_produto_comprado* Alocar_memoria_novo_produto_comprado (Dados_produto_comprado * Produtos_comprados, int Quantidade_de_produtos_comprados) {
	return realloc(Produtos_comprados, Quantidade_de_produtos_comprados * sizeof(Dados_produto_comprado));
}
// Aloca a memoria de um novo favorito do usuario
Dados_favoritado* Alocar_memoria_favorito_novo 				 (Dados_favoritado* favorito, int Quantidade_de_produtos_favoritados) {
	return realloc(favorito, Quantidade_de_produtos_favoritados * sizeof(Dados_favoritado));
}


// lista os produtos
void listar_produtos 							(int TAMANHO_IMAGEM, Perfil * Usuario, int Quantidade_de_cadastros_feitos, bool mostrar_id, bool mostrar_preco, bool mostrar_imagem, bool mostrar_descricao, bool mostrar_quantidade, bool mostrar_comentarios, int todos_usuarios, int usuario_unico, int produto_unico, int numero_do_usuario, int numero_do_produto){

	asciiImg_t* img;
	// lista todos os produtos //
	if(todos_usuarios == 1 && usuario_unico == 0 && produto_unico == 0){
		for (int i = 0; i < Quantidade_de_cadastros_feitos; i++)
		{
			if (Usuario[i].numero_da_quantidade_de_produtos_publicados != 0) {

				printf("-------- Usuario [ %s - %s ]\n\n", Usuario[i].ID, Usuario[i].nome);
				for (int j = 0; j < Usuario[i].Quantidade_de_produtos_cadastrados; j++)
				{
					if(Usuario[i].informacoes[j].produto_publicado){
						printf("__ Produto [%d] __\n", j + 1);
						if(mostrar_imagem){
							/*---------------------------- AREA PARA GERAR A IMAGEM ----------------------------*/
							for(int t = 0 ; t < Usuario[i].informacoes[j].quantidade_de_imagens ; t++){
								img = insta_carregaImagem(Usuario[i].informacoes[j].url[t], MODO_IMAGEM, TAMANHO_IMAGEM);
								if (img == NULL)
								{
									// Falha ao carregar a imagem
									fprintf(stderr, "Falha ao carregar a imagem da URL %s\n", Usuario[i].informacoes[j].url[t]);
								}
								insta_imprimeImagem(img);
								insta_liberaImagem(img);
								printf("\n");
							}
							/*----------------------------------------------------------------------------------*/
						}
						if(mostrar_id)         printf("ID.........: %s\n", Usuario[i].informacoes[j].ID);
						if(mostrar_preco)      printf("Preco..........: R$ %.2f\n", Usuario[i].informacoes[j].preco);
						if(mostrar_quantidade) printf("Quantidade.: %d\n\n", Usuario[i].informacoes[j].Quantidade);
						if(mostrar_descricao)  printf("Descricao..: %s\n", Usuario[i].informacoes[j].Descricao);
						if (mostrar_comentarios){
							/*------------ AREA PARA MOSTRAR OS COMENTARIOS ------------*/
							if (Usuario[i].informacoes[j].numero_de_avaliacoes != 0) {

								printf("\n------- COMENTARIOS -------\n");
								for (int t = 0; t < Usuario[i].informacoes[j].numero_de_avaliacoes; t++) {

									printf("[ Usuario: %s ]: %s\n", Usuario[i].informacoes[j].avaliacoes[t].ID_do_usuario,
										Usuario[i].informacoes[j].avaliacoes[t].TEXTO);
								}
								printf("---------------------------\n");

							}
							/*----------------------------------------------------------*/
						}
						printf("\n");
					}
				}
			}
		}
	}
	// lista todos os produtos de um usuario especifico
	if(todos_usuarios == 0 && usuario_unico == 1 && produto_unico == 0){
		for(int j = 0 ; j < Usuario[numero_do_usuario].Quantidade_de_produtos_cadastrados && usuario_unico == 1 && produto_unico == 0; j++){		
			if(Usuario[numero_do_usuario].informacoes[j].produto_publicado){
				printf("__ Produto [%d] __\n", j + 1);
				if(mostrar_id) 		   printf("ID.........: %s\n", Usuario[numero_do_usuario].informacoes[j].ID);
				if(mostrar_preco)      printf("Preco..........: R$ %.2f\n", Usuario[numero_do_usuario].informacoes[j].preco);
				if(mostrar_quantidade) printf("Quantidade.: %d\n\n", Usuario[numero_do_usuario].informacoes[j].Quantidade);
				if(mostrar_imagem){
					/*---------------------------- AREA PARA GERAR A IMAGEM ----------------------------*/
					for(int t = 0 ; t < Usuario[numero_do_usuario].informacoes[j].quantidade_de_imagens ; t++){
								img = insta_carregaImagem(Usuario[numero_do_usuario].informacoes[j].url[t], MODO_IMAGEM, IMAGEM_NUMERO_COLUNAS);
								if (img == NULL)
								{
									// Falha ao carregar a imagem
									fprintf(stderr, "Falha ao carregar a imagem da URL %s\n", Usuario[numero_do_usuario].informacoes[j].url[t]);
								}
								insta_imprimeImagem(img);
								insta_liberaImagem(img);
								printf("\n");
							}
					/*----------------------------------------------------------------------------------*/
				}
				if(mostrar_descricao){
					printf("Descricao..: %s\n", Usuario[numero_do_usuario].informacoes[j].Descricao);
				}
				if (mostrar_comentarios){
					/*------------ AREA PARA MOSTRAR OS COMENTARIOS ------------*/
					if (Usuario[numero_do_usuario].informacoes[j].numero_de_avaliacoes != 0) {

						printf("\n------- COMENTARIOS -------\n");
						for (int t = 0; t < Usuario[numero_do_usuario].informacoes[j].numero_de_avaliacoes; t++) {

							printf("[ Usuario: %s ]: %s\n", Usuario[numero_do_usuario].informacoes[j].avaliacoes[t].ID_do_usuario, Usuario[numero_do_usuario].informacoes[j].avaliacoes[t].TEXTO);
						}
						printf("---------------------------\n");
					}
					/*----------------------------------------------------------*/
				}
				printf("\n");
				usuario_unico = (j == (Usuario[numero_do_usuario].Quantidade_de_produtos_cadastrados - 1)? 0 : 1);	
			}		
		}
	}
	// lista um produto especIfico de um usuario especifico
	if(todos_usuarios == 0 && usuario_unico == 1 && produto_unico == 1){

		if(mostrar_imagem){
			/*---------------------------- AREA PARA GERAR A IMAGEM ----------------------------*/
			for(int t = 0 ; t < Usuario[numero_do_usuario].informacoes[numero_do_produto].quantidade_de_imagens ; t++){
						img = insta_carregaImagem(Usuario[numero_do_usuario].informacoes[numero_do_produto].url[t], MODO_IMAGEM, IMAGEM_NUMERO_COLUNAS);
						if (img == NULL)
						{
							fprintf(stderr, "Falha ao carregar a imagem da URL %s\n", Usuario[numero_do_usuario].informacoes[numero_do_produto].url[t]);
						}
						insta_imprimeImagem(img);
						insta_liberaImagem(img);
						printf("\n");
					}
			/*----------------------------------------------------------------------------------*/
		}
		if(mostrar_id){
			printf("ID.........: %s\n", Usuario[numero_do_usuario].informacoes[numero_do_produto].ID);
		}
		if(mostrar_preco){
			printf("Preco..........: R$ %.2f\n", Usuario[numero_do_usuario].informacoes[numero_do_produto].preco);
		}
		if(mostrar_quantidade){
			printf("Quantidade.: %d\n\n", Usuario[numero_do_usuario].informacoes[numero_do_produto].Quantidade);
		}
		if(mostrar_descricao){
			printf("Descricao..: %s\n", Usuario[numero_do_usuario].informacoes[numero_do_produto].Descricao);
		}
		if (mostrar_comentarios){
			/*------------ AREA PARA MOSTRAR OS COMENTARIOS ------------*/
			if (Usuario[numero_do_usuario].informacoes[numero_do_produto].numero_de_avaliacoes != 0) {

						printf("\n------- COMENTARIOS -------\n");
						for (int t = 0; t < Usuario[numero_do_usuario].informacoes[numero_do_produto].numero_de_avaliacoes; t++) {
							printf("[ Usuario: %s ]: %s\n", Usuario[numero_do_usuario].informacoes[numero_do_produto].avaliacoes[t].ID_do_usuario,
								Usuario[numero_do_usuario].informacoes[numero_do_produto].avaliacoes[t].TEXTO);
						}
						printf("---------------------------\n");
					}
			/*----------------------------------------------------------*/
		}
		printf("\n\n");
	}
}
// Favorita um produto especifico para um usuario
void favoritar_um_produto 						(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_usuario_logado, int numero_do_usuario_dono, int numero_do_produto) {
		
	LimparTela();

	/*---------------------------- 	mostrar produto a ser avaliado na tela ----------------------------*/
	printf("__ PRODUTO A SER FAVORITADO !!! __\n");
	listar_produtos(IMAGEM_NUMERO_COLUNAS ,Usuario, Quantidade_de_cadastros_feitos, true, true, true, true, true, false, 0, 1, 1, numero_do_usuario_dono, numero_do_produto);
	/*-------------------------------------------------------------------------------------------------*/

	int numero_do_favorito = Usuario[numero_usuario_logado].numero_atual_favoritamento;
	Usuario[numero_usuario_logado].quantidade_de_produtos_favoritados++;
	Usuario[numero_usuario_logado].numero_da_quantidade_de_favoritos_de_um_usuario++;
	Usuario[numero_usuario_logado].favoritos = Alocar_memoria_favorito_novo(Usuario[numero_usuario_logado].favoritos, Usuario[numero_usuario_logado].quantidade_de_produtos_favoritados);
	Usuario[numero_usuario_logado].favoritos[numero_do_favorito].posicao_do_usuario_dono = numero_do_usuario_dono;
	Usuario[numero_usuario_logado].favoritos[numero_do_favorito].posicao_do_produto = numero_do_produto;
	Usuario[numero_usuario_logado].favoritos[numero_do_favorito].favorito = true;
	Usuario[numero_usuario_logado].numero_atual_favoritamento++;

	printf("[ ENTER PARA CONTINUAR ]: ");
	(void)scanf("%*c");
	LimparTela();
	printf("--- > PRODUTO FAVORITADO COM SUCESSO !!!\n\n");
}
// Compra uma quantidade de produtos de um estoque disponivel
void comprar_produto							(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_usuario_logado, int numero_do_usuario_dono, int numero_do_produto) {

	int quantidade_de_produtos_para_compra;
	bool opcoes_de_compra = true;
 
	/*   PRODUTO POSSUI UM ESTOQUE MAIOR QUE 0   */if(Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].Quantidade > 0) {
		
		do{
			printf("|--> USUARIO %s <--|\n", Usuario[numero_usuario_logado].ID);
			printf("Qual a quantidade que deseja COMPRAR: ");
			recebe_numero_valido(&quantidade_de_produtos_para_compra);

			/* QUANTIDADE INVALIDA */if (quantidade_de_produtos_para_compra > Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].Quantidade ||  quantidade_de_produtos_para_compra < 0 ){

					char opcao;
		
					printf("\n[ ERRO ] !!!\n");
					printf("Quantidade de produtos desejada para compra invalida\n");
					printf("Deseja digitar uma nova quantidade [ s / n ]: ");
					(void)scanf("%c%*c", &opcao);

					if(opcao == 'n' || opcao == 'N'){
					
						LimparTela();
						opcoes_de_compra = false;
						printf("O USUARIO VOLTOU !!!\n");
						printf("Motivo: Quantidade para compra invalida\n\n");

					}

			/*  QUANTIDADE VALIDA  */}else{ 
					
					Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].Quantidade -= quantidade_de_produtos_para_compra;
					opcoes_de_compra = false;

					/*-- ADICIONANDO O PRODUTO NA LISTA DE COMPRAS DESSE USUARIO --*/
					Usuario[numero_usuario_logado].quantidade_de_produtos_comprados++;
					Usuario[numero_usuario_logado].produtos_comprados = Alocar_memoria_novo_produto_comprado(Usuario[numero_usuario_logado].produtos_comprados, Usuario[numero_usuario_logado].quantidade_de_produtos_comprados);
					Usuario[numero_usuario_logado].produtos_comprados[Usuario[numero_usuario_logado].numero_atual_de_compra].posicao_do_usuario_dono = numero_do_usuario_dono;
					Usuario[numero_usuario_logado].produtos_comprados[Usuario[numero_usuario_logado].numero_atual_de_compra].posicao_do_produto = numero_do_produto;
					Usuario[numero_usuario_logado].numero_atual_de_compra++;
					/*-------------------------------------------------------------*/

					LimparTela();
					printf("PRODUTO COMPRADO COM SUCESSO !!!\n\n");

			}

		}while(opcoes_de_compra);

	/* PRODUTO NAO POSSUI UM ESTOQUE MAIOR QUE 0 */} else {
		printf("O ESTOQUE DESSE PRODUTO ESTA ESGOTADO\n\n");	
	}
}
// Avalia um produto especifico de um usuario
void avaliar_produto	 						(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_usuario_logado, int numero_do_usuario_dono, int numero_do_produto) {
 
	int numero_da_avaliacao = Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].avaliacao_atual;
	Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].numero_de_avaliacoes++;
	Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].avaliacoes = Alocar_memoria_avaliacao_novo(Usuario, numero_do_usuario_dono, numero_do_produto);
	strcpy(Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].avaliacoes[numero_da_avaliacao].ID_do_usuario, Usuario[numero_usuario_logado].ID);
	Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].avaliacao_atual++;
	printf("|--> USUARIO %s <--|\n", Usuario[numero_usuario_logado].ID);
	printf("Digite seu comentario: ");
	fgets(Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].avaliacoes[numero_da_avaliacao].TEXTO, MAX_CARACTER_AVALIACAO, stdin);
	RemoveQuebraLinha(Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].avaliacoes[numero_da_avaliacao].TEXTO);

	LimparTela();
	printf("AVALIACAO FEITA COM SUCESSO !!!\n\n");
}
// apresenta as opcoes que um usuario pode ter para um produto
void opcoes_com_produto_listado					(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_usuario_logado, int numero_do_usuario_dono, int numero_do_produto){

	int opcao;
	bool continuar_opcao_produtos = true;

	printf("|>--- OPCOES DOS PRODUTOS ---<|\n");
	if(numero_usuario_logado != -1)
	printf("  1) Avaliar				   \n");
	if(numero_usuario_logado != -1)
	printf("  2) Comprar				   \n");
	if(numero_usuario_logado != -1)
	printf("  3) Favoritar				   \n");
	printf("  0) voltar 				   \n");
	printf("|>---------------------------<|\n");

	do{

		printf("Opcao: ");
		recebe_numero_valido(&opcao);

		switch (opcao){

		case 1:

			/* POSSUI USUARIO LOGADO */if(numero_usuario_logado != -1){
				
				continuar_opcao_produtos = false;
				avaliar_produto(Usuario, Quantidade_de_cadastros_feitos, numero_usuario_logado, numero_do_usuario_dono, numero_do_produto);

			}
			/* NAO POSSUI USUARIO LOGADO */else{
				printf("É NECESSARIO LOGIN FAZER LOGIN\n\n");
			}
			break;
		
		case 2:

			/* POSSUI USUARIO LOGADO */if(numero_usuario_logado != -1){
				
				continuar_opcao_produtos = false;
				comprar_produto(Usuario, Quantidade_de_cadastros_feitos, numero_usuario_logado, numero_do_usuario_dono, numero_do_produto);

			}
			/* NAO POSSUI USUARIO LOGADO */else{
				printf("É NECESSARIO LOGIN FAZER LOGIN\n\n");
			}
			break;

		case 3:

			/* POSSUI USUARIO LOGADO */if(numero_usuario_logado != -1){
				
				continuar_opcao_produtos = false;
				favoritar_um_produto(Usuario, Quantidade_de_cadastros_feitos, numero_usuario_logado, numero_do_usuario_dono, numero_do_produto);

			}
			/* NAO POSSUI USUARIO LOGADO */else{
				printf("É NECESSARIO LOGIN FAZER LOGIN\n\n");
			}
			break;
		
		case 0:
			LimparTela();
			printf("O USUARIO VOLTOU !!!\n\n");
			continuar_opcao_produtos = false;
			break;
		
		default:
			printf("OPCAO INVALIDA !!!\n\n");
			break;
		}

	}while(continuar_opcao_produtos);
}
// Detalha um produto especifico
void detalhar_um_produto						(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_usuario_logado){

	int numero_do_usuario_dono = -1;
	int numero_do_produto = -1;
	bool Produto_nao_achado = true;
	char ID_Produto_detalhar[MAX_CARACTER_ID];

	/*--- Area de receber o id do produto para detalhar ---*/
	do {

		printf("ENTRAR EM UM PRODUTO\nDigite o ID do produto [ ENTER PARA VOLTAR ]: ");
		fgets(ID_Produto_detalhar, MAX_CARACTER_ID, stdin);
		RemoveQuebraLinha(ID_Produto_detalhar);
		/* VOLTA DE CASO O USUARIO ENTROU AQUI POR ENGANO */if(strcmp(ID_Produto_detalhar,"\0") == 0){
			LimparTela();
			printf("O USUARIO VOLTOU !!!\n\n");
			return;
		}
		Produto_nao_achado = verifica_existencia_ID(Usuario, Quantidade_de_cadastros_feitos, &numero_do_usuario_dono, &numero_do_produto, ID_Produto_detalhar, 0 , 1);

	} while (Produto_nao_achado);
	printf("\n\n");
	/*-----------------------------------------------------*/

	/*     PRODUTO ENCONTRADO     */if(numero_do_produto != -1){

		LimparTela();
		printf(">--------------------------- DETALHES DO PRODUTO [ %s ] ----<\n", Usuario[numero_do_usuario_dono].informacoes[numero_do_produto].ID);
		listar_produtos(IMAGEM_NUMERO_COLUNAS, Usuario, Quantidade_de_cadastros_feitos, true, true, true, true, true, true, 0 , 1, 1 , numero_do_usuario_dono, numero_do_produto);
		printf(">----------------------------------------------------------------------------------<\n\n\n");

		opcoes_com_produto_listado(Usuario, Quantidade_de_cadastros_feitos, numero_usuario_logado, numero_do_usuario_dono, numero_do_produto);
	}
	/*   PRODUTO NAO ENCONTRADO   */ else{
		LimparTela();
		printf("O USUARIO VOLTOU AS OPCOES DE USUARIO / PRODUTO !!!\n");
		printf("Motivo: Produto nao encontrado\n\n");
	} 
}
// Lista todos os produtos cadastrados no sistema
void Listar_produtos_cadastrados 				(Perfil* Usuario, int Quantidade_de_cadastros_feitos, bool opcoes_de_produto, int numero_usuario_logado) {

	LimparTela();

	printf(">----------------- PRODUTOS DO FREE MARKET -----------------<\n\n");
	listar_produtos((IMAGEM_NUMERO_COLUNAS - 20), Usuario, Quantidade_de_cadastros_feitos,true, true, true, false, false, false, 1, 0, 0, 0, 0);
	printf(">-----------------------------------------------------------<\n\n\n");

	if(opcoes_de_produto){
		detalhar_um_produto(Usuario, Quantidade_de_cadastros_feitos, numero_usuario_logado);
	}
}
// Altera a quantidade de produtos disponiveis de um usuario especifico
void alterar_estoque							(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_do_usuario_logado) {
	
	listar_produtos((IMAGEM_NUMERO_COLUNAS - 30), Usuario, Quantidade_de_cadastros_feitos, true, false, true, false, true, false, 0, 1, 0, numero_do_usuario_logado, 0);
	
	char ID_Produto[MAX_CARACTER_ID];
	int numero_do_usuario_dono = -1;
	int numero_do_produto = -1;
	bool Produto_nao_achado = true;
	bool continuar_nova_quantidade = true;

	/*--- Area de receber o id do produto a ser favoritado ---*/
	do {
		printf("ID do Produto para alteração de estoque\n[ ENTER PARA VOLTAR ]: ");
		fgets(ID_Produto, MAX_CARACTER_ID, stdin);
		RemoveQuebraLinha(ID_Produto);
		/* VOLTA DE CASO O USUARIO ENTROU AQUI POR ENGANO */if(strcmp(ID_Produto,"\0") == 0){
			LimparTela();
			printf("O USUARIO VOLTOU !!!\n\n");
			return;
		}
		Produto_nao_achado = verifica_existencia_ID(Usuario, Quantidade_de_cadastros_feitos, &numero_do_usuario_dono, &numero_do_produto, ID_Produto, 0 , 1);

	} while (Produto_nao_achado);
	printf("\n\n");
	/*-------------------------------------------------------*/

	/* PRODUTO NAO ENCONTRADO */if (numero_do_produto == -1) {
		LimparTela();
		printf("VOLTOU AS OPCOES DE PRODUTO !!!\n");
		printf("Motivo: Produto nao encontrado\n\n");
	}
	/*   PRODUTO ENCONTRADO   */else {

		int nova_quantidade;
		printf("---------- Quantidade atual do produto [ %s ] = %d itens ----------\n", Usuario[numero_do_usuario_logado].informacoes[numero_do_produto].ID ,Usuario[numero_do_usuario_logado].informacoes[numero_do_produto].Quantidade);
		printf("Digite a nova quantidade do produto: ");
		do{
			(void)scanf("%d%*c", &nova_quantidade);

			if(nova_quantidade < 0){
				
				printf("\n[ ERRO ] A nova quantidade deve ser maior ou igual a 0 produtos\nDigite novamente a nova quantidade do produto: ");
				
			}else{
				continuar_nova_quantidade = false;
				Usuario[numero_do_usuario_logado].informacoes[numero_do_produto].Quantidade = nova_quantidade;
			}
		}while(continuar_nova_quantidade);

		LimparTela();
		printf("ESTOQUE ALTERADO COM SUCESSO !!!\n\n");
	}
}
