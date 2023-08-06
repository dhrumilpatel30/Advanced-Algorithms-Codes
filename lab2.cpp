#include <iostream>
#include <random>

using namespace std;

class FermatPrimalityTest {
 public:
  bool isPrime(int n, int k) {
    if (n <= 1) {
      return false;
    }

    if (n % 2 == 0) {
      return false;
    }

    int d = n - 1;
    while (d % 2 == 0) {
      d /= 2;
    }

    for (int i = 0; i < k; i++) {
      int a = rand() % (n - 2) + 2;

      // check gcd before power
      int gcd = optimizedGCD(a - 1, n);
      if (gcd != 1) {
        return false;
      }

      // power
      int x = optimizedPow(a, d, n);

      // check power after gcd
      if (x != 1 && x != n - 1) {
        return false;
      }
    }

    return true;
  }

  // optimized power function
  int optimizedPow(int a, int x, int n) {
    if (x == 0) {
      return 1;
    }

    if (x % 2 == 0) {
      int y = optimizedPow(a, x / 2, n);
      return y * y % n;
    } else {
      return a * optimizedPow(a, x - 1, n) % n;
    }
  }

  // optimized gcd function
  int optimizedGCD(int a, int b) {
    while (b != 0) {
      int c = a % b;
      a = b;
      b = c;
    }

    return a;
  }

  // test custom input and k
  bool isPrime(string input, int k) {
    int n = stoi(input);
    return isPrime(n, k);
  }
};

int main() {
  FermatPrimalityTest test;

  cout << "Enter a number to test: ";
  string input;
  cin >> input;

  cout << "Enter the number of tests: ";
  int k;
  cin >> k;

  if (test.isPrime(input, k)) {
    cout << input << " is prime" << endl;
  } else {
    cout << input << " is not prime" << endl;
  }

  return 0;
}
