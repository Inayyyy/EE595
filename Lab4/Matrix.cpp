#include <iostream>
#include "Matrix.h"
using namespace std;

void Matrix::set_value(int i, int j, int x) {
   value[i][j] = x;
}

int Matrix::get_value(int i, int j) {
   return value[i][j];
}

void Matrix::print_matrix() {
   for (int i = 0; i < sizeof(value) / sizeof(value[0]); i++) {
      for (int j = 0; j < sizeof value[0] / sizeof(int); j++) {
         cout << value[i][j] << " ";
      }
      cout << endl;
   }
}

void Matrix::get_matrix_size() {
   rows = sizeof(value) / sizeof(value[0]);
   cols = sizeof(value[0]) / sizeof(int);
}

int Matrix::get_rows() {
   return rows;
}

int Matrix::get_cols() {
   return cols;
}

int Matrix::get_repeat_row_index() {
   return repeat_row_index;
}

// Return the number of iterations
// PRE: Run get_matrix_size() before calling this function
int Matrix::linear_search() {
   int FirstNum;
   for(int i = 0; i < rows; i++) {
      for(int j = 0; j < cols; j++) {
         if(i == 0 && j == 0) {
            FirstNum = value[i][j];
         } else if (value[i][j] == FirstNum) {
            repeat_row_index = i;
            return (i * cols + j + 1);
         }
      }
   }
}

void swap(int* a, int* b) {
   int temp = *a;
   *a = *b;
   *b = temp;
}

void sort_row_R(int val[], int i, int j) {
   // base case
   if (i >= j) return;
   
   // recursive rule
   int start = i;
   int last = j;
   while(i <= j) {
      if(val[i] <= val[last]) {
         i++;
      } else {
         swap(&val[i], &val[j]);
         j--; 
      }
   }
   // i > j
   swap(&val[i], &val[last]);
   sort_row_R(val, start, i - 1);
   sort_row_R(val, i + 1, last);
}

// Quick sort
void Matrix::sort_row(int row_index) {
   if (row_index >= rows || row_index <0) {
      cout << "Invalid row index." << endl;
   }
   sort_row_R(value[row_index], 0, cols-1);
}

int Matrix::binary_search(int row_index, int target) {
   int counter = 0;
   int l = 0;
   int r = cols - 1;
   repeat_col_index = -1;
   while (l <= r) {
      int mid = l + (r - l)/2;
      counter++;
      if(value[row_index][mid] > target) {
         r = mid - 1;
      } else if (value[row_index][mid] == target) {
         repeat_col_index = mid;
         break;
      } else {
         l = mid + 1;
      }
   }
   return counter;
}

int Matrix::get_repeat_col_index() {
   return repeat_col_index;
}

void Matrix::print_row(int row_index) {
   cout << value[row_index][0];
   for(int i = 1; i < cols; i++) {
      cout << ", " << value[row_index][i];
   }
   cout << endl;
}

