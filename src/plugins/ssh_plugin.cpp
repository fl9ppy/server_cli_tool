#include "plugin_interface.h"
#include <libssh/libssh.h>
#include <iostream>
#include <string>

class SSHPlugin : public PluginInterface {
public:
    std::string getName() const override {
        return "ssh";
    }

    void execute(const std::string& command) override {
        if (command.substr(0, 7) == "connect") {
            std::string host = command.substr(8); // Extract hostname after "connect "
            connectToServer(host);
        } else {
            std::cout << "SSH Plugin received unknown command: " << command << "\n";
        }
    }

private:
    void connectToServer(const std::string& host) {
        ssh_session session = ssh_new();
        if (session == nullptr) {
            std::cerr << "Failed to create SSH session.\n";
            return;
        }

        ssh_options_set(session, SSH_OPTIONS_HOST, host.c_str());
        std::cout << "Connecting to " << host << "...\n";

        int rc = ssh_connect(session);
        if (rc != SSH_OK) {
            std::cerr << "Error connecting to " << host << ": " << ssh_get_error(session) << "\n";
            ssh_free(session);
            return;
        }

        std::cout << "Connected successfully to " << host << "!\n";

        // Authenticate (for example, with password)
        std::string password;
        std::cout << "Enter password: ";
        std::cin >> password;

        rc = ssh_userauth_password(session, nullptr, password.c_str());
        if (rc != SSH_AUTH_SUCCESS) {
            std::cerr << "Authentication failed: " << ssh_get_error(session) << "\n";
        } else {
            std::cout << "Authentication successful!\n";
        }

        ssh_disconnect(session);
        ssh_free(session);
    }
};

// Factory function for creating the plugin
extern "C" PluginInterface* createPlugin() {
    return new SSHPlugin();
}
