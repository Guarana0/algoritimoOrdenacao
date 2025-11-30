#include "Ordenacao.hpp"
#include <algorithm>
#include <vector>

// ==========================================================
// MÉTODOS PRIVADOS (QuickSort e Auxiliares)
// ==========================================================

int Ordenacao::particaoLomuto(std::vector<int>& v, int inicio, int fim, long long& trocas, long long& comparacoes) {
    int pivo = v[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++) {
        comparacoes++; // Comparação do if abaixo
        if (v[j] <= pivo) {
            i++;
            std::swap(v[i], v[j]);
            trocas++;
        }
    }
    std::swap(v[i + 1], v[fim]);
    trocas++;
    return (i + 1);
}

int Ordenacao::particaoHoare(std::vector<int>& v, int inicio, int fim, long long& trocas, long long& comparacoes) {
    int pivo = v[inicio];
    int i = inicio - 1;
    int j = fim + 1;

    while (true) {
        // Encontra elemento à esquerda maior que pivô
        do {
            i++;
            comparacoes++;
        } while (v[i] < pivo);

        // Encontra elemento à direita menor que pivô
        do {
            j--;
            comparacoes++;
        } while (v[j] > pivo);

        if (i >= j) return j;

        std::swap(v[i], v[j]);
        trocas++;
    }
}

void Ordenacao::_quickSortLomuto(std::vector<int>& v, int inicio, int fim, long long& trocas, long long& comparacoes) {
    if (inicio < fim) {
        int p = particaoLomuto(v, inicio, fim, trocas, comparacoes);
        _quickSortLomuto(v, inicio, p - 1, trocas, comparacoes);
        _quickSortLomuto(v, p + 1, fim, trocas, comparacoes);
    }
}

void Ordenacao::_quickSortHoare(std::vector<int>& v, int inicio, int fim, long long& trocas, long long& comparacoes) {
    if (inicio < fim) {
        int p = particaoHoare(v, inicio, fim, trocas, comparacoes);
        _quickSortHoare(v, inicio, p, trocas, comparacoes);
        _quickSortHoare(v, p + 1, fim, trocas, comparacoes);
    }
}

// ==========================================================
// MÉTODOS PÚBLICOS
// ==========================================================

void Ordenacao::bubbleSort(std::vector<int>& v, long long& trocas, long long& comparacoes) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                trocas++;
                trocou = true;
            }
        }
        if (!trocou) break;
    }
}

void Ordenacao::insertionSort(std::vector<int>& v, long long& trocas, long long& comparacoes) {
    int n = v.size();
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;

        // A comparação v[j] > chave acontece dentro do while
        // Se j >= 0 for falso, não compara v[j].
        // Lógica simplificada de contagem:
        while (j >= 0) {
            comparacoes++;
            if (v[j] > chave) {
                v[j + 1] = v[j];
                trocas++; // Deslocamento conta como troca neste contexto
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
}

void Ordenacao::selectionSort(std::vector<int>& v, long long& trocas, long long& comparacoes) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j] < v[min_idx])
                min_idx = j;
        }
        if (min_idx != i) {
            std::swap(v[i], v[min_idx]);
            trocas++;
        }
    }
}

void Ordenacao::quickSortLomuto(std::vector<int>& v, long long& trocas, long long& comparacoes) {
    if (!v.empty()) _quickSortLomuto(v, 0, v.size() - 1, trocas, comparacoes);
}

void Ordenacao::quickSortHoare(std::vector<int>& v, long long& trocas, long long& comparacoes) {
    if (!v.empty()) _quickSortHoare(v, 0, v.size() - 1, trocas, comparacoes);
}

void Ordenacao::bucketSort(std::vector<int>& v, long long& trocas, long long& comparacoes) {
    if (v.empty()) return;

    // Achar min e max (custo linear, não contaremos como comp de ordenação para simplificar,
    // ou podemos contar aqui se o professor for rigoroso. Geralmente ignora-se pré-processamento).
    int maxVal = v[0];
    int minVal = v[0];
    for(size_t i=1; i<v.size(); i++) {
        if(v[i] > maxVal) maxVal = v[i];
        if(v[i] < minVal) minVal = v[i];
    }

    if (maxVal == minVal) return;

    int n = v.size();
    std::vector<std::vector<int>> baldes(n);
    double intervalo = (double)(maxVal - minVal + 1) / n;

    for (int num : v) {
        int indice = (int)((num - minVal) / intervalo);
        if (indice >= n) indice = n - 1;
        baldes[indice].push_back(num);
    }

    int index = 0;
    for (auto& balde : baldes) {
        if (!balde.empty()) {
            // USAR O INSERTION SORT DA CLASSE PARA CONTAR AS MÉTRICAS DO BALDE
            insertionSort(balde, trocas, comparacoes);

            for (int num : balde) {
                v[index++] = num;
                // Movimentação de volta ao vetor original não costuma contar como "troca" de comparação,
                // mas sim cópia. Vamos manter simples.
            }
        }
    }
}
