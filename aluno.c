//Autor: Leonardo Coelho
//Disciplina: AOC-2

#include <stdio.h>
#include "simplegrade.h"
#include "tm.h"

void teste(){
	uint32_t n;
	struct nivel tlb;

// Testes de operações erradas
	printf("Teste 1.1: Memoria estiver NULL\n");
		n = tempo_medio(1, NULL, NULL);

	if (n == 0)
		printf("PASSOU!\n");
	else
		printf("ERRADO! *nivel == NULL\n");

	printf("Teste 1.2: Cache com tempo de acesso igual a 0\n");
	struct nivel teste0[3];
	teste0[0].tempo_acesso = 1;
	teste0[0].taxa_falta = 50000;
	teste0[1].tempo_acesso = 0;
	teste0[1].taxa_falta = 30000;
	teste0[2].tempo_acesso = 100;
	teste0[2].taxa_falta = 0;
	n= tempo_medio(3, teste0, NULL);

	if (n == 0)
		printf("PASSOU!\n");
	else
		printf("ERRADO! *nivel == NULL\n");
	
	// Caso 1.1: sem tlb | 1 + (0.05 * (10 + (0.03 * (100))))
  	printf("Teste 2.1: Cache L2 e sem TLB\n");
	struct nivel teste[3];
	teste[0].tempo_acesso = 1;
	teste[0].taxa_falta = 50000;
	teste[1].tempo_acesso = 10;
	teste[1].taxa_falta = 30000;
	teste[2].tempo_acesso = 100;
	teste[2].taxa_falta = 0;
	n= tempo_medio(3, teste, NULL);

	if (n == 2)
		printf("PASSOU!\n");
	else
		printf("ERRADO! %d != 2.\n", n);

	// Caso 1.2: com tlb | 1 + (0.05 * (10 + (0.03 * (100)))) + tlb
  	printf("Teste 2.2: Cache L2 e com TLB\n");
	struct nivel teste1[3];
	teste1[0].tempo_acesso = 1;
	teste1[0].taxa_falta = 50000;
	teste1[1].tempo_acesso = 10;
	teste1[1].taxa_falta = 30000;
	teste1[2].tempo_acesso = 100;
	teste1[2].taxa_falta = 0;
	tlb.tempo_acesso = 1;
	tlb.taxa_falta = 50000;
	n= tempo_medio(3, teste1, &tlb);

	if (n == 13)
		printf("PASSOU!\n");
	else
		printf("ERRADO! %d != 13.\n", n);

	// Caso 2.1: sem tlb | 1 + (0.05 * (10 + (0.03 * (100))))
  	printf("Teste 3.1: Cache L1 e sem TLB\n");
	struct nivel teste2[2];
	teste2[0].tempo_acesso = 1;
	teste2[0].taxa_falta = 30000;
	teste2[1].tempo_acesso = 100;
	teste2[1].taxa_falta = 0;
	n= tempo_medio(2, teste2, NULL);
	
	if (n == 4)
		printf("PASSOU!\n");
	else
		printf("ERRADO! %d != 4.\n", n);

	// Caso 2.2: com tlb | 1 + (0.05 * (10 + (0.03 * (100)))) + tlb
  	printf("Teste 3.2: Cache L1 e com TLB\n");
	struct nivel teste3[2];
	teste3[0].tempo_acesso = 1;
	teste3[0].taxa_falta = 30000;
	teste3[1].tempo_acesso = 100;
	teste3[1].taxa_falta = 0;
	tlb.tempo_acesso = 1;
	tlb.taxa_falta = 50000;
	n= tempo_medio(2, teste3, &tlb);

	if (n == 15)
		printf("PASSOU!\n");
	else
		printf("ERRADO! %d != 15.\n", n);

	// Caso 3.1: sem tlb | 1 + (0.05 * (10 + (0.01 * (100 + (0.3 (200))))))
  	printf("Teste 3.2: Cache L3 e com TLB\n");
	struct nivel teste4[4];
	teste4[0].tempo_acesso = 1;
	teste4[0].taxa_falta = 50000;
	teste4[1].tempo_acesso = 10;
	teste4[1].taxa_falta = 10000;
	teste4[2].tempo_acesso = 100;
	teste4[2].taxa_falta = 300000;
	teste4[3].tempo_acesso = 200;
	teste4[3].taxa_falta = 0;
	n= tempo_medio(2, teste4, NULL);

	if (n == 2)
		printf("PASSOU!\n");
	else
		printf("ERRADO! %d != 2.\n", n);

	// Caso 3.2: com tlb | 1 + (0.05 * (10 + (0.01 * (100 + (0.3 (200)))))) + tlb
  	printf("Teste 3.2: Cache L3 e com TLB\n");
	struct nivel teste5[4];
	teste5[0].tempo_acesso = 1;
	teste5[0].taxa_falta = 50000;
	teste5[1].tempo_acesso = 10;
	teste5[1].taxa_falta = 10000;
	teste5[2].tempo_acesso = 100;
	teste5[2].taxa_falta = 300000;
	teste5[3].tempo_acesso = 200;
	teste5[3].taxa_falta = 0;
	tlb.tempo_acesso = 1;
	tlb.taxa_falta = 50000;
	n= tempo_medio(2, teste5, &tlb);

	if (n == 4)
		printf("PASSOU!\n");
	else
		printf("ERRADO! %d != 4.\n", n);

}

int main(){

	teste();

	return 0;
}
