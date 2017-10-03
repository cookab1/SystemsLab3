#include <vector>
#include <map>
class NgramList 
{
   struct Ngram
   {
      std::string ngram;
      int count;
      struct Ngram * next;
   };

   typedef struct Ngram Ngram_t;

   private:
      Ngram_t * first;
      std::vector<Ngram> counts;

      int ngramSz;
      std::map<std::string,int> hashMap;
      void insertNgram(std::string s);
      std::string getNextNgram(WordList::const_iterator start, 
                               WordList::const_iterator end);
       
   public:
      NgramList(int ngramSz, const WordList & wl);
      ~NgramList();
      void sortByCount();
      void MergeSort(std::vector<Ngram>, int, int);
      void Merge(std::vector<Ngram>, int, int, int);
      friend std::ostream& operator<<(std::ostream& os, const NgramList & nl);
};

