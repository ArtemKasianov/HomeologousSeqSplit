#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "Path.h"

class Graph
{
    SetOfRef<Vertex> _vertexies;
    SetOfRef<Vertex> _firstVertexies;

public:
    Graph()
    {

    }

    void ClearGraph();


    ~Graph()
    {
        ClearGraph();
    }

    void AddVertex(Vertex *ver)
    {
        _vertexies.AddToSet(ver);
    }

    void AddFirstVertex(Vertex *ver)
    {
        _firstVertexies.AddToSet(ver);
    }


    void FillFirstVertexies();

    Vertex* GetVertexByIndex(int index)
    {
        return _vertexies.GetItemByNum(index);
    }

    Vertex* GetFirstVertexByIndex(int index)
    {
        return _firstVertexies.GetItemByNum(index);
    }

    int GetFirstVertexiesSize()
    {
        return _firstVertexies.GetSizeOfSet();
    }

    void PrintGraph(fstream &graphFile);

    int GetVertexSetSize()
    {
        return _vertexies.GetSizeOfSet();
    }

    void LoadFromGraphViz(std::string graphVizFile);


};



struct PathWithMetaData
{
    SimplifyVertex *_lastVertex;
    Path *_path;
    int _weight;
    int _eWeight;
    int _sWeight;
    int _pWeight;

};


typedef __gnu_cxx::hash_map<std::string,SimplifyVertex*,string_hash_compare> HashStringSimplifyVertex;


class SimplifyGraph
{
  SetOfRef<SimplifyVertex> _simplifyVertexies;
  SetOfRef<SimplifyVertex> _simplifyFirstVertexies;
  HashStringInt _addedVertexies;
  HashStringSimplifyVertex _mapVertexToSimplifyVertex;
  void ContinuePath(Path *pathToContinue,SetOfPathes &pathes, SimplifyVertex *currVertex);

public:
  SimplifyGraph()
  {

  }

  void AddVertex(SimplifyVertex *ver)
  {
	_simplifyVertexies.AddToSet(ver);
  }

  void AddFirstVertex(SimplifyVertex *ver)
  {
	  _simplifyFirstVertexies.AddToSet(ver);
  }

  void FindFirstVertex();

  void ClearGraph();

  void CreateSimplifyVertex(Vertex* verToAdd,SimplifyVertex *simplifyVertex);

  void CreateSimplifyVertex_simple(Vertex* verToAdd,SimplifyVertex *simplifyVertex);

  SimplifyVertex* GetSimplifyVertexByIndex(int i)
  {
	  return _simplifyVertexies.GetItemByNum(i);
  }

  void FillSimplifyVertex(SimplifyVertex *simplifyVertex, Vertex *startVertex);

  void EaseGraph(Graph *graphToSimplify);

  void EaseGraph_simple(Graph *graphToSimplify);

  void PrintGraph(fstream &graphFile);

  int GetVertexSetSize()
  {
      return _simplifyVertexies.GetSizeOfSet();
  }

  ~SimplifyGraph()
  {
      ClearGraph();
  }

  SetOfPathes FindPathes();

  void GetAndPrintPath_Debug(fstream &debugFile);
  void GetAndPrintPath_Debug(fstream &debugFile, int numOfParalogs,SetOfRef<Path> *resultPathes,SetOfRef<Path> *pathesToFree);

  void CountStartEndContinueSVertexLists();




};


#endif // GRAPH_H
