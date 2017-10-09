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
<<<<<<< HEAD
      void MergeSort(vector<Ngram>, int, int);
      void Merge(vector<Ngram>, int, int, int);
=======
      void MergeSort(std::vector<Ngram>, int, int);
      void Merge(std::vector<Ngram>, int, int, int);
>>>>>>> 123a1202ee886fd6b5df895e63e789a8302afe7b
      friend std::ostream& operator<<(std::ostream& os, const NgramList & nl);
};

