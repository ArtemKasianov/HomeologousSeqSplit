//---------------------------------------------------------------------------

//#pragma hdrstop

#include "sam_mapping.h"
#include "FilesFormats.h"
#include <iostream>


//---------------------------------------------------------------------------

//#pragma argsused
using namespace std;

int main(int argc, char* argv[])
{
//    cout << "Begin fasta buff test\n";
//    char* fileNameToLoad = "TestFasta.fasta";
//    char* fileNameToSave = "TestFasta1.fasta";
//    FastaSequenceFileBuf fastaSeqFile(fileNameToLoad);
//    FastaSequenceFileBuf fastaSeqFile1;
	
//    for(int i = 0;i<fastaSeqFile.GetSizeOfSetOfSeq();i++)
//    {
//        cout << i << "\n";
//        FastaSequenceRecord fastaSeqRec = fastaSeqFile.GetSequenceRecordByIndex(i);
//        fastaSeqRec.PrintOnTerminal();
//        fastaSeqFile1.AddSeqRecord(fastaSeqRec);
//    }
	
//    fastaSeqFile1.SaveToFile(fileNameToSave);
//    cout << "End fasta buff test\n";

//    cout << "Begin fastq buff test\n";
//    char* fileNameToLoad_1 = "TestFastq.fastq";
//    char* fileNameToSave_1 = "TestFastq1.fastq";
//    FastqSequenceFileBuf fastqSeqFile(fileNameToLoad_1);
//    FastqSequenceFileBuf fastqSeqFile1;

//    for(int i = 0;i<fastqSeqFile.GetSizeOfSetOfSeq();i++)
//    {
//        cout << i << "\n";
//        FastqSequenceRecord fastqSeqRec = fastqSeqFile.GetSequenceRecordByIndex(i);
//        fastqSeqRec.PrintOnTerminal();
//        fastqSeqFile1.AddSeqRecord(fastqSeqRec);
//    }

//    fastqSeqFile1.SaveToFile(fileNameToSave_1);
//    cout << "End fastq buff test\n";


//    cout << "Begin fasta notbuff test\n";
//    char* fileNameToSave_2 = "TestFasta2.fasta";
//    char* fileNameToSave_3 = "TestFasta2.fastq";

//    cout << "1_1" << "\n";
//    FastaSequenceFileUnBuf fastaSeqFileUnBuf(fileNameToLoad);
//    cout << "1_2" << "\n";
//    FastaSequenceFileBuf fastaSeqFileOut;
//    cout << "1_3" << "\n";
//    FastaSequenceRecord fastaSeqRecOut = fastaSeqFileUnBuf.GetSeqRecordByReadName("Test_3");
//	cout << 1 << "\n";
//	if(fastaSeqRecOut != FastaSequenceRecord::Empty())
//	{
//		fastaSeqFileOut.AddSeqRecord(fastaSeqRecOut);
//	}
//    fastaSeqFileUnBuf.SetOnStart();
//    fastaSeqFileUnBuf.GetNextSeqRead();
//    cout << 2 << "11111 "<< fastaSeqFileUnBuf.IsEndOfFile()<<"\n";
//    while(!fastaSeqFileUnBuf.IsEndOfFile())
//    {
//        cout << "yahoo "<< 3 << "\n";
//		FastaSequenceRecord fastaSeqRecOut_1 = fastaSeqFileUnBuf.GetCurrSeqRecord();
//        cout << "SeqRecord "<< fastaSeqRecOut_1.GetSequenceName() << " " << fastaSeqRecOut_1.GetSequenceText() << "\n";
//        cout << "SizeOfSeqFile "<< fastaSeqFileOut.GetSizeOfSetOfSeq()  << "\n";
//		fastaSeqFileOut.AddSeqRecord(fastaSeqRecOut_1);
//		cout << "SizeOfSeqFile "<<"Adding\n";
//        cout << fastaSeqFileOut.GetSizeOfSetOfSeq()  << "\n";
//        fastaSeqFileUnBuf.GetNextSeqRead();
//        cout << "SizeOfSeqFile "<<"Next\n";
//	}
//	FastaSequenceRecord fastaSeqRecOut_1 = fastaSeqFileUnBuf.GetCurrSeqRecord();
//	fastaSeqFileOut.AddSeqRecord(fastaSeqRecOut_1);
	
//    cout << 4 << "\n";
//    fastaSeqFileOut.SaveToFile(fileNameToSave_2);
//    cout << 5 << "\n";
//    fastaSeqFileUnBuf.CloseSeqFile();

//    cout << "End fasta notbuff test\n";


//    cout << "Begin fastq notbuff test\n";
//    FastqSequenceFileUnBuf fastqSeqFileUnBuf(fileNameToLoad_1);
//    cout << 1 << "\n";
//    FastqSequenceFileBuf fastqSeqFileOut;
//    cout << 2 << "\n";
//    FastqSequenceRecord fastqSeqRecOut = fastqSeqFileUnBuf.GetSeqRecordByReadName("Test_2");
//	cout << 3 << "\n";
//	if(fastqSeqRecOut != FastqSequenceRecord::Empty())
//	{
//		fastqSeqFileOut.AddSeqRecord(fastqSeqRecOut);
//	}
//	cout << 4 << "\n";
//    fastqSeqFileUnBuf.SetOnStart();
//    cout << 5 << "\n";
//    fastqSeqFileUnBuf.GetNextSeqRead();
//    cout << 6 << "\n";
//    while(!fastqSeqFileUnBuf.IsEndOfFile())
//    {
//        cout << 7 << "\n";
//        fastqSeqRecOut = fastqSeqFileUnBuf.GetCurrSeqRecord();
//        cout << 8 << "\n";
//        fastqSeqFileOut.AddSeqRecord(fastqSeqRecOut);
//        cout << 9 << "\n";
//        fastqSeqFileUnBuf.GetNextSeqRead();
//        cout << 10 << "\n";
//    }
//    cout << 11 << "\n";
//    fastqSeqFileOut.SaveToFile(fileNameToSave_3);
//    cout << 12 << "\n";
//    fastqSeqFileUnBuf.CloseSeqFile();
//    cout << "Begin fastq notbuff test\n";

//    SAM_file objSamFile("illumina_vs_AT1G07140.1.bowtiePart");
//    objSamFile.ReadNextLine();
//    while(!objSamFile.IsFileEnded())
//    {
//        objSamFile.PrintToTerminal();
//        objSamFile.ReadNextLine();

//    }

/*
    FastqSequenceFileUnBuf fastq_0("TestFastq_0.fastq");
    FastqSequenceFileUnBuf fastq_1("TestFastq_1.fastq");
    FastqSequenceFileUnBuf fastq_2("TestFastq_2.fastq");
    FastqSequenceFileUnBuf fastq_3("TestFastq_3.fastq");


    UniqueReadList readList_0;
    fastq_0.GetNextSeqRead();
    while(!fastq_0.IsEndOfFile())
    {
        readList_0.Add(fastq_0.GetCurrSeqRecord());
        fastq_0.GetNextSeqRead();
    }

    UniqueReadList readList_1;
    fastq_1.GetNextSeqRead();
    while(!fastq_1.IsEndOfFile())
    {
        readList_1.Add(fastq_1.GetCurrSeqRecord());
        fastq_1.GetNextSeqRead();
    }

    UniqueReadList readList_2;
    fastq_2.GetNextSeqRead();
    while(!fastq_2.IsEndOfFile())
    {
        readList_2.Add(fastq_2.GetCurrSeqRecord());
        fastq_2.GetNextSeqRead();
    }

    UniqueReadList readList_3;
    fastq_3.GetNextSeqRead();
    while(!fastq_3.IsEndOfFile())
    {
        readList_3.Add(fastq_3.GetCurrSeqRecord());
        fastq_3.GetNextSeqRead();
    }


    Diploid diploid_0(readList_0,readList_2);
    Diploid diploid_1(readList_1,readList_3);

    cout << "diploid_0\n";
    diploid_0.GetFirstGaploid().PrintToStdIn();
    diploid_0.GetSecondGaploid().PrintToStdIn();
    cout << "diploid_1\n";
    diploid_1.GetFirstGaploid().PrintToStdIn();
    diploid_1.GetSecondGaploid().PrintToStdIn();


    ConnectionComponent conComp;

    conComp.AddDiploid(diploid_0);
    conComp.PrintToStdIn();
    conComp.AddDiploid(diploid_1);
    conComp.PrintToStdIn();

    conComp.PrintToFastqFiles("testFirst");




    fastq_0.CloseSeqFile();
    fastq_1.CloseSeqFile();
    fastq_2.CloseSeqFile();
    fastq_3.CloseSeqFile();






    Diploid diploid_2(readList_0,readList_2);
    Diploid diploid_3(readList_3,readList_1);

    cout << "diploid_2\n";
    diploid_2.GetFirstGaploid().PrintToStdIn();
    diploid_2.GetSecondGaploid().PrintToStdIn();
    cout << "diploid_3\n";
    diploid_3.GetFirstGaploid().PrintToStdIn();
    diploid_3.GetSecondGaploid().PrintToStdIn();


    ConnectionComponent conComp_1;

    conComp_1.AddDiploid(diploid_2);
    conComp_1.PrintToStdIn();
    conComp_1.AddDiploid(diploid_3);
    conComp_1.PrintToStdIn();

    conComp_1.PrintToFastqFiles("testSecond");



    Diploid diploid_4(readList_0,readList_1);
    Diploid diploid_5(readList_2,readList_3);

    cout << "diploid_4\n";
    diploid_4.GetFirstGaploid().PrintToStdIn();
    diploid_4.GetSecondGaploid().PrintToStdIn();
    cout << "diploid_5\n";
    diploid_5.GetFirstGaploid().PrintToStdIn();
    diploid_5.GetSecondGaploid().PrintToStdIn();


    ConnectionComponent conComp_2;

    conComp_2.AddDiploid(diploid_4);
    conComp_2.PrintToStdIn();
    conComp_2.AddDiploid(diploid_5);
    conComp_2.PrintToStdIn();

    conComp_2.PrintToFastqFiles("testThird");
*/

    SAM_mapping samMap("illumina_vs_AT1G07140.1.bowtiePart","TAIR10_sec.fasta","AT1G07140.1",0.1,0.8);

    //samMap.PrintMappingToFile("testMapping");
    samMap.FindGaploidsAlgorithm_faster("illumina_vs_AT1G07140_1");





    return 0;
}
//---------------------------------------------------------------------------
