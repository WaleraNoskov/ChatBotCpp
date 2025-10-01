#include "client/feature/lists_feature/ListsFeatureAcions.h"
#include "client/feature/lists_feature/ListsFeatureState.h"
#include "ftxui/component/screen_interactive.hpp"
#include "client/feature/framework/Store.h"
#include "client/feature/lists_feature/ListsFeatureReducer.h"
#include "client/feature/lists_feature/presentation/TaskListsPage.h"
#include "ftxui/component/component.hpp"

int main() {
    SqliteService sqliteService{};
    sqliteService.initialize();

    TaskListRepository taskListRepository(sqliteService);
    TaskListService taskListService(taskListRepository);

    Store<ListsFeatureState, ListsFeatureAction> listsFeatureStore(
        ListsFeatureState{},
        [&](const ListsFeatureState &state, const ListsFeatureAction &action) {
            return ListsFeatureReducer(state, action, taskListService);
        });

    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    auto renderer = ftxui::Renderer([&] {
        return RenderTaskListsPage(listsFeatureStore.GetState());
    });

    listsFeatureStore.Subscribe([&] { screen.PostEvent(ftxui::Event::Custom); });
    listsFeatureStore.Dispatch(Add{"Task 1"});
    listsFeatureStore.Dispatch(Refresh{0, 10, ""});

    screen.Loop(renderer);
}
