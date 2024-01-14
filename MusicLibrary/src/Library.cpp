#define NOMINMAX
#include <iomanip>
#include <string>
#include "Library.h"
void clearCinFlag()
{
  std::cin.clear();                                                   // Clear the error flag
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
}
Library::Library()
{
  loadList();
}
Library::~Library()
{
  saveList();
}

void Library::clearScreen()
{
#ifdef _WIN32
  // For Windows
  system("cls");
#else
  // For Unix-like systems (Linux, macOS)
  system("clear");
#endif
}

char Library::chooseRole()
{
  int input;
  std::cout << "\n\t1. Creator" << std::endl
            << "\t2. User" << std::endl;

  std::cout << "\nChoose role: ";
  std::cin >> input;
  clearCinFlag();

  switch (input)
  {
  case 1:
    return 'c';
  case 2:
    return 'u';
  default:
    return 'u';
  }
}

bool Library::creatorMenu()
{
  viewLibrary();

  int input;
  std::cout << "\n\n\t1. Sort Library" << std::endl
            << "\t2. Search for music" << std::endl
            << "\t3. View Top 10" << std::endl
            << "\t4. Add Music" << std::endl
            << "\t5. Remove Music" << std::endl
            << "\t6. Update Music Metadata" << std::endl
            << "\t7. Save and Exit" << std::endl
            << "\t8. Exit" << std::endl;

  std::cout << "\n\nEnter choice: ";
  std::cin >> input;
  clearCinFlag();

  switch (input)
  {
  case 1:
    sortMenu();
    break;
  case 2:
    searchMenu();
    break;
  case 3:
    viewTopMusic();

    break;
  case 4:
    addMusic();
    break;
  case 5:
    removeMenu();
    break;
  case 6:
    updateMenu();
    break;
  case 7:
    return false;
    break;
  case 8:
    exit(0);
    break;
  default:
    std::cout << "Invalid selection! Please try again..." << std::endl;
    creatorMenu();
  }
  return true;
}
bool Library::userMenu()
{
  viewLibrary();

  int input;
  std::cout << "\n\n\t1. Play music" << std::endl
            << "\t2. Sort library" << std::endl
            << "\t3. Search for music" << std::endl
            << "\t4. View Top 10" << std::endl
            << "\t5. Exit" << std::endl;

  std::cout << "\n\nEnter choice: ";
  std::cin >> input;
  clearCinFlag();

  switch (input)
  {
  case 1:
    playMusic();
  case 2:
    sortMenu();
    break;
  case 3:
    searchMenu();
    break;
  case 4:
    viewTopMusic();
    break;
  case 5:
    exit(0);
    break;
  default:
    std::cout << "Invalid selection! Please try again..." << std::endl;
    userMenu();
  }
  return true;
}

void Library::sortMenu()
{
  int input;
  std::cout << "Choose attribute to sort by: " << std::endl
            << " 1. Title" << std::endl
            << " 2. Artist" << std::endl
            << " 3. Genre" << std::endl
            << " 4. Play Count" << std::endl;

  std::cout << "\n\nEnter choice: ";
  std::cin >> input;
  std::cin.clear();                                                   // Clear the error flag
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

  switch (input)
  {
  case 1:
    mergeSort("title", true);
    break;
  case 2:
    mergeSort("artist", true);
    break;
  case 3:
    mergeSort("genre", true);
    break;
  case 4:
    mergeSort("play_count", false);
    break;
  default:
    std::cout << "Invalid selection! Please try again..." << std::endl;
    sortMenu();
  }
}

void Library::searchMenu()
{
  // To implement menu for searching music
  // searchForMusic();
}
void Library::addMenu()
{
  std::cout << "Enter music info: " << std::endl;
  addMusic();
}
void Library::removeMenu()
{
  // To implement menu for removing music from the list
  // deleteMusic();
}
void Library::updateMenu()
{
  // To implement menu for updating music metadata
  // updateMusicMetadata();
}

void Library::viewLibrary(int limit)
{
  clearScreen();

  std::cout << std::setw(MAX_STRING_DISPLAY + 4) << std::left << "Title"
            << "| " << std::setw(MAX_STRING_DISPLAY + 4) << std::left << "Artist"
            << "| " << std::setw(MAX_STRING_DISPLAY + 4) << std::left << "Genre"
            << "| " << std::setw(15) << std::left << "Play Count" << std::endl;

  std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

  int count = 1;
  Music *current = head;
  while (current != nullptr)
  {
    std::cout << std::setw(MAX_STRING_DISPLAY + 4) << std::left << current->viewTitle() << "| "
              << std::setw(MAX_STRING_DISPLAY + 4) << std::left << current->viewArtist() << "| "
              << std::setw(MAX_STRING_DISPLAY + 4) << std::left << current->viewGenre() << "| "
              << std::setw(15) << std::left << current->viewPlayCount() << std::endl;

    current = current->nextMusic;

    if (limit != -1)
    {
      if (count == limit)
        break;
      count++;
    }
  }
}

void Library::viewTopMusic()
{
  // Implementation for viewing top played music (sort the list in descending order based on played_count)
  mergeSort("play_count", false);
  viewLibrary(10);

  std::cout << "\n\nPress any key to go back to the menu...";
  std::cin.get();

  reloadList();
}

void Library::addMusic()
{
  // Implementation for inserting new music ()
  std::string title;
  std::string artist;
  std::string genre;

  std::cout << "Enter music title: ";
  std::getline(std::cin, title);
  std::cout << "Enter music artist: ";
  std::getline(std::cin, artist);
  std::cout << "Enter music genre: ";
  std::getline(std::cin, genre);

  Music *music = new Music();
  music->addMetadata(title, artist, genre);
  pushBack(music);
}

void Library::playMusic()
{
  // Implementation for playing music
  // reuse search music function, then increment playcount
}

void Library::updateMusicMetadata()
{
  // Implementation for updating existing music
}

void Library::deleteMusic()
{
  // Implementation for deleting music record
}

void Library::searchForMusic()
{
  // Implementation for searching for music
}