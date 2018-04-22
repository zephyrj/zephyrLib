#include <Workshop.h>

namespace boost { namespace asio { class io_service; }}

namespace zephyr { namespace core {
  
class Workshop::ParentsGarage final
{
public:
  ParentsGarage();
  ~ParentsGarage();

private:
  std::unique_ptr<boost::asio::io_service> m_workQueue_p;
    
};
  
}}