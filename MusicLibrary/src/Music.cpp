#include "Music.h"

std::string shortenAndAppendEllipsis(const std::string &input, int length)
{
  if (input.length() > length)
  {
    return input.substr(0, length - 3) + "...";
  }
  else
  {
    return input;
  }
}

Music::Music()
{
  prevMusic = nullptr;
  nextMusic = nullptr;
}

void Music::addMetadata(std::string title, std::string artist, std::string genre, int play_count)
{
  this->title = shortenAndAppendEllipsis(title, MAX_STRING_DISPLAY);
  this->artist = shortenAndAppendEllipsis(artist, MAX_STRING_DISPLAY);
  this->genre = shortenAndAppendEllipsis(genre, MAX_STRING_DISPLAY);
  this->play_count = play_count;
}

void Music::editTitle(std::string title)
{
  this->title = title;
}
void Music::editArtist(std::string artist)
{
  this->artist = artist;
}
void Music::editGenre(std::string genre)
{
  this->genre = genre;
}
void Music::incrementPlayCount()
{
  play_count++;
}
std::string Music::viewTitle() const
{
  return title;
}
std::string Music::viewArtist() const
{
  return artist;
}
std::string Music::viewGenre() const
{
  return genre;
}
int Music::viewPlayCount() const
{
  return play_count;
}