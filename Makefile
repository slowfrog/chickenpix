
CC=g++ 

SRC_DIR=src
OBJ_DIR=obj
TMX_SRC_DIR=$(SRC_DIR)/TmxParser
TMX_OBJ_DIR=$(OBJ_DIR)/TmxParser
TIX_SRC_DIR=$(SRC_DIR)/tinyxml
TIX_OBJ_DIR=$(OBJ_DIR)/tinyxml
CL_SRC_DIR=$(SRC_DIR)/CL
CL_OBJ_DIR=$(OBJ_DIR)/CL
SF_SRC_DIR=$(SRC_DIR)/SFML
SF_OBJ_DIR=$(OBJ_DIR)/SFML

CFLAGS=-c -g -Wall -DTIXML_USE_STL  `pkg-config --cflags python`
LDFLAGS=-g -pthread `pkg-config --libs python` -lz
CL_CFLAGS=`pkg-config --cflags clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3` $(CFLAGS) 
CL_LDFLAGS=`pkg-config --libs clanCore-2.3 clanDisplay-2.3 clanApp-2.3 clanSWRender-2.3` $(LDFLAGS)
SF_CFLAGS=-I$(SFML_DIR)/include $(CFLAGS) 
SF_LDFLAGS=-L$(SFML_DIR)/lib $(LDFLAGS) -lsfml-window -lsfml-graphics -lsfml-system 

SOURCES:=$(shell ls $(SRC_DIR)/*.cpp)
TIX_SOURCES:=$(shell ls $(TIX_SRC_DIR)/*.cpp)
TMX_SOURCES:=$(shell ls $(TMX_SRC_DIR)/*.cpp)
CL_SOURCES=$(shell ls $(CL_SRC_DIR)/*.cpp)
SF_SOURCES=$(shell ls $(SF_SRC_DIR)/*.cpp)

OBJECTS=$(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) 
TMX_OBJECTS=$(TMX_SOURCES:$(TMX_SRC_DIR)/%.cpp=$(TMX_OBJ_DIR)/%.o) 
TIX_OBJECTS=$(TIX_SOURCES:$(TIX_SRC_DIR)/%.cpp=$(TIX_OBJ_DIR)/%.o) 
CL_OBJECTS=$(CL_SOURCES:$(CL_SRC_DIR)/%.cpp=$(CL_OBJ_DIR)/%.o)
SF_OBJECTS=$(SF_SOURCES:$(SF_SRC_DIR)/%.cpp=$(SF_OBJ_DIR)/%.o)

CL_EXECUTABLE=clmain
SF_EXECUTABLE=smain

all: $(SOURCES) $(TMX_SOURCES) $(TIX_SOURCES) $(CL_SOURCES) $(SF_SOURCES) $(CL_EXECUTABLE) $(SF_EXECUTABLE)

$(CL_EXECUTABLE): $(OBJECTS) $(TMX_OBJECTS) $(TIX_OBJECTS) $(CL_OBJECTS)
	$(CC) $(CL_LDFLAGS) $(OBJECTS) $(TMX_OBJECTS) $(TIX_OBJECTS) $(CL_OBJECTS) -o $@ 

$(SF_EXECUTABLE): $(OBJECTS) $(TMX_OBJECTS) $(TIX_OBJECTS) $(SF_OBJECTS) 
	$(CC) $(SF_LDFLAGS) $(OBJECTS) $(TMX_OBJECTS) $(TIX_OBJECTS) $(SF_OBJECTS) -o $@ 

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

$(TIX_OBJ_DIR)/%.o: $(TIX_SRC_DIR)/%.cpp
	@echo 'Building file: $<'
	@mkdir -p $(TIX_OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $< 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo 'Building file: $<'
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $< 

src: $(OBJECTS) $(TMX_OBJECTS) $(TIX_OBJECTS) $(CL_OBJECTS) $(SF_OBJECTS)

clean:
	-rm $(OBJECTS) $(CL_OBJECTS) $(SF_OBJECTS)

purge:
	-rm -rf $(CL_OBJ_DIR) $(SF_OBJ_DIR) $(TMX_OBJ_DIR) $(TIX_OBJ_DIR) $(OBJ_DIR) $(CL_EXECUTABLE) $(SF_EXECUTABLE) $(shell find . -name '*~') $(shell find . -name '*.pyc')

