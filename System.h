#include <string>

using namespace std;

class System {
private:
  string name;
  
public:
  System(string const &name);
  virtual ~System();
  string const &getName() const;
  virtual string toString() const;
};
