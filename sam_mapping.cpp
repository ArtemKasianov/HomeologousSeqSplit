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
  int countHits = 0;
  while(!_isFileEnd)
  {


	Read_Hit ReadHitToWrite(_qName,_position, _qReadText, _qQualText,_qReadMapText,_qQualMapText);

    FastqSequenceRecord readToAdd(_qName,_qReadText,_qQualText);

    _readHitsArray.AddToSet(ReadHitToWrite);

    _allReads.Add(readToAdd);
    countHits++;
    ReadNextLine();
	numberOfHit++;

  }

  cout << countHits << "\n";



  _isReadHitsLoaded= 1;
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


    SetOfRead_Hit readHits = _samFile.GetSetOfReadHits();

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


    SetOfRead_Hit readHits = _samFile.GetSetOfReadHits();

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

    ProcessingCountMaxOutput5(percentAcount,percentTcount,percentGcount,percentCcount,percentInscount);


 //cout << "percentAcount=" << percentAcount << "\n";
 //cout << "percentTcount=" << percentTcount << "\n";
 //cout << "percentGcount=" << percentGcount << "\n";
 //cout << "percentCcount=" << percentCcount << "\n"; 

    cout << "_limCountToConsiderDiploid " << _limCountToConsiderDiploid << "\n";
    if(percentAcount > _limCountToConsiderDiploid)
    {
        cout << "percentAcount " << percentAcount << "\n";
        correctLetter = correctLetter | OnlyA;

    }

    if(percentTcount > _limCountToConsiderDiploid)
    {
        cout << "percentTcount " << percentTcount << "\n";
        correctLetter = correctLetter | OnlyT;
    }

    if(percentGcount > _limCountToConsiderDiploid)
    {
        cout << "percentGcount " << percentGcount << "\n";
        correctLetter = correctLetter | OnlyG;
    }

    if(percentCcount > _limCountToConsiderDiploid)
    {
        cout << "percentCcount " << percentCcount << "\n";
        correctLetter = correctLetter | OnlyC;

    }

    if(percentInscount > _limCountToConsiderDiploid)
    {
        cout << "percentInscount " << percentInscount << "\n";
        correctLetter = correctLetter | OnlyIns;

    }



    return correctLetter;

}


UniqueReadList SAM_mapping::GetListOfReadsWithThisLetterAtThisPos(char letter, int pos)
{


    //int numberOfReadsFound = 0;
    UniqueReadList readsList;
    SetOfRead_Hit readHitsList = _samFile.GetSetOfReadHits();
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


int SAM_mapping::FindGaploidsAlgorithm(std::string baseFileNameOutput, std::string outFileNameBaseForRefSubstr, std::string allConflictPoints, std::string notResolvedIll, std::string notResolvedPE)
{
    int sizeOfRef = this->_refSeq.GetSequenceText().length();
    short lettersInThisPos = 0;

    fstream allConflictPointsFile(allConflictPoints.c_str(),fstream::out);
    fstream notResolvedIllFile(notResolvedIll.c_str(),fstream::out);
    fstream notResolvedPEFile(notResolvedPE.c_str(),fstream::out);


    SetOfConComp *setConComp = new SetOfConComp();
    ConnectionComponent conComp;

    setConComp->AddToSet(conComp);

    int i_last = -1;

    double avCovLim = 0.0;

    for(int i =1;i <= sizeOfRef;i++)
    {
        int currCov = CountCoverageAtThisPos(i);

        avCovLim += currCov;
    }
    
    avCovLim = avCovLim/sizeOfRef;
    avCovLim = avCovLim*_fractionOfAvCov;
    cout << avCovLim <<"\n";
    

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

        allConflictPointsFile << i << " ";
	
    cout << i << " " << currCov;
	
	if(lettersInThisPos & OnlyA)
	{
	    cout << " A";
        int sizeOfList = GetListOfReadsWithThisLetterAtThisPos('A',i).GetReadList().GetSizeOfSet();
        allConflictPointsFile << " A " << sizeOfList << " ";
	}
	
	if(lettersInThisPos & OnlyT)
	{
	    cout << " T";

        int sizeOfList = GetListOfReadsWithThisLetterAtThisPos('T',i).GetReadList().GetSizeOfSet();
        allConflictPointsFile << " T " << sizeOfList << " ";
	}
	
	if(lettersInThisPos & OnlyC)
	{
	    cout << " C";
        int sizeOfList = GetListOfReadsWithThisLetterAtThisPos('C',i).GetReadList().GetSizeOfSet();
        allConflictPointsFile << " C " << sizeOfList << " ";
	}
	
	if(lettersInThisPos & OnlyG)
	{
	    cout << " G";
        int sizeOfList = GetListOfReadsWithThisLetterAtThisPos('G',i).GetReadList().GetSizeOfSet();
        allConflictPointsFile << " G " << sizeOfList << " ";
	}

    if(lettersInThisPos & OnlyIns)
    {
        cout << " -";
        int sizeOfList = GetListOfReadsWithThisLetterAtThisPos('-',i).GetReadList().GetSizeOfSet();
        allConflictPointsFile << " - " << sizeOfList << " ";
    }
	cout << "\n";
    allConflictPointsFile << "\n";
        Diploid diploidCurr;
        int currGaploid = 0;
        int diploidFirstGaploid =diploidCurr.GetFirstGaploid()->GetReadList().GetSizeOfSet();
        int diploidSecondGaploid =diploidCurr.GetSecondGaploid()->GetReadList().GetSizeOfSet();

        if(lettersInThisPos & OnlyA)
        {
            diploidCurr.GetFirstGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('A',i).GetReadList());
            diploidCurr.AddConflictPointToFirstGaploid(ConflictPoint('A',i));
            currGaploid++;
        }
        diploidFirstGaploid =diploidCurr.GetFirstGaploid()->GetReadList().GetSizeOfSet();
        diploidSecondGaploid =diploidCurr.GetSecondGaploid()->GetReadList().GetSizeOfSet();

        if(lettersInThisPos & OnlyC)
        {
            if(currGaploid == 0)
            {
                diploidCurr.GetFirstGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('C',i).GetReadList());
                diploidCurr.AddConflictPointToFirstGaploid(ConflictPoint('C',i));
            }
            else
            {
                diploidCurr.GetSecondGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('C',i).GetReadList());
                diploidCurr.AddConflictPointToSecondGaploid(ConflictPoint('C',i));
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
                diploidCurr.AddConflictPointToFirstGaploid(ConflictPoint('G',i));
            }
            else
            {
                diploidCurr.GetSecondGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('G',i).GetReadList());
                 diploidCurr.AddConflictPointToSecondGaploid(ConflictPoint('G',i));
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
                diploidCurr.AddConflictPointToFirstGaploid(ConflictPoint('T',i));
            }
            else
            {
                diploidCurr.GetSecondGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('T',i).GetReadList());
                 diploidCurr.AddConflictPointToSecondGaploid(ConflictPoint('T',i));
            }
            currGaploid++;
        }
        diploidFirstGaploid =diploidCurr.GetFirstGaploid()->GetReadList().GetSizeOfSet();
        diploidSecondGaploid =diploidCurr.GetSecondGaploid()->GetReadList().GetSizeOfSet();

        if((lettersInThisPos & OnlyIns) && (currGaploid <= 1))
        {
            if(currGaploid == 0)
            {
                diploidCurr.GetFirstGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('-',i).GetReadList());
                diploidCurr.AddConflictPointToFirstGaploid(ConflictPoint('-',i));
            }
            else
            {
                diploidCurr.GetSecondGaploid()->AddSetOfReadList(GetListOfReadsWithThisLetterAtThisPos('-',i).GetReadList());
                 diploidCurr.AddConflictPointToSecondGaploid(ConflictPoint('-',i));
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
                notResolvedIllFile << i << "\n";
                allConflictPointsFile << "i " << i << " too long distance\n";

            }
            else
            {
                int connected = 0;
                ConnectionComponent *conComp_curr = setConComp->GetRefItemByNum(setConComp->GetSizeOfSet()-1);
                if(conComp_curr != NULL)
                {
                    allConflictPointsFile << "i " << i << " ";
                    connected = conComp_curr->AddDiploid(diploidCurr,allConflictPointsFile);
                    allConflictPointsFile << "\n";
                }
                else
                {
                    connected = AllOk;
                }

                if(connected == ErrorHappens)
                {
                    ConnectionComponent conCompTemp(diploidCurr);
                    setConComp->AddToSet(conCompTemp);
                    notResolvedIllFile << i << "\n";
                }
                int sizeOfSetConComp = setConComp->GetSizeOfSet();
                int firstGaploidSize = setConComp->GetRefItemByNum(sizeOfSetConComp-1)->GetFirstGaploid()->GetReadList().GetSizeOfSet();
                int secondGaploidSize = setConComp->GetRefItemByNum(sizeOfSetConComp-1)->GetSecondGaploid()->GetReadList().GetSizeOfSet();
                int aaa = 0;
            }

            //i_last = i;
        }
        else
        {
            int connected = 0;
            ConnectionComponent *conComp_curr = setConComp->GetRefItemByNum(setConComp->GetSizeOfSet()-1);
            allConflictPointsFile << "i " << i << " ";
            connected = conComp_curr->AddDiploid(diploidCurr,allConflictPointsFile);
            allConflictPointsFile << "\n";
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





    for(int i = 0; i<(setConComp->GetSizeOfSet()-1);i++)
    {
        if((setConComp->GetItemByNum(i).GetFirstGaploid()->GetReadList().GetSizeOfSet() == 0) || ((setConComp->GetItemByNum(i).GetSecondGaploid()->GetReadList().GetSizeOfSet() == 0)))
        {


            SetOfConComp *setConComp_temp = new SetOfConComp();

            for(int j = 0;j<(setConComp->GetSizeOfSet());j++)
            {
                if(i != j)
                {
                    setConComp_temp->AddToSet(setConComp->GetItemByNum(j));

                }
            }

            delete setConComp;
            setConComp = setConComp_temp;
            i = 0;

        }
    }

    bool isSizeChanged = true;
    while((setConComp->GetSizeOfSet() > 1) && (isSizeChanged))
    {

        isSizeChanged = false;
        for(int i = 0; i<(setConComp->GetSizeOfSet()-1);i++)
        {
            int sizeOfSetCurr = setConComp->GetSizeOfSet()-1;
            notResolvedPEFile << i << " " <<sizeOfSetCurr <<"\n";
            ConnectionComponent *conComp_curr = setConComp->GetRefItemByNum(i);
            if(conComp_curr == NULL)
            {
                continue;
            }
            if((setConComp->GetRefItemByNum(i)->FindIntersectionByPEAndSetCorrectOrder(&(setConComp->GetItemByNum(i+1)))) == AllOk)
            {

                setConComp->GetRefItemByNum(i)->GetFirstGaploid()->AddSetOfReadList(setConComp->GetItemByNum(i+1).GetFirstGaploid()->GetReadList());
                setConComp->GetRefItemByNum(i)->GetSecondGaploid()->AddSetOfReadList(setConComp->GetItemByNum(i+1).GetSecondGaploid()->GetReadList());
                setConComp->GetRefItemByNum(i)->AddSetOfConflictPointToFirstGaploid(setConComp->GetItemByNum(i+1).GetSetOfConflictPointsFirstGaploid());
                setConComp->GetRefItemByNum(i)->AddSetOfConflictPointToSecondGaploid(setConComp->GetItemByNum(i+1).GetSetOfConflictPointsSecondGaploid());
                SetOfConComp *setConComp_temp = new SetOfConComp();

                for(int j = 0;j<(setConComp->GetSizeOfSet());j++)
                {
                    if(i != j)
                    {
                        setConComp_temp->AddToSet(setConComp->GetItemByNum(j));

                    }
                }

                isSizeChanged = true;
                delete setConComp;
                setConComp = setConComp_temp;
                i = 0;
            }

        }

    }


    cout << "output files\n";

    for(int i = 0; i<setConComp->GetSizeOfSet();i++)
    {
        char *toStoreInt = new char[100];
        sprintf(toStoreInt,"%d",i);
        std::string baseFNToWrite = baseFileNameOutput+"_"+toStoreInt;
        std::string outFNRef = outFileNameBaseForRefSubstr+"_"+toStoreInt;
        std::string fileNameRef_1 = outFNRef+"_1_ref"+".fasta";
        std::string fileNameRef_2 = outFNRef+"_2_ref"+".fasta";
        setConComp->GetItemByNum(i).PrintToFastqFiles(baseFNToWrite/*,_samFile.GetAllReadList()*/);

        SetOfConflictPoints setOfFirstGaploid_0 = setConComp->GetItemByNum(i).GetSetOfConflictPointsFirstGaploid();
        SetOfConflictPoints setOfSecondGaploid_0 = setConComp->GetItemByNum(i).GetSetOfConflictPointsSecondGaploid();

        int startPoint = 1000000000;
        int endPoint = 0 ;

        int startPoint_0 = 1000000000;
        int endPoint_0 = 0;

        int startPoint_last = 0;
        int endPoint_last = 0;

        cout << i << "\n";
        for(int j = 0; j< setOfFirstGaploid_0.GetSizeOfSet();j++)
        {
            if(startPoint_0 > setOfFirstGaploid_0.GetItemByNum(j).GetCoor())
            {
                startPoint_0 = setOfFirstGaploid_0.GetItemByNum(j).GetCoor();
            }

            if(endPoint_0 < setOfFirstGaploid_0.GetItemByNum(j).GetCoor())
            {
                endPoint_0 = setOfFirstGaploid_0.GetItemByNum(j).GetCoor();
            }
        }

        for(int j = 0; j< setOfSecondGaploid_0.GetSizeOfSet();j++)
        {
            if(startPoint_0 > setOfSecondGaploid_0.GetItemByNum(j).GetCoor())
            {
                startPoint_0 = setOfSecondGaploid_0.GetItemByNum(j).GetCoor();
            }

            if(endPoint_0 < setOfSecondGaploid_0.GetItemByNum(j).GetCoor())
            {
                endPoint_0 = setOfSecondGaploid_0.GetItemByNum(j).GetCoor();
            }
        }





        if(i == 0)
        {
            startPoint = 0;
            startPoint_last = startPoint;

        }
        else
        {
            SetOfConflictPoints setOfFirstGaploid_L0 = setConComp->GetItemByNum(i-1).GetSetOfConflictPointsFirstGaploid();
            SetOfConflictPoints setOfSecondGaploid_L0 = setConComp->GetItemByNum(i-1).GetSetOfConflictPointsSecondGaploid();

            for(int j = 0; j< setOfFirstGaploid_L0.GetSizeOfSet();j++)
            {
                if(endPoint < setOfFirstGaploid_L0.GetItemByNum(j).GetCoor())
                {
                    endPoint = setOfFirstGaploid_L0.GetItemByNum(j).GetCoor();
                }
            }

            for(int j = 0; j< setOfSecondGaploid_L0.GetSizeOfSet();j++)
            {
                if(endPoint < setOfSecondGaploid_L0.GetItemByNum(j).GetCoor())
                {
                    endPoint = setOfSecondGaploid_L0.GetItemByNum(j).GetCoor();
                }
            }

            //startPoint_last = endPoint + (startPoint_0 - endPoint)/2;
           startPoint_last = endPoint;


        }

        if((i + 1) < setConComp->GetSizeOfSet())
        {
            SetOfConflictPoints setOfFirstGaploid_1 = setConComp->GetItemByNum(i+1).GetSetOfConflictPointsFirstGaploid();
            SetOfConflictPoints setOfSecondGaploid_1 = setConComp->GetItemByNum(i+1).GetSetOfConflictPointsSecondGaploid();

            for(int j = 0; j< setOfFirstGaploid_1.GetSizeOfSet();j++)
            {
                if(startPoint > setOfFirstGaploid_1.GetItemByNum(j).GetCoor())
                {
                    startPoint = setOfFirstGaploid_1.GetItemByNum(j).GetCoor();
                }
            }

            for(int j = 0; j< setOfSecondGaploid_1.GetSizeOfSet();j++)
            {
                if(startPoint > setOfSecondGaploid_1.GetItemByNum(j).GetCoor())
                {
                    startPoint = setOfSecondGaploid_1.GetItemByNum(j).GetCoor();
                }
            }

            //endPoint_last = endPoint_0 + (startPoint - endPoint_0)/2;
            endPoint_last = endPoint_0;

        }
        else
        {
            endPoint = _refSeq.GetSequenceText().length()+1;
            endPoint_last = endPoint;
        }

        cout << startPoint_last << " " << endPoint_last << "\n";

       std::string currString = "";
       FILE *fnRef_1 = fopen(fileNameRef_1.c_str(),"w");
       std::string fileNameOfFasta = ">"+outFNRef+"_1_ref\n";
       fputs(fileNameOfFasta.c_str(),fnRef_1);
       for(int j = 0; j< setOfFirstGaploid_0.GetSizeOfSet();j++)
       {
           cout << "first "<< j << "\n";

           cout << setOfFirstGaploid_0.GetItemByNum(j).GetCoor() <<" " <<setOfFirstGaploid_0.GetItemByNum(j).GetCharVal() << "\n";
           if(j == 0)
           {
               cout << " j = 0" << startPoint_last << " " << (setOfFirstGaploid_0.GetItemByNum(j).GetCoor() - startPoint_last -1) << "\n";
                currString = _refSeq.GetSequenceText().substr(startPoint_last,setOfFirstGaploid_0.GetItemByNum(j).GetCoor() - startPoint_last -1);
                currString = currString.append(1,setOfFirstGaploid_0.GetItemByNum(j).GetCharVal());
           }
           else
           {
               cout << " j != 0" << setOfFirstGaploid_0.GetItemByNum(j-1).GetCoor() << " " << (setOfFirstGaploid_0.GetItemByNum(j).GetCoor() - setOfFirstGaploid_0.GetItemByNum(j-1).GetCoor() -1) << "\n";
               currString = _refSeq.GetSequenceText().substr(setOfFirstGaploid_0.GetItemByNum(j-1).GetCoor(),setOfFirstGaploid_0.GetItemByNum(j).GetCoor() - setOfFirstGaploid_0.GetItemByNum(j-1).GetCoor() -1);
               currString = currString.append(1,setOfFirstGaploid_0.GetItemByNum(j).GetCharVal());
           }




           fputs(currString.c_str(),fnRef_1);





       }
        cout << " end " << setOfFirstGaploid_0.GetItemByNum(setOfFirstGaploid_0.GetSizeOfSet()-1).GetCoor() << " " << (endPoint_last - setOfFirstGaploid_0.GetItemByNum(setOfFirstGaploid_0.GetSizeOfSet()-1).GetCoor()) << "\n";

        if((endPoint_last - setOfFirstGaploid_0.GetItemByNum(setOfFirstGaploid_0.GetSizeOfSet()-1).GetCoor()) > 0)
        {
            cout << "We are here!\n";
            currString = _refSeq.GetSequenceText().substr(setOfFirstGaploid_0.GetItemByNum(setOfFirstGaploid_0.GetSizeOfSet()-1).GetCoor(),endPoint_last - setOfFirstGaploid_0.GetItemByNum(setOfFirstGaploid_0.GetSizeOfSet()-1).GetCoor());
            fputs(currString.c_str(),fnRef_1);
        }


       fputs("\n",fnRef_1);
       fclose(fnRef_1);


       currString = "";
       FILE *fnRef_2 = fopen(fileNameRef_2.c_str(),"w");

       fileNameOfFasta = ">"+outFNRef+"_2_ref\n";
       fputs(fileNameOfFasta.c_str(),fnRef_2);

       for(int j = 0; j< setOfSecondGaploid_0.GetSizeOfSet();j++)
       {

           cout <<"second " << j << "\n";

           cout << setOfSecondGaploid_0.GetItemByNum(j).GetCoor() <<" " <<setOfSecondGaploid_0.GetItemByNum(j).GetCharVal() << "\n";
           if(j == 0)
           {
                currString = _refSeq.GetSequenceText().substr(startPoint_last,setOfSecondGaploid_0.GetItemByNum(j).GetCoor() - startPoint_last-1);
                currString = currString.append(1,setOfSecondGaploid_0.GetItemByNum(j).GetCharVal());
           }
           else
           {
               currString = _refSeq.GetSequenceText().substr(setOfSecondGaploid_0.GetItemByNum(j-1).GetCoor(),setOfSecondGaploid_0.GetItemByNum(j).GetCoor() - setOfSecondGaploid_0.GetItemByNum(j-1).GetCoor()-1);
               currString = currString.append(1,setOfSecondGaploid_0.GetItemByNum(j).GetCharVal());
           }




           fputs(currString.c_str(),fnRef_2);





       }

       if((endPoint_last - setOfSecondGaploid_0.GetItemByNum(setOfSecondGaploid_0.GetSizeOfSet()-1).GetCoor()) > 0)
       {
           cout << "We are here!\n";
           currString = _refSeq.GetSequenceText().substr(setOfSecondGaploid_0.GetItemByNum(setOfSecondGaploid_0.GetSizeOfSet()-1).GetCoor(),endPoint_last - setOfSecondGaploid_0.GetItemByNum(setOfSecondGaploid_0.GetSizeOfSet()-1).GetCoor());
           fputs(currString.c_str(),fnRef_2);
       }


       fputs("\n",fnRef_2);

       fclose(fnRef_2);








        delete[] toStoreInt;
    }



    allConflictPointsFile.close();
    notResolvedIllFile.close();
    notResolvedPEFile.close();
    allConflictPointsFile.flush();
    notResolvedIllFile.flush();
    notResolvedPEFile.flush();

    delete setConComp;

    return AllOk;
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



