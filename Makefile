main: *.cpp *.h
	g++ [A-Z]*.cpp main.cpp -o main

clmain: *.cpp *.h
	g++ [A-Z]*.cpp clmain.cpp `pkg-config --cflags --libs clanCore-2.3 clanDisplay-2.3 clanSWRender-2.3 clanApp-2.3` -lpthread -o clmain

