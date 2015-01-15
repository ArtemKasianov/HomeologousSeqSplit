#include "sam_mapping.h"
#include "FilesFormats.h"


using namespace std;

int main(int argc, char* argv[])
{

    if(argc != 15)
    {
        cout << "error in command line " << argc <<"\n";
        return 0;
    }
    std::string samFileName = argv[1];
    std::string refFileName = argv[2];
    std::string refContigName = argv[3];
    //std::string avFile = argv[4];
    //std::string covTableFile = argv[5];


    std::string baseFileName = argv[4];

    double limVal = atof(argv[5]);
    float fraction = atof(argv[6]);
    std::string outFileName = argv[7];
    std::string allReadsFileName = argv[8];

    std::string resultFileName = argv[9];
    std::string debugFileName = argv[10];

    std::string scaffFileName = argv[11];
    std::string scaffDebugFileName = argv[12];
    int maxInsertSize = atoi(argv[13]);
    std::string fileNameMismatchPt = argv[14];

    cout << "command line : "<< argv[0] << " "<< samFileName << " "<< refFileName << " "<< refContigName << " "<< baseFileName << " "<< limVal << fraction << outFileName <<" \n";

    SAM_mapping samMap(samFileName,refFileName,refContigName,limVal,fraction);


    cout << "SAM_mapping created here\n";
    //samMap.FindGaploidsAlgorithm_faster(baseFileName);
    //samMap.FindGaploidsAlgorithm(baseFileName,outFileName);


   samMap.FindGaploidsAlgorithm(allReadsFileName,baseFileName,outFileName,resultFileName,debugFileName,scaffFileName,scaffDebugFileName,maxInsertSize,fileNameMismatchPt);

  //samMap.PrintMappingToFile("test.map");

    //samMap.CountCoverage(avFile,covTableFile);

    return 0;
}

