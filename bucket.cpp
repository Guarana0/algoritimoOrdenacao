#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> // ADICIONADO: Necessário para usar sort()

using namespace std;

void bucketSort(vector<int>& vetor, int valorMaximo) {
    int tamanho = vetor.size();
    if (tamanho == 0) return;

    // A quantidade de buckets geralmente deve equilibrar memória vs velocidade
    int quantidadeBuckets = tamanho;
    vector<vector<int>> buckets(quantidadeBuckets);

    for (int numero : vetor) {
        // CORREÇÃO: Cast para long long evita overflow na multiplicação
        long long calculoIndice = (long long)numero * quantidadeBuckets;
        int indice = (int)(calculoIndice / (valorMaximo + 1));

        // Segurança extra para garantir que o índice não saia dos limites
        if (indice >= quantidadeBuckets) indice = quantidadeBuckets - 1;

        buckets[indice].push_back(numero);
    }

    // Ordena cada bucket individualmente
    for (int i = 0; i < quantidadeBuckets; i++) {
        if (!buckets[i].empty()) {
           sort(buckets[i].begin(), buckets[i].end());
        }
    }

    // Remonta o vetor
    int posicao = 0;
    for (int i = 0; i < quantidadeBuckets; i++) {
        for (int numero : buckets[i]) {
            vetor[posicao++] = numero;
        }
    }
}

int main() {
    srand(time(NULL));

    int quantidade = 20;
    int valorMaximo = 100;

    vector<int> vetor(quantidade);

    for (int i = 0; i < quantidade; i++) {
        vetor[i] = rand() % (valorMaximo + 1);
    }

    cout << "Vetor original:\n";
    for (int valor : vetor) cout << valor << " ";
    cout << "\n\n";

    bucketSort(vetor, valorMaximo);

    cout << "Vetor ordenado:\n";
    for (int valor : vetor) cout << valor << " ";
    cout << "\n";

    return 0;
}
