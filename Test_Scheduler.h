#pragma once

#if BUILD_TYPE == FOR_TEST

#include <ArduinoUnit.h>
#include "Scheduler.h"
#include "Runnable.h"

class TestRunnable :public Runnable
{
public:
	int runCount;
	int startCount;
	bool startMode;

	TestRunnable()
	{
		runCount = 0;
		startCount = 0;
		startMode = true;
	}

	bool start()
	{
		startCount++;
		return startMode;
	}

	void run()
	{
		runCount++;
	}
};

test(Scheduler_Setup)
{
	Error e;

	Scheduler toTest(&e);

	// test that it starts empty
	assertFalse(e.isError());
	assertFalse(toTest.finish());
	assertFalse(toTest.startAll());
	assertTrue(e.isError());
	e.getError();
	assertFalse(e.isError());
}

test(Scheduler_ValidPopulate)
{
	Error e;

	Scheduler toTest(&e);
	TestRunnable tests[C_SCHEDULER_THREAD_NUM];

	// test that everything starts corectly
	assertFalse(e.isError());
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		assertEqual(tests[i].runCount, 0);
		assertEqual(tests[i].startCount, 0);
	}

	// test that you can add to the scedulare corectly
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		toTest.addRunable(i, &tests[i]);
		assertEqual(tests[i].runCount, 0);
		assertEqual(tests[i].startCount, 0);
	}
	assertFalse(e.isError());

	// test that you can finalize and start a full scedualr
	assertTrue(toTest.finish());
	assertTrue(toTest.startAll());
	assertFalse(e.isError());
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		assertEqual(tests[i].runCount, 0);
		assertEqual(tests[i].startCount, 1);
	}
	assertFalse(e.isError());
}

test(Scheduler_BadPopulate)
{
	Error e;

	Scheduler toTest(&e);
	TestRunnable tests[C_SCHEDULER_THREAD_NUM];

	// test that everything starts corectly
	assertFalse(e.isError());
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		assertEqual(tests[i].runCount, 0);
		assertEqual(tests[i].startCount, 0);
	}

	// test that you can add to the scedulare corectly and attempting to add twice throws an error
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		toTest.addRunable(i, &tests[i]);
		assertFalse(e.isError());
		toTest.addRunable(i, &tests[i]);
		assertTrue(e.isError());
		e.getError();
		assertFalse(e.isError());
		assertEqual(tests[i].runCount, 0);
		assertEqual(tests[i].startCount, 0);
	}
	assertFalse(e.isError());

	// test that you cant add invalid scedualres (over)
	for (int i = C_SCHEDULER_THREAD_NUM; i < C_SCHEDULER_THREAD_NUM + 10; i++)
	{
		toTest.addRunable(i, &tests[0]);
		assertTrue(e.isError());
		e.getError();
		assertFalse(e.isError());
	}

	// test that you cant add invalid scedualres (over)
	for (int i = -1; i >-10; i--)
	{
		toTest.addRunable(i, &tests[0]);
		assertTrue(e.isError());
		e.getError();
		assertFalse(e.isError());
	}

	// test that you can finalize and start a full scedualr
	assertTrue(toTest.finish());
	assertTrue(toTest.startAll());
	assertFalse(e.isError());
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		assertEqual(tests[i].runCount, 0);
		assertEqual(tests[i].startCount, 1);
	}
	assertFalse(e.isError());
}

int factorial(int x, int result = 1) {
	if (x == 1) return result; else return factorial(x - 1, x * result);
}

test(Scheduler_Run)
{
	Error e;

	Scheduler toTest(&e);
	TestRunnable tests[C_SCHEDULER_THREAD_NUM];

	// test that everything starts corectly
	assertFalse(e.isError());
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		assertEqual(tests[i].runCount, 0);
		assertEqual(tests[i].startCount, 0);
	}

	// test that you can add to the scedulare corectly and attempting to add twice throws an error
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		toTest.addRunable(i, &tests[i]);
		assertFalse(e.isError());
		assertEqual(tests[i].runCount, 0);
		assertEqual(tests[i].startCount, 0);
	}
	assertFalse(e.isError());

	// test that you can finalize and start a full scedualr
	assertTrue(toTest.finish());
	assertTrue(toTest.startAll());
	assertFalse(e.isError());
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		assertEqual(tests[i].runCount, 0);
		assertEqual(tests[i].startCount, 1);
	}
	assertFalse(e.isError());

	// check that nothing runs by default
	for (int i = 0; i < 100; i++)
	{
		toTest.run();
	}
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		assertEqual(tests[i].runCount, 0);
	}

	// check that everything runs in parelr if on the same 
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		toTest.setPriority(i, 1);
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < C_SCHEDULER_THREAD_NUM; j++)
		{
			assertEqual(tests[j].runCount, i);
		}
		toTest.run();
	}

	// check that things can run at difrent priorities
	//@TODO

	
}

#endif;
