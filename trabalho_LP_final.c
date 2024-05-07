#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <math.h>

// parametros globais: 

// vetor de struct 
typedef struct{
	int valor;
	int peso;
}itens_mochila;


//struct dos parametros
typedef struct{
	int quantidade_elementos;
	int peso_maximo;
}parametros_problema;


int main(){
	setlocale(LC_ALL,"Portuguese");
	srand(time(NULL));
	
	//funções usadas na resolução
	itens_mochila *leitura_elementos(char nome_arquivo[]);
	parametros_problema leitura_parametro_geral(char nome_arquivo[]);
	int *mochila(int peso_max, itens_mochila itens[], int quantidade);
	void output(itens_mochila itens[],int vetor_resposta[],parametros_problema parametros);
	
    //variaveis de lógica da interface
	int i;
	int flag = 0;
	
	//Variaveis do problema
	parametros_problema parametros;
	itens_mochila *elementos_mochila;
	int *resposta;
    
	// ciclo de interface do usuário
	while(flag == 0){
		
		//Leitura de dados no arquivo
		char arquivo_input[50];
		printf("Digite o nome do arquivo para a leitura dos dados: ");
		scanf("%50[^\n]s",arquivo_input);
		fflush(stdin);
		
		//armazenando os retornos das variaveis em ponteiros
		parametros = leitura_parametro_geral(arquivo_input);
		elementos_mochila = leitura_elementos(arquivo_input);
		
		
		//função do problema
		resposta = mochila(parametros.peso_maximo,elementos_mochila,parametros.quantidade_elementos);
		
		//output do problema
        
		output(elementos_mochila,resposta,parametros);

		printf("deseja resolver outro problema? digite 0 para a continuar. \n");
		printf("resolver outro problema irá sobrescrever a solução atual, confira o resultado antes de continuar : \n");
		scanf("%d",&flag);
		fflush(stdin);
	}	
	free(elementos_mochila);
	free(resposta);
	
	return 0;
}



// funções para os inputs
itens_mochila *leitura_elementos(char nome_arquivo[]){
	FILE *leitura = fopen(nome_arquivo,"r+");
	
	//variaveis de leitura do arquivo
	int numero_itens, peso_max,i = 0;
	char caracter;
	float aux1,aux2;
	itens_mochila *itens;
    
	//as variáveis aux ajudam na conversão de float para int, sendo necessárias para maior abrangencia de casos para o código

	if(leitura){
		fscanf(leitura,"%d %d", &numero_itens, &peso_max);
		itens = (itens_mochila*)calloc(numero_itens, sizeof(itens_mochila));
		
		while(!feof(leitura)){
			fscanf(leitura,"%f %f",&aux1,&aux2);
			(itens + i)->valor = round(aux1);
			(itens + i)->peso = round(aux2);
			i +=1;
		}
		fclose(leitura);
	}
	if (!leitura) {
    perror("Erro ao abrir o arquivo");
    }
	
	return itens; 
}


//Função que le o o numero de itens e o peso maximo

parametros_problema leitura_parametro_geral(char nome_arquivo[]){
	FILE *leitura = fopen(nome_arquivo,"r");
	int numero_itens, peso_max;
	parametros_problema parametros;
	
	if(leitura){
		fscanf(leitura,"%d %d", &numero_itens, &peso_max);
		parametros.quantidade_elementos = numero_itens;
		parametros.peso_maximo = peso_max;
		fclose(leitura);
	}
	if (!leitura) {
    perror("Erro ao abrir o arquivo");
    }
	
	return parametros;
}

//Algoritimo que resolve o problema da mochila para n = quantidade elementos e peso_max = W;

int *mochila(int peso_max, itens_mochila itens[], int quantidade){
    int i, j,c;
    int matriz[quantidade + 1][peso_max + 1];
    int incluir,excluir;
    int *resposta = (int*)malloc((quantidade + 1)*sizeof(int));
    
	for(i = 0 ; i <= quantidade ; i++){
    	*(resposta + i) = 0;
	}
    
	// Construção da matriz K[n][w] de baixo para cima
    for (i = 0; i <= quantidade; i++) {
        for (j = 0; j <= peso_max ; j++) {
            if (i == 0 || j == 0)
                matriz[i][j] = 0;
            else if (itens[i - 1].peso <= j) {
                incluir = itens[i - 1].valor + matriz[i - 1][j - itens[i - 1].peso];
                excluir = matriz[i - 1][j];
                if (incluir > excluir) {
                    matriz[i][j] = incluir;
                } else {
                    matriz[i][j] = excluir;
                }
            }
			else {
                matriz[i][j] = matriz[i - 1][j];
            }
        }
    }

    // Valor maximo que pode ser obtido e armazenado em K[n][W]
	*resposta = matriz[quantidade][peso_max];
    
	// Rastreando os elementos incluidos
    i = quantidade;
    j = peso_max;
    c = 1;


    while (i > 0 && j > 0) {
        if (matriz[i][j] != matriz[i - 1][j]) {
            *(resposta + c) = 1;
            j -= itens[i - 1].peso;
        }
        i--;
        c++;
    }
    printf("\n");
    return resposta;
}

//Output
void output(itens_mochila itens[], int resposta[],parametros_problema parametros) {
    FILE *output = fopen("resultados.txt", "w");
	int i = 0;
	int soma = 0;
    
	//função do output que retorna os itens selecionados com o seu valor e peso respectivos, além do valor e peso total dos itens

	if (output) {
        fprintf(output, "itens selecionados: \n");
        for(i = 1; i <=parametros.quantidade_elementos; i++) {
            if(*(resposta + i) == 1){
            	fprintf(output,"%d %d \n", (itens + parametros.quantidade_elementos - (i) )->valor, (itens + parametros.quantidade_elementos - (i) )->peso);
            	soma += (itens +parametros.quantidade_elementos - (i) )->peso;
			}
        }

        fprintf(output, "soma total = %d Peso_total_itens= %d \n", resposta[0],soma);
        fclose(output);
    }
    else {
        printf("Erro ao criar o output");
    }
}