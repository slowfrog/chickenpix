
CC=g++ 
CFLAGS=`pkg-config --cflags clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3` -c -g -Wall 
LDFLAGS=`pkg-config --libs clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3` -g -pthread 
SRC_DIR=src
OBJ_DIR=obj
SOURCES=$(SRC_DIR)/Animated.cpp \
        $(SRC_DIR)/ClanLib.cpp \
        $(SRC_DIR)/CLInputs.cpp \
        $(SRC_DIR)/CLLoader.cpp \
        $(SRC_DIR)/CLRender.cpp \
        $(SRC_DIR)/CLResources.cpp \
        $(SRC_DIR)/CLState.cpp \
        $(SRC_DIR)/CLVisual.cpp \
        $(SRC_DIR)/CLVisualImage.cpp \
        $(SRC_DIR)/CLVisualSprite.cpp \
        $(SRC_DIR)/CLVisualText.cpp \
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
OBJECTS=$(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) 
EXECUTABLE=clmain

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo 'Building file: $<'
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $< 

src: $(OBJECTS) 

clean:
	-rm $(OBJECTS)

purge:
	-rm -rf $(OBJ_DIR) $(EXECUTABLE) *~ $(SRC_DIR)/*~ 

all: $(SOURCES) $(EXECUTABLE)
