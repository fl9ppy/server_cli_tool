#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <functional>
#include <unordered_map>
#include "config_manager.h"

class Console {
public:
    Console();  // Constructor to initialize ConfigManager
    void run();

private:
    void registerCommands();
    void handleCommand(const std::string& input);

    std::unordered_map<std::string, std::function<void(const std::string&)>> commands;
    ConfigManager configManager; // Config manager for the console
};

#endif
