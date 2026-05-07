#pragma once

const char ChatPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>Open Chat</title>
<meta name="viewport" content="width=device-width, initial-scale=1">

<style>
* { box-sizing: border-box; }

body {
    margin: 0;
    font-family: Arial, sans-serif;
    background: #0f0f0f;
    color: white;
    min-height: 100vh;
}

.app {
    max-width: 520px;
    margin: 0 auto;
    padding: 14px;
}

.header {
    text-align: center;
    padding: 14px 0;
    font-size: 24px;
    font-weight: bold;
}

.card {
    background: #181818;
    border: 1px solid #262626;
    border-radius: 18px;
    padding: 12px;
    box-shadow: 0 8px 20px rgba(0,0,0,0.35);
}

#chatBox {
    height: 45vh;
    overflow-y: auto;
    padding: 8px;
    background: #101010;
    border-radius: 14px;
    margin-bottom: 12px;
}

.empty {
    color: #666;
    text-align: center;
    margin-top: 40px;
    font-size: 14px;
}

.message {
    background: #252525;
    padding: 9px 12px;
    border-radius: 14px;
    margin-bottom: 8px;
    font-size: 14px;
    line-height: 1.3;
    word-break: break-word;
}

#msg {
    width: 100%;
    height: 44px;
    padding: 0 14px;
    border: none;
    outline: none;
    border-radius: 13px;
    background: #242424;
    color: white;
    font-size: 15px;
    margin-bottom: 9px;
}

button {
    width: 100%;
    height: 44px;
    border: none;
    border-radius: 13px;
    background: #2d7dff;
    color: white;
    font-size: 15px;
    font-weight: bold;
}

button:active {
    transform: scale(0.98);
}
</style>
</head>

<body>

<div class="app">
    <div class="header">Open Chat</div>

    <div class="card">
        <div id="chatBox">
            <div class="empty">No messages yet</div>
        </div>

        <input id="msg" maxlength="120" placeholder="Write message...">
        <button onclick="sendMessage()">Send Message</button>
    </div>
</div>

<script>
const chatBox = document.getElementById("chatBox");
const input = document.getElementById("msg");

function loadChat() {
    fetch("/messages")
    .then(r => r.text())
    .then(t => {
        chatBox.innerHTML = t.length ? t : '<div class="empty">No messages yet</div>';
        chatBox.scrollTop = chatBox.scrollHeight;
    });
}

function sendMessage() {
    const msg = input.value.trim();
    if (!msg) return;

    fetch("/send?msg=" + encodeURIComponent(msg))
    .then(() => {
        input.value = "";
        loadChat();
    });
}

input.addEventListener("keydown", e => {
    if (e.key === "Enter") sendMessage();
});

setInterval(loadChat, 1000);
loadChat();
</script>

</body>
</html>
)rawliteral";