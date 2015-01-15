#ifndef PATH_H
#define PATH_H

#include "Vertex.h";


class Path
{
    SetOfRef<SimplifyVertex> _vertexies;
    SetOf<int> _sReadWeights;
    SetOf<int> _peReadWeights;
    UniqueReadList _readList;

    UniqueReadList _currReadList;
    UniqueReadList _fullReadList;

    int _indexInResPath;
    SetOf<int> _weightOfConnToAnotherPathes;






public:

    Path()
    {

    }

    Path(Path* startPath);




    UniqueReadList* GetCurrReadList()
    {
        return &_currReadList;
    }

    UniqueReadList* GetFullReadList()
    {
        return &_fullReadList;
    }

    void AddVertex(SimplifyVertex *vertexToAdd)
    {

        _readList.AddSetOfReadList(vertexToAdd->GetReadList());
        _vertexies.AddToSet(vertexToAdd);
    }

    void AddVertexAndCreatingNewPath(SimplifyVertex *vertexToAdd);

    void AddSReadWeights(int valToAdd)
    {
        _sReadWeights.AddToSet(valToAdd);
    }

    void AddPEReadWeights(int valToAdd)
    {
        _peReadWeights.AddToSet(valToAdd);
    }

    int GetSizeOfSimplifyVertexSet()
    {
        return _vertexies.GetSizeOfSet();
    }

    std::string GetName();

    int CompDiffConnWithEqualLastVertex(Path* compPath, double minConn);
    int CheckEqualityOfPathes(Path* pathToCompare,int shiftFromEnd);

    int CheckVertexConnectivityByPEReads(SimplifyVertex *vertexToCheck);
    int CheckVertexConnectivityByPEReads(SimplifyVertex *vertexToCheck, fstream &debugFile);
    int CheckVertexConnectivityBySReads(SimplifyVertex *vertexToCheck);

    int CheckPathConnectivityByPEReads(Path *pathTOCheck);
    double CountConnectivityByPEReads(Path* connTo);
    int CheckIsTwoPathMoreConnectivityToAnotherPath(Path* compPath,Path *toPath, double minConn);
    void CheckIsTwoPathMoreConnectivityToAnotherPath(Path* compPath,Path *toPath,double &weightThis, double &weightComp);

    SimplifyVertex* GetSimplifyVertexByNum(int index)
    {
        return _vertexies.GetItemByNum(index);
    }
   // int CompDiffConnWithEqualLastVertex(Path* compPath, double minConn);
    void PrintPath(fstream &pathFile);

    std::string GetReadNameByNum(int index)
    {
        return _readList.GetReadList().GetRefItemByNum(index)->GetSequenceName();
    }

    int GetSizeOfReadList()
    {
        return _readList.GetReadList().GetSizeOfSet();
    }

	SetOfFastqSeqRecords GetReadList()
    {
        return _readList.GetReadList();
	}

	UniqueReadList GetUniqueReadList()
	{
		return _readList;
    }

    int GetIndexInResPath()
    {
        return _indexInResPath;
    }

    void SetIndexInResPath(int index)
    {
        _indexInResPath = index;
    }


    void AddConnWeightToAnotherPath(int weight);


    int GetSizeOfResPathSet()
    {
        return _weightOfConnToAnotherPathes.GetSizeOfSet();
    }

    int GetConnWeightToAnotherPathByNum(int index)
    {
        return *_weightOfConnToAnotherPathes.GetRefItemByNum(index);
    }

    void AddEndedReadsToFullReadList();
    void AddStartedReadsToCurrReadList();
    void AddAllCurrReadsToFullReadList();

    void AddCurrReadList(UniqueReadList *currReadList);
    void AddFullReadList(UniqueReadList *fullReadList);

    bool CheckInclusionInPath(Path *path);
};


typedef SetOf<Path> SetOfPathes;


#endif // PATH_H
