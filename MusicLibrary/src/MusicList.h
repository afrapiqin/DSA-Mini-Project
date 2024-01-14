#include <iostream>
#include "Music.h"

class MusicList
{
protected:
  Music *head;
  Music *tail;

public:
  MusicList();

  void pushBack(Music *music);
  void mergeSort(std::string sortBy = "title", bool asc = true); // by default the function will sort the list by title in ascending order
  void saveList() const;
  void reloadList();
  void loadList();

private:
  Music *mergeSortRecursive(Music *start, std::string &sortBy, bool &asc);
  Music *merge(Music *first, Music *second, std::string &sortBy, bool &asc);
  bool compareNodes(Music *node1, Music *node2, std::string &sortBy);
  Music *findMiddle(Music *start);
};