#include "tm.h"
#include "simplegrade.h"

//tempo_medio(int niveis_hierarquia, struct nivel * niveis, struct nivel * tlb)


void testes_parametros(){
	DESCRIBE("Testando parâmetros inválidos");

	IF("Não tem nenhum nível");
	THEN("Deve retornar zero");
	isEqualUint32(tempo_medio(0, NULL, NULL),0,1);

	IF("Não tem nenhum nível mas diz que tem");
	THEN("Deve retornar zero");
	isEqualUint32(tempo_medio(1, NULL, NULL),0,1);


	IF("Algum tempo de acesso é zero");
	THEN("Deve retornar zero");
	{
		struct nivel n;
		n.tempo_acesso = 0;
		n.taxa_falta = 0; /* não interessa */
		isEqualUint32(tempo_medio(1, &n, NULL),0,1);
	}

	IF("Algum tempo de acesso é menor que o anterior");
	THEN("Deve retornar zero");
	{
		struct nivel n[2];
		n[0].tempo_acesso = 10;
		n[0].taxa_falta = 0; /* não interessa */
		n[1].tempo_acesso = 1;
		n[1].taxa_falta = 0; /* não interessa */
		isEqualUint32(tempo_medio(2, n, NULL),0,1);
	}

	IF("Tempo de acesso da TLB é maior que memória");
	THEN("Deve retornar zero");
	{
		struct nivel n;
		struct nivel tlb;
		n.tempo_acesso = 10;
		n.taxa_falta = 0; /* não interessa */
		tlb.tempo_acesso = 15;
		tlb.taxa_falta = 1; /* não interessa */
		isEqualUint32(tempo_medio(1, &n, &tlb),0,1);
	}



}


void teste_so_mem(){
	DESCRIBE("Testando só memória principal");

	IF("Somente a memória principal é usada");
	THEN("O tempo médio tem que ser igual ao da memória");

	{
		struct nivel n;
		n.tempo_acesso = 10;
		n.taxa_falta = 0; /* não interessa */
		isEqualUint32(tempo_medio(1, &n, NULL),10,1);
	}

	{
		struct nivel n;
		n.tempo_acesso = 100;
		n.taxa_falta = 0; /* não interessa */
		isEqualUint32(tempo_medio(1, &n, NULL),100,1);
	}
}


void teste_mem_tlb(){
	DESCRIBE("Testando só memória principal e TLB");

	IF("Se a taxa de miss da TLB é zero");
	THEN("O tempo médio tem que ser igual ao da memória mais o tempo da TLB");

	{
		struct nivel n;
		n.tempo_acesso = 10;
		n.taxa_falta = 0; /* não interessa */
		struct nivel tlb;
		tlb.tempo_acesso = 1;
		tlb.taxa_falta = 0;
		isEqualUint32(tempo_medio(1, &n, &tlb),11,1);
	}


	IF("Se a taxa de miss da TLB é zero");
	THEN("O tempo médio tem que ser igual ao da memória mais o tempo da TLB");

	{
		struct nivel n;
		n.tempo_acesso = 10;
		n.taxa_falta = 0; /* não interessa */
		struct nivel tlb;
		tlb.tempo_acesso = 1;
		tlb.taxa_falta = 50000; // 95% de hit
 		// Tm = 1 + 0.05 * 10 * 2 + 10 = 1 + 1 + 10 = 12 ns

		isEqualUint32(tempo_medio(1, &n, &tlb),12,2);
	}

	

}


void teste_l1(){
	DESCRIBE("Testando cache L1");

	IF("Se não tem TLB");
	THEN("Calcular o tempo médio");

	{
		struct nivel n[2];
		n[0].tempo_acesso = 1;
		n[0].taxa_falta = 50000; // 95% hit
		n[1].tempo_acesso = 100;
		n[1].taxa_falta = 0; /* não interessa */
		// Tm = 1 + .05 * 100  = 1 + 5 = 6 ns
		
		isEqualUint32(tempo_medio(2, n, NULL),6,2);
	}


	IF("Se tem TLB");
	THEN("Cuidar o tempo de falta na TLB");

	{
		struct nivel n[2];
		n[0].tempo_acesso = 1;
		n[0].taxa_falta = 50000; // 95% hit
		n[1].tempo_acesso = 100;
		n[1].taxa_falta = 0; /* não interessa */
		struct nivel tlb;
		tlb.tempo_acesso = 1;
		tlb.taxa_falta = 50000; // 95%
		// Tm = 1 + 0.05 * 100 * 2  (page fault) + 1 + 0.05 * 100 (cache miss)
		// Tm = 1 + 10 + 1 + 5 = 17
		isEqualUint32(tempo_medio(2, n, &tlb),17,2);
	}

}


void teste_l2(){
	DESCRIBE("Testando cache L2");

	IF("Se não tem TLB");
	THEN("Calcular o tempo médio");

	{
		struct nivel n[2];
		n[0].tempo_acesso = 1;
		n[0].taxa_falta = 50000; // 95% hit
		n[1].tempo_acesso = 10;
		n[1].taxa_falta = 100000; // 90% hit
		n[2].tempo_acesso = 100;
		n[2].taxa_falta = 0;
		
		
		// Tm = 1 + 0.05 * (10 + 0.1 * 100)
		// Tm = 1 + 0.05 * (10 + 10)
		// Tm = 1 + 1 = 2

		isEqualUint32(tempo_medio(3, n, NULL),2,2);
	}

	IF("Se tem TLB");
	THEN("Cuidar o tempo de falta na TLB");

	{
		struct nivel n[3];
		n[0].tempo_acesso = 1;
		n[0].taxa_falta = 50000; // 95% hit
		n[1].tempo_acesso = 10;
		n[1].taxa_falta = 100000; // 90% hit
		n[2].tempo_acesso = 100;
		n[2].taxa_falta = 0;
		struct nivel tlb;
		tlb.tempo_acesso = 1;
		tlb.taxa_falta = 50000; // 95%
		// Tm = 1 + 0.05 * 100 * 2  (page fault) + 1 + 0.05 * (10 + 0.1 * 100)
		// Tm  = 11 + 2 = 13
		isEqualUint32(tempo_medio(3, n, &tlb),13,2);
	}

}




void teste_l3(){
	DESCRIBE("Testando cache L3");

	IF("Se não tem TLB");
	THEN("Calcular o tempo médio");

	{
		struct nivel n[4];
		n[0].tempo_acesso = 1;
		n[0].taxa_falta = 5000; // 95% hit
		n[1].tempo_acesso = 5;
		n[1].taxa_falta = 10000; // 90% hit
		n[2].tempo_acesso = 10;
		n[2].taxa_falta = 20000; // 80% hit
		n[3].tempo_acesso = 100;
		n[3].taxa_falta = 0;
		
		
		// Tm = 1 + 0.05 * (5 + 0.1 * (10 + 0.2*100))
		// Tm = 1 + 0.05 * (5 + 0.1 * (10 + 20))
		// Tm = 1 + 0.05 * (5 + 3)
		// Tm = 1 + 0.4 = 1.4 == arrendoda para 2

		isEqualUint32(tempo_medio(4, n, NULL),2,5);
	}
}


int main(int argc, char ** argv){

	if (argc < 1 || !argv)
		return 1;

	DESCRIBE("Teste da calculadora de tempo médio de acesso a hierarquia de memória");

	testes_parametros();
	teste_so_mem();
	teste_mem_tlb();
	teste_l1();
	teste_l2();
	teste_l3();

	GRADEME();

	if (grade==maxgrade)
		return 0;
	else return grade;

}
