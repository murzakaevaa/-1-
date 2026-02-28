// Археолог нашел N артефактов. Известны веса (ci) и налоговое бремя (di) находок.
// Нужно выбрать такое подмножество находок, чтобы их суммарный вес превысил Z кг,
// а их общее налоговое бремя оказалось минимальным. Известно, что решение единственно.
// Укажите порядковые номера вещей, которые нужно взять. Исходные данные находятся
// в текстовом файле, в первой строке указаны N и Z, во второй строке значения весов
// (в кг), в третьей - величина налога по каждой находке. Вывести так же суммарный вес
// и общую ценность результата.

#include <iostream>
#include <fstream>
#include <vector>
#include "artifacts.h"

int main() {

    std::setlocale(LC_ALL, "russian");

    // FIX_ME: Имена переменных должны быть в snake_case
    // ifstream input("t.txt");
    std::ifstream input_file("t.txt");

    // FIX_ME: Добавлена проверка открытия файла и возврат кода ошибки
    if (!input_file.is_open()) {
        std::cout << "Ошибка открытия файла!\n";
        return 1;
    }

    // FIX_ME: Имена переменных должны быть в snake_case
    // int N, Z;
    int artifacts_count = 0;
    int required_weight = 0;
    input_file >> artifacts_count >> required_weight;

    // FIX_ME: Имена переменных должны быть в snake_case
    // vector<int> weights;
    // vector<int> taxes;
    std::vector<int> weights;
    std::vector<int> taxes;

    // Считываем веса предметов
    for (int i = 0; i < artifacts_count; ++i) {
        int value = 0;
        input_file >> value;
        weights.push_back(value);
    }

    // Считываем налоговое бремя предметов
    for (int i = 0; i < artifacts_count; ++i) {
        int value = 0;
        input_file >> value;
        taxes.push_back(value);
    }

    input_file.close();


    find_optimal_artifacts(required_weight, weights, taxes);

    // FIX_ME: Добавить явный return 0
    return 0;
}