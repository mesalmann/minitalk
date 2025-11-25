# Minitalk

Minitalk is a simple messaging program using **UNIX signals (SIGUSR1 / SIGUSR2)** for inter-process communication.  
The client sends a string bit-by-bit, and the server reconstructs characters and prints the message.

---

## Features
- SIGUSR1 → bit 1  
- SIGUSR2 → bit 0  
- Server sends an ACK (SIGUSR1) after each bit  
- Message ends when `'\0'` is received
