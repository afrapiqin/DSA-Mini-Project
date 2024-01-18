#include <iostream>

#define MAX_STRING_DISPLAY 22
std::string shortenAndAppendEllipsis(const std::string &input, int length);

class Music
{
public:
  Music();
  void addMetadata(std::string title, std::string artist, std::string genre, int play_count = 0);
  void editTitle(std::string title);
  void editArtist(std::string artist);
  void editGenre(std::string genre);

  void incrementPlayCount();

  std::string viewTitle() const;
  std::string viewArtist() const;
  std::string viewGenre() const;
  int viewPlayCount() const;

  Music *prevMusic;
  Music *nextMusic;

private:
  std::string title;
  std::string artist;
  std::string genre;
  int play_count;
};