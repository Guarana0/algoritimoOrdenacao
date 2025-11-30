#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include "Ordenacao.hpp"

// Struct para acumular médias
struct Resultados {
    long long trocas = 0;
    long long comparacoes = 0;
    long long tempoMs = 0;
};

// Gerador de vetores
// Tipo: 0=Ordenado, 1=Inverso, 2=Aleatorio, 3=Quase Ordenado
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
        int qtdTrocas = n * 0.10;
        for (int i = 0; i < qtdTrocas; i++) {
            std::swap(v[dis(gen)], v[dis(gen)]);
        }
    }
    return v;
}

// Função genérica de teste
template <typename Func>
void rodarAlgoritmo(Func algoritmo, const std::vector<int>& vetorOriginal, Resultados& acumulador) {
    std::vector<int> copia = vetorOriginal;

    long long t = 0;
    long long c = 0;

    auto inicio = std::chrono::high_resolution_clock::now();

    algoritmo(copia, t, c);

    auto fim = std::chrono::high_resolution_clock::now();

    acumulador.tempoMs += std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio).count();
    acumulador.trocas += t;
    acumulador.comparacoes += c;
}

int main() {
    std::vector<int> tamanhos;
    tamanhos.push_back(100);
    tamanhos.push_back(1000);
    tamanhos.push_back(10000);
    tamanhos.push_back(100000);

    std::vector<std::string> nomesCenarios;
    nomesCenarios.push_back("Ordenado");
    nomesCenarios.push_back("Inverso");
    nomesCenarios.push_back("Aleatorio");
    nomesCenarios.push_back("QuaseOrd");

    std::cout << "TAMANHO | CENARIO     | ALGORITMO      | TEMPO(ms) | TROCAS       | COMPARACOES" << std::endl;
    std::cout << "----------------------------------------------------------------------------------" << std::endl;

    for (size_t i = 0; i < tamanhos.size(); ++i) {
        int n = tamanhos[i];

        for (int tipo = 0; tipo < 4; tipo++) {

            // Definição de repetições conforme regra do trabalho
            int numVetores = (tipo >= 2) ? 10 : 1;
            int numRepeticoes = (tipo >= 2) ? 1 : 10;

            Resultados resBubble, resInsert, resSelect, resQuickL, resQuickH, resBucket;

            for (int v = 0; v < numVetores; v++) {
                std::vector<int> vetorBase = gerarVetor(n, tipo, v + 42);

                for (int r = 0; r < numRepeticoes; r++) {

                    // Executa todos os algoritmos sem travas
                    rodarAlgoritmo(Ordenacao::bubbleSort, vetorBase, resBubble);
                    rodarAlgoritmo(Ordenacao::insertionSort, vetorBase, resInsert);
                    rodarAlgoritmo(Ordenacao::selectionSort, vetorBase, resSelect);

                    rodarAlgoritmo(Ordenacao::quickSortLomuto, vetorBase, resQuickL);
                    rodarAlgoritmo(Ordenacao::quickSortHoare, vetorBase, resQuickH);
                    rodarAlgoritmo(Ordenacao::bucketSort, vetorBase, resBucket);
                }
            }

            // Calcula divisores para média
            // Cast para long long para evitar problemas de divisão se for zero (embora não deva ser)
            long long totalExecucoes = numVetores * numRepeticoes;

            // Função lambda para impressão
            // Nota: Se seu compilador reclamar de lambda, avise. Mas C++11 suporta.
            // Para garantir compatibilidade, definimos as variáveis antes.

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
