# Smart Power Monitor — Cellular Connection Recovery (ESP32)

An ESP32 firmware prototype (**Stage 1G-4C**) that simulates cellular internet monitoring, AT-command diagnostics, and automatic connection recovery for an IoT Smart Power Monitor. 

Built and tested in **Wokwi**, this project uses a software-simulated modem layer to validate network failover logic and offline mode transitions without requiring physical GSM/LTE hardware.

🔗 **[Run Live Simulation on Wokwi](YOUR_WOKWI_PROJECT_LINK_HERE)**

---

## 🚀 Key Features

* **Simulated Cellular Modem:** Mimics standard GSM/LTE AT command responses (`AT+CGATT?`, `AT+CGACT?`) and HTTP server health checks (`200 OK`) in software.
* **Automated Recovery Routine:** Executes up to **3 sequential recovery attempts** when connectivity drops, verifying network attachment and PDP data context before re-testing internet access.
* **Graceful Offline Fallback:** Automatically transitions the device into `OFFLINE MODE` if all recovery attempts fail, ensuring uninterrupted local power monitoring.
* **Hardware-Ready UART Setup:** Pre-configured with `HardwareSerial(2)` on **GPIO 17 (TX)** and **GPIO 18 (RX)** at `115200` baud for drop-in integration with physical cellular modules (e.g., SIM800L, SIM7600).

---

## 🛠️ Hardware & Pin Configuration

| Component | ESP32 Pin | Notes |
| :--- | :--- | :--- |
| **Modem TX** | `GPIO 17` | UART2 Transmit |
| **Modem RX** | `GPIO 18` | UART2 Receive |
| **Serial Monitor** | `USB / UART0` | `115200` baud |

---

## 🔄 Recovery Workflow

1. **Startup Check:** Runs an initial `INTERNET_TEST` to verify an `HTTP/1.1 200 OK` response.
2. **Failure Detection:** If the check fails or returns an `ERROR`, the system triggers `recoverConnection()`.
3. **Diagnostic Loop (Max 3 Retries):**
   * Checks cellular network registration via `AT+CGATT?` (expects `+CGATT: 1`).
   * Checks active data context via `AT+CGACT?` (expects `+CGACT: 1,1`).
   * Re-runs the HTTP connectivity check.
4. **State Transition:** Restores `ONLINE` status upon success, or switches to `OFFLINE MODE` after 3 failed attempts.

---

## 💻 How to Run

1. Open the project in **Wokwi** (or clone this repository into **VS Code** with the Wokwi extension).
2. Start the simulation and open the **Serial Monitor** at `115200` baud.
3. *(Optional)* To test failure recovery, increment a counter inside `simulateModemResponse()` to return `"ERROR"` on the first two `INTERNET_TEST` calls and observe the automatic recovery on attempt #2.
