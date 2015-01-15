#include "considerpath.h"

ConsiderPath::ConsiderPath(Path *path)
{
    _path = path;

    int sizeSimplVertexSet = _path->GetSizeOfSimplifyVertexSet();
    int sizeVertexSet = _path->GetSimplifyVertexByNum(sizeSimplVertexSet-1)->GetVertexSetSize();





    _startPos = path->GetSimplifyVertexByNum(0)->GetVertexByIndex(0)->GetCoor();
    _endPos = path->GetSimplifyVertexByNum(sizeSimplVertexSet-1)->GetVertexByIndex(sizeVertexSet-1)->GetCoor();

    _pathSize = _endPos - _startPos;

    int countVertex = 0;

    for(int i = 0; i < sizeSimplVertexSet;i++)
    {
        for(int j = 0; j < sizeVertexSet;j++)
        {
            countVertex++;
        }
    }

    _vertexCount = countVertex;

    _weight=-1;





}
