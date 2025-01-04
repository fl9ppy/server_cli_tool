#include "config_manager.h"
#include <fstream>
#include <iostream>

ConfigManager::ConfigManager(const std::string& configFilePath) : configFilePath(configFilePath) {}

bool ConfigManager::loadConfig() {
    std::ifstream file(configFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open configuration file: " << configFilePath << "\n";
        return false;
    }
    file >> configData;
    file.close();
    return true;
}

bool ConfigManager::saveConfig() {
    std::ofstream file(configFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to write to configuration file: " << configFilePath << "\n";
        return false;
    }
    file << configData.dump(4); // Pretty-print with 4 spaces
    file.close();
    return true;
}

void ConfigManager::set(const std::string& key, const std::string& value) {
    configData[key] = value;
}

std::string ConfigManager::get(const std::string& key) const {
    if (configData.contains(key)) {
        return configData[key];
    }
    return "";
}
