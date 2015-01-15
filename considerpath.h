#ifndef CONSIDERPATH_H
#define CONSIDERPATH_H
#include "Path.h"

class ConsiderPath
{
private:
    Path *_path;

    int _startPos;
    int _endPos;

    int _pathSize;
    int _vertexCount;
    int _weight;

public:
    ConsiderPath(Path *_path);

    Path* GetPath()
    {
        return _path;
    }

    int GetStartPos()
    {
        return _startPos;
    }

    int GetEndPos()
    {
        return _endPos;
    }

    int GetPathSize()
    {
        return _pathSize;
    }

    int GetVertexCount()
    {
        return _vertexCount;
    }

    double GetWeight()
    {
        return _weight;
    }

    void SetWeight(double weight)
    {
        _weight = weight;
    }

};






#endif // CONSIDERPATH_H
