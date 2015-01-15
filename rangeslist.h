#ifndef RANGESLIST_H
#define RANGESLIST_H
#include "considerscaffold.h"
#include <fstream>

class RangesList
{
private: SetOfRef<int> _rangesList;
public:
    RangesList();

    int GetRangeByIndex(int index)
    {
        return *(_rangesList.GetItemByNum(index));
    }
    int GetSizeOfRangesSet()
    {
        return _rangesList.GetSizeOfSet();
    }

    void Clear();

    void AddRange(int range);

    void CountRanges(Path* pathA, Path* pathB);
    void CountRanges(ConsiderScaffold* scaffold, Path* path);
    void CountRanges(ConsiderScaffold* scaffoldA, ConsiderScaffold* scaffoldB);

    void PrintRanges(fstream &fileToWrite);

};

#endif // RANGESLIST_H
