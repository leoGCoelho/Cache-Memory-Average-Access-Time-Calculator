#ifndef _TM_H_
#define _TM_H_

#include <stdint.h>

struct nivel{
			uint32_t tempo_acesso; // em nanossegundos
			uint32_t taxa_falta; // em faltas por milhão de acessos -- deve ser zero para o último nível (memória)
		};

uint32_t tempo_medio(int niveis_hierarquia, struct nivel * niveis, struct nivel * tlb);

#endif // _TM_H_
