#include <Secretary.h>

class Secretary::Aaron
{
public:
  Aaron()
  {}
  
  ~Aaron() = default;
  
};

Secretary::Secretary() : appointedSecretary_p(std::make_unique<Aaron>())
{}

Secretary::~Secretary() = default;
  
