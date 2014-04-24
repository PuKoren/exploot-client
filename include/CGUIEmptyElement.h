#pragma once
#include <irrlicht/irrlicht.h>

#define MGUIET_EMPTY (irr::gui::EGUI_ELEMENT_TYPE)(irr::gui::EGUIET_COUNT+1)

class CGUIEmptyElement : public irr::gui::IGUIElement
{
public:
   CGUIEmptyElement(irr::gui::IGUIEnvironment* environment, irr::gui::IGUIElement* parent)
      : irr::gui::IGUIElement((irr::gui::EGUI_ELEMENT_TYPE)MGUIET_EMPTY, environment, parent, -1, environment->getVideoDriver()->getViewPort()) {}

   irr::gui::IGUIEnvironment* GetEnvironment() { return Environment; }

   virtual const irr::c8* getTypeName() const   { return "empty"; }

   virtual bool isPointInside(const irr::core::position2d<irr::s32>& point) const
   {
      return false;
   }

   virtual bool bringToFront(IGUIElement* element)
   {
      bool result = IGUIElement::bringToFront(element);

      // pass that on
      if ( Parent )
      {
         Parent->bringToFront(this);
      }
      return result;
   }

};
