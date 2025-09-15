#ifndef UNTITLED_CHATVIEWMODEL_H
#define UNTITLED_CHATVIEWMODEL_H
#include <mutex>
#include <string>
#include <vector>

struct Message {
    std::string user;
    std::string message;
};

class ChatViewModel {
public:
    ChatViewModel() = default;

    void addMessage(const std::string &user, const std::string &message);

    std::vector<Message> getMessages();

private:
    std::vector<Message> _messages;
    std::mutex _mutex;
};


#endif //UNTITLED_CHATVIEWMODEL_H
