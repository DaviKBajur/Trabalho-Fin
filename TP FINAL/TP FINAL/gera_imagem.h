#pragma once
#ifndef __GERA_IMAGEM_h__
#define __GERA_IMAGEM_h__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define ERRO_CARREGAR_IMAGEM 1
#define IMAGEM_NUMERO_COLUNAS 80
#define IMAGEM_COLORIDA true
#define IMAGEM_PRETO_BRANCO false
#define MODO_IMAGEM IMAGEM_COLORIDA

/// Estrutura que representa uma imagem em Ascii
struct asciiImg_s {
	uint8_t* bytes;
	int nBytes;
};
/// Tipo "Imagem ASCII"
typedef struct asciiImg_s asciiImg_t;

/**
 *  \brief Fun��o que carrega uma imagem informada na URL.
 *
 *  \param [in] colorido Define se a imagem ser� colorida.
 *  \param [in] largura Define a largura da imagem gerada.
 *  \return Endere�o da estrutura com a imagem.
 *          Caso a imagem n�o tenha sido carregada corretamente, a fun��o
 *          retornar� NULL.
 */
asciiImg_t* insta_carregaImagem(char url[], bool colorido, int largura);
/**
 *  \brief Fun��o que imprime uma Imagem ASCII.
 *
 *  \param [in] img Endere�o da estrutura com os dados da imagem.
 */
void insta_imprimeImagem(asciiImg_t* img);
/**
 *  \brief Fun��o que libera a mem�ria alocada por uma imagem.
 *
 *  \param [in] img Endere�o da estrutura com os dados da imagem a ser liberada.
 */
void insta_liberaImagem(asciiImg_t* img);

#endif