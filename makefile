CXX		:=	clang++
FLAGS	:=	-Wall -Wextra -std=c++17

INCLUDE	:=	include
SRC		:=	src
BIN		:=	bin

LIBS	:=	-lSDL2 -lSDL2_image
EXE		:=	main

DEPS	:=	$(wildcard $(SRC)/*.cpp)
OBJ		:=	$(patsubst $(SRC)/%.cpp, $(BIN)/%.o, $(DEPS))


ifndef WIN64
$(BIN)/%.o: $(SRC)/%.cpp
	mkdir -p $(BIN)
	$(CXX) -c -o $@ $< $(FLAGS) -I$(INCLUDE)

$(BIN)/$(EXE): $(OBJ)
	$(CXX) $(FLAGS) -I$(INCLUDE) -o $@ $^ $(LIBS) -fuse-ld=mold
else
$(BIN)/%.o: $(SRC)/%.cpp
	mkdir -p $(BIN)/win64
	x86_64-w64-mingw32-g++ -c -o $@ $< $(FLAGS) -m64 -I$(INCLUDE) -ISDL/include

$(BIN)/win64/$(EXE): $(OBJ)
	x86_64-w64-mingw32-g++ $(FLAGS) -I$(INCLUDE) -o $@ $^ -s -L SDL/lib -lmingw32 -lSDL2main $(LIBS) -static-libstdc++
	cp -R lib/win/. $(BIN)/win64/
	cp -R lib/res/ $(BIN)/win64/
endif

run: $(BIN)/$(EXE)
		./$(BIN)/$(EXE)


start:
		clear
		./$(BIN)/$(EXE)

clean:
		rm -rf $(BIN)/*

setup:
	mkdir -p $(BIN)
	mkdir -p $(SRC)
	mkdir -p $(INCLUDE)
	touch $(SRC)/main.cpp
	clear
