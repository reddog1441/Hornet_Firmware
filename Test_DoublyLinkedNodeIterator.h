#pragma once

#if BUILD_TYPE == FOR_TEST

#include "DoublyLinkedNode.h"
#include "DoublyLinkedNodeIterator.h"
#include "Point.h"
#include <iostream>
using namespace std;

test(DoublyLinkedNodeIterator_Setup)
{
	typedef DoublyLinkedNode<Point>::Node PointNode;

	Point p1 = Point(1, 100);
	Point p2 = Point(2, 200);
	Point p3 = Point(3, 300);
	Point p4 = Point(4, 400);
	Point p5 = Point(5, 500);
	Point p6 = Point(6, 600);


	PointNode n1(p1);
	PointNode n2(p2);
	PointNode n3(p3);
	PointNode n4(p4);
	PointNode n5(p5);
	PointNode n6(p6);

	DoublyLinkedNodeIterator<Point> iter(n1);

	iter--;


	cout << "Forward iteration I:" << endl;
	for (iter++; iter != iter.rightEnd(); iter++)
	{
		cout << *iter << endl;
	}
	//assert that it's at right end
	assertEquals(*iter->getAngle(), 6)
	assertEquals(*iter->getDistance(), 600)


	cout << "Backward iteration I:" << endl;
	for (iter--; iter != iter.leftEnd(); iter--)
	{
		cout << *iter << endl;
	}
	//assert that it's at left end
	assertEquals(*iter->getAngle(), 1)
	assertEquals(*iter->getDistance(), 100)


	cout << "Get Values of second node:" << endl;
	if (iter != iter.rightEnd())
	{
		iter++; //move one space left
	}
	//assert that it's at second node
	assertEquals(*iter->getAngle(), 2)
	assertEquals(*iter->getDistance(), 200)

}
#endif