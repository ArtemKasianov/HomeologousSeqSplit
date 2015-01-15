#include "mismatchpointsfile.h"


int MismatchPointsFile::LoadFile(std::string fileName)
{
    FILE *currFile = fopen(fileName.c_str(),"r");
    if(currFile == NULL)
    {
        return 0;
    }



    unsigned position = -1;
    int isNotDeletion = -1;
    char* varTxt = new char[200];


    while(!feof(currFile))
    {


        fscanf(currFile,"%u %u %s",&position,&isNotDeletion,varTxt);

        if(feof(currFile))
        {
           break;
        }

        MismatchVariant objMismatchVar;

        _positions.AddPosition(position);
        objMismatchVar.position = position;
        objMismatchVar.isDeletion = (isNotDeletion)?false:true;
        objMismatchVar.varText = varTxt;

        _mismatchVars.AddToSet(objMismatchVar);

        char tempChar = fgetc(currFile);

        while(!feof(currFile))
        {
            if(tempChar == '\n')
            {
                break;
            }

            tempChar = fgetc(currFile);
        }


    }


    fclose(currFile);
    delete[] varTxt;
}

void MismatchPointsFile::GetVarsByPosition(unsigned position,SetOfRef<MismatchVariant> &notInsertVars, SetOfRef<MismatchVariant> &insertVars)
{
    for(int i = 0;i < _mismatchVars.GetSizeOfSet();i++)
    {
        MismatchVariant *currMismatchVar = _mismatchVars.GetRefItemByNum(i);
        if(currMismatchVar->position == position)
        {
            if(currMismatchVar->isDeletion)
            {
                insertVars.AddToSet(currMismatchVar);
            }
            else
            {
                notInsertVars.AddToSet(currMismatchVar);
            }
        }
    }
}
