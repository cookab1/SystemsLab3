
#include <iostream>
#include <string>
#include <vector>
#include "WordList.h"
#include "NgramList.h"
#include <stdio.h>

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
   first = NULL;
   p = wl.begin();
   while (p != wl.end())
   {
      std::string ngram = getNextNgram(p, wl.end());
      p++;
      if (!ngram.empty()) insertNgram(ngram);
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
   Ngram_t * nextNgram;
   while (first != NULL)
   {
      nextNgram = first->next;
      delete(first);
      first = nextNgram;
   }
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
   std::map<string, int>::iterator it = hashMap.find(s):

   if (it == hashMap.end())
   {
       //Ngram_t * newNode = new Ngram_t();
       //newNode->ngram = s;
       //newNode->count = 1;
       haspMap.insert(std::map<string,int>::value_type(s, 1);
   }
   else if (it != hashMap.end())
   {
       it->second += 1;
   }
   else
   {
   }
}   

/*
 * sortByCount
 *
 * performs a bubble sort on the linked list of ngrams, sorting the
 * nodes in the list by the count
 *
 * param: none
 * return: none (modfied private linked list)
 */
void NgramList::sortByCount()
{
    //Implement merge sort
    std::map<string, int>::iterator it = hashMap.begin();
    
    while(it != hashMap.end())
    {
        //cout << it->second;
        Ngram next = new Ngram();
        next.ngram = it->first;
        next.count = it->second;
        counts.push_back(next);
        it++;
    }

    MergeSort(counts, 0, counts.size());
}

void MergeSort(std::vector<Ngram> counts, int low, int high)
{
    int mid;
    if(low < high)
    {
        mid=(low+high)/2;
        
        MergeSort(counts, low, mid);
        MergeSort(counts, mid+1, high);
        
        Merge(counts, low, high, mid); 
    }
}

void Merge(std::vector<Ngram> counts, int low, int high, int mid)
{
    int i, j, k, 
    Ngram temp[high-low+1];
    i = low;
    k = 0;
    j = mid + 1;

    while(i <= mid && j <= high)
    {
        if(counts.at(i)->count < counts.at(j)->count)
        {
            temp[k] = counts.at(i);
            k++;
            i++;
        }
        else
        {
            temp[k] = counts.at(j);
            k++;
            j++;
        }
    }

    while(i <= mid)
    {
        temp[k] = counts.at(i);
        k++;
        i++;
    }

    while(j <= high)
    {
        temp[k] = counts.at(j);
        k++;
        j++;
    }

    for(i = low; i <= high; i++)
    {
        counts.at(i) = temp[i-low];
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
std::ostream& operator<<(std::ostream& os, const NgramList & nglst)
{
   cout << "List of " << nglst.ngramSz << " word ngrams and counts\n";
   cout << "--------------------------------\n";
   //NgramList::Ngram_t * ptr = nglst.first;
   for (int i; counts.at(i) != NULL, i++)
   {
      cout << counts.at(i)->ngram << ", " << counts.at(i)->count << endl;
   } 
   return os;
}
