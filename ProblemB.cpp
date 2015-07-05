#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

const int MAX_I = 20; // as given.
const int MAX_L = 6;  // as given.
const int BASE  = 10; // we use 10-base system (decimal).

int digit(int a, int n) {
  // return n-th digit of integer a.
  // (958, 0) -> 8. (958, 2) -> 9.
  for (int i = 0; i < n; i++) {
    a /= BASE;
  }
  return a % BASE;
}

int digitsToInt(int digits[], int L) {
  int ret = 0;
  for (int i = 0; i < L; i++) {
    int buf = digits[i];
    for (int j = 0; j < i; j++) {
      buf *= BASE;
    }
    ret += buf;
  }
  return ret;
}

int getMax(int a, int L){
  int digits[MAX_L];
  for (int i = 0; i < L; i++) {
    digits[i] = digit(a, i);
  }

  sort(digits, digits + L);
  return digitsToInt(digits, L);
}

int getMin(int a, int L){
  int digits[MAX_L];
  for (int i = 0; i < L; i++) {
    digits[i] = digit(a, i);
  }

  sort(digits, digits + L, greater<int>());
  return digitsToInt(digits, L);
}

int main(int argc, char* argv[]) {
  int a[MAX_I + 1];
  int L;
  
  while (1) {
    cin >> a[0] >> L;
    if ((a[0] == 0) && (L == 0)) break;
    
    int i = 1, j;
    for (i = 1; i <= MAX_I; i++) {
      a[i] = getMax(a[i - 1], L) - getMin(a[i - 1], L);
      for (j = 0; j < i; j++) {
        if (i != j && a[i] == a[j]) break; // (i, j) is found!
      }
      if (i != j && a[i] == a[j]) break; // (i, j) is found!
    }
    cout << j << " " << a[i] << " " << i - j << endl;
  }

  return 0;
}

/*
VERSION 01 13:19-14:08 http://ideone.com/IcH2Ir
VERSION 02 http://ideone.com/cDIpxn
*/
