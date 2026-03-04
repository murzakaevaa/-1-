#include "numbers.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// FIX_ME: Имя функции должно быть в lower_case_with_underscores 
// double Count(int N, int K) {
double count_numbers_with_many_zeros(int length, int base) {
  // dp[i][j] — количество чисел длины i, заканчивающихся на j подряд идущих нулей
  // dp[i][4] — количество чисел, где уже было 4+ подряд идущих нулей
  // FIX_ME: Имена переменных должны быть в snake_case 
  // vector<vector<long long>> dp(N + 1, vector<long long>(5, 0));
  std::vector<std::vector<long long>> dp(
    length + 1, std::vector<long long>(5, 0));

    
  dp[1][0] = base - 1;  // Любая цифра кроме нуля
  dp[1][1] = 1;         // Только ноль

    
  for (int i = 2; i <= length; ++i) {
    for (int j = 0; j < 4; ++j) {
      dp[i][0] += dp[i - 1][j] * (base - 1);
    }

    // Увеличиваем счетчик нулей в конце числа
    dp[i][1] += dp[i - 1][0];
    dp[i][2] += dp[i - 1][1];
    dp[i][3] += dp[i - 1][2];

    // Числа, где появилось 4+ нулей подряд
    dp[i][4] += dp[i - 1][3];     // Добавили ноль к трем нулям
    dp[i][4] += dp[i - 1][4] * base;  // К уже плохим числам можно добавить любую цифру
  }

  // FIX_ME: Имена переменных должны быть в snake_case 
  // double count = dp[N][4];
  double result_count = dp[length][4];

  // FIX_ME: Исправить опечатку "болше" на "более", использовать '\n' вместо endl
  // cout <<"Количество чисел, содержащих болше 3 нулей подряд: "<< count << endl;
  std::cout << "Количество чисел, содержащих более 3 нулей подряд: "
    << result_count << "\n";

  return result_count;
}

// FIX_ME: Имя функции должно быть в lower_case_with_underscores 
// void HomeDyn16() {
void solve_task() {
  int length = 0;
  int base = 0;

  std::cout << "Система счисления: ";
  std::cin >> base;
  std::cout << "Количество разрядов: ";
  std::cin >> length;

  // FIX_ME: Добавить проверку условия N + K < 26
  if (base < 2 || base > 10 || length <= 1 || length >= 20 ||
    length + base >= 26) {
      std::cout << "Ошибка: должны выполняться условия 2 ≤ K ≤ 10, "
      << "1 < N < 20, N + K < 26\n";
      return;
  }

  // FIX_ME: Имена переменных должны быть в snake_case 
  // double all = pow(K, N);
  double total_numbers = std::pow(static_cast<double>(base),
    static_cast<double>(length));

  // FIX_ME: Использовать '\n' вместо endl
  // cout<<"Общее количество: "<<all<<endl;
  std::cout << "Общее количество: " << total_numbers << "\n";

  // FIX_ME: Имена переменных должны быть в snake_case
  // double result = Count(N, K) / all;
  double result = count_numbers_with_many_zeros(length, base) / total_numbers;

  // FIX_ME: Использовать '\n' вместо endl
  // cout << result << endl;
  std::cout << result << "\n";
}