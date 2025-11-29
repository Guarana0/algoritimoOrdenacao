#ifndef ORDENACAO_HPP
#define ORDENACAO_HPP

#include <vector>
#include <functional>
#include <string>

class Ordenacao {
public:
    // Métodos estáticos de ordenação
    static void bucketSort(std::vector<int>& vetor, int valorMaximo);
    static void bubbleSort(std::vector<int>& vetor);
    static void selectionSort(std::vector<int>& vetor);
    static void insertionSort(std::vector<int>& vetor);
    static void mergeSort(std::vector<int>& vetor);
    static void quickSort(std::vector<int>& vetor);

    static void medirTempo(const std::string& nomeAlgoritmo, std::function<void(std::vector<int>&)> func, std::vector<int> dados);

private:
    static void mergeSortHelper(std::vector<int>& vetor, int inicio, int fim);
    static void merge(std::vector<int>& vetor, int inicio, int meio, int fim);
    static void quickSortHelper(std::vector<int>& vetor, int inicio, int fim);
    static int partition(std::vector<int>& vetor, int inicio, int fim);
};

#endif // ORDENACAO_HPP
