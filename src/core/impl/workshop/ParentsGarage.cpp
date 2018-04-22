#include "ParentsGarage.h"

#include <boost/asio/io_service.hpp>

namespace zephyr { namespace core {
  
Workshop::ParentsGarage::ParentsGarage() : m_workQueue_p(std::make_unique<boost::asio::io_service>())
{}
  
Workshop::ParentsGarage::~ParentsGarage()
{}

}}