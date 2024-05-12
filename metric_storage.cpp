
#include "metric_storage.h"

namespace tools {

MetricStorage::MetricStorage(tools::Layer layer)
    : layer_{layer}, nodes_{init_nodes(layer_)} {}

void MetricStorage::add_metrics(MetricStorage::Metrics metrics) {
  if (layer_ != Layer::Operation) {
    throw std::runtime_error{"error"};
  }

  total_ += metrics;
  counters_.increment(Layer::Operation);
  std::get<OperationNodes>(nodes_).emplace_back(std::move(metrics));
}

void MetricStorage::add_metrics(MetricStorage metrics) {
  if (!is_valid_child_node(metrics)) {
    throw std::runtime_error("invalid node");
  }

  total_ += metrics.total_;
  counters_.increment(metrics.layer_);
  counters_ += metrics.counters_;
  std::get<ChildNodes>(nodes_).emplace_back(std::move(metrics));
}

MetricStorage::Metrics MetricStorage::total() const {
  return total_;
}

Layer MetricStorage::layer() const {
  return layer_;
}

MetricStorage::Metrics MetricStorage::average(Layer layer) const {
  return total() / counters_.count(layer);
}

bool MetricStorage::is_valid_child_node(const MetricStorage &metrics) const {
  return Range::is_valid(metrics.layer_)
         && Range::index(layer_) + 1 == Range::index(metrics.layer_);
}

MetricStorage::Nodes MetricStorage::init_nodes(Layer layer) {
  if (layer == Layer::Operation) {
    return OperationNodes{};
  }

  return ChildNodes{};
}


}// namespace tools;
