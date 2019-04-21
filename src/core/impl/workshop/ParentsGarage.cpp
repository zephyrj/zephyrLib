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
    std::thread t([&workQueue](){ workQueue.run(); });
    m_workThread.push_back(std::move(t));
  }
  
  void join()
  {
    if (m_workThread[0].joinable())
    {
      m_workThread[0].join();
    }
  }
  
  size_t m_workerId;
  std::vector<std::thread> m_workThread;
 
};
  
Workshop::ParentsGarage::ParentsGarage() 
  : m_workQueue_p(std::make_unique<boost::asio::io_service>()),
    m_workers(),
    m_numberOfConfiguredWorkers(0),
    m_working(false)
{}
  
Workshop::ParentsGarage::~ParentsGarage() = default;

void Workshop::ParentsGarage::async_start_work()
{
  if (m_numberOfConfiguredWorkers == 0) Exception::throw_exception<result::NO_ACTIVE_WORKERS>();
  if (m_working) Exception::throw_exception<result::ALREADY_IN_PROGRESS>();

  boost::asio::use_service<boost::asio::detail::task_io_service>(*m_workQueue_p).work_started();
  auto it = std::begin(m_workers);
  auto end = std::next(std::begin(m_workers), m_numberOfConfiguredWorkers);
  while (it != end) {
    (*it)->async_start_work(*m_workQueue_p);
    it++;
  }
  m_working = true;
}

void Workshop::ParentsGarage::stop_work()
{
  if (!m_working) Exception::throw_exception<result::NOT_IN_PROGRESS>();

  boost::asio::use_service<boost::asio::detail::task_io_service>(*m_workQueue_p).work_finished();
  auto it = std::begin(m_workers);
  auto end = std::next(std::begin(m_workers), m_numberOfConfiguredWorkers);
  while (it != end) {
    (*it)->join();
    it++;
  }
  m_working = false;
}

void Workshop::ParentsGarage::add_worker()
{
  if (m_numberOfConfiguredWorkers >= m_workers.max_size()) Exception::throw_exception<result::MAX_WORKER_LIMIT_REACHED>();

  m_workers[m_numberOfConfiguredWorkers] = std::make_unique<Workshop::ParentsGarage::Worker>(m_numberOfConfiguredWorkers);
  m_numberOfConfiguredWorkers++;
}

void Workshop::ParentsGarage::add_to_work_queue(const std::function<void(void)>& workItem)
{
  m_workQueue_p->post(workItem);
}

void Workshop::ParentsGarage::add_to_work_queue(std::function<void(void)>&& workItem)
{
  m_workQueue_p->post(std::move(workItem));
}

}}