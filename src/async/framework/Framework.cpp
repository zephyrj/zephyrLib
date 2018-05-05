#include "Framework.hpp"

#include <iostream>
#include <algorithm>

#include <boost/asio/io_service.hpp>

namespace zephyr { namespace async {

void Framework::workerThread(Framework *framework_p)
{
  while (framework_p->isRunning())
  {
    try
    {
      framework_p->getIOService().run();
    }
    catch (std::exception & ex)
    {
      std::cerr << "Caught exception in the zephyr::async::Framework worker thread: " << ex.what() << std::endl;
    }
  }
}

Framework::Framework() :
    running(false),
    components_mutex(),
    components(),
    io_service(std::make_unique<boost::asio::io_service>()),
    worker_thread(nullptr)
{}

Framework::~Framework() = default;

void Framework::run()
{
  if (running == false)
  {
    boost::asio::use_service<boost::asio::detail::task_io_service>(*io_service).work_started();
    worker_thread = std::make_unique<std::thread>(&workerThread, this);
    running = true;
  }
}

void Framework::shutdown()
{
  if (running == true)
  {
    boost::asio::use_service<boost::asio::detail::task_io_service>(*io_service).work_finished();
    worker_thread->join();
    worker_thread.reset(nullptr);
    running = false;
  }
}

bool Framework::isRunning()
{
  return running;
}

void Framework::componentAdded(framework::Component* component)
{
  components_mutex.lock();
  components.push_back(component);
  components_mutex.unlock();
}

void Framework::componentRemoved(framework::Component* component)
{
  components_mutex.lock();
  auto it = std::find(components.begin(),
                      components.end(),
                      component);

  if (it != components.end())
  {
    components.erase(it);
  }
  components_mutex.unlock();
}

boost::asio::io_service &Framework::getIOService()
{
  return *io_service;
}

}}