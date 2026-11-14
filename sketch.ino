#define MODEM_TX 17
#define MODEM_RX 18

HardwareSerial ModemSerial(2);

// ==========================================
// SIMULATED MODEM RESPONSE
// ==========================================

String simulateModemResponse(String command) {

  // Normal Internet test
  if (command == "INTERNET_TEST") {
    return "HTTP/1.1 200 OK\r\nSERVER: TEST_SERVER\r\n";
  }

  // Simulated cellular attachment
  if (command == "AT+CGATT?") {
    return "+CGATT: 1\r\nOK";
  }

  // Simulated data connection
  if (command == "AT+CGACT?") {
    return "+CGACT: 1,1\r\nOK";
  }

  return "OK";
}


// ==========================================
// SEND COMMAND
// ==========================================

String sendCommand(String command) {

  Serial.print(">> ");
  Serial.println(command);

  String response = simulateModemResponse(command);

  delay(1000);

  Serial.print("<< ");
  Serial.println(response);

  return response;
}


// ==========================================
// CHECK INTERNET CONNECTION
// ==========================================

bool checkInternetConnection() {

  Serial.println();
  Serial.println("Checking Internet connection...");

  String response = sendCommand("INTERNET_TEST");

  if (response.indexOf("200 OK") != -1 &&
      response.indexOf("ERROR") == -1) {

    Serial.println("Internet connection: OK✅");

    return true;
  }

  Serial.println("Internet connection: FAILED❌");

  return false;
}


// ==========================================
// CONNECTION RECOVERY
// ==========================================

bool recoverConnection() {

  const int MAX_RETRIES = 3;

  Serial.println();
  Serial.println("======================================");
  Serial.println("     CONNECTION RECOVERY STARTED");
  Serial.println("======================================");

  for (int attempt = 1; attempt <= MAX_RETRIES; attempt++) {

    Serial.print("Recovery attempt #");
    Serial.println(attempt);

    delay(2000);

    // Check cellular attachment
    String attachResponse = sendCommand("AT+CGATT?");

    if (attachResponse.indexOf("+CGATT: 1") == -1 ||
        attachResponse.indexOf("ERROR") != -1) {

      Serial.println("Cellular attachment failed.");
      continue;
    }

    // Check data context
    String dataResponse = sendCommand("AT+CGACT?");

    if (dataResponse.indexOf("+CGACT: 1,1") == -1 ||
        dataResponse.indexOf("ERROR") != -1) {

      Serial.println("Data connection failed.");
      continue;
    }

    // Test Internet
    if (checkInternetConnection()) {

      Serial.println();
      Serial.println("======================================");
      Serial.println(" CONNECTION RESTORED");
      Serial.println("======================================");

      return true;
    }

    Serial.println("Recovery attempt failed.");
  }

  Serial.println();
  Serial.println("======================================");
  Serial.println(" ALL RECOVERY ATTEMPTS FAILED");
  Serial.println(" ENTERING OFFLINE MODE......");
  Serial.println("======================================");

  return false;
}


// ==========================================
// SETUP
// ==========================================

void setup() {

  Serial.begin(115200);

  ModemSerial.begin(
    115200,
    SERIAL_8N1,
    MODEM_RX,
    MODEM_TX
  );

  Serial.println();
  Serial.println("======================================");
  Serial.println("       SMART POWER MONITOR");
  Serial.println("       STAGE 1G-4C");
  Serial.println("       CONNECTION RECOVERY");
  Serial.println("======================================");

  Serial.println();

  // Initial Internet check
  if (checkInternetConnection()) {

    Serial.println();
    Serial.println("SYSTEM STATUS: ONLINE🟢");

  } else {

    Serial.println();
    Serial.println("SYSTEM STATUS: CONNECTION LOST🔴");

    bool recovered = recoverConnection();

    if (recovered) {

      Serial.println();
      Serial.println("SYSTEM STATUS: ONLINE");

    } else {

      Serial.println();
      Serial.println("SYSTEM STATUS: OFFLINE MODE🚫");

    }
  }
}


// ==========================================
// LOOP
// ==========================================

void loop() {

  delay(5000);
}




int internetTestCount = 0;

if (command == "INTERNET_TEST") {

    internetTestCount++;

    if (internetTestCount < 3) {
        return "ERROR";
    }

    return "HTTP/1.1 200 OK\r\nSERVER: TEST_SERVER\r\n";
}