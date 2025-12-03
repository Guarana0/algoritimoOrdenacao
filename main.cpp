#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include "Ordenacao.hpp"

struct Resultados {
    int trocas = 0;
    int comparacoes = 0;
    int tempoMs = 0;
};

// Gerador de vetores
std::vector<int> gerarVetor(int n, int tipo, int sementeExtra) {
    std::vector<int> v(n);
    std::mt19937 gen(sementeExtra);

    // Caso Aleatório (Tipo 2)
    if (tipo == 2) {
        std::uniform_int_distribution<> dis(0, n * 2);
        for (int i = 0; i < n; i++) v[i] = dis(gen);
        return v;
    }

    // Base sequencial
    for (int i = 0; i < n; i++) v[i] = i;

    // Modificações
    if (tipo == 1) { // Inverso
        std::reverse(v.begin(), v.end());
    }
    else if (tipo == 3) { // Quase Ordenado
        std::uniform_int_distribution<> dis(0, n - 1);
        int qtdTrocas = (int)(n * 0.10);
        for (int i = 0; i < qtdTrocas; i++) {
            //serve para respeitar o intervalo de geracao de valores
            std::swap(v[dis(gen)], v[dis(gen)]);
        }
    }
    return v;
}

// Função genérica de teste
template <typename Func>
void rodarAlgoritmo(Func algoritmo, const std::vector<int>& vetorOriginal, Resultados& acumulador) {
    std::vector<int> copia = vetorOriginal;

    // 1. Zera os contadores globais
    trocas = 0;
    comparacoes = 0;

    auto inicio = std::chrono::high_resolution_clock::now();

    // 2. Executa o algoritmo
    algoritmo(copia);

    auto fim = std::chrono::high_resolution_clock::now();

    // 3. Soma no acumulador convertendo para int
    acumulador.tempoMs += (int)std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio).count();
    acumulador.trocas += trocas;
    acumulador.comparacoes += comparacoes;
}

int main() {
    std::vector<int> tamanhos;
    tamanhos.push_back(100);
    tamanhos.push_back(1000);
    tamanhos.push_back(10000);
    tamanhos.push_back(100000);

    std::vector<std::string> nomesCenarios;
    nomesCenarios.push_back("Ordenado"); // tipo 1
    nomesCenarios.push_back("Inverso"); // tipo 2
    nomesCenarios.push_back("Aleatorio"); // tipo 3
    nomesCenarios.push_back("QuaseOrd"); // tipo 4

    std::cout << "TAMANHO | CENARIO     | ALGORITMO      | TEMPO(ms) | TROCAS       | COMPARACOES" << std::endl;
    std::cout << "----------------------------------------------------------------------------------" << std::endl;

    for (size_t i = 0; i < tamanhos.size(); ++i) {
        int n = tamanhos[i];

        for (int tipo = 0; tipo < 4; tipo++) {

            int numVetores = (tipo >= 2) ? 10 : 1;
            int numRepeticoes = (tipo >= 2) ? 1 : 10;

            Resultados resBubble, resInsert, resSelect, resQuickL, resQuickH, resBucket;

            for (int v = 0; v < numVetores; v++) {
                std::vector<int> vetorBase = gerarVetor(n, tipo, v + 42);

                for (int r = 0; r < numRepeticoes; r++) {
                    rodarAlgoritmo(Ordenacao::bubbleSort, vetorBase, resBubble);
                    rodarAlgoritmo(Ordenacao::insertionSort, vetorBase, resInsert);
                    rodarAlgoritmo(Ordenacao::selectionSort, vetorBase, resSelect);
                    rodarAlgoritmo(Ordenacao::quickSortLomuto, vetorBase, resQuickL);
                    rodarAlgoritmo(Ordenacao::quickSortHoare, vetorBase, resQuickH);
                    rodarAlgoritmo(Ordenacao::bucketSort, vetorBase, resBucket);
                }
            }

            // Divisor para média (int)
            int totalExecucoes = numVetores * numRepeticoes;

            // setw define largura do campo
            // ja imprime com a media
            auto imprimir = [&](std::string nome, Resultados r) {
                 std::cout << std::left << std::setw(8) << n
                          << " | " << std::setw(11) << nomesCenarios[tipo]
                          << " | " << std::setw(14) << nome
                          << " | " << std::setw(9) << (r.tempoMs / totalExecucoes)
                          << " | " << std::setw(12) << (r.trocas / totalExecucoes)
                          << " | " << (r.comparacoes / totalExecucoes) << std::endl;
            };

            imprimir("Bubble", resBubble);
            imprimir("Insertion", resInsert);
            imprimir("Selection", resSelect);
            imprimir("QuickLomuto", resQuickL);
            imprimir("QuickHoare", resQuickH);
            imprimir("Bucket", resBucket);

            std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
        }
    }

    return 0;
}