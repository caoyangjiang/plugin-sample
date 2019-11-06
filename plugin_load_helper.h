#ifndef PLUGIN_LOAD_HELPER_H_
#define PLUGIN_LOAD_HELPER_H_

#include <iostream>
#include <string>

#include "plugin_create_helper.h"

#if defined(_WIN32) && (!defined(JCY_LOAD_FUNC) || !defined(JCY_SYM_FUNC) || \
                        !defined(JCY_LIB_HANDLE))
#include <windows.h>
#endif

#ifndef JCY_LIB_HANDLE
#if defined(_WIN32)
#define JCY_LIB_HANDLE HMODULE
#else
#define JCY_LIB_HANDLE void*
#endif
#endif

#if !defined(JCY_LOAD_FUNC) || !defined(JCY_SYM_FUNC)
#ifdef _WIN32
#define JCY_LOAD_FUNC(path) LoadLibrary(TEXT(path))
#define JCY_SYM_FUNC(lib, sym) GetProcAddress((lib), (sym))
#define JCY_FREE_FUNC(lib) FreeLibrary(lib)
#else
#include <dlfcn.h>
#define JCY_LOAD_FUNC(path) dlopen((path), RTLD_LAZY)
#define JCY_SYM_FUNC(lib, sym) dlsym((lib), (sym))
#define JCY_FREE_FUNC(lib) dlclose(lib)
#endif
#endif

class DynamicLibLoader {
 public:
  bool Load(const std::string& lib_path) {
    lib_handle_ = JCY_LOAD_FUNC(lib_path.c_str());
    return lib_handle_ != NULL;
  }

  void Unload() {
    if (lib_handle_ != NULL) JCY_FREE_FUNC(lib_handle_);
  }

  void* GetSymbol(const std::string& symbol) {
    return JCY_SYM_FUNC(lib_handle_, symbol.c_str());
  }

 private:
  JCY_LIB_HANDLE lib_handle_ = NULL;
};

#define JCY_PLUGIN_LOADER_DEFINE(plugin_interface)                          \
  JCY_PLUGIN_DEFINE(plugin_interface)                                       \
                                                                            \
  class plugin_interface##PluginLoader {                                    \
   public:                                                                  \
    bool Load(const std::string& plugin_path) {                             \
      auto load_lib_result = lib_loader_.Load(plugin_path);                 \
      if (!load_lib_result) {                                               \
        return false;                                                       \
      }                                                                     \
                                                                            \
      auto load_symbol_result =                                             \
          lib_loader_.GetSymbol(kPlugin_Desc_Symbol_Name);                  \
      if (load_symbol_result == NULL) {                                     \
        return false;                                                       \
      }                                                                     \
                                                                            \
      plugin_desc_ = reinterpret_cast<plugin_interface##_PluginDesc*>(      \
          load_symbol_result);                                              \
      return true;                                                          \
    }                                                                       \
                                                                            \
    void Unload() { return lib_loader_.Unload(); }                          \
                                                                            \
    plugin_interface* CreatePlugin() {                                      \
      plugin_interface* plugin = nullptr;                                   \
      plugin_desc_->create_func(&plugin);                                   \
      return plugin;                                                        \
    }                                                                       \
                                                                            \
    std::string GetFileName() const { return plugin_desc_->file_name; }     \
    std::string GetClassName() const { return plugin_desc_->class_name; }   \
    std::string GetPluginName() const { return plugin_desc_->plugin_name; } \
    std::string GetPluginVersion() const {                                  \
      return plugin_desc_->plugin_version;                                  \
    }                                                                       \
                                                                            \
   private:                                                                 \
    const std::string kPlugin_Desc_Symbol_Name =                            \
        std::string(#plugin_interface) + "_plugin_desc";                    \
    DynamicLibLoader lib_loader_;                                           \
    plugin_interface##_PluginDesc* plugin_desc_;                            \
  };

#endif  // PLUGIN_LOAD_HELPER_H_
