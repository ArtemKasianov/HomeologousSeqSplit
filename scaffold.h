#ifndef SCAFFOLD_H
#define SCAFFOLD_H
#include "filteredpathesset.h"
class Scaffold
{
private:
    SetOfRef<Path> _pathes;
    UniqueReadList _readList;


public:
    Scaffold();

    void AddPath(Path *pathToAdd)
    {
        _readList.AddSetOfReadList(pathToAdd->GetReadList());
        _pathes.AddToSet(pathToAdd);
    }

    Path* GetPathByIndex(int index)
    {
        return _pathes.GetItemByNum(index);
    }

    int GetSizeOfPathesSet()
    {
        return _pathes.GetSizeOfSet();
    }

    void PrintScaffold(fstream &scaffFile);

    std::string GetReadNameByNum(int index)
    {
        return _readList.GetReadList().GetRefItemByNum(index)->GetSequenceName();
    }

    int GetSizeOfReadList()
    {
        return _readList.GetReadList().GetSizeOfSet();
    }

    SetOfFastqSeqRecords GetReadList()
    {
        return _readList.GetReadList();
    }

};

#endif // SCAFFOLD_H
