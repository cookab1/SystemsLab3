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
   first = NULL;
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

   //mergeSort(NgramList::counts, 0, NgramList::counts.size());
   //mergeSort(std::begin(NgramList::counts, std::end(NgramList::counts));
   //mergeSort(NgramList::counts.begin(), NgramList::counts.end());
   
   //uses built in sort that should be O(nlogn)
   
   //std::sort(NgramList::counts.begin(), NgramList::counts.end(), NgramList::CompareCount());
   
   NgramList::sortVector();

   //Print the sorted Ngrams 
   /*    
   for (int i = 0; i < NgramList::counts.size(); i++)
   {
       std::cout << "STRING: " << NgramList::counts[i]->ngram << " COUNT: " << NgramList::counts[i]->count << "\n";
   }
   */
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
   /* 
   Ngram_t * ptr = first;
   //Ngram_t * newNode = new Ngram_t();
   //newNode->ngram = s;
   //newNode->count = 1;

   while (ptr != NULL)
   {
      //s already in list
      if (ptr->ngram == s) 
      {
         ptr->count++;
         //delete(newNode);
         return;
      }
      ptr = ptr->next;
   }
   //insert in front of list
   Ngram_t * newNode = new Ngram_t();
   newNode->ngram = s;
   newNode->count = 1;
   newNode->next = first;
   first = newNode;
   */
   
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
        //std::cout << "Word: " << it->first << " Value: " << it->second << "\n";
        counts.push_back(newNode);
        it++;
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
   Ngram_t * ptr = first;
   Ngram_t * ptr1;
   Ngram_t * ptr2;
   int tcount;
   string tngram;

   while (ptr != NULL)
   {
      ptr1 = first; 
      ptr2 = ptr1->next;
      while (ptr2 != NULL) 
      {
         if (ptr2->count > ptr1->count)
         {
            tcount = ptr1->count;
            tngram = ptr1->ngram;
            ptr1->count = ptr2->count;
            ptr1->ngram = ptr2->ngram; 
            ptr2->count = tcount;
            ptr2->ngram = tngram;
         }
         ptr1 = ptr2; 
         ptr2 = ptr2->next;
      }
      ptr = ptr->next;
   }
   
   /*
   NgramList::it = hashMap.begin();
   while (it != hashMap.end())
   {
       Ngram_t * newNode = new Ngram_t();
       newNode->ngram = it->first;
       newNode->count = it->second;
       NgramList::counts.push_back(*newNode);
       it++;            

   }
   NgramList::mergeSort(counts, 0, counts.size());*/
}
/*
template<typename I>
void mergeSort(I begin, I end)
{
    std::size_t length = std::distance(begin, end);
    if (length <= 1)
        return;
    
    std::size_t mid = length/2;
    I midPoint = std::next(begin, mid);

    mergeSort(begin, midPoint);
    mergeSort(midPoint, end);

    merge(begin, midPoint, end);
}

template<typename I>
void merge(I begin, I midPoint, I end)
{
    typename std::vector<typename std::iterator_traits<I>::value_type> TmpVec;

    TmpVec tmp(std::make_move_iterator(begin), std::make_move_iterator(end));

    TmpVec::iterator beginAlt = std::begin(tmp);
    TmpVec::iterator endAlt = std::end(tmp);
    TmpVec::iterator midAlt = std::next(beginAlt, std::distance(begin, midPoint));

    TmpVec::iterator l = beginAlt;
    TmpVec::iterator r = midAlt;
    I i = begin;

    while(l < midPoint && r < end)
    {
        *i = std::move((*l->count < *r->count) ? *l++ : *r++);
        ++i;
    }
    while(l < midAlt)
    {
        *i = std::move(*l++);
        ++i;
    }
    while(r < endAlt)
    {
        *i = std::move(*r++);
        ++i;
    }

}
*/

/*
void NgramList::mergeSort(vector<Ngram> & counts, int low, int high)
{
    if(low < high)
    {
        //mid=(low+high)/2;
        int mid = l+(high-l)/2;

        NgramList::mergeSort(counts, low, mid);
        NgramList::mergeSort(counts, mid+1, high);

        NgramList::merge(counts, low, high, mid);
    }
}

void NgramList::merge(vector<Ngram> & counts, int low, int high, int mid)
{
    int i, j, k;
    Ngram temp[high-low+1];
    i = low;
    k = 0;
    j = mid + 1;

    while(i <= mid && j <= high)
    {
        if(counts.at(i).count < counts.at(j).count)
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
*/


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
   NgramList::Ngram_t * ptr = nglst.first;
   while (ptr != NULL)
   {
      cout << ptr->ngram << ", " << ptr->count << endl;
      ptr = ptr->next;
   }
   /*
   vector<NgramList::Ngram> const *counts = &(nglst.counts);
   for (std::vector<NgramList::Ngram>::size_type i = 0; i != nglst.counts.size(); i++)
   {
      cout << counts->at(i).ngram << ", " << counts->at(i).count << endl;
   }*/

   return os;
}
