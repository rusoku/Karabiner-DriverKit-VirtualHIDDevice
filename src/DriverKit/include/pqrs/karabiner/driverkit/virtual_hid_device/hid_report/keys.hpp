#pragma once

namespace pqrs {
namespace karabiner {
namespace driverkit {
namespace virtual_hid_device {
namespace hid_report {

class __attribute__((packed)) keys final {
public:
  keys(void) : keys_{} {}

  const uint8_t (&get_raw_value(void) const)[32] {
    return keys_;
  }

  bool empty(void) const {
    for (const auto& k : keys_) {
      if (k != 0) {
        return false;
      }
    }
    return true;
  }

  void clear(void) {
    memset(keys_, 0, sizeof(keys_));
  }

  void insert(uint8_t key) {
    if (!exists(key)) {
      for (auto&& k : keys_) {
        if (k == 0) {
          k = key;
          return;
        }
      }
    }
  }

  void erase(uint8_t key) {
    for (auto&& k : keys_) {
      if (k == key) {
        k = 0;
      }
    }
  }

  bool exists(uint8_t key) const {
    for (const auto& k : keys_) {
      if (k == key) {
        return true;
      }
    }

    return false;
  }

  size_t count(void) const {
    size_t result = 0;
    for (const auto& k : keys_) {
      if (k) {
        ++result;
      }
    }
    return result;
  }

  bool operator==(const keys& other) const { return (memcmp(this, &other, sizeof(*this)) == 0); }
  bool operator!=(const keys& other) const { return !(*this == other); }

private:
  uint8_t keys_[32];
};

} // namespace hid_report
} // namespace virtual_hid_device
} // namespace driverkit
} // namespace karabiner
} // namespace pqrs
