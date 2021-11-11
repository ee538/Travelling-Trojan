#include <iostream>
#include "src/lib/trojanmap.h"

using namespace std;

int main() {
  
  TrojanMap x;
  x.CreateGraphFromCSVFile();
  x.PrintMenu();
  return 0;
  
}