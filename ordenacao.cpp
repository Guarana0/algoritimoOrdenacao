#include "Ordenacao.hpp"
#include <algorithm>
#include <vector>

// variáveis globais de contagem
int trocas = 0;
int comparacoes = 0;

int Ordenacao::particaoLomuto(std::vector<int>& v, int inicio, int fim) {
    int pivo = v[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++) {
        comparacoes++;
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

int Ordenacao::particaoHoare(std::vector<int>& v, int inicio, int fim) {
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

void Ordenacao::_quickSortLomuto(std::vector<int>& v, int inicio, int fim) {
    if (inicio < fim) {
        int p = particaoLomuto(v, inicio, fim);
        _quickSortLomuto(v, inicio, p - 1);
        _quickSortLomuto(v, p + 1, fim);
    }
}

void Ordenacao::_quickSortHoare(std::vector<int>& v, int inicio, int fim) {
    if (inicio < fim) {
        int p = particaoHoare(v, inicio, fim);
        _quickSortHoare(v, inicio, p);
        _quickSortHoare(v, p + 1, fim);
    }
}

void Ordenacao::bubbleSort(std::vector<int>& v) {
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

void Ordenacao::insertionSort(std::vector<int>& v) {
    int n = v.size();
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;

        // Se j >= 0 for falso, não compara v[j].
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

void Ordenacao::selectionSort(std::vector<int>& v) {
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

void Ordenacao::quickSortLomuto(std::vector<int>& v) {
    if (!v.empty()) _quickSortLomuto(v, 0, v.size() - 1);
}

void Ordenacao::quickSortHoare(std::vector<int>& v) {
    if (!v.empty()) _quickSortHoare(v, 0, v.size() - 1);
}

void Ordenacao::bucketSort(std::vector<int>& v) {
    if (v.empty()) return;
    
    // Encontrar max e min
    int maxVal = v[0];
    int minVal = v[0];
    for(size_t i=1; i<v.size(); i++) {
        // Nota: para ser purista, aqui também poderiam contar comparações, 
        // mas em Bucket Sort geralmente focamos na ordenação interna.
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
            insertionSort(balde);

            for (int num : balde) {
                v[index++] = num;
            }
        }
    }
}