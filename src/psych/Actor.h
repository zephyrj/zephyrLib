#pragma once

#include <Schema.h>

namespace zephyr { namespace psych {

class Actor
{
public:
  Actor(std::string name,
        int assimilation_tendency = 50,
        int accommodation_tendency = 50)
        : m_name(std::move(name),
          m_assimilation_tendency(assimilation_tendency),
          m_accommodation_tendency(accommodation_tendency),
          m_state(EQUALIBRIUM)

  ~Actor() = default;

private:
  std::string m_name;

  Schema m_schema;

  // likelihood of fitting new info into existing schema. antonym would be prejudice
  int m_assimilation_tendency;
  // likelihood of creating a new schema to accommodate new info
  int m_accommodation_tendency;

  enum m_state {
    EQUALIBRIUM = 0,
    DISEQUALIBRIUM
  };

};

}}