#include "sam_mapping.h"
#include "FilesFormats.h"
#include "snptextfile.h"
#include <string>


using namespace std;

int main(int argc, char* argv[])
{




    if(argc != 15)
    {
        cout << "error in command line " << argc <<"\n";
        return 0;
    }

    std::string vartTxtFileName = argv[1];
    std::string samFileName = argv[2];
    std::string refFileName = argv[3];
    std::string refContigName = argv[4];
    double limVal = atof(argv[5]);
    float fraction = atof(argv[6]);

    std::string fileGraph = argv[7];
    std::string fileSimpleGraph = argv[8];
    std::string resultFileName = argv[9];
    std::string fileDebugFileName = argv[10];
    std::string scaffFileName = argv[11];
    std::string scaffDebugFileName = argv[12];
    int maxInsertSize = atoi(argv[13]);
    double minWeightRatio = atof(argv[14]);


    VariantTextFile varTxtFile(vartTxtFileName);
    //varTxtFile.PrintDebug();
    cout << "before filter\n";
    varTxtFile.FilterVarPtsByWeight(minWeightRatio);
    cout << "after filter\n";
    //varTxtFile.PrintDebug();

    cout << "before samMap constructor\n";
    SAM_mapping samMap(samFileName,refFileName,refContigName,limVal,fraction);
    cout << "after samMap constructor\n";

    samMap.FindGaploidsAlgorithm(fileGraph,fileSimpleGraph,resultFileName,fileDebugFileName,scaffFileName,scaffDebugFileName,maxInsertSize,minWeightRatio);


//    Graph *testGraph = new Graph();

//    testGraph->LoadFromGraphViz(graphVizFile.c_str());

//    delete testGraph;
//    std::string samFileName = argv[1];
//    std::string refFileName = argv[2];
//    std::string refContigName = argv[3];
    //std::string avFile = argv[4];
    //std::string covTableFile = argv[5];


 //   std::string baseFileName = argv[4];

//    double limVal = atof(argv[5]);
//    float fraction = atof(argv[6]);
//    std::string outFileName = argv[7];
//    std::string allReadsFileName = argv[8];

//    std::string resultFileName = argv[9];
//    std::string debugFileName = argv[10];

//    std::string scaffFileName = argv[11];
//    std::string scaffDebugFileName = argv[12];
//    int maxInsertSize = atoi(argv[13]);

   // cout << "command line : "<< argv[0] << " "<< samFileName << " "<< refFileName << " "<< refContigName << " "<< baseFileName << " "<< limVal << fraction << outFileName <<" \n";

  //  SAM_mapping samMap(samFileName,refFileName,refContigName,limVal,fraction);


  //  cout << "SAM_mapping created here\n";
    //samMap.FindGaploidsAlgorithm_faster(baseFileName);
    //samMap.FindGaploidsAlgorithm(baseFileName,outFileName);


//   samMap.FindGaploidsAlgorithm(allReadsFileName,baseFileName,outFileName,resultFileName,debugFileName,scaffFileName,scaffDebugFileName,maxInsertSize);

  //samMap.PrintMappingToFile("test.map");

    //samMap.CountCoverage(avFile,covTableFile);

    return 0;
}

