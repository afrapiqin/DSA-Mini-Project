#include "src/Library.h"
int main()
{

  Library myLibrary;

  std::cout << "THE MUSIC PLAYER SYSTEM" << std::endl;
  std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
  std::cout << "Team members:" << std::endl;
  std::cout << "Hisyam Imran MEC232004" << std::endl;
  std::cout << "Mooi Tah Hoi MEC232002" << std::endl;
  std::cout << "Afif Rafiqin Adnan MEC232001" << std::endl;

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
