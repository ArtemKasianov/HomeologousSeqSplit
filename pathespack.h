#ifndef PATHESPACK_H
#define PATHESPACK_H
#include <string>
#include "utils.h"

#include "Path.h"
class PathesPack
{
private:
    SetOfRef<Path> _pathes;
    int _startPos;
    int _endPos;


    std::string _name;


public:
    PathesPack();

    int GetStartPos()
    {
        return _startPos;
    }

    int GetEndPos()
    {
        return _endPos;
    }

    int GetNumberOfPathes()
    {
        return _pathes.GetSizeOfSet();
    }

    Path* GetPathByIndex(int index)
    {
        return _pathes.GetItemByNum(index);
    }

    std::string GetName()
    {
        return _name;
    }

    void AddPath(Path *pathToAdd);



};

#endif // PATHESPACK_H
