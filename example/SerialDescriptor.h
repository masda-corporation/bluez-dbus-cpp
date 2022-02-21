#pragma once

#include <bluez-dbus-cpp/GattDescriptor1.h>
#include <bluez-dbus-cpp/GattCharacteristic1.h>

namespace org {
namespace bluez {

class SerialDescriptor : public GattDescriptor1
{
public:
  SerialDescriptor( std::shared_ptr<GattCharacteristic1> service, std::string name, std::string uuid, std::string variable)
    : GattDescriptor1{ move(service), move(name), move(uuid) }
  {
    value_.assign(variable.begin(), variable.end());
  }

  static SerialDescriptor* create(std::shared_ptr<GattCharacteristic1> service, std::string name, std::string uuid, std::string variable)
  {
    return new SerialDescriptor(move(service), move(name), move(uuid), move(variable));
  }

protected:
  virtual std::vector<uint8_t> ReadValue(const std::map<std::string, sdbus::Variant>& options)
  {
    return value_;
  }

  virtual sdbus::ObjectPath Characteristic()
  {
    return characteristic_->getPath();
  }

protected:
  virtual std::vector<uint8_t> Value()
  {
    return value_;
  }

  virtual std::vector<std::string> Flags()
  {
    return { "read" };
  }

protected:
  std::vector<uint8_t> value_;
};

}
}
