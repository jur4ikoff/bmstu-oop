#pragma once

#include <memory>
#include <string>
#include "AbstractDatabaseFactory.h"

class SqliteFactory : public AbstractDatabaseFactory
{
public:
    SqliteFactory() = default;
    std::unique_ptr<DatabaseConnection> create() override;
};
