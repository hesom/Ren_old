#pragma once
#include "keymap.h"
#include <vector>
namespace ren
{
	/*! Implement this interface to be able to subscribe to keyboard events.
		Each of these functions will only be called when the corresponding keyboard
		event occured. Make sure to call InputerManager::attachKeyListener to attach your
		listener
	*/
	class IKeyListener
	{
	public:
	    virtual ~IKeyListener() = default;
	    virtual auto onKeyPressed(Key key, std::vector<KeyMod> mods) -> void = 0;
		virtual auto onKeyReleased(Key key, std::vector<KeyMod> mods) -> void  = 0;
	};
}

