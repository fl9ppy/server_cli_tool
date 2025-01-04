#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "plugin_interface.h"
#include <string>
#include <unordered_map>
#include <memory>

class PluginManager {
public:
    void loadPlugin(const std::string& path);    // Load a plugin from file
    void listPlugins() const;                   // List all loaded plugins
    void executeCommand(const std::string& pluginName, const std::string& command);

private:
    std::unordered_map<std::string, std::unique_ptr<PluginInterface>> plugins;
};

#endif
