#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0
#define TAM 10000

struct grafo{
    int tamVertices;
    int matriz[TAM][TAM];
}Grafo;

void zeraGrafo(){
    int i , j;
    for(i=0 ; i<Grafo.tamVertices ; i++){
        for(j=0 ; j<Grafo.tamVertices ; j++){
            Grafo.matriz[i][j] = FALSE;
        }
    }
}

//o grafo vai de 0 ate o vertice maximo
void inicializaGrafo(int valor){
    Grafo.tamVertices = valor+1;
}

void pulaLinha(){
    printf("\n");
}

void limpaTela(){
    system("clear");
}
void espera(){
    getchar();
}

void imprimeGrafo(){

    limpaTela();
    printf("\tImpressao da matriz de Adjacencia...\n");

    int i , j;
    pulaLinha();
    printf("\t");
    for(i=0 ; i<Grafo.tamVertices ; i++){
        printf("%d\t",i);
    }
    pulaLinha();pulaLinha();
    for(i=0 ; i<Grafo.tamVertices ; i++){
        printf("%d\t",i);
        for(j=0 ; j<Grafo.tamVertices ; j++){
            printf("%d\t",Grafo.matriz[i][j]);
        }
        pulaLinha();
    }
    pulaLinha();

    printf("\nPress para sair..");
    espera();
    limpaTela();
    return;
}

void lerArquivoGrafo(){
    FILE * f = fopen("ArquivoGrafo.txt" , "r");
    if(f == NULL){
        limpaTela();
        printf("Erro na abertura do arquivo, press para finalizar...");
        espera();
        exit(1);
    }

    //pega o total de vertices do grafo
    int tot;
    fscanf(f , "%d\n" , &tot);
    inicializaGrafo(tot);

    printf("TAM do Grafo: %d\n",tot);

    //limpa o grafo
    zeraGrafo();

    while(!feof(f)){
        int v ,a;
        fscanf(f , "%d %d\n",&v ,&a);
        printf("v = %d, a = %d\n",v,a);
        Grafo.matriz[v][a] = TRUE;
        Grafo.matriz[a][v] = TRUE;
    }
    fclose(f);
}

void apresentacao(){
    printf("\tProblema do Clique\n\nComponentes:\n\t\tFelipe Derkian\n\t\tBrunno Claudino\n\n");
}

int verificaClique(){

    int k , i , j , tam_cliques=0;
    int vet_cliques_tam[tam_cliques];
    //pega o vertice base Ex.: [1] -> 2 -> 3 -> NULL, base = 1
    for(k=0 ; k<=Grafo.tamVertices ; k++){
        int tam=0;
        int vet_adj[tam]; //serve para receber todos os vertices adjcentes de k

        //verifica a existencia de adjcentes
        for(i=0;i<Grafo.tamVertices ; i++){
            //caso exista a adjacencia inseri-o no vetor
            if(Grafo.matriz[k][i] == 1){
                vet_adj[tam] = i; tam++;
            }
        }

        //verifico se existe o clique
        int p,q;
        for(p=0;p<tam-1;p++){

            //se for constatado que um vertice não é adj ele recebe -1 logo nao faz parte do clique
            if(vet_adj[p] == -1) continue;

            //faz a checagem do vet[p] con tdos os sucessores apartir de p+1
            for(q=p+1;q<tam;q++){
                if(vet_adj[q] != -1 && Grafo.matriz[vet_adj[p]][vet_adj[q]] != 1){
                    vet_adj[q] = -1;
                }
            }
        }

        //verifica os vertices que sobreviveram ao clique a partir do vertice K
        int t=0;
        for(q=0;q<tam;q++){
            if(vet_adj[q] != -1){
                t++;
            }
        }
        //apos pegar o tam clique salva
        vet_cliques_tam[tam_cliques] = t+1; //mais 1 por causa do vertice de start que é o K no primeiro for
        tam_cliques++;//incrementa o tamanho do vertice do clique

    }

    //verifica o maior clique dentro do vetor vet_clique_tam que armazena todos os tam cliques
    int maiorClique = -1;
    for(i=0 ; i<tam_cliques ; i++){
         //****se quiser o maior, menor ou igual, basta mudar o IF no for****
        if(vet_cliques_tam[i] > maiorClique){
            maiorClique = vet_cliques_tam[i];
        }
    }

    //retorna o maior clique, mas pode ser o manor ou igual ... basta trocar o IF do for acima
    return maiorClique;
}

int main(){
    apresentacao();
    espera();
    lerArquivoGrafo();
    imprimeGrafo();
    int maiorClique = verificaClique();
    printf("\n\tImpressao do resultado\n\nO maior Clique no grafo = %d.\n",maiorClique);

	return 0;
}


















