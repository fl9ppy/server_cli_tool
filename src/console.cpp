#include "console.h"
#include "plugin_manager.h"
#include <iostream>
#include <sstream>
#include <string>

// Global plugin manager
PluginManager pluginManager;

// Utility function to split input into command and arguments
std::vector<std::string> splitInput(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Console constructor
Console::Console() : configManager("config/config.json") {
    // Load configurations on startup
    if (!configManager.loadConfig()) {
        std::cerr << "Warning: Could not load configuration file.\n";
    }
}

// Register available commands
void Console::registerCommands() {
    commands["help"] = [](const std::string&) {
        std::cout << "Available commands:\n";
        std::cout << "  help       - Show help message\n";
        std::cout << "  exit       - Exit the CLI\n";
        std::cout << "  clear      - Clear the terminal\n";
        std::cout << "  load       - Load a plugin from a file\n";
        std::cout << "  list       - List loaded plugins\n";
        std::cout << "  use        - Use a specific plugin with a command\n";
        std::cout << "  config set - Set a configuration key and value\n";
        std::cout << "  config get - Get a configuration value by key\n";
    };

    commands["exit"] = [](const std::string&) {
        std::cout << "Goodbye!\n";
        exit(0);
    };

    commands["clear"] = [](const std::string&) {
        std::cout << "\033[2J\033[H"; // ANSI escape code to clear the terminal
    };

    commands["load"] = [](const std::string& args) {
        if (args.empty()) {
            std::cout << "Usage: load <plugin_path>\n";
            return;
        }
        std::cout << "Loading plugin from: " << args << "\n";
        pluginManager.loadPlugin(args);
    };

    commands["list"] = [](const std::string&) {
        pluginManager.listPlugins();
    };

    commands["config set"] = [this](const std::string& args) {
        auto tokens = splitInput(args);
        if (tokens.size() < 2) {
            std::cout << "Error: Missing arguments.\n";
            std::cout << "Usage: config set <key> <value>\n";
            return;
        }
        std::string key = tokens[0];
        std::string value = args.substr(key.length() + 1); // Get the rest as value
        configManager.set(key, value);
        if (configManager.saveConfig()) {
            std::cout << "Configuration saved: " << key << " = " << value << "\n";
        }
    };

    commands["config get"] = [this](const std::string& args) {
        if (args.empty()) {
            std::cout << "Error: Missing key.\n";
            std::cout << "Usage: config get <key>\n";
            return;
        }
        std::string value = configManager.get(args);
        if (value.empty()) {
            std::cout << "No value found for key: " << args << "\n";
        } else {
            std::cout << args << " = " << value << "\n";
        }
    };
}

// Dispatch commands to their handlers
void Console::handleCommand(const std::string& input) {
    auto tokens = splitInput(input);
    if (tokens.empty()) return;

    std::string baseCommand = tokens[0];
    std::string subCommand = tokens.size() > 1 ? baseCommand + " " + tokens[1] : baseCommand;
    std::string args = input.substr(subCommand.length());
    args.erase(0, args.find_first_not_of(" ")); // Trim leading spaces

    // Check for full command (e.g., "config set")
    auto it = commands.find(subCommand);
    if (it != commands.end()) {
        it->second(args);
    } else {
        std::cout << "Unknown command: " << baseCommand << "\n";
    }
}

// Run the REPL loop
void Console::run() {
    registerCommands();

    std::string input;
    std::cout << "Welcome to MyTool CLI! Type 'help' for a list of commands.\n";
    while (true) {
        std::cout << "mytool > ";
        std::getline(std::cin, input);
        handleCommand(input);
    }
}
