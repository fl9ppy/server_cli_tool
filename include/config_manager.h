#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp> // JSON library

class ConfigManager {
public:
    ConfigManager(const std::string& configFilePath);

    bool loadConfig();  // Load configurations from file
    bool saveConfig();  // Save configurations to file
    void set(const std::string& key, const std::string& value); // Set a key-value pair
    std::string get(const std::string& key) const;             // Get a value by key

private:
    std::string configFilePath;
    nlohmann::json configData;
};

#endif
