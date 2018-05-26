# Trabalho 1 - Arquitetura e Organização de Computadores II - 2018/1
Prof. Maurício Lima Pilla - http://lups.inf.ufpel.edu.br/~pilla

## Dados do aluno

Declaro que o presente trabalho contém código desenvolvido exclusivamente por mim e que não foi compartilhado de nenhuma forma com terceiros a não ser o professor da disciplina. Compreendo que qualquer violação destes princípios será punida rigorosamente de acordo com o Regimento da UFPEL.

(Preencha com seus dados)

- Nome completo: 
- Username do Bitbucket: 
- Email @inf: 

## Descrição

Neste primeiro trabalho, os alunos deverão implementar uma calculadora de tempo médio de acesso para memória parametrizável.

A assinatura da função a ser implementada é:

		struct nivel{
			uint32_t tempo_acesso; // em nanossegundos
			uint32_t taxa_falta; // em faltas por milhão de acessos -- deve ser zero para o último nível (memória)
		};

		uint32_t tempo_medio(int niveis_hierarquia, struct nivel * niveis, struct nivel * tlb);


Onde:

- _niveis_hierarquia_ diz quantos elementos níveis a hierarquia de memória possui (contando a memória principal);
- _niveis_ aponta para um vetor com as configurações dos níveis de _cache_ e da memória principal, ordenados da _cache_ mais próxima da CPU até a memória principal;
- _tlb_ aponta para a configuração da TLB (mas pode ser NULL se não for usada).

A função deve retornar _zero_ quando:

- Qualquer tempo de acesso for _zero_;
- Um nível de memória possuir tempo de acesso **menor** que o anterior;
- _niveis_ for NULL;
- O tempo de acesso à TLB for maior ou igual ao tempo de acesso à memória.


Nos demais casos, a função deve retornar o tempo médio de acesso calculado em nanossegundos. O valor final deve ser arredondado para cima, caso haja necessidade. 

Caso a TLB seja empregada, uma falta no seu acesso implica em acesso à memória principal para a tabela de páginas de um nível.

Caso a TLB não seja configurada, considere que nãO há tabela de páginas.

O professor providenciará o arquivo de testes próximo do prazo de entrega.

## Produtos

* Implementação (*tm.c*)
* Testes do aluno (*testes.c*)

## Cronograma

* Envio da versão final: _27/04/2018_ 


