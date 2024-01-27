#pragma once

#include "esphome/components/input_datetime/input_datetime.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"
#include "esphome/core/preferences.h"

namespace esphome {
namespace template_ {

struct TemplateInputDatetimeRTCValue {
  ESPTime value;
  bool has_date{false};
  bool has_time{false};
};

class TemplateInputDatetime : public input_datetime::InputDatetime, public PollingComponent {
 public:
  void set_template(std::function<optional<std::string>()> &&f) { this->f_ = f; }

  void setup() override;
  void update() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

  Trigger<ESPTime> *get_set_trigger() const { return set_trigger_; }
  void set_optimistic(bool optimistic) { optimistic_ = optimistic; }

  void set_initial_value(std::string initial_value) {
    if (!ESPTime::strptime(initial_value, initial_value_)) {
      // wrong fromat, should be handled by cv allready;
    }
  }
  void set_has_date(bool initial_has_date) { has_date = initial_has_date; }
  void set_has_time(bool initial_has_time) { has_time = initial_has_time; }
  void set_restore_value(bool restore_value) { this->restore_value_ = restore_value; }

 protected:
  void control(ESPTime) override;
  bool optimistic_{false};
  ESPTime initial_value_{0};
  bool restore_value_{false};
  Trigger<ESPTime> *set_trigger_ = new Trigger<ESPTime>();
  optional<std::function<optional<std::string>()>> f_;

  ESPPreferenceObject pref_;
};

}  // namespace template_
}  // namespace esphome
