#include "artifacts.h"
#include <iostream>
#include <vector>
#include <climits>

// Функция для решения задачи о рюкзаке

// FIX_ME: Имя функции должно быть в lower_case_with_underscores
// void knapSack(int W, vector<int>& wt, vector<int>& val) {
void find_optimal_artifacts(int min_weight,
    const std::vector<int>& weights,
    const std::vector<int>& taxes) {
    // Количество предметов
    // FIX_ME: Имена переменных должны быть в snake_case
    // int n = wt.size();
    int item_count = weights.size();

    // Максимально возможный вес всех предметов
    // FIX_ME: Имена переменных должны быть в snake_case
    // int maxWeight = 0;
    int max_total_weight = 0;

    // Считаем общий вес всех предметов
    for (int weight : weights) {
        max_total_weight += weight;
    }

    // Вектор min_tax, где min_tax[w] хранит минимальное налоговое бремя для веса w
    // FIX_ME: Имена переменных должны быть в snake_case
    // vector<int> dp(maxWeight + 1, INT_MAX);
    std::vector<int> min_tax(max_total_weight + 1, INT_MAX);


    // Нулевой вес имеет нулевое налоговое бремя
    min_tax[0] = 0;

    // Матрица is_selected, где is_selected[w][i] = true, если предмет i включен в набор для веса w
    // FIX_ME: Имена переменных должны быть в snake_case
    // vector<vector<bool>> selected(maxWeight + 1, vector<bool>(n, false));
    std::vector<std::vector<bool>> is_selected(
        max_total_weight + 1, std::vector<bool>(item_count, false));


    // Заполняем min_tax и is_selected
    for (int i = 0; i < item_count; ++i) {  // Перебираем все предметы

        for (int w = max_total_weight; w >= weights[i]; --w) {  // Перебираем все возможные веса
            if (min_tax[w - weights[i]] != INT_MAX &&
                min_tax[w - weights[i]] + taxes[i] < min_tax[w]) {
                // Обновляем минимальное налоговое бремя
                min_tax[w] = min_tax[w - weights[i]] + taxes[i];
                // Копируем набор предметов для веса (w - weights[i])
                is_selected[w] = is_selected[w - weights[i]];
                // Добавляем текущий предмет в набор
                is_selected[w][i] = true;
            }
        }
    }

    // Находим минимальное налоговое бремя для весов > min_weight
    // FIX_ME: Имена переменных должны быть в snake_case
    // int minVal = INT_MAX;
    // int bestWeight = 0;
    // vector<bool> bestSelection(n, false);
    int best_min_tax = INT_MAX;
    int best_weight = 0;  // Вес с минимальным налоговым бременем
    std::vector<bool> best_selection(item_count, false);

    // FIX_ME: Неправильное условие - суммарный вес должен быть СТРОГО БОЛЬШЕ Z
    // for (int w = W; w <= maxWeight; w++)
    for (int w = min_weight + 1; w <= max_total_weight; ++w) {
        if (min_tax[w] < best_min_tax) {
            best_min_tax = min_tax[w];
            best_weight = w;
            best_selection = is_selected[w];
        }
    }

    // Вывод результата

    if (best_min_tax == INT_MAX) {
        // FIX_ME: Использовать '\n' вместо endl
        // cout << "Невозможно достичь минимального веса " << W << endl;
        std::cout << "Невозможно набрать вес больше " << min_weight << " кг\n";
    }
    else {
        std::cout << "Порядковые номера выбранных предметов: ";
        for (int i = 0; i < item_count; ++i) {
            if (best_selection[i]) {
                std::cout << i + 1 << " ";
            }
        }
        // FIX_ME: Использовать '\n' вместо endl
        // cout << endl;
        std::cout << "\n";

        // FIX_ME: Использовать '\n' вместо endl
        // cout << "Общий вес: " << bestWeight << " кг" << endl;
        // cout << "Итоговое налогообложение: " << minVal << endl;
        std::cout << "Общий вес: " << best_weight << " кг\n";
        std::cout << "Итоговое налогообложение: " << best_min_tax << "\n";
    }
}