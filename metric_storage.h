
#ifndef COUNTERS_METRIC_STORAGE_H
#define COUNTERS_METRIC_STORAGE_H

#include "counter_array.h"
#include "index_range.h"


#include <vector>
#include <variant>

namespace tools {

enum class Layer : uint8_t {
    Model,
    Block,
    Operation,
};

struct OperationMetrics {
    uint64_t clock = 0;

    constexpr auto &operator+=(const OperationMetrics &rhs) noexcept {
      clock += rhs.clock;
      return *this;
    }

    friend constexpr OperationMetrics operator+(OperationMetrics lhs, const OperationMetrics &rhs) noexcept {
      lhs += rhs;
      return lhs;
    }

    constexpr OperationMetrics &operator/=(std::size_t cnt) noexcept {
      clock /= cnt;
      return *this;
    }

    friend constexpr OperationMetrics operator/(OperationMetrics lhs, std::size_t cnt) noexcept {
      lhs /= cnt;
      return lhs;
    }
};

class MetricStorage {
public:
    using Metrics = OperationMetrics;

    explicit MetricStorage(Layer layer);

    void add_metrics(Metrics metrics);
    void add_metrics(MetricStorage metrics);

    [[nodiscard]] Metrics total() const;
    [[nodiscard]] Metrics average(Layer layer) const;
    [[nodiscard]] Layer layer() const;

private:
    using Range = IndexRange<Layer, Layer::Model, Layer::Operation>;
    using LayerCounters = CounterArray<uint64_t, Range>;
    using OperationNodes = std::vector<Metrics>;
    using ChildNodes = std::vector<MetricStorage>;
    using Nodes = std::variant<ChildNodes, OperationNodes>;

    [[nodiscard]] bool is_valid_child_node(const MetricStorage &metrics) const;

    static Nodes init_nodes(Layer layer);

    Layer layer_;
    Metrics total_{};
    LayerCounters counters_{};
    Nodes nodes_{};
};


} //namespace;




#endif //COUNTERS_METRIC_STORAGE_H
