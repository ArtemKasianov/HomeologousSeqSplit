#include "sam_mapping.h"



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


	Read_Hit ReadHitToWrite(_qName,_position, _qReadText, _qQualText,_qReadMapText,_qQualMapText);

    FastqSequenceRecord readToAdd(_qName,_qReadText,_qQualText);

    _readHitsArray.AddToSet(ReadHitToWrite);

    _allReads.Add(readToAdd);

    ReadNextLine();
	numberOfHit++;


  }

  //cout << "numberOfHit=" << numberOfHit << "\n";
  //cout << "_readHitsArray_size" << _readHitsArray.GetSizeOfSet() << "\n";


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
        resultStr = resultStr + this->_refSeq.GetCharOfSequenceTextByNum(i);
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
  cout << "startLoadingHits" << "\n";
  int countSets = sizeOfRef/1000 + 1;
  cout << countSets << "\n";

  for(int i = 0;i<countSets;i++)
  {
      SetOfRead_Hit currSetOfReadHits;
      _readHitsListArray.AddToSet(currSetOfReadHits);
  }

  while(!_isFileEnd)
  {

    //cout << "numberOfHit-" <<numberOfHit <<"\n";
    //cout << "position-" <<_position <<"\n";

      int currReadHitSet = _position/1000;
      //cout << "currReadHitSet-" <<currReadHitSet << " " << "countSets-" <<countSets<<"\n";

//      if(currReadHitSet > 13362)
//      {
//          cout << "currReadHitSet-" <<currReadHitSet << " " << "countSets-" <<countSets<<"\n";
//      }

//      if(currReadHitSet == 2231)
//      {
//          cout << "numberOfHit-" <<numberOfHit <<"\n";
//          cout << "position-" <<_position <<"\n";
//          cout << "currReadHitSet-" <<currReadHitSet << " " << "countSets-" <<countSets<<"\n";
//      }

//      if(currReadHitSet == 2250)
//      {
//          cout << "currReadHitSet-" <<currReadHitSet << " " << "countSets-" <<countSets<<"\n";
//      }

//      if(currReadHitSet == 2260)
//      {
//          cout << "currReadHitSet-" <<currReadHitSet << " " << "countSets-" <<countSets<<"\n";
//      }
//      if(_position == 2231751)
//      {
//          cout << "Start Position work\n";
//      }
    Read_Hit ReadHitToWrite(_qName,_position, _qReadText, _qQualText,_qReadMapText,_qQualMapText);
//    if(_position == 2231751)
//    {
//        cout << "after ReadHitToWrite\n";
//    }
    FastqSequenceRecord readToAdd(_qName,_qReadText,_qQualText);
//    if(_position == 2231751)
//    {
//        cout << "after readToAdd\n";
//    }
    _readHitsArray.AddToSet(ReadHitToWrite);
//    if(_position == 2231751)
//    {
//        cout << "after _readHitsArray.AddToSet\n";
//    }

    SetOfRead_Hit *rHitsList = _readHitsListArray.GetRefItemByNum(currReadHitSet);

//    if(_position == 2231751)
//    {
//        cout << "SetOfRead_Hit_Lists *rHitsList = _readHitsListArray.GetRefItemByNum(currReadHitSet);\n";
//    }



    _readHitsListArray.GetRefItemByNum(currReadHitSet)->AddToSet(ReadHitToWrite);
//    if(_position == 2231751)
//    {
//        cout << "after _readHitsListArray.GetRefItemByNum(currReadHitSet)->AddToSet(ReadHitToWrite);\n";
//    }
    _allReads.Add(readToAdd);
//    if(_position == 2231751)
//    {
//        cout << "after _allReads.Add(readToAdd);\n";
//    }
    ReadNextLine();
//    if(_position == 2231751)
//    {
//        cout << "after ReadNextLine\n";
//    }
    numberOfHit++;


  }

  //cout << "numberOfHit=" << numberOfHit << "\n";
  //cout << "_readHitsArray_size" << _readHitsArray.GetSizeOfSet() << "\n";


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
        Read_Hit ReadHitToWrite(_qName,_position, _qReadText, _qQualText,_qReadMapText,_qQualMapText);

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
    //cout <<"position-" << position << " coorTest-" << coorTest << "\n";
    if(_samFile.IsReadHitsListLoaded())
    {
        readHits = *(_samFile.GetSetOfReadHitsAtPos((int)(position/(1000))));

    }
    else
    {
        readHits = _samFile.GetSetOfReadHits();
    }

    //cout << "readHits position -" << position << " length-" <<readHits.GetSizeOfSet() << "\n";
    //SetOfRead_Hit readHits = _samFile.GetSetOfReadHits();

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

   // ProcessingCountMaxOutput5(percentAcount,percentTcount,percentGcount,percentCcount,percentInscount);


 //cout << "percentAcount=" << percentAcount << "\n";
 //cout << "percentTcount=" << percentTcount << "\n";
 //cout << "percentGcount=" << percentGcount << "\n";
 //cout << "percentCcount=" << percentCcount << "\n"; 

   // cout << "_limCountToConsiderDiploid " << _limCountToConsiderDiploid << "\n";
    if(percentAcount > _limCountToConsiderDiploid)
    {
       // cout << "percentAcount " << percentAcount << "\n";
        correctLetter = correctLetter | OnlyA;

    }

    if(percentTcount > _limCountToConsiderDiploid)
    {
        //cout << "percentTcount " << percentTcount << "\n";
        correctLetter = correctLetter | OnlyT;
    }

    if(percentGcount > _limCountToConsiderDiploid)
    {
        //cout << "percentGcount " << percentGcount << "\n";
        correctLetter = correctLetter | OnlyG;
    }

    if(percentCcount > _limCountToConsiderDiploid)
    {
        //cout << "percentCcount " << percentCcount << "\n";
        correctLetter = correctLetter | OnlyC;

    }

    if(percentInscount > _limCountToConsiderDiploid)
    {
        //cout << "percentInscount " << percentInscount << "\n";
        correctLetter = correctLetter | OnlyIns;

    }





    return correctLetter;

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
    cout << "We are here 1\n";
    int sizeOfRef = this->_refSeq.GetSequenceText().length();
    short lettersInThisPos = 0;

    fstream allConflictPointsFile(allConflictPoints.c_str(),fstream::out);

    //Graph *currGraph = new Graph();


    int i_last = -1;

    double avCovLim = 0.0;

//    for(int i =1;i <= sizeOfRef;i++)
//    {
//        int currCov = CountCoverageAtThisPos(i);

//        avCovLim += currCov;
//    }
    cout << "We are here 2\n";
    avCovLim = avCovLim/sizeOfRef;
    avCovLim = avCovLim*_fractionOfAvCov;
    cout << avCovLim <<"\n";
    
    cout << "sizeOfRef="<< sizeOfRef<<"\n";

    SetOfRef<Vertex> lastVertexies;

   //sizeOfRef = 100;


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
	
        cout << i << " " << currCov;
	


        if(lettersInThisPos & OnlyA)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('A',i);


            cout << " A";
            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            allConflictPointsFile << " A " << sizeOfList << " ";


        }

        if(lettersInThisPos & OnlyT)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('T',i);


            cout << " T";
            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            allConflictPointsFile << " T " << sizeOfList << " ";


        }

        if(lettersInThisPos & OnlyC)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('C',i);


            cout << " C";
            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            allConflictPointsFile << " C " << sizeOfList << " ";


        }

        if(lettersInThisPos & OnlyG)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('G',i);


            cout << " G";
            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            allConflictPointsFile << " G " << sizeOfList << " ";


        }

        if(lettersInThisPos & OnlyIns)
        {
            UniqueReadList tempReadList = GetListOfReadsWithThisLetterAtThisPos('-',i);


            cout << " -";
            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            allConflictPointsFile << " - " << sizeOfList << " ";


        }
        cout << "\n";
        allConflictPointsFile << "\n";





    }







    cout << "output files\n";

    


    allConflictPointsFile.close();




    return AllOk;
}

#include "rangeslist.h"

int SAM_mapping::FindGaploidsAlgorithm(std::string allConflictPoints, std::string fileGraph,std::string fileSimpleGraph, std::string resultFileName, std::string fileDebugFileName, std::string scaffFileName,std::string scaffDebugFileName, int maxInsertSize)
{
    cout << "We are here 1\n";
    int sizeOfRef = this->_refSeq.GetSequenceText().length();
    cout << sizeOfRef <<"\n";
    sizeOfRef = 10000;

    short lettersInThisPos = 0;

    //fstream allConflictPointsFile(allConflictPoints.c_str(),fstream::out);
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
    cout << "We are here 2\n";
    avCovLim = avCovLim/sizeOfRef;
    avCovLim = avCovLim*_fractionOfAvCov;
    cout << avCovLim <<"\n";

    cout << "sizeOfRef="<< sizeOfRef<<"\n";

    SetOfRef<Vertex> lastVertexies;

   // sizeOfRef = 0;
    for(int i =1;i <= sizeOfRef;i++)
    {
//        if(i > 1000)
//        {
//            break;
//        }
        // cout << i << "startCoverage\n";
        int currCov = CountCoverageAtThisPos(i);
       // cout << i << "endCoverage\n";
        if((currCov < avCovLim) || (currCov < 10)) continue;
        lettersInThisPos = 0;

        lettersInThisPos = FindWhatLetterIsCorrectAtThisPos(i);

        if((lettersInThisPos == OnlyA) || (lettersInThisPos == OnlyC) || (lettersInThisPos == OnlyG)
                || (lettersInThisPos == OnlyT) || (lettersInThisPos == OnlyIns) || (lettersInThisPos == 0))
        {

            continue;
        }

       // allConflictPointsFile << i << " ";

       // cout << i << " " << currCov;

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

            //cout << " A";
            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            //allConflictPointsFile << " A " << sizeOfList << " ";
            //cout << "currVertexies-" << currVertex->GetName() << "\n";
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

            //cout << " T";
            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            //allConflictPointsFile << " T " << sizeOfList << " ";
            //cout << "currVertexies-" << currVertex->GetName() << "\n";
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

            //cout << " C";
            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            //allConflictPointsFile << " C " << sizeOfList << " ";
            //cout << "currVertexies-" << currVertex->GetName() << "\n";
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

            //cout << " G";
            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
            //allConflictPointsFile << " G " << sizeOfList << " ";
            //cout << "currVertexies-" << currVertex->GetName() << "\n";
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

            //cout << " -";
            int sizeOfList = tempReadList.GetReadList().GetSizeOfSet();
           // allConflictPointsFile << " - " << sizeOfList << " ";
            //cout << "currVertexies-" << currVertex->GetName() << "\n";
            delete[] tempBuf;
        }
       // cout << "\n";
       // allConflictPointsFile << "\n";

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

                //cout << "j m "<<j<<" " << m<< "weight-" << weight << "\n";
                    		lastVertexies.GetItemByNum(j)->ConnectToVertex(currVertexies.GetItemByNum(m),weight);
                    		currVertexies.GetItemByNum(m)->ConnectFromVertex(lastVertexies.GetItemByNum(j),weight);
			}

                }
            }



        }

        for(int j=0;j<currVertexies.GetSizeOfSet();j++)
        {
            //cout << "Add Vertex Start\n";
            currGraph->AddVertex(currVertexies.GetItemByNum(j));
            //cout << "Add Vertex End\n";
        }
      //  cout << "vertex[0]-" <<currGraph->GetVertexByIndex(0) << "\n";
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





        // allConflictPointsFile.flush();

        lastVertexies = currVertexies;



    }

    cout << "before graph construction\n";
    SimplifyGraph *simplGraph = new SimplifyGraph();

    currGraph->FillFirstVertexies();
    currGraph->PrintGraph(fileStreamGraph);
    cout << "after printing source graph\n";
    cout << "count first vertexies - " << currGraph->GetFirstVertexiesSize()<< "\n";
    simplGraph->EaseGraph(currGraph);
    simplGraph->FindFirstVertex();
simplGraph->PrintGraph(fileStreamSimpleGraph);

SetOfRef<Path> *resultPathes = new SetOfRef<Path>();
SetOfRef<Path> *pathesToFree = new SetOfRef<Path>();

simplGraph->GetAndPrintPath_Debug(fileStreamDebug,4,resultPathes,pathesToFree);



PrintFastaWithResultContigsByPathes(resultFileName,resultPathes,fileStreamDebug);

RangesList rl;

for(int z = 0; z < resultPathes->GetSizeOfSet();z++)
{
    for(int y = z+1;y < resultPathes->GetSizeOfSet();y++)
    {
        Path *pathA = resultPathes->GetItemByNum(z);
        Path *pathB = resultPathes->GetItemByNum(y);

        rl.CountRanges(pathA,pathB);
    }

}

fstream fileRanges("rangesList.txt",fstream::out);
rl.PrintRanges(fileRanges);
rl.Clear();
fileRanges.close();



//Scaffolder scaff;

//cout << "scaffolder created\n";

//scaff.Scaffolding(resultPathes,maxInsertSize);

//cout << "scaffolding complete\n";
//PrintScaffoldsToFasta(scaffFileName,&scaff,fileStreamDebug);

//scaff.Clear();

cout << "Clear complete\n"<<"\n";













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
//    debugFile << "resPathes->GetSizeOfSet() = "<< resPathes->GetSizeOfSet()<<"\n";
//    Path *tPath =  resPathes->GetItemByNum(1);
//    debugFile << "tPath = "<< tPath<<"\n";
//    return;
    for(int i=0;i<resPathes->GetSizeOfSet();i++)
    {
        Path *currPath = resPathes->GetItemByNum(i);

//        break;
        if(currPath->GetSizeOfSimplifyVertexSet() < 2)
        {

            if(currPath->GetSimplifyVertexByNum(0)->GetVertexSetSize() == 1)
            continue;
        }



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
                        if(currVertex->GetSymbol().c_str()[0] != '-')
                        seqText = seqText +currVertex->GetSymbol();
                    }


                    seqText = seqText + GetConsensusString(startPos,endPos);

                    if(currSVertex->GetVertexByIndex(k+1)->GetSymbol().c_str()[0] != '-')
                    seqText = seqText + currSVertex->GetVertexByIndex(k+1)->GetSymbol();




                }
            }
            else
            {
                if(currSVertex->GetVertexByIndex(0)->GetSymbol().c_str()[0] != '-')
                seqText = seqText + currSVertex->GetVertexByIndex(0)->GetSymbol();
            }

            if(nextSVertex != NULL)
            {
                int startSVertex = currSVertex->GetVertexByIndex(currSVertex->GetVertexSetSize()-1)->GetCoor()+1;

                int endSVertex = nextSVertex->GetVertexByIndex(0)->GetCoor()-1;


                seqText = seqText + GetConsensusString(startSVertex,endSVertex);

            }

  //          debugFile << seqText << "\n";


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

	//cout << i << " \n";

        if(i_last > 0)
        {
            int diff = i - i_last;

            if(diff > 100)
            {
                ConnectionComponent conCompTemp(diploidCurr);
                setConComp->AddToSet(conCompTemp);
                int sizeOfSetConComp = setConComp->GetSizeOfSet();
                int aaa = 0;
		  //cout << "diff > 100 \n";
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

            //i_last = i;
        }

        i_last = i;

        cout << "above100 - " << countAbove100 << "\n";
        cout << "below100 - " << countBelow100 << "\n";


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
//    debugFile << "resPathes->GetSizeOfSet() = "<< resPathes->GetSizeOfSet()<<"\n";
//    Path *tPath =  resPathes->GetItemByNum(1);
//    debugFile << "tPath = "<< tPath<<"\n";
//    return;

    //cout << resScaffolds->GetSizeOfConsScaffoldSet() << "\n";

    for(int z=0;z<resScaffolds->GetSizeOfConsScaffoldSet();z++)
    {

        ConsiderScaffold *resPathes = resScaffolds->GetConsScaffoldByIndex(z);
        std::string seqText = "";
        std::string conName = "";
        char *tempChar = new char[255];
        itoa(z,tempChar,10);

        conName = conName + "Scaffold_" + tempChar + "\n";

        delete[] tempChar;
        cout<<"resPathes = " << resPathes->GetSizeOfPathesSet() << "\n";

        for(int i=0;i<resPathes->GetSizeOfPathesSet();i++)
        {

ConsiderPath *tempPath = resPathes->GetPathByNum(i);
if(tempPath == NULL)
{
    cout << "NULL \n";
}
return;
Path *currPath = resPathes->GetPathByNum(i)->GetPath();

            if(currPath == NULL)
            {
                cout << "NULL \n";
            }
        

            //        break;
            if(currPath->GetSizeOfSimplifyVertexSet() < 2)
            {

                if(currPath->GetSimplifyVertexByNum(0)->GetVertexSetSize() == 1)
                continue;
            }



            //char *tempChar = new char[255];

            //itoa(i,tempChar,10);
           // std::string conName = currPath->GetName() + "_Path_" + tempChar;


            //delete[] tempChar;





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
                            if(currVertex->GetSymbol().c_str()[0] != '-')
                            seqText = seqText +currVertex->GetSymbol();
                        }


                        seqText = seqText + GetConsensusString(startPos,endPos);

                        if(currSVertex->GetVertexByIndex(k+1)->GetSymbol().c_str()[0] != '-')
                        seqText = seqText + currSVertex->GetVertexByIndex(k+1)->GetSymbol();




                    }
                }
                else
                {
                    if(currSVertex->GetVertexByIndex(0)->GetSymbol().c_str()[0] != '-')
                    seqText = seqText + currSVertex->GetVertexByIndex(0)->GetSymbol();
                }

                if(nextSVertex != NULL)
                {
                    int startSVertex = currSVertex->GetVertexByIndex(currSVertex->GetVertexSetSize()-1)->GetCoor()+1;

                    int endSVertex = nextSVertex->GetVertexByIndex(0)->GetCoor()-1;


                    seqText = seqText + GetConsensusString(startSVertex,endSVertex);

                }

      //          debugFile << seqText << "\n";


            }


        }
        FastaSequenceRecord fastaSeqRec(conName,seqText);

        fastaFile.AddSeqRecord(fastaSeqRec);

    }

   fastaFile.SaveToFile(fasta_fn.c_str());


}



