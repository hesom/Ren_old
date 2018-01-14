#pragma once
#include <vector>
#include <memory>
#include "ui/keylistener.h"
#include "ui/mouselistener.h"

namespace ren
{
	/*! The InputManager is a singleton class which dispatches the keyboard and mouse inputs gathered
		by the window to subscribed listener classes (aka observer design pattern)
	*/
	class InputManager
	{
	private:
		InputManager();
		double m_mouseX_old = 0;
		double m_mouseY_old = 0;
		std::vector<IKeyListener*> keyListeners;
		std::vector<IMouseListener*> mouseListeners;
	public:
		/*! Returns the singleton instance of the InputManager
			\return the instance
		*/
		static InputManager& getInstance();

		InputManager(InputManager const&) = delete;
		void operator=(InputManager const&) = delete;

		/*! Handles the single event after a key is pressed down.
			\param key the glfw key id
			\param mods the glfw mod keys pressed, encoded in a single int (shift, alt, etc)
		*/
		void handleKeyPressedEvent(const int key, const int mods);

		/*! Handles the single event after a key is released.
			\param key the glfw key id
			\param mods the glfw mod keys pressed, encoded in a single int (shift, alt, etc)
		*/
		void handleKeyReleasedEvent(const int key, const int mods);

		/*! Handles the single event after a key is pressed.
			\param button the glfw mouse button id
			\param mods the glfw mod keys pressed, encoded in a single int (shift, alt, etc)
		*/
		void handleMousePressedEvent(const int button, const int mods);

		/*! Handles the single event after a key is released.
			\param key the glfw key id
			\param mods the glfw mod keys pressed, encoded in a single int (shift, alt, etc)
		*/
		void handleMouseReleasedEvent(const int button, const int mods);

		/*! Handles the event after the mouse is released.
			\param xpos the x position of the mouse. 0 is top left of the window
			\param ypos the y position of the mouse. 0 is top left of the window
		*/
		void handleCursorEvent(const double xpos, const double ypos);

		/*! Handles the event after scrolling with the mouse wheel 
			\param xoffset how far the mouse wheel was scrolled from left to right 
			\param yoffset how far the mouse wheel was scrolled from top to bottom
		*/
		void handleScrollEvent(const double xoffset, const double yoffset);

		/*! Attaches a IMouseListener that gets notified each time a mouse event occurs
			\param mouseListener pointer to the IMouseListener to be attached
		*/
		void attachMouseListener (IMouseListener* mouseListener);

		/*! Detaches a IMouseListener to unsubscribed from event notifications
			\param mouseListener pointer to the IMouseListener to be detached
		*/
		void detachMouseListener(const IMouseListener* mouseListener);

		/*! Attaches a IKeyListener that gets notified each time a keyboard event occurs
			\param keyListener pointer to the IKeyListener to be attached
		*/
		void attachKeyListener(IKeyListener* keyListener);

		/*! Detaches a IKeyListener to unsubscribed from event notifications
			\param keyListener pointer to the IKeyListener to be detached
		*/
		void detachKeyListener(const IKeyListener* keyListener);

	private:
		/*! Maps glfw key enum values to a safer internal enum class format */
		static Key mapKey(int glfwKey);
		/*! Maps glfw mod enum values to a safer internal enum class format */
		static std::vector<KeyMod> mapMods(int glfwMod);
		/*! Maps glfw mouse button enum values to a safer internal enum class format */
		static MouseButton mapMouse(int glfwMouse);
	};

	
}


