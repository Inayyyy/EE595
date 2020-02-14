#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
   int value[20][10];
   int rows;
   int cols;
   int repeat_row_index;
   int repeat_col_index;
public:
   void set_value(int i, int j, int x);
   int linear_search();
   void sort_row(int row_index);
   int binary_search(int row_index, int target);
   void print_matrix();
   int get_value(int i, int j);
   void get_matrix_size();
   int get_rows();
   int get_cols();
   int get_repeat_row_index();
   int get_repeat_col_index();
   void print_row(int row_index);
};

#endif
