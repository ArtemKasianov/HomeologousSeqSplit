#include "snptextfile.h"

VariantTextFile::VariantTextFile(std::string variantFileName)
{
    FILE *currFile = fopen(variantFileName.c_str(),"r");


    char *refPoint = new char[200];
    int refPointVal = -1;
    char *refPointToConvert = new char[200];
    char *consPoint = new char[200];
    char *consensus = new char[200];
    char *residue = new char[200];
    char *IUPAC = new char[200];
    char *status = new char[200];
    char *notes = new char[200];
    std::string residueStr = "";
    bool isDeletion = false;

    char tempChar1 = fgetc(currFile);
    while(!feof(currFile))
    {
        if(tempChar1 == '\n')
        {
            break;
        }

        tempChar1 = fgetc(currFile);
    }



    while(!feof(currFile))
    {

        SetOfVariantValues setVarVals;
        isDeletion = false;
        fscanf(currFile,"%s\t%s\t%s\t%s",refPoint,consPoint,consensus,residue);
        if(feof(currFile))
        {
            break;
        }
        char nextChar = fgetc(currFile);
        residueStr = residue;
        while((nextChar != '\t') && (!feof(currFile)))
        {
            fscanf(currFile,"%s",residue);
            residueStr = residueStr +" "+ residue;
            nextChar = fgetc(currFile);
        }
        int currSymbolIndex = 0;


        while(refPoint[currSymbolIndex] != '\0')
        {
            if(refPoint[currSymbolIndex] == '^')
            {
                isDeletion = true;
                break;
            }
            else
            {
                refPointToConvert[currSymbolIndex] = refPoint[currSymbolIndex];
            }
            currSymbolIndex++;
        }
        refPointToConvert[currSymbolIndex] = '\0';
        refPointVal = atoi(refPointToConvert);
        int countSpaces = 0;
        int spaces_index = 0;
        for(int i = 0; i < residueStr.length();i++)
        {
            if(residueStr[i] == ' ')
            {

                countSpaces++;
                if(countSpaces == 3)
                {
                    spaces_index = i+1;
                    break;
                }
            }
        }

        char *currVarVal = new char[200];
        char *currVarValWeight = new char[200];
     //   currVarVal = "";
      //  currVarValWeight = "";

        bool isValFilling = true;
        bool isWeightFilling = false;

        int fillingIndex = 0;

        for(int i = spaces_index; i < residueStr.length();i++)
        {

            if(residueStr[i] == ' ')
            {

                if(isValFilling)
                {
                    currVarVal[fillingIndex] = '\0';
                    currVarValWeight[0] = '\0';
                }

                if(isWeightFilling)
                {

                    currVarValWeight[fillingIndex] = '\0';


                    int currVarValWeightInt = atoi(currVarValWeight);

                    VariantValue tempVarVal(currVarVal,currVarValWeightInt);
                    setVarVals.AddToSet(tempVarVal);
                    //cout << currVarVal << " " << currVarValWeightInt << " "<< currVarValWeight<< "\n";
                    currVarVal[0] = '\0';
                }
                fillingIndex = 0;

                isValFilling = !isValFilling;
                isWeightFilling = !isWeightFilling;
                continue;


            }
            if(isValFilling)
            {
                currVarVal[fillingIndex] = residueStr[i];
                fillingIndex++;
            }

            if(isWeightFilling)
            {
                if((residueStr[i] != '(') && (residueStr[i] != ')') && (residueStr[i] != ','))
                {
                    currVarValWeight[fillingIndex] = residueStr[i];
                    fillingIndex++;
                }

            }
        }
        currVarValWeight[fillingIndex] = '\0';
        int currVarValWeightInt = atoi(currVarValWeight);
        VariantValue tempVarVal(currVarVal,currVarValWeightInt);
        setVarVals.AddToSet(tempVarVal);
        //cout << currVarVal << " " << currVarValWeightInt << "\n";

        delete [] currVarVal;
        delete [] currVarValWeight;

        char tempChar = fgetc(currFile);
        while(!feof(currFile))
        {
            if(tempChar == '\n')
            {
                break;
            }

            tempChar = fgetc(currFile);
        }

     /*   cout << refPoint<<" " << consPoint << " " << residueStr << " "<< refPointVal;
        if(isDeletion)
        {
            cout << " deletion\n";
        }
        else
        {
            cout << " no deletion\n";
        }*/



        //       fscanf(currFile,"%u\t%u\t%s\t%s\t%s\t%s\t%s",&refPoint,&consPoint,consensus,residue,IUPAC,status,notes);

   /*     char tempChar = fgetc(currFile);

        while(!feof(currFile))
        {
            if(tempChar == '\n')
            {
                break;
            }

            tempChar = fgetc(currFile);
        }


        cout << refPoint << " " << consPoint << " " << consensus << " " << residue << " " << IUPAC << " " << status << " " << notes << "\n";
*/
        //refPointVal++;
        VariantPoint tempVarPt(refPointVal,setVarVals,isDeletion);
        _varPts.AddToSet(tempVarPt);

    }





    delete [] refPoint;
    delete [] refPointToConvert;
    delete [] consPoint;
    delete [] consensus;
    delete [] residue;
    delete [] IUPAC;
    delete [] status;
    delete [] notes;
    fclose(currFile);
}


void VariantTextFile::PrintDebug()
{
    for(int i = 0; i < _varPts.GetSizeOfSet();i++)
    {
        cout <<"----------" << _varPts.GetItemByNum(i).GetRefPoint() << "----------\n";
        if(_varPts.GetItemByNum(i).IsDeletion())
        {
           cout <<"---------- deletion ----------\n";
        }
        else
        {
            cout <<"---------- no deletion ----------\n";
        }

        for(int j = 0;j < _varPts.GetItemByNum(i).GetSizeOfVariantValues();j++)
        {
            VariantValue tempCurrVarVal = _varPts.GetItemByNum(i).GetVariantValueByNum(j);

            cout << tempCurrVarVal.GetVariantText() << " " << tempCurrVarVal.GetVariantWeight() << "\n";
        }


    }
}

void VariantTextFile::FilterVarPtsByWeight(double minWeightRatio)
{
    cout << "In FilterVarPtsByWeight\n";

    SetOfVariantPoints setVarPts;
    for(int i = 0;i<_varPts.GetSizeOfSet();i++)
    {
        VariantPoint varPt = _varPts.GetItemByNum(i);
        int maxWeight = -1;

        if(varPt.GetSizeOfVariantValues() > 0)
        {
            if((varPt.GetVariantValueByNum(0).GetVariantText() == "(Complex") || (varPt.GetVariantValueByNum(0).GetVariantText() == "(Long"))
            {
                SetOfVariantValues setVarVals;

                VariantValue tempVarVal(varPt.GetVariantValueByNum(0).GetVariantText(),varPt.GetVariantValueByNum(0).GetVariantWeight());
                setVarVals.AddToSet(tempVarVal);
                VariantPoint newVarPt(varPt.GetRefPoint(),setVarVals,varPt.IsDeletion());

                setVarPts.AddToSet(newVarPt);
                continue;
            }

        }
        for(int j = 0; j < varPt.GetSizeOfVariantValues();j++)
        {
            if(varPt.GetVariantValueByNum(j).GetVariantWeight() > maxWeight)
            {
                maxWeight = varPt.GetVariantValueByNum(j).GetVariantWeight();
            }
        }



        SetOfVariantValues setVarVals;

        for(int j = 0; j < varPt.GetSizeOfVariantValues();j++)
        {

            int currWeight = varPt.GetVariantValueByNum(j).GetVariantWeight();

            //if(varPt.GetRefPoint() == 7211)
            //{

                //cout << "currWeight - " << currWeight<< "\n";
            //}

            if(maxWeight <= 0)
            {

                continue;
            }
            if((currWeight) > (minWeightRatio*maxWeight))
            {
                setVarVals.AddToSet(varPt.GetVariantValueByNum(j));
            }
        }

        if(setVarVals.GetSizeOfSet() < 2)
        {
             //cout << "varPt - " << varPt.GetRefPoint() << " maxWeight - " << maxWeight << "\n";
            continue;
        }

        VariantPoint newVarPt(varPt.GetRefPoint(),setVarVals,varPt.IsDeletion());

        setVarPts.AddToSet(newVarPt);

    }
    cout << "before filtering varPtsSet.size - " << _varPts.GetSizeOfSet() << "\n";
    int countVarVals = 0;

    for(int i = 0; i < _varPts.GetSizeOfSet();i++)
    {
        for(int j = 0; j < _varPts.GetItemByNum(i).GetSizeOfVariantValues();j++)
        {
            countVarVals++;
        }
    }
    cout << "before filtering varValsSet.size - " << countVarVals << "\n";

    _varPts = setVarPts;
    countVarVals = 0;
    for(int i = 0; i < setVarPts.GetSizeOfSet();i++)
    {
        for(int j = 0; j < setVarPts.GetItemByNum(i).GetSizeOfVariantValues();j++)
        {
            countVarVals++;
        }
    }
    cout << "after filtering varValsSet.size - " << countVarVals << "\n";
    cout << "after filtering varPtsSet.size - " << setVarPts.GetSizeOfSet() << "\n";
}
