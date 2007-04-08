#ifndef CEVENT_H
#define CEVENT_H
class CEvent{
public:
	/*typedef enum MouseButton_e{
		MB_LEFT = 0x01,
		MB_MIDDLE,
		MB_RIGHT,
		MB_WHEELUP,
		MB_WHEELDOWN
	}MouseButton;*/
	enum EventType_e{
		EVT_KEYPRESS,
		EVT_KEYRELEASE,
		EVT_MOUSEPRESS,
		EVT_MOUSERELEASE,
		EVT_WINDOWCLOSE
	}EventType;
	union {
		struct {
			unsigned char key;
		}keyPress;
		struct {
			unsigned char key;
		}keyRelease;
		struct {
			unsigned char button;
			int x;
			int y;
		}mousePress;
		struct {
			unsigned char button;
			int x;
			int y;
		}mouseRelease;
	}data;
	  //CEvent& operator==( EventType_e );
	  //CEvent& operator=( EventType_e );
private:
};
#endif
