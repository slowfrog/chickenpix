
CC=g++ 

SRC_DIR=src
OBJ_DIR=obj
SRC_DIR1=$(SRC_DIR)/CL
OBJ_DIR1=$(OBJ_DIR)/CL

CFLAGS=-c -g -Wall 
LDFLAGS=-g -pthread 
CFLAGS1=`pkg-config --cflags clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3` -I$(SRC_DIR) $(CFLAGS) 
LDFLAGS1=`pkg-config --libs clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3` $(LDFLAGS)

SOURCES=$(SRC_DIR)/Animated.cpp \
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
        $(SRC_DIR)/Visual.cpp

SOURCES1=$(SRC_DIR1)/ClanLib.cpp \
         $(SRC_DIR1)/CLInputs.cpp \
         $(SRC_DIR1)/CLLoader.cpp \
         $(SRC_DIR1)/CLRender.cpp \
         $(SRC_DIR1)/CLResources.cpp \
         $(SRC_DIR1)/CLState.cpp \
         $(SRC_DIR1)/CLVisual.cpp \
         $(SRC_DIR1)/CLVisualImage.cpp \
         $(SRC_DIR1)/CLVisualSprite.cpp \
         $(SRC_DIR1)/CLVisualText.cpp \
         $(SRC_DIR1)/clmain.cpp

OBJECTS=$(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) 
OBJECTS1=$(SOURCES1:$(SRC_DIR1)/%.cpp=$(OBJ_DIR1)/%.o)

EXECUTABLE1=clmain

$(EXECUTABLE1): $(OBJECTS) $(OBJECTS1) 
	$(CC) $(LDFLAGS1) $(OBJECTS) $(OBJECTS1) -o $@ 

$(OBJ_DIR1)/%.o: $(SRC_DIR1)/%.cpp
	@echo 'Building file: $<'
	@mkdir -p $(OBJ_DIR1)
	$(CC) $(CFLAGS1) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $< 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo 'Building file: $<'
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $< 

src: $(OBJECTS) $(OBJECTS1) 

clean:
	-rm $(OBJECTS) $(OBJECTS1)

purge:
	-rm -rf $(OBJ_DIR1) $(OBJ_DIR) $(EXECUTABLE1) *~ */*~ 

all: $(SOURCES) $(SOURCES1) $(EXECUTABLE1)
