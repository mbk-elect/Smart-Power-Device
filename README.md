# Smart Power Monitor — Cellular Connection Recovery

**ESP32 Firmware Prototype | Stage 1G-4C**

An ESP32-based firmware prototype that simulates cellular internet monitoring, AT-command diagnostics, and automatic connection recovery for an IoT Smart Power Monitor.

Developed and tested using **Wokwi**, this project implements a software-simulated modem layer to validate network recovery logic and offline-mode transitions without requiring physical GSM/LTE hardware.

🔗 **[Run Live Simulation on Wokwi](YOUR_ACTUAL_WOKWI_PROJECT_LINK)**

---

## 🚀 Key Features

- **Simulated Cellular Modem:** Mimics standard GSM/LTE AT-command responses, including `AT+CGATT?` and `AT+CGACT?`, alongside HTTP server health checks returning `200 OK`.
- **Automated Connection Recovery:** Performs up to three sequential recovery attempts when internet connectivity is lost.
- **Network Diagnostics:** Checks cellular network attachment and Packet Data Protocol (PDP) context activation before retesting internet connectivity.
- **Graceful Offline Fallback:** Automatically transitions into `OFFLINE MODE` when all recovery attempts fail, allowing local power-monitoring operations to continue.
- **Hardware-Ready UART Configuration:** Configures `HardwareSerial(2)` on GPIO 17 (TX) and GPIO 18 (RX), operating at 115200 baud, for future integration with physical cellular modules.

## 🛠️ Hardware & Pin Configuration

| Component | ESP32 Pin | Configuration |
|---|---|---|
| Modem TX | GPIO 17 | UART2 Transmit |
| Modem RX | GPIO 18 | UART2 Receive |
| Serial Monitor | USB / UART0 | 115200 baud |

**Note:** Cellular communication is simulated in the current Wokwi prototype. Physical GSM/LTE modem integration has not been established by this simulation.

## 🔄 System Recovery Workflow

The firmware follows a structured connection-monitoring and recovery process:

1. **Startup Check:** Performs an initial `INTERNET_TEST` to verify internet connectivity through a simulated `HTTP/1.1 200 OK` response.
2. **Failure Detection:** If the connectivity test fails or returns `ERROR`, the firmware triggers `recoverConnection()`.
3. **Diagnostic and Recovery Loop:** Executes a maximum of three recovery attempts, checking:
   - Network attachment using `AT+CGATT?` (expected response: `+CGATT: 1`).
   - PDP context activation using `AT+CGACT?` (expected response: `+CGACT: 1,1`).
   - Internet connectivity through another HTTP health check.
4. **State Transition:**
   - Successful recovery restores the `ONLINE` state.
   - Three unsuccessful recovery attempts trigger `OFFLINE MODE`.

## 💻 How to Run the Project

### Option 1: Wokwi Simulation

1. Open the project using the Wokwi simulation link above.
2. Start the simulation.
3. Open the Serial Monitor.
4. Set the baud rate to **115200**.
5. Observe the connection-monitoring and recovery messages.

### Option 2: Visual Studio Code

1. Clone this repository.
2. Open the project in Visual Studio Code.
3. Install the Wokwi extension if it is not already installed.
4. Open the project and start the simulation.
5. Monitor the firmware output through the Serial Monitor.

## 🧪 Testing Connection Recovery

To test failure recovery, modify the simulated modem response logic inside `simulateModemResponse()`.

Configure the function to return `ERROR` for the first two `INTERNET_TEST` calls, then observe how the firmware executes its recovery routine.

This allows the connection-monitoring and recovery sequence to be evaluated without a physical cellular network.

## 📁 Project Structure

```text
Smart-Power-Device/
│
├── README.md
├── diagram.json
├── sketch.ino
└── wokwi-project.txt
```

## 🎯 Project Objective

This prototype is part of the development of an IoT Smart Power Monitor. Its purpose is to validate cellular connectivity monitoring, automated recovery, and offline-mode handling before integration with physical GSM/LTE hardware.

**Development Stage:** Stage 1G-4C  
**Platform:** ESP32  
**Simulation Environment:** Wokwi  
**Programming Language:** C++ (Arduino Framework)
