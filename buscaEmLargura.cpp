/*
Projeto e Analise de Algoritmos
Exercicio de Grafos, Busca em Profundidade 
MONITORIA - 05/08/2016
PSEUDOCÓDIGO:
BFS(G,s):
	para cada vértice u de G (excluindo o s)
		cor[u] <- branco; d[u] 	<- oo; pi[u] <- NULO
	
	cor[s] <- cinza; d[s] <- 0; pi[s] <- NULO		
	
	declare uma fila vazia Q
	insira s na fila Q
	
	enquanto Q não é vazia
		remova o próximo elem. da fila Q e o armazene em u 
		para cada vértice v em Adj[u]
			se cor[v] = branco
            cor[v] <- cinza; d[v] <- d[u] + 1; pi[v] <- u
            insira v na fila Q
      	cor[u] <- preto


Exercício:

PARTE I: Implementar o algoritmo de Busca em Largura com lista de adjacência e analisar o tempo pra grafo denso e espaço.
PARTE II: Analise o algoritmo e dê a ordem de grandeza pra operação da busca em largura.


Dicas de implementação em C++:
- Para aumentar a legibilidade, declare um enum para as cores:
  enum Cor {branco, preto, cinza};
- Para o valor infinito, use "INT_MAX". Necessário incluir
  #include <climits>
- Para NULO use -1, pois o valor 0 representa o 1o vértice.
- Pode usar uma lista como fila. Declare com list<int> Q;
- Para inserir um valor x na fila use 
  Q.push_back(x);
- Para testar se Q é vazia use Q.empty()
- Para excluir e armazenar o próximo elem. de Q use 
  int u = Q.front(); Q.pop_front();

*/


#include <iostream>
#include <climits>
#include <list>
#include <ctime>
using namespace std;

#define N 8

enum Cores{branco, cinza, preto};
enum V{s,w,r,t,x,v,u,y};

list<int> Adj[N];
list<int> Q;

Cores cor[N];
int d[N];
int pi[N];

void inicializa_grafo()
{
   Adj[s].push_back(w);
   Adj[s].push_back(r);
   Adj[r].push_back(s);
   Adj[r].push_back(v);
   Adj[v].push_back(r);
   Adj[w].push_back(s);
   Adj[w].push_back(t);
   Adj[w].push_back(x);
   Adj[t].push_back(w);
   Adj[t].push_back(x);
   Adj[t].push_back(u);
   Adj[x].push_back(w);
   Adj[x].push_back(t);
   Adj[x].push_back(u);
   Adj[x].push_back(y);
   Adj[u].push_back(t);
   Adj[u].push_back(x);
   Adj[u].push_back(y);
   Adj[y].push_back(x);
   Adj[y].push_back(u);
}

void inicializa_cores(Cores cor[], int d[]){
	cor[0] = branco;
	d[0] = 0;
	pi[0] = -1;

	for(int i=1; i < N; i++){
		cor[i] = branco;
		d[i] = INT_MAX;  
		pi[i] = -1;
	}
}

/*
Print-Path(G, s, v)
	se v = s então
		imprime s
	senão
		se pi[v ] = NULO então
			imprime não existe caminho de s a v .
		senão
			Print-Path(G, s, pi[v ])
			imprime v
*/

void imprimir_caminho(int s, int v){
	if(v == s){
		cout << s;
	}else{
		if(pi[v] == -1){
			cout << "Nao existe caminho de s a v";
		}else{
			imprimir_caminho(s, pi[v]);
			cout << v;
		}
	}
}

void busca_largura(Cores cor[]){
	while(!Q.empty()){
		int u = Q.front();
		Q.pop_front();
		list<int>::iterator it;

		for(it=Adj[u].begin(); it != Adj[u].end(); it++){
			if(cor[*it] == branco){
				cor[*it] = cinza;
				d[*it] = d[u] + 1;
				pi[*it] = u;
				Q.push_back(*it);
			}	
		}
		
		cor[u] = preto;
	}	
}

int main(){

	inicializa_grafo();
	inicializa_cores(cor, d);

	Q.push_back(s);

	busca_largura(cor);
	imprimir_caminho(s, t);

	return 0;
}