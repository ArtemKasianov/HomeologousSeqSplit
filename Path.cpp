#include "Path.h"

int Path::CheckVertexConnectivityByPEReads(SimplifyVertex *vertexToCheck)
{
    int vertexToCheckCoor = vertexToCheck->GetVertexByIndex(0)->GetCoor();

    int countVertexConnected = 0;

    for(int i = _vertexies.GetSizeOfSet()-1;i >0;i--)
    {
        int currVertexCoor = _vertexies.GetItemByNum(i)->GetVertexByIndex(0)->GetCoor();
        SimplifyVertex *currSimplifyVertex = _vertexies.GetItemByNum(i);

        //if((vertexToCheckCoor - currVertexCoor) < 600)
        //{

            int connectivityCount = 0;
            for(int j = 0; j < 1/*vertexToCheck->GetVertexSetSize()*/;j++)
            {
                Vertex *currVertexToCheck = vertexToCheck->GetVertexByIndex(j);
                for(int k = 0;k < currSimplifyVertex->GetVertexSetSize();k++)
                {
                    Vertex *currVertex = currSimplifyVertex->GetVertexByIndex(k);
                    int currConnectivity = currVertexToCheck->GetReadsList().FindIntersectionOfListsByPE(currVertex->GetReadsList().GetReadList());
                    connectivityCount = connectivityCount + currConnectivity;
                }
            }

            if(connectivityCount > 0)
            {
                countVertexConnected = countVertexConnected + connectivityCount;
            }
        //}
    }

    return countVertexConnected;
}

int Path::CheckPathConnectivityByPEReads(Path *pathToCheck)
{
	int connectivity = 0;

    connectivity = _fullReadList.FindIntersectionOfListsByPE(pathToCheck->GetFullReadList()->GetReadList());//_readList.FindIntersectionOfListsByPE(pathTOCheck->GetReadList());

	/*for(int i = 0;i<_vertexies.GetSizeOfSet();i++)
	{
		SimplifyVertex *currSimpVertexA = _vertexies.GetItemByNum(i);
		for(int j = 0; j < currSimpVertexA->GetVertexSetSize();j++)
		{
			Vertex *currVertexA = currSimpVertexA->GetVertexByIndex(j);

			for(int k = 0; k < pathTOCheck->GetSizeOfSimplifyVertexSet();k++)
			{
				SimplifyVertex *currSimpVertexB = pathTOCheck->GetSimplifyVertexByNum(k);

				for(int m = 0; m < currSimpVertexB->GetVertexSetSize();m++)
				{
					Vertex *currVertexB = currSimpVertexB->GetVertexByIndex(j);

					connectivity = connectivity + currVertexA->GetReadsList().FindIntersectionOfListsByPE(currVertexB->GetReadsList().GetReadList());

				}

			}

		}

	}*/

	return connectivity;
}


int Path::CheckVertexConnectivityByPEReads(SimplifyVertex *vertexToCheck, fstream &debugFile)
{
	int countVertexConnected = 0;

    countVertexConnected = _fullReadList.FindIntersectionOfListsByPE(vertexToCheck->GetReadList());

//    int vertexToCheckCoor = vertexToCheck->GetVertexByIndex(0)->GetCoor();
   // debugFile << "vertexConnectToCoor - " << vertexToCheckCoor <<"\n";
	/*int countVertexConnected = 0;

	for(int i = _vertexies.GetSizeOfSet()-1;i >0;i--)
	{
		int currVertexCoor = _vertexies.GetItemByNum(i)->GetVertexByIndex(0)->GetCoor();
		SimplifyVertex *currSimplifyVertex = _vertexies.GetItemByNum(i);


			int connectivityCount = 0;
			for(int j = 0; j < 1;j++)
			{
				Vertex *currVertexToCheck = vertexToCheck->GetVertexByIndex(j);

				for(int k = 0;k < currSimplifyVertex->GetVertexSetSize();k++)
				{

					Vertex *currVertex = currSimplifyVertex->GetVertexByIndex(k);


					int currConnectivity = currVertexToCheck->GetReadsList().FindIntersectionOfListsByPE(currVertex->GetReadsList().GetReadList());
					connectivityCount = connectivityCount + currConnectivity;
				}
			}

			if(connectivityCount > 0)
			{
				countVertexConnected = countVertexConnected + connectivityCount;
			}
		//}
	} */

	return countVertexConnected;
}

std::string Path::GetName()
{
    std::string resultName;

    resultName = _vertexies.GetItemByNum(0)->GetName() + "_" + _vertexies.GetItemByNum(_vertexies.GetSizeOfSet()-1)->GetName();

    return resultName;

}

int Path::CheckEqualityOfPathes(Path* pathToCompare,int shiftFromEnd)
{

    if((pathToCompare->GetSizeOfSimplifyVertexSet()-shiftFromEnd) != GetSizeOfSimplifyVertexSet())
    {
        return 0;
    }
    for(int i = 0; i < (pathToCompare->GetSizeOfSimplifyVertexSet() - shiftFromEnd);i++ )
    {

        if(pathToCompare->GetSimplifyVertexByNum(i) != GetSimplifyVertexByNum(i))
        {
            return 0;
        }

    }

    return 1;
}


void Path::AddConnWeightToAnotherPath(int weight)
{
    if((_weightOfConnToAnotherPathes.GetSizeOfSet()-1)==_indexInResPath )
    {
        _weightOfConnToAnotherPathes.AddToSet(-1);
    }
    else
    {
        _weightOfConnToAnotherPathes.AddToSet(weight);
    }
}


int Path::CheckVertexConnectivityBySReads(SimplifyVertex *vertexToCheck)
{




    int vertexToCheckCoor = vertexToCheck->GetVertexByIndex(0)->GetCoor();

    if(_vertexies.GetSizeOfSet()<2)
    {
        return 0;
    }

    int checkingVertexStart = (_vertexies.GetSizeOfSet() >= 5)?_vertexies.GetSizeOfSet()-5:0;


    for(int i = _vertexies.GetSizeOfSet()-2;i >= 0; i--)
    {
        int currVertexCoor = _vertexies.GetItemByNum(i)->GetVertexByIndex(0)->GetCoor();
        SimplifyVertex *currSimplifyVertex = _vertexies.GetItemByNum(i);

        if((vertexToCheckCoor - currVertexCoor) < 100)
        {
             int connectivityCount = 0;

             connectivityCount = currSimplifyVertex->GetUniqueReadList().FindIntersectionOfLists(vertexToCheck->GetReadList());



        }

    }


    int countVertexConnected = 0;

    for(int i = _vertexies.GetSizeOfSet()-1;i >=0;i--)
    {
        int currVertexCoor = _vertexies.GetItemByNum(i)->GetVertexByIndex(0)->GetCoor();
        SimplifyVertex *currSimplifyVertex = _vertexies.GetItemByNum(i);


        if((vertexToCheckCoor - currVertexCoor) < 100)
        {

            int connectivityCount = 0;
            for(int j = 0; j < 1;j++)
            {
                Vertex *currVertexToCheck = vertexToCheck->GetVertexByIndex(j);
                for(int k = 0;k < currSimplifyVertex->GetVertexSetSize();k++)
                {

                    Vertex *currVertex = currSimplifyVertex->GetVertexByIndex(k);
                    int currConnectivity = currVertexToCheck->GetReadsList().FindIntersectionOfLists(currVertex->GetReadsList().GetReadList());
                    connectivityCount = connectivityCount + currConnectivity;
                }
            }

            if(connectivityCount > 0)
            {
                countVertexConnected = countVertexConnected + connectivityCount;
            }
        }
    }


    return countVertexConnected;


}
Path::Path(Path *startPath)
{
    for(int i = 0;i < startPath->GetSizeOfSimplifyVertexSet();i++)
    {
        this->AddVertex(startPath->GetSimplifyVertexByNum(i));
    }
}

int Path::CompDiffConnWithEqualLastVertex(Path* compPath, double minConn)
{

    double weightThis = 0.0;
    double weightComp = 0.0;

    Vertex *lastThisVertex = _vertexies.GetItemByNum(_vertexies.GetSizeOfSet()-1)->GetVertexByIndex(0);
    Vertex *lastCompVertex =compPath->GetSimplifyVertexByNum(compPath->GetSizeOfSimplifyVertexSet()-1)->GetVertexByIndex(0);
    for(int i = 0;i<_vertexies.GetSizeOfSet()-1;i++)
    {
        SimplifyVertex *currThisSimplVertex = _vertexies.GetItemByNum(i);
        for(int j = 0;j<currThisSimplVertex->GetVertexSetSize();j++)
        {
            Vertex *currThisVertex = currThisSimplVertex->GetVertexByIndex(j);
            bool isFoundEquality = false;
            for(int k = 0;k<compPath->GetSizeOfSimplifyVertexSet()-1;k++)
            {
                SimplifyVertex *currCompSimplVertex = compPath->GetSimplifyVertexByNum(k);
                for(int m = 0;m<currCompSimplVertex->GetVertexSetSize();m++)
                {
                    Vertex *currCompVertex = currCompSimplVertex->GetVertexByIndex(m);
                    if((currThisVertex->GetCoor() == currCompVertex->GetCoor()) && (currThisVertex->GetSymbol() != currCompVertex->GetSymbol()))
                    {
                        weightThis += lastThisVertex->GetReadsList().FindIntersectionOfListsByPE(currThisVertex->GetReadsList().GetReadList());
                        weightComp += lastCompVertex->GetReadsList().FindIntersectionOfListsByPE(currCompVertex->GetReadsList().GetReadList());
                        isFoundEquality = true;
                        break;
                    }

                }

                if(isFoundEquality)
                {
                    break;
                }
            }
        }
    }

    if(weightThis>weightComp)
    {
        if(weightComp < minConn*weightThis)
        {
            return 0;
        }

    }
    else
    {
        if(weightThis < minConn*weightComp)
        {
            return 1;
        }
    }

    return 2;


}

double Path::CountConnectivityByPEReads(Path* connTo)
{

	double weight = 0.0;

    weight = _fullReadList.FindIntersectionOfListsByPE(connTo->GetFullReadList()->GetReadList());
    //_readList.FindIntersectionOfListsByPE(connTo->GetReadList());

/*    for(int i = 0;i<_vertexies.GetSizeOfSet()-1;i++)
	{
		SimplifyVertex *currThisSimplVertex = _vertexies.GetItemByNum(i);
		for(int j = 0;j<currThisSimplVertex->GetVertexSetSize();j++)
		{
			Vertex *currThisVertex = currThisSimplVertex->GetVertexByIndex(j);

			for(int k = 0;k<connTo->GetSizeOfSimplifyVertexSet()-1;k++)
			{
				SimplifyVertex *currCompSimplVertex = connTo->GetSimplifyVertexByNum(k);
				for(int m = 0;m<currCompSimplVertex->GetVertexSetSize();m++)
				{
					Vertex *currCompVertex = currCompSimplVertex->GetVertexByIndex(m);

					weight += currThisVertex->GetReadsList().FindIntersectionOfListsByPE(currCompVertex->GetReadsList().GetReadList());
				}


			}
		}
	}
*/


    return weight;


}

void Path::AddEndedReadsToFullReadList()
{
    int lastVertexIndex = _vertexies.GetSizeOfSet()-1;

    SimplifyVertex *lastSVertex = _vertexies.GetItemByNum(lastVertexIndex);

    UniqueReadList tempReadList;

    int sizeOfCurrList = _currReadList.GetReadListRef()->GetSizeOfSet();

    for(int i = 0; i < sizeOfCurrList;i++)
    {
        if(!(lastSVertex->GetEndListRef().ExistThisRead(_currReadList.GetReadListRef()->GetRefItemByNum(i)->GetSequenceName())))
        {
            tempReadList.Add(_currReadList.GetReadListRef()->GetItemByNum(i));
        }
        else
        {
            _fullReadList.Add(_currReadList.GetReadListRef()->GetItemByNum(i));
        }
    }


    _currReadList.Clear();

    _currReadList.AddSetOfReadList(tempReadList.GetReadList());


}


void Path::AddStartedReadsToCurrReadList()
{
    int lastVertexIndex = _vertexies.GetSizeOfSet()-1;

    SimplifyVertex *lastSVertex = _vertexies.GetItemByNum(lastVertexIndex);

    _currReadList.AddSetOfReadList(lastSVertex->GetStartListRef().GetReadList());
}

void Path::AddAllCurrReadsToFullReadList()
{
    _fullReadList.AddSetOfReadList(_currReadList.GetReadList());

    _currReadList.Clear();
}

int Path::CheckIsTwoPathMoreConnectivityToAnotherPath(Path* compPath,Path *toPath, double minConn)
{

    double weightThis = 0.0;
	double weightComp = 0.0;



	weightThis = toPath->GetUniqueReadList().FindIntersectionOfListsByPE(_readList.GetReadList());
	weightComp = toPath->GetUniqueReadList().FindIntersectionOfListsByPE(compPath->GetReadList());


  /*  for(int z = 0;z<toPath->GetSizeOfSimplifyVertexSet();z++)
	{
		SimplifyVertex *currToSimplVertex = toPath->GetSimplifyVertexByNum(z);
		for(int y = 0;y<currToSimplVertex->GetVertexSetSize();y++)
		{

			Vertex *currToVertex = currToSimplVertex->GetVertexByIndex(y);
			for(int i = 0;i<_vertexies.GetSizeOfSet()-1;i++)
			{
				SimplifyVertex *currThisSimplVertex = _vertexies.GetItemByNum(i);
				for(int j = 0;j<currThisSimplVertex->GetVertexSetSize();j++)
				{
					Vertex *currThisVertex = currThisSimplVertex->GetVertexByIndex(j);
					bool isFoundEquality = false;
					for(int k = 0;k<compPath->GetSizeOfSimplifyVertexSet()-1;k++)
					{
						SimplifyVertex *currCompSimplVertex = compPath->GetSimplifyVertexByNum(k);
						for(int m = 0;m<currCompSimplVertex->GetVertexSetSize();m++)
						{
							Vertex *currCompVertex = currCompSimplVertex->GetVertexByIndex(m);
							if((currThisVertex->GetCoor() == currCompVertex->GetCoor()) && (currThisVertex->GetSymbol() != currCompVertex->GetSymbol()))
							{
								weightThis += currToVertex->GetReadsList().FindIntersectionOfListsByPE(currThisVertex->GetReadsList().GetReadList());
								weightComp += currToVertex->GetReadsList().FindIntersectionOfListsByPE(currCompVertex->GetReadsList().GetReadList());
								isFoundEquality = true;
								break;
							}

						}

						if(isFoundEquality)
						{
							break;
						}
					}
				}
			}
		}
	}*/

    if(weightThis>weightComp)
    {
        if(weightComp < minConn*weightThis)
        {
            return 0;
        }

    }
    else
    {
        if(weightThis < minConn*weightComp)
        {
            return 1;
        }
    }

    return 2;


}



void Path::CheckIsTwoPathMoreConnectivityToAnotherPath(Path* compPath,Path *toPath,double &weightThis, double &weightComp)
{
	weightThis = toPath->GetUniqueReadList().FindIntersectionOfListsByPE(_readList.GetReadList());
	weightComp = toPath->GetUniqueReadList().FindIntersectionOfListsByPE(compPath->GetReadList());

	/*for(int z = 0;z<toPath->GetSizeOfSimplifyVertexSet();z++)
	{
		SimplifyVertex *currToSimplVertex = toPath->GetSimplifyVertexByNum(z);
		for(int y = 0;y<currToSimplVertex->GetVertexSetSize();y++)
		{

			Vertex *currToVertex = currToSimplVertex->GetVertexByIndex(y);
			for(int i = 0;i<_vertexies.GetSizeOfSet()-1;i++)
			{
				SimplifyVertex *currThisSimplVertex = _vertexies.GetItemByNum(i);
				for(int j = 0;j<currThisSimplVertex->GetVertexSetSize();j++)
				{
					Vertex *currThisVertex = currThisSimplVertex->GetVertexByIndex(j);
					bool isFoundEquality = false;
					for(int k = 0;k<compPath->GetSizeOfSimplifyVertexSet()-1;k++)
					{
						SimplifyVertex *currCompSimplVertex = compPath->GetSimplifyVertexByNum(k);
						for(int m = 0;m<currCompSimplVertex->GetVertexSetSize();m++)
						{
							Vertex *currCompVertex = currCompSimplVertex->GetVertexByIndex(m);
							if((currThisVertex->GetCoor() == currCompVertex->GetCoor()) && (currThisVertex->GetSymbol() != currCompVertex->GetSymbol()))
							{
								weightThis += currToVertex->GetReadsList().FindIntersectionOfListsByPE(currThisVertex->GetReadsList().GetReadList());
								weightComp += currToVertex->GetReadsList().FindIntersectionOfListsByPE(currCompVertex->GetReadsList().GetReadList());
								isFoundEquality = true;
								break;
							}

						}

						if(isFoundEquality)
						{
							break;
						}
					}
				}
			}
		}
	} */




}








void Path::PrintPath(fstream &pathFile)
{
    for(int i = 0; i<_vertexies.GetSizeOfSet();i++)
    {
        pathFile << _vertexies.GetItemByNum(i)->GetName() << " ";

    }


    pathFile << "\n";
}

void Path::AddVertexAndCreatingNewPath(SimplifyVertex *vertexToAdd)
{

    _readList.AddSetOfReadList(vertexToAdd->GetReadList());
    _vertexies.AddToSet(vertexToAdd);

    UniqueReadList tempReadList;

    int sizeOfCurrList = _currReadList.GetReadListRef()->GetSizeOfSet();

    for(int i = 0; i < sizeOfCurrList;i++)
    {
        if(vertexToAdd->GetUniqueReadListRef()->ExistThisRead(_currReadList.GetReadListRef()->GetRefItemByNum(i)->GetSequenceName()))
        {
            tempReadList.Add(_currReadList.GetReadListRef()->GetItemByNum(i));
        }
    }

    _currReadList.Clear();

    _currReadList.AddSetOfReadList(tempReadList.GetReadList());

}


void Path::AddCurrReadList(UniqueReadList *currReadList)
{
    _currReadList.AddSetOfReadList(currReadList->GetReadList());
}

void Path::AddFullReadList(UniqueReadList *fullReadList)
{
    _fullReadList.AddSetOfReadList(fullReadList->GetReadList());
}


bool Path::CheckInclusionInPath(Path *path)
{

    for(int i = 0; i < _vertexies.GetSizeOfSet();i++)
    {
        bool isFound = false;
        for(int j = 0; j < path->GetSizeOfSimplifyVertexSet();j++)
        {
            if(_vertexies.GetItemByNum(i) == path->GetSimplifyVertexByNum(j))
            {
                isFound = true;
                break;
            }
        }

        if(!isFound)
        {
            return false;
        }
    }

    return true;
}


