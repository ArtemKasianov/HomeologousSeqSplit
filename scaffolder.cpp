#include "scaffolder.h"
#include <iostream>
#include <fstream>

Scaffolder::Scaffolder()
{
}

int CheckPathesInclusion(Path *pathToCheck,SetOfRef<Path> usedPathes)
{
    for(int i = 0;i<usedPathes.GetSizeOfSet();i++)
    {
        if(pathToCheck == usedPathes.GetItemByNum(i))
        {
            return 1;
        }
    }
    return 0;
}

void Scaffolder::Scaffolding(FilteredPathesSet *filterPathes, int maxInsertSize)
{

    SetOfRef<Path> usedPathes;

    for(int i = 0;i<filterPathes->GetPathesPackSetSize();i++)
    {
        PathesPack *currPathPack = filterPathes->GetPathesPackByIndex(i);
        PathesPack *currPathPackTemp = currPathPack;

        int nextIndexPack = 0;
        int nextIndexPath = 0;

        for(int j = 0; j<currPathPack->GetNumberOfPathes();j++)
        {
            Path *currStartPath = currPathPack->GetPathByIndex(j);
            nextIndexPack = i;
            nextIndexPath = 0;
            Scaffold *currScaffold;
            if(CheckPathesInclusion(currStartPath,usedPathes))
            {
                continue;
            }
            usedPathes.AddToSet(currStartPath);
            currScaffold->AddPath(currStartPath);
            nextIndexPack++;
            while(nextIndexPack < filterPathes->GetPathesPackSetSize())
            {


                PathesPack *nextPathPack = filterPathes->GetPathesPackByIndex(nextIndexPack);



                if(nextPathPack->GetStartPos() - currPathPackTemp->GetEndPos() > maxInsertSize)
                {
                    break;
                }

                nextIndexPath = 0;

                int countPathesCompared = 0;
                int sizeOfNextPack = nextPathPack->GetNumberOfPathes();
                int *compareWeightSet = new int[sizeOfNextPack];

                int maxConn = -1;
                int maxIndex = -1;

                while(nextIndexPath < nextPathPack->GetNumberOfPathes())
                {
                    Path *nextPath = nextPathPack->GetPathByIndex(nextIndexPath);
                    if(CheckPathesInclusion(nextPath,usedPathes))
                    {
                        nextIndexPath++;
                        continue;
                    }



                    int peConn = currStartPath->CheckPathConnectivityByPEReads(nextPath);
                    for(int z = 0; z < currScaffold->GetSizeOfPathesSet();z++)
                    {
                        Path *zPath = currScaffold->GetPathByIndex(z);

                        peConn += zPath->CheckPathConnectivityByPEReads(nextPath);
                    }

                    if(peConn > maxConn)
                    {
                        maxConn = peConn;
                        maxIndex = nextIndexPath;
                    }
                    countPathesCompared++;
                    nextIndexPath++;
                }

                if(maxConn > 0)
                {
                    currScaffold->AddPath(nextPathPack->GetPathByIndex(maxIndex));
                    usedPathes.AddToSet(nextPathPack->GetPathByIndex(maxIndex));
                    currStartPath = nextPathPack->GetPathByIndex(maxIndex);
                    currPathPackTemp = nextPathPack;
                }
                else
                {

                }

                nextIndexPack++;
            }










        }
    }


}

void Scaffolder::PrintScaffoldsForDebug(fstream &scaffFile)
{
    for(int i = 0;i<_scaffolds.GetSizeOfSet();i++)
    {
        _scaffolds.GetItemByNum(i)->PrintScaffold(scaffFile);
    }
}

void Scaffolder::Clear()
{
    for(int i = 0;i < _scaffolds.GetSizeOfSet();i++)
    {
        Scaffold *currScaffold = _scaffolds.GetItemByNum(i);

        if(currScaffold != NULL)
        {
            delete currScaffold;
        }

    }

    for(int i = 0;i < _consScaffolds.GetSizeOfSet();i++)
    {
        ConsiderScaffold *currConsScaffold = _consScaffolds.GetItemByNum(i);

        if(currConsScaffold != NULL)
        {
            currConsScaffold->Clear();
            delete currConsScaffold;
        }

    }
}



void Scaffolder::Scaffolding(SetOfRef<Path> *resPath, int maxInsertSize)
{

    cout << "Scaffolding \n";
    fstream fileStreamDebugScaff("debugerScaffold.txt",fstream::out);
    SetOfRef<ConsiderPath> resConsPath;
//fileStreamDebugScaff << resPath->GetSizeOfSet() << "\n";
    for(int i=0;i<resPath->GetSizeOfSet();i++)
    {
        ConsiderPath *consPathTemp = new ConsiderPath(resPath->GetItemByNum(i));

        resConsPath.AddToSet(consPathTemp);
    }
//    fileStreamDebugScaff << "Consider path created" << "\n";
//    fileStreamDebugScaff << resConsPath.GetSizeOfSet() << "\n";


    UsedPathes objUsedPathes;
    int countStartPathes = 0;
    cout << "Start scaffolding\n";
    for(int i = 0;i < resConsPath.GetSizeOfSet();i++)
    {
        ConsiderPath *objConsiderPath=resConsPath.GetItemByNum(i);


       if(objUsedPathes.ExistPath(objConsiderPath))
       {
            continue;
       }

       //cout <<"considerPath - " << objConsiderPath->GetPath()->GetName() << "\n";
       countStartPathes++;
       objUsedPathes.AddPath(objConsiderPath);


        ConsiderScaffold *currConsScaff = new ConsiderScaffold();



        currConsScaff->AddPath(objConsiderPath);

        //cout <<"Number of pathes - " << currConsScaff->GetSizeOfPathesSet() << "\n";

        if(objConsiderPath == NULL)
        {
            //cout << "objConsiderPath after addPath = NULL\n";
        }


        //cout << "before Count\n";
        if(currConsScaff->GetPathByNum(0) == NULL)
        {
            //cout << "NULL\n";
        }
        else
        {
            //cout << "not NULL\n";
        }

        currConsScaff->CountStartAndEnd();

//        cout << "startCurrConsScaff - " << currConsScaff->GetStartPos()<< "\n";
//        cout << "endCurrConsScaff - " << currConsScaff->GetEndPos()<< "\n";

        if(objConsiderPath == NULL)
        {
//            cout << "objConsiderPath = NULL\n";
        }

//        cout << "before constructor\n";
        if(currConsScaff->GetPathByNum(0) == NULL)
        {
//            cout << "NULL\n";
        }
        else
        {
//            cout << "not NULL\n";
        }

        int lastCurrConsScaffSize = 0;
        fileStreamDebugScaff << "ConsiderPath i=" << i <<"\n";
        while((currConsScaff->GetSizeOfPathesSet() - lastCurrConsScaffSize) != 0)
	{
       lastCurrConsScaffSize  = currConsScaff->GetSizeOfPathesSet();  
	AlternativePathComparer objPathComparer(currConsScaff);
      
        
         for(int j = 0;j<resConsPath.GetSizeOfSet();j++)
         {
            ConsiderPath *currConsPath = resConsPath.GetItemByNum(j);

            /*if(objUsedPathes.ExistPath(currConsPath))
            {
                continue;
            }*/

            objPathComparer.CheckPath(currConsPath,maxInsertSize);




        }

 
        currConsScaff = objPathComparer.GetResultScaff(objUsedPathes,fileStreamDebugScaff);
	
       }

    	 

        _consScaffolds.AddToSet(currConsScaff);
        //cout << "_consScaffolds-" << _consScaffolds.GetSizeOfSet() << "\n";
        fileStreamDebugScaff << "currConsScaff->GetSizeOfPathesSet() - " << currConsScaff->GetSizeOfPathesSet() << "\n";
        fileStreamDebugScaff << "lastCurrConsScaffSize - " << lastCurrConsScaffSize << "\n";
    }

    //cout <<"CountStartPathes - " <<countStartPathes << "\n";
    cout <<"End scaffolding\n";
    cout << "*******************************************\n";
    fileStreamDebugScaff.close();



}

int Scaffolder::InnerScaffolding(int maxInsertSize)
{
    UsedScaffs usedScaffs;
    SetOfRef<ConsiderScaffold> resultScaffs;



    for(int i = 0; i < _consScaffolds.GetSizeOfSet();i++)
    {
        ConsiderScaffold *currConsScaff = _consScaffolds.GetItemByNum(i);

        if(usedScaffs.ExistPath(currConsScaff)) continue;

        bool isStop = false;

        while(!isStop)
        {

            
	     currConsScaff->CountStartAndEnd();
	     
	     ConsiderScaffold *leftConsScaff = NULL;
            ConsiderScaffold *rightConsScaff = NULL;
            long int leftWeight = 0;
            long int rightWeight = 0;



            for(int j = 0; j < _consScaffolds.GetSizeOfSet();j++)
            {
                if(i == j) continue;

                ConsiderScaffold *nextConsScaff = _consScaffolds.GetItemByNum(j);

                if(usedScaffs.ExistPath(nextConsScaff)) continue;

                if((currConsScaff->GetStartPos() <= nextConsScaff->GetStartPos()) && (nextConsScaff->GetStartPos() <= currConsScaff->GetEndPos()))
                {
                    continue;
                }

                if(nextConsScaff->GetEndPos() < currConsScaff->GetStartPos())
                {
                    if(leftConsScaff != NULL)
                    {
                        if(nextConsScaff->GetEndPos() <= leftConsScaff->GetEndPos())
                        {
                            continue;
                        }
                    }

                    long int weight = currConsScaff->CheckConnectionBeetweenScaffolds(nextConsScaff);

                    if(weight < minWeightToScaffoldByPE) continue;

                    if(weight > leftWeight)
                    {
                        leftConsScaff = nextConsScaff;
                        leftWeight = weight;
                    }
                    else
                    {
                       if(weight == leftWeight)
                       {
                            leftConsScaff = NULL;
                       }
                    }
                }
                else
                {
                    if(nextConsScaff->GetStartPos() > currConsScaff->GetEndPos())
                    {
                        if(rightConsScaff != NULL)
                        {
                            if(nextConsScaff->GetEndPos() >= rightConsScaff->GetEndPos())
                            {
                                continue;
                            }
                        }

                        long int weight = currConsScaff->CheckConnectionBeetweenScaffolds(nextConsScaff);
                        if(weight < minWeightToScaffoldByPE) continue;

                        if(weight > rightWeight)
                        {
                            rightConsScaff = nextConsScaff;
                            rightWeight = weight;
                        }
                        else
                        {
                           if(weight == rightWeight)
                           {
                           	   rightConsScaff = NULL;
                           }
                        }
                    }
                }


            }


            if((leftConsScaff == NULL) && (rightConsScaff == NULL))
            {
                isStop = true;
                continue;
            }

            if(leftConsScaff != NULL)
            {
                for(int k = 0; k < leftConsScaff->GetSizeOfPathesSet();k++)
                {
                    currConsScaff->AddPath(leftConsScaff->GetPathByNum(k));
                }

                usedScaffs.AddPath(leftConsScaff);
            }

            if(rightConsScaff != NULL)
            {
                for(int k = 0; k < rightConsScaff->GetSizeOfPathesSet();k++)
                {
                    currConsScaff->AddPath(rightConsScaff->GetPathByNum(k));
                }

                usedScaffs.AddPath(rightConsScaff);
            }


        }

        resultScaffs.AddToSet(currConsScaff);
        //usedScaffs.AddPath(currConsScaff);
    }

    _consScaffolds = resultScaffs;

    return resultScaffs.GetSizeOfSet();

}

void Scaffolder::PackScaffolds()
{
    int lastScaffoldSize = 0;

    cout << "PackScaffs start\n";

    int iterNum = 0; 
         int indexOfRemoved = -1;
    while(lastScaffoldSize != _consScaffolds.GetSizeOfSet())
    {
        iterNum++;
       // cout << "IterationNumber - " << iterNum << "\n";
     //cout << "_consScaffolds.GetSizeOfSet()-" << _consScaffolds.GetSizeOfSet() << "\n";

        lastScaffoldSize = _consScaffolds.GetSizeOfSet();

        SetOfRef<ConsiderScaffold> newConsScaff;

        bool isFound = false;
        indexOfRemoved = -1;
        for(int i = 0;i < (_consScaffolds.GetSizeOfSet());i++)
        {
            ConsiderScaffold *consScaffA = _consScaffolds.GetItemByNum(i);


        /*    if(indexOfRemoved != i)
            {
                newConsScaff.AddToSet(consScaffA);
            }*/

            if(isFound)
            {
                continue;
            }

            for(int j = 0;j < _consScaffolds.GetSizeOfSet();j++)
            {


                if(i == j)
                {
                    continue;
                }
                ConsiderScaffold *consScaffB = _consScaffolds.GetItemByNum(j);

                if(consScaffA->MergeScaffold(consScaffB))
                {
                    isFound = true;
                    indexOfRemoved = j;
                    break;
                }
            }






        }


        for(int i = 0; i < _consScaffolds.GetSizeOfSet();i++)
        {
            ConsiderScaffold *consScaffA = _consScaffolds.GetItemByNum(i);

            if(indexOfRemoved != i)
            {
                newConsScaff.AddToSet(consScaffA);
            }





        }



	
       /*if(indexOfRemoved != (_consScaffolds.GetSizeOfSet()-1))
	{
	 ConsiderScaffold *consScaffA = _consScaffolds.GetItemByNum(_consScaffolds.GetSizeOfSet()-1);
	newConsScaff.AddToSet(consScaffA);	  
    }*/



        _consScaffolds = newConsScaff;

       // cout << "After merging\n";
       // PrintScaffoldsToSVertex();
       // cout << "**************\n";




    }

//    cout << "PackScaffs end\n";

}


void Scaffolder::PrintScaffoldsToSVertex()
{
    for(int i = 0; i < _consScaffolds.GetSizeOfSet();i++)
    {
        ConsiderScaffold *currScaff = _consScaffolds.GetItemByNum(i);

        for(int j = 0; j < currScaff->GetSizeOfPathesSet();j++)
        {
            Path *currPath = currScaff->GetPathByNum(j)->GetPath();

            for(int k = 0; k < currPath->GetSizeOfSimplifyVertexSet();k++)
            {
                SimplifyVertex *currSVertex = currPath->GetSimplifyVertexByNum(k);


                cout << currSVertex->GetName() << "_";

            }
        }

        cout << "\n";
    }





}


bool ExistInIntSet(SetOf<int> &setInt, int checkVal)
{
    for(int i = 0; i < setInt.GetSizeOfSet();i++)
    {
        if(*(setInt.GetRefItemByNum(i)) == checkVal)
        {
            return true;
        }
    }

    return false;
}

void Scaffolder::SortSet()
{
    int maxVal = 0;
    int minVal = 0;

    SetOfRef<ConsiderScaffold> newConsiderScaff;

    SetOf<int> usedIndexies;

    for(int i = 0; i < _consScaffolds.GetSizeOfSet();i++)
    {
        if(_consScaffolds.GetItemByNum(i)->GetSizeOfPathesSet()> maxVal )
        {
            maxVal = _consScaffolds.GetItemByNum(i)->GetSizeOfPathesSet();
        }
    }

    int lowestVal = -1;
    int minValJ = -1;
    for(int i = 0; i < _consScaffolds.GetSizeOfSet();i++)
    {
        minVal = 0;
        for(int j = 0;j<_consScaffolds.GetSizeOfSet();j++)
        {
            if((_consScaffolds.GetItemByNum(j)->GetSizeOfPathesSet() > minVal) && !ExistInIntSet(usedIndexies,j))
            {
                minVal = _consScaffolds.GetItemByNum(j)->GetSizeOfPathesSet();
                minValJ = j;

            }
        }

        lowestVal = minVal;
        newConsiderScaff.AddToSet(_consScaffolds.GetItemByNum(minValJ));
        usedIndexies.AddToSet(minValJ);

    }

    _consScaffolds = newConsiderScaff;
}


bool Scaffolder::CheckEqualitySetOfScaffs()
{
    cout << "EqualityCheck\n";
    for(int i = 0; i < _consScaffolds.GetSizeOfSet();i++)
    {
        for(int j = 0; j < _consScaffolds.GetSizeOfSet();j++)
        {
            //cout << i << " " << j;

            if(_consScaffolds.GetItemByNum(i)->CheckEqualityOfScaffold(_consScaffolds.GetItemByNum(j),i,j))
            {
                cout << " 1 \n";
            }
            else
            {
                //cout << " 0 \n";
            }
        }
    }
}
