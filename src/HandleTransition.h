#pragma once

#include <vector>

// Forward(s)
class EntityManager;

/**
 Class : manage entities between 2 EntityManager during a switch mode
 **/
class HandleTransition  {
public:
  typedef std::vector<std::string> TTagCollection;
  
public:
  HandleTransition(){}
  ~HandleTransition(){}
  
  // Copy entities with tag "tag"
  void transit( EntityManager &from, EntityManager &to, const std::string &tag);
  void transit( EntityManager &from, EntityManager &to, const TTagCollection &vtag);

private:
  
};
