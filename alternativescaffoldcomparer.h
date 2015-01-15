#ifndef ALTERNATIVESCAFFOLDCOMPARER_H
#define ALTERNATIVESCAFFOLDCOMPARER_H
#include "considerpath.h"
#include "considerscaffold.h"
#include "usedpathes.h"


class AlternativeScaffoldComparer
{
private:
    SetOfRef<ConsiderScaffold> _leftScaffolds;
    SetOfRef<ConsiderScaffold> _rightScaffolds;

    int _maxWeightLeft;
    int _maxWeightRight;

    int _startLeft;
    int _endLeft;

    int _startRight;
    int _endRight;

    ConsiderScaffold *_currScaffold;

public:
    AlternativeScaffoldComparer(ConsiderScaffold *_currScaffold);

    void CheckScaffoldToLeft(ConsiderScaffold *altScaff);
    void CheckScaffoldToRight(ConsiderScaffold *altScaff);

    void CheckScaffold(ConsiderScaffold *altScaff);
};







class AlternativePathComparer
{
private:
    ConsiderPath *_pathLeft;
    ConsiderPath *_pathRight;

    int _maxWeightLeft;
    int _maxWeightRight;

    SetOf<int> _setOfWeightsLeft;
    SetOf<int> _setOfWeightsRight;

    void CheckPathToLeft(ConsiderPath *altPath);
    void CheckPathToRight(ConsiderPath *altPath);

    ConsiderScaffold *_currScaff;
public:
    AlternativePathComparer(ConsiderScaffold *currScaff)
    {
        _currScaff = currScaff;

        _pathLeft = NULL;

        _pathRight = NULL;

        _maxWeightLeft = -1;
        _maxWeightRight = -1;


        ConsiderPath* pathCons = _currScaff->GetPathByNum(0);

        if(pathCons == NULL)
        {
            cout << "in constructor NULL\n";
        }
        else
        {
            cout << "in constructor not NULL\n";
        }
    }

    ConsiderScaffold* GetResultScaff(UsedPathes &usPath)
    {

        ConsiderScaffold *resScaff = new ConsiderScaffold();
        if(_pathLeft != NULL)
        {

            usPath.AddPath(_pathLeft);
            resScaff->AddPath(_pathLeft);
        }


        for(int i = 0; i < _currScaff->GetSizeOfPathesSet();i++)
        {
            ConsiderPath *currPath = _currScaff->GetPathByNum(i);

//            if(currPath == NULL)
//            {
//                cout << "currPath - NULL\n";
//            }
            resScaff->AddPath(currPath);

        }


        if(_pathRight != NULL)
        {
            usPath.AddPath(_pathRight);
            resScaff->AddPath(_pathRight);
        }




        delete _currScaff;

        ConsiderPath* pathTemp = resScaff->GetPathByNum(0);
        if(pathTemp == NULL)
        {
            cout << "NULL PATH\n";
            return NULL;
        }


        resScaff->CountStartAndEnd();

        _currScaff = resScaff;


        return resScaff;
    }

    ConsiderScaffold* GetResultScaff(UsedPathes &usPath, fstream &fileStreamDebugScaffolder)
    {

        double minTreshold = 0.3;
        ConsiderScaffold *resScaff = new ConsiderScaffold();
        if(_pathLeft != NULL)
        {
            double tresholdLeft = minTreshold*_maxWeightLeft;
            int countPassed = 0;
            if(_setOfWeightsLeft.GetSizeOfSet() > 1)
            {
                for(int i = 0; i < _setOfWeightsLeft.GetSizeOfSet();i++)
                {
                    if(tresholdLeft <= *(_setOfWeightsLeft.GetRefItemByNum(i)))
                    {
                        countPassed++;
                    }
                }
            }

            if(countPassed < 2)
            {

                fileStreamDebugScaffolder << "pathLeft not NULL\n";
                //usPath.AddPath(_pathLeft);
                resScaff->AddPath(_pathLeft);
            }
            else
            {
                fileStreamDebugScaffolder << "pathLeft not resolved countPassed - "<< countPassed<<"\n";
            }
        }


        for(int i = 0; i < _currScaff->GetSizeOfPathesSet();i++)
        {
            ConsiderPath *currPath = _currScaff->GetPathByNum(i);

//            if(currPath == NULL)
//            {
//                cout << "currPath - NULL\n";
//            }
            fileStreamDebugScaffolder << "currPath not NULL\n";
            resScaff->AddPath(currPath);

        }


        if(_pathRight != NULL)
        {
            double tresholdRight = minTreshold*_maxWeightRight;
            int countPassed = 0;
            if(_setOfWeightsRight.GetSizeOfSet() > 1)
            {
                for(int i = 0; i < _setOfWeightsRight.GetSizeOfSet();i++)
                {
                    if(tresholdRight <= *(_setOfWeightsRight.GetRefItemByNum(i)))
                    {
                        countPassed++;
                    }
                }
            }

            if(countPassed < 2)
            {
                fileStreamDebugScaffolder << "pathRight not NULL\n";
                //usPath.AddPath(_pathRight);
                resScaff->AddPath(_pathRight);
            }
            else
            {
                fileStreamDebugScaffolder << "pathRight not resolved countPassed - "<< countPassed<<"\n";
            }
        }




        delete _currScaff;

        ConsiderPath* pathTemp = resScaff->GetPathByNum(0);
        if(pathTemp == NULL)
        {
            cout << "NULL PATH\n";
            return NULL;
        }


        resScaff->CountStartAndEnd();

        _currScaff = resScaff;


        return resScaff;
    }

    void CheckPath(ConsiderPath *altPath,int maxIns);
};

#endif // ALTERNATIVESCAFFOLDCOMPARER_H
