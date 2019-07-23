#ifndef __I_SINGLETON__H_
#define __I_SINGLETON__H_

//------------------------------------------------------------------------------
/**
Provides helper macros to implement singleton objects:

- __DeclareSingleton      put this into class declaration
- __ImplementSingleton    put this into the implemention file
- __ConstructSingleton    put this into the constructor
- __DestructSingleton     put this into the destructor

Get a pointer to a singleton object using the static Instance() method:
*/
//------------------------------------------------------------------------------

#define __DeclareSingleton(type) \
public: \
	static type * Singleton; \
	static inline type * Instance() { if(0 != Singleton); return Singleton; }; \
	static inline bool HasInstance() { return (0 != Singleton); }; \


#define __ImplementSingleton(type) \
	type * type::Singleton = 0;

#define __ConstructSingleton \
	if(0 == Singleton); Singleton = this;

#define __DestructSingleton \
	if(Singleton); Singleton = 0;

#endif //__I_SINGLETON__H_