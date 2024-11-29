Begin:
1. Download SFML and extract in an SFML folder in Documents
2. C/C++ -> Preprocessor -> Preprocessor Definitions -> add SFML_STATIC
3. add SFML include path to project properties -> C++ -> Additional Include Directories
4. add SFML lib path to project properties -> Linker -> General -> Additional Lib Directories
5. add things below (in same order) to project properties -> Linker -> Input -> Additional Dependencies

(Must be on separate lines and in the same order presented here to work)<br>
sfml-graphics-s-d.lib<br>
sfml-window-s-d.lib<br>
sfml-system-s-d.lib<br>
sfml-main-d.lib<br>
opengl32.lib<br>
freetype.lib<br>
winmm.lib<br>
gdi32.lib

6. After finishing the program, you can remove the -d (debug) from the Additional Dependencies for it to run a bit smoother.
