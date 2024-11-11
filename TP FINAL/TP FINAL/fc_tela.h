#pragma once
#ifndef __FC_TELA_h__
#define __FC_TELA_h__

#include <stdbool.h>

// Remove a quebra de linha de uma string
void RemoveQuebraLinha	(char dado[]);
// limpa a tela do sistema inteiro
void LimparTela			();
// limpa a tela e c'	oloca o titulo
void LimpaTelaTitulo	(char titulo[], char subtitulo[], bool limpatela);

#endif