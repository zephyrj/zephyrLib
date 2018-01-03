#include "Framework.hpp"
#include <thread>
#include <iostream>

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
    io_service(new boost::asio::io_service()),
    io_service_work(new boost::asio::io_service::work(*io_service)),
    worker_thread(nullptr)
{}

void Framework::run()
{
  if (running == false)
  {
    worker_thread = new std::thread(&workerThread, this);
    running = true;
  }
}

void Framework::shutdown()
{
  if (running == true)
  {
    io_service_work.reset();
    worker_thread->join();
    delete worker_thread;
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

}}