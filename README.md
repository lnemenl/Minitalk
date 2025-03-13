
# Minitalk
<p align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/refs/heads/main/covers/cover-minitalk-bonus.png" alt="Minitalk Cover">
</p>
<img src="https://img.shields.io/badge/Score-125%2F125-brightgreen" alt="Score Badge">


*A signal-based communication program that transmits messages bit by bit.*

Welcome to **Minitalk**, a lightweight client-server communication system crafted for the 42 school curriculum. This project demonstrates inter-process communication using UNIX signals, allowing messages to be sent between processes with just SIGUSR1 and SIGUSR2.

---

## Features
- **Server** starts first and displays its PID
- **Client** sends messages to the server using only UNIX signals
- Messages are transmitted bit by bit using binary encoding
- Server acknowledges each bit received for reliable transmission
- Fast and efficient communication protocol
- Handles multiple clients without restarting
- Full Unicode character support
- Error handling for invalid PIDs and signal transmission failures

---

## Installation
1. Clone the repo:
   ```bash
   git clone https://github.com/lnemenl/Minitalk.git
   cd Minitalk/Minitalk
   ```
2. Compile it:
   ```bash
   make
   ```

---

## Usage
First, start the server:
```bash
./server
```

The server will display its PID, which you'll need for the client.

Then, in another terminal, run the client with the server's PID and your message:
```bash
./client [server_pid] "Your message here"
```

### Examples:
```bash
./client 4242 "Hello, Minitalk!"
./client 4242 "Unicode works too: 🚀 💻 🔥"
```

The server will receive and display the message, and the client will confirm successful transmission.

---

## How It Works
1. The client converts each character to its binary representation
2. For each bit:
   - SIGUSR1 represents a 0
   - SIGUSR2 represents a 1
3. The server reconstructs the message bit by bit
4. After each bit, the server sends an acknowledgment signal back to the client
5. The client waits for this acknowledgment before sending the next bit
6. A null terminator is sent to indicate the end of the message

This approach ensures reliable transmission even with non-queueable signals.

---

## Technical Challenges
- **Signal Reliability**: UNIX signals aren't queued, so acknowledgment mechanisms ensure no bits are lost
- **Binary Encoding**: Each character is broken down into individual bits for transmission
- **Unicode Support**: Properly handles multi-byte characters for full Unicode compatibility
- **Error Handling**: Robust error detection for invalid PIDs, signal failures, and other edge cases

---

## Allowed Functions
- write
- signal/sigaction
- sigemptyset/sigaddset
- kill
- getpid
- malloc/free
- pause
- sleep/usleep
- exit

---

## Bonus Features
- Server acknowledges every received message
- Full Unicode character support

---

## License
This project is part of the 42 school curriculum. Feel free to use it as a reference, but be aware of the academic integrity policies if you're a 42 student.

---

Built with precision and patience at 42. Completed with a perfect score of 125/125.
