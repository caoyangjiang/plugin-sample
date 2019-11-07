# plugin-sample
a simple cross platform plugin creator and loader


There are three parties involved in the plugin, host, plugin provider and client.

**Host** defines the plugin interfaces and provide mechanism to load the plugin.
**Plugin Provider** provides the plugin implementation and adhere to the plugin loading rules specified by the host.
**client** uses software provided by the Host and wishes to use a 3rd party plugin written by a 3rd parity Plugin Provider.


#### Try it out
This sample code demonstrates how to create, load and use a plugin.

To create executable (**Host** software)
~~~~~~~~~~~~~~~~
g++ -std=c++17 test_host.cpp -ldl
~~~~~~~~~~~~~~~~

To create plugin (**Plugin Provider**)
~~~~~~~~~~~~~~~~ 
g++ test_dummy_plugin.cpp -std=c++17 -fPIC -shared -o libPlugin.so 
~~~~~~~~~~~~~~~~

To use the plugin (**Client**)
~~~~~~~~~~~~~~~~
./a.out libPlugin.so 
~~~~~~~~~~~~~~~~

#### Explaination 
Host uses plugin_create_helper.h, plugin_load_helper.h, dummy_plugin_interface.h, and test_host.cpp
Plugin provider uses plugin_create_helper.h, dummy_plugin_interface.h.  The reason that Plugin provider 
also need plugin_create_helper.h is because there needs to be some extra information embeded in their plugin so that
Host can find their implementation (symbol) when client tries to use the plugin. Macro JCY_PLUGIN_DEFINE and JCY_PLUGIN_EMBED 
are used to embed the information of the plugin that Plugin provider wrote. Since Host provides the macros and plugin interfaces,
Host knows how to look for the plugin implementation that Plugin provider provides.

#### Pros
You can embed as many different plugin as you like in a single dynamic library.

#### Cons
The same plugin can't exist twice in a .so file. In another word,  plugin interfaces must be different within a dynamic library, otherwise, it will cause redefined symbol error.

#### Disclaimer
I only spent a day to put this together. So it is pretty rough. The goal is to show how a simple C++ plugin work.

#### Reference
https://sourcey.com/articles/building-a-simple-cpp-cross-platform-plugin-system
https://github.com/FFmpeg/nv-codec-headers
