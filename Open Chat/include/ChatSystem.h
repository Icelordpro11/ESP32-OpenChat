#pragma once

#include <Arduino.h>
#include <WebServer.h>

class ChatSystem
{
public:
    ChatSystem(WebServer& server);

    void SetupRoutes();

private:
    WebServer& server;

    static const int maxMessages = 5;
    static const int maxMessageLength = 120;

    String messages[maxMessages];
    int messageCount = 0;

    void ShowChat();
    void HandleMessages();
    void HandleSend();

    void AddMessage(const String& message);
    String EscapeHtml(const String& text);
};