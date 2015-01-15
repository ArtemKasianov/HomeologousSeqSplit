#ifndef FILTEREDPATHESSET_H
#define FILTEREDPATHESSET_H

#include "pathespack.h"

class FilteredPathesSet
{
private:
    SetOfRef<PathesPack> _pathes;
public:
    FilteredPathesSet(SetOfRef<Path> *oldPath);

    PathesPack* GetPathesPackByIndex(int index)
    {
        return _pathes.GetItemByNum(index);
    }

    int GetPathesPackSetSize()
    {
        return _pathes.GetSizeOfSet();
    }

    ~FilteredPathesSet()
    {
        for(int i = 0; i<_pathes.GetSizeOfSet();i++)
        {
            PathesPack *currPathesPack = _pathes.GetItemByNum(i);
            delete currPathesPack;
        }
    }

    void Clear();
};

#endif // FILTEREDPATHESSET_H
