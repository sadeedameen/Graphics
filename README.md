# Graphics

1.select Applications/Accessories/Terminal on the Ubuntu desktop

2.type ls /usr/include/GL 

3.if glut.h gl.h etc are there, great 

4.if not, install it 

```sh
sudo apt-get install freeglut3-dev
```
5.
```sh
g++ pgm.cpp -lGl -lGLU -lglut
```

Program to implemnet BFS algorith using OpnenGL
