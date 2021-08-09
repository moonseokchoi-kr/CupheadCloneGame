#pragma once

#include "pch.h"

#include "CEventManager.h"

class CObject;
class FSMAI;


void CreateObject(CObject* _object, GROUP_TYPE _group, Vec2 _pos, Vec2 _scale);
void CreateObject(CObject* _object, GROUP_TYPE _group);
void DeleteObject(CObject* _object);

void ChangeScene(SCENE_TYPE _type);

void ChangeAIState(FSMAI* ai, MON_STATE _nextState);

template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
		{
			delete _vec[i];
		}
	}
	_vec.clear();
}

template<typename T1, typename T2>
void Safe_Delete_Map(unordered_map<T1, T2>& _map)
{
	typename unordered_map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}
