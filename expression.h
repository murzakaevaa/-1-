#include <string>

// FIX_ME: Запрещено using namespace std 
// using namespace std;

// FIX_ME: Добавлена вспомогательная функция для проверки цифры
bool is_digit(char c);

// FIX_ME: Имена функций должны быть в lower_case_with_underscores
// int calc(string str);
// int element(string str)
int process_element(const std::string& element_str);
int calculate_expression(const std::string& expr_str);

// FIX_ME: Добавлены рекурсивные функции для поиска парной скобки
int find_matching_bracket(const std::string& str, int start_pos);
int find_matching_bracket_from_pos(const std::string& str, int pos, int balance);

