#pragma once
#ifndef __ESTRUTURAS_h__
#define __ESTRUTURAS_h__

#define MAX_CARACTER_DESCRICAO (400 + 1)
#define MAX_CARACTER_URL 	   (600 + 1)
#define MAX_CARACTER_ID 	   (50 + 1)
#define MAX_CARACTER_NOME  (50 + 1)
#define MAX_CARACTER_EMAIL (65 + 1)
#define MAX_CARACTER_SENHA (50 + 1)
#define MAX_CARACTER_AVALIACAO (400 + 1)

// Estrutura que guarda as informacoes dos produtos comprados
typedef struct Dados_produto_comprado {

	int posicao_do_usuario_dono;
	int posicao_do_produto;
	
}Dados_produto_comprado;
// Estrutura que guarda as informacoes de uma avaliacao de um usuario
typedef struct dados_avaliacao_de_um_usuario {

	char ID_do_usuario[MAX_CARACTER_ID];
	char TEXTO[MAX_CARACTER_AVALIACAO];

}Dados_avaliacao;
// Estrutura que guarda as informacoes de um produto favoritado
typedef struct Dados_Produto_favoritado {

	int posicao_do_usuario_dono;
	int posicao_do_produto;
	bool favorito;

}Dados_favoritado;
// Estrutura que guarda as informacoes de um produto
typedef struct dados_produtos{

	char ID[MAX_CARACTER_ID];
	char Descricao[MAX_CARACTER_DESCRICAO];
	int Quantidade;
	float preco;

	int quantidade_de_imagens;
	char ** url;

	int numero_de_avaliacoes;
	Dados_avaliacao* avaliacoes;
	int avaliacao_atual;

	bool produto_publicado;

}Produtos;
// Estrutura que guarda as informacoes de um usuario
typedef struct dados_usuario {

	char ID[MAX_CARACTER_ID];
	char nome[MAX_CARACTER_NOME];
	char email[MAX_CARACTER_EMAIL];
	char senha[MAX_CARACTER_SENHA];
	bool logado;

	Produtos* informacoes; // Um array de produtos para esse usu�rio
	int numero_da_quantidade_de_produtos_publicados;
	int Quantidade_de_produtos_cadastrados;
	int Produto_atual_para_cadastro;

	Dados_favoritado* favoritos;
	int numero_atual_favoritamento;
	int quantidade_de_produtos_favoritados;
	int numero_da_quantidade_de_favoritos_de_um_usuario;

	Dados_produto_comprado* produtos_comprados;
	int numero_atual_de_compra;
	int quantidade_de_produtos_comprados;

} Perfil;


#endif