#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct grafo{
	int tamanho;
	int* adjMatriz;
}Grafo;

int getIndex(int i, int j, int n){
	if(i < j)
		return (2 * n - i - 1) * i/2 + (j - i) - 1;
	else
		return (2 * n - j - 1) * j/2 + (i - j) - 1;
}

int edge(int i, int j, Grafo *g) {
	return g->adjMatriz[getIndex(i, j, g->tamanho)];
}

void setEdge(int valor, int i, int j, Grafo *g) {
	g->adjMatriz[getIndex(i, j, g->tamanho)] = valor;
}

int insereE_prob(float p){
	int x;
	x=rand() % 100;
  
	if(x<=(p*100)) {
    	return 1;
  }else{
   	return 0;
  } 
}


Grafo *criaGrafo(int n, float p) {
	Grafo *g=(Grafo *)malloc(sizeof(Grafo));;
	g->tamanho=n;
	g->adjMatriz=(int *)malloc((g->tamanho*(g->tamanho-1)/2)*sizeof(int *));
	
	int i,j;
	for(i=0;i<g->tamanho;i++) {
		for(j=0;j<g->tamanho;j++) {
			if(i!=j){
				int x=insereE_prob(p);
				setEdge(x,i,j,g);
			}
		}
	}
	return g;
}

void imprimeG(Grafo *g) {
	int i,j;
	for(i=0;i<g->tamanho;i++) {
		printf("\n");
		printf("| ");
		for(j=0;j<g->tamanho;j++) {
			if(i!=j){
				printf("%d | ",edge(i, j, g));		
			}else{
					printf("0 | ");	
			}
	  }
	}
}

int Teste1_numVertices(Grafo *g1, Grafo *g2) {
	printf("\nTeste1_numVertices\n");
	printf("G1 = %d\n",g1->tamanho);
	printf("G2 = %d\n",g2->tamanho);
	if(g1->tamanho == g2->tamanho){
		return 0;
	}else{
		return 1;	
	}
}

int Teste2_numArestas(Grafo *g1, Grafo *g2) {
	int i, j;
	int m1= 0;
	int m2 = 0; 
  
	for(i = 0; i < g1->tamanho; i++){
		for(j = 0; j < g2->tamanho; j++){
			if(i<j) {
				if( edge(i, j, g1) == 1) {
					m1++;
				}
				if ( edge(i, j, g2) == 1) {
					m2++;
				}
    	}	
		}      	
	}
    
  printf("\nTeste2_numArestas\n");
	printf("G1 = %d\n",m1);
	printf("G2 = %d\n",m2);
	
	if(m1==m2){
		return 0;	
	}else{
		return 1;
	}
}

void bpVisit(Grafo *g, int *cor, int i) {
	int j;
	cor[i] = -1; //pinta de cinza
	for(j=0;j<g->tamanho;j++){
		if(i!=j){
			if(edge(i,j,g)==1){
				//se tiver aresta, eh um vizinho
				if(cor[j]==0){
					//visita se for branco
					bpVisit(g,cor,j);
				}
			}
	  }
		cor[i] = 1;
	}
}

int bpConexo(Grafo *g){
	int cor[g->tamanho];
	int i,j = 0;
  
	//-1 cinza
	//0 branco
	//1 preto
  
	for(i=0;i<g->tamanho;i++){
		//pinta todo mundo de branco
    cor[i] = 0;
	}
	
	bpVisit(g,cor,0);
  
	for(i=0;i<g->tamanho;i++){
		if(cor[i]==0){
			//se achar algum branco
			//eh pq eh desconexo
			return 0;
		}
  }
	return 1;
}

int Teste3_ConexoDesconexo(Grafo *g1, Grafo *g2){
	int a = bpConexo(g1);
	printf("\nTeste3_ConexoDesconexo");
	printf("\nG1 = %d\n",a);
	int b = bpConexo(g2);
	printf("G2 = %d\n",b);
	
	if(a == b){
		//Ou os dois sao conexos
		//Ou os dois sao desconexos
		return 0;
	}else{
		return 1;
	}
}

void bpVisit2(Grafo *g, int *cor, int *pais, int i, int *aux){
	int j;
	cor[i]=-1; //pinta de cinza
	
	for(j=0;j<g->tamanho;j++){
		if(i!=j){
			if(edge(i,j,g)==1){
				//se tiver aresta, eh um vizinho
				if(cor[j]==-1){
					//se for cinza
					if(pais[i]!=j){
						//se for cinza, e nao for o pai dele
						//achamos um circuito 
						*aux=1;
					}
				}else if(cor[j]==0){
					pais[j] = i;
					//j eh u, que eh o filho
					//i eh v, que eh o pai	
					bpVisit2(g, cor, pais, j, aux); //erro era aqui &cont -> cont
				}
    	}
		}
	}
	cor[i] = 1;
}

int bpCircuito(Grafo *g) {
	int cor[g->tamanho];
	int pais[g->tamanho];
	
	int aux = 0;
	int circuito = 0;
	
	//-1 cinza
	//0 branco
  //1 preto
  int i,j = 0;
	for(i=0;i<g->tamanho;i++){
		//pinta todo mundo de branco
   	cor[i] = 0;
   	//coloca -1(NULL) todo mundo sem pai
		pais[i] = -1;
  }
  	
	for(i=0;i<g->tamanho;i++){
		bpVisit2(g, cor, pais, i, &aux);
		if(aux==1){
			//se aux for 1, eh pq tem circuito
			return 1;
		}
	}
	return 0;
}

int Teste4_Circuito(Grafo *g1, Grafo *g2){
	int a = bpCircuito(g1);
	printf("\nTeste4_Circuito");
	printf("\nG1 = %d\n",a);
	int b = bpCircuito(g2);
	printf("G2 = %d\n",b);
	if(a == b){
		//Ou os dois tem circuitos
		//Ou os dois nao tem circuitos
		return 0;
	}else{
		return 1;
	}
}

int bpNumComponentesConexas(Grafo *g){
	int cor[g->tamanho];
	int cont = 0;
  
	//-1 cinza
	//0 branco
	//1 preto
  
  int i,j = 0;
	for(i=0;i<g->tamanho;i++){
		//pinta todo mundo de branco
   	cor[i] = 0;
	}
	
	for(i=0;i<g->tamanho;i++){
		if(cor[i]==0){
			cont++;
			bpVisit(g,cor,i);
		}
	}
	return cont;
}

int Teste5_NumComponentesConexas(Grafo *g1, Grafo *g2){
	int a = bpNumComponentesConexas(g1);
	printf("\nTeste5_NumComponentesConexas");
	printf("\nG1 = %d\n",a);
	int b = bpNumComponentesConexas(g2);
	printf("G2 = %d\n",b);
	
	if(a == b){
		//Os dois tem o mesmo numero de componentes conexas
		return 0;
	}else{
		return 1;
	}
}

void ordena(int *grau,int n) {
	int i, j, aux;
	for(i=1;i<n;i++) {
		for(j=0;j<n-1;j++){
			if(grau[j]>grau[j+1]) {
					aux=grau[j];
					grau[j]=grau[j+1];
					grau[j+1]=aux;
			}
		}
	}
}

void conta_NumGraus(Grafo *g, int *grau){
	int i,j;
	
	for(i=0;i<g->tamanho;i++){
		grau[i]=0;
	}
	
	for(i=0;i<g->tamanho;i++) {
		for(j=0;j<g->tamanho;j++) {
	    if(i!=j){
	    	grau[i] = grau[i] + edge(i, j, g);		
			}	
	  }
	}
}

int Teste6_VetorGraus(Grafo *g1, Grafo *g2){
	int i;
	int grauG1[g1->tamanho];
	int grauG2[g2->tamanho];
	
	printf("\nTeste6_VetorGraus");
	
	if (g1->tamanho == g2->tamanho){
		conta_NumGraus(g1, grauG1);
		conta_NumGraus(g2, grauG2);
		
		printf("\nG1 = ");
		for(i=0;i<g1->tamanho;i++){
			printf("%d ", grauG1[i]);
		}
		printf("\nG1 = ");
		ordena(grauG1, g1->tamanho);	
		for(i=0;i<g1->tamanho;i++){
			printf("%d ", grauG1[i]);
		}
		
		printf("\nG2 = ");
		for(i=0;i<g2->tamanho;i++){
			printf("%d ", grauG2[i]);
		}
		printf("\nG2 = ");
		ordena(grauG2, g2->tamanho);	
		for(i=0;i<g2->tamanho;i++){
			printf("%d ", grauG2[i]);
		}
		printf("\n");
		for(i=0;i<g1->tamanho;i++){ 
			if(grauG1[i] != grauG2[i]){
				return 1; 
			}
		}
		return 0; 	
	}else{
		printf("\nNumero incompativel de Vertices\n");
		return 1;
	}
}

int numero(int x){
	//se for 0, gera um numero aleatorio de vertices (de 1 a 20 vertices)
	if(x==0){
		x=(rand() % 20) +1;
		return x;
	}
	//se nao, retorno o numero que foi passado
	else{
		return x;
	}
}

int main() {
	srand(time(NULL));
	
	clock_t ini;
	clock_t fim;
	float tempo = 0;
	
	Grafo *g1;
  Grafo *g2;
	
	int teste1, teste2, teste3, teste4, teste5, teste6;
  
	//numero de vertices padrao
	//mas na hora de criar o grafo 
	//pode colocar o tanto que quiser
	int n1 = 8; 
	int n2 = 12; 
	int n3 = 16;
	
	//probabilidades padrao
	//mas na hora de criar o grafo 
	//pode colocar qualquer numero entre 0 e 1
	float p1 = 0.25; 
	float p2 = 0.5;
	float p3 = 0.75;
	
	float p_g1 = p2; //probabilidade de ter aresta do g1
	float p_g2 = p_g1; // e do g2
	
	int repeticoes = 100;
	
	int cont = repeticoes;
	while(cont>0){
		cont--;
		
		g1 = criaGrafo(numero(n1),p_g1);
		g2 = criaGrafo(numero(n1),p_g2);
		
		printf("Grafo 1:");
		printf("\n");
		imprimeG(g1);
		printf("\n");
		printf("\n");
	
		printf("Grafo 2:");
		printf("\n");
		imprimeG(g2);
		printf("\n");
		
		ini = clock();
		//tempo apenas da verificacao das caracteristicas 
		//e dos printf dessa parte
	  	
		//retorna 1 se sao diferentes nas caracteriscas 
		//retorna 0 caso contrario
		
		teste1 = Teste1_numVertices(g1, g2);
		printf("teste1 = %d\n",teste1);
	
		teste2 = Teste2_numArestas(g1, g2);
		printf("teste2 = %d\n",teste2);
	
		teste3 = Teste3_ConexoDesconexo(g1, g2);
		printf("teste3 = %d\n",teste3);
	
		teste4 = Teste4_Circuito(g1, g2);
		printf("teste4 = %d\n",teste4);
	
		teste5 = Teste5_NumComponentesConexas(g1, g2);
		printf("teste5 = %d\n",teste5);
		
		teste6 = Teste6_VetorGraus(g1, g2);
		printf("teste6 = %d\n",teste6);
		
		fim = clock();
		tempo = tempo + (fim-ini);
		
		if((teste1+teste2+teste3+teste4+teste5+teste6)==0){
	  		printf("\nG1 e G2 podem ser isomorfos\n");
	  		//nao eh certeza que esses grafos sejam isomorfos
	  		//break;
		}else{
			printf("\nG1 e G2 nao sao isomorfos\n");
			//certeza que nao sao isomorfos
		}
		printf("\n*********************************\n");
	}
	
	float x = tempo/repeticoes;
	printf("\nTempo Medio = %f\n",x);  
	
	return 0;
}