#ifndef CONSIDERSCAFFOLD_H
#define CONSIDERSCAFFOLD_H
#include "considerpath.h"

class ConsiderScaffold
{
private:
    SetOfRef<ConsiderPath> _consPathes;
    int _startPos;
	int _endPos;
	UniqueReadList _readList;
    int _weight;
public:
	ConsiderScaffold();
	void AddPath(ConsiderPath *consPath)
	{

		_readList.AddSetOfReadList(consPath->GetPath()->GetReadList());
		_consPathes.AddToSet(consPath);
	}

	void CountStartAndEnd();

	ConsiderPath* GetPathByNum(int index)
	{

	   return _consPathes.GetItemByNum(index);
	}

	int GetSizeOfPathesSet()
	{
		return _consPathes.GetSizeOfSet();
	}

	void Clear()
	{
		for(int i = 0;i<_consPathes.GetSizeOfSet();i++)
		{
			ConsiderPath *consPath = _consPathes.GetItemByNum(i);

			delete consPath;
		}
	}

	int GetStartPos()
	{
		return _startPos;
	}

	int GetEndPos()
	{
		return _endPos;
	}

    void SetWeight(int weight)
    {
        _weight = weight;
    }

    int GetWeight()
    {
        return _weight;
    }

	int CountConnectivityToPathLeft(ConsiderPath* consPathFrom);
	int CountConnectivityToPathRight(ConsiderPath* consPathTo);
    int CountConnectivityToScaffoldLeft(ConsiderScaffold* consScaffFrom);
    int CountConnectivityToScaffoldRight(ConsiderScaffold* consScaffTo);
	int CheckIsTwoPathMoreConnectivityToScaffold(ConsiderPath *firstPath, ConsiderPath *secondPath);

	long int CheckConnectionBeetweenScaffolds(ConsiderScaffold *scaffB);

	std::string GetReadNameByNum(int index)
	{
		return _readList.GetReadList().GetRefItemByNum(index)->GetSequenceName();
	};

	int GetSizeOfReadList()
	{
		return _readList.GetReadList().GetSizeOfSet();
	};

	SetOfFastqSeqRecords GetReadList()
	{
		return _readList.GetReadList();
	};

	UniqueReadList GetUniqueReadList()
	{
		return _readList;
	};

    bool MergeScaffold(ConsiderScaffold *scaff);

    bool CheckEqualityOfScaffold(ConsiderScaffold *scaff,int iIndex, int jIndex);



};

#endif // CONSIDERSCAFFOLD_H
