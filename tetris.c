#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.
typedef struct {
    char nome; 
    int id;    
} Peca;

#define TAMANHO_MAXIMO 5
Peca fila[TAMANHO_MAXIMO];
int frente = -1;
int re = -1;
int contador_id = 0;
void inicializarFila();
int estaVazia();
int estaCheia();
Peca gerarPeca();
void enqueue();
void dequeue();
void visualizarFila();
void exibirMenu();
int main() {
  int opcao;
  srand(time(NULL));
  inicializarFila();

  printf("Capacidade maxima da fila: %d pecas.\n", TAMANHO_MAXIMO);

  visualizarFila();

    // Loop principal do programa
    do {
        exibirMenu();
        printf("Escolha uma acao (0-2): ");
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer de entrada em caso de erro
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1; // Força repetição
        }

        switch (opcao) {
            case 1:
                dequeue(); 
                break;
            case 2:
                enqueue(); 
                break;
            case 0:
                printf("\n👋 Jogo encerrado. Ate a proxima rodada!\n");
                break;
            default:
                printf("\nOpcao invalida\n");
        }

        if (opcao != 0) {
            printf("\n--- Estado Atual ---\n");
            visualizarFila();
            printf("--------------------\n");
        }

    } while (opcao != 0);

    return 0;
}
      int estaVazia() {
    
    return (frente == -1);
}
     int estaCheia() {
    
    return ((re + 1) % TAMANHO_MAXIMO == frente);
} 
     Peca gerarPeca() {
    Peca novaPeca;
    
    char tipos[] = {'I', 'O', 'T', 'L'}; 
    int numTipos = sizeof(tipos) / sizeof(tipos[0]);
        
    int indiceAleatorio = rand() % numTipos;
    novaPeca.nome = tipos[indiceAleatorio];
    
    novaPeca.id = contador_id++;
    
    return novaPeca;
} 
   void inicializarFila() {
    // Inserimos peças até o limite, usando o enqueue modificado para inicialização
    for (int i = 0; i < TAMANHO_MAXIMO; i++) {
        Peca p = gerarPeca();
        
        if (estaVazia()) {
            frente = 0;
            re = 0;
        } else {
            // Avança 're' de forma circular
            re = (re + 1) % TAMANHO_MAXIMO;
        }
        
        fila_pecas[re] = p;
        printf("  [INIT] Peca %c com ID %d adicionada.\n", p.nome, p.id);
    }
}

/**
 * @brief Adiciona uma nova peça ao final da fila (enqueue).
 * Requisito: Inserir nova peça ao final da fila.
 */
void enqueue() {
    if (estaCheia()) {
        printf("❌ Fila CHEIA! Nao e possivel adicionar mais pecas. Maximo de %d.\n", TAMANHO_MAXIMO);
        return;
    }

    Peca novaPeca = gerarPeca();

    if (estaVazia()) {
        // Caso a fila estava vazia, frente e re apontam para a primeira posição
        frente = 0;
        re = 0;
    } else {
        // Caso contrário, avança 're' de forma circular
        re = (re + 1) % TAMANHO_MAXIMO;
    }

    // Insere a peça na posição 're'
    fila_pecas[re] = novaPeca;
    printf("✅ ENQUEUE: Peca %c com ID %d inserida no final da fila.\n", novaPeca.nome, novaPeca.id);
}

/**
 * @brief Remove a peça da frente da fila (dequeue).
 * Requisito: Jogar uma peça (remove a peça da frente da fila).
 */
void dequeue() {
    if (estaVazia()) {
        printf("❌ Fila VAZIA! Nao ha pecas para jogar (dequeue).\n");
        return;
    }

    // A peça a ser jogada/removida está na posição 'frente'
    Peca pecaRemovida = fila_pecas[frente];
    
    printf("🕹️ DEQUEUE: Peca jogada! Tipo %c, ID %d.\n", pecaRemovida.nome, pecaRemovida.id);

    // Verifica se esta é a última peça
    if (frente == re) {
        // Se frente e re são iguais, a fila ficou vazia após a remoção
        frente = -1;
        re = -1;
    } else {
        // Caso contrário, avança 'frente' de forma circular
        frente = (frente + 1) % TAMANHO_MAXIMO;
    }
}

/**
 * @brief Exibe o estado atual da fila, mostrando o tipo e o ID de cada peça.
 * Requisito: Exibir o estado atual da fila após cada ação.
 */
void visualizarFila() {
    if (estaVazia()) {
        printf("Fila de pecas: VAZIA.\n");
        return;
    }

    printf("Fila de Pecas (Frente -> Re):\n");
    
    printf("  "); // Margem para melhor visualização

    // Loop para percorrer a fila circularmente
    int i = frente;
    do {
        // Exibe a informação da peça atual
        printf("[%c %d]", fila_pecas[i].nome, fila_pecas[i].id);
        
        // Se a peça atual não for a última, adiciona um separador visual
        if (i != re) {
            printf(" -> ");
        }
        
        // Move para a próxima posição de forma circular
        i = (i + 1) % TAMANHO_MAXIMO;
        
    } while (i != (re + 1) % TAMANHO_MAXIMO); // Continua até o elemento depois de 're'

    printf("\n");
    printf("Indices: Frente = %d, Re = %d\n", frente, re);
}

/**
 * @brief Exibe o menu de opções para o jogador.
 * Requisito: Usabilidade e clareza.
 */
void exibirMenu() {
    printf("\n=== Opcoes de Acao ===\n");
    printf("1. Jogar peca (Dequeue)\n");
    printf("2. Inserir nova peca (Enqueue)\n");
    printf("0. Sair\n");
    printf("======================\n");

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



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


