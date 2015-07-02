#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int digit(int a, int n) {
  // return n-th digit of integer a.
  for (int i = 0; i < n; i++) {
    a = a / 10;
  }
  return a % 10;
}

int digits_to_int(int digits[], int L) {
  int ret = 0;
  for (int i = 0; i < L; i++) {
    int buf = digits[i];
    for (int j = 0; j < i; j++) {
      buf *= 10;
    }
    ret += buf;
  }
  return ret;
}

int getMax(int a, int L){
  int digits[6];
  for (int i = 0; i < L; i++) {
    digits[i] = digit(a, i);
  }

  sort(digits, digits + L);
  return digits_to_int(digits, L);
}

int getMin(int a, int L){
  int digits[6];
  for (int i = 0; i < L; i++) {
    digits[i] = digit(a, i);
  }

  sort(digits, digits + L, greater<int>());
  return digits_to_int(digits, L);
}

int main(int argc, char* argv[]) {
  int a[21];
  int L;
  while (1) {
    cin >> a[0] >> L;
    if ((a[0] == 0) && (L == 0)) break;
    int i = 1, j;
    for (i = 1; i <= 20; i++) {
      a[i] = getMax(a[i - 1], L) - getMin(a[i - 1], L);
      for (j = 0; j < i; j++) {
        if (i != j && a[i] == a[j]) break;
      }
      if (i != j && a[i] == a[j]) break;
    }
    cout << j << " " << a[i] << " " << i - j << endl;
  }

  return 0;
}

/*
VERSION 01 13:19-14:08 http://ideone.com/IcH2Ir

*/
