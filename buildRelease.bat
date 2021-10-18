g++ -c src/*.cpp -std=c++14 -Wall -O3 -m64 -I include -I SDL/include
g++ *.o -o bin/release/main -s -L SDL/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
cd /D bin/release
start main.exe