#include "GraphImpl.h"

namespace zephyr { namespace psych {

Schema::GraphImpl::GraphImpl() : assimilation_tendency(50),
                                 accommodation_tendency(50),
                                 attributes()
{}

Schema::GraphImpl::~GraphImpl() = default;

}}
