#include <vector>
#include <string>

// FIX_ME: Запрещено using namespace std 
// using namespace std;

// Функция для нахождения максимальной суммы и пути
// FIX_ME: Имя функции должно быть в lower_case_with_underscores 
// void findPath(vector<vector<int>>& board, int N, ofstream& output) {
void find_max_path(const std::vector<std::vector<int>>& board,
  int board_size,
  std::ofstream& output_file);

