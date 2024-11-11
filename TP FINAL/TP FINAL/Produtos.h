#pragma once
#ifndef __PRODUTOS_h__
#define __PRODUTOS_h__

#include <stdbool.h>
#include "estruturas.h"

Dados_avaliacao* Alocar_memoria_avaliacao_novo 				 (Perfil* Usuario, int numero_do_usuario_dono, int numero_do_produto);
// Aloca a memoria do novo produto comprado de um usuario
Dados_produto_comprado* Alocar_memoria_novo_produto_comprado (Dados_produto_comprado * Produtos_comprados, int Quantidade_de_produtos_comprados);
// Aloca a memoria de um novo favorito do usuario
Dados_favoritado* Alocar_memoria_favorito_novo 				 (Dados_favoritado* favorito, int Quantidade_de_produtos_favoritados);

// lista os produtos do sistema
void listar_produtos                            (int TAMANHO_IMAGEM, Perfil * Usuario, int Quantidade_de_cadastros_feitos, bool mostrar_id, bool mostrar_preco, bool mostrar_imagem, bool mostrar_descricao, bool mostrar_quantidade, bool mostrar_comentarios, int todos_usuarios, int usuario_unico, int produto_unico, int numero_do_usuario, int numero_do_produto);
// Detalha um produto especifico
void detalhar_um_produto						(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_usuario_logado);
// Lista todos os produtos cadastrados no sistema
void Listar_produtos_cadastrados 				(Perfil* Usuario, int Quantidade_de_cadastros_feitos, bool opcoes_de_produto, int numero_usuario_logado);
// Altera a quantidade de produtos disponiveis de um usuario especifico
void alterar_estoque							(Perfil* Usuario, int Quantidade_de_cadastros_feitos, int numero_do_usuario_logado);

#endif