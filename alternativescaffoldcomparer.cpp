#include "alternativescaffoldcomparer.h"

AlternativeScaffoldComparer::AlternativeScaffoldComparer(ConsiderScaffold *_currScaffold)
{
    _maxWeightLeft = -1;
    _maxWeightRight = -1;

    _startLeft = -1;
    _endLeft = -1;

    _startRight = -1;
    _endRight = -1;
}


void AlternativeScaffoldComparer::CheckScaffoldToLeft(ConsiderScaffold *altScaff)
{
    int startScaff =  _currScaffold->GetStartPos();
    int endScaff =  _currScaffold->GetEndPos();
    int startConsScaff =  altScaff->GetStartPos();
    int endConsScaff =  altScaff->GetEndPos();

    int currWeight = 0;

    if(_leftScaffolds.GetSizeOfSet() == 0)
    {
        currWeight = _currScaffold->CountConnectivityToScaffoldLeft(altScaff);
        if(currWeight>=minWeightToScaffoldByPE)
        {
            _maxWeightLeft = -1;
            _leftScaffolds.Clear();

            _maxWeightLeft = currWeight;


            altScaff->SetWeight(currWeight);
            _leftScaffolds.AddToSet(altScaff);

            _startLeft = startConsScaff;
            _endLeft = endConsScaff;

        }
        return;
    }





    if(endConsScaff < _startLeft)
    {
        return;
    }

    int currWeight = _currScaffold->CountConnectivityToScaffoldLeft(altScaff);
    if(currWeight<minWeightToScaffoldByPE)
    {
        return;
    }

    if(startConsScaff > _endLeft)
    {
        _maxWeightLeft = -1;
        _leftScaffolds.Clear();

        altScaff->SetWeight(currWeight);
        _maxWeightLeft = currWeight;
        _leftScaffolds.AddToSet(altScaff);

        _startLeft = startConsScaff;
        _endLeft = endConsScaff;

        return;
    }

    altScaff->SetWeight(currWeight);
    _leftScaffolds.AddToSet(altScaff);

    if(_startLeft > startConsScaff)
    {
        _startLeft = startConsScaff;
    }

    if(_endLeft < endConsScaff)
    {
        _endLeft = endConsScaff;
    }

    if(_maxWeightLeft > currWeight)
    {
        _maxWeightLeft = currWeight;


    }


}



void AlternativeScaffoldComparer::CheckScaffoldToRight(ConsiderScaffold *altScaff)
{
    int startScaff =  _currScaffold->GetStartPos();
    int endScaff =  _currScaffold->GetEndPos();
    int startConsScaff =  altScaff->GetStartPos();
    int endConsScaff =  altScaff->GetEndPos();

    int currWeight = 0;

    if(_rightScaffolds.GetSizeOfSet() == 0)
    {
        currWeight = _currScaffold->CountConnectivityToScaffoldRight(altScaff);
        if(currWeightIn>=minWeightToScaffoldByPE)
        {
            _maxWeightRight = -1;
            _rightScaffolds.Clear();

            _maxWeightRight = currWeight;
            altScaff->SetWeight(currWeight);
            _rightScaffolds.AddToSet(altScaff);

            _startRight = startConsScaff;
            _endRight = endConsScaff;
        }
        return;

    }





    if(startConsScaff > _endRight)
    {
        return;
    }


    int currWeight = _currScaffold->CountConnectivityToScaffoldRight(altScaff);
    if(currWeight<minWeightToScaffoldByPE)
    {

        return;
    }

    if(endConsScaff < _startRight)
    {
        _maxWeightRight = -1;
        _rightScaffolds.Clear();

        _maxWeightRight = currWeight;
        altScaff->SetWeight(currWeight);
        _rightScaffolds.AddToSet(altScaff);

        _startRight = startConsScaff;
        _endRight = endConsScaff;

        return;
    }
    altScaff->SetWeight(currWeight);
    _rightScaffolds.AddToSet(altScaff);

    if(_startRight > startConsScaff)
    {
        _startRight = startConsScaff;
    }

    if(_endRight < endConsScaff)
    {
        _endRight = endConsScaff;
    }

    if(currWeight > _maxWeightRight)
    {

        _maxWeightRight = currWeight;
    }
}


void AlternativePathComparer::CheckScaffold(ConsiderScaffold *altScaff)
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
      cout << "Left" << "\n";

        CheckPathToLeft(altPath);
        return;
    }

    if((endScaff < startConsPath) && ((startConsPath-endScaff)<=maxIns))
    {
     cout << "Right" << "\n";

        CheckPathToRight(altPath);
        return;
    }

  cout << "not Left not Right\n";

    ConsiderPath* pathCons = _currScaff->GetPathByNum(0);

    if(pathCons == NULL)
    {
        cout << "pathCons NULL\n";
    }


}
