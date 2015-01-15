#include "sam_mapping.h"
#include "FilesFormats.h"
#include "snptextfile.h"
#include <string>


using namespace std;

int main(int argc, char* argv[])
{




    if(argc != 9)
    {
        cout << "error in command line " << argc <<"\n";
        return 0;
    }

    std::string samFileName = argv[1];
    std::string refFileName = argv[2];
    std::string refContigName = argv[3];
    double limVal = atof(argv[4]);
    float fraction = atof(argv[5]);

    unsigned minCov = atoi(argv[6]);
    unsigned maxCov = atoi(argv[7]);
    std::string splitFileName = argv[8];





    SAM_mapping samMap(samFileName,refFileName,refContigName,limVal,fraction);


    samMap.SplitRefSeqByCoverage(minCov,maxCov,refContigName,splitFileName);






    return 0;
}
