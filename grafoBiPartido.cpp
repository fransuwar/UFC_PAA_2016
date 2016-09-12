/*
Projeto e Analise de Algoritmos
Exercicio de Grafos, Busca em Profundidade utilizada para detectar grafo Bipartido
MONITORIA - 05/08/2016
PSEUDOCÓDIGO:
DFS-VISIT-BIPARTIDO(u)                        		// Mesma complexidade da DFS.
	cor[u] <- cinza
	para cada v adjacente a u
		se cor[v] = branco
			pi[v] <- u
			conj[v] <- (conj[u] = A) ? B : A     	(*)
			se DFS-VISIT-BIPARTIDO(v) = falso
				retorne falso
		senão se conj[v] = conj[u]              	(*)
			retorne falso (contém ciclo ímpar)   	(*)
	retorne verdadeiro                         		(*)
    
DFS-BIPARTIDO(Adj[], n)
	para cada vértice u
		cor[u] <- branco; pi[u] <- NULO
	conj[1] <- A // primeiro vértice em A      		(*)
	para u <- 1 até n
		se cor[u] = branco
			se DFS-VISIT-BIPARTIDO(u) = falso    	(*)
				retorne falso                     	(*)
	retorne verdadeiro                         		(*)

IMPRIME-CICLO-IMPAR(u, v)
	se u=v então
		imprime u
	w <- v
	enquanto w != u faça
		imprime w
		w <- pi[w]
	imprime w

Exercício:

PARTE I: Finalizar a atividade da aula do dia 09/09 (da última aula), ou seja implementar um algoritmo para checar se um grafo é bipartido, 
		 testar em um grafo com ciclo par e um com ciclo ímpar, se não for bipartido imprimir o ciclo ímpar.	

*/

#include <iostream>
#include <list>
#include <ctime>
using namespace std;

#define N 9


/*Enumeracoes*/
enum Cores{branco, cinza, preto};
enum Pecas{cueca,calca,cinto,camisa,gravata,paleto,meias,sapatos,relogio};

list<int> Adj[N];
Cores cor[N];
int d[N]; //tempo inicial em que o vertice foi acessado
int f[N]; //tempo em que o vertice foi finalizado
int pi[N];
int tempo = 0;
char conjunto[N];

/*Assinatura funçoes*/
bool DFS_VISIT_BIPARTIDO(int u);
bool DFS_BIPARTIDO();
void inicializa_grafo();
void imprime_ciclo_impar(int u, int v);

/*Implementacao funcoes*/
bool DFS_VISIT_BIPARTIDO(int u){
	list<int>::iterator it;
	cor[u] = cinza;
	d[u] = tempo++;
	
	for(it=Adj[u].begin(); it != Adj[u].end(); it++){
		if(cor[*it] == branco){
			pi[*it] = u;
			conjunto[*it] = (conjunto[u] == 'A') ? 'B' : 'A';
			if(!DFS_VISIT_BIPARTIDO(*it)){
				return false;
			}
		}else if(conjunto[*it] == conjunto[u]){
			imprime_ciclo_impar(u, *it);
			return false; //Contem ciclo impar
		}		
	}
	
	cor[u] = preto;
	f[u] = tempo++;

	return true;
}
/*
Projeto e Analise de Algoritmos
Exercicio de Grafos, Busca em Profundidade 
MONITORIA - 05/08/2016
PSEUDOCÓDIGO:
DFS-VISIT(u)
	cor[u] <- cinza
	d[u] <- tempo <- tempo + 1
	para cada v adjacente a u
		se cor[v] = branco
		pi[v] <- u
		DFS-VISIT(v)
	cor[u] <- preto
	f[u] <- tempo <- tempo + 1

DFS(Adj[], n)
	para cada vértice u
		cor[u] <- branco; pi[u] <- NULO
		tempo <- 0
	para cada vértice u
		se cor[u] = branco
		DFS-VISIT(u)


Exercício:

PARTE I: Implementar o algoritmo de Busca em Profundidade com lista de adjacência e analisar o tempo pra grafo denso e espaço
PARTE II: Analise o algoritmo e dê a ordem de grandeza pra operação da busca em profundidade.

*/


bool DFS_BIPARTIDO(){
	list<int>::iterator it;
	
	for(int u = 0; u < N; u++){
		cor[u] = branco;
		pi[u] = -1;		
	}

	conjunto[0] = 'A'; //primeiro vertice em A
	
	for(int u = 0; u < N; u++){
		if(cor[u] == branco){
			if(!DFS_VISIT_BIPARTIDO(u)){
				return false;
			}
		}
	}

	return true;
}

void imprime_ciclo_impar(int u, int v){
	if(u == v){
		cout << "u";
	}

	int w = v;
	while(w!=u){
		cout << w;
		w = pi[w];
	}

	cout << w;
}

void inicializa_grafo()
{
   Adj[cueca].push_back(calca);
   Adj[cueca].push_back(sapatos);
   Adj[calca].push_back(sapatos);
   Adj[calca].push_back(cinto);
   Adj[cinto].push_back(paleto);
   Adj[camisa].push_back(cinto);
   Adj[camisa].push_back(gravata);
   Adj[gravata].push_back(paleto);
   Adj[meias].push_back(sapatos);

}

int main(){
	inicializa_grafo();
	if(DFS_BIPARTIDO())
		cout << "true" << endl;
	else
		cout << "false" << endl;

	return 0;
}