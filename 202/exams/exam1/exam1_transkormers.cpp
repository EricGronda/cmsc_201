#include <iostream>
#include <string>
using namespace std;

int main(){
  char ch;
  int j = 4;
  char title[] = "Transformers";
  ch = title[j];
  title[j++] = 'k';
  title[j] = ch;
  cout << title << endl;
  cout << ch << endl;

  return 0;
}
