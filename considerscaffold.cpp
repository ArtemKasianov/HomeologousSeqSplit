#include "considerscaffold.h"

ConsiderScaffold::ConsiderScaffold()
{
}

void ConsiderScaffold::CountStartAndEnd()
{

    if(_consPathes.GetSizeOfSet() <= 0)
    {
        _startPos = -1;
        _endPos = -1;
        return;
    }
    _startPos = _consPathes.GetItemByNum(0)->GetStartPos();
    _endPos = _consPathes.GetItemByNum(0)->GetEndPos();

   // cout << "CountStartAndEnd\n";
   //cout << "_startPos" <<_startPosLocal <<"\n";
   // cout << "_endPos"<< _endPos<< "\n";
   // cout << "end\n";
//return;

    if(_consPathes.GetSizeOfSet()==1)
    {
        return;
    }
    for(int i = 1;i<_consPathes.GetSizeOfSet();i++)
    {
        if(_startPos > _consPathes.GetItemByNum(i)->GetStartPos())
        {
            _startPos = _consPathes.GetItemByNum(i)->GetStartPos();
        }

        if(_endPos < _consPathes.GetItemByNum(i)->GetEndPos())
        {
            _endPos = _consPathes.GetItemByNum(i)->GetEndPos();
        }
    }
}

int ConsiderScaffold::CountConnectivityToPathLeft(ConsiderPath *consPathFrom)
{
    int countConn = 0;
    for(int i = 0;i < _consPathes.GetSizeOfSet();i++)
    {
        countConn += consPathFrom->GetPath()->CountConnectivityByPEReads(_consPathes.GetItemByNum(i)->GetPath());
    }

    return countConn;
}



int ConsiderScaffold::CountConnectivityToScaffoldLeft(ConsiderScaffold *consScaffFrom)
{
    int countConn = 0;
    for(int i = 0;i < _consPathes.GetSizeOfSet();i++)
    {
        for(int j = 0; j < consScaffFrom->GetSizeOfPathesSet();j++)
        {
            countConn += consScaffFrom->GetPathByNum(j)->GetPath()->CountConnectivityByPEReads(_consPathes.GetItemByNum(i)->GetPath());
        }
    }

    return countConn;
}


int ConsiderScaffold::CountConnectivityToPathRight(ConsiderPath *consPathTo)
{
    int countConn = 0;
    for(int i = 0;i < _consPathes.GetSizeOfSet();i++)
    {
       countConn += _consPathes.GetItemByNum(i)->GetPath()->CountConnectivityByPEReads(consPathTo->GetPath());
    }

    return countConn;
}


int ConsiderScaffold::CountConnectivityToScaffoldRight(ConsiderScaffold *consScaffTo)
{
    int countConn = 0;
    for(int i = 0;i < _consPathes.GetSizeOfSet();i++)
    {
        for(int j = 0; j < consScaffTo->GetSizeOfPathesSet();j++)
        {
            countConn += _consPathes.GetItemByNum(i)->GetPath()->CountConnectivityByPEReads(consScaffTo->GetPathByNum(j)->GetPath());
        }
    }

    return countConn;
}



int ConsiderScaffold::CheckIsTwoPathMoreConnectivityToScaffold(ConsiderPath *firstPath, ConsiderPath *secondPath)
{
    double weightFirst = 0.0;
    double weightSecond = 0.0;

    for(int i = 0;i < _consPathes.GetSizeOfSet();i++)
    {
        ConsiderPath *currConsPath = _consPathes.GetItemByNum(i);

        firstPath->GetPath()->CheckIsTwoPathMoreConnectivityToAnotherPath(secondPath->GetPath(),currConsPath->GetPath(),weightFirst,weightSecond);
    }

    if(weightFirst == weightSecond)
    {
        return 0;
    }
    else
    {
        if(weightFirst > weightSecond)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }

}


long int ConsiderScaffold::CheckConnectionBeetweenScaffolds(ConsiderScaffold *scaffB)
{
	long int connBeetweenScaff = 0;

    for(int i = 0; i<_consPathes.GetSizeOfSet();i++)
    {
        Path *pathA = _consPathes.GetItemByNum(i)->GetPath();

        for(int j = 0; j < scaffB->GetSizeOfPathesSet();j++)
        {
            Path *pathB = scaffB->GetPathByNum(j)->GetPath();

            connBeetweenScaff += pathA->GetFullReadList()->FindIntersectionOfListsByPE(pathB->GetCurrReadList()->GetReadList());

        }
    }
   // connBeetweenScaff = _readList.FindIntersectionOfListsByPE(scaffB->GetReadList());

   /* for(int iA = 0;iA<_consPathes.GetSizeOfSet();iA++)
	{
		Path *currPathA = _consPathes.GetItemByNum(iA)->GetPath();

		for(int jA = 0; jA < currPathA->GetSizeOfSimplifyVertexSet();jA++)
		{
			SimplifyVertex *currSVertexA = currPathA->GetSimplifyVertexByNum(jA);

			for(int kA = 0; kA < currSVertexA->GetVertexSetSize();kA++)
			{

				Vertex *currVertexA = currSVertexA->GetVertexByIndex(kA);

				for(int iB = 0;iB<scaffB->GetSizeOfPathesSet();iB++)
				{
					Path *currPathB = scaffB->GetPathByNum(iB)->GetPath();

					for(int jB = 0;jB < currPathB->GetSizeOfSimplifyVertexSet();jB++)
					{
						SimplifyVertex *currSVertexB = currPathB->GetSimplifyVertexByNum(jB);

						for(int kB = 0;kB < currSVertexB->GetVertexSetSize();kB++)
						{
							Vertex *currVertexB = currSVertexB->GetVertexByIndex(kB);


							connBeetweenScaff += currVertexA->GetReadsList().FindIntersectionOfListsByPE(currVertexB->GetReadsList().GetReadList());

						}
					}
				}




			}

		}
	}*/


    return connBeetweenScaff;

}


bool ConsiderScaffold::MergeScaffold(ConsiderScaffold *scaff)
{
    if(!((scaff->GetStartPos() >= _startPos) && (scaff->GetStartPos() <= _endPos)) &&
            !((scaff->GetEndPos() >= _startPos) && (scaff->GetEndPos() <= _endPos)) )
    {
        return false;
    }

    SetOfRef<ConsiderPath> consPathesNew;


        int i = 0;

        bool isIntersect = false;
        ConsiderPath *consPathA = _consPathes.GetItemByNum(i);
        
        for(int j = 0; j < scaff->GetSizeOfPathesSet();j++)
        {
            ConsiderPath *consPathB = scaff->GetPathByNum(j);

            if(consPathB->GetEndPos() < consPathA->GetStartPos())
            {
                consPathesNew.AddToSet(consPathB);
                continue;
            }

            if(((consPathB->GetStartPos() >= consPathA->GetStartPos()) && (consPathB->GetStartPos() <= consPathA->GetEndPos()))
                || ((consPathB->GetEndPos() >= consPathA->GetStartPos()) && (consPathB->GetEndPos() <= consPathA->GetEndPos())))
            {
                if(consPathB == consPathA)
                {
                    consPathesNew.AddToSet(consPathA);
                    i++;
                    if(i < _consPathes.GetSizeOfSet())
                    {
                        consPathA = _consPathes.GetItemByNum(i);
                    }

                    isIntersect = true;
                    continue;

                }
                else
                {
                    return false;
                }

            }

            if(consPathB->GetStartPos() > consPathA->GetEndPos())
            {
                if(i == _consPathes.GetSizeOfSet())
                {
                    consPathesNew.AddToSet(consPathB);
                }


                for(;i < _consPathes.GetSizeOfSet();i++)
                {
                    consPathA = _consPathes.GetItemByNum(i);
                    if(consPathB->GetStartPos() <= consPathA->GetEndPos())
                    {

                        j--;
                        break;
                    }

                    consPathesNew.AddToSet(consPathA);
                }






            }

        }

	 for(;i < _consPathes.GetSizeOfSet();i++)
        {
        	consPathA = _consPathes.GetItemByNum(i);
              consPathesNew.AddToSet(consPathA);
         }

        if(isIntersect)
        {
            /*cout << "Start\n";
            for(int i = 0; i < _consPathes.GetSizeOfSet();i++)
            {
                ConsiderPath *consPathX = _consPathes.GetItemByNum(i);

                for(int j = 0; j < consPathX->GetPath()->GetSizeOfSimplifyVertexSet();j++)
                {
                    SimplifyVertex* sVer = consPathX->GetPath()->GetSimplifyVertexByNum(j);

                    cout << sVer->GetName() << "_";
                }
            }
            cout << "\n";

            cout << "Path_to_merge\n";
            for(int i = 0; i < scaff->GetSizeOfPathesSet();i++)
            {
                ConsiderPath *consPathX = scaff->GetPathByNum(i);

                for(int j = 0; j < consPathX->GetPath()->GetSizeOfSimplifyVertexSet();j++)
                {
                    SimplifyVertex* sVer = consPathX->GetPath()->GetSimplifyVertexByNum(j);

                    cout << sVer->GetName() << "_";
                }
            }
            cout << "\n";

            _consPathes = consPathesNew;
            cout << "End\n";
            for(int i = 0; i < _consPathes.GetSizeOfSet();i++)
            {
                ConsiderPath *consPathX = _consPathes.GetItemByNum(i);

                for(int j = 0; j < consPathX->GetPath()->GetSizeOfSimplifyVertexSet();j++)
                {
                    SimplifyVertex* sVer = consPathX->GetPath()->GetSimplifyVertexByNum(j);

                    cout << sVer->GetName() << "_";
                }
            }
            cout << "\n";*/

            return true;
        }

        return false;


}



bool ConsiderScaffold::CheckEqualityOfScaffold(ConsiderScaffold *scaff, int iIndex, int jIndex)
{
    int maxSize = (scaff->GetSizeOfPathesSet() > _consPathes.GetSizeOfSet())?scaff->GetSizeOfPathesSet():_consPathes.GetSizeOfSet();
    int minSize = (scaff->GetSizeOfPathesSet() < _consPathes.GetSizeOfSet())?scaff->GetSizeOfPathesSet():_consPathes.GetSizeOfSet();
    bool equalSize = (maxSize==minSize)?true:false;

    int countEquals = 0;


    for(int i = 0; i < _consPathes.GetSizeOfSet();i++)
    {

        for(int j = 0; j < scaff->GetSizeOfPathesSet();j++)
        {
            if(_consPathes.GetItemByNum(i) == scaff->GetPathByNum(j))
            {
                countEquals++;
                break;
            }
        }
    }

    if(countEquals > 0)
    {
        cout << iIndex << " " << jIndex << " countEquals-" << countEquals << " iSize - " << _consPathes.GetSizeOfSet() << " jSize - " << scaff->GetSizeOfPathesSet() << "\n";
    }

    if(equalSize)
    {
        if(maxSize == countEquals)
        {
            return true;
        }
    }
    else
    {
        return false;
    }


    return true;
}
