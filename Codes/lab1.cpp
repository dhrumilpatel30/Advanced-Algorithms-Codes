#include <bits/stdc++.h>

using namespace std;

int swaps, comparisons;

int partition(int array[], int p, int r) {
  srand(time(NULL));
  int randomIndex = p + rand() % (r - p + 1);
  //	cout<<randomIndex<<" ";
  int pivot = array[randomIndex];
  array[randomIndex] = array[r];
  array[r] = pivot;
  int i = (p - 1);
  for (int j = p; j < r; j++) {
    if (array[j] < pivot) {
      i++;
      swap(array[i], array[j]);
      swaps++;
    }
    comparisons++;
  }
  if ((i + 1) != r) {
    swap(array[i + 1], array[r]);
    swaps++;
    comparisons++;
  }
  return (i + 1);
}

void randMergeSort(int array[], int p, int r) {
  if (p < r) {
    int q = partition(array, p, r);

    randMergeSort(array, p, q - 1);
    randMergeSort(array, q + 1, r);
  }
}

int main() {
  swaps = 0;
  comparisons = 0;
  int array[] = {4,  3,  6,  8,  5,  9,  20, 50, 12, 30, 432, 12,  69,
                 29, 40, 50, 10, 4,  23, 34, 45, 45, 24, 89,  799, 45,
                 80, 50, 10, 30, 43, 54, 65, 76, 87, 98, 21,  32,  43,
                 78, 98, 57, 29, 91, 34, 54, 64, 19, 82, 87,  65};
  randMergeSort(array, 0, sizeof(array) / sizeof(array[0]) - 1);
  cout << endl << "sortedArray :";
  for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
    cout << array[i] << " ";
  cout << endl;
  cout << "swaps : " << swaps << endl;
  cout << "comparisons : " << comparisons << endl;
  return 0;
}
