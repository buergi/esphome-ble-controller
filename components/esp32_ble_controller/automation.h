#pragma once

#include <memory>

#include "esphome/core/automation.h"
#include "esphome/core/optional.h"

#include "esp32_ble_controller.h"

using std::shared_ptr;

namespace esphome {
namespace esp32_ble_controller {

// authentication ///////////////////////////////////////////////////////////////////////////////////////////////

/// Trigger for showing the pass key during authentication with a client.
class BLEControllerShowPassKeyTrigger : public Trigger<std::string> {
public:
  BLEControllerShowPassKeyTrigger(ESP32BLEController* controller) {
    controller->add_on_show_pass_key_callback([this](string pass_key) {
      this->trigger(pass_key);
    });
  }
};

/// Trigger that is fired when authentication with a client is completed (either with success or failure).
class BLEControllerAuthenticationCompleteTrigger : public Trigger<bool> {
public:
  BLEControllerAuthenticationCompleteTrigger(ESP32BLEController* controller) {
    controller->add_on_authentication_complete_callback([this](bool success) {
      this->trigger(success);
    });
  }
};

// connect & disconnect ///////////////////////////////////////////////////////////////////////////////////////////////

/// Trigger that is fired when the BLE server has connected to a client.
class BLEControllerServerConnectedTrigger : public Trigger<> {
public:
  BLEControllerServerConnectedTrigger(ESP32BLEController* controller) {
    controller->add_on_connected_callback([this]() {
      this->trigger();
    });
  }
};

/// Trigger that is fired when the BLE server has disconnected from a client.
class BLEControllerServerDisconnectedTrigger : public Trigger<> {
public:
  BLEControllerServerDisconnectedTrigger(ESP32BLEController* controller) {
    controller->add_on_disconnected_callback([this]() {
      this->trigger();
    });
  }
};

// custom command execution ///////////////////////////////////////////////////////////////////////////////////////////////

class BLECustomCommandResultSender {
public:
  void operator=(const string& result) { global_ble_controller->send_command_result(result); }
};

/// Trigger that is fired when a custom command is executed.
class BLEControllerCustomCommandExecutionTrigger : public Trigger<std::vector<std::string>, BLECustomCommandResultSender> {
public:
  BLEControllerCustomCommandExecutionTrigger(ESP32BLEController* controller) {}
};

} // namespace esp32_ble_controller
} // namespace esphome
