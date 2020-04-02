#ifndef _H_TYPEDEF_
#define _H_TYPEDEF_
#include "boost/shared_ptr.hpp"
#include "boost/thread.hpp"
typedef unsigned char byte;
typedef boost::shared_mutex RWmutex;
typedef boost::shared_lock<RWmutex> readLock;
typedef boost::unique_lock<RWmutex> writeLock;

#define RELEASE_MSG(...) ;
typedef enum _LOGTYPE_
{
	LOGDEBUG,
	LOGREALESE,
}LOGTYPE;

#endif
