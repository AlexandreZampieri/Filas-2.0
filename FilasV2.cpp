//Feito por Alexandre Zampieri Salles e Caio Victor Andrade 
#include <iostream>
using namespace std;

#define MAX 100

struct Fila {
    int ini;
    int fim;
    int nos[MAX];
};

struct Guiche {
    int id;
    Fila* senhasAtendidas;
    Guiche* proximo;
};

struct ListaGuiches {
    Guiche* inicio;
};

Fila* initFila() {
    Fila *f = new Fila;
    f->ini = 0;
    f->fim = 0;
    return f;
}

int isEmpty(Fila *f) { return (f->ini == f->fim); }
int incrementa(int i) { return (i == MAX - 1 ? 0 : i + 1); }

int count(Fila *f) {
    int qtd = 0;
    int i = f->ini;
    while (i != f->fim) {
        qtd++;
        i = incrementa(i);
    }
    return qtd;
}

int enqueue(Fila *f, int valor) {
    if (incrementa(f->fim) == f->ini) return 0;
    f->nos[f->fim] = valor;
    f->fim = incrementa(f->fim);
    return 1;
}

int dequeue(Fila *f) {
    if (isEmpty(f)) return -1;
    int valor = f->nos[f->ini];
    f->ini = incrementa(f->ini);
    return valor;
}

ListaGuiches* initLista() {
    ListaGuiches* l = new ListaGuiches;
    l->inicio = NULL; 
    return l;
}

void adicionarGuiche(ListaGuiches* l, int id) {
    Guiche* novo = new Guiche;
    novo->id = id;
    novo->senhasAtendidas = initFila();
    novo->proximo = l->inicio; 
    l->inicio = novo;
    cout << "Guiche " << id << " aberto com sucesso!" << endl;
}

Guiche* buscarGuiche(ListaGuiches* l, int id) {
    Guiche* atual = l->inicio;
    while (atual != NULL) { 
        if (atual->id == id) return atual;
        atual = atual->proximo;
    }
    return NULL; 
}

int contarGuiches(ListaGuiches* l) {
    int qtd = 0;
    Guiche* atual = l->inicio;
    while (atual != NULL) { 
        qtd++;
        atual = atual->proximo;
    }
    return qtd;
}

int totalGeralAtendidas(ListaGuiches* l) {
    int total = 0;
    Guiche* atual = l->inicio;
    while (atual != NULL) { 
        total += count(atual->senhasAtendidas);
        atual = atual->proximo;
    }
    return total;
}

void listarAtendidasPorGuiche(Guiche* g) {
    if (isEmpty(g->senhasAtendidas)) {
        cout << "Nenhuma senha atendida neste guiche ate o momento." << endl;
        return;
    }
    cout << "Senhas atendidas pelo guiche " << g->id << ": ";
    int i = g->senhasAtendidas->ini;
    while (i != g->senhasAtendidas->fim) {
        cout << g->senhasAtendidas->nos[i] << " ";
        i = incrementa(i);
    }
    cout << endl;
}

int main() {
    Fila* senhasGeradas = initFila();
    ListaGuiches* listaDeGuiches = initLista();
    
    int opcao;
    int proximaSenha = 1;

    do {
        cout << "\n-----" << endl;
        cout << "Senhas aguardando: " << count(senhasGeradas) << endl;
        cout << "Guiches abertos: " << contarGuiches(listaDeGuiches) << endl;
        cout << "\n-----" << endl;
        cout << "0 - Sair" << endl;
        cout << "1 - Gerar senha" << endl;
        cout << "2 - Abrir guiche" << endl;
        cout << "3 - Realizar atendimento" << endl;
        cout << "4 - Listar senhas atendidas" << endl;
        cout << "Opçao: ";
         cin >> opcao;

        switch(opcao) {
            case 1: {
                if (enqueue(senhasGeradas, proximaSenha)) {
                    cout << "Senha gerada: " << proximaSenha << endl;
                    proximaSenha++;
                } else {
                    cout << "Fila de senhas cheia!" << endl;
                }
                break;
            }
            case 2: { 
                int id;
                cout << "Digite o Id para o novo guiche: ";
                cin >> id;
                if (buscarGuiche(listaDeGuiches, id) != NULL) { 
                    cout << "Atençao: Ja existe um guiche com este Id!" << endl;
                } else {
                    adicionarGuiche(listaDeGuiches, id);
                }
                break;
            }
            case 3: { 
                if (isEmpty(senhasGeradas)) {
                    cout << "Nenhuma senha aguardando atendimento." << endl;
                    break;
                }
                int id;
                cout << "Digite o Id do guiche que vai atender: ";
                cin >> id;
                
                Guiche* g = buscarGuiche(listaDeGuiches, id);
                if (g == NULL) { 
                    cout << "Guiche nao encontrado!" << endl;
                } else {
                    int senha = dequeue(senhasGeradas);
                    cout << "Guiche " << g->id << " atendendo a senha: " << senha << endl;
                    enqueue(g->senhasAtendidas, senha); 
                }
                break;
            }
            case 4: { 
                int id;
                cout << "Digite o ID do guiche: ";
                cin >> id;
                Guiche* g = buscarGuiche(listaDeGuiches, id);
                if (g == NULL) { 
                    cout << "Guiche nao encontrado!" << endl;
                } else {
                    listarAtendidasPorGuiche(g);
                }
                break;
            }
            case 0: { 
                if (!isEmpty(senhasGeradas)) {
                    cout << "Ainda existem senhas que nao tiveram atendimento. Nao e possivel sair." << endl;
                    opcao = -1; 
                }
                break;
            }
            default:
                cout << "Opcao invalida." << endl;
        } 

    } while(opcao != 0);
		cout << "\nEncerrado com sucesso." << endl;
 		 cout << "Total de senhas atendidas: " << totalGeralAtendidas(listaDeGuiches) << endl;

    return 0;
}
