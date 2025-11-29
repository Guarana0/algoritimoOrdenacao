#include "ordenacao.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

// Variáveis globais para contagem (opcional, mas mantive conforme seu código)
int comparacoes = 0;
int trocas = 0;

void Ordenacao::bucketSort(std::vector<int>& vetor, int valorMaximo) {
    int tamanho = vetor.size();
    if (tamanho == 0) return;

    int quantidadeBuckets = tamanho;
    std::vector<std::vector<int>> buckets(quantidadeBuckets);

    for (int numero : vetor) {
        long long calculoIndice = (long long)numero * quantidadeBuckets;
        int indice = (int)(calculoIndice / (valorMaximo + 1));

        if (indice >= quantidadeBuckets) indice = quantidadeBuckets - 1;

        buckets[indice].push_back(numero);
    }

    for (int i = 0; i < quantidadeBuckets; i++) {
        if (!buckets[i].empty()) {
           std::sort(buckets[i].begin(), buckets[i].end());
        }
    }

    int posicao = 0;
    for (int i = 0; i < quantidadeBuckets; i++) {
        for (int numero : buckets[i]) {
            vetor[posicao++] = numero;
        }
    }
}

void Ordenacao::bubbleSort(std::vector<int>& vetor) {
    int n = vetor.size();
    bool houveTroca;

    // Loop externo: controla as passadas pelo vetor
    for (int i = 0; i < n - 1; i++) {
        houveTroca = false;
        comparacoes++;
        for (int j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                // Se o elemento atual for maior que o próximo, troca
                std::swap(vetor[j], vetor[j + 1]);
                houveTroca = true;
                trocas++;
            }
        }
        if (!houveTroca) {
            break;
        }
    }
}

void Ordenacao::selectionSort(std::vector<int>& vetor) {
    int n = vetor.size();
    for (int i = 0; i < n - 1; i++) {
        int indiceMenor = i;
        comparacoes++;

        for (int j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[indiceMenor]) {
                indiceMenor = j; // Atualizamos o índice do menor encontrado
            }
        }

        if (indiceMenor != i) {
            std::swap(vetor[i], vetor[indiceMenor]);
            trocas++;
        }
    }
}