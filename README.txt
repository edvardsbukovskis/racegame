Creators:
LU DF students Andris Lapiņš and Edvards Bukovskis



The front-end of the game is created using SDL/SDL2 libraries. The game renders sprites and textures using SDL functions, the game's concept is a racing game, currently there is a car that can be controlled using either keyboard keys W,A,S,D or UP, DOWN, LEFT, RIGHT arrows. There is an acceleration function implemented so that when keys W or UP are pressed, the car accelerates, when the keys are released the car decelerates. There is collision implemented so the car cannot drive out of bounds of the window but it lacks the implementation of collision with racetrack borders.


To install SDL/SDL2 run these commands:

#install sdl2
sudo apt install libsdl2-dev libsdl2-2.0-0 -y;

#install sdl image
sudo apt install libjpeg9-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y;

#install sdl mixer
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;

#install sdl true type fonts
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y;


To run the game:
1.You must have the necessary libraries installed
2.There already is a makefile so in the terminal window you should go to the path of the makefile and run the command "make".
3.After executing "make" command there should be game.exe file created, to launh the game simply run command "./game" from terminal.
