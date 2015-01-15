#ifndef USEDSCAFFS_H
#define USEDSCAFFS_H

#include "considerscaffold.h"

class UsedScaffs
{
private:
    SetOfRef<ConsiderScaffold> _consScaffs;
public:
    UsedScaffs();

    void AddPath(ConsiderScaffold *consScaff)
    {
        if(!ExistPath((consScaff)))
        {
            _consScaffs.AddToSet(consScaff);
        }
    }

    int ExistPath(ConsiderScaffold *consScaff)
    {
        //return 0;
        for(int i=0;i<_consScaffs.GetSizeOfSet();i++)
        {
            ConsiderScaffold *currConsScaff = _consScaffs.GetItemByNum(i);

            if(consScaff == currConsScaff)
            {
                return 1;
            }

        }
        return 0;
    }
};

#endif // USEDSCAFFS_H
