#include "filteredpathesset.h"

FilteredPathesSet::FilteredPathesSet(SetOfRef<Path> *oldPath)
{
    int currStartCoor = -1;
    int currEndCoor = -1;
    PathesPack *currPack = NULL;
    for(int i = 0; i<oldPath->GetSizeOfSet();i++)
    {
        Path *currPath = oldPath->GetItemByNum(i);

        int startPosTemp = currPath->GetSimplifyVertexByNum(0)->GetVertexByIndex(0)->GetCoor();

        int simplVertexIndex = currPath->GetSizeOfSimplifyVertexSet()-1;
        int vertexIndex = currPath->GetSimplifyVertexByNum(currPath->GetSizeOfSimplifyVertexSet()-1)->GetVertexSetSize()-1;
        int endPosTemp = currPath->GetSimplifyVertexByNum(simplVertexIndex)->GetVertexByIndex(vertexIndex)->GetCoor();

        if(startPosTemp >= currEndCoor)
        {
            currStartCoor = startPosTemp;
            currEndCoor = endPosTemp;
            _pathes.AddToSet(currPack);

            currPack = new PathesPack();

            currPack->AddPath(currPath);

        }
        else
        {
            if((startPosTemp == currStartCoor) && (endPosTemp == currEndCoor))
            {
                currPack->AddPath(currPath);
            }


        }

    }

}


void FilteredPathesSet::Clear()
{
    for(int i = 0; i < _pathes.GetSizeOfSet();i++)
    {
        PathesPack *currPathesPack = _pathes.GetItemByNum(i);

        if(currPathesPack != NULL)
        {
            delete currPathesPack;
        }
    }
}
