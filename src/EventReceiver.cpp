#include "EventReceiver.h"

EventReceiver::~EventReceiver(){

}

bool EventReceiver::OnEvent(const SEvent& event)
{
    if(mListener){
        if(mListener->OnEvent(event)){
            return true;
        }
    }
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT){
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }

    return false;
}

bool EventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

void EventReceiver::setListener(IEventReceiver *pListener){
    mListener = pListener;
}


EventReceiver::EventReceiver(){
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i){
        KeyIsDown[i] = false;
    }
    mListener = NULL;
}
