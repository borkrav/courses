// File extstrset3.h

// Inherit from setstr class and add comparisons such as <
#ifndef EXTSTRSET_H
#define EXTSTRSET_H

#include <string>
#include "strset3.h"

class extStrSet : public strSet
{
public:
    extStrSet operator == (const extStrSet& rtSide);  // Equal
    extStrSet operator <  (const extStrSet& rtSide);  // Strict subset
    extStrSet operator >  (const extStrSet& rtSide);  // Strict superset
    // Leave off other comparisons: != <= >=

    extStrSet ( );
    extStrSet (std::string s);

    friend std::ostream& operator <<
        (std::ostream & os, const extStrSet & ess);
};

std::ostream& operator <<
    (std::ostream & os, const extStrSet & ess);

// ===============Converting strSet to extStrSet==============
// Coerce base class strSet to derived class extStrSet
// This is a "downcast", so it is potentially dangerous.
// The type cheat is (extStrSet*), ie, coerce to  pointer to
//     derived type extStrSet
// This will be safe because the derived class has no data

inline extStrSet& ss2extss (const strSet& ss)  // Downcast
   { return *(extStrSet*)&ss ; }

#endif
