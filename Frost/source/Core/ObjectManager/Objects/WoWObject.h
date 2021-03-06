/*	Frost Open-Source World of Warcraft Bot
	Copyright (C) 2013 https://code.google.com/p/ejt-projects/

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef _WOWOBJECT_H_
#define _WOWOBJECT_H_

#include <CMemory.h>

#include <Offsets\Constants.h>
#include <Offsets\Descriptors.h>
#include <Offsets\Offsets.h>

#include <CLocation.h>

using namespace std;

class WoWObject {
public:
	WoWObject(unsigned int objPtr);
	~WoWObject();

	int Type();
	unsigned long Guid();
	int Entry();

	virtual CLocation Location();

	template<class T>
	T GetDescriptorField(unsigned int field) {
		if(IsValid()) {
			field *= Descriptors::DescriptorMulti;
			unsigned int descPtr = Mem.Read<unsigned int>(ObjectPointer + Descriptors::DescriptorOffset);
		
			if(descPtr != 0) {
				T ret = (T)Mem.Read<T>(descPtr + field);
				return ret;
			} else {
				return (T)0;
			}
		} else {
			return (T)0;
		}
	};
	
	virtual bool WoWObject::IsValid() {
		return (ObjectPointer != 0);
	}

private:
	unsigned int ObjectPointer;
};

#endif