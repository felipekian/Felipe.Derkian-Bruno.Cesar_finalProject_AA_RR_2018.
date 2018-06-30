#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TRUE  1
#define FALSE 0
#define TAM 30001

struct grafo{
	int tamVertices;
	int vetVisitado[TAM];
	int Matriz[TAM][TAM];
}Grafo;

struct cliqueMax{
	int Principal;
	int tamClique;
	int vetClique[TAM];
}CliqueMax;

void espera(){
	getchar();
}

void pulaLinha(){
	printf("\n");
}

void imprimeMatriz(){

    printf("\n\n\t...Matriz de Adjacencia...\n\n");

    int i , j;

    printf("\tTotal de Vertices = %d\n\n",Grafo.tamVertices);

    printf("\t");
    for(i=0 ; i<=Grafo.tamVertices ; i++){
        printf("%d\t",i);
    }
    pulaLinha();pulaLinha();
    for(i=0 ; i<=Grafo.tamVertices ; i++){
        printf("%d\t",i);
        for(j=0 ; j<=Grafo.tamVertices ; j++){
            printf("%d\t",Grafo.Matriz[i][j]);
        }
        pulaLinha();
    }
    pulaLinha();

    printf("\nPress para sair..");
    espera();
    pulaLinha();
    pulaLinha();


}

void limparGrafo(){
    int i,j;
    for(i=0;i<TAM;i++){

        Grafo.vetVisitado[i]=0;
        Grafo.tamVertices=0;

        for(j=0;j<TAM;j++){
            Grafo.Matriz[i][j]=0;
        }
    }
}

void limpaClique(){
    int i;

    CliqueMax.Principal=-1;
    CliqueMax.tamClique=0;

    for(i=0;i<TAM;i++){
        CliqueMax.vetClique[i]=-1;
    }
}

void lerArquivo(){
	
	

    limparGrafo();

	FILE *f = fopen("ArquivoGrafo.txt","r");

	if(f == NULL){
		system("clear");
		printf("\n\n\tNao foi possivel acessar o arquivo...\n\n");
		espera();
		exit(1);
	}
	
	printf("\n\n\t...Lendo Arquivo com Grafo...\n\n");

	int total;

	fscanf(f , "%d\n",&total);

	Grafo.tamVertices = total;

	while(!feof(f)){

		int v,a;
		fscanf(f,"%d %d\n",&v,&a);

		Grafo.Matriz[v][a] = 1;
		Grafo.Matriz[a][v] = 1;

	}
	fclose(f);
}

void apresentacao(){

	printf("\n\t\t...Problema do Clique Maximo...\n\n\tComponentes\n\t\tFelipe Derkian,\n\t\tBruno Cesar.\n\n");

}

void verificarCliqueMaximo(){
    limpaClique();
	int  vertice , i , j , tam_adj;
        tam_adj = 0;
	int vet_adj[TAM]={0};

    printf("\t\t...Procurando Clique no Grafo...\n\n");

	for(vertice=0 ; vertice <= Grafo.tamVertices ; vertice++){

        printf("Verificando vertice %d.\n",vertice);
	
	tam_adj=0;

		//pega os adjacentes ao vertice selecionado
		//printf("Procurando Adjacentes..\n");
		for(i=0 ; i <= Grafo.tamVertices ; i++){
			if(Grafo.Matriz[ vertice ][ i ] == 1){
				vet_adj[ tam_adj] = i; tam_adj++;
			}
		}

        //printf("Verificando exitencia de clique..\n");
		for(i=0 ; i<tam_adj-1 ; i++){
			if(vet_adj[i] == -1) continue;
			for(j = i+1 ; j < tam_adj ; j++){
				if(vet_adj[j] != -1 && Grafo.Matriz[ vet_adj[i] ][ vet_adj[j] ] != 1){
					vet_adj[j] = -1;
				}
			}
		}

        //printf("calculando o tamanho do clique..\n");
		int tot = 1;
		for(i = 0 ; i < tam_adj ; i++){
			if( vet_adj[i] != -1){
				tot++;
			}
		}

        //printf("verificando se o clique eh maior..\n");
		if( tot > CliqueMax.tamClique){

			CliqueMax.tamClique = tot;
			CliqueMax.Principal = vertice;

			int k=0;
			for(i=0 ; i<tam_adj ; i++){
				if(vet_adj[i] != -1){
					CliqueMax.vetClique[k++] = vet_adj[i];
				}
			}
		}

	}

}

void imprimeCliqueMax(){

	int i , j;

	printf("\n\n\t\t...Impressao das Arestas...\n\n");

    if(CliqueMax.tamClique > 1)
        printf("\tClique maximo no Grafo = %d.\n\n",CliqueMax.tamClique);
    else
        printf("\tClique maximo no Grafo = %d.\n\n",CliqueMax.tamClique-1);


	for(i=0 ; i<CliqueMax.tamClique -1 ; i++){
		printf("\t\t%d <----> %d\n",CliqueMax.Principal,CliqueMax.vetClique[i]);
	}

	for(i=0 ; i<CliqueMax.tamClique -2 ; i++){
		for(j=i+1 ; j<CliqueMax.tamClique-1 ; j++){
			printf("\t\t%d <----> %d\n",CliqueMax.vetClique[i], CliqueMax.vetClique[j]);
		}
	}

}

int main(){
	apresentacao();
	lerArquivo();
	if(Grafo.tamVertices < 21)
            imprimeMatriz();
    else
        printf("\nNao vai imprimir tabela.. total de vertices > 20\n\n");

	clock_t ci , cf;
    ci = clock();//clock inicial
	verificarCliqueMaximo();
    cf = clock();//clock final

    double tempoTotal = (double) (cf - ci) / (double) CLOCKS_PER_SEC;

	imprimeCliqueMax();

    printf("\nTempo total Clique: %lf seg\n\n",tempoTotal);

    printf("Press enter..");
    espera();

	return 0;
}

