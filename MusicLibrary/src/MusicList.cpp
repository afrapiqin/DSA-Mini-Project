#include <fstream>
#include "MusicList.h"

MusicList::MusicList()
{
  head = nullptr;
  tail = nullptr;
}

void MusicList::pushBack(Music *music)
{
  if (head == nullptr)
  {
    // If the linked list is empty, add to head
    head = music;
  }
  else
  {
    // Traverse to the end of the list and add the new item
    Music *current = head;
    while (current->nextMusic != nullptr)
    {
      current = current->nextMusic;
    }
    current->nextMusic = music;
    music->prevMusic = current;
  }
  tail = music;
}

void MusicList::saveList() const
{
  std::ofstream outFile("Library.bin", std::ios::binary);

  if (!outFile)
  {
    throw std::runtime_error("Error opening file for writing");
  }

  Music *current = head;
  while (current != nullptr)
  {
    outFile.write(reinterpret_cast<const char *>(current), sizeof(Music));
    current = current->nextMusic;
  }

  outFile.close();
}
void MusicList::loadList()
{
  std::ifstream inFile("Library.bin", std::ios::binary);
  if (!inFile.fail())
  {
    Music *tail = nullptr;

    while (inFile.peek() != EOF)
    {
      Music *newNode = new Music();
      inFile.read(reinterpret_cast<char *>(newNode), sizeof(Music));

      if (head == nullptr)
      {
        head = tail = newNode;
      }
      else
      {
        tail->nextMusic = newNode;
        newNode->prevMusic = tail;
        tail = newNode;
      }
    }

    inFile.close();
  }
}
void MusicList::reloadList()
{
  head = nullptr;
  loadList();
}
void MusicList::mergeSort(std::string sortBy, bool asc)
{
  head = mergeSortRecursive(head, sortBy, asc);
}
// Recursive function to perform merge sort on the list
Music *MusicList::mergeSortRecursive(Music *start, std::string &sortBy, bool &asc)
{
  if (!start || !start->nextMusic)
  {
    return start;
  }

  Music *mid = findMiddle(start);
  Music *secondHalf = mid->nextMusic;
  mid->nextMusic = nullptr;

  Music *firstHalfSorted = mergeSortRecursive(start, sortBy, asc);
  Music *secondHalfSorted = mergeSortRecursive(secondHalf, sortBy, asc);

  return merge(firstHalfSorted, secondHalfSorted, sortBy, asc);
}

// Function to merge two sorted lists
Music *MusicList::merge(Music *first, Music *second, std::string &sortBy, bool &asc)
{
  if (!first)
    return second;
  if (!second)
    return first;

  if ((asc && compareNodes(first, second, sortBy)) || (!asc && !compareNodes(first, second, sortBy)))
  {
    first->nextMusic = merge(first->nextMusic, second, sortBy, asc);
    first->nextMusic->prevMusic = first;
    first->prevMusic = nullptr;
    return first;
  }
  else
  {
    second->nextMusic = merge(first, second->nextMusic, sortBy, asc);
    second->nextMusic->prevMusic = second;
    second->prevMusic = nullptr;
    return second;
  }
}

bool MusicList::compareNodes(Music *node1, Music *node2, std::string &sortBy)
{
  switch (sortBy[0])
  {
  case 't':
    return node1->viewTitle().front() < node2->viewTitle().front();
  case 'a':
    return node1->viewArtist().front() < node2->viewArtist().front();
  case 'g':
    return node1->viewGenre().front() < node2->viewGenre().front();
  case 'p':
    return node1->viewPlayCount() < node2->viewPlayCount();
  default:
    return false;
  }
}

// Function to find the middle of the list
Music *MusicList::findMiddle(Music *start)
{
  if (!start)
    return nullptr;

  Music *slow = start;
  Music *fast = start->nextMusic;

  while (fast && fast->nextMusic)
  {
    slow = slow->nextMusic;
    fast = fast->nextMusic->nextMusic;
  }

  return slow;
}