#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#include <string>

class PluginInterface {
public:
    virtual ~PluginInterface() {}

    // Plugin name
    virtual std::string getName() const = 0;

    // Command execution
    virtual void execute(const std::string& command) = 0;
};

extern "C" PluginInterface* createPlugin();

#endif
