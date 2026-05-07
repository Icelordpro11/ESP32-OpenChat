#include "ChatSystem.h"
#include "ChatPage.h"

// Handles the captive portal routes, chat messages, and communication between users connected to the ESP32.

ChatSystem::ChatSystem(WebServer& server) : server(server)
{
}

void ChatSystem::SetupRoutes()
{
    server.on("/", [this]() { ShowChat(); });

    server.on("/generate_204", [this]() { ShowChat(); });
    server.on("/gen_204", [this]() { ShowChat(); });
    server.on("/hotspot-detect.html", [this]() { ShowChat(); });
    server.on("/library/test/success.html", [this]() { ShowChat(); });
    server.on("/connecttest.txt", [this]() { ShowChat(); });
    server.on("/ncsi.txt", [this]() { ShowChat(); });
    server.on("/fwlink", [this]() { ShowChat(); });

    server.on("/messages", [this]() { HandleMessages(); });
    server.on("/send", [this]() { HandleSend(); });

    server.onNotFound([this]() { ShowChat(); });
}

void ChatSystem::ShowChat()
{
    server.send_P(200, "text/html", ChatPage);
}

void ChatSystem::HandleMessages()
{
    String output;

    for (int i = 0; i < messageCount; i++)
        output += "<div class='message'>" + messages[i] + "</div>";

    server.send(200, "text/html", output);
}

void ChatSystem::HandleSend()
{
    String msg = server.arg("msg");
    msg.trim();

    if (msg.length() > maxMessageLength)
        msg = msg.substring(0, maxMessageLength);

    if (msg.length() > 0)
        AddMessage(EscapeHtml(msg));

    server.send(200, "text/plain", "OK");
}

void ChatSystem::AddMessage(const String& message)
{
    if (messageCount < maxMessages)
    {
        messages[messageCount] = message;
        messageCount++;
        return;
    }

    for (int i = 0; i < maxMessages - 1; i++)
        messages[i] = messages[i + 1];

    messages[maxMessages - 1] = message;
}

String ChatSystem::EscapeHtml(const String& text)
{
    String result = text;

    result.replace("&", "&amp;");
    result.replace("<", "&lt;");
    result.replace(">", "&gt;");
    result.replace("\"", "&quot;");
    result.replace("'", "&#39;");

    return result;
}