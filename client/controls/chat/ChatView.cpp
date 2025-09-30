#include "ChatView.h"

#include "ftxui/component/component.hpp"

ChatView::ChatView(ChatViewModel &viewModel) : _viewModel(viewModel) {
    _input = ftxui::Input(&_inputText, "Enter message");

    _sendButton = ftxui::Button("Send", [&] {
        if (!_inputText.empty()) {
            _viewModel.addMessage("User", _inputText);
            _inputText.clear();
        }
    });

    _container = ftxui::Container::Horizontal({_input, _sendButton});

    _renderer = ftxui::Renderer(_container, [&] {
        ftxui::Elements messageElements;
        auto messages = _viewModel.getMessages();
        for (const auto &message: messages)
            messageElements.push_back(ftxui::text(message.user + ":" + message.message));

        return ftxui::vbox({
            ftxui::vbox(messageElements) | ftxui::border | ftxui::flex,
            ftxui::hbox({
                _input->Render() | ftxui::flex,
                _sendButton->Render()
            })
        });
    });
}

ftxui::Component ChatView::getComponent() {
    return _renderer;
}
