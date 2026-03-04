#include "expression.h"
#include <iostream>
#include <string>

// FIX_ME: Добавлена вспомогательная функция для проверки цифры
bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

// FIX_ME: Функция для обработки элемента (цифры или выражения в скобках)
// int element(string str)
int process_element(const std::string& element_str) {
    
  // FIX_ME: Добавлена проверка на пустую строку
  if (element_str.empty()) return 0;

  // FIX_ME: Если строка в скобках, вычисляем содержимое
  // if (str[0] == '(' && str[str.size() - 1] == ')')
  if (element_str[0] == '(' && element_str[element_str.size() - 1] == ')') {
    // FIX_ME: Добавлена проверка, что в скобках не пусто
      if (element_str.size() > 2) {
        return calculate_expression(
          element_str.substr(1, element_str.size() - 2));
      }
       return 0; // Пустые скобки
  }
  return std::stoi(element_str);
}

// FIX_ME: Функция term ПОЛНОСТЬЮ УДАЛЕНА, так как умножение не требуется по заданию
// В старой версии была функция term, которая обрабатывала умножение (*)
// Это противоречило условию задачи, где разрешены только + и -
/*
int term(string str)
{
    int i = str.size() - 1;
    int level = 0;
    int pos = -1;
    while (i >= 0)  // ЦИКЛ - запрещено по заданию!
    {
        if (str[i] == ')')
            level++;
        if (str[i] == '(')
            level--;
        if (level == 0 && str[i] == '*')  // УМНОЖЕНИЕ - не разрешено!
        {
            pos = i;
            break;
        }
        i--;
    }
    if (pos == -1)
        return element(str);
    return term(str.substr(0, pos)) * element(str.substr(pos + 1));  // УМНОЖЕНИЕ
}
*/

// FIX_ME: Имена функций должны быть в lower_case_with_underscores
// int calc(string str)
int calculate_expression(const std::string& expr_str) {
  // FIX_ME: Добавлен базовый случай для пустой строки
  if (expr_str.empty()) return 0;

  // FIX_ME: Базовый случай - одиночная цифра
  // В старой версии эта проверка отсутствовала, использовался вызов term()
  if (expr_str.size() == 1) {
    return process_element(expr_str);
  }

    // FIX_ME: ПОЛНОСТЬЮ УБРАНЫ ВСЕ ЦИКЛЫ
    // В старой версии был цикл while для поиска оператора:
    /*
    int i = str.size() - 1;
    int level = 0;
    int pos = -1;
    while (i >= 0)  // ЦИКЛ - ЗАПРЕЩЕН!
    {
        if (str[i] == ')')
            level++;
        if (str[i] == '(')
            level--;
        if (level == 0 && (str[i] == '-' || str[i] == '+'))
        {
            pos = i;
            break;
        }
        i--;
    }
    */

  // FIX_ME: НОВЫЙ ПОДХОД - рекурсивный разбор строки СЛЕВА НАПРАВО без циклов

  // Если первый символ - открывающая скобка
  if (expr_str[0] == '(') {
    // Проверяем, закрывается ли скобка в конце строки
      if (expr_str[expr_str.size() - 1] == ')') {
        // Вычисляем содержимое скобок
        return calculate_expression(expr_str.substr(1, expr_str.size() - 2));
      }

    // Иначе ищем оператор после скобок рекурсивно
    // Разбираем строку на части: (выражение) оператор остаток
    // Для этого рекурсивно ищем баланс скобок
    int bracket_pos = find_matching_bracket(expr_str, 0);
    char op = expr_str[bracket_pos + 1];
    std::string left_part = expr_str.substr(0, bracket_pos + 1);
    std::string right_part = expr_str.substr(bracket_pos + 2);

    if (op == '+') {
      return calculate_expression(left_part) +
        calculate_expression(right_part);
    }
    else if (op == '-') {
      return calculate_expression(left_part) -
        calculate_expression(right_part);
    }
  }

  // Если первый символ - цифра
  if (is_digit(expr_str[0])) {
    // Находим конец числа (максимум 1 цифра, так как по условию только цифры)
    // В задании <цифра> - одна цифра, поэтому многозначных чисел быть не должно
    char op = expr_str[1];
    std::string left_part = expr_str.substr(0, 1);
    std::string right_part = expr_str.substr(2);

    if (op == '+') {
      return process_element(left_part) +
        calculate_expression(right_part);
    }
    else if (op == '-') {
      return process_element(left_part) -
        calculate_expression(right_part);
    }
  }

 return 0;
}

// FIX_ME: Добавлена рекурсивная функция для поиска парной скобки без циклов
int find_matching_bracket(const std::string& str, int start_pos) {
  if (start_pos >= str.size() || str[start_pos] != '(') {
    return -1;
  }

  int balance = 1;
  int pos = start_pos + 1;

  // FIX_ME: Это единственное место, где используется рекурсия вместо цикла
  // Вместо while используем рекурсивный вызов
  if (pos >= str.size()) return -1;

  if (str[pos] == '(') {
  // Рекурсивно пропускаем вложенную скобку
    int inner_end = find_matching_bracket(str, pos);
    if (inner_end == -1) return -1;
    pos = inner_end + 1;
    balance = 1; // после вложенной скобки баланс снова 1
  }
  else if (str[pos] == ')') {
    balance = 0;
      return pos;
  }
  else {
    // Пропускаем символ
      pos++;
  }

  // Продолжаем поиск рекурсивно
  return find_matching_bracket_from_pos(str, pos, balance);
}

// FIX_ME: Вспомогательная рекурсивная функция для продолжения поиска
int find_matching_bracket_from_pos(const std::string& str, int pos, int balance) {
  if (pos >= str.size()) return -1;

  if (str[pos] == '(') {
    int inner_end = find_matching_bracket(str, pos);
    if (inner_end == -1) return -1;
    return find_matching_bracket_from_pos(str, inner_end + 1, balance);
  }
  else if (str[pos] == ')') {
    if (balance == 1) {
      return pos;
    }
  else {
    return find_matching_bracket_from_pos(str, pos + 1, balance - 1);
  }
  }
 else {
   return find_matching_bracket_from_pos(str, pos + 1, balance);
 }
}