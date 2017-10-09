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
   typedef struct Ngram Ngram_t;
   
   struct Compare
   {
       bool operator()(Ngram_t* x, Ngram_t* y)
       {
           return x->count >= y->count;
       }
   };
   typedef struct Compare CompareCount;
   

   private:
      //added variables
      //std::unordered_map<std::string, int>::iterator it;
      //std::vector<Ngram> counts;
      //std::unordered_map<std::string, int> hashMap;


      Ngram_t * first;
      int ngramSz;
      void insertNgram(std::string s);
      std::string getNextNgram(WordList::const_iterator start, 
                               WordList::const_iterator end);
       
   public:
      std::unordered_map<std::string, int>::iterator it;
      std::vector<Ngram_t*> counts;
      std::unordered_map<std::string, int> hashMap;
      NgramList(int ngramSz, const WordList & wl);
      ~NgramList();
      void sortByCount();

      //added functions
      //void mergeSort(std::vector<Ngram_t> &, int, int);
      //void merge(std::vector<Ngram_t> &, int, int ,int);
      void populateVector(std::vector<Ngram_t*> counts);
      void sortVector();
      //static bool compareCount(Ngram_t &a, Ngram_t &b);
      //template<typename I>
      //void mergeSort(I begin, I end);
      //template<typename I>
      //void merge(I begin, I midPoint, I end);
      
      //bool compareByNumber(const Ngram, const Ngram); 

      friend std::ostream& operator<<(std::ostream& os, const NgramList & nl);
};
