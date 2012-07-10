#pragma once

#include "Resources.h"
#include "System.h"
#include "VisualContext.h"  

// Class Loader
class Loader: public System {
protected:
  std::string resourceFile;
  std::string meFile;
  std::string mLevel;
public:
  // Constructor/Destructor
  Loader( string const &name);
  virtual ~Loader();
  
  // System interface
  virtual void init   ( EntityManager&);
  virtual void update ( EntityManager&, int);
  virtual void exit   ( EntityManager&);
  
   inline SystemType getType() const { return LOADER_TYPE;}
  
  // Loader interface
  virtual void addImage  ( Resources *resources) =0;
  virtual void addSprites( Resources *resources) =0;
  virtual void addFont   ( Resources *resources) =0;
  virtual void addAudio  ( Resources *resources) =0;

  // Laod resources build entities
  void setEntities ( const std::string&);
  void setResources( const std::string&);
  void setLevel    ( const std::string&);
  
  // Debug
  virtual string toString() const;
  
protected:
  virtual void initResources( EntityManager&);
  virtual void loadLevel    ( EntityManager&);
  virtual void loadEntities ( EntityManager&);
  
  virtual void addImage ( string const &path, Resources *resources,
                          string const &alias="") const = 0;
  virtual void addFont  ( string const &path, int size, Resources *resources,
                          string const &alias="") = 0;
  virtual void addSprite( string const &path, Resources *resources,
                          string const &name) = 0;
  virtual void addAudio ( string const &path, Resources *resources,
                          string const &name) = 0;
  
private:
  void createImage( EntityManager&,ImagePart const &part, float x, float y, int zOrder,
                    Resources *resources) const;
  void loadTmxMap ( EntityManager&, string const &name) const;
  
private:
};
