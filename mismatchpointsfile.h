#ifndef MISMATCHPOINTSFILE_H
#define MISMATCHPOINTSFILE_H

#include <string>
#include <stdlib.h>
#include "FilesFormats.h"
#include "Vertex.h"

struct MismatchVariant
{
    unsigned position;
    bool isDeletion;
    std::string varText;
};

typedef SetOf<MismatchVariant> SetOfMismatchVars;

class PositionsList
{
private:
    HashUnsignedInt _insertedPositions;
    SetOf<unsigned> _storedValues;

public:
    unsigned GetPositionByNum(int index)
    {
        unsigned *refVal = _storedValues.GetRefItemByNum(index);

        if(refVal == NULL)
        {
            return -1;

        }
        else
        {
            return *refVal;
        }

    }

    int GetPositionsSize()
    {
        return _storedValues.GetSizeOfSet();
    }

    void AddPosition(unsigned position)
    {
        if(_insertedPositions.find(position) == _insertedPositions.end())
        {
            _storedValues.AddToSet(position);
            _insertedPositions[position] = 1;
        }
    }
};

class MismatchPointsFile
{
private:
    SetOfMismatchVars _mismatchVars;
    PositionsList _positions;
    bool _isFileOpen;
    int LoadFile(std::string fileName);
public:
    MismatchPointsFile(std::string fileName)
    {
        if(LoadFile(fileName))
        {
            _isFileOpen = true;
        }
        else
        {
            _isFileOpen = false;
        }
    }



    MismatchVariant* GetMismatchVarByNum(int index)
    {
        if(_isFileOpen)
        {
            return _mismatchVars.GetRefItemByNum(index);
        }
        else
        {
            return NULL;
        }
    }
    int GetNumberOfMismatchVars()
    {
        if(_isFileOpen)
        {
            return _mismatchVars.GetSizeOfSet();
        }
        else
        {
            return -1;
        }
    }

    void GetVarsByPosition(unsigned position,SetOfRef<MismatchVariant> &notInsertVars, SetOfRef<MismatchVariant> &insertVars);

    unsigned GetPositionsByNum(int index)
    {
        return _positions.GetPositionByNum(index);
    }

    int GetSizeOfPositionsSet()
    {
        return _positions.GetPositionsSize();
    }

};

#endif // MISMATCHPOINTSFILE_H
