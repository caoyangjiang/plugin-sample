
#include <iostream>
#include <memory>

#include "dummy_plugin_interface.h"
#include "plugin_load_helper.h"

int main(int argc, char** argv)
{
  // HVR_PLUGIN_DEFINE(DummyPluginInterface);
  JCY_PLUGIN_LOADER_DEFINE(DummyPluginInterface);

  DummyPluginInterfacePluginLoader loader;

  auto load_result = loader.Load(argv[1]);
  std::cout << "Load result: " << load_result << std::endl;
  std::cout << "File: " << loader.GetFileName() << std::endl;
  std::cout << "Class: " << loader.GetClassName() << std::endl;
  std::cout << "Plugin: " << loader.GetPluginName() << std::endl;
  std::cout << "Version: " << loader.GetPluginVersion() << std::endl;

  std::unique_ptr<DummyPluginInterface> plugin(loader.CreatePlugin());
  if (plugin == NULL) {
    std::cout << "Plugin is NULL !" << std::endl;
  } else {
    plugin->Load();
    plugin->Process();
    plugin->Unload();
  }

  return 0;
}
