#ifndef SNPTEXTFILE_H
#define SNPTEXTFILE_H

#include <string>
#include <stdlib.h>
#include "FilesFormats.h"


class VariantValue
{

private:
    std::string _variantText;
    int _variantWeight;
public:
    VariantValue()
    {
        _variantText = "";
        _variantWeight = -1;
    }

    VariantValue(std::string variantText,int variantWeight)
    {
        _variantText = variantText;
        _variantWeight = variantWeight;
    }

    std::string GetVariantText()
    {
        return _variantText;
    }

    int GetVariantWeight()
    {
        return _variantWeight;
    }

    static VariantValue Empty()
    {
        return VariantValue();
    }

};

typedef SetOf<VariantValue> SetOfVariantValues;

class VariantPoint
{
private:
    int _refPoint;

    bool _isDeletion;
    SetOfVariantValues _varVals;
public:
    VariantPoint()
    {
        _refPoint = -1;

    }

    VariantPoint(int refPoint, SetOfVariantValues &varVals, bool isDeletion)
    {
        _refPoint = refPoint;
        _varVals = varVals;
        _isDeletion = isDeletion;
    }

    int GetRefPoint()
    {
        return _refPoint;
    }

    int GetSizeOfVariantValues()
    {
        return _varVals.GetSizeOfSet();
    }

    VariantValue GetVariantValueByNum(int index)
    {
        return _varVals.GetItemByNum(index);
    }

    static VariantPoint Empty()
    {
        return VariantPoint();
    }

    bool IsDeletion()
    {
        return _isDeletion;
    }

};

typedef SetOf<VariantPoint> SetOfVariantPoints;

class VariantTextFile
{
private:
    std::string _fileName;
    bool _isFileOpen;

    void LoadVariantPoints(FILE *fileHandle);

    SetOfVariantPoints _varPts;


public:
    VariantTextFile(std::string variantFileName);

    int GetSizeOfVariantPointsSet()
    {
        if(_isFileOpen)
        {
            return _varPts.GetSizeOfSet();
        }
        else
        {
            return -1;
        }
    }

    VariantPoint GetVariantPointByNum(int index)
    {
        if(_isFileOpen)
        {
            return _varPts.GetItemByNum(index);
        }
        else
        {
            return VariantPoint::Empty();
        }

    }

    void PrintDebug();

    void FilterVarPtsByWeight(double minWeightRatio);

};

#endif // SNPTEXTFILE_H
