#include "pathespack.h"

PathesPack::PathesPack()
{
    _name = "";
}

void PathesPack::AddPath(Path *pathToAdd){
    if(_pathes.GetSizeOfSet() == 0)
    {
        _pathes.AddToSet(pathToAdd);

        std::string nam = "";

        _startPos = pathToAdd->GetSimplifyVertexByNum(0)->GetVertexByIndex(0)->GetCoor();

        int simplVertexIndex = pathToAdd->GetSizeOfSimplifyVertexSet()-1;
        int vertexIndex = pathToAdd->GetSimplifyVertexByNum(pathToAdd->GetSizeOfSimplifyVertexSet()-1)->GetVertexSetSize()-1;
        _endPos = pathToAdd->GetSimplifyVertexByNum(simplVertexIndex)->GetVertexByIndex(vertexIndex)->GetCoor();


        char *tempStartPos = new char[255];
        char *tempEndPos = new char[255];
        itoa(_startPos,tempStartPos,10);
        itoa(_endPos,tempEndPos,10);



        nam = nam + tempStartPos + "_" + tempEndPos;

        delete[] tempStartPos;
        delete[] tempEndPos;
        _name = nam;

    }
    else
    {
        int startPosTemp = pathToAdd->GetSimplifyVertexByNum(0)->GetVertexByIndex(0)->GetCoor();

        int simplVertexIndex = pathToAdd->GetSizeOfSimplifyVertexSet()-1;
        int vertexIndex = pathToAdd->GetSimplifyVertexByNum(pathToAdd->GetSizeOfSimplifyVertexSet()-1)->GetVertexSetSize()-1;
        int endPosTemp = pathToAdd->GetSimplifyVertexByNum(simplVertexIndex)->GetVertexByIndex(vertexIndex)->GetCoor();


        if((_startPos == startPosTemp) && (_endPos == endPosTemp))
        {
            _pathes.AddToSet(pathToAdd);
        }
    }
}
