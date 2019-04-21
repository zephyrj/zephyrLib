#pragma once

#include <Schema.h>

#include <unordered_map>

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
  /*!
   * Concepts are vertices within the graph (the nodes)
   */
  struct concept_definition
  {
    std::string identifier;
    std::unique_ptr<GraphImpl> schema;
  };

  /*!
   * Associations are the edges within the graph (the lines between nodes)
   */
  struct association_definition
  {
    enum type {
      /*!
       * https://en.wikipedia.org/wiki/Contiguity_(psychology)
       * Association by contiguity is the principle that ideas, memories, and experiences are linked when one is
       * frequently experienced with the other.
       * For example, if you constantly see a knife and a fork together they become linked (associated).
       * The more these two items (stimuli) are perceived together the stronger the link between them
       */
      CONTIGUITY,

      /*!
       * https://en.wikipedia.org/wiki/Similarity_(psychology)
       * Similarity refers to the psychological nearness or proximity of two mental representations
       * Similarity is not symmetric; we often prefer to state similarity in one direction.
       * For example, it feels more natural to say that 101 is like 100 than to say that 100 is like 101
       */
      SIMILARITY,

      /*!
       * This is almost the opposite of similarity; things can be linked because they significantly contrast
       * with each other. For example: black and white, rich and poor
       */
      CONTRAST

    };
    int strength;
  };

  using Schema = boost::adjacency_list<boost::setS, boost::vecS, boost::bidirectionalS, concept_definition, association_definition>;

  using Concept = Schema::vertex_descriptor;
  using ConceptIterator = boost::graph_traits<Schema>::vertex_iterator;

  using Association = Schema::edge_descriptor;
  using AssociationIterator = boost::graph_traits<Schema>::adjacency_iterator;

  std::unordered_multimap<std::string, boost::variant<int, std::string>> attributes;

};

}}


