#include "king.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// Функция для нахождения максимальной суммы и пути
// FIX_ME: Имя функции должно быть в lower_case_with_underscores
// void findPath(vector<vector<int>>& board, int N, ofstream& output) {
void find_max_path(const std::vector<std::vector<int>>& board,
  int board_size,
  std::ofstream& output_file) {
  // FIX_ME: Имена переменных должны быть в snake_case 
  // vector<vector<int>> dp(N, vector<int>(N, 0));
  std::vector<std::vector<int>> max_sum(
    board_size, std::vector<int>(board_size, 0));

  // Начальная позиция (правый нижний угол)
  max_sum[board_size - 1][board_size - 1] = board[board_size - 1][board_size - 1];

  // Заполнение таблицы максимальных сумм
  for (int i = board_size - 1; i >= 0; --i) {
    for (int j = board_size - 1; j >= 0; --j) {
      if (i < board_size - 1) {
        max_sum[i][j] = std::max(
          max_sum[i][j], max_sum[i + 1][j] + board[i][j]);
        }
      if (j < board_size - 1) {
        max_sum[i][j] = std::max(
          max_sum[i][j], max_sum[i][j + 1] + board[i][j]);
      }
    }
  }

  // Максимальная сумма монет
  // FIX_ME: Имена переменных должны быть в snake_case 
  // int maxSum = dp[0][0];
  int max_sum_value = max_sum[0][0];

  // FIX_ME: Использовать '\n' вместо endl
  // output << maxSum << endl;
  output_file << max_sum_value << "\n";

  // Восстановление пути
  // FIX_ME: Имена переменных должны быть в snake_case 
  // vector<char> path;
  // int x = 0, y = 0;
  std::vector<char> path;

  // FIX_ME: начало движения начинается с правого нижнего угла, а не с левого верхнего
  // int row = 0;
  // int col = 0;
  int row = board_size - 1;
  int col = board_size - 1;

  // FIX_ME: Условие цикла - пока не дошли до левого верхнего угла
  // while (x < N - 1 || y < N - 1) {
  while (row > 0 || col > 0) {
    // FIX_ME: Проверка достижения верхней границы
    // if (x == N - 1) {
    if (row == 0) {
      path.push_back('L');
      col--;
    }
    // FIX_ME: Проверка достижения левой границы
    // else if (y == N - 1) {
    else if (col == 0) {
    path.push_back('U');
    row--;
    }
    // FIX_ME: Сравнение путей вверх и влево
    // else if (dp[x + 1][y] > dp[x][y + 1]) {
    else if (max_sum[row - 1][col] > max_sum[row][col - 1]) {
      path.push_back('U');
      row--;
    }
    else {
      path.push_back('L');
      col--;
    }
 }

 // Вывод пути, так как идем с конца
 for (char move : path) {
   // FIX_ME: Использовать '\n' в конце, но не в цикле
   output_file << move;
 }
 // FIX_ME: Использовать '\n' вместо endl
 // output << endl;
 output_file << "\n";
}