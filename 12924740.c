/* Rafael Francisco de Freitas Timoteo 12924740 */

/* O processador executa instruções a partir do endereço zero.
 * as instruções DDF e DFF não precisam ser codificadas.
 * as instruções de deslocamento preservam o sinal.
 * a instrução PAR termina o simulador. */
 
#include <stdio.h>
#include <stdlib.h>

#define MEMSIZE 10000

int M[MEMSIZE];  // representa a memória do HIPO.

void loadM (char *imgFileName) {
	FILE *fp;
	fp=fopen (imgFileName, "rt");
	int i=0;
	while (!feof(fp)) {
		printf ("lendo linha %d ", i);
		/* quem escrever o conteúdo da memória deve ter o cuidado de fazê-lo 
		 * conforme a especificação. Esta função não checa. */
		/* podem acontecer coisas inesperadas caso falte ou sobre \n no arquivo. 
		 * */
		fscanf (fp, "%d\n", &(M[i]));
		printf ("conteúdo: %d ", M[i]);
		++i;
	}
	fclose(fp);
}

void dumpM () {
	for (int i=0;i<MEMSIZE;i++) {
		printf ("(%d,%d)\t", i, M[i]);
	}
}

int acc;
int pc;  // ou ai
int mbr; // talvez não seja necessário.

int Instrucao(int valor){
	return valor/100;
}

int Endereco(int valor){
	return valor%100;
}

void executa () {
    printf("Execução:\n");

    acc = 0;
    pc = 0;
    
    int II;
    int EE;
    
    II = Instrucao(M[pc]);
    EE = Endereco(M[pc]);
    
    while (II != 70) { // loop infinito até encontrar a instrução de parada (PAR)
        II = Instrucao(M[pc]); // extrai o II da instrução 
        EE = Endereco(M[pc]); // extrai o EE da instrução 
        pc++; 
        
        switch (II) {
            case 11: // (CEA) Copie o conteúdo do endereço EE no acumulador.
                acc = M[EE];
                break;
                
            case 12: // (CAE) Copie o conteúdo do acumulador no endereço EE. 
                M[EE] = acc;
                break;
                
            case 21: //  (SOM) Some o conteúdo do endereço EE com o conteúdo do acumulador e guarde o resultado no acumulador.
                acc += M[EE];
                break;
                
            case 22: // (SUB) Subtraia o conteúdo do endereço EE do conteúdo do acumulador e guarde o resultado no acumulador.
                acc -= M[EE];
                break;
                
            case 23: // (MUL) Multiplique o conteúdo do endereço EE com o conteúdo do acumulador e guarde o resultado no acumulador.
                acc *= M[EE];
                break;
                
            case 24: // (DIV) Divide o conteúdo do acumulador pelo conteúdo do endereço EE e guarde o resultado no acumulador.
                if (M[EE] == 0) {
                    printf("Erro: divisão por zero.\n");
                    break;
                }
                acc = acc/M[EE];
                break;
                
            case 25: // (MOD) [AC] recebe o resto da divisão [AC] / [EE].
                if (M[EE] == 0) {
                    printf("Erro: divisão por zero.\n");
                    break;
                }
                acc = acc%M[EE];
                break;
                
            case 31: // (LER) Leia um número e guarde-o no endereço EE.
                printf("Digite um número: ");
                scanf("%d", &M[EE]);
                break;
                
            case 41: // (IMP) Imprima o conteúdo do endereço EE.
                printf("%d\n", M[EE]);
                break;
                
            case 50: // (NOP) Nenhuma operação é efetuada.
                break;
                
            case 51: // (DES) Desvie a execução para o endereço EE, i.e. pc recebe EE.
                pc = EE;
                break;
                
            case 52: // (DPO) Se o conteúdo do acumulador for maior do que zero, desvie a execução para o endereço EE.
                if (acc > 0) {
                    pc = EE;
                }
                break;
                
            case 53: // (DPZ) Se o conteúdo do acumulador for maior ou igual a zero, desvie a execução para o endereço EE. 
                if (acc >= 0) {
                    pc = EE;
                }
                break;
                
            case 54: // (DNE) Se o conteúdo do acumulador for menor do que zero, desvie a execução para o endereço EE.
                if (acc < 0) 
                    pc = EE;
                break;
                
            case 55: // (DNZ) Se o conteúdo do acumulador for menor ou igual a zero, desvie a execução para o endereço EE. 
                if (acc <= 0) {
                    pc = EE;
                }
                break;
                
            case 56: // (DDZ) Se o conteúdo do acumulador for diferente de zero, desvie a execução para o endereço EE. 
                if (acc != 0) {
                    pc = EE;
                }
                break;
                
            case 57: // (DZZ) Se o conteúdo do acumulador for igual a zero, desvie a execução para o endereço EE. 
                if (acc == 0) {
                    pc = EE;
                }
                break;
                
            case 61: // (ADE) Desloque os dígitos do acumulador uma posição à esquerda, desprezando o digito mais significativo.
                acc *= 10;
                break;
                
            case 62: // (ADD) Desloque os dígitos do acumulador uma posição à direita, desprezando o digito menos significativo.
                acc /= 10;
                break;
            
        }
    }
}


void main (int argc, char *argv[]) {
	puts ("Hello");
	if (argc>1) {
		/* Um computador frequentemente tem um programa que carrega um 
		 * executável na memória. Esse programa é mais complicado que o tipo
		 * de programa que é suficiente para oferecer um entendimento básico
		 * dos conceitos que quero explorar na disciplina. Por isso, a carga de
		 * um programa na memória, neste simulador, é algo feito "por fora"
		 * da simulação.
		 * */
		loadM(argv[1]);
		dumpM();
		executa();
	}
}