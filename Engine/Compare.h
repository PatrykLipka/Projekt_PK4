#pragma once
template<typename T>
bool compare_distance(T & obj1, T& obj2)
{
	if (obj1 && obj2)
		return obj1->distance < obj2->distance;

	return true;
}

template<typename T>
bool compare_distance2(T obj1,T obj2)
{
	if (obj1 && obj2)
		return obj1.distance < obj2.distance;

	return true;
}