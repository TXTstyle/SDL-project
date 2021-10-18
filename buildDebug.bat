g++ -c src/*.cpp -std=c++14 -Wall -g -m64 -I include -I SDL/include
g++ *.o -o bin/debug/main -L SDL/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
cd /D bin/debug
start main.exe
