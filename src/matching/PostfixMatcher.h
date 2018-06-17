#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stack>

namespace zephyr { namespace matching {

template <typename TypeToMatchAgainst>
class PostfixQuery
{
public:
  PostfixQuery() = default;
  virtual ~PostfixQuery() = default;

  bool matches(const TypeToMatchAgainst& matchAgainst)
  {
    if (m_assertions.empty())
    {
      throw exception::EmptyQuery();
    }

    if (m_conjunctions.empty())
    {
      for (const auto& filterElement : m_assertions)
      {
        bool match = filterElement->applyTo(matchAgainst);
        if (match) return true;
      }
      return false;
    }

    if (!m_matchStack.empty())
    {
      while (!m_matchStack.empty())
      {
        m_matchStack.pop();
      }
    }

    for (auto nextElement : m_queryOrder)
    {
      if (filterElementisConjunction(nextElement))
      {
        const auto& conjunction = m_conjunctions.at(getConjuctionIndex(nextElement));

        if (m_matchStack.size() < 2)
        {
          if (conjunction == filter::Conjunction::AND)
          {
            throw exception::InvalidQuery("Not enough operands to perform AND conjunction");
          }
          else if (conjunction == filter::Conjunction::OR)
          {
            throw exception::InvalidQuery("Not enough operands to perform OR conjunction");
          }
        }

        auto first = m_matchStack.top();
        m_matchStack.pop();

        auto second = m_matchStack.top();
        m_matchStack.pop();

        if (conjunction == filter::Conjunction::AND)
        {
          m_matchStack.push((second && first));
        }
        else
        {
          m_matchStack.push((second || first));
        }
      }
      else
      {
        m_matchStack.push(m_assertions.at(getFilterIndex(nextElement))->applyTo(message));
      }
    }

    while (!m_matchStack.empty())
    {
      auto matchSuccess = m_matchStack.top();
      if (!matchSuccess) return false;
      m_matchStack.pop();
    }

    return true;
  }

  PostfixQuery& add_assertion(std::unique_ptr<Assertion<TypeToMatchAgainst>> assertion)
  {
    m_assertions.push_back(std::move(filter));
    m_queryOrder.push_back(m_assertions.size());
    return *this;
  }

  PostfixQuery& add_conjunction(Conjunction conjunction)
  {
    if (m_queryOrder.size() < 2) throw exception::InvalidQuery("Insufficient operands to perform conjunction on");

    m_conjunctions.push_back(conjunction);
    m_queryOrder.push_back(-(m_conjunctions.size()));
    return *this;
  }

  PostfixQuery& AND()
  {
    if (m_queryOrder.size() < 2) throw exception::InvalidQuery("Insufficient operands to perform AND conjunction on");

    m_conjunctions.push_back(filter::Conjunction::AND);
    m_queryOrder.push_back(-(m_conjunctions.size()));
    return *this;
  }

  PostfixQuery& OR()
  {
    if (m_queryOrder.size() < 2) throw exception::InvalidQuery("Insufficient operands to perform OR conjunction on");

    m_conjunctions.push_back(filter::Conjunction::OR);
    m_queryOrder.push_back(-(m_conjunctions.size()));
    return *this;
  }

  void clear()
  {
    m_assertions.clear();
    m_conjunctions.clear();
    m_queryOrder.clear();
  }

private:
  bool filterElementIsConjunction(int elementNumber)
  {
    if (elementNumber < 0) return true;
    return false;
  }

  unsigned int getConjunctionIndex(int orderNumber)
  {
    // Need to subtract one because the vector index starts from 0
    return (abs(orderNumber))-1;
  }

  unsigned int getFilterIndex(unsigned int orderNumber)
  {
    // Need to subtract one because the vector index starts from 0
    return (orderNumber)-1;
  }

private:
  std::vector<std::unique_ptr<Assertion<TypeToMatchAgainst>>> m_assertions;
  std::vector<Conjunction> m_conjunctions;

  std::deque<int> m_queryOrder;

  std::stack<bool> m_matchStack;

};

}}