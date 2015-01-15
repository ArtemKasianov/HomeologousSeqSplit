#ifndef USEDPATHES_H
#define USEDPATHES_H
#include "considerpath.h"

class UsedPathes
{
private:
    HashUnsignedInt _usedPathes;
public:
    UsedPathes();


    void AddPath(ConsiderPath *consPath)
    {
        if(_usedPathes.find(consPath->GetPath()->GetIndexInResPath()) == _usedPathes.end())
        {

           _usedPathes[consPath->GetPath()->GetIndexInResPath()] = 1;
        }


    }

    int ExistPath(ConsiderPath *consPath)
    {
        return 0;
        if(_usedPathes.find(consPath->GetPath()->GetIndexInResPath()) == _usedPathes.end())
        {
            return 0;
        }
        else
        {
            return 1;
        }

    }
};

#endif // USEDPATHES_H
