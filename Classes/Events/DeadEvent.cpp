//
//  DeadEvent.cpp
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#include "DeadEvent.h"
const char* DeadEvent::DEAD_EVENT_TYPE="DeadEventType";
DeadEvent* DeadEvent::create(Entity* e,const Point& p)
{
    DeadEvent* event=new DeadEvent(e,p);
    if(event){
        return event;
    }
    
    if (event) {
        delete event;
    }
    return NULL;
}

DeadEvent::DeadEvent(Entity* e,const Point& p)
:EventCustom(DeadEvent::DEAD_EVENT_TYPE)
,deadPoint(p)
,entity(e)
{
    
}