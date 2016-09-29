#include <uC++.h>
#include <iostream>

using namespace std;

#define AUTOMATIC_SIGNAL uCondition myCond;
#define WAITUNTIL( pred, before, after ) before;  while (pred == false) myCond.wait(); after;
#define RETURN( expr ) myCond.signal(); return expr;


//AUTOMATIC_SIGNAL defines the condition I use
//WAIT UNTIL executes before, then loops on the predicate, waiting as long as it's false, then executes after
//RETURN signals on the condition, at which point WAITUNTIL rechecks the predicate and possibly lets the next task go
