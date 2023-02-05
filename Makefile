all : main.cpp ; clang++ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -std=c++11 libraylib.a  main.cpp   -o pong 


clean : ; main.c 