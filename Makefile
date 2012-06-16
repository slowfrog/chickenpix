CC=g++ 
#CFLAGS=`pkg-config --cflags clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3 clanGL-2.3 clanGL1-2.3` -pthread -c -Wall 
#LDFLAGS=`pkg-config --libs clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3 clanGL-2.3 clanGL1-2.3 clanGUI-2.3 clanVorbis-2.3 ` 
CFLAGS=`pkg-config --cflags clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3` -c -Wall 
LDFLAGS=`pkg-config --libs clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3` -pthread 
SRC_DIR=src
SOURCES=$(SRC_DIR)/Animated.cpp \
        $(SRC_DIR)/ClanLib.cpp \
        $(SRC_DIR)/CLLoader.cpp \
        $(SRC_DIR)/CLRender.cpp \
        $(SRC_DIR)/CLSprites.cpp \
        $(SRC_DIR)/CLState.cpp \
        $(SRC_DIR)/CLVisual.cpp \
        $(SRC_DIR)/Component.cpp \
        $(SRC_DIR)/Entity.cpp \
        $(SRC_DIR)/EntityManager.cpp \
        $(SRC_DIR)/Input.cpp \
        $(SRC_DIR)/Loader.cpp \
        $(SRC_DIR)/Mobile.cpp \
        $(SRC_DIR)/Render.cpp \
        $(SRC_DIR)/Resource.cpp \
        $(SRC_DIR)/System.cpp \
        $(SRC_DIR)/Transform.cpp \
        $(SRC_DIR)/Visual.cpp \
        $(SRC_DIR)/clmain.cpp
OBJECTS=$(SOURCES:.cpp=.o) 
EXECUTABLE=clmain


$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 

.cpp.o: 
	$(CC) $(CFLAGS) $< -o $@

src: $(OBJECTS) 

clean:
	rm $(OBJECTS)

all: $(SOURCES) $(EXECUTABLE) 