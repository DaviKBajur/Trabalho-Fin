#pragma once
#ifndef __FC_VERIFICACAO_h__
#define __FC_VERIFICACAO_h__

#include <stdio.h>
#include <stdbool.h>
#include "Perfil.h"

// Verifica se o ID do usuario / produto existe
bool verifica_existencia_ID						(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int *Numero_do_usuario, int *Numero_do_produto, char Id_lido[], int verifica_usuario, int veriifica_produto);
// Verifica se a opcao é realmente um numero para nao dar erro de repeticao
void recebe_numero_valido						(int* numero);

#endif