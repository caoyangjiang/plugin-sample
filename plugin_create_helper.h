
#ifndef PLUGIN_CREATE_HELPER_H_
#define PLUGIN_CREATE_HELPER_H_

#define JCY_PLUGIN_API_VERSION 1

#ifdef _WIN32
#define JCY_EXPORT __declspec(dllexport)
#else
#define JCY_EXPORT
#endif

#define JCY_PLUGIN_DEFINE(plugin_interface)             \
  typedef void (*CreatePluginFunc)(plugin_interface**); \
                                                        \
  struct plugin_interface##_PluginDesc {                \
    int api_version;                                    \
    const char* file_name;                              \
    const char* class_name;                             \
    const char* plugin_name;                            \
    const char* plugin_version;                         \
    CreatePluginFunc create_func;                       \
  };

#define JCY_PLUGIN_EMBED(plugin_type, plugin_interface, plugin_name,          \
                         plugin_version)                                      \
  extern "C" {                                                                \
  JCY_EXPORT void Create(plugin_interface** plugin) {                         \
    *plugin = new plugin_type();                                              \
  }                                                                           \
                                                                              \
  JCY_EXPORT plugin_interface##_PluginDesc plugin_interface##_plugin_desc = { \
      JCY_PLUGIN_API_VERSION, __FILE__, #plugin_type, plugin_name,            \
      plugin_version,         Create};                                        \
  }

#endif  // PLUGIN_CREATE_HELPER_H_
