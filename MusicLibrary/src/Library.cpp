#define NOMINMAX
#include <iomanip>
#include <string>
#include <algorithm> // For std::transform
#include <cctype>    // For std::tolower
#include <vector>
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
    std::cout << "Invalid selection! Please try again..." << std::endl;
    std::cin.get();
  }

  return -1;
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
    std::cin.get();
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
    break;
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
    std::cin.get();
    sortMenu();
  }
}

void Library::searchMenu()
{
  searchForMusic();
  clearCinFlag();
}
void Library::addMenu()
{
  std::cout << "Enter music info: " << std::endl;
  addMusic();
}
void Library::removeMenu()
{
  deleteMusic();
}
void Library::updateMenu()
{
  updateMusicMetadata();
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
  std::vector<Music *> searchResults = searchForMusic();
  if (searchResults.empty())
  {
    std::cout << "No music found matching the search term." << std::endl;
    return;
  }

  std::cout << "Enter the number of the song to play (or 0 to exit to user menu): ";
  int selection;
  std::cin >> selection;

  if (selection == 0)
  {
    return; // User chooses to exit to user menu
  }

  if (selection < 1 || selection > searchResults.size())
  {
    std::cout << "Invalid selection." << std::endl;
    return; // Invalid selection, exit the function
  }

  Music *currentMusic = searchResults[selection - 1];

  // Playback loop
  while (currentMusic != nullptr)
  {
    currentMusic->incrementPlayCount(); // increment playcount
    std::cout << "Playing " << currentMusic->viewTitle() << " by " << currentMusic->viewArtist() << std::endl;

    std::cout << "Enter 'N' for next song or 'S' to stop: ";
    char command;
    std::cin >> command;

    if (command == 'N' || command == 'n')
    {
      currentMusic = currentMusic->nextMusic;
      if (currentMusic == nullptr)
      {
        std::cout << "End of the playlist." << std::endl;
        break; // Reached the end of the playlist
      }
    }
    else if (command == 'S' || command == 's')
    {
      break; // Stop playback
    }
    else
    {
      std::cout << "Invalid command. Please enter 'N' for next or 'S' to stop." << std::endl;
    }
  }
}

void Library::updateMusicMetadata()
{
  std::string updateTitle;
  std::cout << "Enter the title of the music you want to update: ";
  std::getline(std::cin, updateTitle);

  // Convert updateTitle to lowercase for case-insensitive comparison
  std::transform(updateTitle.begin(), updateTitle.end(), updateTitle.begin(),
                 [](unsigned char c)
                 { return std::tolower(c); });

  Music *currentMusic = head;

  while (currentMusic != nullptr)
  {
    std::string title = currentMusic->viewTitle();

    // Convert title to lowercase
    std::transform(title.begin(), title.end(), title.begin(), ::tolower);

    // Check if the music title matches the updateTitle
    if (title == updateTitle)
    {
      std::string newTitle, newArtist, newGenre;

      // Get the updated information from the user
      std::cout << "Enter new title: ";
      std::getline(std::cin, newTitle);
      std::cout << "Enter new artist: ";
      std::getline(std::cin, newArtist);
      std::cout << "Enter new genre: ";
      std::getline(std::cin, newGenre);

      // Update the metadata of the current music
      currentMusic->addMetadata(newTitle, newArtist, newGenre);
      std::cout << "Music updated successfully." << std::endl;
      return;
    }

    currentMusic = currentMusic->nextMusic; // Move to the next music item
  }

  // If the loop completes, the music was not found
  std::cout << "Music with title \"" << updateTitle << "\" not found." << std::endl;
  std::cin.get();
}

void Library::deleteMusic()
{
  std::string deleteTitle;
  std::cout << "Enter the title of the music you want to delete: ";
  std::getline(std::cin, deleteTitle);

  // Convert deleteTitle to lowercase for case-insensitive comparison
  std::transform(deleteTitle.begin(), deleteTitle.end(), deleteTitle.begin(),
                 [](unsigned char c)
                 { return std::tolower(c); });

  Music *currentMusic = head;
  Music *prevMusic = nullptr;

  while (currentMusic != nullptr)
  {
    std::string title = currentMusic->viewTitle();

    // Convert title to lowercase
    std::transform(title.begin(), title.end(), title.begin(), ::tolower);

    // Check if the music title matches the deleteTitle
    if (title == deleteTitle)
    {
      // Update pointers to bypass the current music node
      if (prevMusic)
      {
        prevMusic->nextMusic = currentMusic->nextMusic;
      }
      else
      {
        head = currentMusic->nextMusic;
      }

      // Delete the current music node
      delete currentMusic;

      std::cout << "Music deleted successfully." << std::endl;
      return;
    }

    prevMusic = currentMusic;
    currentMusic = currentMusic->nextMusic; // Move to the next music item
  }

  // If the loop completes, the music was not found
  std::cout << "Music with title \"" << deleteTitle << "\" not found." << std::endl;
  std::cin.get();
}

std::vector<Music *> Library::searchForMusic()
{
  // Implementation for searching music
  std::string searchTerm;
  std::cout << "Enter search term: ";
  getline(std::cin, searchTerm);

  // Convert search term to lowercase for case-insensitive comparison
  std::transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(),
                 [](unsigned char c)
                 { return std::tolower(c); });

  std::vector<Music *> searchResults;
  Music *currentMusic = head;
  int index = 1;

  std::cout << "Search Results:" << std::endl;
  while (currentMusic != nullptr)
  {
    std::string title = currentMusic->viewTitle();
    std::string artist = currentMusic->viewArtist();
    std::string genre = currentMusic->viewGenre();

    // Convert attributes to lowercase
    std::transform(title.begin(), title.end(), title.begin(), ::tolower);
    std::transform(artist.begin(), artist.end(), artist.begin(), ::tolower);
    std::transform(genre.begin(), genre.end(), genre.begin(), ::tolower);

    // Check if the search term is in any of the attributes
    if (title.find(searchTerm) != std::string::npos ||
        artist.find(searchTerm) != std::string::npos ||
        genre.find(searchTerm) != std::string::npos)
    {
      std::cout << index << ": " << currentMusic->viewTitle() << ", " << currentMusic->viewArtist()
                << ", " << currentMusic->viewGenre() << std::endl;
      searchResults.push_back(currentMusic);
      index++;
    }

    currentMusic = currentMusic->nextMusic; // Move to the next music item
  }

  if (searchResults.empty())
    std::cout << "Not found!" << std::endl;
  return searchResults;
}
