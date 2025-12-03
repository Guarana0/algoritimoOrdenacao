#ifndef ORDENACAO_HPP
#define ORDENACAO_HPP

#include <vector>
#include <string>
#include <iostream>
#include <chrono>

// Declaração das variáveis globais
extern int trocas;
extern int comparacoes;

class Ordenacao {
private:
    // Métodos auxiliares privados (sem contadores nos parâmetros)
    static int particaoLomuto(std::vector<int>& v, int inicio, int fim);
    static int particaoHoare(std::vector<int>& v, int inicio, int fim);
    static void _quickSortLomuto(std::vector<int>& v, int inicio, int fim);
    static void _quickSortHoare(std::vector<int>& v, int inicio, int fim);

public:
    // Algoritmos O(n^2)
    static void bubbleSort(std::vector<int>& v);
    static void insertionSort(std::vector<int>& v);
    static void selectionSort(std::vector<int>& v);

    // Algoritmos O(n log n)
    static void quickSortLomuto(std::vector<int>& v);
    static void quickSortHoare(std::vector<int>& v);

    // Algoritmo Extra
    static void bucketSort(std::vector<int>& v);
};

#endif