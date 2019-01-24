#include "Animal.h"

int main(){
  Animal dog;
  Animal cat;

  dog.SetSound("bark");
  dog.SetName("Max");
  cat.SetSound("meow");
  cat.SetName("Furball");

  cout << "dog's name is: " << dog.GetName() << endl;
  cout << "dog makes sound: " << dog.GetSound() << endl;
  cout << "cat's name is: " << cat.GetName() << endl;
  cout << "cat makes sound: " << cat.GetSound() << endl;

  dog.WhoAmI();
  cat.WhoAmI();

  return 0;
}
