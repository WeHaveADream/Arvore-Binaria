#include <stdio.h>
#include <stdlib.h>

struct No {
    int dado;
    struct No* anterior;
    struct No* proximo;
};

struct ListaDuplamenteEncadeada {
    struct No* inicio;
    struct No* fim;
    int tamanho;
};

struct No* criarNo(int dado) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = dado;
    novoNo->anterior = NULL;
    novoNo->proximo = NULL;
    return novoNo;
}

struct ListaDuplamenteEncadeada* criarLista() {
    struct ListaDuplamenteEncadeada* novaLista = (struct ListaDuplamenteEncadeada*)malloc(sizeof(struct ListaDuplamenteEncadeada));
    novaLista->inicio = NULL;
    novaLista->fim = NULL;
    novaLista->tamanho = 0;
    return novaLista;
}

int estaVazia(struct ListaDuplamenteEncadeada* lista) {
    return lista->tamanho == 0;
}

int estaRepetido(struct ListaDuplamenteEncadeada* lista, int dado) {
    struct No* atual = lista->inicio;
    while (atual != NULL) {
        if (atual->dado == dado) {
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

void adicionar(struct ListaDuplamenteEncadeada* lista, int dado) {
    if (estaRepetido(lista, dado)) {
        printf("O elemento já existe na lista!\n");
        return;
    }

    struct No* novoNo = criarNo(dado);
    if (estaVazia(lista)) {
        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else {
        novoNo->anterior = lista->fim;
        lista->fim->proximo = novoNo;
        lista->fim = novoNo;
    }
    lista->tamanho++;

    printf("Elemento %d adicionado com sucesso!\n", dado);
    printf("Lista atualizada: ");
    imprimirLista(lista);
}

void inserir(struct ListaDuplamenteEncadeada* lista, int dado, int posicao) {
    if (posicao < 0 || posicao > lista->tamanho) {
        printf("Posição inválida!\n");
        return;
    }
    if (estaRepetido(lista, dado)) {
        printf("O elemento já existe na lista!\n");
        return;
    }

    struct No* novoNo = criarNo(dado);
    if (estaVazia(lista)) {
        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else if (posicao == 0) {
        novoNo->proximo = lista->inicio;
        lista->inicio->anterior = novoNo;
        lista->inicio = novoNo;
    } else if (posicao == lista->tamanho) {
        novoNo->anterior = lista->fim;
        lista->fim->proximo = novoNo;
        lista->fim = novoNo;
    } else {
        struct No* atual = lista->inicio;
        int contador = 0;
        while (contador < posicao) {
            atual = atual->proximo;
            contador++;
        }
        novoNo->anterior = atual->anterior;
        novoNo->proximo = atual;
        atual->anterior->proximo = novoNo;
        atual->anterior = novoNo;
    }
    lista->tamanho++;

    printf("Elemento %d inserido na posição %d com sucesso!\n", dado, posicao);
    printf("Lista atualizada: ");
    imprimirLista(lista);
}

void removerNaPosicao(struct ListaDuplamenteEncadeada* lista, int posicao) {
    if (estaVazia(lista)) {
        printf("A lista está vazia!\n");
        return;
    }
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posição inválida!\n");
        return;
    }
    if (posicao == 0) {
        struct No* temp = lista->inicio;
        lista->inicio = lista->inicio->proximo;
        if (lista->inicio != NULL) {
            lista->inicio->anterior = NULL;
        }
        free(temp);
    } else if (posicao == lista->tamanho - 1) {
        struct No* temp = lista->fim;
        lista->fim = lista->fim->anterior;
        lista->fim->proximo = NULL;
        free(temp);
    } else {
        struct No* atual = lista->inicio;
        int contador = 0;
        while (contador < posicao) {
            atual = atual->proximo;
            contador++;
        }
        atual->anterior->proximo = atual->proximo;
        atual->proximo->anterior = atual->anterior;
        free(atual);
    }
    lista->tamanho--;

    printf("Elemento na posição %d removido com sucesso!\n", posicao);
    printf("Lista atualizada: ");
    imprimirLista(lista);
}

int contarElementos(struct ListaDuplamenteEncadeada* lista) {
    return lista->tamanho;
}

int contarPares(struct ListaDuplamenteEncadeada* lista) {
    struct No* atual = lista->inicio;
    int count = 0;
    while (atual != NULL) {
        if (atual->dado % 2 == 0) {
            count++;
        }
        atual = atual->proximo;
    }
    return count;
}

int contarImpares(struct ListaDuplamenteEncadeada* lista) {
    struct No* atual = lista->inicio;
    int count = 0;
    while (atual != NULL) {
        if (atual->dado % 2 != 0) {
            count++;
        }
        atual = atual->proximo;
    }
    return count;
}

void unirListas(struct ListaDuplamenteEncadeada* lista1, struct ListaDuplamenteEncadeada* lista2) {
    if (estaVazia(lista2)) {
        return;
    }
    if (estaVazia(lista1)) {
        lista1->inicio = lista2->inicio;
        lista1->fim = lista2->fim;
    } else {
        lista1->fim->proximo = lista2->inicio;
        lista2->inicio->anterior = lista1->fim;
        lista1->fim = lista2->fim;
    }
    lista1->tamanho += lista2->tamanho;
    free(lista2);

    printf("Listas unidas com sucesso!\n");
    printf("Lista atualizada: ");
    imprimirLista(lista1);
}

void imprimirLista(struct ListaDuplamenteEncadeada* lista) {
    struct No* atual = lista->inicio;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

void exibirMenu() {
    printf("\n--- MENU ---\n");
    printf("1. Adicionar elemento\n");
    printf("2. Inserir elemento em uma posição\n");
    printf("3. Remover elemento de uma posição\n");
    printf("4. Contar elementos\n");
    printf("5. Contar números pares\n");
    printf("6. Contar números ímpares\n");
    printf("7. Unir listas\n");
    printf("0. Sair\n");
    printf("-------------\n");
}

int main() {
    struct ListaDuplamenteEncadeada* lista = criarLista();
    int opcao, elemento, posicao;
    do {
        exibirMenu();
        printf("Digite sua opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Encerrando o programa...\n");
                break;
            case 1:
                printf("Digite o elemento a ser adicionado: ");
                scanf("%d", &elemento);
                adicionar(lista, elemento);
                break;
            case 2:
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &elemento);
                printf("Digite a posição de inserção: ");
                scanf("%d", &posicao);
                inserir(lista, elemento, posicao);
                break;
            case 3:
                printf("Digite a posição do elemento a ser removido: ");
                scanf("%d", &posicao);
                removerNaPosicao(lista, posicao);
                break;
            case 4:
                printf("A lista contém %d elementos.\n", contarElementos(lista));
                break;
            case 5:
                printf("A lista contém %d números pares.\n", contarPares(lista));
                break;
            case 6:
                printf("A lista contém %d números ímpares.\n", contarImpares(lista));
                break;
            case 7:
                printf("Criando uma nova lista...\n");
                struct ListaDuplamenteEncadeada* novaLista = criarLista();
                printf("Digite o número de elementos da nova lista: ");
                scanf("%d", &posicao);
                printf("Digite os elementos da nova lista:\n");
                for (int i = 0; i < posicao; i++) {
                    printf("Elemento %d: ", i+1);
                    scanf("%d", &elemento);
                    adicionar(novaLista, elemento);
                }
                unirListas(lista, novaLista);
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
