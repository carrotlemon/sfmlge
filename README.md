Begin:
1. Download SFML and extract in an SFML folder in Documents
2. add SFML include path to project properties -> C++ -> Additional Include Directories
3. add SFML lib path to project properties -> Linker -> Additional Lib Directories
4. add things below (in same order) to project properties -> Linker -> Input -> Additional Dependencies

sfml-graphics-s-d.lib
sfml-window-s-d.lib
sfml-system-s-d.lib
sfml-main-d.lib
opengl32.lib
freetype.lib
winmm.lib
gdi32.lib
