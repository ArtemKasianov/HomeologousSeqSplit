#ifndef SCAFFOLDER_H
#define SCAFFOLDER_H
#include "scaffold.h"
#include "considerscaffold.h"
#include "usedpathes.h"
#include "alternativepathcomparer.h"
#include "usedscaffs.h"


class Scaffolder
{
private:
    SetOfRef<Scaffold> _scaffolds;
    SetOfRef<ConsiderScaffold> _consScaffolds;

public:
    Scaffolder();

    void Scaffolding(FilteredPathesSet *filterPathes, int maxInsertSize);

    void Scaffolding(SetOfRef<Path> *resPath, int maxInsertSize);

    void PrintScaffoldsForDebug(fstream &scaffFile);
    void PrintScaffoldsToFasta(string fasta_fn, fstream &debugFile);

    int GetSizeOfScaffoldSet()
    {
        return _scaffolds.GetSizeOfSet();
    }

    Scaffold* GetScaffoldByIndex(int index)
    {
        return _scaffolds.GetItemByNum(index);
    }

    int GetSizeOfConsScaffoldSet()
    {
        return _consScaffolds.GetSizeOfSet();
    }

    ConsiderScaffold* GetConsScaffoldByIndex(int index)
    {
        return _consScaffolds.GetItemByNum(index);
    }
    void Clear();
    int InnerScaffolding(int maxInsertSize);

    void PackScaffolds();

    void PrintScaffoldsToSVertex();

    void SortSet();

    bool CheckEqualitySetOfScaffs();



};

#endif // SCAFFOLDER_H
