#pragma once

#include <memory>
#include <string>
#include "AbstractDatabaseFactory.h"

class PostgresqlFactory : public AbstractDatabaseFactory
{
public:
    PostgresqlFactory() = default;
    std::unique_ptr<DatabaseConnection> create() override;
};
