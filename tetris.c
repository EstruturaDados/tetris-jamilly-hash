#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.

#define MAX 5  // tamanho máximo da fila (fixo e igual ao inicial)

// Struct da peça 
typedef struct {
    char nome;  // tipo da peça: 'I', 'O', 'T', 'L'
    int id;     // identificador único
} Peca;

//  Estrutura da fila
typedef struct {
    Peca itens[MAX];
    int frente;
    int tras;
    int tamanho;
} Fila;

//  Geração automática de peças 
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Funções da fila 
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

int filaCheia(Fila *f) {
    return f->tamanho == MAX;
}

// Inserir peça no final
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\n❌ A fila já está cheia! Não é possível adicionar nova peça.\n");
        return;
    }

    f->tras = (f->tras + 1) % MAX;
    f->itens[f->tras] = p;
    f->tamanho++;

    printf("✔ Peça [%c %d] inserida.\n", p.nome, p.id);
}

// Remover peça da frente
void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("\n❌ A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX;
    f->tamanho--;

    printf("🧩 Peça jogada: [%c %d]\n", removida.nome, removida.id);
}

// Exibir a fila
void exibirFila(Fila *f) {
    printf("\nFila de peças:\n");

    if (filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }

    int i = f->frente;
    for (int c = 0; c < f->tamanho; c++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

//  Programa principal
int main() {
    Fila fila;
    inicializarFila(&fila);

    srand(time(NULL));
    int contadorID = 0;
    int opcao;

    // Inicializar a fila com 5 peças automáticas
    printf("Inicializando fila com 5 peças...\n");
    for (int i = 0; i < MAX; i++) {
        enqueue(&fila, gerarPeca(contadorID++));
    }

    exibirFila(&fila);

    // Menu principal
    do {
        printf("\n========== MENU ==========\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                exibirFila(&fila);
                break;

            case 2:
                enqueue(&fila, gerarPeca(contadorID++));
                exibirFila(&fila);
                break;

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    


    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


   
return 0;
}
