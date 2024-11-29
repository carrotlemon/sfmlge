Begin:
1. Download SFML and extract in an SFML folder in Documents
2. add SFML include path to project properties -> C++ -> Additional Include Directories
3. add SFML lib path to project properties -> Linker -> General -> Additional Lib Directories
4. add things below (in same order) to project properties -> Linker -> Input -> Additional Dependencies

(Must be on separate lines and in the same order presented here to work)<br>
sfml-graphics-s-d.lib<br>
sfml-window-s-d.lib<br>
sfml-system-s-d.lib<br>
sfml-main-d.lib<br>
opengl32.lib<br>
freetype.lib<br>
winmm.lib<br>
gdi32.lib
