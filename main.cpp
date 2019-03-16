//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <limits>
using namespace std;
typedef int Vertex;
//----------------------------------------------------------------------------------------------------------------------
template <class T>
class No {
private:
    T item;
    No<T> * prox;
public:
    T getItem() { return this->item; }
    void setItem(T pItem) { this->item = pItem; }
    No<T> * getProx() { return this->prox; }
    void setProx(No<T> * pProx) { this->prox = pProx; }
};
//----------------------------------------------------------------------------------------------------------------------
template <class T>
class Lista {
private:
    No<T> * prim, * ult;
    bool vazia() { return (this->prim == this->ult); }
    No<T> * predecessor(No<T> * no) {
        No<T> * aux = this->prim;
        while (aux->getProx() != no){ aux = aux->getProx(); }
        return aux;
    }
public:
    Lista() {
        this->prim = new No<T>();
        this->prim->setProx(nullptr);
        this->ult = this->prim;
    }

    No<T> * getFrente() { return this->prim; }
    void setFrente(No<T> * frente) { this->prim = frente; }
    No<T> * getTras() { return this->ult; }
    void setTras(No<T> * tras) { this->ult = tras; }

    void insere(T);
    void remove(int, T *);
    No<T> * busca(int);
};
//----------------------------------------------------------------------------------------------------------------------
template <class T>
class Fila {
private:
    No<T> * frente, * tras;
public:
    Fila() {
        this->frente = new No<T>();
        this->frente->setProx(nullptr);
        this->tras = this->frente;
    }

    No<T> * getFrente() { return this->frente; }
    void setFrente(No<T> * pFrente) { this->frente = pFrente; }
    No<T> * getTras() { return this->tras; }
    void setTras(No<T> * pTras) { this->tras = pTras; }

    void enfileira(T);
    void desenfileira(T *);
    bool vazia();
};
//----------------------------------------------------------------------------------------------------------------------
class Vertice {
private:
    int numVertice, cor, distancia, predecessor;

public:
    Vertice() {}
    Vertice(int pNumVertice) { this->setNumVertice(pNumVertice); }

    int getNumVertice() { return this->numVertice; }
    void setNumVertice(int pNumVertice) { this->numVertice = pNumVertice; }
    int getCor() { return this->cor; }
    void setCor(int pCor) { this->cor = pCor; }
    int getDistancia() { return this->distancia; }
    void setDistancia(int pDistancia) { this->distancia = pDistancia; }
    int getPredecessor() { return this->predecessor; }
    void setPredecessor(int pPredecessor) { this->predecessor = pPredecessor; }
};
//----------------------------------------------------------------------------------------------------------------------
class Grafo {
private:
    vector<Lista<Vertex>> adj;
    int ordem, tamanho;
    void destroi();

public:
    Grafo(int pN){ inicializar(pN); }

    void inicializar(int);
    void inserirAresta(Vertex, Vertex);
    void mostrar();

    int getOrdem() { return this->ordem; }
    void setOrdem(int pOrdem) { this->ordem = pOrdem; }
    int getTamanho() { return this->tamanho; }
    void setTamanho(int pTamanho) { this->tamanho = pTamanho; }
    vector<Lista<Vertex>> getAdj() { return this->adj; }
};
//----------------------------------------------------------------------------------------------------------------------
template <typename T>
void Lista<T>::insere(T pItem) {
    this->ult->setProx(new No<T>());
    this->ult = this->ult->getProx();
    this->ult->setItem(pItem);
    this->ult->setProx(nullptr);
}
template <typename T>
void Lista<T>::remove(int pChave, T * x) {
    if (!this->vazia()) {
        No<T> * aux = this->busca(pChave);
        if (aux != nullptr) {
            * x = aux->getItem();
            No<T> * p = this->predecessor(aux);
            p->setProx(aux->getProx());
            delete aux;
            if (p->getProx() == nullptr) { this->ult = p; }
        }
    }
}
template <typename T>
No<T> * Lista<T>::busca(int pChave) {
    No<T> * aux = this->prim->getProx();
    while (aux != nullptr && aux->getItem() != pChave) { aux = aux->getProx(); }
    return aux;
}
//----------------------------------------------------------------------------------------------------------------------
template <typename T>
bool Fila<T>::vazia() { return (this->frente == this->tras); }
template <typename T>
void Fila<T>::enfileira(T pItem) {
    this->tras->setProx(new No<T>());
    this->tras = this->tras->getProx();
    this->tras->setItem(pItem);
    this->tras->setProx(nullptr);
}
template <typename T>
void Fila<T>::desenfileira(T * pItem) {
    if (!this->vazia()) {
        No<T> * aux = this->frente;
        this->frente = this->frente->getProx();
        * pItem = this->frente->getItem();
        delete aux;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Grafo::destroi() {
    this->adj.clear();
    this->setOrdem(0);
    this->setTamanho(0);
}
void Grafo::inicializar(int pN) {
    if (this->getOrdem() != 0) { this->destroi(); }
    this->setOrdem(pN);
    this->setTamanho(0);

    for (int i = 0; i <=pN; i++) { this->adj.push_back(Lista<Vertex>()); }
}
void Grafo::inserirAresta(Vertex u, Vertex v) {
    this->adj[u].insere(v);
    this->adj[v].insere(u);
    this->setTamanho(this->getTamanho()+1);
}
void Grafo::mostrar() {
    for (int i = 1; i <= this->getOrdem(); i++) {
        cout << "v[" << i << "] = ";
        Lista<Vertex> aux = adj[i];
        No<Vertex> * aux2 = aux.getFrente()->getProx();
        while (aux2 != nullptr) {
            cout << aux2->getItem() << " ";
            aux2 = aux2->getProx();
        }
        cout << endl;
    }
}
//----------------------------------------------------------------------------------------------------------------------
int coordParaVertice(int i, int j) {
    if (i == 1){ return (i*j); }
    else { return ((8*(i-1))+j); }
}
bool existeAresta(int li, int lj, int ci, int cj) {
    int n1 = li-lj;
    int n2 = ci-cj;

    if (n1 < 0) { n1 = n1*(-1); }
    if (n2 < 0) { n2 = n2*(-1); }

    return ((n1+n2) == 3);
}
void grafoCavalo(Grafo &g) {
    if (g.getOrdem() == 64) {

        vector<pair<int, int>> coordenadas;
        coordenadas.push_back(make_pair(0,0));

        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                pair<int, int> aux = make_pair(i, j);
                coordenadas.push_back(aux);
            }
        }

        for (int i = 1; i <= 64; i++) {
            for (int j = 1; j <= 64; j++) {
                if (i != j && i < j) {
                    int li = coordenadas[i].second;
                    int lj = coordenadas[j].second;
                    int ci = coordenadas[i].first;
                    int cj = coordenadas[j].first;

                    if (li != lj && ci != cj && existeAresta(li, lj, ci, cj)) {
                        g.inserirAresta(i, j);
                    }
                }
            }
        }
    } else { cout << "A ORDEM DO GRAFO PRECISAR SER IGUAL A 64"; }
}
vector<Vertice> BFS(Grafo g, Vertex s) {
    vector<Lista<Vertex>> listaAdj = g.getAdj();
    vector<Vertice> vertices(g.getOrdem()+1);
    for (int i = 0; i <= g.getOrdem(); i++) {
        vertices[i].setNumVertice(i);
        vertices[i].setCor(0);
        vertices[i].setDistancia(numeric_limits<int>::max());
        vertices[i].setPredecessor(-1);
    }
    vertices[s].setCor(1);
    vertices[s].setDistancia(0);
    vertices[s].setPredecessor(-1);

    Fila<Vertice> fila;
    fila.enfileira(vertices[s]);
    while (!fila.vazia()) {
        Vertice u;
        fila.desenfileira(&u);
        Lista<Vertex> aux = listaAdj[u.getNumVertice()];
        No<Vertex> * aux2 = aux.getFrente()->getProx();
        while (aux2 != nullptr) {
            if (vertices[aux2->getItem()].getCor() == 0) {
                vertices[aux2->getItem()].setCor(1);
                vertices[aux2->getItem()].setDistancia(u.getDistancia()+1);
                vertices[aux2->getItem()].setPredecessor(u.getNumVertice());
                fila.enfileira(vertices[aux2->getItem()]);
            }
            aux2 = aux2->getProx();
        }
        vertices[u.getNumVertice()].setCor(2);
    }
    return vertices;
}
void run(Grafo grafo) {
    vector<pair<int, int>> coordenadas;
    string entrada;
    for (int i = 0; i < 5; i++) {
        cin >> entrada;
        coordenadas.push_back(make_pair(entrada[0]-96, entrada[1]-48));
    }

    vector<int> posicoes;
    for (pair<int, int> x : coordenadas) {
        posicoes.push_back(coordParaVertice(x.first, x.second));
    }

    vector<int> distancias;
    int rei = posicoes[4];
    for (unsigned int j = 0; j < posicoes.size()-1; j++) {
        vector<Vertice> bfsResultado = BFS(grafo, posicoes[j]);
        int predecessorRei = bfsResultado[rei].getPredecessor();
        Vertice aux = bfsResultado[predecessorRei];

        distancias.push_back(aux.getDistancia());
    }

    int menor = numeric_limits<int>::max();
    for (int x : distancias) {
        if ( x < menor) { menor = x; }
    }

    vector<int> saida;
    for (int x : distancias) {
        if (x == menor) { saida.push_back(x); }
    }

    for (unsigned int j = 0; j < saida.size()-1; j++) {
        cout << saida[j] << " ";
    }
    cout << saida[saida.size()-1] << endl;
}
//----------------------------------------------------------------------------------------------------------------------
int main() {
    Grafo grafo(64);
    grafoCavalo(grafo);

    int numEntradas;

    cin >> numEntradas;
    for (int i = 0; i < numEntradas; i++) {
        run(grafo);
    }

    return 0;
}