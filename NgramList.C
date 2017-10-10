#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include "WordList.h"
#include "NgramList.h"
#include <stdio.h>
#include <algorithm>
#include <iterator>

using namespace std;


/*
 * NgramList
 *
 * takes as input the size of the ngrams to be built and the list  
 * of words to build the ngrams from and builds a linked list of 
 * ngrams.
 *
 * param: int ngramSz - size of the ngram
 * param: const WordList & wl - list of the words use
 */
NgramList::NgramList(int ngramSz, const WordList & wl)
{
   this->ngramSz = ngramSz;
   WordList::const_iterator p;
   //first = NULL;
   p = wl.begin();
   while (p != wl.end())
   {
      std::string ngram = getNextNgram(p, wl.end());
      p++;
      //puts the ngram into a unordered_map in O(1) time
      if (!ngram.empty()) insertNgram(ngram);
   }
   //populates the vector from the unordered_map
   populateVector(NgramList::counts);

   //uses built in sort that should be O(nlogn)
   NgramList::sortVector();

   //Print the sorted Ngrams
   cout << "List of 2 word ngrams and counts\n";
   cout << "--------------------------------\n";      
   for (int i = 0; i < NgramList::counts.size(); i++)
   {
       std::cout << NgramList::counts[i]->ngram << ", " <<  NgramList::counts[i]->count << "\n";
   }
   
}  

/*
 * NgramList destructor
 *
 * automatically called when NgramList object goes out of scope
 * deletes the linked list
 */
NgramList::~NgramList()
{
    /*
   Ngram_t * nextNgram;
   while (first != NULL)
   {
      nextNgram = first->next;
      delete(first);
      first = nextNgram;
    }
    */
    counts.erase(counts.begin(), counts.end());
    hashMap.erase(hashMap.begin());
    //delete(*it);
}

void NgramList::sortVector()
{
    std::sort(NgramList::counts.begin(), NgramList::counts.end(), NgramList::CompareCount());
}

/*
 * getNextNgram
 *
 * takes as input an iterator that points to the word to start the
 * ngram and an iterator that points to the end of the word list
 * and builds and returns the ngram. returns empty string if no
 * ngram can be built, for example, if there are insufficient words
 * to build one.
 *
 * param: WordList::const_iterator start - points to first word in ngram
 * param: WordList::const_iterator end - points to end of word list
 * return: std::string - returns ngram or empty string
 */
std::string NgramList::getNextNgram(WordList::const_iterator start, 
                                    WordList::const_iterator end)
{
   int i, len;
   string ngram = "";
   for (i = 0; i < ngramSz && start != end; i++)
   {
      std::string word = (*start);
      //see if the string ends with punctuation
      //don't create ngrams that continue after punctuation
      if (!isalpha(word[word.length()-1]) && i < ngramSz - 1) return "";

      //take off all ending punctuation
      len = word.length() - 1;
      while (len >= 0 && !isalpha(word[len])) 
      {
         //remove last character
         word = word.substr(0, word.length() - 1);
         len--;
      }
      if (len < 0) return "";  //give up

      //is the first word in the ngram?
      if (ngram == "") ngram = word;
      else ngram = ngram + " " + word;

      start++;
   }

   //could we build a long enough ngram?
   if (i < ngramSz) return "";

   //take off beginning punctuation
   while (ngram.length() > 0 && !isalpha(ngram[0])) 
      ngram = ngram.substr(1, ngram.length());
   return ngram;
}

/*
 * insertNgram
 *
 * looks for the ngram to be inserted. If it is already in
 * the linked list,  it increments the count. If not, it 
 * inserts it into the linked list.
 *
 * param: std::string s - ngram to be inserted
 * return: none
 */
void NgramList::insertNgram(std::string s)
{
   //insert and find O(1) for unordered_map   
   NgramList::it = hashMap.find(s);

   if (it == hashMap.end())
       hashMap.insert({s, 1});
   else
       it->second += 1;
   
}

/*
 * populates a vector with the ngrams from the unordered_map
 */
void NgramList::populateVector(vector<Ngram_t*> & counts)
{
    NgramList::it = hashMap.begin();
    while(it != hashMap.end())
    {
        Ngram_t * newNode = new Ngram_t();
        newNode->ngram = it->first;
        newNode->count = it->second;
        counts.push_back(newNode);
        it++;
    }
}


/*
 * operator<<
 *
 * prints the list of ngrams
 *
 * param: std::ostream & os - output stream to direct the output to
 * param: const NgramList & nglst - ngram list object
 * return: std::ostream & - output stream
 */
/*  
std::ostream& operator<<(std::ostream& os, const NgramList & nglst)
{
   cout << "List of " << nglst.ngramSz << " word ngrams and counts\n";
   cout << "--------------------------------\n";
   NgramList::Ngram_t * ptr = nglst.first;
   while (ptr != NULL)
   {
      cout << ptr->ngram << ", " << ptr->count << endl;
      ptr = ptr->next;
   }

   return os;
}
*/
