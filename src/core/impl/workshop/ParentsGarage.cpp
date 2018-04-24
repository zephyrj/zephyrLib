#include "ParentsGarage.h"

#include <boost/asio/io_service.hpp>
#include <boost/thread.hpp>
#include <thread>

#include <exception/Exception.h>

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
    if (m_workThread.joinable())
    {
      m_workThread.join();
    }
  }
  
  size_t m_workerId;
  std::thread m_workThread;
 
};
  
Workshop::ParentsGarage::ParentsGarage() 
  : m_workQueue_p(std::make_unique<boost::asio::io_service>()),
    m_workers(),
    m_numberOfConfiguredWorkers(0)
{}
  
Workshop::ParentsGarage::~ParentsGarage() = default;

void Workshop::ParentsGarage::async_start_work()
{
  boost::asio::use_service<boost::asio::detail::task_io_service>(*m_workQueue_p).work_started();
  for (auto& worker : m_workers)
  {
    worker->async_start_work(*m_workQueue_p);
  }
}

void Workshop::ParentsGarage::stop_work()
{
  boost::asio::use_service<boost::asio::detail::task_io_service>(*m_workQueue_p).work_finished();
  for (auto& worker : m_workers)
  {
    worker->join();
  }
}

void Workshop::ParentsGarage::add_worker()
{
  if (m_numberOfConfiguredWorkers >= m_workers.max_size())
  {
    Exception::throw_exception<result::MAX_WORKER_LIMIT_REACHED>();
  }

  m_workers[m_numberOfConfiguredWorkers] = std::make_unique<Workshop::ParentsGarage::Worker>(m_numberOfConfiguredWorkers);
  m_workers[m_numberOfConfiguredWorkers]->async_start_work(*m_workQueue_p);
  m_numberOfConfiguredWorkers++;
}

}}