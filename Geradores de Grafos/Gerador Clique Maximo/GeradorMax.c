#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE  1
#define FALSE 0


void criarGrafo(){

    FILE * f = fopen("ArquivoGrafo.txt","w");

    if(f == NULL) {
        printf("\n\nNao foi possivel gerar o arqivo...");
        exit(1);
    }



    int vert;
    printf("\n\n\t\tDigite o total de vertices: ");
    scanf("%d",&vert);

    printf("\n\n\t\t...Gerando arquivo...\n\n");

    fprintf(f , "%d\n",vert);

    int i , j;

    for(i=0 ; i<vert ; i++){
        for(j=i+1 ; j<=vert ; j++){
            if(i != j){
                fprintf(f,"%d %d\n",i,j);
            }
        }
    }

    fclose(f);

	printf("\t\tArquivo Gerado...\n\n");

}


int main(){
    criarGrafo();
	return 0;
}

