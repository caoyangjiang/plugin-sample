

#ifndef DUMMY_PLUGIN_INTERFACE_H_
#define DUMMY_PLUGIN_INTERFACE_H_

#include "plugin_create_helper.h"

class DummyPluginInterface {
 public:
  virtual ~DummyPluginInterface() {}
  virtual int Load() = 0;
  virtual int Process() = 0;
  virtual void Unload() = 0;
};

JCY_PLUGIN_DEFINE(DummyPluginInterface)

#endif  // DUMMY_PLUGIN_INTERFACE_H_