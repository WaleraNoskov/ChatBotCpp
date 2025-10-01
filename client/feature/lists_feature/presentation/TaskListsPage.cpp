#include "TaskListsPage.h"

#include "ftxui/component/component.hpp"

ftxui::Element RenderTaskListsPage(const ListsFeatureState &state) {
    std::vector<ftxui::Element> items{};

    for (auto &list: state.lists) {
        items.push_back(ftxui::hbox({
            ftxui::text(list.getName()) | ftxui::bold,
            ftxui::filler(),
            ftxui::text(std::to_string(list.getTasks().size()) + " total")
        }));
    }

    return ftxui::vbox({
               ftxui::hbox(
                   ftxui::text("Task Lists") | ftxui::bold
               ),
               ftxui::separator(),
               ftxui::vbox(items)
           }) | ftxui::border;
}
