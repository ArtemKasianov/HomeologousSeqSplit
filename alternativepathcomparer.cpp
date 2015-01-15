#include "alternativepathcomparer.h"

void AlternativePathComparer::CheckPathToLeft(ConsiderPath *altPath)
{
    int startScaff =  _currScaff->GetStartPos();
    int endScaff =  _currScaff->GetEndPos();
    int startConsPath =  altPath->GetStartPos();
    int endConsPath =  altPath->GetEndPos();



    if(_pathLeft == NULL)
    {
        int currWeightIn = _currScaff->CountConnectivityToPathLeft(altPath);
        if(currWeightIn>=minWeightToScaffoldByPE)
        {
            _maxWeightLeft = -1;
            _setOfWeightsLeft.Clear();

            _maxWeightLeft = currWeightIn;
            _setOfWeightsLeft.AddToSet(currWeightIn);
            _pathLeft = altPath;
        }
        return;
    }

    int startLeftPath = _pathLeft->GetStartPos();
    int endLeftPath = _pathLeft->GetEndPos();

    if(endConsPath < startLeftPath)
    {
        return;
    }

    int currWeight = _currScaff->CountConnectivityToPathLeft(altPath);
    if(currWeight<minWeightToScaffoldByPE)
    {
        return;
    }

    if(startConsPath > endLeftPath)
    {
        _maxWeightLeft = -1;
        _setOfWeightsLeft.Clear();

        _maxWeightLeft = currWeight;
        _setOfWeightsLeft.AddToSet(currWeight);
        _pathLeft = altPath;

        return;
    }


    _setOfWeightsLeft.AddToSet(currWeight);
    if(_maxWeightLeft > currWeight)
    {
        _maxWeightLeft = currWeight;

        _pathLeft = altPath;

    }














}

void AlternativePathComparer::CheckPathToRight(ConsiderPath *altPath)
{
    int startScaff =  _currScaff->GetStartPos();
    int endScaff =  _currScaff->GetEndPos();
    int startConsPath =  altPath->GetStartPos();
    int endConsPath =  altPath->GetEndPos();

       //return;
    if(_pathRight == NULL)
    {
        int currWeightIn = _currScaff->CountConnectivityToPathRight(altPath);
        if(currWeightIn>=minWeightToScaffoldByPE)
        {
            _maxWeightRight = -1;
            _setOfWeightsRight.Clear();

            _maxWeightRight = currWeightIn;
            _setOfWeightsRight.AddToSet(currWeightIn);

            _pathRight = altPath;
        }
        return;
    }

    int startRightPath = _pathRight->GetStartPos();
    int endRightPath = _pathRight->GetEndPos();

    if(startConsPath > endRightPath)
    {
        return;
    }


    int currWeight = _currScaff->CountConnectivityToPathRight(altPath);
    if(currWeight<minWeightToScaffoldByPE)
    {

        return;
    }

    if(endConsPath < startRightPath)
    {
        _maxWeightRight = -1;
        _setOfWeightsRight.Clear();

        _maxWeightRight = currWeight;
        _setOfWeightsRight.AddToSet(currWeight);
        _pathRight = altPath;

        return;
    }

    _setOfWeightsRight.AddToSet(currWeight);

    if(currWeight > _maxWeightRight)
    {

        _maxWeightRight = currWeight;
        _pathRight = altPath;
    }


}


void AlternativePathComparer::CheckPath(ConsiderPath *altPath,int maxIns)
{
    int startScaff =  _currScaff->GetStartPos();
    int endScaff =  _currScaff->GetEndPos();
    int startConsPath =  altPath->GetStartPos();
    int endConsPath =  altPath->GetEndPos();

   // cout << "startScaff - " << startScaff << "\n";
   // cout << "endScaff - " << endScaff << "\n";
   // cout << "startConsPath - " << startConsPath << "\n";
   // cout << "endConsPath - " << endConsPath << "\n";

    if((endConsPath < startScaff) && ((startScaff-endConsPath)<=maxIns))
    {
//      cout << "Left" << "\n";

        CheckPathToLeft(altPath);
        return;
    }

    if((endScaff < startConsPath) && ((startConsPath-endScaff)<=maxIns))
    {
//     cout << "Right" << "\n";

        CheckPathToRight(altPath);
        return;
    }

//  cout << "not Left not Right\n";

    ConsiderPath* pathCons = _currScaff->GetPathByNum(0);

    if(pathCons == NULL)
    {
//        cout << "pathCons NULL\n";
    }


}
