#include <iostream>
#include <map>

class music
{
public:
  void AddMusic(std::string title, std::string artist, std::string genre);
  void EditTitle(std::string title);
  void EditArtist(std::string artist);
  void EditGenre(std::string genre);

private:
  std::string title;
  std::string artist;
  std::string genre;
};