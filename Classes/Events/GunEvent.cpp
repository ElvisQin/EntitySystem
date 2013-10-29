//
//  GunEvent.cpp
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#include "GunEvent.h"

const char* GunEvent::GUN_EVENT_TYPE="GunEventType";

GunEvent::GunEvent(const Point& ip,const Point&tp,const char* type)
:EventCustom(GunEvent::GUN_EVENT_TYPE)
,initPoint(ip)
,targetPoint(tp)
,targetType(type)
{
}