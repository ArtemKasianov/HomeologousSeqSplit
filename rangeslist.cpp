#include "rangeslist.h"
#include <math.h>;

RangesList::RangesList()
{
}

void RangesList::Clear()
{
    for(int i = 0; i < _rangesList.GetSizeOfSet();i++)
    {
        int *currRange = _rangesList.GetItemByNum(i);

        if(currRange != NULL)
        {
            delete currRange;
        }
    }
}

void RangesList::AddRange(int range)
{
    int *tempPtr = new int();

    *tempPtr = range;

    _rangesList.AddToSet(tempPtr);
}

void RangesList::CountRanges(Path *pathA, Path *pathB)
{
    for(int i = 0; i < pathA->GetSizeOfSimplifyVertexSet();i++)
    {

        for(int j = 0; j < pathA->GetSimplifyVertexByNum(i)->GetVertexSetSize();j++)
        {

            Vertex *currVertexA = pathA->GetSimplifyVertexByNum(i)->GetVertexByIndex(j);



            for(int m = 0; m < pathB->GetSizeOfSimplifyVertexSet();m++)
            {
                for(int k = 0; k < pathB->GetSimplifyVertexByNum(m)->GetVertexSetSize();k++)
                {

                    Vertex *currVertexB = pathB->GetSimplifyVertexByNum(m)->GetVertexByIndex(k);

                    AddRange(abs(currVertexA->GetCoor()-currVertexB->GetCoor()));


                }
            }
          //  return;

        }


    }
}

void RangesList::CountRanges(ConsiderScaffold *scaffoldA, ConsiderScaffold *scaffoldB)
{
    for(int i = 0; i < scaffoldA->GetSizeOfPathesSet();i++)
    {
        Path *currPathA = scaffoldA->GetPathByNum(i)->GetPath();
        for(int j = 0; j < scaffoldB->GetSizeOfPathesSet();j++)
        {
            Path *currPathB = scaffoldB->GetPathByNum(j)->GetPath();

            CountRanges(currPathA,currPathB);
        }


    }
}


void RangesList::CountRanges(ConsiderScaffold *scaffold, Path *path)
{
    for(int i = 0; i < scaffold->GetSizeOfPathesSet();i++)
    {
        Path *currPathA = scaffold->GetPathByNum(i)->GetPath();
        CountRanges(currPathA,path);


    }
}


void RangesList::PrintRanges(fstream &fileToWrite)
{
    for(int i = 0; i < _rangesList.GetSizeOfSet();i++)
    {
        int currRange = *(_rangesList.GetItemByNum(i));
        fileToWrite << currRange<<"\n";
    }
}
