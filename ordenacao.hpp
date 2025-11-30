#ifndef ORDENACAO_HPP
#define ORDENACAO_HPP

#include <vector>
#include <string>
#include <iostream>
#include <chrono>

class Ordenacao {
private:
    // Métodos auxiliares privados com contadores
    static int particaoLomuto(std::vector<int>& v, int inicio, int fim, long long& trocas, long long& comparacoes);
    static int particaoHoare(std::vector<int>& v, int inicio, int fim, long long& trocas, long long& comparacoes);
    static void _quickSortLomuto(std::vector<int>& v, int inicio, int fim, long long& trocas, long long& comparacoes);
    static void _quickSortHoare(std::vector<int>& v, int inicio, int fim, long long& trocas, long long& comparacoes);

public:
    // Algoritmos O(n^2) - Agora recebem contadores
    static void bubbleSort(std::vector<int>& v, long long& trocas, long long& comparacoes);
    static void insertionSort(std::vector<int>& v, long long& trocas, long long& comparacoes);
    static void selectionSort(std::vector<int>& v, long long& trocas, long long& comparacoes);

    // Algoritmos O(n log n)
    static void quickSortLomuto(std::vector<int>& v, long long& trocas, long long& comparacoes);
    static void quickSortHoare(std::vector<int>& v, long long& trocas, long long& comparacoes);

    // Algoritmo Extra
    static void bucketSort(std::vector<int>& v, long long& trocas, long long& comparacoes);
};

#endif
