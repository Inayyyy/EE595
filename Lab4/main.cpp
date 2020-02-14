#include <iostream>
#include <sstream>
#include <fstream>
#include "Matrix.h"

using namespace std;

void read_from_file(char*, Matrix&);

int main(int argc, char* argv[]) {
   if (argc != 2) {
      cout << "Follow the excutable with input file. E.g. ./Lab4_3973887764 input.txt" << endl;
   } else {
      Matrix matrix;  // only a name without real object
      read_from_file(argv[1], matrix);
      matrix.get_matrix_size();
      cout << matrix.linear_search() << endl; //1
      int repeat_row = matrix.get_repeat_row_index();
      matrix.sort_row(repeat_row);
      int iterate_bs = matrix.binary_search(repeat_row, matrix.get_value(0, 0)); //4
      matrix.print_row(repeat_row); //2
      cout << matrix.get_repeat_col_index() << endl;  //3
      cout << iterate_bs << endl; //4
   }
}

void read_from_file(char* filename, Matrix& matrix) {
   ifstream input;
   input.open(filename);
   string line;
   int i = 0;
   int j = 0;
   while(getline(input, line)) {
      istringstream row(line);
      int val;
      while(row >> val) {
         matrix.set_value(i, j, val);
         j++;
      }
      i++;
      j = 0;
   }
   input.close();
}
