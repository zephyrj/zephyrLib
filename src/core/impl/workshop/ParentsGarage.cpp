#include "ParentsGarage.h"

#include <boost/asio/io_service.hpp>
#include <thread>

namespace zephyr { namespace core {
  
struct Workshop::ParentsGarage::Worker
{
  explicit Worker(size_t id) : m_workerId(id),
                               m_workThread()
  {}
  
  ~Worker() = default;
  
  void async_start_work(boost::asio::io_service& workQueue) 
  {
    m_workThread = std::thread([&workQueue](){ workQueue.run(); });
  }
  
  void join()
  {
    m_workThread.join();
  }
  
  size_t m_workerId;
  std::thread m_workThread;
 
};
  
Workshop::ParentsGarage::ParentsGarage() 
  : m_workQueue_p(std::make_unique<boost::asio::io_service>()),
    m_workers(),
    m_numberOfActiveWorkers(0)
{}
  
Workshop::ParentsGarage::~ParentsGarage()
{}
  
void Workshop::ParentsGarage::add_worker()
{
  if (m_numberOfActiveWorkers >= m_workers.max_size())
  {
    // todo exception or error code
    return;
  }
  m_workers[m_numberOfActiveWorkers] = std::make_unique<Workshop::ParentsGarage::Worker>(m_numberOfActiveWorkers);
  m_workers[m_numberOfActiveWorkers]->async_start_work(*m_workQueue_p);
  m_numberOfActiveWorkers++;
}

}}