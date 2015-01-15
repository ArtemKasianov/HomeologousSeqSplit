#include "Graph.h"
#include <string>
#include <stdlib.h>


void Graph::ClearGraph()
{
    for(int i = 0;i < _vertexies.GetSizeOfSet();i++)
    {
        delete _vertexies.GetItemByNum(i);
    }

    _vertexies.Clear();
    _firstVertexies.Clear();
}


void Graph::FillFirstVertexies()
{
    for(int i = 0;i< _vertexies.GetSizeOfSet();i++)
    {
        if(_vertexies.GetItemByNum(i)->GetConnFromVertexByIndex(0)._connVertex == NULL)
        {
            _firstVertexies.AddToSet(_vertexies.GetItemByNum(i));
        }
    }
}




void Graph::LoadFromGraphViz(std::string graphVizFile)
{
//    FILE *pGarphVizFile = fopen(graphVizFile.c_str(),"r");




//    char tempChar = fgetc(pGarphVizFile);

//    while(!feof(pGarphVizFile))
//    {
//        if(tempChar == '\n')
//        {
//            break;
//        }

//        tempChar = fgetc(pGarphVizFile);
//    }

//    int state = 0;

//    std::string readingStr = "";

//    char *firstVertexChar = new char[2];

//    while(!feof(pGarphVizFile))
//    {
//        tempChar = fgetc(pGarphVizFile);

//        if(tempChar == '}')
//        {
//            break;
//        }

//        if(tempChar == '\n')
//        {
//            break;
//        }

//        switch(state)
//        {
//        case 0 :
//            if(tempChar == '_')
//            {
//                if(readingStr.length() > 1)
//                {
//                    cout <<"FAULT\n";
//                    return;
//                }

//                firstVertexChar = readingStr.c_str();
//                readingStr = "";
//                state++;
//            }
//            readingStr = readingStr + tempChar;
//            break;
//        }



//        fscanf(pGarphVizFile,"%s->%s [weight=%u]",firstVertex,secondVertex,&connectWeight);
//        cout << firstVertex << " " << secondVertex << " " << connectWeight << "\n";
//        sscanf(firstVertex,"%s_%u",firstVertexLetter,&firstVertexCoor);
//        cout << firstVertexLetter << " " << firstVertexCoor << "\n";
//        sscanf(secondVertex,"%s_%u",secondVertexLetter,&secondVertexCoor);
//        cout << secondVertexLetter << " " << secondVertexCoor << "\n";


//        char tempChar = fgetc(pGarphVizFile);

//        while(!feof(pGarphVizFile))
//        {
//            if(tempChar == '\n')
//            {
//                break;
//            }

//            tempChar = fgetc(pGarphVizFile);
//        }


//    }




//    fclose(pGarphVizFile);
}





void SimplifyGraph::FindFirstVertex()
{
    for(int i = 0;i< _simplifyVertexies.GetSizeOfSet();i++)
    {
        if(_simplifyVertexies.GetItemByNum(i)->GetConnFromVertexByIndex(0)._connVertex == NULL)
        {
            _simplifyFirstVertexies.AddToSet(_simplifyVertexies.GetItemByNum(i));
        }
    }
}

void SimplifyGraph::ClearGraph()
{
    for(int i = 0;i < _simplifyVertexies.GetSizeOfSet();i++)
    {
        delete _simplifyVertexies.GetItemByNum(i);
    }

    _simplifyVertexies.Clear();
    _simplifyFirstVertexies.Clear();
}

void SimplifyGraph::FillSimplifyVertex(SimplifyVertex *simplifyVertex, Vertex *startVertex)
{
    Vertex *currVertex = startVertex;
    if(_addedVertexies.find(currVertex->GetName()) == _addedVertexies.end())
    {
        _addedVertexies[currVertex->GetName()] = 1;
    }
    else
    {
        return;
    }
    while((currVertex->GetConnToVertexByIndex(0)._connVertex != NULL) && (currVertex->GetConnectToSize() == 1) && 
(((Vertex*)currVertex->GetConnToVertexByIndex(0)._connVertex)->GetConnectFromSize() == 1))
    {
        simplifyVertex->AddVertex(currVertex);
        
    currVertex = (Vertex*)currVertex->GetConnToVertexByIndex(0)._connVertex;
    }
    simplifyVertex->AddVertex(currVertex);
    simplifyVertex->SetName(simplifyVertex->GetVertexByIndex(0)->GetName() + "_" + simplifyVertex->GetVertexByIndex(simplifyVertex->GetVertexSetSize()-1)->GetName());


    if(currVertex->GetConnToVertexByIndex(0)._connVertex == NULL)
    {
        return;
    }


    for(int i = 0; i < currVertex ->GetConnectToSize();i++)
    {

        SimplifyVertex *tempPtrSimplifyVertex = new SimplifyVertex();
        this->AddVertex(tempPtrSimplifyVertex);
        FillSimplifyVertex(tempPtrSimplifyVertex,(Vertex*)currVertex->GetConnToVertexByIndex(i)._connVertex);
        simplifyVertex->ConnectToVertex(tempPtrSimplifyVertex,currVertex->GetConnToVertexByIndex(i)._weight);
        tempPtrSimplifyVertex->ConnectFromVertex(simplifyVertex,currVertex->GetConnToVertexByIndex(i)._weight);

    }
}

void SimplifyGraph::CreateSimplifyVertex(Vertex* verToAdd,SimplifyVertex *simplifyVertex)
{
	Vertex *currVertex = verToAdd;

	while((currVertex->GetConnFromVertexByIndex(0)._connVertex != NULL) &&
			(currVertex->GetConnectFromSize() == 1) &&
		  (((Vertex*)currVertex->GetConnFromVertexByIndex(0)._connVertex)->GetConnectToSize() == 1) &&
		  _addedVertexies.find(currVertex->GetName()) == _addedVertexies.end())
	{
		currVertex = (Vertex*)currVertex->GetConnFromVertexByIndex(0)._connVertex;
	}




	while((currVertex->GetConnToVertexByIndex(0)._connVertex != NULL) && (currVertex->GetConnectToSize() == 1) &&
	(((Vertex*)currVertex->GetConnToVertexByIndex(0)._connVertex)->GetConnectFromSize() == 1))
	{
		simplifyVertex->AddVertex(currVertex);
		_addedVertexies[currVertex->GetName()] = 1;
		currVertex = (Vertex*)currVertex->GetConnToVertexByIndex(0)._connVertex;
	}

	simplifyVertex->AddVertex(currVertex);
	_addedVertexies[currVertex->GetName()] = 1;
	simplifyVertex->SetName(simplifyVertex->GetVertexByIndex(0)->GetName() + "_" + simplifyVertex->GetVertexByIndex(simplifyVertex->GetVertexSetSize()-1)->GetName());


}


void SimplifyGraph::CreateSimplifyVertex_simple(Vertex* verToAdd,SimplifyVertex *simplifyVertex)
{
	Vertex *currVertex = verToAdd;


	simplifyVertex->AddVertex(currVertex);
	_addedVertexies[currVertex->GetName()] = 1;
	simplifyVertex->SetName(simplifyVertex->GetVertexByIndex(0)->GetName() + "_" + simplifyVertex->GetVertexByIndex(0)->GetName());


}

void SimplifyGraph::EaseGraph(Graph *graphToSimplify)
{


    for(int i = 0;i<graphToSimplify->GetVertexSetSize();i++)
    {
        Vertex *currVertex = graphToSimplify->GetVertexByIndex(i);
        if(_addedVertexies.find(currVertex->GetName()) == _addedVertexies.end())
        {

            SimplifyVertex *tempPtrSimplifyVertex = new SimplifyVertex();
            this->AddVertex(tempPtrSimplifyVertex);
            CreateSimplifyVertex(currVertex,tempPtrSimplifyVertex);

        }
    }


    for(int i = 0;i < this->GetVertexSetSize();i++)
    {
        SimplifyVertex *currSimplifyVertex;
        currSimplifyVertex = this->GetSimplifyVertexByIndex(i);


        for(int j = 0;j < currSimplifyVertex->GetVertexSetSize();j++)
        {
            Vertex* currVertex = currSimplifyVertex->GetVertexByIndex(j);
            
            this->_mapVertexToSimplifyVertex[currVertex->GetName()] = currSimplifyVertex;
        }



    }


    for(int i = 0;i < this->GetVertexSetSize();i++)
    {
        SimplifyVertex *currSimplifyVertex = this->GetSimplifyVertexByIndex(i);


        Vertex *firstVertex = currSimplifyVertex->GetVertexByIndex(0);
        Vertex *lastVertex = currSimplifyVertex->GetVertexByIndex(currSimplifyVertex->GetVertexSetSize()-1);

        if(firstVertex->GetConnFromVertexByIndex(0)._connVertex != NULL)
        {
            for(int j = 0;j < firstVertex->GetConnectFromSize();j++)
            {


                Vertex *currConnFromVertex = (Vertex*)firstVertex->GetConnFromVertexByIndex(j)._connVertex;

                SimplifyVertex *currConnFromSimplifyVertex = this->_mapVertexToSimplifyVertex[currConnFromVertex->GetName()];

                currSimplifyVertex->ConnectFromVertex(currConnFromSimplifyVertex,firstVertex->GetConnFromVertexByIndex(j)._weight);

            }
        }


        if(lastVertex->GetConnToVertexByIndex(0)._connVertex != NULL)
        {
            for(int j = 0;j < lastVertex->GetConnectToSize();j++)
            {

                Vertex *currConnToVertex = (Vertex*)lastVertex->GetConnToVertexByIndex(j)._connVertex;

                SimplifyVertex *currConnToSimplifyVertex = this->_mapVertexToSimplifyVertex[currConnToVertex->GetName()];

                currSimplifyVertex->ConnectToVertex(currConnToSimplifyVertex,lastVertex->GetConnToVertexByIndex(j)._weight);
            }
		}

	}



}




void SimplifyGraph::EaseGraph_simple(Graph *graphToSimplify)
{


	for(int i = 0;i<graphToSimplify->GetVertexSetSize();i++)
	{
		Vertex *currVertex = graphToSimplify->GetVertexByIndex(i);
		if(_addedVertexies.find(currVertex->GetName()) == _addedVertexies.end())
		{

			SimplifyVertex *tempPtrSimplifyVertex = new SimplifyVertex();
			this->AddVertex(tempPtrSimplifyVertex);


			CreateSimplifyVertex_simple(currVertex,tempPtrSimplifyVertex);

		}
	}


	for(int i = 0;i < this->GetVertexSetSize();i++)
	{
		SimplifyVertex *currSimplifyVertex;
		currSimplifyVertex = this->GetSimplifyVertexByIndex(i);


		for(int j = 0;j < currSimplifyVertex->GetVertexSetSize();j++)
		{
			Vertex* currVertex = currSimplifyVertex->GetVertexByIndex(j);

			this->_mapVertexToSimplifyVertex[currVertex->GetName()] = currSimplifyVertex;
		}



	}


	for(int i = 0;i < this->GetVertexSetSize();i++)
	{
		SimplifyVertex *currSimplifyVertex = this->GetSimplifyVertexByIndex(i);


		Vertex *firstVertex = currSimplifyVertex->GetVertexByIndex(0);
		Vertex *lastVertex = currSimplifyVertex->GetVertexByIndex(currSimplifyVertex->GetVertexSetSize()-1);

		if(firstVertex->GetConnFromVertexByIndex(0)._connVertex != NULL)
		{
			for(int j = 0;j < firstVertex->GetConnectFromSize();j++)
			{


				Vertex *currConnFromVertex = (Vertex*)firstVertex->GetConnFromVertexByIndex(j)._connVertex;

				SimplifyVertex *currConnFromSimplifyVertex = this->_mapVertexToSimplifyVertex[currConnFromVertex->GetName()];

				currSimplifyVertex->ConnectFromVertex(currConnFromSimplifyVertex,firstVertex->GetConnFromVertexByIndex(j)._weight);

			}
		}


		if(lastVertex->GetConnToVertexByIndex(0)._connVertex != NULL)
		{
			for(int j = 0;j < lastVertex->GetConnectToSize();j++)
			{

				Vertex *currConnToVertex = (Vertex*)lastVertex->GetConnToVertexByIndex(j)._connVertex;

				SimplifyVertex *currConnToSimplifyVertex = this->_mapVertexToSimplifyVertex[currConnToVertex->GetName()];

				currSimplifyVertex->ConnectToVertex(currConnToSimplifyVertex,lastVertex->GetConnToVertexByIndex(j)._weight);
			}
		}

	}



}



void Graph::PrintGraph(fstream &graphFile)
{
	graphFile << "digraph startGraph{\n";


    for(int i = 0; i < _vertexies.GetSizeOfSet();i++)
    {

        _vertexies.GetItemByNum(i)->PrintVertex((graphFile));

    }

    graphFile << "}\n";
}

void SimplifyGraph::PrintGraph(fstream &graphFile)
{
    graphFile << "digraph simplifyGraph{\n";
    for(int i = 0; i < _simplifyVertexies.GetSizeOfSet();i++)
    {
        _simplifyVertexies.GetItemByNum(i)->PrintVertex((graphFile));
    }
    graphFile << "}\n";
}

void SimplifyGraph::ContinuePath(Path *pathToContinue, SetOfPathes &pathes, SimplifyVertex *currVertex)
{
    if(currVertex->GetConnToVertexByIndex(0)._connVertex == NULL)
    {
        return;
    }

    Path tempPath(pathToContinue);

    bool isPathContinued = false;

    SimplifyVertex *nextVertex = (SimplifyVertex*)currVertex->GetConnToVertexByIndex(0)._connVertex;

    int sReadsConnectivity = pathToContinue->CheckVertexConnectivityBySReads(nextVertex);
    int peReadsConnectivity = pathToContinue->CheckVertexConnectivityByPEReads(nextVertex);

    if((sReadsConnectivity>0) || (peReadsConnectivity > 0))
    {

        pathToContinue->AddVertex(nextVertex);
        pathToContinue->AddSReadWeights(sReadsConnectivity);
        pathToContinue->AddPEReadWeights(peReadsConnectivity);
        isPathContinued = true;
 
        ContinuePath(pathToContinue,pathes,nextVertex);

    }






    if(currVertex->GetConnectToSize() > 1)
    {
        for(int i = 0; i < currVertex->GetConnectToSize();i++)
        {
            nextVertex = (SimplifyVertex*)currVertex->GetConnToVertexByIndex(i)._connVertex;

            if(isPathContinued)
            {

                Path newPath(tempPath);

                int sReadsConnectivity = newPath.CheckVertexConnectivityBySReads(nextVertex);
                int peReadsConnectivity = newPath.CheckVertexConnectivityByPEReads(nextVertex);

                if((sReadsConnectivity>0) || (peReadsConnectivity > 0))
                {

                    newPath.AddVertex(nextVertex);
                    newPath.AddSReadWeights(sReadsConnectivity);
                    newPath.AddPEReadWeights(peReadsConnectivity);

                    ContinuePath(&newPath,pathes,nextVertex);
                }

                pathes.AddToSet(newPath);
            }
            else
            {
                int sReadsConnectivity = pathToContinue->CheckVertexConnectivityBySReads(nextVertex);
                int peReadsConnectivity = pathToContinue->CheckVertexConnectivityByPEReads(nextVertex);

                if((sReadsConnectivity>0) || (peReadsConnectivity > 0))
                {

                    pathToContinue->AddVertex(nextVertex);
                    pathToContinue->AddSReadWeights(sReadsConnectivity);
                    pathToContinue->AddPEReadWeights(peReadsConnectivity);
                    isPathContinued = true;
   
                    ContinuePath(pathToContinue,pathes,nextVertex);

                }
            }

        }
    }
}

void SimplifyGraph::GetAndPrintPath_Debug(fstream &debugFile)
{
    SimplifyVertex *firstVertex = _simplifyFirstVertexies.GetItemByNum(0);

    debugFile << "digraph debugGraph{\n";

    bool stop = false;

    Path *pathToContinue = new Path();

    SimplifyVertex *prevVertex = firstVertex;

    SimplifyVertex *nextVertex = (SimplifyVertex*)prevVertex->GetConnToVertexByIndex(1)._connVertex;

    pathToContinue->AddVertex(firstVertex);


    int sReadsConnectivity = pathToContinue->CheckVertexConnectivityBySReads(nextVertex);
    int peReadsConnectivity = pathToContinue->CheckVertexConnectivityByPEReads(nextVertex);

    if((sReadsConnectivity>0)||(peReadsConnectivity>0))
    {
        pathToContinue->AddVertex(nextVertex);
        debugFile << prevVertex->GetName() << "->" << nextVertex->GetName();
        debugFile << " [label=" << sReadsConnectivity << "," << peReadsConnectivity << "]\n";
    }
    else
    {
        debugFile << "}\n";

        delete pathToContinue;
    }



    while(!stop)
    {



        SimplifyVertex *nextVertex = (SimplifyVertex*)prevVertex->GetConnToVertexByIndex(0)._connVertex;




        if(nextVertex == NULL)
        {
            break;
        }


        int sReadsConnectivity = pathToContinue->CheckVertexConnectivityBySReads(nextVertex);
        int peReadsConnectivity = pathToContinue->CheckVertexConnectivityByPEReads(nextVertex);

        if((sReadsConnectivity>0)||(peReadsConnectivity>0))
        {
            pathToContinue->AddVertex(nextVertex);
            debugFile << prevVertex->GetName() << "->" << nextVertex->GetName();
            debugFile << " [label=" << sReadsConnectivity << "," << peReadsConnectivity << "]\n";
        }
        else
        {
            break;
        }



        prevVertex = nextVertex;
    }


    debugFile << "}\n";

    delete pathToContinue;
}



/*void FilterConsiderPathByWeight(SetOf<int> &indexiesOfCheckingPathes,SetOf<int> &sendPathToResult, SetOfRef<PathWithMetaData> &considerPathes,SetOfRef<PathWithMetaData> &considerPathesChecked, fstream &debugFile)
{
    double maxWeightConsider = -1.0;
    for(int j = 0; j < indexiesOfCheckingPathes.GetSizeOfSet();j++)
    {
        if(considerPathes.GetItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)))->_weight > maxWeightConsider)
        {
            maxWeightConsider= considerPathes.GetItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)))->_weight;
        }

    }
    debugFile << "max weight - " << maxWeightConsider<< "\n";


    for(int j = 0; j < indexiesOfCheckingPathes.GetSizeOfSet();j++)
    {
        PathWithMetaData *tempConsiderPathes = considerPathes.GetItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)));
        debugFile << "considerPathes i=" << *(indexiesOfCheckingPathes.GetRefItemByNum(j)) << "\n";
        double weightTemp = tempConsiderPathes->_weight;
        debugFile << "weight - " << weightTemp << "\n";
        if(weightTemp > 0.3*maxWeightConsider)
        {
            debugFile << "Added to result\n";
            *(sendPathToResult.GetRefItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)))) = 1;
        }
        else
        {
            debugFile << "Excluded from result\n";
            *(sendPathToResult.GetRefItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)))) = 0;
        }

        considerPathesChecked.AddToSet(tempConsiderPathes);
    }
}*/

bool CheckExistenseInIntSet(int val, SetOf<int> &setToCheck)
{
    for(int i = 0; i < setToCheck.GetSizeOfSet();i++)
    {
        if(*(setToCheck.GetRefItemByNum(i)) == val)
        {
            return true;
        }
    }

    return false;
}

bool FilterConsiderPathByWeight(SetOf<int> &indexiesOfCheckingPathes,SetOf<int> &sendPathToResult, SetOfRef<PathWithMetaData> &considerPathes,SetOfRef<PathWithMetaData> &considerPathesChecked, fstream &debugFile)
{
    double maxWeightConsider = -1.0;
    int indexOfMax = -1;
    for(int j = 0; j < indexiesOfCheckingPathes.GetSizeOfSet();j++)
    {
        if(considerPathes.GetItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)))->_weight > maxWeightConsider)
        {
            maxWeightConsider= considerPathes.GetItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)))->_weight;
            indexOfMax = *(indexiesOfCheckingPathes.GetRefItemByNum(j));
        }

    }

    SetOf<int> indexiesOfNotExcludedPathes;
    SetOf<int> indexiesOfUsedPathes;
    indexiesOfUsedPathes.AddToSet(indexOfMax);
    PathWithMetaData *maxConsiderPath = considerPathes.GetItemByNum(indexOfMax);

    debugFile << "max weight - " << maxWeightConsider<< "\n";




    for(int j = 0; j < indexiesOfCheckingPathes.GetSizeOfSet();j++)
    {
        if(CheckExistenseInIntSet(j,indexiesOfUsedPathes))
        {
            continue;
        }


        PathWithMetaData *tempConsiderPathes = considerPathes.GetItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)));




        debugFile << "considerPathes i=" << *(indexiesOfCheckingPathes.GetRefItemByNum(j)) << "\n";
        double weightTemp = tempConsiderPathes->_weight;
        debugFile << "weight - " << weightTemp << "\n";
        if(weightTemp <= 0.3*maxWeightConsider)
        {
            debugFile << "Excluded from result\n";
            *(sendPathToResult.GetRefItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)))) = 0;
            considerPathesChecked.AddToSet(tempConsiderPathes);
        }
        else
        {
            indexiesOfNotExcludedPathes.AddToSet(*(indexiesOfCheckingPathes.GetRefItemByNum(j)));
        }
    }

    if(indexiesOfNotExcludedPathes.GetSizeOfSet() == 1)
    {
        *(sendPathToResult.GetRefItemByNum(*(indexiesOfNotExcludedPathes.GetRefItemByNum(0)))) = 1;
        considerPathesChecked.AddToSet(considerPathes.GetItemByNum(*(indexiesOfNotExcludedPathes.GetRefItemByNum(0))));
        return false;
    }


    bool isEqualExist = false;

    for(int i = 0; i < indexiesOfNotExcludedPathes.GetSizeOfSet();i++)
    {


        PathWithMetaData *currCheckingPath = considerPathes.GetItemByNum(*(indexiesOfNotExcludedPathes.GetRefItemByNum(i)));

        for(int j = i+1;j < indexiesOfNotExcludedPathes.GetSizeOfSet();j++)
        {
            PathWithMetaData *pathToCompare = considerPathes.GetItemByNum(*(indexiesOfNotExcludedPathes.GetRefItemByNum(j)));

            if(currCheckingPath->_weight == pathToCompare->_weight)
            {
                isEqualExist = true;
                break;
            }

        }

        if(isEqualExist)
        {
            break;
        }
    }

    if(isEqualExist)
    {
        for(int i = 0; i < considerPathes.GetSizeOfSet();i++)
        {
            *(sendPathToResult.GetRefItemByNum(i)) = 0;
        }
    }
    else
    {
        for(int i = 0; i < indexiesOfNotExcludedPathes.GetSizeOfSet();i++)
        {
            *(sendPathToResult.GetRefItemByNum(*(indexiesOfNotExcludedPathes.GetRefItemByNum(i)))) = 1;
        }
    }

    for(int i = 0; i < indexiesOfNotExcludedPathes.GetSizeOfSet();i++)
    {
        considerPathesChecked.AddToSet(considerPathes.GetItemByNum(*(indexiesOfNotExcludedPathes.GetRefItemByNum(i))));
    }

    return isEqualExist;

}


/*bool FilterConsiderPathByWeight(SetOf<int> &indexiesOfCheckingPathes,SetOf<int> &sendPathToResult, SetOfRef<PathWithMetaData> &considerPathes,SetOfRef<PathWithMetaData> &considerPathesChecked, fstream &debugFile)
{
    double maxWeightConsider = -1.0;
    for(int j = 0; j < indexiesOfCheckingPathes.GetSizeOfSet();j++)
    {
        if(considerPathes.GetItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)))->_weight > maxWeightConsider)
        {
            maxWeightConsider= considerPathes.GetItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)))->_weight;
        }

    }
    debugFile << "max weight - " << maxWeightConsider<< "\n";

    SetOf<int> &indexiesOfNotExcludedPathes;
    for(int j = 0; j < indexiesOfCheckingPathes.GetSizeOfSet();j++)
    {
        PathWithMetaData *tempConsiderPathes = considerPathes.GetItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)));
        debugFile << "considerPathes i=" << *(indexiesOfCheckingPathes.GetRefItemByNum(j)) << "\n";
        double weightTemp = tempConsiderPathes->_weight;
        debugFile << "weight - " << weightTemp << "\n";
        if(weightTemp <= 0.3*maxWeightConsider)
        {
            debugFile << "Excluded from result\n";
            *(sendPathToResult.GetRefItemByNum(*(indexiesOfCheckingPathes.GetRefItemByNum(j)))) = 0;
            considerPathesChecked.AddToSet(tempConsiderPathes);
        }
        else
        {
            indexiesOfNotExcludedPathes.AddToSet(*(indexiesOfCheckingPathes.GetRefItemByNum(j)));
        }
    }

    if(indexiesOfNotExcludedPathes.GetSizeOfSet() == 1)
    {
        *(sendPathToResult.GetRefItemByNum(*(indexiesOfNotExcludedPathes.GetRefItemByNum(0)))) = 1;
        considerPathesChecked.AddToSet(considerPathes.GetItemByNum(*(indexiesOfNotExcludedPathes.GetRefItemByNum(0))));
        return false;
    }


    bool isEqualExist = false;

    for(int i = 0; i < indexiesOfNotExcludedPathes.GetSizeOfSet();i++)
    {


        PathWithMetaData *currCheckingPath = considerPathes.GetItemByNum(*(indexiesOfNotExcludedPathes.GetRefItemByNum(i)));

        for(int j = i+1;j < indexiesOfNotExcludedPathes.GetSizeOfSet();j++)
        {
            PathWithMetaData *pathToCompare = considerPathes.GetItemByNum(*(indexiesOfNotExcludedPathes.GetRefItemByNum(j)));

            if(currCheckingPath->_weight == pathToCompare->_weight)
            {
                isEqualExist = true;
                break;
            }

        }

        if(isEqualExist)
        {
            break;
        }
    }

    if(isEqualExist)
    {
        for(int i = 0; i < considerPathes.GetSizeOfSet();i++)
        {
            *(sendPathToResult.GetRefItemByNum(i)) = 0;
        }
    }
    else
    {
        for(int i = 0; i < indexiesOfNotExcludedPathes.GetSizeOfSet();i++)
        {
            *(sendPathToResult.GetRefItemByNum(*(indexiesOfNotExcludedPathes.GetRefItemByNum(i)))) = 1;
        }
    }

    for(int i = 0; i < indexiesOfNotExcludedPathes.GetSizeOfSet();i++)
    {
        considerPathesChecked.AddToSet(considerPathes.GetItemByNum(*(indexiesOfNotExcludedPathes.GetRefItemByNum(i))));
    }

    return isEqualExist;

}*/


int FilterConsiderPathByWeight(SetOf<int> &sendPathToResult, SetOfRef<PathWithMetaData> &considerPathes)
{
    double maxWeightConsiderNew = 0.0;

    for(int i = 0; i < considerPathes.GetSizeOfSet();i++)
    {
        if(*(sendPathToResult.GetRefItemByNum(i)))
        {
            if(considerPathes.GetItemByNum(i)->_weight > maxWeightConsiderNew )
            {
                maxWeightConsiderNew = considerPathes.GetItemByNum(i)->_weight;
            }

        }

    }

    int numberOfConsideredPathes = 0;

    for(int i = 0; i < sendPathToResult.GetSizeOfSet();i++)
    {
        if(*(sendPathToResult.GetRefItemByNum(i)) == 1)
        {
            numberOfConsideredPathes++;
        }
    }

    if(numberOfConsideredPathes <= 4)
    {
        for(int i = 0;i<considerPathes.GetSizeOfSet();i++)
        {
            double weightTemp = considerPathes.GetItemByNum(i)->_weight;

            if((weightTemp < 0.3*maxWeightConsiderNew ))
            {

                *(sendPathToResult.GetRefItemByNum(i)) = 0;

            }

        }
    }
    else
    {
        for(int i = 0;i<considerPathes.GetSizeOfSet();i++)
        {
            double weightTemp = considerPathes.GetItemByNum(i)->_weight;

            if((weightTemp < 0.5*maxWeightConsiderNew ))
            {

                *(sendPathToResult.GetRefItemByNum(i)) = 0;

            }

        }
    }

    int numberOfResultPathes = 0;

    for(int i = 0; i < sendPathToResult.GetSizeOfSet();i++)
    {
        if(*(sendPathToResult.GetRefItemByNum(i)) == 0)
        {
            numberOfResultPathes++;
        }
    }

    return numberOfResultPathes;
}


void FindWhatNewBranchedPathesCorrect(fstream &debugFile,SetOfRef<PathWithMetaData> &considerPathes,SetOfRef<PathWithMetaData> &considerPathesTemp,SetOf<SetOf<int> > &currPathsConsiderPathIndexies, int currPathIndex, double minTreshold)
{
    int maxPathWeight = 0;
    for(int k = 0;k < considerPathesTemp.GetSizeOfSet();k++)
    {
        if(considerPathesTemp.GetItemByNum(k)->_weight > maxPathWeight)
        {
            maxPathWeight = considerPathesTemp.GetItemByNum(k)->_weight;
        }
    }

    debugFile << "considerPathes size=" << considerPathes.GetSizeOfSet() <<"\n";
    debugFile << "maxPathWeight = " << maxPathWeight << "\n";

    double treshold = minTreshold*maxPathWeight;

    debugFile << "treshold = " << treshold << "\n";


    for(int k = 0; k < considerPathesTemp.GetSizeOfSet();k++)
    {
        if(considerPathesTemp.GetItemByNum(k)->_weight > treshold)
        {

            considerPathes.AddToSet(considerPathesTemp.GetItemByNum(k));
            currPathsConsiderPathIndexies.GetRefItemByNum(currPathIndex)->AddToSet(considerPathes.GetSizeOfSet()-1);
        }
        else
        {
            debugFile << "considerPath k=" << k <<" excluded" << "\n";
        }
    }
}

bool CheckPathWithMetaDataExistenceInConsiderPathes(PathWithMetaData *pathMetaData, SetOfRef<PathWithMetaData> &considerPath)
{
    for(int j = 0; j < considerPath.GetSizeOfSet();j++)
    {
        if(considerPath.GetItemByNum(j) == pathMetaData)
        {
            return true;
        }
    }

    return false;
}

int CompareConsiderPathesAndCountSignificance(fstream &debugFile,PathWithMetaData *currPathMetaData,PathWithMetaData *nextPathMetaData, double minTreshold)
{
    SimplifyVertex *currLastVertex = currPathMetaData->_lastVertex;
    SimplifyVertex *nextLastVertex = nextPathMetaData->_lastVertex;


    Path *currPath = currPathMetaData->_path;
    Path *nextPath = nextPathMetaData->_path;

    unsigned currWeight = 0;
    unsigned nextWeight = 0;


    for(int i = 0; i < currPath->GetSizeOfSimplifyVertexSet();i++)
    {
        SimplifyVertex *currSVertex = currPath->GetSimplifyVertexByNum(i);

        for(int j = 0;j<nextPath->GetSizeOfSimplifyVertexSet();j++)
        {
            SimplifyVertex *nextSVertex = nextPath->GetSimplifyVertexByNum(j);

            if((currSVertex->GetStartPos() != nextSVertex->GetStartPos()) ||
                    (currSVertex->GetEndPos() != nextSVertex->GetEndPos()) )
            {
                continue;
            }

            if(currSVertex != nextSVertex)
            {
                currWeight += currSVertex->GetUniqueReadList().FindIntersectionOfLists(currLastVertex->GetReadList());
                currWeight += currSVertex->GetUniqueReadList().FindIntersectionOfListsByPE(currLastVertex->GetReadList());

                nextWeight += nextSVertex->GetUniqueReadList().FindIntersectionOfLists(nextLastVertex->GetReadList());
                nextWeight += nextSVertex->GetUniqueReadList().FindIntersectionOfListsByPE(nextLastVertex->GetReadList());
            }

            break;

        }
    }

    debugFile << "Comparing\n";
    debugFile << "currWeight - " << currWeight << "\n";
    debugFile << "nextWeight - " << nextWeight << "\n";

    if(currWeight == 0 && nextWeight == 0)
    {
        return 3;
    }


    int maxWeightIndex = (nextWeight > currWeight)?1:0;

    if(maxWeightIndex == 0)
    {
        if(currWeight < minTreshold*nextWeight)
        {
            return 1;
        }
    }
    else
    {
        if(nextWeight < minTreshold*currWeight)
        {
            return 0;
        }
    }

    return 2;
}

bool ExistIntInSetOfInt(SetOf<int> set, int val)
{
    for(int i = 0; i < set.GetSizeOfSet();i++)
    {
        if(val == *(set.GetRefItemByNum(i)))
        {
            return true;
        }
    }

    return false;
}

void ValidatePathesWithCommonNextVertexies(fstream &debugFile,SetOfRef<PathWithMetaData> &considerPathes, SetOf<int> &sendPathToResult,SetOf<int> &indexiesOfPathesWithCommonNextVertex,double minTreshold,int countIter, int iVal)
{
    SetOf<SetOfFastqSeqRecordsRef> differencesOfListsOfPathes;
    UniqueReadList tempUReadList;
    for(int i = 0;i<indexiesOfPathesWithCommonNextVertex.GetSizeOfSet();i++)
    {
        int currIndex = *(indexiesOfPathesWithCommonNextVertex.GetRefItemByNum(i));

        Path *currPath = considerPathes.GetItemByNum(currIndex)->_path;

        UniqueReadList *currPathCurrReadList = currPath->GetCurrReadList();


        UniqueReadListRef currPathCurrReadListRef = currPathCurrReadList->DiversityFromReadList(tempUReadList);

        for(int j = 0; j < indexiesOfPathesWithCommonNextVertex.GetSizeOfSet();j++)
        {
            if(i == j) continue;

            int checkIndex = *(indexiesOfPathesWithCommonNextVertex.GetRefItemByNum(j));

            Path *checkPath = considerPathes.GetItemByNum(checkIndex)->_path;

            UniqueReadList *checkPathCurrReadList = checkPath->GetCurrReadList();


            UniqueReadListRef checkPathCurrReadListRef = checkPathCurrReadList->DiversityFromReadList(tempUReadList);


            currPathCurrReadListRef.DiversityFromReadListIn(checkPathCurrReadListRef);

        }

        debugFile << "Path index=" << currIndex << " " <<" weight = " << currPathCurrReadListRef.GetReadList().GetSizeOfSet() << "\n";

        differencesOfListsOfPathes.AddToSet(currPathCurrReadListRef.GetReadList());

    }

//1



    int maxIndex = -1;
    int maxVal = -1;

    for(int i = 0; i < differencesOfListsOfPathes.GetSizeOfSet();i++)
    {
        if(differencesOfListsOfPathes.GetRefItemByNum(i)->GetSizeOfSet() > maxVal)
        {
            maxVal = differencesOfListsOfPathes.GetRefItemByNum(i)->GetSizeOfSet();
            maxIndex = i;
        }
    }


//2



    if(maxVal == 0)
    {
        for(int i = 0; i < indexiesOfPathesWithCommonNextVertex.GetSizeOfSet();i++ )
        {
             int currIndex = *(indexiesOfPathesWithCommonNextVertex.GetRefItemByNum(i));
             *(sendPathToResult.GetRefItemByNum(currIndex)) = 0;
             debugFile << "Path index=" << currIndex << " excluded from result weight - " << differencesOfListsOfPathes.GetRefItemByNum(i)->GetSizeOfSet()<<"\n";
        }

        return;
    }

//3

//    if(iVal == 1)
//    {
//        if(countIter == 13)
//        {
//            return;
//        }
//    }

    double treshold = minTreshold*maxVal;

    debugFile << "treshold = " << treshold << "\n";

    for(int i = 0; i <indexiesOfPathesWithCommonNextVertex.GetSizeOfSet();i++ )
    {

        int currIndex = *(indexiesOfPathesWithCommonNextVertex.GetRefItemByNum(i));
        if((differencesOfListsOfPathes.GetRefItemByNum(i)->GetSizeOfSet() == 0) ||  (treshold >  differencesOfListsOfPathes.GetRefItemByNum(i)->GetSizeOfSet()))
        {
            *(sendPathToResult.GetRefItemByNum(currIndex)) = 0;
            debugFile << "Path index=" << currIndex << " excluded from result weight - " << differencesOfListsOfPathes.GetRefItemByNum(i)->GetSizeOfSet()<<"\n";
        }
        else
        {
            *(sendPathToResult.GetRefItemByNum(currIndex)) = 1;
            debugFile << "Path index=" << currIndex << " added to result weight - " << differencesOfListsOfPathes.GetRefItemByNum(i)->GetSizeOfSet()<<"\n";
        }
    }

//4


}

void CheckSignificanceOfConsiderPathesWeights(fstream &debugFile,SetOf<int> *indexOfConsiderPathes,SetOfRef<PathWithMetaData> &considerPathes, SetOf<int> &sendPathToResult,double minTreshold,int countIter)
{

    SetOf<int> indexChecked;

    for(int i = 0; i < indexOfConsiderPathes->GetSizeOfSet();i++)
    {

        int currIndex = *(indexOfConsiderPathes->GetRefItemByNum(i));
//1

        if(ExistIntInSetOfInt(indexChecked,currIndex)) continue;
//2

        indexChecked.AddToSet(currIndex);
//3


        PathWithMetaData *currPathMetaData = considerPathes.GetItemByNum(currIndex);
//4


    //    SetOfRef<PathWithMetaData> pathesWithCommonNextVertex;
        SetOf<int> indexiesOfPathesWithCommonNextVertex;
//5

        //pathesWithCommonNextVertex.AddToSet(currPathMetaData);
        indexiesOfPathesWithCommonNextVertex.AddToSet(currIndex);
//6



        SimplifyVertex *currLastVertex = currPathMetaData->_path->GetSimplifyVertexByNum(currPathMetaData->_path->GetSizeOfSimplifyVertexSet()-2);
        SimplifyVertex *currNextVertex = currPathMetaData->_path->GetSimplifyVertexByNum(currPathMetaData->_path->GetSizeOfSimplifyVertexSet()-1);

        debugFile << "currPathIndex = " << currIndex << "\n";
        debugFile << "currLastVertexName - " << currLastVertex->GetName()<<"\n" << "currNextVertexName - "  << currNextVertex->GetName() << "\n";
        debugFile << "_path->GetSizeOfSimplifyVertexSet() - " << currPathMetaData->_path->GetSizeOfSimplifyVertexSet();



        for(int j = i+1; j < indexOfConsiderPathes->GetSizeOfSet();j++)
        {



            int checkIndex = *(indexOfConsiderPathes->GetRefItemByNum(j));
            PathWithMetaData *checkPathMetaData = considerPathes.GetItemByNum(checkIndex);
            SimplifyVertex *checkLastVertex = checkPathMetaData->_path->GetSimplifyVertexByNum(checkPathMetaData->_path->GetSizeOfSimplifyVertexSet()-2);
            SimplifyVertex *checkNextVertex = checkPathMetaData->_path->GetSimplifyVertexByNum(checkPathMetaData->_path->GetSizeOfSimplifyVertexSet()-1);




            if(checkNextVertex == currNextVertex)
            {

                debugFile << "checkPathIndex = " << checkIndex << "\n";
                debugFile << "checkLastVertexName - " << checkLastVertex->GetName() << "\n"<<"checkNextVertexName - "  << checkNextVertex->GetName() << "\n";


            //    pathesWithCommonNextVertex.AddToSet(checkPathMetaData);
                indexiesOfPathesWithCommonNextVertex.AddToSet(checkIndex);
                indexChecked.AddToSet(checkIndex);
            }



        }



        ValidatePathesWithCommonNextVertexies(debugFile,considerPathes,sendPathToResult,indexiesOfPathesWithCommonNextVertex,minTreshold,countIter,i);
        /*if((countIter == 13) && (i == 1))
        {
            return;
        }*/

    }





}


void SimplifyGraph::GetAndPrintPath_Debug(fstream &debugFile, int numOfParalogs, SetOfRef<Path> *resultPathes,SetOfRef<Path> *pathesToFree)
{
    //SetOfRef<Path> *resultPathes = new SetOfRef<Path>();
    SetOfRef<PathWithMetaData> *currPathes = new SetOfRef<PathWithMetaData>();
    
    
    fstream fileRangeTest("peReadsRange.test",fstream::out);

    
    //SetOfRef<Path> *pathesToFree = new SetOfRef<Path>();
    SetOfRef<PathWithMetaData> *pathesMetaToFree = new SetOfRef<PathWithMetaData>();

    //Path *testPath = new Path();

    //resultPathes->AddToSet(testPath);
   // delete testPath;

    try
    {


        for(int i = 0;i < _simplifyFirstVertexies.GetSizeOfSet();i++)
        {
            //debugFile << "firstVertex i=" << i << "\n";
            PathWithMetaData *currPathMeta = new PathWithMetaData();
            Path *currPath = new Path();
            pathesToFree->AddToSet(currPath);
            pathesMetaToFree->AddToSet(currPathMeta);
            currPathMeta->_lastVertex = _simplifyFirstVertexies.GetItemByNum(i);
            currPath->AddVertex(currPathMeta->_lastVertex);
            currPath->GetCurrReadList()->AddSetOfReadList(_simplifyFirstVertexies.GetItemByNum(i)->GetReadList());
            currPathMeta->_path = currPath;
            currPathMeta->_weight = 0;
            currPathMeta->_pWeight = 0;
            currPathMeta->_sWeight = 0;
            currPathMeta->_eWeight = 0;
            currPathes->AddToSet(currPathMeta);

        }

        //return;


        bool stop = false;
        int countIteration = 0;
        while((currPathes->GetSizeOfSet() > 0) && !stop)
        {
            SetOfRef<PathWithMetaData> considerPathes;
            SetOfRef<SimplifyVertex> setOfConToVertexes;

            //debugFile << "Start resolving stage\n";

            debugFile << "Iteration number = " << countIteration<< "\n";




            for(int i = 0;i < currPathes->GetSizeOfSet();i++)
            {
                PathWithMetaData *currPathMeta = currPathes->GetItemByNum(i);
                for(int j = 0; j < currPathMeta->_lastVertex->GetConnectToSize();j++)
                {
                    SimplifyVertex *currLastVertex = currPathMeta->_lastVertex;
                    if(currLastVertex->GetConnToVertexByIndex(j)._connVertex == NULL)
                    {
                        stop = true;
                        break;
                    }
                    bool isFoundSVertex = false;
                    for(int k = 0;k < setOfConToVertexes.GetSizeOfSet();k++)
                    {
                        if(((SimplifyVertex*)currPathMeta->_lastVertex->GetConnToVertexByIndex(j)._connVertex) == (setOfConToVertexes.GetItemByNum(k)))
                        {
                            isFoundSVertex = true;
                            break;
                        }
                    }


                    if(!isFoundSVertex)
                    setOfConToVertexes.AddToSet((SimplifyVertex*)currPathMeta->_lastVertex->GetConnToVertexByIndex(j)._connVertex);
                }

                currPathes->GetItemByNum(i)->_path->AddEndedReadsToFullReadList();

                if(stop)
                {
                    break;
                }
            }

            if(stop)
            {
                break;
            }





            SetOf<SetOf<int> > currPathsConsiderPathIndexies;

            for(int i = 0;i<currPathes->GetSizeOfSet();i++)
            {
              debugFile << "Path number i=" << i << "\n";

                SimplifyVertex *currVertex = currPathes->GetItemByNum(i)->_lastVertex;
                debugFile << "Last vertex name - " << currVertex->GetName()<< "\n";

                bool isNotAllZero = false;


                SetOfRef<PathWithMetaData> considerPathesTemp;

                SetOf<int> currPathesConsiderPathesSet;

                currPathsConsiderPathIndexies.AddToSet(currPathesConsiderPathesSet);


                for(int j = 0;j<currVertex->GetConnectToSize();j++)
                {
                    SimplifyVertex *nextVertex = (SimplifyVertex*)currVertex->GetConnToVertexByIndex(j)._connVertex;

                  debugFile << "To vertex name - " << nextVertex->GetName() << "\n";

                    double weight = currVertex->GetConnToVertexByIndex(j)._weight;
                    debugFile << "weight In Graph - " << weight << "\n";


                    Path *oldPath = currPathes->GetItemByNum(i)->_path;
                    Path *newOldPath = new Path();
                    pathesToFree->AddToSet(newOldPath);
                    for(int k = 0;k< oldPath->GetSizeOfSimplifyVertexSet();k++)
                    {
                        newOldPath->AddVertex(oldPath->GetSimplifyVertexByNum(k));
                    }

                    newOldPath->AddCurrReadList(oldPath->GetCurrReadList());
                    newOldPath->AddFullReadList(oldPath->GetFullReadList());

                    newOldPath->AddVertexAndCreatingNewPath(nextVertex);

                    weight = newOldPath->GetCurrReadList()->GetReadListRef()->GetSizeOfSet();
                    //newOldPath->AddStartedReadsToCurrReadList();



                    debugFile << "weight - " << weight << "\n";

                    if(weight == 0)
                    {

                        //resultPathes->AddToSet(currPathes->GetItemByNum(i)->_path);
                       debugFile << "Path send to result - cause connect weight = 0\n";

                        break;
                    }

                    isNotAllZero = true;
                    
                    //newOldPath->AddVertex(nextVertex);

                    PathWithMetaData *pathMeta = new PathWithMetaData();
                    pathesMetaToFree->AddToSet(pathMeta);

                    pathMeta->_lastVertex = nextVertex;
                    pathMeta->_path = newOldPath;
                    pathMeta->_weight = weight;
                    pathMeta->_eWeight = -1;
                    pathMeta->_pWeight = -1;
                    pathMeta->_sWeight = -1;
                    


                    //debugFile << "To vertex added to path weight = " << weight<<"\n";

                    considerPathesTemp.AddToSet(pathMeta);


                }

                if(!isNotAllZero)
                {
                    //resultPathes->AddToSet(currPathes->GetItemByNum(i)->_path);
                    //numberOfResultPathesAdded++;
                }
                else
                {
                    debugFile << "currPath i=" << i << "\n";
                    FindWhatNewBranchedPathesCorrect(debugFile,considerPathes,considerPathesTemp,currPathsConsiderPathIndexies,i,0.3);

                }





            }







           // debugFile << "Generation of pathes ended\n";

            SetOfRef<PathWithMetaData> considerPathesNew;
            SetOf<int> sendPathToResult;

            for(int i = 0; i < considerPathes.GetSizeOfSet();i++)
            {


                sendPathToResult.AddToSet(1);
            }



            for(int i = 0; i < currPathsConsiderPathIndexies.GetSizeOfSet();i++)
            {
                SetOf<int> *indexOfConsiderPathes = currPathsConsiderPathIndexies.GetRefItemByNum(i);

                if(indexOfConsiderPathes->GetSizeOfSet() < 2)
                {
                    if(indexOfConsiderPathes->GetSizeOfSet() == 1)
                    {

                        *(sendPathToResult.GetRefItemByNum(0)) = 1;

                    }



                    continue;
                }

                debugFile << "considerPath i=" << i<<"\n";
                CheckSignificanceOfConsiderPathesWeights(debugFile,indexOfConsiderPathes,considerPathes,sendPathToResult,0.3,countIteration);






            }




            /*if(countIteration == 13)
            {
                return;
            }*/


			for(int i = 0; i < considerPathes.GetSizeOfSet();i++)
            {
                if(*(sendPathToResult.GetRefItemByNum(i)))
                {
                    debugFile << "considerPath i="<< i<<" added to result set\n";
                    considerPathesNew.AddToSet(considerPathes.GetItemByNum(i));
                }
                else
                {
                    debugFile << "considerPath i="<< i<<" excluded from result set\n";

                }
            }







            bool isEqualPathFound = false;
            int numberOfResultPathesAdded = 0;

            SetOf<int> indexiesOfCurrPathesAddedToResultPathes;
            for(int i = 0;i<currPathes->GetSizeOfSet();i++)
            {
                //debugFile << "currPath i=" << i << " checking\n";
                isEqualPathFound = false;
                for(int j = 0; j < considerPathesNew.GetSizeOfSet();j++)
                {
                    if(currPathes->GetItemByNum(i)->_path->CheckEqualityOfPathes(considerPathesNew.GetItemByNum(j)->_path,1))
                    {
                        //debugFile << "currPath i=" << i << " equal to path j=" << j << "\n";
                        isEqualPathFound = true;
                        break;
                    }
                }

                if(!isEqualPathFound)
                {



                    Path* pathTemp = currPathes->GetItemByNum(i)->_path;
                    indexiesOfCurrPathesAddedToResultPathes.AddToSet(i);
                    //if((pathTemp->GetSimplifyVertexByNum(pathTemp->GetSizeOfSimplifyVertexSet()-1)->GetConnToVertexByIndex(0)._connVertex == NULL) /*||(pathTemp->GetSizeOfSimplifyVertexSet() > 1)*/)
                    //{
                    numberOfResultPathesAdded++;
					pathTemp->AddAllCurrReadsToFullReadList();
					debugFile << "Added to resultPathes path - " << pathTemp->GetName() << std::endl;
                    debugFile << "resultPathes FullReadsSet - " << pathTemp->GetFullReadList()->GetReadListRef()->GetSizeOfSet() << std::endl;
					resultPathes->AddToSet(pathTemp);
					//}

				}

            }


            for(int i = 0; i < setOfConToVertexes.GetSizeOfSet();i++)
            {
                //debugFile << "connToVertexies i=" << i << " checking\n";
                bool isEqualVertexFound = false;
                for(int j = 0; j < considerPathesNew.GetSizeOfSet();j++)
                {
                    if(setOfConToVertexes.GetItemByNum(i) == considerPathesNew.GetItemByNum(j)->_lastVertex)
                    {
                        //debugFile << "connToVertexies i=" << i << " equal considerPathNewTo vertex j=" << j<< "\n";
                        isEqualVertexFound = true;
                    }
                }

                if(!isEqualVertexFound)
                {
                    PathWithMetaData *pathMetaNew = new PathWithMetaData();
                    Path *singleVertexPathNew = new Path();
                    pathesToFree->AddToSet(singleVertexPathNew);
                    pathesMetaToFree->AddToSet(pathMetaNew);

                    //SimplifyVertex *sVertex = setOfConToVertexes.GetItemByNum(i);
                    /*bool isZeroWeightFound = false;
                    for(int k =0;k< sVertex->GetConnectFromSize();k++)
                    {
                        if(sVertex->GetConnFromVertexByIndex(k)._weight == 0)
                        {
                            isZeroWeightFound = true;
                            break;
                        }
                    }

                    for(int k =0;k< sVertex->GetConnectToSize();k++)
                    {
                        if(sVertex->GetConnToVertexByIndex(k)._weight == 0)
                        {
                            isZeroWeightFound = true;
                            break;
                        }
                    }

                    if(!isZeroWeightFound)
                    {

                        continue;
                    }*/

                    singleVertexPathNew->AddVertex(setOfConToVertexes.GetItemByNum(i));
                    singleVertexPathNew->GetCurrReadList()->AddSetOfReadList(setOfConToVertexes.GetItemByNum(i)->GetReadList());

                    pathMetaNew->_lastVertex = setOfConToVertexes.GetItemByNum(i);
                    pathMetaNew->_path = singleVertexPathNew;
                    pathMetaNew->_weight = -1;

                    considerPathesNew.AddToSet(pathMetaNew);

                    //debugFile << "To vertex i=" << i << " without in edges and create new path\n";
                }


			}

			debugFile << "considerPathesNew.GetSizeOfSet() - " << considerPathesNew.GetSizeOfSet() << std::endl;
			debugFile << "numberOfResultPathesAdded - " << numberOfResultPathesAdded << std::endl;

			int currNumOfParalogs = considerPathesNew.GetSizeOfSet()+numberOfResultPathesAdded;

			debugFile << "currNumOfParalogs - " << currNumOfParalogs << std::endl;

			if((considerPathesNew.GetSizeOfSet()+numberOfResultPathesAdded) > numOfParalogs)
			{


				debugFile << "currNumOfParalogs above 4" << std::endl;

				for(int i = 0; i < currPathes->GetSizeOfSet();i++)
				{
					if(!ExistIntInSetOfInt(indexiesOfCurrPathesAddedToResultPathes,i))
                    {
						currPathes->GetItemByNum(i)->_path->AddAllCurrReadsToFullReadList();
						debugFile << "Added to resultPathes path - " << currPathes->GetItemByNum(i)->_path->GetName() << std::endl;
                        debugFile << "resultPathes FullReadsSet - " << currPathes->GetItemByNum(i)->_path->GetFullReadList()->GetReadListRef()->GetSizeOfSet() << std::endl;
						resultPathes->AddToSet(currPathes->GetItemByNum(i)->_path);
					}
                }
                currPathes->Clear();

                int sizeOfConToVertexies = setOfConToVertexes.GetSizeOfSet();

                if(sizeOfConToVertexies > numOfParalogs)
                {
                    sizeOfConToVertexies = numOfParalogs;
                    debugFile << "Danger situation size of conTo above "<< sizeOfConToVertexies <<"!!!\n";
                }

                for(int i = 0;i < sizeOfConToVertexies;i++)
                {
                    PathWithMetaData *pathMetaNew = new PathWithMetaData();
                    Path *singleVertexPathNew = new Path();
                    pathesToFree->AddToSet(singleVertexPathNew);
                    pathesMetaToFree->AddToSet(pathMetaNew);

                    SimplifyVertex *sVertex = setOfConToVertexes.GetItemByNum(i);

                    singleVertexPathNew->AddVertex(setOfConToVertexes.GetItemByNum(i));
                    singleVertexPathNew->GetCurrReadList()->AddSetOfReadList(setOfConToVertexes.GetItemByNum(i)->GetReadList());


                    pathMetaNew->_lastVertex = setOfConToVertexes.GetItemByNum(i);
                    pathMetaNew->_path = singleVertexPathNew;
                    pathMetaNew->_weight = -1;

                    currPathes->AddToSet(pathMetaNew);

                    //currPathes->AddToSet(considerPathesNew.GetItemByNum(i));

                }

            }
            else
            {
                currPathes->Clear();
                for(int i = 0;i < considerPathesNew.GetSizeOfSet();i++)
                {
                    considerPathesNew.GetItemByNum(i)->_path->AddStartedReadsToCurrReadList();
                    currPathes->AddToSet(considerPathesNew.GetItemByNum(i));

                }
            }


            //debugFile << "CurrPathes at iteration i =" << countIteration<< "\n";
           /* for(int i =0;i<currPathes->GetSizeOfSet();i++)
            {
                currPathes->GetItemByNum(i)->_path->PrintPath(debugFile);
            }


            //debugFile << "ResultPathes at iteration i =" << countIteration<< "\n";
            for(int i =0;i<resultPathes->GetSizeOfSet();i++)
            {
                resultPathes->GetItemByNum(i)->PrintPath(debugFile);
            }*/


            if(currPathes->GetSizeOfSet() > numOfParalogs)
            {
                //debugFile << "error - number of current pathes above 4\n";

                break;
            }



            if(countIteration == -1)
            {
                //debugFile << "End at iteration-" << countIteration<< "\n";
                break;
            }

            countIteration++;




        }


        for(int i = 0; i < currPathes->GetSizeOfSet();i++)
        {
			currPathes->GetItemByNum(i)->_path->AddAllCurrReadsToFullReadList();
			debugFile << "Added to resultPathes path - " << currPathes->GetItemByNum(i)->_path->GetName() << std::endl;
            debugFile << "resultPathes FullReadsSet - " << currPathes->GetItemByNum(i)->_path->GetFullReadList()->GetReadListRef()->GetSizeOfSet() << std::endl;

			resultPathes->AddToSet(currPathes->GetItemByNum(i)->_path);
		}

        //debugFile << "Number of result pathes - " << resultPathes->GetSizeOfSet() << "\n";

        //debugFile << "Result pathes:\n";

        /*for(int i = 0;i < resultPathes->GetSizeOfSet();i++ )
        {
            resultPathes->GetItemByNum(i)->PrintPath(debugFile);
        }*/


    }
    catch(exception exc)
    {

        //debugFile << "Exception happens" << "\n";
    }

//        for(int i = 0; i < currPathes->GetSizeOfSet(); i++)
//        {
//            delete currPathes->GetItemByNum(i);
//        }

    //return;
//        for(int i = 0; i < pathesToFree->GetSizeOfSet();i++)
//        {
//            Path *tempPtr = pathesToFree->GetItemByNum(i);
//             debugFile << tempPtr << "\n";
//           delete tempPtr;
//        }

        for(int i = 0; i < pathesMetaToFree->GetSizeOfSet();i++)
        {
            PathWithMetaData *tempPtrMeta = pathesMetaToFree->GetItemByNum(i);
             //debugFile << tempPtrMeta << "\n";
             delete tempPtrMeta;
        }








fileRangeTest.close();


    delete currPathes;

    delete pathesMetaToFree;


}


SetOfPathes SimplifyGraph::FindPathes()
{
    SetOfPathes pathes;
    for(int i = 0;i<_simplifyFirstVertexies.GetSizeOfSet();i++)
    {
        Path currPath;




        currPath.AddVertex(_simplifyFirstVertexies.GetItemByNum(i));


        ContinuePath(&currPath,pathes,_simplifyFirstVertexies.GetItemByNum(i));

        pathes.AddToSet(currPath);


    }

    return pathes;




}

void SimplifyGraph::CountStartEndContinueSVertexLists()
{
    for(int i = 0; i < _simplifyVertexies.GetSizeOfSet();i++)
    {
        _simplifyVertexies.GetItemByNum(i)->CountStartEndContinueLists();
        //return;
    }
}
