#include "test_dummy_plugin.h"

#include <iostream>
#include <thread>

#include "plugin_create_helper.h"

JCY_PLUGIN_DEFINE(DummyPluginInterface)
JCY_PLUGIN_EMBED(TestDummyPlugin, DummyPluginInterface, "MyDummyPlugin",
                 "0.0.1")

TestDummyPlugin::TestDummyPlugin()
{
  std::cout << "TestDummyPlugin Created" << std::endl;
}

TestDummyPlugin::~TestDummyPlugin()
{
  std::cout << "TestDummyPlugin Destroyed" << std::endl;
}

int TestDummyPlugin::Load()
{
  std::cout << "Loading" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  return 1;
}

int TestDummyPlugin::Process()
{
  std::cout << "Processing" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  return 1;
}

void TestDummyPlugin::Unload()
{
  std::cout << "Unload" << std::endl;
}
