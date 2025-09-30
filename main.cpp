#include "controls/chat/ChatView.h"
#include "controls/chat/ChatViewModel.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "data_access/SqliteService.h"

int main() {
    SqliteService sqliteService{};
    sqliteService.initialize();

    ChatViewModel chatViewModel;
    ChatView chatView(chatViewModel);

    auto screen = ftxui::ScreenInteractive::TerminalOutput();

    std::thread bot_thread([&]() {
        int counter = 0;

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            chatViewModel.addMessage("Bot", "Hello! [message #" + std::to_string(counter++) + "]");
            screen.PostEvent(ftxui::Event::Custom);
        }
    });

    screen.Loop(chatView.getComponent());
    bot_thread.join();
}
