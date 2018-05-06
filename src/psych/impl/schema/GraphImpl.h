#pragma once

#include <Schema.h>

#include "boost/variant.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/exception.hpp>

namespace zephyr { namespace psych {

class Schema::GraphImpl final
{
public:
  GraphImpl();
  ~GraphImpl();

private:
  struct concept_definition
  {
    std::string identifier;
    std::unique_ptr<GraphImpl> schema;
  };

  struct association_definition
  {
    enum type {
      CONTIGUITY,
      SIMILARITY,
      CONTRAST
    };
    int strength;
  };

  using Schema = boost::adjacency_list<boost::setS, boost::vecS, boost::bidirectionalS, concept_definition, association_definition>;

  using Concept = Schema::vertex_descriptor;
  using ConceptIterator = boost::graph_traits<Schema>::vertex_iterator;

  using Association = Schema::edge_descriptor;
  using AssociationIterator =  boost::graph_traits<Schema>::adjacency_iterator;

  // likelihood of fitting new info into existing schema. antonym would be prejudice
  int assimilation_tendency;
  // likelihood of creating a new schema to accommodate new info
  int accommodation_tendency;

  std::unordered_multimap<std::string, boost::variant<int, std::string>> attributes;

  enum state {
    EQUALIBRIUM = 0,
    DISEQUALIBRIUM
  };

};

}}


