#pragma once
#ifndef __PERFIL_h__
#define __PERFIL_h__

#include "estruturas.h"
#include <stdbool.h>

void listar_IDS (Perfil* Usuario, int Quantidade_de_cadastros_feitos, int mostrar_produtos, int mostrar_usuario, int mostrar_qt_produtos, int mostrar_qt_favoritados);
void Opcao_listar_ou_busca_usuarios_cadastrados (Perfil* Usuario, int Quantidade_de_cadastros_feitos, char titulo[], bool listar, bool buscar);
void visitar_usuario (Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_do_usuario_logado); 

#endif