#include <iostream>
#include <list>

#include "controller.h"

using namespace std;

int main() {
  Model lol;
  auto rez = lol.Test("28.5+3*(1-5)*(3+4)");
  return 0;
}