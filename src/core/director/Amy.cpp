#include <Director.h>

class Director::Amy
{
public:
  Amy()
  {}
  
  ~Amy() = default;
  
};

Director::Director() : appointedDirector_p(std::make_unique<Amy>())
{}

Director::~Director() = default;
  
