#include <iostream>
using namespace std;

const int DAYS_OF_SMALL_MONTH = 19;
const int DAYS_OF_BIG_MONTH = 20;
const int MONTHS_OF_YEAR = 10;

const int YEAR_OF_MILLENNIUM_DAY = 1000;
const int MONTH_OF_MILLENNIUM_DAY = 1;
const int DAY_OF_MILLENNIUM_DAY = 1;

int dayOfMonth(int month, int year) {
  if (year % 3 == 0) {
    return DAYS_OF_BIG_MONTH;
  }
  else if (month % 2 == 0) {
    return DAYS_OF_SMALL_MONTH;
  }
  else {
    return DAYS_OF_BIG_MONTH;
  }
}

int main(int argc, char* argv[]) {
  int N;
  cin >> N;

  int Y, M, D;
  for (int n = 0; n < N; n++) {
    cin >> Y >> M >> D;
    int dayTook = 0;

    while ((Y != YEAR_OF_MILLENNIUM_DAY) || (M != MONTH_OF_MILLENNIUM_DAY)) {
      dayTook += dayOfMonth(M, Y);
      M++;
      if (M > MONTHS_OF_YEAR) {
        M = 1;
        Y++;
      }
    }

    dayTook -= D - DAY_OF_MILLENNIUM_DAY;

    cout << dayTook << endl;
  }

  return 0;
}

/*
VERSION 01 16:56-17:31 http://ideone.com/pdi1fZ
VERSION 02
*/
