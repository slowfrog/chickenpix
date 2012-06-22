
CC=g++ 

SRC_DIR=src
OBJ_DIR=obj
TMX_SRC_DIR=$(SRC_DIR)/TmxParser
TMX_OBJ_DIR=$(OBJ_DIR)/TmxParser
CL_SRC_DIR=$(SRC_DIR)/CL
CL_OBJ_DIR=$(OBJ_DIR)/CL
SF_SRC_DIR=$(SRC_DIR)/SFML
SF_OBJ_DIR=$(OBJ_DIR)/SFML

CFLAGS=-c -g -Wall -I/usr/include/python2.6
LDFLAGS=-g -pthread -lpython2.6 -lz -ltinyxml
CL_CFLAGS=`pkg-config --cflags clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3` $(CFLAGS) 
CL_LDFLAGS=`pkg-config --libs clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3` $(LDFLAGS)
SF_CFLAGS=-I$(SFML_DIR)/include $(CFLAGS) 
SF_LDFLAGS=-L$(SFML_DIR)/lib $(LDFLAGS) -lsfml-window -lsfml-graphics -lsfml-system 

SOURCES=$(SRC_DIR)/Animated.cpp \
        $(SRC_DIR)/Component.cpp \
        $(SRC_DIR)/ComponentRegistry.cpp \
        $(SRC_DIR)/Entity.cpp \
        $(SRC_DIR)/EntityManager.cpp \
        $(SRC_DIR)/Input.cpp \
        $(SRC_DIR)/Inputs.cpp \
        $(SRC_DIR)/Loader.cpp \
        $(SRC_DIR)/Mobile.cpp \
        $(SRC_DIR)/Render.cpp \
        $(SRC_DIR)/Resource.cpp \
        $(SRC_DIR)/Resources.cpp \
        $(SRC_DIR)/Scriptable.cpp \
        $(SRC_DIR)/Scripting.cpp \
        $(SRC_DIR)/System.cpp \
        $(SRC_DIR)/Transform.cpp \
        $(SRC_DIR)/BVisual.cpp \
        $(SRC_DIR)/PythonTypes.cpp

TMX_SOURCES=$(TMX_SRC_DIR)/TmxImage.cpp \
            $(TMX_SRC_DIR)/TmxLayer.cpp \
            $(TMX_SRC_DIR)/TmxMap.cpp \
            $(TMX_SRC_DIR)/TmxObject.cpp \
            $(TMX_SRC_DIR)/TmxObjectGroup.cpp \
            $(TMX_SRC_DIR)/TmxPolygon.cpp \
            $(TMX_SRC_DIR)/TmxPolyline.cpp \
            $(TMX_SRC_DIR)/TmxPropertySet.cpp \
            $(TMX_SRC_DIR)/TmxTile.cpp \
            $(TMX_SRC_DIR)/TmxTileset.cpp \
            $(TMX_SRC_DIR)/TmxUtil.cpp \
            $(TMX_SRC_DIR)/base64.cpp

CL_SOURCES=$(CL_SRC_DIR)/ClanLib.cpp \
         $(CL_SRC_DIR)/CLInputs.cpp \
         $(CL_SRC_DIR)/CLLoader.cpp \
         $(CL_SRC_DIR)/CLRender.cpp \
         $(CL_SRC_DIR)/CLResources.cpp \
         $(CL_SRC_DIR)/CLState.cpp \
         $(CL_SRC_DIR)/CLVisualImage.cpp \
         $(CL_SRC_DIR)/CLVisualSprite.cpp \
         $(CL_SRC_DIR)/CLVisualText.cpp \
         $(CL_SRC_DIR)/clmain.cpp

SF_SOURCES=$(SF_SRC_DIR)/SFMLInputs.cpp \
         $(SF_SRC_DIR)/SFMLLoader.cpp \
         $(SF_SRC_DIR)/SFMLRender.cpp \
         $(SF_SRC_DIR)/SFMLResources.cpp \
         $(SF_SRC_DIR)/SFMLState.cpp \
         $(SF_SRC_DIR)/SFMLVisualImage.cpp \
         $(SF_SRC_DIR)/SFMLVisualSprite.cpp \
         $(SF_SRC_DIR)/SFMLVisualText.cpp \
         $(SF_SRC_DIR)/smain.cpp

OBJECTS=$(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) 
TMX_OBJECTS=$(TMX_SOURCES:$(TMX_SRC_DIR)/%.cpp=$(TMX_OBJ_DIR)/%.o) 
CL_OBJECTS=$(CL_SOURCES:$(CL_SRC_DIR)/%.cpp=$(CL_OBJ_DIR)/%.o)
SF_OBJECTS=$(SF_SOURCES:$(SF_SRC_DIR)/%.cpp=$(SF_OBJ_DIR)/%.o)

CL_EXECUTABLE=clmain
SF_EXECUTABLE=smain

all: $(SOURCES) $(TMX_SOURCES) $(CL_SOURCES) $(SF_SOURCES) $(CL_EXECUTABLE) $(SF_EXECUTABLE)

$(CL_EXECUTABLE): $(OBJECTS) $(TMX_OBJECTS) $(CL_OBJECTS) 
	$(CC) $(CL_LDFLAGS) $(OBJECTS) $(TMX_OBJECTS) $(CL_OBJECTS) -o $@ 

$(SF_EXECUTABLE): $(OBJECTS) $(TMX_OBJECTS) $(SF_OBJECTS) 
	$(CC) $(SF_LDFLAGS) $(OBJECTS) $(TMX_OBJECTS) $(SF_OBJECTS) -o $@ 

$(CL_OBJ_DIR)/%.o: $(CL_SRC_DIR)/%.cpp
	@echo 'Building file: $<'
	@mkdir -p $(CL_OBJ_DIR)
	$(CC) $(CL_CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $< 

$(SF_OBJ_DIR)/%.o: $(SF_SRC_DIR)/%.cpp
	@echo 'Building file: $<'
	@mkdir -p $(SF_OBJ_DIR)
	$(CC) $(SF_CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $< 

$(TMX_OBJ_DIR)/%.o: $(TMX_SRC_DIR)/%.cpp
	@echo 'Building file: $<'
	@mkdir -p $(TMX_OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $< 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo 'Building file: $<'
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $< 

src: $(OBJECTS) $(TMX_OBJECTS) $(CL_OBJECTS) $(SF_OBJECTS)

clean:
	-rm $(OBJECTS) $(TMX_OBJECTS) $(CL_OBJECTS) $(SF_OBJECTS)

purge:
	-rm -rf $(CL_OBJ_DIR) $(SF_OBJ_DIR) $(TMX_OBJ_DIR) $(OBJ_DIR) $(CL_EXECUTABLE) $(SF_EXECUTABLE) $(shell find . -name '*~') $(shell find . -name '*.pyc')

