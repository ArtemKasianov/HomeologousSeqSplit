#ifndef PRESCAFFOLD_H
#define PRESCAFFOLD_H
#include "Path.h"

class PreScaffold
{
public:
    SetOfRef<Path> _pathes;
    PreScaffold();

    void AddPath(Path *pathA);
    SetOfRef<Path> FindConnectedToThisPathPathes(Path *pathA);

};

#endif // PRESCAFFOLD_H
