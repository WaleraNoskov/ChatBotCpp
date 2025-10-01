#include "../data_access_sqlite/SqliteService.h"
#include "gtest/gtest.h"

TEST(SqliteServiceTests, Initialize_CreatesTables) {
    SqliteService service{};
    EXPECT_NO_THROW(service.initialize());

    const auto database = service.getDatabase();
    ASSERT_NE(database, nullptr);

    sqlite3_stmt* stmt;
    auto sql = "select name from sqlite_master where type='table' and name='task_lists';";
    EXPECT_EQ(SQLITE_OK, sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr));
    EXPECT_EQ(SQLITE_ROW, sqlite3_step(stmt));
    sqlite3_finalize(stmt);

    stmt = nullptr;
    sql = "select name from sqlite_master where type='table' and name='tasks';";
    EXPECT_EQ(SQLITE_OK, sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr));
    EXPECT_EQ(SQLITE_ROW, sqlite3_step(stmt));
    sqlite3_finalize(stmt);
}
