#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
class NgramList 
{
   public:

   struct Ngram
   {
      std::string ngram;
      int count;
      struct Ngram * next;

   };
   struct CompareCount
   {
       bool operator()(const Ngram& x, const Ngram& y) const
       {
           return x.count >= y.count;
       }
   };

   typedef struct Ngram Ngram_t;

   private:
      //added variables
      std::unordered_map<std::string, int>::iterator it;
      std::vector<Ngram> counts;
      std::unordered_map<std::string, int> hashMap;


      Ngram_t * first;
      int ngramSz;
      void insertNgram(std::string s);
      std::string getNextNgram(WordList::const_iterator start, 
                               WordList::const_iterator end);
       
   public:
      NgramList(int ngramSz, const WordList & wl);
      ~NgramList();
      void sortByCount();

      //added functions
      void mergeSort(std::vector<Ngram> &, int, int);
      void merge(std::vector<Ngram> &, int, int ,int);
      void populateVector(std::vector<Ngram> & counts);
      //template<typename I>
      //void mergeSort(I begin, I end);
      //template<typename I>
      //void merge(I begin, I midPoint, I end);
      
      //bool compareByNumber(const Ngram, const Ngram); 

      friend std::ostream& operator<<(std::ostream& os, const NgramList & nl);
};
