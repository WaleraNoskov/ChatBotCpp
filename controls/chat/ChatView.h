#ifndef UNTITLED_CHATVIEW_H
#define UNTITLED_CHATVIEW_H
#include "ChatViewModel.h"
#include "ftxui/component/component_base.hpp"


class ChatView {
public:
    explicit ChatView(ChatViewModel &viewModel);

    ftxui::Component getComponent();

private:
    ChatViewModel &_viewModel;
    std::string _inputText;
    ftxui::Component _input;
    ftxui::Component _sendButton;
    ftxui::Component _container;
    ftxui::Component _renderer;
};


#endif //UNTITLED_CHATVIEW_H
