#include "sam_mapping.h"


void SAM_file::PrintCoveredCoorsOfPairsOfReads(UniqueReadList readList, long int coor, fstream &debugFile,string currScaffNam,setOfScaffNamVer &setScaffVer)
{


    if(!IsReadHitsListLoaded()) return;

    for(int i = 0; i < readList.GetReadList().GetSizeOfSet();i++)
    {
        std::string seqNamA = readList.GetReadList().GetRefItemByNum(i)->GetSequenceName();

        int posDishA = seqNamA.find_last_of("_");
        std::string basFileNamA = seqNamA.substr(0,posDishA);
        std::string numA = seqNamA.substr(posDishA+1,1);

        long int startPairCoor = -1;
        long int endPairCoor = -1;

        SetOfRead_Hit setReadHit;

        bool isReadHitFound = false;

        if(!IsReadHitsListLoaded())
        {
            setReadHit = GetSetOfReadHits();
        }
        else
        {
            setReadHit = *GetSetOfReadHitsAtPos((int)coor/1000);
        }


        for(int j = 0; j < setReadHit.GetSizeOfSet();j++)
        {
            std::string seqNamB = setReadHit.GetItemByNum(j).GetQName();

            startPairCoor = setReadHit.GetItemByNum(j).GetTStart();
            endPairCoor = setReadHit.GetItemByNum(j).GetTEnd();

            int posDishB = seqNamB.find_last_of("_");
            std::string basFileNamB = seqNamB.substr(0,posDishB);
            std::string numB = seqNamB.substr(posDishB+1,1);

            if(basFileNamA == basFileNamB)
            {

                if(numA != numB)
                {
                    isReadHitFound = true;

                    debugFile << seqNamA << " "<< seqNamB << " " << startPairCoor << " " << endPairCoor;
                    for(int k = 0; k < setScaffVer.GetSizeOfSet();k++)
                    {
                        if(setScaffVer.GetRefItemByNum(k)->_scaffName != currScaffNam)
                        {
                            if((setScaffVer.GetRefItemByNum(k)->_vertexPos > startPairCoor) && (setScaffVer.GetRefItemByNum(k)->_vertexPos < endPairCoor))
                            {
                                debugFile << " " << setScaffVer.GetRefItemByNum(k)->_scaffName;
                            }
                        }
                    }

                    debugFile <<"\n" ;



                    break;
                }

            }




        }

        if(isReadHitFound)
        {
            continue;
        }

        if(!IsReadHitsListLoaded())
        {

            debugFile << "not found \n";
            continue;
        }

        setReadHit = *GetSetOfReadHitsAtPos(((int)coor/1000) + 1);


        for(int j = 0; j < setReadHit.GetSizeOfSet();j++)
        {
            std::string seqNamB = setReadHit.GetItemByNum(j).GetQName();

            startPairCoor = setReadHit.GetItemByNum(j).GetTStart();
            endPairCoor = setReadHit.GetItemByNum(j).GetTEnd();

            int posDishB = seqNamB.find_last_of("_");
            std::string basFileNamB = seqNamB.substr(0,posDishB);
            std::string numB = seqNamB.substr(posDishB+1,1);

            if(basFileNamA == basFileNamB)
            {

                if(numA != numB)
                {
                    isReadHitFound = true;
                    debugFile << startPairCoor << " " << endPairCoor <<"\n";
                    break;
                }

            }




        }

        if(isReadHitFound)
        {
            continue;
        }



        setReadHit = *GetSetOfReadHitsAtPos(((int)coor/1000) - 1);


        for(int j = 0; j < setReadHit.GetSizeOfSet();j++)
        {
            std::string seqNamB = setReadHit.GetItemByNum(j).GetQName();

            startPairCoor = setReadHit.GetItemByNum(j).GetTStart();
            endPairCoor = setReadHit.GetItemByNum(j).GetTEnd();

            int posDishB = seqNamB.find_last_of("_");
            std::string basFileNamB = seqNamB.substr(0,posDishB);
            std::string numB = seqNamB.substr(posDishB+1,1);

            if(basFileNamA == basFileNamB)
            {

                if(numA != numB)
                {
                    isReadHitFound = true;
                    debugFile << startPairCoor << " " << endPairCoor <<"\n";
                    break;
                }

            }




        }

        if(isReadHitFound)
        {
            continue;
        }
        else
        {
            debugFile << "not found \n";
            continue;
        }

    }







}

string GetWhatStringRepresentVertex(Vertex* currVertex)
{
    string vertexStr = currVertex->GetSymbol();
    string filteredVertexStr = "";

    for(int i = 0; i<vertexStr.length();i++)
    {
        if(vertexStr[i] != '-')
        {
            filteredVertexStr = filteredVertexStr+vertexStr[i];
        }
    }

    return filteredVertexStr;

}

void SAM_file::GenerateDeletions(string qText, string CIAGR, SetOfDeletions &deletions, int qStart,int tStart)
{
   // std::string qTextOut = "";
    std::string numberOfLetters = "";
   // int positionWrited = 0;

    for(int i = 0;i < CIAGR.length();i++)
    {

        char letter;
        letter = CIAGR[i];

        int numOfLetters = atoi(numberOfLetters.c_str());

        if(letter == '=')
        {
     //       qTextOut = qText;
            numberOfLetters = "";

            break;
        }
        else
        {
            if(letter == 'X')
            {
                numberOfLetters = "";
                break;
            }
            else
            {
                if(letter == 'I')
                {

                  //  cout << "before letter == I\n";
                  //  cout << "numOfLetters - " << numOfLetters << "\n";
                  //  cout << "before qStart - " << qStart << "\n";
                  //  cout << "CIAGR - " << CIAGR << "\n";
                    std::string insertText = qText.substr(qStart,numOfLetters);
                    Deletion delTemp(insertText,qStart,tStart);
                    qStart += numOfLetters;
                    //tStart += numOfLetters;
                    deletions.AddToSet(delTemp);
                  //  cout << "after qStart - " << qStart << "\n";
                  //  cout << "after letter == I\n";
                    numberOfLetters = "";
                    continue;
                }
                else
                {
                    if(letter == 'D')
                    {
                        //qStart += numOfLetters;
                        tStart += numOfLetters;
                        numberOfLetters = "";
                        continue;
                    }
                    else
                    {
                        if(letter == 'S')
                        {
                            qStart += numOfLetters;
                            tStart += numOfLetters;
                            numberOfLetters = "";
                            continue;
                        }
                        else
                        {
                            if(letter == 'N')
                            {
                                qStart += numOfLetters;
                                tStart += numOfLetters;
                                numberOfLetters = "";
                                continue;
                            }
                            else
                            {
                                if(letter == 'M')
                                {
                                    //cout << "before M qStart - " <<qStart << "\n";
                                    qStart += numOfLetters;
                                    tStart += numOfLetters;
                                    numberOfLetters = "";
                                    //cout << "after M qStart - " <<qStart << "\n";
                                    continue;
                                }
                                else
                                {
                                    numberOfLetters = numberOfLetters + letter;
                                    continue;
                                }
                            }
                        }
                    }
                }
            }

        }

    }

   // return qTextOut;
}

SAM_file::SAM_file()
{
    _isFileEnd = false;
    _isReadHitsLoaded = false;
    _isFileOpened = false;
    _fileName = "";
    _qName = "";
    _flag = "";
    _tName = "";
    _position = -1;
    _mapQual = "";
    _CIAGR = "";
    _MRNM = "";
    _MPOS = "";
    _ISIZE = "";
	_qReadText = "";
	_qReadMapText = "";
	_qQualText = "";
	_qQualMapText = "";
	_readHitsArray = SetOfRead_Hit();
	_currFile = NULL;
}

int SAM_file::OpenFile()
{
    int notError = 1;

    _currFile = fopen(_fileName.c_str(),"r");
    if(_currFile == NULL)
    {
        _isFileOpened = false;
        notError = ErrorHappens;
    }
    else
	{
        _isFileOpened = true;
    }

    return notError;
}

void SAM_file::ReadNextLine()
{
    if((!_isFileOpened) || (_isFileEnd))
	{
        return;
    }

    char* qName = new char[200];
    char* flag = new char[200];
    char* tName = new char[200];
    int position = -1;
    char* mapQual = new char[200];
    char* CIAGR = new char[200];
    char* MRNM = new char[200];
    char* MPOS = new char[200];
    char* ISIZE = new char[200];
    char* qReadText = new char[2000];
    char* qQualText = new char[2000];

    SetOfDeletions deletions;


    fscanf(_currFile,"%s %s %s %u %s %s %s %s %s %s %s",qName,flag,tName,&position,mapQual,CIAGR,MRNM,MPOS,ISIZE,qReadText,qQualText);

    char tempChar = fgetc(_currFile);

	while(!feof(_currFile))
    {
        if(tempChar == '\n')
        {
            break;
        }

        tempChar = fgetc(_currFile);
    }

    if(feof(_currFile))
    {
        _isFileEnd = true;
    }

    _qName = qName;
    _flag = flag;
    _tName = tName;
    _position = position;
    _mapQual = mapQual;
	_CIAGR = CIAGR;
	_MRNM = MRNM;
    _MPOS = MPOS;
    _ISIZE = ISIZE;
	_qReadText = qReadText;
	_qQualText = qQualText;

    //int qTextLen = _qReadText.length();
    _qReadMapText =GenerateMappedReadOrQual(qReadText,_CIAGR);
    //int qMapTextLen = _qReadMapText.length();
    _qQualMapText =GenerateMappedReadOrQual(qQualText,_CIAGR);
   // qTextLen = _qReadText.length();

    GenerateDeletions(qReadText,_CIAGR,deletions,0,position);

    _deletionsAtPoint = deletions;


    _isFileOpened = true;

    delete[] qName;
    delete[] flag;
    delete[] tName;
    delete[] mapQual;
    delete[] CIAGR;
    delete[] MRNM;
	delete[] MPOS;
	delete[] ISIZE;
	delete[] qReadText;
	delete[] qQualText;

}

void SAM_file::PrintToTerminal()
{
	cout << _qName << " " << _flag << " " << _tName << " " << _position << " " << _mapQual << " " << _CIAGR;
	cout << _MRNM << " " <<_MPOS <<" " << _ISIZE << " " << _qReadText << " " << _qQualText << "\n";
}

void SAM_file::LoadReadHits()
{


  if(_isReadHitsLoaded )
  {
	return;
  }
  if(!_isFileOpened)
  {
	return;
  }
  _readHitsArray.Clear();
  int numberOfHit = 0;
  this->SetFileToStart();
  ReadNextLine();
  while(!_isFileEnd)
  {


    Read_Hit ReadHitToWrite(_qName,_position, _qReadText, _qQualText,_qReadMapText,_qQualMapText,_deletionsAtPoint);

    FastqSequenceRecord readToAdd(_qName,_qReadText,_qQualText);

    _readHitsArray.AddToSet(ReadHitToWrite);

    _allReads.Add(readToAdd);

    ReadNextLine();
	numberOfHit++;


  }




  _isReadHitsLoaded= 1;
}

std::string SAM_mapping::GetConsensusString(int startCoor,int endCoor)
{
    std::string resultStr = "";

    if(startCoor > endCoor)
    {
        return resultStr;
    }

    for(int i = startCoor; i <= endCoor;i++)
    {
        resultStr = resultStr + FindWhatLetterHasMaximumWeightAtThisPos(i);
        resultStr = resultStr + GetDelStrWithMaxWeightAtPos(i);
    }

    return resultStr;
}

void SAM_file::LoadReadHits(int sizeOfRef)
{


  if(_isReadHitsLoaded )
  {
    return;
  }
  if(_isReadHitsListLoaded )
  {
    return;
  }
  if(!_isFileOpened)
  {
    return;
  }
  _readHitsArray.Clear();
  _readHitsListArray.Clear();
  int numberOfHit = 0;
  this->SetFileToStart();
  ReadNextLine();
  int countSets = sizeOfRef/1000 + 1;


  for(int i = 0;i<countSets;i++)
  {
      SetOfRead_Hit currSetOfReadHits;
      _readHitsListArray.AddToSet(currSetOfReadHits);
  }

  while(!_isFileEnd)
  {



      int currReadHitSet = _position/1000;

      int endPosition = _position + _qReadText.length();

      int endReadHitSet = endPosition/1000;


      //cout <<"QName - " << _qName << "\n";
      Read_Hit ReadHitToWrite(_qName,_position, _qReadText, _qQualText,_qReadMapText,_qQualMapText,_deletionsAtPoint);

      FastqSequenceRecord readToAdd(_qName,_qReadText,_qQualText);

    _readHitsArray.AddToSet(ReadHitToWrite);


    SetOfRead_Hit *rHitsList = _readHitsListArray.GetRefItemByNum(currReadHitSet);





    _readHitsListArray.GetRefItemByNum(currReadHitSet)->AddToSet(ReadHitToWrite);

    if(currReadHitSet != endReadHitSet)
    {
        _readHitsListArray.GetRefItemByNum(endReadHitSet)->AddToSet(ReadHitToWrite);
    }

    _allReads.Add(readToAdd);


    ReadNextLine();

    numberOfHit++;


  }




  _isReadHitsLoaded= 1;
  _isReadHitsListLoaded= 1;
}

void SAM_file::LoadReadHits(double percentOfReadLenLowLim)
{


  if(_isReadHitsLoaded )
  {
    return;
  }
  if(!_isFileOpened)
  {
    return;
  }
  _readHitsArray.Clear();
  int numberOfHit = 0;
  this->SetFileToStart();
  ReadNextLine();

  while(!_isFileEnd)
  {

    double percentOfReadLen = (_qReadMapText.length())/(_qReadText.length());
    if(percentOfReadLen >= percentOfReadLenLowLim)
    {
        Read_Hit ReadHitToWrite(_qName,_position, _qReadText, _qQualText,_qReadMapText,_qQualMapText,_deletionsAtPoint);

        FastqSequenceRecord readToAdd(_qName,_qReadText,_qQualText);

        _readHitsArray.AddToSet(ReadHitToWrite);

        _allReads.Add(readToAdd);
    }

    ReadNextLine();
    numberOfHit++;

  }





  _isReadHitsLoaded= 1;
}


std::string SAM_file::GenerateMappedReadOrQual(std::string qText, std::string ciagrString)
{

	std::string qTextOut = "";
	std::string numberOfLetters = "";
	int positionWrited = 0;
    for(int i = 0;i < ciagrString.length();i++)
    {

        char letter;
        letter = ciagrString[i];

        int numOfLetters = atoi(numberOfLetters.c_str());

        if(letter == '=')
        {
            qTextOut = qText;
            numberOfLetters = "";

            break;
        }
        else
        {
            if(letter == 'X')
            {
                numberOfLetters = "";
                break;
            }
            else
            {
                if(letter == 'I')
                {

                    positionWrited = positionWrited + numOfLetters;
                    numberOfLetters = "";
                    continue;
                }
                else
                {
                    if(letter == 'D')
                    {
                        for(int j = 0;j < numOfLetters;j++)
                        {
                            qTextOut = qTextOut + '-';
                        }
                        numberOfLetters = "";
                        continue;
                    }
                    else
                    {
                        if(letter == 'S')
                        {
                            positionWrited = positionWrited + numOfLetters;
                            numberOfLetters = "";
                            continue;
                        }
                        else
                        {
                            if(letter == 'N')
                            {
                                positionWrited = positionWrited + numOfLetters;
                                numberOfLetters = "";
                                continue;
                            }
                            else
                            {
                                if(letter == 'M')
                                {
                                    qTextOut = qTextOut + qText.substr(positionWrited,numOfLetters);
                                    positionWrited = positionWrited + numOfLetters;
                                    numberOfLetters = "";
                                    continue;
                                }
                                else
                                {
                                    numberOfLetters = numberOfLetters + letter;
                                    continue;
                                }
                            }
                        }
                    }
                }
            }

        }

    }

    return qTextOut;
}

SetOf<std::string> SAM_mapping::GetAllDelStrsAtPos(unsigned int pos)
{
    SetOf<std::string> setDelStrs;

    SetOfRead_Hit readHits;

    if(_samFile.IsReadHitsListLoaded())
    {
        readHits = *(_samFile.GetSetOfReadHitsAtPos((int)(pos/(1000))));
    }
    else
    {
        readHits = _samFile.GetSetOfReadHits();
    }

    //cout << "sizeOfReadHitsSet - " << readHits.GetSizeOfSet() << "\n";

    for(int i = 0;i < readHits.GetSizeOfSet();i++)
    {
        std::string delStr = readHits.GetItemByNum(i).GetDeletionTextAtPosInMap(pos);
        if(delStr == "" || delStr == "-") continue;
        if(!setDelStrs.IsValueExistInSet(delStr))
        {
            setDelStrs.AddToSet(delStr);
        }
    }

    return setDelStrs;





}



string SAM_mapping::GetDelStrWithMaxWeightAtPos(unsigned int pos)
{
    SetOf<std::string> setDelStrs = GetAllDelStrsAtPos(pos);

    string delStr = "";

    int maxWeight = 0;

    for(unsigned int i = 0; i < setDelStrs.GetSizeOfSet();i++)
    {
        int currWeight = GetListOfReadsWithThisTextAtThisPos(*(setDelStrs.GetRefItemByNum(i)),pos,true).GetReadList().GetSizeOfSet();

        if(currWeight > maxWeight)
        {
            maxWeight = currWeight;
            delStr = *(setDelStrs.GetRefItemByNum(i));
        }

    }



    return delStr;





}


int SAM_mapping::CountNumOfLetterInReadsAtRefPos(char letter,int position)
{


    SetOfRead_Hit readHits;

    if(_samFile.IsReadHitsListLoaded())
    {
        readHits = *(_samFile.GetSetOfReadHitsAtPos((int)(position/(1000))));
    }
    else
    {
        readHits = _samFile.GetSetOfReadHits();
    }

    //SetOfRead_Hit readHits = _samFile.GetSetOfReadHits();

    int numberOfHits = readHits.GetSizeOfSet();

    int countOfLetter = 0;

    for(int i = 0; i < numberOfHits;i++)
    {
        if(readHits.GetItemByNum(i).GetPosByNumInMap(position) == letter)
        {
            countOfLetter++;
        }
    }

    return countOfLetter;
}

int SAM_mapping::CountDeletionsOfLettersInReadsAtRefPos(int position)
{
int countOfLetter = 0;

    /*

    SetOfRead_Hit readHits = _samFile.GetSetOfReadHits();

    int numberOfHits = readHits.GetSizeOfSet();

    int countOfLetter = 0;
    char currLetterMap = readHits.GetItemByNum(i).GetPosByNumInMap(position);
    char currLetterInRead =

    for(int i = 0; i < numberOfHits;i++)
    {

        for(j = position+1;j<readHits.GetItemByNum(i).GetQText().length();j++)
        {
            if(readHits.GetItemByNum(i).GetPosByNumInMap(j) == letter)
            {
                countOfLetter++;
            }
        }
    }

    return countOfLetter;*/
return countOfLetter;
}

int SAM_mapping::CountCoverageAtThisPos(int position)
{
    SetOfRead_Hit readHits;

    int coorTest = (int)(position/1000);

    if(_samFile.IsReadHitsListLoaded())
    {
        readHits = *(_samFile.GetSetOfReadHitsAtPos((int)(position/(1000))));

    }
    else
    {
        readHits = _samFile.GetSetOfReadHits();
    }




    int numberOfHits = readHits.GetSizeOfSet();

    int countOfLetter = 0;

    for(int i = 0; i < numberOfHits;i++)
    {
        if(readHits.GetItemByNum(i).GetPosByNumInMap(position) != 'N')
        {
            countOfLetter++;
        }
    }

    return countOfLetter;
}

int FindMax(double *arrVal, int size)
{
    double maxVal = -1;
    int maxI = -1;

    for(int i = 0;i<size;i++)
    {
        if(*(arrVal+i)> maxVal)
        {
            maxI = i;
            maxVal = *(arrVal+i);
        }
    }

    return maxI;
}

void ProcessingCountMaxOutput3(double &count1, double &count2, double &count3)
{
    double *arrForCount3 = new double[3];

    arrForCount3[0] = count1;
    arrForCount3[1] = count2;
    arrForCount3[2] = count3;


    int indexOfMax = FindMax(arrForCount3,3);



    if(indexOfMax == 0)
    {
        count2 = 0.0;
        count3 = 0.0;
    }
    else if(indexOfMax == 1)
    {
        count1 = 0.0;
        count3 = 0.0;
    }
    else if(indexOfMax == 2)
    {
        count1 = 0.0;
        count2 = 0.0;
    }

    delete[] arrForCount3;

}


void ProcessingCountMaxOutput4(double &count1, double &count2, double &count3, double &count4)
{
    double *arrForCount4 = new double[4];
    arrForCount4[0] = count1;
    arrForCount4[1] = count2;
    arrForCount4[2] = count3;
    arrForCount4[3] = count4;

    int indexOfMax = FindMax(arrForCount4,4);

    if(indexOfMax == 0)
    {
        ProcessingCountMaxOutput3(count2,count3,count4);
    }
    else if(indexOfMax == 1)
    {
        ProcessingCountMaxOutput3(count1,count3,count4);
    }
    else if(indexOfMax == 2)
    {
        ProcessingCountMaxOutput3(count1,count2,count4);
    }
    else if(indexOfMax == 3)
    {
        ProcessingCountMaxOutput3(count1,count2,count3);
    }




    delete[] arrForCount4;




}

void ProcessingCountMaxOutput5(double &count1, double &count2, double &count3, double &count4, double &count5)
{
    double *arrForCount5 = new double[5];
    arrForCount5[0] = count1;
    arrForCount5[1] = count2;
    arrForCount5[2] = count3;
    arrForCount5[3] = count4;
    arrForCount5[4] = count5;

    int indexOfMax = FindMax(arrForCount5,5);

    if(indexOfMax == 0)
    {
        ProcessingCountMaxOutput4(count2,count3,count4,count5);
    }
    else if(indexOfMax == 1)
    {
        ProcessingCountMaxOutput4(count1,count3,count4,count5);
    }
    else if(indexOfMax == 2)
    {
        ProcessingCountMaxOutput4(count1,count2,count4,count5);
    }
    else if(indexOfMax == 3)
    {
        ProcessingCountMaxOutput4(count1,count2,count3,count5);
    }
    else if(indexOfMax == 4)
    {
        ProcessingCountMaxOutput4(count1,count2,count3,count4);
    }



    delete[] arrForCount5;




}




short SAM_mapping::FindWhatLetterIsCorrectAtThisPos(int position)
{
    short correctLetter = 0;

    int Acount = 0;
    int Tcount = 0;
    int Gcount = 0;
    int Ccount = 0;
    int Inscount = 0;




    Acount = CountNumOfLetterInReadsAtRefPos('A',position);
    Tcount = CountNumOfLetterInReadsAtRefPos('T',position);
    Gcount = CountNumOfLetterInReadsAtRefPos('G',position);
    Ccount = CountNumOfLetterInReadsAtRefPos('C',position);
    Inscount = CountNumOfLetterInReadsAtRefPos('-',position);


    double percentAcount = 0;
    double percentTcount = 0;
    double percentGcount = 0;
    double percentCcount = 0;
    double percentInscount = 0;


    int sumOfMappedReads = Acount + Tcount + Gcount + Ccount + Inscount;
    if(sumOfMappedReads > 0)
    {
        percentAcount = (double)Acount/(double)sumOfMappedReads;
        percentTcount = (double)Tcount/(double)sumOfMappedReads;
        percentGcount = (double)Gcount/(double)sumOfMappedReads;
        percentCcount = (double)Ccount/(double)sumOfMappedReads;
        percentInscount = (double)Inscount/(double)sumOfMappedReads;

    }


    if(percentAcount > _limCountToConsiderDiploid)
    {

        correctLetter = correctLetter | OnlyA;

    }

    if(percentTcount > _limCountToConsiderDiploid)
    {

        correctLetter = correctLetter | OnlyT;
    }

    if(percentGcount > _limCountToConsiderDiploid)
    {

        correctLetter = correctLetter | OnlyG;
    }

    if(percentCcount > _limCountToConsiderDiploid)
    {
 
        correctLetter = correctLetter | OnlyC;

    }

    if(percentInscount > _limCountToConsiderDiploid)
    {

        correctLetter = correctLetter | OnlyIns;

    }





    return correctLetter;

}


string SAM_mapping::FindWhatLetterHasMaximumWeightAtThisPos(int position)
{


    int Acount = 0;
    int Tcount = 0;
    int Gcount = 0;
    int Ccount = 0;
    int Inscount = 0;




    Acount = CountNumOfLetterInReadsAtRefPos('A',position);
    Tcount = CountNumOfLetterInReadsAtRefPos('T',position);
    Gcount = CountNumOfLetterInReadsAtRefPos('G',position);
    Ccount = CountNumOfLetterInReadsAtRefPos('C',position);
    Inscount = CountNumOfLetterInReadsAtRefPos('-',position);


    if((Acount > Tcount) && (Acount > Gcount) && (Acount > Ccount) && (Acount > Inscount))
    {
        return "A";
    }

    if((Tcount > Acount) && (Tcount > Gcount) && (Tcount > Ccount) && (Tcount > Inscount))
    {
        return "T";
    }

    if((Gcount > Tcount) && (Gcount > Acount) && (Gcount > Ccount) && (Gcount > Inscount))
    {
        return "G";
    }

    if((Inscount > Tcount) && (Inscount > Gcount) && (Inscount > Ccount) && (Inscount > Acount))
    {
        return "-";
    }




    return "N";

}


UniqueReadList SAM_mapping::GetListOfReadsWithThisLetterAtThisPos(char letter, int pos)
{


    //int numberOfReadsFound = 0;
    UniqueReadList readsList;

    SetOfRead_Hit readHitsList;

    if(_samFile.IsReadHitsListLoaded())
    {
        readHitsList = *(_samFile.GetSetOfReadHitsAtPos((int)(pos/(1000))));
    }
    else
    {
        readHitsList = _samFile.GetSetOfReadHits();
    }

    //SetOfRead_Hit readHitsList = _samFile.GetSetOfReadHits();

    int readHitsListSize = readHitsList.GetSizeOfSet();



    for(int i = 0; i < readHitsListSize;i++)
    {

        if(readHitsList.GetItemByNum(i).GetPosByNumInMap(pos) == letter)
        {
            FastqSequenceRecord seqRecord(readHitsList.GetItemByNum(i).GetQName(),readHitsList.GetItemByNum(i).GetQText(),readHitsList.GetItemByNum(i).GetQQual());

            readsList.Add(seqRecord);

            int sizeDebug = readsList.GetReadList().GetSizeOfSet();
            sizeDebug++;
        }
    }






    return readsList;
}


UniqueReadList SAM_mapping::GetListOfReadsWithThisTextAtThisPos(std::string text, int pos,bool isDeletion)
{

    if(pos == 8380)
    {
        cout << "Before GetListOfReadsWithThisTextAtThisPos(std::string text, int pos,bool isDeletion)\n";
    }
    if(text.length() < 2 && !isDeletion)
    {
        return GetListOfReadsWithThisLetterAtThisPos(text.c_str()[0],pos);
    }

    if(!isDeletion)
    {
        cout << "text - " << text << "\n";
        cout << "pos - " << pos << "\n";
        cout << "isDeletion - " << isDeletion << "\n";
        cerr << "fatal error at function GetListOfReadsWithThisTextAtThisPos\n";
        exit(EXIT_FAILURE);
    }

    std::string textToCheck = "";

    for(int i = 0; i<text.length();i++)
    {
        if(text[i] != '-')
        {
            textToCheck = textToCheck+text[i];
        }
    }
    if(pos == 8380)
    {
        cout << "textCheck - " << textToCheck << "\n";
    }

    UniqueReadList readsList;



    //int numberOfReadsFound = 0;


    SetOfRead_Hit readHitsList;

    if(_samFile.IsReadHitsListLoaded())
    {
        readHitsList = *(_samFile.GetSetOfReadHitsAtPos((int)(pos/(1000))));
    }
    else
    {
        readHitsList = _samFile.GetSetOfReadHits();
    }

    //SetOfRead_Hit readHitsList = _samFile.GetSetOfReadHits();

    int readHitsListSize = readHitsList.GetSizeOfSet();



    for(int i = 0; i < readHitsListSize;i++)
    {
        if(textToCheck == "")
        {
            if(readHitsList.GetItemByNum(i).GetDeletionTextAtPosInMap(pos)=="-")
            {
                FastqSequenceRecord seqRecord(readHitsList.GetItemByNum(i).GetQName(),readHitsList.GetItemByNum(i).GetQText(),readHitsList.GetItemByNum(i).GetQQual());

                readsList.Add(seqRecord);

                int sizeDebug = readsList.GetReadList().GetSizeOfSet();
                sizeDebug++;
            }
        }
        else
        {



            if(readHitsList.GetItemByNum(i).GetDeletionTextAtPosInMap(pos) == textToCheck)
            {
                FastqSequenceRecord seqRecord(readHitsList.GetItemByNum(i).GetQName(),readHitsList.GetItemByNum(i).GetQText(),readHitsList.GetItemByNum(i).GetQQual());

                readsList.Add(seqRecord);

                int sizeDebug = readsList.GetReadList().GetSizeOfSet();
                sizeDebug++;
            }
        }
    }






    return readsList;
}



UniqueReadList SAM_mapping::GetListOfReadsAtThisPos( int pos)
{


    //int numberOfReadsFound = 0;
    UniqueReadList readsList;

    SetOfRead_Hit readHitsList;

    if(_samFile.IsReadHitsListLoaded())
    {
        readHitsList = *(_samFile.GetSetOfReadHitsAtPos((int)(pos/(1000))));
    }
    else
    {
        readHitsList = _samFile.GetSetOfReadHits();
    }

    //SetOfRead_Hit readHitsList = _samFile.GetSetOfReadHits();

    int readHitsListSize = readHitsList.GetSizeOfSet();



    for(int i = 0; i < readHitsListSize;i++)
    {

        if(readHitsList.GetItemByNum(i).GetPosByNumInMap(pos) != 'N')
        {
            FastqSequenceRecord seqRecord(readHitsList.GetItemByNum(i).GetQName(),readHitsList.GetItemByNum(i).GetQText(),readHitsList.GetItemByNum(i).GetQQual());

            readsList.Add(seqRecord);

            int sizeDebug = readsList.GetReadList().GetSizeOfSet();
            sizeDebug++;
        }
    }






    return readsList;
}




int SAM_mapping::PrintMappingToFile(char *fileName)
{

    std::fstream fileToWrite(fileName,std::fstream::out);

    SetOfRead_Hit setReadHits = _samFile.GetSetOfReadHits();

    int sizeOfNumberReadHits = setReadHits.GetSizeOfSet();
    int lenOfRef = _refSeq.GetSequenceText().length();



    int maxName = -1;
    std::string seqNam_1 = _refSeq.GetSequenceName();
    int lenSeqNam = seqNam_1.length();
    if(lenSeqNam > maxName)
    {
        maxName = _refSeq.GetSequenceName().length();
    }

    std::string debugQName_max = "";
    std::string debugQText_max = "";
    std::string debugQMapText_max = "";
    int i_max = 0;
    for(int i = 0;i<sizeOfNumberReadHits;i++)
    {
        std::string debugQName = setReadHits.GetItemByNum(i).GetQName();
        std::string debugQText = setReadHits.GetItemByNum(i).GetQText();
        std::string debugQMapText = setReadHits.GetItemByNum(i).GetQMapText();
        if(i==6932)
        {
            int a = 0;
            a++;
        }
        if(setReadHits.GetItemByNum(i).GetQName().length() > maxName)
        {
            i_max = i;

            debugQName_max = setReadHits.GetItemByNum(i).GetQName();
            debugQText_max = setReadHits.GetItemByNum(i).GetQText();
            debugQMapText_max = setReadHits.GetItemByNum(i).GetQMapText();

            maxName = setReadHits.GetItemByNum(i).GetQName().length();
        }
    }

    fileToWrite << _refSeq.GetSequenceName();

    int diff = maxName - _refSeq.GetSequenceName().length() + 1;

    for(int k = 0; k < diff;k++)
    {
        fileToWrite << " ";
    }


    for(int j = 0;j<lenOfRef;j++)
    {
        fileToWrite << _refSeq.GetCharOfSequenceTextByNum(j);
    }

    fileToWrite <<"\n";



    for(int i = 0;i<sizeOfNumberReadHits;i++)
    {
        fileToWrite << setReadHits.GetItemByNum(i).GetQName();

        diff = maxName - setReadHits.GetItemByNum(i).GetQName().length() + 1;

        for(int k = 0; k < diff;k++)
        {
            fileToWrite << " ";
        }

        for(unsigned int j=1;j<=lenOfRef;j++)
        {
            fileToWrite << setReadHits.GetItemByNum(i).GetPosByNumInMap(j);
        }
        fileToWrite << "\n";
    }

    fileToWrite.close();

    return AllOk;



}

int SAM_mapping::CountCoverage(std::string avFileNameOutput, std::string covTableFileNameOutput)
{

    int sizeOfRef = this->_refSeq.GetSequenceText().length();
    double avCovLim = 0.0;

    fstream fileToWrite(covTableFileNameOutput.c_str(),fstream::out);








    for(int i =1;i <= sizeOfRef;i++)
    {
        int currCov = CountCoverageAtThisPos(i);

        fileToWrite << i << " "<< currCov << "\n";
        avCovLim += currCov;
    }

    avCovLim = avCovLim/sizeOfRef;

     fileToWrite.close();





    fstream fileToWrite1(avFileNameOutput.c_str(),fstream::out);

    fileToWrite1 << avCovLim << "\n";

    fileToWrite1.close();



}


int SAM_mapping::FindGaploidsAlgorithm(std::string allConflictPoints)
{

    int sizeOfRef = this->_refSeq.GetSequenceText().length();
    short lettersInThisPos = 0;

    fstream allConflictPointsFile(allConflictPoints.c_str(),fstream::out);




    int i_last = -1;

    double avCovLim = 0.0;


    avCovLim = avCovLim/sizeOfRef;
    avCovLim = avCovLim*_fractionOfAvCov;


    SetOfRef<Vertex> lastVertexies;




    for(int i =1;i <= sizeOfRef;i++)
    {

        int currCov = CountCoverageAtThisPos(i);
        if(/*(currCov < avCovLim) ||*/ (currCov < 10)) continue;
        lettersInThisPos = 0;

        lettersInThisPos = FindWhatLetterIsCorrectAtThisPos(i);

        if((lettersInThisPos == OnlyA) || (lettersInThisPos == OnlyC) || (lettersInThisPos == OnlyG)
                || (lettersInThisPos == OnlyT) || (lettersInThisPos == OnlyIns) || (lettersInThisPos == 0))
        {

            continue;
        }

        allConflictPointsFile << i << " ";
	

	


        if(lettersInThisPos & OnlyA)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('A',i);



            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            allConflictPointsFile << " A " << sizeOfList << " ";


        }

        if(lettersInThisPos & OnlyT)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('T',i);



            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            allConflictPointsFile << " T " << sizeOfList << " ";


        }

        if(lettersInThisPos & OnlyC)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('C',i);


 
            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            allConflictPointsFile << " C " << sizeOfList << " ";


        }

        if(lettersInThisPos & OnlyG)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('G',i);


   
            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            allConflictPointsFile << " G " << sizeOfList << " ";


        }

        if(lettersInThisPos & OnlyIns)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('-',i);



            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            allConflictPointsFile << " - " << sizeOfList << " ";


        }

        allConflictPointsFile << "\n";





    }







 

    


    allConflictPointsFile.close();




    return AllOk;
}



int SAM_mapping::FindGaploidsAlgorithm(std::string allConflictPoints, std::string fileGraph,std::string fileSimpleGraph, std::string resultFileName, std::string fileDebugFileName, std::string scaffFileName,std::string scaffDebugFileName, int maxInsertSize)
{

    int sizeOfRef = this->_refSeq.GetSequenceText().length();

    sizeOfRef = 1000000;

    short lettersInThisPos = 0;

 
    fstream fileStreamGraph(fileGraph.c_str(),fstream::out);
    fstream fileStreamSimpleGraph(fileSimpleGraph.c_str(),fstream::out);
    fstream fileStreamDebug(fileDebugFileName.c_str(),fstream::out);
    fstream fileStreamDebugScaff(scaffDebugFileName.c_str(),fstream::out);

    Graph *currGraph = new Graph();


    int i_last = -1;

    double avCovLim = 0.0;

    for(int i =1;i <= sizeOfRef;i++)
    {
        int currCov = CountCoverageAtThisPos(i);

        avCovLim += currCov;
    }

    avCovLim = avCovLim/sizeOfRef;
    avCovLim = avCovLim*_fractionOfAvCov;


    SetOfRef<Vertex> lastVertexies;


    for(int i =1;i <= sizeOfRef;i++)
    {

        int currCov = CountCoverageAtThisPos(i);

        if((currCov < avCovLim) || (currCov < 10)) continue;
        lettersInThisPos = 0;

        lettersInThisPos = FindWhatLetterIsCorrectAtThisPos(i);

        if((lettersInThisPos == OnlyA) || (lettersInThisPos == OnlyC) || (lettersInThisPos == OnlyG)
                || (lettersInThisPos == OnlyT) || (lettersInThisPos == OnlyIns) || (lettersInThisPos == 0))
        {

            continue;
        }



        SetOfRef<Vertex> currVertexies;

        if(lettersInThisPos & OnlyA)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('A',i);
            std::string tempLetter = "";
            char *tempBuf = new char[100];
            itoa(i,tempBuf,10);
            tempLetter =tempLetter + "A_" + tempBuf;
            SetOf<ConnVertex> conVerFrom;
            SetOf<ConnVertex> conVerTo;
            ConnVertex connVerVal_From;
            connVerVal_From._connVertex = NULL;
            ConnVertex connVerVal_To;
            connVerVal_To._connVertex = NULL;
            conVerFrom.AddToSet(connVerVal_From);
            conVerTo.AddToSet(connVerVal_To);

            Vertex *currVertex = new Vertex(tempReadList,tempLetter,"A",i,conVerFrom,conVerTo);
            currVertexies.AddToSet(currVertex);


            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();

            delete[] tempBuf;
        }

        if(lettersInThisPos & OnlyT)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('T',i);
            std::string tempLetter = "";
            char *tempBuf = new char[100];
            itoa(i,tempBuf,10);
            tempLetter =tempLetter + "T_" + tempBuf;
            SetOf<ConnVertex> conVerFrom;
            SetOf<ConnVertex> conVerTo;
            ConnVertex connVerVal_From;
            connVerVal_From._connVertex = NULL;
            ConnVertex connVerVal_To;
            connVerVal_To._connVertex = NULL;
            conVerFrom.AddToSet(connVerVal_From);
            conVerTo.AddToSet(connVerVal_To);

            Vertex *currVertex = new Vertex(tempReadList,tempLetter,"T",i,conVerFrom,conVerTo);
            currVertexies.AddToSet(currVertex);


            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();

            delete[] tempBuf;
        }

        if(lettersInThisPos & OnlyC)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('C',i);
            std::string tempLetter = "";
            char *tempBuf = new char[100];
            itoa(i,tempBuf,10);
            tempLetter =tempLetter + "C_" + tempBuf;
            SetOf<ConnVertex> conVerFrom;
            SetOf<ConnVertex> conVerTo;
            ConnVertex connVerVal_From;
            connVerVal_From._connVertex = NULL;
            ConnVertex connVerVal_To;
            connVerVal_To._connVertex = NULL;
            conVerFrom.AddToSet(connVerVal_From);
            conVerTo.AddToSet(connVerVal_To);

            Vertex *currVertex = new Vertex(tempReadList,tempLetter,"C",i,conVerFrom,conVerTo);
            currVertexies.AddToSet(currVertex);


            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();

            delete[] tempBuf;
        }

        if(lettersInThisPos & OnlyG)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('G',i);
            std::string tempLetter = "";
            char *tempBuf = new char[100];
            itoa(i,tempBuf,10);
            tempLetter =tempLetter + "G_" + tempBuf;
            SetOf<ConnVertex> conVerFrom;
            SetOf<ConnVertex> conVerTo;
            ConnVertex connVerVal_From;
            connVerVal_From._connVertex = NULL;
            ConnVertex connVerVal_To;
            connVerVal_To._connVertex = NULL;
            conVerFrom.AddToSet(connVerVal_From);
            conVerTo.AddToSet(connVerVal_To);

            Vertex *currVertex = new Vertex(tempReadList,tempLetter,"G",i,conVerFrom,conVerTo);
            currVertexies.AddToSet(currVertex);


            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();

            delete[] tempBuf;
        }

        if(lettersInThisPos & OnlyIns)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('-',i);
            std::string tempLetter = "";
            char *tempBuf = new char[100];
            itoa(i,tempBuf,10);
            tempLetter =tempLetter + "Ins_" + tempBuf;
            SetOf<ConnVertex> conVerFrom;
            SetOf<ConnVertex> conVerTo;
            ConnVertex connVerVal_From;
            connVerVal_From._connVertex = NULL;
            ConnVertex connVerVal_To;
            connVerVal_To._connVertex = NULL;
            conVerFrom.AddToSet(connVerVal_From);
            conVerTo.AddToSet(connVerVal_To);

            Vertex *currVertex = new Vertex(tempReadList,tempLetter,"-",i,conVerFrom,conVerTo);
            currVertexies.AddToSet(currVertex);


            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();

            delete[] tempBuf;
        }


        if(lastVertexies.GetSizeOfSet()>0)
        {
            for(int j = 0;j<lastVertexies.GetSizeOfSet();j++)
            {
                UniqueReadList currLastVertex = GetListOfReadsWithThisLetterAtThisPos(lastVertexies.GetItemByNum(j)->GetSymbol().c_str()[0],lastVertexies.GetItemByNum(j)->GetCoor());
                for(int m = 0;m<currVertexies.GetSizeOfSet();m++)
                {
                    UniqueReadList currCurrVertex = GetListOfReadsWithThisLetterAtThisPos(currVertexies.GetItemByNum(m)->GetSymbol().c_str()[0],currVertexies.GetItemByNum(m)->GetCoor());

                    int weight = currCurrVertex.FindIntersectionOfLists(currLastVertex.GetReadList());
                    if(weight > 0)
			{


                    		lastVertexies.GetItemByNum(j)->ConnectToVertex(currVertexies.GetItemByNum(m),weight);
                    		currVertexies.GetItemByNum(m)->ConnectFromVertex(lastVertexies.GetItemByNum(j),weight);
			}

                }
            }



        }

        for(int j=0;j<currVertexies.GetSizeOfSet();j++)
        {

            currGraph->AddVertex(currVertexies.GetItemByNum(j));

        }

        if(lastVertexies.GetSizeOfSet()>0)
        {
            SetOfRef<Vertex> notConnectedVertexiesTo;
            SetOfRef<Vertex> connectedVertexiesTo;
            SetOfRef<Vertex> notConnectedVertexiesFrom;
            SetOfRef<Vertex> connectedVertexiesFrom;

            for(int j = 0;j<lastVertexies.GetSizeOfSet();j++)
            {
                Vertex *lastVertexCheck = lastVertexies.GetItemByNum(j);


                if(lastVertexCheck->GetConnToVertexByIndex(0)._connVertex == NULL)
                {
                    notConnectedVertexiesTo.AddToSet(lastVertexCheck);
                }
                else
                {
                    connectedVertexiesTo.AddToSet(lastVertexCheck);
                }
            }

            for(int j = 0;j<currVertexies.GetSizeOfSet();j++)
            {
                Vertex *currVertexCheck = currVertexies.GetItemByNum(j);


                if(currVertexCheck->GetConnFromVertexByIndex(0)._connVertex == NULL)
                {
                    notConnectedVertexiesFrom.AddToSet(currVertexCheck);
                }
                else
                {
                    connectedVertexiesFrom.AddToSet(currVertexCheck);
                }
            }

            for(int j = 0; j<notConnectedVertexiesTo.GetSizeOfSet();j++)
            {
                for(int m = 0;m<notConnectedVertexiesFrom.GetSizeOfSet();m++)
                {
                    notConnectedVertexiesTo.GetItemByNum(j)->ConnectToVertex(notConnectedVertexiesFrom.GetItemByNum(m),0);
                    notConnectedVertexiesFrom.GetItemByNum(m)->ConnectFromVertex(notConnectedVertexiesTo.GetItemByNum(j),0);
                }

            }

            for(int j = 0; j<notConnectedVertexiesTo.GetSizeOfSet();j++)
            {
                for(int m = 0;m<connectedVertexiesFrom.GetSizeOfSet();m++)
                {
                    notConnectedVertexiesTo.GetItemByNum(j)->ConnectToVertex(connectedVertexiesFrom.GetItemByNum(m),0);
                    connectedVertexiesFrom.GetItemByNum(m)->ConnectFromVertex(notConnectedVertexiesTo.GetItemByNum(j),0);
                }

            }

            for(int j = 0; j<notConnectedVertexiesFrom.GetSizeOfSet();j++)
            {
                for(int m = 0;m<connectedVertexiesTo.GetSizeOfSet();m++)
                {
                    notConnectedVertexiesFrom.GetItemByNum(j)->ConnectFromVertex(connectedVertexiesTo.GetItemByNum(m),0);
                    connectedVertexiesTo.GetItemByNum(m)->ConnectToVertex(notConnectedVertexiesFrom.GetItemByNum(j),0);
                }
            }

        }







        lastVertexies = currVertexies;



    }


    SimplifyGraph *simplGraph = new SimplifyGraph();

    currGraph->FillFirstVertexies();
    currGraph->PrintGraph(fileStreamGraph);

    simplGraph->EaseGraph(currGraph);
    simplGraph->FindFirstVertex();
simplGraph->PrintGraph(fileStreamSimpleGraph);

SetOfRef<Path> *resultPathes = new SetOfRef<Path>();
SetOfRef<Path> *pathesToFree = new SetOfRef<Path>();

simplGraph->GetAndPrintPath_Debug(fileStreamDebug,4,resultPathes,pathesToFree);




PrintFastaWithResultContigsByPathes(resultFileName,resultPathes,fileStreamDebug);





Scaffolder scaff;



scaff.Scaffolding(resultPathes,maxInsertSize);


PrintScaffoldsToFasta(scaffFileName,&scaff,fileStreamDebug);

scaff.Clear();















    //allConflictPointsFile.close();
    fileStreamDebug.close();
    fileStreamGraph.close();
    fileStreamSimpleGraph.close();
    fileStreamDebugScaff.close();

    delete currGraph;
    delete simplGraph;


    return AllOk;
}

void SAM_mapping::PrintFastaWithResultContigsByPathes(string fasta_fn, SetOfRef<Path> *resPathes, fstream &debugFile)
{



    FastaSequenceFileBuf fastaFile;

    for(int i=0;i<resPathes->GetSizeOfSet();i++)
    {
        Path *currPath = resPathes->GetItemByNum(i);


//        if(currPath->GetSizeOfSimplifyVertexSet() < 2)
//        {

//            if(currPath->GetSimplifyVertexByNum(0)->GetVertexSetSize() == 1)
//            continue;
//        }



        char *tempChar = new char[255];

        itoa(i,tempChar,10);
        std::string conName = currPath->GetName() + "_Path_" + tempChar;
        std::string seqText = "";

        delete[] tempChar;





        for(int j = 0;j < currPath->GetSizeOfSimplifyVertexSet();j++)
        {
            SimplifyVertex *currSVertex = currPath->GetSimplifyVertexByNum(j);
            SimplifyVertex *nextSVertex = NULL;

//            debugFile << currSVertex->GetName() << "\n";

            if(j != currPath->GetSizeOfSimplifyVertexSet()-1)
            {
                nextSVertex = currPath->GetSimplifyVertexByNum(j+1);
            }


            if(currSVertex->GetVertexSetSize() > 1)
            {
                for(int k=0;k<currSVertex->GetVertexSetSize()-1;k++)
                {
                    Vertex *currVertex = currSVertex->GetVertexByIndex(k);
                    int startPos = currVertex->GetCoor()+1;
                    int endPos = currSVertex->GetVertexByIndex(k+1)->GetCoor()-1;


                    if(k==0)
                    {

                        seqText = seqText +GetWhatStringRepresentVertex(currVertex);
                    }


                    seqText = seqText + GetConsensusString(startPos,endPos);

                    seqText = seqText +GetWhatStringRepresentVertex(currSVertex->GetVertexByIndex(k+1));




                }
            }
            else
            {
                seqText = seqText +GetWhatStringRepresentVertex(currSVertex->GetVertexByIndex(0));
                //if(currSVertex->GetVertexByIndex(0)->GetSymbol().c_str()[0] != '-')
                //seqText = seqText + currSVertex->GetVertexByIndex(0)->GetSymbol();
            }

            if(nextSVertex != NULL)
            {
                int startSVertex = currSVertex->GetVertexByIndex(currSVertex->GetVertexSetSize()-1)->GetCoor()+1;

                int endSVertex = nextSVertex->GetVertexByIndex(0)->GetCoor()-1;


                seqText = seqText + GetConsensusString(startSVertex,endSVertex);

            }

  //          debugFile << seqText << "\n";


        }

        int last_svertex_index = currPath->GetSizeOfSimplifyVertexSet() - 1;
        int last_vertex_index = currPath->GetSimplifyVertexByNum(last_svertex_index)->GetVertexSetSize() - 1;
        Vertex* lastVertex = currPath->GetSimplifyVertexByNum(last_svertex_index)->GetVertexByIndex(last_vertex_index);
        if(lastVertex->GetConnToVertexByIndex(0)._connVertex != NULL /*&& lastVertex->GetConnToVertexByIndex(0)._weight > 0*/)
        {
            Vertex* nearestVertex = (Vertex*)lastVertex->GetConnToVertexByIndex(0)._connVertex;
            int startExtendedVertex = lastVertex->GetCoor()+1;
            int endExtendedVertex = nearestVertex->GetCoor()-1;
            seqText = seqText + GetConsensusString(startExtendedVertex,endExtendedVertex);

        }

        FastaSequenceRecord fastaSeqRec(conName,seqText);

        fastaFile.AddSeqRecord(fastaSeqRec);

    }



   fastaFile.SaveToFile(fasta_fn.c_str());


}

int SAM_mapping::FindGaploidsAlgorithm_faster(std::string baseFileNameOutput)
{
    int sizeOfRef = this->_refSeq.GetSequenceText().length();
    short lettersInThisPos = 0;

    SetOfConComp *setConComp = new SetOfConComp();
    ConnectionComponent conComp;

    setConComp->AddToSet(conComp);

    int i_last = -1;

    for(int i =0;i < sizeOfRef;i++)
    {
        lettersInThisPos = 0;

        lettersInThisPos = FindWhatLetterIsCorrectAtThisPos(i);

        if((lettersInThisPos == OnlyA) || (lettersInThisPos == OnlyC) || (lettersInThisPos == OnlyG)
                || (lettersInThisPos == OnlyT) || (lettersInThisPos == 0))
        {

            continue;
        }

        Diploid diploidCurr;
        int currGaploid = 0;
        int diploidFirstGaploid =diploidCurr.GetFirstGaploid()->GetReadList().GetSizeOfSet();
        int diploidSecondGaploid =diploidCurr.GetSecondGaploid()->GetReadList().GetSizeOfSet();

        if(lettersInThisPos & OnlyA)
        {
            diploidCurr.GetFirstGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('A',i).GetReadList());
            currGaploid++;
        }
        diploidFirstGaploid =diploidCurr.GetFirstGaploid()->GetReadList().GetSizeOfSet();
        diploidSecondGaploid =diploidCurr.GetSecondGaploid()->GetReadList().GetSizeOfSet();

        if(lettersInThisPos & OnlyC)
        {
            if(currGaploid == 0)
            {
                diploidCurr.GetFirstGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('C',i).GetReadList());
            }
            else
            {
                diploidCurr.GetSecondGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('C',i).GetReadList());
            }
            currGaploid++;
        }
        diploidFirstGaploid =diploidCurr.GetFirstGaploid()->GetReadList().GetSizeOfSet();
        diploidSecondGaploid =diploidCurr.GetSecondGaploid()->GetReadList().GetSizeOfSet();

        if((lettersInThisPos & OnlyG) && (currGaploid <= 1))
        {
            if(currGaploid == 0)
            {
                diploidCurr.GetFirstGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('G',i).GetReadList());
            }
            else
            {
                diploidCurr.GetSecondGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('G',i).GetReadList());
            }
            currGaploid++;
        }
        diploidFirstGaploid =diploidCurr.GetFirstGaploid()->GetReadList().GetSizeOfSet();
        diploidSecondGaploid =diploidCurr.GetSecondGaploid()->GetReadList().GetSizeOfSet();

        if((lettersInThisPos & OnlyT) && (currGaploid <= 1))
        {
            if(currGaploid == 0)
            {
                diploidCurr.GetFirstGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('T',i).GetReadList());
            }
            else
            {
                diploidCurr.GetSecondGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('T',i).GetReadList());
            }
            currGaploid++;
        }
        diploidFirstGaploid =diploidCurr.GetFirstGaploid()->GetReadList().GetSizeOfSet();
        diploidSecondGaploid =diploidCurr.GetSecondGaploid()->GetReadList().GetSizeOfSet();



        if(i_last > 0)
        {
            int diff = i - i_last;

            if(diff > 100)
            {
                ConnectionComponent conCompTemp(diploidCurr);
                setConComp->AddToSet(conCompTemp);
                int sizeOfSetConComp = setConComp->GetSizeOfSet();
                int aaa = 0;

            }
            else
            {
                int connected = 0;
                ConnectionComponent *conComp_curr = setConComp->GetRefItemByNum(setConComp->GetSizeOfSet()-1);
                if(conComp_curr != NULL)
                {
                    connected = conComp_curr->AddDiploid(diploidCurr);
                }
                else
                {
                    connected = AllOk;
                }

                if(connected == ErrorHappens)
                {
                    ConnectionComponent conCompTemp(diploidCurr);
                    setConComp->AddToSet(conCompTemp);
                }
                int sizeOfSetConComp = setConComp->GetSizeOfSet();
                int firstGaploidSize = setConComp->GetRefItemByNum(sizeOfSetConComp-1)->GetFirstGaploid()->GetReadList().GetSizeOfSet();
                int secondGaploidSize = setConComp->GetRefItemByNum(sizeOfSetConComp-1)->GetSecondGaploid()->GetReadList().GetSizeOfSet();
                int aaa = 0;
            }

            //i_last = i;
        }

        i_last = i;

//        int connected = 0;
//        connected = setConComp->GetItemByNum(setConComp->GetSizeOfSet()-1).AddDiploid(diploidCurr);
//        if(connected == ErrorHappens)
//        {
//            ConnectionComponent conCompTemp(diploidCurr);
//            setConComp->AddToSet(conCompTemp);
//        }


    }



    for(int i = 0; i<setConComp->GetSizeOfSet();i++)
    {
        char *toStoreInt = new char[100];
        sprintf(toStoreInt,"%d",i);
        std::string baseFNToWrite = baseFileNameOutput+"_"+toStoreInt;
        setConComp->GetItemByNum(i).PrintToFastqFiles(baseFNToWrite);

        delete[] toStoreInt;
    }




    delete setConComp;

    return AllOk;
}



int SAM_mapping::CountStats(std::string fileNameStats)
{
    int sizeOfRef = this->_refSeq.GetSequenceText().length();
    short lettersInThisPos = 0;

    int countAbove100 = 0;
    int countBelow100 = 0;

    int i_last = -1;

    for(int i =0;i < sizeOfRef;i++)
    {
        lettersInThisPos = 0;

        lettersInThisPos = FindWhatLetterIsCorrectAtThisPos(i);

        if((lettersInThisPos == OnlyA) || (lettersInThisPos == OnlyC) || (lettersInThisPos == OnlyG)
                || (lettersInThisPos == OnlyT) || (lettersInThisPos == 0))
        {
            continue;
        }

        if(i_last > 0)
        {
            int diff = i - i_last;

            if(diff > 100)
            {
                countAbove100++;
            }
            else
            {
                countBelow100++;
            }


        }

        i_last = i;




    }

    std::fstream fileToWrite(fileNameStats.c_str(),std::fstream::out);

    fileToWrite << "above100 - " << countAbove100 << "\n";
    fileToWrite << "below100 - " << countBelow100 << "\n";

    fileToWrite.close();


    return AllOk;
}


void SAM_mapping::PrintScaffoldsToFasta(string fasta_fn, Scaffolder *resScaffolds, fstream &debugFile)
{



    FastaSequenceFileBuf fastaFile;





    for(int z=0;z<resScaffolds->GetSizeOfConsScaffoldSet();z++)
    {

        ConsiderScaffold *resPathes = resScaffolds->GetConsScaffoldByIndex(z);


        std::string seqText = "";
        std::string conName = "";
        char *tempChar = new char[255];
        itoa(z,tempChar,10);

        conName = conName + "Scaffold_" + tempChar;

        delete []tempChar;


        for(int i=0;i<resPathes->GetSizeOfPathesSet();i++)
        {




		Path *currPath = resPathes->GetPathByNum(i)->GetPath();
		
		conName = conName + "_"+currPath->GetName();
		
        











            for(int j = 0;j < currPath->GetSizeOfSimplifyVertexSet();j++)
            {
                SimplifyVertex *currSVertex = currPath->GetSimplifyVertexByNum(j);
                SimplifyVertex *nextSVertex = NULL;



                if(j != currPath->GetSizeOfSimplifyVertexSet()-1)
                {
                    nextSVertex = currPath->GetSimplifyVertexByNum(j+1);
                }


                if(currSVertex->GetVertexSetSize() > 1)
                {
                    for(int k=0;k<currSVertex->GetVertexSetSize()-1;k++)
                    {
                        Vertex *currVertex = currSVertex->GetVertexByIndex(k);
                        int startPos = currVertex->GetCoor()+1;
                        int endPos = currSVertex->GetVertexByIndex(k+1)->GetCoor()-1;


                        if(k==0)
                        {
                            seqText = seqText +GetWhatStringRepresentVertex(currVertex);
                            //if(currVertex->GetSymbol().c_str()[0] != '-')
                            //seqText = seqText +currVertex->GetSymbol();
                        }


                        seqText = seqText + GetConsensusString(startPos,endPos);

                        seqText = seqText +GetWhatStringRepresentVertex(currSVertex->GetVertexByIndex(k+1));
                        //if(currSVertex->GetVertexByIndex(k+1)->GetSymbol().c_str()[0] != '-')
                        //seqText = seqText + currSVertex->GetVertexByIndex(k+1)->GetSymbol();




                    }
                }
                else
                {
                    seqText = seqText +GetWhatStringRepresentVertex(currSVertex->GetVertexByIndex(0));
                    //if(currSVertex->GetVertexByIndex(0)->GetSymbol().c_str()[0] != '-')
                    //seqText = seqText + currSVertex->GetVertexByIndex(0)->GetSymbol();
                }

                if(nextSVertex != NULL)
                {
                    int startSVertex = currSVertex->GetVertexByIndex(currSVertex->GetVertexSetSize()-1)->GetCoor()+1;

                    int endSVertex = nextSVertex->GetVertexByIndex(0)->GetCoor()-1;


                    seqText = seqText + GetConsensusString(startSVertex,endSVertex);

                }




            }


            int last_svertex_index = currPath->GetSizeOfSimplifyVertexSet() - 1;
            int last_vertex_index = currPath->GetSimplifyVertexByNum(last_svertex_index)->GetVertexSetSize() - 1;
            Vertex* lastVertex = currPath->GetSimplifyVertexByNum(last_svertex_index)->GetVertexByIndex(last_vertex_index);
            int endExtendedVertex = -1;
            if(lastVertex->GetConnToVertexByIndex(0)._connVertex != NULL /*&& lastVertex->GetConnToVertexByIndex(0)._weight > 0*/)
            {
                Vertex* nearestVertex = (Vertex*)lastVertex->GetConnToVertexByIndex(0)._connVertex;
                int startExtendedVertex = lastVertex->GetCoor()+1;
                endExtendedVertex = nearestVertex->GetCoor()-1;
                seqText = seqText + GetConsensusString(startExtendedVertex,endExtendedVertex);

            }




            if(i<(resPathes->GetSizeOfPathesSet() - 1))
            {
                int i_next = i + 1;
                int last_currSVertex = currPath->GetSizeOfSimplifyVertexSet()-1;
                int last_currVertex = currPath->GetSimplifyVertexByNum(last_currSVertex)->GetVertexSetSize()-1;
                int startCoor = currPath->GetSimplifyVertexByNum(last_currSVertex)->GetVertexByIndex(last_currVertex)->GetCoor();
                int endCoor = resPathes->GetPathByNum(i_next)->GetPath()->GetSimplifyVertexByNum(0)->GetVertexByIndex(0)->GetCoor();
                if(endExtendedVertex > -1)
                {
                    startCoor = endExtendedVertex;
                }


                for(int y = startCoor+1; y < endCoor;y++ )
                {
                    seqText = seqText + "N";
                }

            }


        }

	 


        FastaSequenceRecord fastaSeqRec(conName,seqText);

        fastaFile.AddSeqRecord(fastaSeqRec);

    }

   fastaFile.SaveToFile(fasta_fn.c_str());


}

void SAM_mapping::CreatingVertex(unsigned int refPoint,bool isDeletion, string varText,SetOfRef<Vertex> &currVertexies)
{
    //refPoint = refPoint - 1;
    UniqueReadList tempReadList = GetListOfReadsWithThisTextAtThisPos(varText,refPoint,isDeletion);
    if(tempReadList.GetReadList().GetSizeOfSet() < 1)
    {
        return;
    }
    std::string tempLetter = "";
    char *tempBuf = new char[100];
    itoa(refPoint,tempBuf,10);
    if(isDeletion)
    {
        tempLetter =tempLetter + "DEL@" +varText+"_"+ tempBuf;
    }
    else
    {
        tempLetter =tempLetter  + varText+"_"+ tempBuf;
    }
    SetOf<ConnVertex> conVerFrom;
    SetOf<ConnVertex> conVerTo;
    ConnVertex connVerVal_From;
    connVerVal_From._connVertex = NULL;
    ConnVertex connVerVal_To;
    connVerVal_To._connVertex = NULL;
    conVerFrom.AddToSet(connVerVal_From);
    conVerTo.AddToSet(connVerVal_To);

    Vertex *currVertex = new Vertex(tempReadList,tempLetter,varText,refPoint,conVerFrom,conVerTo);
    currVertexies.AddToSet(currVertex);


    int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();

    delete[] tempBuf;
}

void SAM_mapping::CreatingVertex(unsigned int refPoint,bool isDeletion, string varText,SetOfRef<Vertex> &currVertexies, fstream &fileStreamMismatchPt)
{
    //refPoint = refPoint - 1;
    UniqueReadList tempReadList = GetListOfReadsWithThisTextAtThisPos(varText,refPoint,isDeletion);
    if(tempReadList.GetReadList().GetSizeOfSet() < 1)
    {
        return;
    }
    std::string tempLetter = "";
    char *tempBuf = new char[100];
    itoa(refPoint,tempBuf,10);
    if(isDeletion)
    {
        fileStreamMismatchPt << refPoint << " 0 " << varText <<"\n";
        tempLetter =tempLetter + "DEL@" +varText+"_"+ tempBuf;
    }
    else
    {
        fileStreamMismatchPt << refPoint << " 1 " << varText <<"\n";
        tempLetter =tempLetter  + varText+"_"+ tempBuf;
    }
    SetOf<ConnVertex> conVerFrom;
    SetOf<ConnVertex> conVerTo;
    ConnVertex connVerVal_From;
    connVerVal_From._connVertex = NULL;
    ConnVertex connVerVal_To;
    connVerVal_To._connVertex = NULL;
    conVerFrom.AddToSet(connVerVal_From);
    conVerTo.AddToSet(connVerVal_To);

    Vertex *currVertex = new Vertex(tempReadList,tempLetter,varText,refPoint,conVerFrom,conVerTo);
    currVertexies.AddToSet(currVertex);


    int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();

    delete[] tempBuf;
}

void SAM_mapping::ConnectNotConnectedPrevVertexies(SetOfRef<Vertex> &currVertexies,SetOfRef<Vertex> &lastVertexies, Graph *currGraph)
{
    if(lastVertexies.GetSizeOfSet()>0)
    {
        for(int j = 0;j<lastVertexies.GetSizeOfSet();j++)
        {
            UniqueReadList currLastVertex = lastVertexies.GetItemByNum(j)->GetReadsList();// GetListOfReadsWithThisLetterAtThisPos(lastVertexies.GetItemByNum(j)->GetSymbol().c_str()[0],lastVertexies.GetItemByNum(j)->GetCoor());
            for(int m = 0;m<currVertexies.GetSizeOfSet();m++)
            {
                UniqueReadList currCurrVertex = currVertexies.GetItemByNum(m)->GetReadsList();//GetListOfReadsWithThisLetterAtThisPos(currVertexies.GetItemByNum(m)->GetSymbol().c_str()[0],currVertexies.GetItemByNum(m)->GetCoor());

                int weight = currCurrVertex.FindIntersectionOfLists(currLastVertex.GetReadList());
                if(weight > 0)
        {


                        lastVertexies.GetItemByNum(j)->ConnectToVertex(currVertexies.GetItemByNum(m),weight);
                        currVertexies.GetItemByNum(m)->ConnectFromVertex(lastVertexies.GetItemByNum(j),weight);
        }

            }
        }



    }

    for(int j=0;j<currVertexies.GetSizeOfSet();j++)
    {

        currGraph->AddVertex(currVertexies.GetItemByNum(j));

    }

    if(lastVertexies.GetSizeOfSet()>0)
    {
        SetOfRef<Vertex> notConnectedVertexiesTo;
        SetOfRef<Vertex> connectedVertexiesTo;
        SetOfRef<Vertex> notConnectedVertexiesFrom;
        SetOfRef<Vertex> connectedVertexiesFrom;

        for(int j = 0;j<lastVertexies.GetSizeOfSet();j++)
        {
            Vertex *lastVertexCheck = lastVertexies.GetItemByNum(j);


            if(lastVertexCheck->GetConnToVertexByIndex(0)._connVertex == NULL)
            {
                notConnectedVertexiesTo.AddToSet(lastVertexCheck);
            }
            else
            {
                connectedVertexiesTo.AddToSet(lastVertexCheck);
            }
        }

        for(int j = 0;j<currVertexies.GetSizeOfSet();j++)
        {
            Vertex *currVertexCheck = currVertexies.GetItemByNum(j);


            if(currVertexCheck->GetConnFromVertexByIndex(0)._connVertex == NULL)
            {
                notConnectedVertexiesFrom.AddToSet(currVertexCheck);
            }
            else
            {
                connectedVertexiesFrom.AddToSet(currVertexCheck);
            }
        }

        for(int j = 0; j<notConnectedVertexiesTo.GetSizeOfSet();j++)
        {
            for(int m = 0;m<notConnectedVertexiesFrom.GetSizeOfSet();m++)
            {
                notConnectedVertexiesTo.GetItemByNum(j)->ConnectToVertex(notConnectedVertexiesFrom.GetItemByNum(m),0);
                notConnectedVertexiesFrom.GetItemByNum(m)->ConnectFromVertex(notConnectedVertexiesTo.GetItemByNum(j),0);
            }

        }

        for(int j = 0; j<notConnectedVertexiesTo.GetSizeOfSet();j++)
        {
            for(int m = 0;m<connectedVertexiesFrom.GetSizeOfSet();m++)
            {
                notConnectedVertexiesTo.GetItemByNum(j)->ConnectToVertex(connectedVertexiesFrom.GetItemByNum(m),0);
                connectedVertexiesFrom.GetItemByNum(m)->ConnectFromVertex(notConnectedVertexiesTo.GetItemByNum(j),0);
            }

        }

        for(int j = 0; j<notConnectedVertexiesFrom.GetSizeOfSet();j++)
        {
            for(int m = 0;m<connectedVertexiesTo.GetSizeOfSet();m++)
            {
                notConnectedVertexiesFrom.GetItemByNum(j)->ConnectFromVertex(connectedVertexiesTo.GetItemByNum(m),0);
                connectedVertexiesTo.GetItemByNum(m)->ConnectToVertex(notConnectedVertexiesFrom.GetItemByNum(j),0);
            }
        }

    }
}

int SAM_mapping::FindGaploidsAlgorithm(VariantTextFile &varTxtFile,std::string fileGraph,std::string fileSimpleGraph, std::string resultFileName, std::string fileDebugFileName, std::string scaffFileName,std::string scaffDebugFileName, int maxInsertSize, double fraction)
{

    int sizeOfRef = this->_refSeq.GetSequenceText().length();

    sizeOfRef = 1000000;

    short lettersInThisPos = 0;


    fstream fileStreamGraph(fileGraph.c_str(),fstream::out);
    fstream fileStreamSimpleGraph(fileSimpleGraph.c_str(),fstream::out);
    fstream fileStreamDebug(fileDebugFileName.c_str(),fstream::out);
    fstream fileStreamDebugScaff(scaffDebugFileName.c_str(),fstream::out);

    Graph *currGraph = new Graph();


    double avCovLim = 0.0;


    SetOfRef<Vertex> lastVertexies;

    cout << "Size of Variant Point Set - " << varTxtFile.GetSizeOfVariantPointsSet()<<"\n";

    //varTxtFile.PrintDebug();

    for(int i = 0; i < varTxtFile.GetSizeOfVariantPointsSet();i++)
    {
        VariantPoint currVarPt = varTxtFile.GetVariantPointByNum(i);


        SetOfRef<Vertex> currVertexies;
        bool isAbortJCycle = false;

        if(!currVarPt.IsDeletion() && (currVarPt.GetVariantValueByNum(0).GetVariantText() != "(Complex") && (currVarPt.GetVariantValueByNum(0).GetVariantText() != "(Long"))
        {

            unsigned maxTextLengthOfVarVal = 0;

            for(int j = 0; j < currVarPt.GetSizeOfVariantValues();j++)
            {
                VariantValue currVarVal = currVarPt.GetVariantValueByNum(j);

                if(currVarVal.GetVariantText().length() > maxTextLengthOfVarVal)
                {
                    maxTextLengthOfVarVal = currVarVal.GetVariantText().length();
                }
            }

            if(maxTextLengthOfVarVal > 1)
            {

                SetOf<string> tempSet;
                cout << "-----------------\n";
                cout << "RefPoint - " << currVarPt.GetRefPoint() << "\n";
                tempSet = GetAllDelStrsAtPos(currVarPt.GetRefPoint());

                for(int zk = 0; zk < tempSet.GetSizeOfSet();zk++)
                {
                    cout <<zk << " - " << *tempSet.GetRefItemByNum(zk) << "\n";
                }

                cout << "-----------------\n";
                for(int j = 0; j < maxTextLengthOfVarVal;j++)
                {
                    SetOfRef<Vertex> innerCurrVertexies;

                    for(int k = 0;k < currVarPt.GetSizeOfVariantValues();k++)
                    {
                        VariantValue currVarVal = currVarPt.GetVariantValueByNum(k);

                        if(currVarVal.GetVariantText().length() <= (maxTextLengthOfVarVal-j))
                        {
                            CreatingVertex(currVarPt.GetRefPoint()+j,false,"-",innerCurrVertexies);

                        }
                        else
                        {
                            string varValString = currVarVal.GetVariantText();
                            unsigned lenVarValString = varValString.length();
                            unsigned coorOfInsert = lenVarValString - maxTextLengthOfVarVal + j;
                            CreatingVertex(currVarPt.GetRefPoint()+j,false,varValString.substr(coorOfInsert,1),innerCurrVertexies);


                        }
                    }

                    ConnectNotConnectedPrevVertexies(innerCurrVertexies,lastVertexies,currGraph);
                    lastVertexies = innerCurrVertexies;
                }
                continue;
            }
        }

        for(int j = 0; j < currVarPt.GetSizeOfVariantValues();j++)
        {
            VariantValue currVarVal = currVarPt.GetVariantValueByNum(j);
            SetOf<std::string> setStrs;
            //SetOfVariantValues setStrsVarVal;
            if((currVarVal.GetVariantText() == "(Complex") || (currVarVal.GetVariantText() == "(Long"))
            {

                cout << "In clause pt - " << currVarPt.GetRefPoint() << "\n";
                if(currVarPt.IsDeletion())
                {
                    setStrs = GetAllDelStrsAtPos(currVarPt.GetRefPoint());

                    //*(setStrs.GetRefItemByNum(0)) = "--";
                    int maxLen = 0;
                    for(int zu = 0;zu < setStrs.GetSizeOfSet();zu++)
                    {

                        cout << "setStrs - " << *(setStrs.GetRefItemByNum(zu)) << "\n";
                    }

                    setStrs.AddToSet("--");
                    cout << "setStrs Size - " << setStrs.GetSizeOfSet() << "\n";
                    if((setStrs.GetSizeOfSet() > 1) && (*(setStrs.GetRefItemByNum(0)) != ""))
                    {
                        cout << "We are here \n";
                        unsigned int *weights = new unsigned[setStrs.GetSizeOfSet()];
                        unsigned int maxWeight = 0;

                        for(int k = 0; k < setStrs.GetSizeOfSet();k++)
                        {
                            weights[k] = GetListOfReadsWithThisTextAtThisPos(*(setStrs.GetRefItemByNum(k)),currVarPt.GetRefPoint(),currVarPt.IsDeletion()).GetReadList().GetSizeOfSet();
                            if(weights[k] > maxWeight)
                            {
                                maxWeight = weights[k];
                            }
                        }
                        int countPassedFilter = 0;
                        for(int k = 0; k < setStrs.GetSizeOfSet();k++)
                        {
                            if(weights[k] > maxWeight*fraction)
                            {
                                countPassedFilter++;

                            }
                        }
                        cout << "Count passed filter - " << countPassedFilter<<" \n";
                        if(countPassedFilter > 1)
                        {
                            SetOfRef<Vertex> innerCurrVertexies;
                            for(int k = 0; k < setStrs.GetSizeOfSet();k++)
                            {
                                if(weights[k] > maxWeight*fraction)
                                {

                                    CreatingVertex(currVarPt.GetRefPoint(),true,*(setStrs.GetRefItemByNum(k)),innerCurrVertexies);
                                }
                            }

                            ConnectNotConnectedPrevVertexies(innerCurrVertexies,lastVertexies,currGraph);

                            lastVertexies = innerCurrVertexies;

                        }


                        cout << "And we are here \n";

                        delete [] weights;
                    }
                    else
                    {
                        break;
                    }
                }

                unsigned int startPt = currVarPt.GetRefPoint();
                unsigned int endPt = -1;
                if(i < (varTxtFile.GetSizeOfVariantPointsSet() - 1))
                {
                    endPt = varTxtFile.GetVariantPointByNum(i+1).GetRefPoint() - 1;
                }
                else
                {
                    endPt = _refSeq.GetSequenceText().length()-1;
                }



                cout << "End clause pt - " << currVarPt.GetRefPoint() << "\n";
                cout << "startPt - " << startPt << "\n";
                cout << "endPt - " << endPt << "\n";

                for(int k = startPt; k <= endPt;k++)
                {
                    SetOfRef<Vertex> innerCurrVertexies;
                    lettersInThisPos = FindWhatLetterIsCorrectAtThisPos(i);

                    if((lettersInThisPos == OnlyA) || (lettersInThisPos == OnlyC) || (lettersInThisPos == OnlyG)
                            || (lettersInThisPos == OnlyT) || (lettersInThisPos == OnlyIns) || (lettersInThisPos == 0))
                    {

                        continue;
                    }

                    if(lettersInThisPos & OnlyA)
                    {
                        CreatingVertex(k,false,"A",innerCurrVertexies);
                    }
                    if(lettersInThisPos & OnlyC)
                    {
                        CreatingVertex(k,false,"C",innerCurrVertexies);
                    }
                    if(lettersInThisPos & OnlyG)
                    {
                        CreatingVertex(k,false,"G",innerCurrVertexies);
                    }
                    if(lettersInThisPos & OnlyT)
                    {
                        CreatingVertex(k,false,"T",innerCurrVertexies);
                    }
                    if(lettersInThisPos & OnlyIns)
                    {
                        CreatingVertex(k,false,"-",innerCurrVertexies);
                    }

                    ConnectNotConnectedPrevVertexies(innerCurrVertexies,lastVertexies,currGraph);

                    lastVertexies = innerCurrVertexies;



                }
                isAbortJCycle = true;
                break;
            }
            if(currVarPt.GetRefPoint() == 8380)
            {
                cout << "Before CreatingVertex\n";
            }
            CreatingVertex(currVarPt.GetRefPoint(),currVarPt.IsDeletion(),currVarVal.GetVariantText(),currVertexies);
            if(currVarPt.GetRefPoint() == 8380)
            {
                cout << "After CreatingVertex\n";
            }


            /*UniqueReadList tempReadList = GetListOfReadsWithThisTextAtThisPos(currVarVal.GetVariantText(),currVarPt.GetRefPoint(),currVarPt.IsDeletion());
            if(tempReadList.GetReadList().GetSizeOfSet() < 1)
            {
                continue;
            }
            std::string tempLetter = "";
            char *tempBuf = new char[100];
            itoa(i,tempBuf,10);
            if(currVarPt.IsDeletion())
            {
                tempLetter =tempLetter + "DEL@" +currVarVal.GetVariantText()+"_"+ tempBuf;
            }
            else
            {
                tempLetter =tempLetter  + currVarVal.GetVariantText()+"_"+ tempBuf;
            }
            SetOf<ConnVertex> conVerFrom;
            SetOf<ConnVertex> conVerTo;
            ConnVertex connVerVal_From;
            connVerVal_From._connVertex = NULL;
            ConnVertex connVerVal_To;
            connVerVal_To._connVertex = NULL;
            conVerFrom.AddToSet(connVerVal_From);
            conVerTo.AddToSet(connVerVal_To);

            Vertex *currVertex = new Vertex(tempReadList,tempLetter,currVarVal.GetVariantText(),i,conVerFrom,conVerTo);
            currVertexies.AddToSet(currVertex);


            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();

            delete[] tempBuf;*/


        }

        if((currVertexies.GetSizeOfSet() < 2) || (isAbortJCycle))
        {
            continue;
        }


        ConnectNotConnectedPrevVertexies(currVertexies,lastVertexies,currGraph);






        lastVertexies = currVertexies;



    }


    int countVertexWithToNull = 0;
    for(int i = 0; i < currGraph->GetVertexSetSize();i++)
    {
        Vertex *currVertex = currGraph->GetVertexByIndex(i);

        if(currVertex->GetConnToVertexByIndex(0)._connVertex == NULL)
        {
            cout << "NULL vertex pos - " << currVertex->GetCoor() << "\n";
            countVertexWithToNull++;
        }
    }

    cout << "countVertexWithToNull - " << countVertexWithToNull << "\n";


    SimplifyGraph *simplGraph = new SimplifyGraph();

    currGraph->FillFirstVertexies();
    currGraph->PrintGraph(fileStreamGraph);

    simplGraph->EaseGraph(currGraph);
    simplGraph->FindFirstVertex();
    simplGraph->PrintGraph(fileStreamSimpleGraph);


   SetOfRef<Path> *resultPathes = new SetOfRef<Path>();
   SetOfRef<Path> *pathesToFree = new SetOfRef<Path>();

   simplGraph->GetAndPrintPath_Debug(fileStreamDebug,4,resultPathes,pathesToFree);




//PrintFastaWithResultContigsByPathes(resultFileName,resultPathes,fileStreamDebug);





 Scaffolder scaff;



 scaff.Scaffolding(resultPathes,maxInsertSize);


 PrintScaffoldsToFasta(scaffFileName,&scaff,fileStreamDebug);

scaff.Clear();















    //allConflictPointsFile.close();
    fileStreamDebug.close();
    fileStreamGraph.close();
    fileStreamSimpleGraph.close();
    fileStreamDebugScaff.close();

    delete currGraph;
    delete simplGraph;


    return AllOk;
}

























int SAM_mapping::FindGaploidsAlgorithm(std::string fileGraph,std::string fileSimpleGraph, std::string resultFileName, std::string fileDebugFileName, std::string scaffFileName,std::string scaffDebugFileName, int maxInsertSize, double fraction)
{

    int sizeOfRef = this->_refSeq.GetSequenceText().length();

    sizeOfRef = 1000000;

    short lettersInThisPos = 0;


    fstream fileStreamGraph(fileGraph.c_str(),fstream::out);
    fstream fileStreamSimpleGraph(fileSimpleGraph.c_str(),fstream::out);
    fstream fileStreamDebug(fileDebugFileName.c_str(),fstream::out);
    fstream fileStreamDebugScaff(scaffDebugFileName.c_str(),fstream::out);

    Graph *currGraph = new Graph();


    double avCovLim = 0.0;


    for(int i =1;i <= sizeOfRef;i++)
    {
        int currCov = CountCoverageAtThisPos(i);

        avCovLim += currCov;
    }

    avCovLim = avCovLim/sizeOfRef;
    avCovLim = avCovLim*_fractionOfAvCov;

    SetOfRef<Vertex> lastVertexies;

    //cout << "Size of Variant Point Set - " << varTxtFile.GetSizeOfVariantPointsSet()<<"\n";

    //varTxtFile.PrintDebug();

    for(int i = 1; i < sizeOfRef;i++)
    {
        SetOfRef<Vertex> currVertexies;

        int currCov = CountCoverageAtThisPos(i);

        //if((currCov < avCovLim) || (currCov < 10)) continue;
        if(currCov < 5) continue;
        lettersInThisPos = 0;

        lettersInThisPos = FindWhatLetterIsCorrectAtThisPos(i);

        if((lettersInThisPos != OnlyA) && (lettersInThisPos != OnlyC) && (lettersInThisPos != OnlyG)
                && (lettersInThisPos != OnlyT) && (lettersInThisPos != OnlyIns) && (lettersInThisPos != 0))
        {

            if(lettersInThisPos & OnlyA)
            {
                CreatingVertex(i,false,"A",currVertexies);
            }
            if(lettersInThisPos & OnlyC)
            {
                CreatingVertex(i,false,"C",currVertexies);
            }
            if(lettersInThisPos & OnlyG)
            {
                CreatingVertex(i,false,"G",currVertexies);
            }
            if(lettersInThisPos & OnlyT)
            {
                CreatingVertex(i,false,"T",currVertexies);
            }
            if(lettersInThisPos & OnlyIns)
            {
                CreatingVertex(i,false,"-",currVertexies);
            }

            ConnectNotConnectedPrevVertexies(currVertexies,lastVertexies,currGraph);

            lastVertexies = currVertexies;
        }





        //SetOfRef<Vertex> currVertexiesAdd;



        SetOf<std::string> setStrs;
        setStrs = GetAllDelStrsAtPos(i);


        if(setStrs.GetSizeOfSet() == 0)
        {
            continue;
        }


        setStrs.AddToSet("--");

        unsigned int *weights = new unsigned[setStrs.GetSizeOfSet()];
        unsigned int maxWeight = 0;

        for(int k = 0; k < setStrs.GetSizeOfSet();k++)
        {
            weights[k] = GetListOfReadsWithThisTextAtThisPos(*(setStrs.GetRefItemByNum(k)),i,true).GetReadList().GetSizeOfSet();
            if(weights[k] > maxWeight)
            {
                maxWeight = weights[k];
            }
        }


        int countPassedFilter = 0;
        for(int k = 0; k < setStrs.GetSizeOfSet();k++)
        {


            if(weights[k] > maxWeight*fraction)
            {
                countPassedFilter++;

            }
        }



        if(countPassedFilter > 1)
        {
            SetOfRef<Vertex> innerCurrVertexies;
            for(int k = 0; k < setStrs.GetSizeOfSet();k++)
            {
                if(weights[k] > maxWeight*fraction)
                {

                    CreatingVertex(i,true,*(setStrs.GetRefItemByNum(k)),innerCurrVertexies);
                }
            }

            ConnectNotConnectedPrevVertexies(innerCurrVertexies,lastVertexies,currGraph);

            lastVertexies = innerCurrVertexies;

        }



        delete [] weights;

    }




    currGraph->FillFirstVertexies();
    currGraph->PrintGraph(fileStreamGraph);





/*


    int countVertexWithToNull = 0;
    for(int i = 0; i < currGraph->GetVertexSetSize();i++)
    {
        Vertex *currVertex = currGraph->GetVertexByIndex(i);

        if(currVertex->GetConnToVertexByIndex(0)._connVertex == NULL)
        {

            countVertexWithToNull++;
        }
    }




    SimplifyGraph *simplGraph = new SimplifyGraph();

    currGraph->FillFirstVertexies();
    currGraph->PrintGraph(fileStreamGraph);

    simplGraph->EaseGraph(currGraph);
    simplGraph->FindFirstVertex();
    simplGraph->PrintGraph(fileStreamSimpleGraph);


 SetOfRef<Path> *resultPathes = new SetOfRef<Path>();
 SetOfRef<Path> *pathesToFree = new SetOfRef<Path>();

 simplGraph->GetAndPrintPath_Debug(fileStreamDebug,4,resultPathes,pathesToFree);




PrintFastaWithResultContigsByPathes(resultFileName,resultPathes,fileStreamDebug);





Scaffolder scaff;



scaff.Scaffolding(resultPathes,maxInsertSize);

long int lastSizeOfScaffSet = scaff.GetSizeOfConsScaffoldSet();

long int currSizeOfScaffSet = -1;


while((lastSizeOfScaffSet - currSizeOfScaffSet) > 0)
{

    if(currSizeOfScaffSet != -1)
    {
        lastSizeOfScaffSet = currSizeOfScaffSet;
    }

    currSizeOfScaffSet = scaff.InnerScaffolding(maxInsertSize);


}

PrintScaffoldsToFasta(scaffFileName,&scaff,fileStreamDebug);

fstream finderScaffolderErrors("scaffErrors.txt",fstream::out);




for(int i =0; i < scaff.GetSizeOfConsScaffoldSet();i++)
{
    ConsiderScaffold *currScaffA = scaff.GetConsScaffoldByIndex(i);

    char *tempBuf = new char[100];
    itoa(i,tempBuf,10);

    string scaffNamA = "";
    scaffNamA = scaffNamA + "Scaffolder_" +tempBuf;

    finderScaffolderErrors << scaffNamA;

    delete [] tempBuf;

    for(int j = 0;j < scaff.GetSizeOfConsScaffoldSet();j++)
    {
        if(j == i) continue;

        ConsiderScaffold *currScaffB = scaff.GetConsScaffoldByIndex(j);

        if((currScaffA->GetStartPos() <= currScaffB->GetStartPos()) && (currScaffB->GetStartPos() <= currScaffA->GetEndPos())) continue;

        int connectWeight = currScaffA->CheckConnectionBeetweenScaffolds(currScaffB);

        if(connectWeight > 0)
        {
            tempBuf = new char[100];
            itoa(j,tempBuf,10);

            string scaffNamB = "";
            scaffNamB = scaffNamB + "Scaffolder_" +tempBuf;

            finderScaffolderErrors <<" " << scaffNamB << " " << connectWeight;

            delete [] tempBuf;
        }
    }

    finderScaffolderErrors << "\n";
}





scaff.Clear();














    finderScaffolderErrors.close();

*/
    //allConflictPointsFile.close();
    fileStreamDebug.close();
    fileStreamGraph.close();
    fileStreamSimpleGraph.close();
    fileStreamDebugScaff.close();

    delete currGraph;
    //delete simplGraph;


    return AllOk;
}




int SAM_mapping::CreateMismatchPtsFile(std::string mismatchPtFileName, double fraction,unsigned minCov,unsigned maxCov)
{

    int sizeOfRef = this->_refSeq.GetSequenceText().length();

    //sizeOfRef = 1000000;

    short lettersInThisPos = 0;



    fstream fileStreamMismatchPt(mismatchPtFileName.c_str(),fstream::out);



  /*  double avCovLim = 0.0;


    for(int i =1;i <= sizeOfRef;i++)
    {
        int currCov = CountCoverageAtThisPos(i);

        avCovLim += currCov;
    }

    avCovLim = avCovLim/sizeOfRef;
    avCovLim = avCovLim*_fractionOfAvCov;

*/

    for(int i = 1; i < sizeOfRef;i++)
    {


        int currCov = CountCoverageAtThisPos(i);
        if((currCov < minCov) || (currCov > maxCov)) continue;
        lettersInThisPos = 0;

        lettersInThisPos = FindWhatLetterIsCorrectAtThisPos(i);

        if((lettersInThisPos != OnlyA) && (lettersInThisPos != OnlyC) && (lettersInThisPos != OnlyG)
                && (lettersInThisPos != OnlyT) && (lettersInThisPos != OnlyIns) && (lettersInThisPos != 0))
        {



            if(lettersInThisPos & OnlyA)
            {

                int covLetter = 0;
                covLetter = this->CountNumOfLetterInReadsAtRefPos('A',i);
                fileStreamMismatchPt << i << " 1 A " /*<< covLetter */<< "\n";
            }
            if(lettersInThisPos & OnlyC)
            {
                int covLetter = 0;
                covLetter = this->CountNumOfLetterInReadsAtRefPos('C',i);
                fileStreamMismatchPt << i << " 1 C " /*<< covLetter */<< "\n";
            }
            if(lettersInThisPos & OnlyG)
            {
                int covLetter = 0;
                covLetter = this->CountNumOfLetterInReadsAtRefPos('G',i);
                fileStreamMismatchPt << i << " 1 G " /*<< covLetter */<< "\n";
            }
            if(lettersInThisPos & OnlyT)
            {
                int covLetter = 0;
                covLetter = this->CountNumOfLetterInReadsAtRefPos('T',i);
                fileStreamMismatchPt << i << " 1 T " /*<< covLetter */<< "\n";
            }
            if(lettersInThisPos & OnlyIns)
            {
                int covLetter = 0;
                covLetter = this->CountNumOfLetterInReadsAtRefPos('-',i);
                fileStreamMismatchPt << i << " 1 - " /*<< covLetter */<< "\n";
            }

        }








        SetOf<std::string> setStrs;
        setStrs = GetAllDelStrsAtPos(i);


        if(setStrs.GetSizeOfSet() == 0)
        {
            continue;
        }


        setStrs.AddToSet("--");

        unsigned int *weights = new unsigned[setStrs.GetSizeOfSet()];
        unsigned int maxWeight = 0;

        for(int k = 0; k < setStrs.GetSizeOfSet();k++)
        {
            weights[k] = GetListOfReadsWithThisTextAtThisPos(*(setStrs.GetRefItemByNum(k)),i,true).GetReadList().GetSizeOfSet();
            if(weights[k] > maxWeight)
            {
                maxWeight = weights[k];
            }
        }


        int countPassedFilter = 0;
        for(int k = 0; k < setStrs.GetSizeOfSet();k++)
        {


            if(weights[k] > maxWeight*fraction)
            {
                countPassedFilter++;

            }
        }



        if(countPassedFilter > 1)
        {
            for(int k = 0; k < setStrs.GetSizeOfSet();k++)
            {
                if(weights[k] > maxWeight*fraction)
                {
                    fileStreamMismatchPt << i << " 0 " << *(setStrs.GetRefItemByNum(k)) <<"\n";
                }
            }
        }



        delete [] weights;

    }


    fileStreamMismatchPt.close();


    return AllOk;
}

void SAM_mapping::CountConnectionByPEreadsBetweenScaffs(Scaffolder &scaff)
{
    fstream connectionScaffs("connectionScaffs.txt",fstream::out);

    for(int i = 0;i < scaff.GetSizeOfConsScaffoldSet();i++)
    {
        for(int j = 0; j < scaff.GetSizeOfConsScaffoldSet();j++)
        {
            if(i == j) continue;
            ConsiderScaffold *currScaffA = scaff.GetConsScaffoldByIndex(i);
            ConsiderScaffold *currScaffB = scaff.GetConsScaffoldByIndex(j);

            long int weight = currScaffA->CheckConnectionBeetweenScaffolds(currScaffB);

            if(weight > 0)
            {
                connectionScaffs << i << " " << j << " " << weight << "\n";
            }
        }

    }


    for(int i = 0;i < scaff.GetSizeOfConsScaffoldSet();i++)
    {
        ConsiderScaffold *currScaffA = scaff.GetConsScaffoldByIndex(i);
        connectionScaffs << "Scaffold_" << i <<  " " << currScaffA->GetStartPos() << " " << currScaffA->GetEndPos() << "\n";




    }




    connectionScaffs.close();

}





void SAM_mapping::CountConnectionByPEreadsBetweenPathes(SetOfRef<Path> *pathes)
{
    fstream connectionPathes("connectionPathes.txt",fstream::out);



    for(int i = 0;i < pathes->GetSizeOfSet();i++)
    {
        Path *currPathA = pathes->GetItemByNum(i);
        connectionPathes << "Contigs_" << i <<  " " << currPathA->GetName() << " ";
        connectionPathes << currPathA->GetFullReadList()->GetReadListRef()->GetSizeOfSet();
        connectionPathes << "\n";




    }


    for(int i = 0;i < pathes->GetSizeOfSet();i++)
    {
        for(int j = 0; j < pathes->GetSizeOfSet();j++)
        {
            if(i == j) continue;
            Path *currPathA = pathes->GetItemByNum(i);
            Path *currPathB = pathes->GetItemByNum(j);

            long int weight = currPathA->CheckPathConnectivityByPEReads(currPathB);

            if(weight > 0)
            {
                connectionPathes << i << " " << j << " " << weight << "\n";
            }
        }

    }







    connectionPathes.close();

}


void FoundDuplicatePathes(SetOfRef<Path> *resultPathes)
{
    int countEqualPathes = 0;
    for(int i = 0;i<resultPathes->GetSizeOfSet();i++)
    {
        Path *currResPathA = resultPathes->GetItemByNum(i);
        int resPathASVertexSize = currResPathA->GetSizeOfSimplifyVertexSet();
        for(int j = 0; j<resultPathes->GetSizeOfSet();j++)
        {
            if(i == j) continue;
            Path *currResPathB = resultPathes->GetItemByNum(j);
            int resPathBSVertexSize = currResPathB->GetSizeOfSimplifyVertexSet();

            if(resPathASVertexSize != resPathBSVertexSize) continue;

            bool isNotFoundEqualSVertex = false;
            for(int k = 0; k < currResPathA->GetSizeOfSimplifyVertexSet();k++)
            {
                SimplifyVertex *currSVertexA = currResPathA->GetSimplifyVertexByNum(k);
                SimplifyVertex *currSVertexB = currResPathB->GetSimplifyVertexByNum(k);

                if(currSVertexA != currSVertexB)
                {
                    isNotFoundEqualSVertex = true;
                    break;
                }



            }

            if(isNotFoundEqualSVertex)
            {
                continue;
            }
            else
            {
                countEqualPathes++;
                cout << "i - " << i << " " << currResPathA->GetName() << "\n";
                cout << "j - " << j << " " << currResPathB->GetName() << "\n";
                break;
            }
        }
    }

    cout << "countEqualPathes - " <<countEqualPathes << "\n";
}

void FoundDuplicateScaffs(Scaffolder *scaff)
{



    int countEqualScaffs = 0;
    for(int i = 0;i<scaff->GetSizeOfConsScaffoldSet();i++)
    {
        ConsiderScaffold *currScaffA = scaff->GetConsScaffoldByIndex(i);
        int scaffAPathSize = currScaffA->GetSizeOfPathesSet();
        for(int j = 0; j<scaff->GetSizeOfConsScaffoldSet();j++)
        {
            if(i == j) continue;
            ConsiderScaffold *currScaffB = scaff->GetConsScaffoldByIndex(j);
            int scaffBPathSize = currScaffB->GetSizeOfPathesSet();



            if(scaffAPathSize != scaffBPathSize) continue;

            bool isNotFoundEqualPath = false;
            for(int k = 0; k < currScaffA->GetSizeOfPathesSet();k++)
            {
                Path *currPathA = currScaffA->GetPathByNum(k)->GetPath();
                Path *currPathB = currScaffB->GetPathByNum(k)->GetPath();

                if(currPathA != currPathB)
                {
                    isNotFoundEqualPath = true;
                    break;
                }



            }

            if(isNotFoundEqualPath)
            {
                continue;
            }
            else
            {
                countEqualScaffs++;
                break;
            }
        }
    }

    cout << "countEqualScaffs - " <<countEqualScaffs << "\n";
}


int SAM_mapping::FindGaploidsFromMismatchPtsAlgorithm(std::string fileGraph,std::string fileSimpleGraph, std::string resultFileName, std::string fileDebugFileName, std::string scaffFileName,std::string scaffDebugFileName, int maxInsertSize, double fraction,std::string mismatchPtsFileName,unsigned maxPosition)
{

    int sizeOfRef = this->_refSeq.GetSequenceText().length();

    if(maxPosition == 0)
    {
        maxPosition = sizeOfRef +100;
    }

    short lettersInThisPos = 0;


    fstream fileStreamGraph(fileGraph.c_str(),fstream::out);
    fstream fileStreamSimpleGraph(fileSimpleGraph.c_str(),fstream::out);
    fstream fileStreamDebug(fileDebugFileName.c_str(),fstream::out);
    fstream fileStreamDebugScaff(scaffDebugFileName.c_str(),fstream::out);






    Graph *currGraph = new Graph();


    double avCovLim = 0.0;


    for(int i =1;i <= sizeOfRef;i++)
    {
        int currCov = CountCoverageAtThisPos(i);

        avCovLim += currCov;
    }

    avCovLim = avCovLim/sizeOfRef;
    avCovLim = avCovLim*_fractionOfAvCov;

    MismatchPointsFile mismatchPtsFile(mismatchPtsFileName);

    SetOfRef<Vertex> lastVertexies;

    for(int i = 0;i < mismatchPtsFile.GetSizeOfPositionsSet();i++)
    {
        SetOfRef<Vertex> currVertexies;

        unsigned currPosition = mismatchPtsFile.GetPositionsByNum(i);

        if(currPosition > maxPosition)
        {
            continue;
        }




        SetOfRef<MismatchVariant> notInsertVars;
        SetOfRef<MismatchVariant> insertVars;


        mismatchPtsFile.GetVarsByPosition(currPosition,notInsertVars,insertVars);


        for(int j = 0;j < notInsertVars.GetSizeOfSet();j++)
        {
            MismatchVariant *currMismatchVar = notInsertVars.GetItemByNum(j);
            CreatingVertex(currMismatchVar->position,currMismatchVar->isDeletion,currMismatchVar->varText,currVertexies);

        }

        if(notInsertVars.GetSizeOfSet() > 0)
        {
            ConnectNotConnectedPrevVertexies(currVertexies,lastVertexies,currGraph);

            lastVertexies = currVertexies;
        }


        if(insertVars.GetSizeOfSet() == 0)
        {
            continue;
        }




        SetOf<std::string> setStrs;
        for(int j = 0; j < insertVars.GetSizeOfSet();j++)
        {
            MismatchVariant *currMismatchVar = insertVars.GetItemByNum(j);

            setStrs.AddToSet(currMismatchVar->varText);


        }







        unsigned int *weights = new unsigned[setStrs.GetSizeOfSet()];
        unsigned int maxWeight = 0;

        for(int k = 0; k < setStrs.GetSizeOfSet();k++)
        {
            weights[k] = GetListOfReadsWithThisTextAtThisPos(*(setStrs.GetRefItemByNum(k)),currPosition,true).GetReadList().GetSizeOfSet();
            if(weights[k] > maxWeight)
            {
                maxWeight = weights[k];
            }
        }


        int countPassedFilter = 0;
        for(int k = 0; k < setStrs.GetSizeOfSet();k++)
        {


            if(weights[k] > maxWeight*fraction)
            {
                countPassedFilter++;

            }
        }



        if(countPassedFilter > 1)
        {

            SetOfRef<Vertex> innerCurrVertexies;
            for(int k = 0; k < setStrs.GetSizeOfSet();k++)
            {
                if(weights[k] > maxWeight*fraction)
                {

                    CreatingVertex(currPosition,true,*(setStrs.GetRefItemByNum(k)),innerCurrVertexies);
                }
            }



            ConnectNotConnectedPrevVertexies(innerCurrVertexies,lastVertexies,currGraph);

            lastVertexies = innerCurrVertexies;

        }



        delete [] weights;

    }









    //currGraph->FillFirstVertexies();
    //currGraph->PrintGraph(fileStreamGraph);






  /*  int countVertexWithToNull = 0;
    for(int i = 0; i < currGraph->GetVertexSetSize();i++)
    {
        Vertex *currVertex = currGraph->GetVertexByIndex(i);

        if(currVertex->GetConnToVertexByIndex(0)._connVertex == NULL)
        {

            countVertexWithToNull++;
        }
    }*/




    SimplifyGraph *simplGraph = new SimplifyGraph();

    currGraph->FillFirstVertexies();
    currGraph->PrintGraph(fileStreamGraph);

	simplGraph->EaseGraph_simple(currGraph);
    simplGraph->FindFirstVertex();
    simplGraph->PrintGraph(fileStreamSimpleGraph);

    simplGraph->CountStartEndContinueSVertexLists();


   SetOfRef<Path> *resultPathes = new SetOfRef<Path>();
   SetOfRef<Path> *pathesToFree = new SetOfRef<Path>();

   simplGraph->GetAndPrintPath_Debug(fileStreamDebug,4,resultPathes,pathesToFree);



   PrintFastaWithResultContigsByPathes(resultFileName,resultPathes,fileStreamDebug);

   CountConnectionByPEreadsBetweenPathes(resultPathes);

for(int i = 0; i < resultPathes->GetSizeOfSet();i++)
{
    resultPathes->GetItemByNum(i)->SetIndexInResPath(i);
}


FoundDuplicatePathes(resultPathes);

Scaffolder scaff;

scaff.Scaffolding(resultPathes,maxInsertSize);
scaff.SortSet();
//cout << "Start Scaffolds\n";
//scaff.PrintScaffoldsToSVertex();
//cout << "*****************\n";
scaff.PackScaffolds();
//cout << "End Scaffolds\n";
//scaff.PrintScaffoldsToSVertex();
//cout << "*****************\n";
PrintScaffoldsToFasta(scaffFileName,&scaff,fileStreamDebug);


//FoundDuplicateScaffs(&scaff);
int countAboveOnePathInScaff = 0;

for(int i = 0; i < scaff.GetSizeOfScaffoldSet();i++)
{

    cout << "ConsScaff i - " << i << " " << scaff.GetConsScaffoldByIndex(i)->GetSizeOfPathesSet() << "\n";
    if(scaff.GetConsScaffoldByIndex(i)->GetSizeOfPathesSet() > 1)
    {
        countAboveOnePathInScaff++;
    }
}

cout << "countAboveOnePathInScaff - " << countAboveOnePathInScaff << "\n";



scaff.CheckEqualitySetOfScaffs();
/*
long int lastSizeOfScaffSet = scaff.GetSizeOfConsScaffoldSet();

long int currSizeOfScaffSet = -1;


while((lastSizeOfScaffSet - currSizeOfScaffSet) > 0)
{

	if(currSizeOfScaffSet != -1)
	{
		lastSizeOfScaffSet = currSizeOfScaffSet;
	}

	currSizeOfScaffSet = scaff.InnerScaffolding(maxInsertSize);


}
*/


CountConnectionByPEreadsBetweenScaffs(scaff);







//fstream finderScaffolderErrors("scaffErrors.txt",fstream::out);

/*

for(int i =0; i < scaff.GetSizeOfConsScaffoldSet();i++)
{
	ConsiderScaffold *currScaffA = scaff.GetConsScaffoldByIndex(i);

	char *tempBuf = new char[100];
	itoa(i,tempBuf,10);

	string scaffNamA = "";
	scaffNamA = scaffNamA + "Scaffolder_" +tempBuf;

  //	finderScaffolderErrors << scaffNamA;

	delete [] tempBuf;

	for(int j = 0;j < scaff.GetSizeOfConsScaffoldSet();j++)
	{
		if(j == i) continue;

		ConsiderScaffold *currScaffB = scaff.GetConsScaffoldByIndex(j);

		if((currScaffA->GetStartPos() <= currScaffB->GetStartPos()) && (currScaffB->GetStartPos() <= currScaffA->GetEndPos())) continue;

		int connectWeight = currScaffA->CheckConnectionBeetweenScaffolds(currScaffB);

		if(connectWeight > 0)
		{
			tempBuf = new char[100];
			itoa(j,tempBuf,10);

			string scaffNamB = "";
			scaffNamB = scaffNamB + "Scaffolder_" +tempBuf;

	//		finderScaffolderErrors <<" " << scaffNamB << " " << connectWeight;

			delete [] tempBuf;
		}
	}

	//finderScaffolderErrors << "\n";
}



*/

//scaff.Clear();











  delete resultPathes;
  delete pathesToFree;


  // finderScaffolderErrors.close();
	//allConflictPointsFile.close();
	fileStreamDebug.close();
	fileStreamGraph.close();
	fileStreamSimpleGraph.close();
	fileStreamDebugScaff.close();


    delete currGraph;
    delete simplGraph;

    cout << "End of count\n";

	return AllOk;
}



void SAM_mapping::SplitRefSeqByCoverage(unsigned minCov, unsigned maxCov, std::string refConNam, std::string splitFileName)
{
    int sizeOfRef = this->_refSeq.GetSequenceText().length();


    FastaSequenceFileBuf fileWithSplitedContigs;

    unsigned startPos = 0;
    unsigned endPos = 0;
    bool isWrited = false;
    std::string seqText = "";

    for(int i = 0; i < sizeOfRef;i++)
    {
        int currCov = CountCoverageAtThisPos(i);
        if((currCov < minCov) || (currCov > maxCov))
        {
            if(!isWrited)
            {
                endPos = i;

                std::string seqNam = "";

                char *tempBuf = new char[255];
                sprintf(tempBuf,"%d_%d",startPos,endPos);

                seqNam = seqNam + ">" + refConNam + "_" + tempBuf;

                delete []tempBuf;

                FastaSequenceRecord fastaSeqRec(seqNam,seqText);

                fileWithSplitedContigs.AddSeqRecord(fastaSeqRec);

                isWrited = true;

            }

            continue;
        }
        else
        {
            if(isWrited)
            {
                startPos = i+1;
                isWrited = false;
                seqText = "";

            }

            seqText = seqText + _refSeq.GetCharOfSequenceTextByNum(i);
        }
    }



    fileWithSplitedContigs.SaveToFile(splitFileName.c_str());





}
