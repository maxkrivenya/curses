# curses

1. Using a struct WinSize : {int width, int height} to store dimensions of a frame;

2. Using a struct Frame to store:
- struct WinSize ws for dimensions
- char* name for [frame name]
- char* buf for constructing the frame
- const char* bc - background color
- const char* fc - foreground color
  
i wanna add a List<Frame> or something for making tiny input/output fields 
