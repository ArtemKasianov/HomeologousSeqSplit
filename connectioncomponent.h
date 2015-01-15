#ifndef CONNECTIONCOMPONENT_H
#define CONNECTIONCOMPONENT_H

#include "FilesFormats.h"
#include "ConflictPoint.h"

class UniqueReadListRef
{
private:
    SetOfFastqSeqRecordsRef _setOfReads;
    HashStringInt _existedReadsList;

public:
    UniqueReadListRef():_setOfReads(),_existedReadsList()
    {

    }

    void Add(FastqSequenceRecord* addingValue)
    {

        if(_existedReadsList.find(addingValue->GetSequenceName()) == _existedReadsList.end())
        {
           _setOfReads.AddToSet(addingValue);
           _existedReadsList[addingValue->GetSequenceName()] = 1;
        }
    }

    void Clear()
    {
        _setOfReads.Clear();
        _existedReadsList.clear();
    }

    SetOfFastqSeqRecordsRef GetReadList() const
    {
        return _setOfReads;
    }

    bool ExistThisRead(std::string readName);

    int FindIntersectionOfLists(SetOfFastqSeqRecordsRef readListB);
    int FindIntersectionOfLists(SetOfFastqSeqRecords readListB);

    void PrintToStdIn();
    int PrintToFastqFile(std::string fileName);
    int PrintToFastqFile(FILE *fileToWrite);
    void AddSetOfReadList(SetOfFastqSeqRecordsRef readListToAdd);
    void AddSetOfReadList(SetOfFastqSeqRecords *readListToAdd);
    int FindIntersectionOfListsByPE(SetOfFastqSeqRecords readListB);
    int FindIntersectionOfListsByPE(SetOfFastqSeqRecordsRef readListB);
    UniqueReadListRef DiversityFromReadList(UniqueReadListRef readListB);
    UniqueReadListRef DiversityFromReadListIn(UniqueReadListRef readListB);
    SetOfFastqSeqRecordsRef DiversityFromReadListFastqSeq(UniqueReadListRef readListB);
    UniqueReadListRef UnionReadLists(UniqueReadListRef readListB);
    SetOfFastqSeqRecordsRef UnionReadListsFastqSeq(UniqueReadListRef readListB);

};

class UniqueReadList
{
private:
    SetOfFastqSeqRecords _setOfReads;
    HashStringInt _existedReadsList;

public:
    UniqueReadList():_setOfReads(),_existedReadsList()
    {

    }

    void Clear()
    {
        _setOfReads.Clear();
        _existedReadsList.clear();
    }

    void Add(FastqSequenceRecord addingValue)
    {

        if(_existedReadsList.find(addingValue.GetSequenceName()) == _existedReadsList.end())
        {
           _setOfReads.AddToSet(addingValue);
           _existedReadsList[addingValue.GetSequenceName()] = 1;
        }
    }

    SetOfFastqSeqRecords GetReadList() const
    {
        return _setOfReads;
    }

    SetOfFastqSeqRecords* GetReadListRef()
    {
        return &_setOfReads;
    }

    bool ExistThisRead(std::string readName);

    int FindIntersectionOfLists(SetOfFastqSeqRecords readListB);
    int FindIntersectionOfLists(SetOfFastqSeqRecordsRef readListB);

    void PrintToStdIn();
    int PrintToFastqFile(std::string fileName);
    int PrintToFastqFile(std::string fileName,UniqueReadList allReads, UniqueReadList secGaploid);
    int PrintToFastqFile(FILE *fileToWrite);
    void AddSetOfReadList(SetOfFastqSeqRecords readListToAdd);
    void AddSetOfReadList(SetOfFastqSeqRecordsRef readListToAdd);
    int FindIntersectionOfListsByPE(SetOfFastqSeqRecords readListB);
    int FindIntersectionOfListsByPE(SetOfFastqSeqRecordsRef readListB);
    UniqueReadListRef DiversityFromReadList(UniqueReadListRef readListB);
    UniqueReadListRef DiversityFromReadList(UniqueReadList readListB);
    UniqueReadListRef UnionReadLists(UniqueReadListRef readListB);
    UniqueReadListRef UnionReadLists(UniqueReadList readListB);

    SetOfFastqSeqRecordsRef DiversityFromReadListFastqSeq(UniqueReadListRef readListB);
    SetOfFastqSeqRecordsRef DiversityFromReadListFastqSeq(UniqueReadList readListB);
    SetOfFastqSeqRecordsRef UnionReadListsFastqSeq(UniqueReadListRef readListB);
    SetOfFastqSeqRecordsRef UnionReadListsFastqSeq(UniqueReadList readListB);

};





class Diploid
{
private:
    UniqueReadList _firstGaploidReadList;
    UniqueReadList _secondGaploidReadList;
    SetOfConflictPoints _conflPointFirstGaploid;
    SetOfConflictPoints _conflPointSecondGaploid;

public:
    Diploid():_firstGaploidReadList(),_secondGaploidReadList()
    {

    }

    Diploid(UniqueReadList firstGaploidReadList, UniqueReadList secondGaploidReadList):_firstGaploidReadList(firstGaploidReadList),_secondGaploidReadList(secondGaploidReadList)
    {

    }

    UniqueReadList* GetFirstGaploid()
    {
        return &_firstGaploidReadList;
    }

    UniqueReadList* GetSecondGaploid()
    {
        return &_secondGaploidReadList;
    }

    void Swap()
    {
        UniqueReadList temp = _firstGaploidReadList;
        _firstGaploidReadList = _secondGaploidReadList;
        _secondGaploidReadList = temp;
    }

    void AddConflictPointToFirstGaploid(ConflictPoint conflPoint)
    {
       _conflPointFirstGaploid.AddToSet(conflPoint);
    }

    void AddConflictPointToSecondGaploid(ConflictPoint conflPoint)
    {
       _conflPointSecondGaploid.AddToSet(conflPoint);
    }

    SetOfConflictPoints GetSetOfConflictPointsFirstGaploid()
    {
       return _conflPointFirstGaploid;
    }

    SetOfConflictPoints GetSetOfConflictPointsSecondGaploid()
    {
       return _conflPointSecondGaploid;
    }

    void AddSetOfConflictPointToFirstGaploid(SetOfConflictPoints setConflPoint)
    {
        for(int i = 0; i < setConflPoint.GetSizeOfSet();i++)
        {
            _conflPointFirstGaploid.AddToSet(setConflPoint.GetItemByNum(i));
        }
    }

    void AddSetOfConflictPointToSecondGaploid(SetOfConflictPoints setConflPoint)
    {
        for(int i = 0; i < setConflPoint.GetSizeOfSet();i++)
        {
            _conflPointSecondGaploid.AddToSet(setConflPoint.GetItemByNum(i));
        }
    }

    int FindIntersecAndSetCorrectOrder(Diploid* diploidA, fstream &fstrToStore);
    int FindIntersecAndSetCorrectOrder(Diploid* diploidA);
};



class ConnectionComponent
{
private:
    UniqueReadList _firstGaploidReadList;
    UniqueReadList _secondGaploidReadList;
    Diploid _lastDiploid;
    SetOfConflictPoints _conflPointFirstGaploid;
    SetOfConflictPoints _conflPointSecondGaploid;
    


public:
    static ConnectionComponent Empty()
    {
        ConnectionComponent emptyVal;
        return emptyVal;
    }

    ConnectionComponent():_firstGaploidReadList(),_secondGaploidReadList(),_lastDiploid(),_conflPointFirstGaploid(),_conflPointSecondGaploid()
    {

    }

    ConnectionComponent(Diploid diploidToAdd):_firstGaploidReadList(),_secondGaploidReadList(),_conflPointFirstGaploid(),_conflPointSecondGaploid()
    {

        _firstGaploidReadList.AddSetOfReadList(diploidToAdd.GetFirstGaploid()->GetReadList());
        _secondGaploidReadList.AddSetOfReadList(diploidToAdd.GetSecondGaploid()->GetReadList());
        _conflPointFirstGaploid = diploidToAdd.GetSetOfConflictPointsFirstGaploid();
        _conflPointSecondGaploid = diploidToAdd.GetSetOfConflictPointsSecondGaploid();
        _lastDiploid = diploidToAdd;

    }


    UniqueReadList* GetFirstGaploid()
    {
        return &_firstGaploidReadList;
    }

    UniqueReadList* GetSecondGaploid()
    {
        return &_secondGaploidReadList;
    }

   void AddConflictPointToFirstGaploid(ConflictPoint conflPoint)
   {
      _conflPointFirstGaploid.AddToSet(conflPoint);
   }
   
   void AddConflictPointToSecondGaploid(ConflictPoint conflPoint)
   {
      _conflPointSecondGaploid.AddToSet(conflPoint);
   }
   
   SetOfConflictPoints GetSetOfConflictPointsFirstGaploid()
   {
      return _conflPointFirstGaploid;
   }
   
   SetOfConflictPoints GetSetOfConflictPointsSecondGaploid()
   {
      return _conflPointSecondGaploid;
   }

   void AddSetOfConflictPointToFirstGaploid(SetOfConflictPoints setConflPoint)
   {
       for(int i = 0; i < setConflPoint.GetSizeOfSet();i++)
       {
           _conflPointFirstGaploid.AddToSet(setConflPoint.GetItemByNum(i));
       }
   }

   void AddSetOfConflictPointToSecondGaploid(SetOfConflictPoints setConflPoint)
   {
       for(int i = 0; i < setConflPoint.GetSizeOfSet();i++)
       {
           _conflPointSecondGaploid.AddToSet(setConflPoint.GetItemByNum(i));
       }
   }

    int AddDiploid(Diploid diploidA,fstream &fstrToStore);
    int AddDiploid(Diploid diploidA);
    void PrintToStdIn();
    int PrintToFastqFiles(std::string baseFileName,UniqueReadList allReads);
    int PrintToFastqFiles(std::string baseFileName);

    void Swap();
    int FindIntersectionByPEAndSetCorrectOrder(ConnectionComponent *conCompB);


};

typedef SetOf<ConnectionComponent> SetOfConComp;



#endif // CONNECTIONCOMPONENT_H
