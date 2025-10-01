#include <memory>

#include "data_access_sqlite/TaskListRepository.h"
#include "gtest/gtest.h"

class TaskListRepositoryTests : public::testing::Test {
protected:
    SqliteService service;
    std::unique_ptr<TaskListRepository> repository;

    void SetUp() override {
        service.initialize();
        repository = std::make_unique<TaskListRepository>(service);
    }
};

TEST_F(TaskListRepositoryTests, AddsAndGetsById) {
    const TaskList list(0, "List 1");
    ASSERT_TRUE(repository->add(list));

    const auto all = repository->getAll(0, 10, "");
    ASSERT_FALSE(all.empty());

    const int id = all.front().getId();
    const auto gotList = repository->getById(id);
    ASSERT_TRUE(gotList.has_value());
    EXPECT_EQ("List 1", gotList->getName());
}

TEST_F(TaskListRepositoryTests, EditesList) {
    const TaskList list(0, "List 1");
    ASSERT_TRUE(repository->add(list));

    const auto all = repository->getAll(0, 10, "");
    const int id = all.front().getId();

    const TaskList updated(id, "Updated Name");
    ASSERT_TRUE(repository->edit(updated));

    const auto gotList = repository->getById(id);
    ASSERT_TRUE(gotList.has_value());
    EXPECT_EQ("Updated Name", gotList->getName());
}

TEST_F(TaskListRepositoryTests, RemovesList) {
    const TaskList list(0, "List 1");
    ASSERT_TRUE(repository->add(list));

    const auto all = repository->getAll(0, 10, "");
    const int id = all.front().getId();

    ASSERT_TRUE(repository->remove(id));
    auto gotList = repository->getById(id);
    EXPECT_FALSE(gotList.has_value());
}

TEST_F(TaskListRepositoryTests, GetsAllWithPaginationAndFilter) {
    ASSERT_TRUE(repository->add(TaskList(0, "ALPHA")));
    ASSERT_TRUE(repository->add(TaskList(0, "BETA")));
    ASSERT_TRUE(repository->add(TaskList(0, "GAMMA")));

    auto page1 = repository->getAll(0, 2, "a");
    EXPECT_EQ(page1.size(), 2);

    auto page2 = repository->getAll(1, 2, "a");
    EXPECT_EQ(page2.size(), 1);

    auto filtered = repository->getAll(0, 10, "beta");
    ASSERT_EQ(filtered.size(), 1);
    ASSERT_EQ(filtered[0].getName(), "BETA");
}

