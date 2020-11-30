# CODE

For the development I used VSCode with the __PlatformIO__ framework.  
You will need this environment too, for compiling and uploading to a D1 mini.

## Structure

I tried to make the code as reusable as possible, so separated the controls into modules in the lib folder. The main class contains only minimal necessary configuration, and act as a bridge between modules.  

This setup allows for easy modifications. (For example I can get the tube, display, and clock modules and make a brend new design for a simple nixie clock.)
