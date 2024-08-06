# curses

1. struct WinSize : {int width, int height} - dimensions of a frame;
2. struct Frame* frame_ptr - current frame on framestack
3. struct List<struct Frame*> framestack - head is a default console, gets rendered until **frame_ptr**
4. struct Action - map [char event->struct Frame* value], value gets pushed on the **framestack** when event is the input
5. Using a struct Frame to store:
- struct WinSize ws for dimensions
- char* name for [frame name]
- char* buf for constructing the frame
- const char* bc - background color
- const char* fc - foreground color
- fields - a list of input FRAMES
- events - a list of ACTIONS
  
