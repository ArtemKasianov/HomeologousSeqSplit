#include "sam_mapping.h"
#include "FilesFormats.h"
#include "snptextfile.h"
#include <string>


using namespace std;

int main(int argc, char* argv[])
{




    if(argc != 16)
    {
        cout << "error in command line " << argc <<"\n";
        return 0;
    }

    std::string samFileName = argv[1];
    std::string refFileName = argv[2];
    std::string refContigName = argv[3];
    double limVal = atof(argv[4]);
    float fraction = atof(argv[5]);

    std::string fileGraph = argv[6];
    std::string fileSimpleGraph = argv[7];
    std::string resultFileName = argv[8];
    std::string fileDebugFileName = argv[9];
    std::string scaffFileName = argv[10];
    std::string scaffDebugFileName = argv[11];
    int maxInsertSize = atoi(argv[12]);
    double minWeightRatio = atof(argv[13]);
    std::string mismatchPtsFileName = argv[14];
    unsigned maxPosition = atoi(argv[15]);



    SAM_mapping samMap(samFileName,refFileName,refContigName,limVal,fraction);


    samMap.FindGaploidsFromMismatchPtsAlgorithm(fileGraph,fileSimpleGraph,resultFileName,fileDebugFileName,scaffFileName,scaffDebugFileName,maxInsertSize,minWeightRatio,mismatchPtsFileName,maxPosition);




    return 0;
}


