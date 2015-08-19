#if BUILD_TYPE == FOR_TEST

#pragma once
#include <Arduino.h>

#define ASSERT_ISEQUAL_MESSAGE(x, y) __FILE__+(String)" Line:"+(String)__LINE__ +(String)('\n')+(String)"ASSERT_ISEQUAL Failed: "+(String)x + (String)"!="+(String)y
#define ASSERT_ISEQUAL(x, y) do {if(x!=y){return ASSERT_ISEQUAL_MESSAGE(x,y);} } while(0) 

#define ASSERT_NOTEQUAL_MESSAGE(x, y) __FILE__+(String)" Line:"+(String)__LINE__ +(String)('\n')+(String)"ASSERT_NOTEQUAL Failed: "+(String)x + (String)"=="+(String)y
#define ASSERT_NOTEQUAL(x, y) do {if(x==y){return ASSERT_NOTEQUAL_MESSAGE(x,y);} } while(0) 

class Test
{
public:

	virtual void setup() = 0;

	virtual String run() = 0;

	virtual void cleanUp() = 0;
};

#endif

