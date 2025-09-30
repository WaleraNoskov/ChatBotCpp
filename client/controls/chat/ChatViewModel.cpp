#include "ChatViewModel.h"

void ChatViewModel::addMessage(const std::string &user, const std::string &message) {
    std::lock_guard lock(_mutex);
    _messages.push_back({user, message});
}

std::vector<Message> ChatViewModel::getMessages() {
    std::lock_guard lock(_mutex);
    return _messages;
}
