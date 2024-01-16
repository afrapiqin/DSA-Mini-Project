#include <iostream>
#include <vector>
#include "MusicList.h"

#ifdef _WIN32
#include <windows.h>
#elif __unix__ || __linux__
#include <cstdlib>
#endif

class Library : public MusicList
{
public:
  Library();  // Constructor to be called once in main(), it will load the list from Library.bin
  ~Library(); // Destructor will be called once the program ended, it will save the list to Library.bin

  char chooseRole();
  bool creatorMenu();
  bool userMenu();
  void sortMenu();
  void searchMenu();
  void addMenu();
  void removeMenu();
  void updateMenu();

private:
  void viewLibrary(int limit = -1);
  void playMusic();
  void viewTopMusic();
  void addMusic();
  void deleteMusic();
  void updateMusicMetadata();
  std::vector<Music*> searchForMusic();
  void clearScreen();
};
