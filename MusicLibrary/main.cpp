#include "src/Library.h"
int main()
{

  Library myLibrary;

  char role;
  role = myLibrary.chooseRole();

  bool running = true;
  while (running)
  {
    switch (role)
    {
    case 'c':
      running = myLibrary.creatorMenu();
      break;
    case 'u':
      running = myLibrary.userMenu();
      break;
    }
  }
  return 0;
}