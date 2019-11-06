#include "dummy_plugin_interface.h"

class TestDummyPlugin : public DummyPluginInterface {
 public:
  TestDummyPlugin();
  ~TestDummyPlugin() override;

  int Load() override;
  int Process() override;
  void Unload() override;
};
