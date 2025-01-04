#include "plugin_manager.h"
#include <iostream>
#include <dlfcn.h>

void PluginManager::loadPlugin(const std::string& path) {
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error loading plugin: " << dlerror() << "\n";
        return;
    }

    auto createPlugin = (PluginInterface* (*)()) dlsym(handle, "createPlugin");
    if (!createPlugin) {
        std::cerr << "Error finding symbol 'createPlugin': " << dlerror() << "\n";
        dlclose(handle);
        return;
    }

    std::unique_ptr<PluginInterface> plugin(createPlugin());
    std::string pluginName = plugin->getName();
    plugins[pluginName] = std::move(plugin);

    std::cout << "Loaded plugin: " << pluginName << "\n";
}

void PluginManager::listPlugins() const {
    std::cout << "Loaded plugins:\n";
    for (const auto& pair : plugins) {
        std::cout << "  - " << pair.first << "\n";
    }
}

void PluginManager::executeCommand(const std::string& pluginName, const std::string& command) {
    auto it = plugins.find(pluginName);
    if (it == plugins.end()) {
        std::cerr << "Plugin not found: " << pluginName << "\n";
        return;
    }

    it->second->execute(command);
}
