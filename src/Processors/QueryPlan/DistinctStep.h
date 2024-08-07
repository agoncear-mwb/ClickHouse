#pragma once
#include <Processors/QueryPlan/ITransformingStep.h>
#include <QueryPipeline/SizeLimits.h>

namespace DB
{

/// Execute DISTINCT for specified columns.
class DistinctStep : public ITransformingStep
{
public:
    DistinctStep(
        const DataStream & input_stream_,
        const SizeLimits & set_size_limits_,
        UInt64 limit_hint_,
        const Names & columns_,
        /// If is enabled, execute distinct for separate streams. Otherwise, merge streams.
        bool pre_distinct_);

    String getName() const override { return "Distinct"; }
    const Names & getColumnNames() const { return columns; }

    void transformPipeline(QueryPipelineBuilder & pipeline, const BuildQueryPipelineSettings &) override;

    void describeActions(JSONBuilder::JSONMap & map) const override;
    void describeActions(FormatSettings & settings) const override;

    bool isPreliminary() const { return pre_distinct; }

    UInt64 getLimitHint() const { return limit_hint; }

    void applyOrder(SortDescription sort_desc) { distinct_sort_desc = std::move(sort_desc); }

private:
    void updateOutputStream() override;

    SizeLimits set_size_limits;
    UInt64 limit_hint;
    const Names columns;
    bool pre_distinct;
    SortDescription distinct_sort_desc;
};

}
