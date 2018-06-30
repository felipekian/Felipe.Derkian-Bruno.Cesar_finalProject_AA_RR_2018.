#include <stdio.h>
#include <stdlib.h>

void criar_Grafo();
void espera();

int main(){

    printf("\n\t\tGerador de Grafos Aleatorio\n\n");

    criar_Grafo();
    printf("\tGrafo gerado...\n\n");
    espera();
    return 0;
}

void espera(){
    //system("pause");
	getchar();
	getchar();
}

void criar_Grafo(){

    FILE * f = fopen("ArquivoGrafo.txt","w");

    if(f == NULL){
        printf("Nao foi possivel gravar no arquivo....\n\n");
        espera();
        exit(1);
    }

    int vertices , arestas;

    printf("Informe o Total de Vertices: ");
    scanf("%d",&vertices);
    //printf("Informe o Total de Arestas: ");
    //scanf("%d",&arestas);

    printf("\n\n\tgerando....\n\n");

    fprintf(f,"%d\n",vertices);

    int i, j;

    for(i=0 ; i < vertices+1 ; i++){
        int k = rand() % (vertices+1);
        for(j=0 ; j<k ; j++){
            int h;
            do{
                h = rand() % (vertices+1);
            }while(i==h);
            fprintf(f , "%d %d\n",i,h);
        }
    }

    fclose(f);

}
