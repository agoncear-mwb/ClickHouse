#include "StorageLoop.h"
#include <Interpreters/DatabaseCatalog.h>
#include <Databases/IDatabase.h>
#include <Interpreters/Context.h>
#include <Common/Exception.h>
#include <Storages/StorageFactory.h>
#include <Processors/QueryPlan/QueryPlan.h>
#include <Processors/QueryPlan/BuildQueryPipelineSettings.h>
#include <Processors/QueryPlan/Optimizations/QueryPlanOptimizationSettings.h>
#include <Storages/checkAndGetLiteralArgument.h>
#include <Parsers/ASTSelectQuery.h>
#include <Storages/SelectQueryInfo.h>


namespace DB
{
namespace ErrorCodes
{

}
StorageLoop::StorageLoop(
    const StorageID & table_id_,
    StoragePtr inner_storage_)
    : IStorage(table_id_)
    , inner_storage(std::move(inner_storage_))
{
    StorageInMemoryMetadata storage_metadata = inner_storage->getInMemoryMetadata();
    setInMemoryMetadata(storage_metadata);
}


void StorageLoop::read(
    QueryPlan & query_plan,
    const Names & column_names,
    const StorageSnapshotPtr & storage_snapshot,
    SelectQueryInfo & query_info,
    ContextPtr context,
    QueryProcessingStage::Enum processed_stage,
    size_t max_block_size,
    size_t num_streams)
{

    query_info.optimize_trivial_count = false;

    inner_storage->read(query_plan,
                        column_names,
                        storage_snapshot,
                        query_info,
                        context,
                        processed_stage,
                        max_block_size,
                        num_streams);
}

void registerStorageLoop(StorageFactory & factory)
{
    factory.registerStorage("Loop", [](const StorageFactory::Arguments & args)
                            {
                                StoragePtr inner_storage;
                                return std::make_shared<StorageLoop>(args.table_id, inner_storage);
                            });
}
}
