//Autor: Leonardo Coelho
//Disciplina: AOC-2

#include <stdio.h>
#include <math.h>
#include "tm.h"

uint32_t tempo_medio(int niveis_hierarquia, struct nivel * niveis, struct nivel * tlb){
	if(niveis == NULL) return 0;  // Se o vetor de niveis da cache estiver sem nada
	if(tlb != NULL && tlb->tempo_acesso >= niveis[niveis_hierarquia-1].tempo_acesso) return 0; // Se o tempo de acesso a TLB for maior que o da memoria

	int i;
	float valor=1.0, tlbM=0.0, teste;
	uint32_t val;

	valor = niveis[niveis_hierarquia-1].tempo_acesso;  // valor = memoria principal

	for(i=niveis_hierarquia-2; i>=0; i--){ // Cache de menor nivel >> cache de maior nivel
		if(niveis[i].tempo_acesso == 0 ) return 0;  // Se qualquer tempo de acesso for 0
		if(niveis[i].tempo_acesso > niveis[i+1].tempo_acesso && i!=1)return 0; // Se qualquer nivel tiver tempo de acesso menor que seu anterior

		valor = niveis[i].tempo_acesso + (niveis[i].taxa_falta/1000000.0) * valor; // Miss * milhoes de acessos
	}

	if(tlb != NULL){ // Se tiver TLB
		if(tlb->taxa_falta == 0) // Se TLB nao tiver miss
			tlbM = tlb->tempo_acesso;
		else{ //Calculo normal (mem. principal*2, por conta do acesso ao banco de paginas)
				tlbM = tlb->tempo_acesso + ((tlb->taxa_falta/1000000.0) * niveis[niveis_hierarquia-1].tempo_acesso) * 2;
		}

		valor = valor + tlbM; // Valor da media + TLB
	}
 

// Arredendamento dos valores
	val = valor; // int = float
	teste = valor - val;

	if(teste > 0) return valor+1; // Se a comparação entre eles der um numero com sinal, arredonda para cima

	return valor;
}