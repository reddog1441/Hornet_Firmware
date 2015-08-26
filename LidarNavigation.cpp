#pragma once

#include "LidarNavigation.h"


LidarNavigation::LidarNavigation(HornetManager *theHornetManager, Error *theError)
{
	_e = theError;
	_hornetManager = theHornetManager;
}

LidarNavigation::LidarNavigation()
{
	Point* headPoint = new Point(HEAD);
	head = new PointNode(*headPoint);
	Point* tailPoint = new Point(TAIL);
	PointNode* tail = new PointNode(*tailPoint);
	head->insertAfter(*tail);
	for (int i = 0; i < L_POINTS_IN_PATTERN; i++)
	{
		Point* point = new Point(NULLPOINT);
		PointNode* node = new PointNode(*point);
		head->insertAfter(*node);
	}
}

void LidarNavigation::setupPoints(float angle, float distance)
{
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head);
	iter = iter.last();
	iter--;
	if ((*iter).getState() == DATA)
	{
		_setup = true;
		newLidarPoint(angle, distance); //call here so we don't lose a point
	}
	else
	{
		iter = iter.first();
		for (iter; (*iter).getState() != NULLPOINT; iter++)
		{
			//goes to the next NULLPOINT
		}
		(*iter).setPoint(angle, distance, DATA);
	}
}

void LidarNavigation::processLidarData(float angle, float distance)
{
	if (!_setup) 
	{
		setupPoints(angle, distance);
	}
	else
	{
		newLidarPoint(angle, distance);
	}
}

void LidarNavigation::newLidarPoint(float angle, float distance)
{
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head);
	iter++;
	PointNode* node = iter.getNode();
	iter.getNode()->dropNode();
	iter = iter.last();
	iter.getNode()->insertBefore(*node);
	iter = iter.last();
	iter--;
	(*iter).setPoint(angle, distance);
}


PointNode* LidarNavigation::getHead()
{
	return head;
}

bool LidarNavigation::isPattern()
{
	//if all your points drawn into lines have an average angle offset less than or equal to
	//the L_LINE_TO_LINE_OFFSET then you can return true otherwise return false
	float angleOfBestFit = 0;
	float nextAngle;
	float x1;
	float x2;
	float y1;
	float y2;
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head);
	iter++;
	for (int i = 1; i < L_POINTS_IN_PATTERN; i++)
	{
		x1 = (*iter).getX();
		y1 = (*iter).getY();
		iter++;
		x2 = (*iter).getX();
		y2 = (*iter).getY();

		nextAngle = atan((y2 - y1) / (x2 - x1)) * 180 / PI;
		angleOfBestFit = ((angleOfBestFit * (i-1)) + nextAngle) / i;
		Serial.println(nextAngle);
		
	}Serial.println(angleOfBestFit);
	return true;
}

bool LidarNavigation::isFeature()
{
	//if you have 2 patterns at 90 degree
	L_PATTERNS_IN_CORNER_FEATURE;
	return true;
}

bool LidarNavigation::isAnchor()
{
	//if you have have a recurring feature over..
	L_FEATURE_RECURRENCE_IN_ANCHOR;
	return true;
}


int LidarNavigation::getSize()
{
	int count = 0;
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head); //head
	iter++; //first data member
	DoublyLinkedNodeIterator<Point> iterEnd = DoublyLinkedNodeIterator<Point>(*head);
	iterEnd = iterEnd.last(); //tail
	for (count; iter != iterEnd; count++)
	{
		iter++;
	}
	return count;
}

/*void LidarNavigation::newLidarPoint(float angle, float distance)
{
	// add point to a node at the end of the linked nodes
	Point* point = new Point(angle, distance);
	PointNode* node = new PointNode(*point);
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head);
	iter = iter.last();
	iter.getNode()->insertBefore(*node);
}

void LidarNavigation::processLidarData(float angle, float distance)
{
	if (getSize() >= L_POINTS_IN_PATTERN)
	{
		removePoint();
	}
	newLidarPoint(angle, distance);

	if (getSize() == 10) //you have enough to start looks for patterns/features/anchors
	{
		if (isPattern())
		{
			//copy DoublyLinkedNodes and assign type as Pattern
		}
		if (isFeature())
		{

		}
		if (isAnchor())
		{

		}
	}
}

LidarNavigation::LidarNavigation()
{
Point* headPoint = new Point(2000, 10000);
head = new PointNode(*headPoint);
Point* tailPoint = new Point(10000, 2000);
PointNode* tail = new PointNode(*tailPoint);
head->insertAfter(*tail);
}

void LidarNavigation::removePoint()
{
	// delete point and node at the start of the linked nodes
	// should check if there is actually data to delete so you don't accidentally
	// delete head and tail, however this function is only called under certain condition
	// therefore another check will be a waste of time
	DoublyLinkedNodeIterator<Point> iter = DoublyLinkedNodeIterator<Point>(*head);
	iter++;
	const PointNode* node = iter.getNode(); //get a reference to the Node we are deleting
	const Point* point = &(*iter); //get a reference to the Point we are deleting
	iter.getNode()->dropNode();
	delete node;
	delete point;
}*/

void LidarNavigation::EOSweep(float pitch, float roll, float yaw)
{
	// compare sweeps, look for ancors
}
