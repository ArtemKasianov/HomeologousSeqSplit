#include "prescaffold.h"

PreScaffold::PreScaffold()
{
}


void PreScaffold::AddPath(Path *pathA)
{
    for(int i = 0; i < _pathes.GetSizeOfSet();i++)
    {
        Path *currTestPath = _pathes.GetItemByNum(i);
        if(currTestPath == pathA)
        {
            return;
        }

    }
    SetOfRef<Path> pathSet = FindConnectedToThisPathPathes(pathA);

    for(int i = 0; i < pathSet.GetSizeOfSet();i++)
    {
        AddPath(pathSet.GetItemByNum(i));
    }
}

SetOfRef<Path> PreScaffold::FindConnectedToThisPathPathes(Path *pathA)
{

}
