#include "scaffold.h"

Scaffold::Scaffold()
{
}

void Scaffold::PrintScaffold(fstream &scaffFile)
{
    std::string startVertexName = _pathes.GetItemByNum(0)->GetSimplifyVertexByNum(0)->GetName();
    int lastPathIndex =  _pathes.GetSizeOfSet()-1;
    int lastSVertexIndex = _pathes.GetItemByNum(lastPathIndex)->GetSizeOfSimplifyVertexSet()-1;
    int lastVertexIndex = _pathes.GetItemByNum(lastPathIndex)->GetSimplifyVertexByNum(lastSVertexIndex)->GetVertexSetSize()-1;
    std::string endVertexName = _pathes.GetItemByNum(lastPathIndex)->GetSimplifyVertexByNum(lastSVertexIndex)->GetName();

    scaffFile << ">Scaffold_" <<startVertexName << "_" << endVertexName << "\n";

    for(int i = 0; i < _pathes.GetSizeOfSet();i++)
    {
        _pathes.GetItemByNum(i)->PrintPath(scaffFile);
    }


}
