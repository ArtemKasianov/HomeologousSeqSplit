#include "connectioncomponent.h"


void UniqueReadList::AddSetOfReadList(SetOfFastqSeqRecords setFastqReadList)
{
    int sizeOfSet = setFastqReadList.GetSizeOfSet();

    for(int i=0;i<sizeOfSet;i++)
    {
        this->Add(setFastqReadList.GetItemByNum(i));
    }   
}

void UniqueReadList::AddSetOfReadList(SetOfFastqSeqRecordsRef setFastqReadList)
{
    int sizeOfSet = setFastqReadList.GetSizeOfSet();

    for(int i=0;i<sizeOfSet;i++)
    {
        this->Add(*(setFastqReadList.GetItemByNum(i)));
    }
}

int UniqueReadList::FindIntersectionOfLists(SetOfFastqSeqRecords readListB)
{
    int countOfIntersected = 0;

    for(int i = 0; i < readListB.GetSizeOfSet();i++)
    {
        if(this->_existedReadsList.find(readListB.GetItemByNum(i).GetSequenceName()) != this->_existedReadsList.end())
        {
            countOfIntersected++;
        }
    }

    return countOfIntersected;

}

int UniqueReadList::FindIntersectionOfListsByPE(SetOfFastqSeqRecords readListB)
{
    int countOfIntersected = 0;

    int sizeOfSetB = readListB.GetSizeOfSet();

    for(int iB = 0;iB < sizeOfSetB;iB++)
    {
        std::string seqNamB = readListB.GetItemByNum(iB).GetSequenceName();
        int sizeOfSeqB = seqNamB.length();
        int posDishB = sizeOfSeqB - 7;
        std::string basFileNamB = seqNamB.substr(0,posDishB);
        std::string numB = seqNamB.substr(posDishB+1,1);
        std::string nameToSearch = basFileNamB;
        if(numB == "1")
        {
            nameToSearch = nameToSearch + "_2:N:0:";

        }
        else
        {
            nameToSearch = nameToSearch + "_1:N:0:";
        }

        if(ExistThisRead(nameToSearch))
        {
            countOfIntersected++;
        }
    }





    return countOfIntersected;

}

int UniqueReadList::FindIntersectionOfLists(SetOfFastqSeqRecordsRef readListB)
{
    int countOfIntersected = 0;

    for(int i = 0; i < readListB.GetSizeOfSet();i++)
    {
        if(this->_existedReadsList.find(readListB.GetItemByNum(i)->GetSequenceName()) != this->_existedReadsList.end())
        {
            countOfIntersected++;
        }
    }

    return countOfIntersected;

}

int UniqueReadList::FindIntersectionOfListsByPE(SetOfFastqSeqRecordsRef readListB)
{
    int countOfIntersected = 0;

    int sizeOfSetB = readListB.GetSizeOfSet();

    for(int iB = 0;iB < sizeOfSetB;iB++)
    {
        std::string seqNamB = readListB.GetItemByNum(iB)->GetSequenceName();
        int sizeOfSeqB = seqNamB.length();
        int posDishB = sizeOfSeqB - 7;
        std::string basFileNamB = seqNamB.substr(0,posDishB);
        std::string numB = seqNamB.substr(posDishB+1,1);
        std::string nameToSearch = basFileNamB;
        if(numB == "1")
        {
            nameToSearch = nameToSearch + "_2:N:0:";

        }
        else
        {
            nameToSearch = nameToSearch + "_1:N:0:";
        }

        if(ExistThisRead(nameToSearch))
        {
            countOfIntersected++;
        }
    }





    return countOfIntersected;

}

void UniqueReadList::PrintToStdIn()
{
    int sizeOfSet = _setOfReads.GetSizeOfSet();
    cout << "startOfList\n";
    for(int i = 0;i < sizeOfSet;i++)
    {
        cout << _setOfReads.GetItemByNum(i).GetSequenceName() << "\n";
    }

    cout << "endOfList\n";
}


int UniqueReadList::PrintToFastqFile(std::string fileName)
{
    int sizeOfSet = _setOfReads.GetSizeOfSet();
    FILE *fileToWrite = fopen(fileName.c_str(),"w");
    if(fileToWrite == NULL)
    {
        return ErrorHappens;
    }
    for(int i = 0;i < sizeOfSet;i++)
    {
        _setOfReads.GetItemByNum(i).WriteToFileSeq(fileToWrite);
    }
    fclose(fileToWrite);
    return AllOk;
}

int UniqueReadList::PrintToFastqFile(std::string fileName, UniqueReadList allReads, UniqueReadList secGaploid)
{
    int sizeOfSet = allReads.GetReadList().GetSizeOfSet();
    FILE *fileToWrite = fopen(fileName.c_str(),"w");
    if(fileToWrite == NULL)
    {
        return ErrorHappens;
    }
    for(int i = 0;i < sizeOfSet;i++)
    {

        if(!(secGaploid.ExistThisRead(allReads.GetReadList().GetItemByNum(i).GetSequenceName())))
        {
            allReads.GetReadList().GetItemByNum(i).WriteToFileSeq(fileToWrite);
        }
    }
    fclose(fileToWrite);
    return AllOk;
}


int UniqueReadList::PrintToFastqFile(FILE *fileToWrite)
{
    int sizeOfSet = _setOfReads.GetSizeOfSet();
    if(fileToWrite == NULL)
    {
        return ErrorHappens;
    }
    for(int i = 0;i < sizeOfSet;i++)
    {
        _setOfReads.GetItemByNum(i).WriteToFile(fileToWrite);
    }

    return AllOk;
}

UniqueReadListRef UniqueReadList::DiversityFromReadList(UniqueReadList readListB)
{
    int sizeOfA = _setOfReads.GetSizeOfSet();
    UniqueReadListRef retVal;

    for(int i = 0; i < sizeOfA;i++)
    {
        if(!(readListB.ExistThisRead(_setOfReads.GetItemByNum(i).GetSequenceName())))
        {
            retVal.Add(_setOfReads.GetRefItemByNum(i));
        }
    }

    return retVal;

}

UniqueReadListRef UniqueReadList::DiversityFromReadList(UniqueReadListRef readListB)
{
    int sizeOfA = _setOfReads.GetSizeOfSet();
    UniqueReadListRef retVal;

    for(int i = 0; i < sizeOfA;i++)
    {
        if(!(readListB.ExistThisRead(_setOfReads.GetItemByNum(i).GetSequenceName())))
        {
            retVal.Add(_setOfReads.GetRefItemByNum(i));
        }
    }

    return retVal;
}

UniqueReadListRef UniqueReadList::UnionReadLists(UniqueReadListRef readListB)
{
    UniqueReadListRef retVal;
    retVal.AddSetOfReadList(&(_setOfReads));
    retVal.AddSetOfReadList(readListB.GetReadList());

    return retVal;

}

UniqueReadListRef UniqueReadList::UnionReadLists(UniqueReadList readListB)
{
    UniqueReadListRef retVal;
    retVal.AddSetOfReadList(&(_setOfReads));
    retVal.AddSetOfReadList(readListB.GetReadListRef());

    return retVal;
}




SetOfFastqSeqRecordsRef UniqueReadList::DiversityFromReadListFastqSeq(UniqueReadList readListB)
{
    int sizeOfA = _setOfReads.GetSizeOfSet();
    UniqueReadListRef retVal;

    for(int i = 0; i < sizeOfA;i++)
    {
        if(!(readListB.ExistThisRead(_setOfReads.GetItemByNum(i).GetSequenceName())))
        {
            retVal.Add(_setOfReads.GetRefItemByNum(i));
        }
    }

    return retVal.GetReadList();

}

SetOfFastqSeqRecordsRef UniqueReadList::DiversityFromReadListFastqSeq(UniqueReadListRef readListB)
{
    int sizeOfA = _setOfReads.GetSizeOfSet();
    UniqueReadListRef retVal;

    for(int i = 0; i < sizeOfA;i++)
    {
        if(!(readListB.ExistThisRead(_setOfReads.GetItemByNum(i).GetSequenceName())))
        {
            retVal.Add(_setOfReads.GetRefItemByNum(i));
        }
    }

    return retVal.GetReadList();
}

SetOfFastqSeqRecordsRef UniqueReadList::UnionReadListsFastqSeq(UniqueReadListRef readListB)
{
    UniqueReadListRef retVal;
    retVal.AddSetOfReadList(&(_setOfReads));
    retVal.AddSetOfReadList(readListB.GetReadList());

    return retVal.GetReadList();

}

SetOfFastqSeqRecordsRef UniqueReadList::UnionReadListsFastqSeq(UniqueReadList readListB)
{
    UniqueReadListRef retVal;
    retVal.AddSetOfReadList(&(_setOfReads));
    retVal.AddSetOfReadList(readListB.GetReadListRef());

    return retVal.GetReadList();
}


//***********************************************************************************************





void UniqueReadListRef::AddSetOfReadList(SetOfFastqSeqRecordsRef setFastqReadList)
{
    int sizeOfSet = setFastqReadList.GetSizeOfSet();

    for(int i=0;i<sizeOfSet;i++)
    {
        this->Add(setFastqReadList.GetItemByNum(i));
    }
}

void UniqueReadListRef::AddSetOfReadList(SetOfFastqSeqRecords *setFastqReadList)
{
    int sizeOfSet = setFastqReadList->GetSizeOfSet();

    for(int i=0;i<sizeOfSet;i++)
    {
        this->Add(setFastqReadList->GetRefItemByNum(i));
    }
}

int UniqueReadListRef::FindIntersectionOfLists(SetOfFastqSeqRecords readListB)
{
    int countOfIntersected = 0;

    for(int i = 0; i < readListB.GetSizeOfSet();i++)
    {
        if(this->_existedReadsList.find(readListB.GetItemByNum(i).GetSequenceName()) != this->_existedReadsList.end())
        {
            countOfIntersected++;
        }
    }

    return countOfIntersected;

}

int UniqueReadListRef::FindIntersectionOfLists(SetOfFastqSeqRecordsRef readListB)
{
    int countOfIntersected = 0;

    for(int i = 0; i < readListB.GetSizeOfSet();i++)
    {
        if(this->_existedReadsList.find(readListB.GetItemByNum(i)->GetSequenceName()) != this->_existedReadsList.end())
        {
            countOfIntersected++;
        }
    }

    return countOfIntersected;

}


int UniqueReadListRef::FindIntersectionOfListsByPE(SetOfFastqSeqRecords readListB)
{
    int countOfIntersected = 0;
    int sizeOfSetB = readListB.GetSizeOfSet();

    for(int iB = 0;iB < sizeOfSetB;iB++)
    {
        std::string seqNamB = readListB.GetItemByNum(iB).GetSequenceName();
        int sizeOfSeqB = seqNamB.length();
        int posDishB = sizeOfSeqB - 7;
        std::string basFileNamB = seqNamB.substr(0,posDishB);
        std::string numB = seqNamB.substr(posDishB+1,1);
        std::string nameToSearch = basFileNamB;
        if(numB == "1")
        {
            nameToSearch = nameToSearch + "_2:N:0:";

        }
        else
        {
            nameToSearch = nameToSearch + "_1:N:0:";
        }

        if(ExistThisRead(nameToSearch))
        {
            countOfIntersected++;
        }
    }



    return countOfIntersected;

}


int UniqueReadListRef::FindIntersectionOfListsByPE(SetOfFastqSeqRecordsRef readListB)
{
    int countOfIntersected = 0;
    int sizeOfSetB = readListB.GetSizeOfSet();

    for(int iB = 0;iB < sizeOfSetB;iB++)
    {
        std::string seqNamB = readListB.GetItemByNum(iB)->GetSequenceName();
        int sizeOfSeqB = seqNamB.length();
        int posDishB = sizeOfSeqB - 7;
        std::string basFileNamB = seqNamB.substr(0,posDishB);
        std::string numB = seqNamB.substr(posDishB+1,1);
        std::string nameToSearch = basFileNamB;
        if(numB == "1")
        {
            nameToSearch = nameToSearch + "_2:N:0:";

        }
        else
        {
            nameToSearch = nameToSearch + "_1:N:0:";
        }

        if(ExistThisRead(nameToSearch))
        {
            countOfIntersected++;
        }
    }



    return countOfIntersected;

}

void UniqueReadListRef::PrintToStdIn()
{
    int sizeOfSet = _setOfReads.GetSizeOfSet();
    cout << "startOfList\n";
    for(int i = 0;i < sizeOfSet;i++)
    {
        cout << _setOfReads.GetItemByNum(i)->GetSequenceName() << "\n";
    }

    cout << "endOfList\n";
}


int UniqueReadListRef::PrintToFastqFile(std::string fileName)
{
    int sizeOfSet = _setOfReads.GetSizeOfSet();
    FILE *fileToWrite = fopen(fileName.c_str(),"w");
    if(fileToWrite == NULL)
    {
        return ErrorHappens;
    }
    for(int i = 0;i < sizeOfSet;i++)
    {
        _setOfReads.GetItemByNum(i)->WriteToFileSeq(fileToWrite);
    }
    fclose(fileToWrite);
    return AllOk;
}




int UniqueReadListRef::PrintToFastqFile(FILE *fileToWrite)
{
    int sizeOfSet = _setOfReads.GetSizeOfSet();
    if(fileToWrite == NULL)
    {
        return ErrorHappens;
    }
    for(int i = 0;i < sizeOfSet;i++)
    {
        _setOfReads.GetItemByNum(i)->WriteToFile(fileToWrite);
    }

    return AllOk;
}



UniqueReadListRef UniqueReadListRef::DiversityFromReadList(UniqueReadListRef readListB)
{
    int sizeOfA = _setOfReads.GetSizeOfSet();
    UniqueReadListRef retVal;

    for(int i = 0; i < sizeOfA;i++)
    {
        if(!(readListB.ExistThisRead(_setOfReads.GetItemByNum(i)->GetSequenceName())))
        {
            retVal.Add(_setOfReads.GetItemByNum(i));
        }
    }

    return retVal;
}


UniqueReadListRef UniqueReadListRef::DiversityFromReadListIn(UniqueReadListRef readListB)
{
    int sizeOfA = _setOfReads.GetSizeOfSet();
    UniqueReadListRef retVal;

    for(int i = 0; i < sizeOfA;i++)
    {
        if(!(readListB.ExistThisRead(_setOfReads.GetItemByNum(i)->GetSequenceName())))
        {
            retVal.Add(_setOfReads.GetItemByNum(i));
        }
    }

    Clear();

    AddSetOfReadList(retVal.GetReadList());

    return retVal;
}



UniqueReadListRef UniqueReadListRef::UnionReadLists(UniqueReadListRef readListB)
{
    UniqueReadListRef retVal;
    retVal.AddSetOfReadList(_setOfReads);
    retVal.AddSetOfReadList(readListB.GetReadList());

    return retVal;

}






SetOfFastqSeqRecordsRef UniqueReadListRef::DiversityFromReadListFastqSeq(UniqueReadListRef readListB)
{
    int sizeOfA = _setOfReads.GetSizeOfSet();
    UniqueReadListRef retVal;

    for(int i = 0; i < sizeOfA;i++)
    {
        if(!(readListB.ExistThisRead(_setOfReads.GetItemByNum(i)->GetSequenceName())))
        {
            retVal.Add(_setOfReads.GetItemByNum(i));
        }
    }

    return retVal.GetReadList();
}

SetOfFastqSeqRecordsRef UniqueReadListRef::UnionReadListsFastqSeq(UniqueReadListRef readListB)
{
    UniqueReadListRef retVal;
    retVal.AddSetOfReadList(_setOfReads);
    retVal.AddSetOfReadList(readListB.GetReadList());

    return retVal.GetReadList();

}














int Diploid::FindIntersecAndSetCorrectOrder(Diploid* diploidA, fstream &fstrToStore)
{
    int a00 = this->_firstGaploidReadList.FindIntersectionOfLists(diploidA->GetFirstGaploid()->GetReadList());
    int a01 = this->_firstGaploidReadList.FindIntersectionOfLists(diploidA->GetSecondGaploid()->GetReadList());
    int a10 = this->_secondGaploidReadList.FindIntersectionOfLists(diploidA->GetFirstGaploid()->GetReadList());
    int a11 = this->_secondGaploidReadList.FindIntersectionOfLists(diploidA->GetSecondGaploid()->GetReadList());
    fstrToStore <<a00 << " " << a01 << " " << a10 << " " << a11;
    if((a00 > a01) && (a11 > a10))
    {

    }
    else if((a00 < a01) && (a11 < a10))
    {
        diploidA->Swap();
    }
    else
    {
       /*cout << "a00=" << a00 << "\n";
       cout << "a01=" << a01 << "\n";
       cout << "a10=" << a10 << "\n";
       cout << "a11=" << a11 << "\n";*/ 
	return ErrorHappens;
    }

    return AllOk;
}

int Diploid::FindIntersecAndSetCorrectOrder(Diploid* diploidA)
{
    int a00 = this->_firstGaploidReadList.FindIntersectionOfLists(diploidA->GetFirstGaploid()->GetReadList());
    int a01 = this->_firstGaploidReadList.FindIntersectionOfLists(diploidA->GetSecondGaploid()->GetReadList());
    int a10 = this->_secondGaploidReadList.FindIntersectionOfLists(diploidA->GetFirstGaploid()->GetReadList());
    int a11 = this->_secondGaploidReadList.FindIntersectionOfLists(diploidA->GetSecondGaploid()->GetReadList());
    if((a00 > a01) && (a11 > a10))
    {

    }
    else if((a00 < a01) && (a11 < a10))
    {
        diploidA->Swap();
    }
    else
    {
       /*cout << "a00=" << a00 << "\n";
       cout << "a01=" << a01 << "\n";
       cout << "a10=" << a10 << "\n";
       cout << "a11=" << a11 << "\n";*/
    return ErrorHappens;
    }

    return AllOk;
}

int ConnectionComponent::AddDiploid(Diploid diploidA)
{
    if(_lastDiploid.GetFirstGaploid()->GetReadList().GetSizeOfSet() == 0)
    {
        _firstGaploidReadList.AddSetOfReadList(diploidA.GetFirstGaploid()->GetReadList());
        _secondGaploidReadList.AddSetOfReadList(diploidA.GetSecondGaploid()->GetReadList());
        _conflPointFirstGaploid = diploidA.GetSetOfConflictPointsFirstGaploid();
        _conflPointSecondGaploid = diploidA.GetSetOfConflictPointsSecondGaploid();
        _lastDiploid = diploidA;
        return AllOk;
    }
    int isIntersect = _lastDiploid.FindIntersecAndSetCorrectOrder(&diploidA);
    if(isIntersect == ErrorHappens)
    {
        return ErrorHappens;
    }


    _firstGaploidReadList.AddSetOfReadList(diploidA.GetFirstGaploid()->GetReadList());
    _secondGaploidReadList.AddSetOfReadList(diploidA.GetSecondGaploid()->GetReadList());

    SetOfConflictPoints setConflictPoint = diploidA.GetSetOfConflictPointsFirstGaploid();

    for(int z = 0; z<setConflictPoint.GetSizeOfSet();z++)
    {
        _conflPointFirstGaploid.AddToSet(setConflictPoint.GetItemByNum(z));
    }

    setConflictPoint = diploidA.GetSetOfConflictPointsSecondGaploid();

    for(int z = 0; z<setConflictPoint.GetSizeOfSet();z++)
    {
        _conflPointSecondGaploid.AddToSet(setConflictPoint.GetItemByNum(z));
    }

    _lastDiploid = diploidA;

    return AllOk;


}


int ConnectionComponent::AddDiploid(Diploid diploidA,fstream &fstrToStore)
{
    if(_lastDiploid.GetFirstGaploid()->GetReadList().GetSizeOfSet() == 0)
    {
        _firstGaploidReadList.AddSetOfReadList(diploidA.GetFirstGaploid()->GetReadList());
        _secondGaploidReadList.AddSetOfReadList(diploidA.GetSecondGaploid()->GetReadList());
        _conflPointFirstGaploid = diploidA.GetSetOfConflictPointsFirstGaploid();
        _conflPointSecondGaploid = diploidA.GetSetOfConflictPointsSecondGaploid();
        _lastDiploid = diploidA;
        return AllOk;
    }
    int isIntersect = _lastDiploid.FindIntersecAndSetCorrectOrder(&diploidA,fstrToStore);
    if(isIntersect == ErrorHappens)
    {
        return ErrorHappens;
    }


    _firstGaploidReadList.AddSetOfReadList(diploidA.GetFirstGaploid()->GetReadList());
    _secondGaploidReadList.AddSetOfReadList(diploidA.GetSecondGaploid()->GetReadList());

    SetOfConflictPoints setConflictPoint = diploidA.GetSetOfConflictPointsFirstGaploid();

    for(int z = 0; z<setConflictPoint.GetSizeOfSet();z++)
    {
        _conflPointFirstGaploid.AddToSet(setConflictPoint.GetItemByNum(z));
    }

    setConflictPoint = diploidA.GetSetOfConflictPointsSecondGaploid();

    for(int z = 0; z<setConflictPoint.GetSizeOfSet();z++)
    {
        _conflPointSecondGaploid.AddToSet(setConflictPoint.GetItemByNum(z));
    }

    _lastDiploid = diploidA;

    return AllOk;


}

void ConnectionComponent::PrintToStdIn()
{
    cout << "startConnectionComponent\n";
    cout << "startFirstGaploid\n";
    _firstGaploidReadList.PrintToStdIn();
    cout << "endFirstGaploid\n";
    cout << "startSecondGaploid\n";
    _secondGaploidReadList.PrintToStdIn();
    cout << "endSecondGaploid\n";
}

int ConnectionComponent::PrintToFastqFiles(std::string baseFileName, UniqueReadList allReads)
{

    std::string fileName1Gaploid = baseFileName+"_1.fastq";
    std::string fileName2Gaploid = baseFileName+"_2.fastq";
    int retValue = AllOk;
    int retValOfPrintFunct = _firstGaploidReadList.PrintToFastqFile(fileName1Gaploid,allReads,_secondGaploidReadList);
    retValue = (retValOfPrintFunct==ErrorHappens)?ErrorHappens:retValue;
    retValOfPrintFunct = _secondGaploidReadList.PrintToFastqFile(fileName2Gaploid,allReads,_firstGaploidReadList);
    retValue = (retValOfPrintFunct==ErrorHappens)?ErrorHappens:retValue;
    return retValue;

}

int ConnectionComponent::PrintToFastqFiles(std::string baseFileName)
{

    std::string fileName1Gaploid = baseFileName+"_1.fastq";
    std::string fileName2Gaploid = baseFileName+"_2.fastq";
    int retValue = AllOk;
    int retValOfPrintFunct = _firstGaploidReadList.PrintToFastqFile(fileName1Gaploid);
    retValue = (retValOfPrintFunct==ErrorHappens)?ErrorHappens:retValue;
    retValOfPrintFunct = _secondGaploidReadList.PrintToFastqFile(fileName2Gaploid);
    retValue = (retValOfPrintFunct==ErrorHappens)?ErrorHappens:retValue;
    return retValue;

}







void ConnectionComponent::Swap()
{
    _lastDiploid.Swap();
    UniqueReadList temp = _firstGaploidReadList;
    _secondGaploidReadList = _firstGaploidReadList;
    _firstGaploidReadList = _secondGaploidReadList;
}

int ConnectionComponent::FindIntersectionByPEAndSetCorrectOrder(ConnectionComponent *conCompB)
{
    int a00 = this->_firstGaploidReadList.FindIntersectionOfListsByPE(conCompB->GetFirstGaploid()->GetReadList());
    int a01 = this->_firstGaploidReadList.FindIntersectionOfListsByPE(conCompB->GetSecondGaploid()->GetReadList());
    int a10 = this->_secondGaploidReadList.FindIntersectionOfListsByPE(conCompB->GetFirstGaploid()->GetReadList());
    int a11 = this->_secondGaploidReadList.FindIntersectionOfListsByPE(conCompB->GetSecondGaploid()->GetReadList());
    
    if(a00 > a01)
    {
    
    }
    else if(a00 < a01)
    {
    
    }
    else
    {
    	
    }
    if((a00 > a01) && (a11 > a10))
    {

    }
    else if((a00 < a01) && (a11 < a10))
    {
        conCompB->Swap();
    }
    else
    {
        return ErrorHappens;
    }

    return AllOk;
}

bool UniqueReadList::ExistThisRead(std::string readName)
{
    bool found = false;
    if(this->_existedReadsList.find(readName) != this->_existedReadsList.end())
    {
        found = true;
    }
    return found;
}


bool UniqueReadListRef::ExistThisRead(std::string readName)
{
    bool found = false;
    if(this->_existedReadsList.find(readName) != this->_existedReadsList.end())
    {
        found = true;
    }
    return found;
}







