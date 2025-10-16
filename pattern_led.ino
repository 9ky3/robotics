int ledPin = 13;
int slowDelay = 1000;
int fastDelay = 200;

String pattern[20];  // store up to 20 commands
int patternLength = 0;
bool running = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Type a pattern like: slow fast slow fast");
  Serial.println("Then type 'start' to begin or 'stop' to end.");
}

void loop() {
  // Check if something is typed
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.equalsIgnoreCase("start")) {
      if (patternLength == 0) {
        Serial.println("No pattern set! Type a pattern first.");
      } else {
        running = true;
        Serial.println("Starting pattern...");
      }
    } 
    else if (input.equalsIgnoreCase("stop")) {
      running = false;
      Serial.println("Pattern stopped.");
    } 
    else {
      // Store the pattern
      patternLength = 0;
      int startIdx = 0;
      while (startIdx < input.length()) {
        int spaceIdx = input.indexOf(' ', startIdx);
        if (spaceIdx == -1) spaceIdx = input.length();
        String cmd = input.substring(startIdx, spaceIdx);
        cmd.trim();
        if (cmd.length() > 0 && patternLength < 20) {
          pattern[patternLength++] = cmd;
        }
        startIdx = spaceIdx + 1;
      }

      Serial.print("Pattern saved: ");
      for (int i = 0; i < patternLength; i++) {
        Serial.print(pattern[i]);
        Serial.print(" ");
      }
      Serial.println();
    }
  }

  // Run pattern if active
  if (running) {
    for (int i = 0; i < patternLength; i++) {
      if (!running) break;  // if stopped mid-sequence
      if (pattern[i].equalsIgnoreCase("slow")) {
        blinkOnce(slowDelay);
      } else if (pattern[i].equalsIgnoreCase("fast")) {
        blinkOnce(fastDelay);
      }
    }
  }
}

void blinkOnce(int speed) {
  digitalWrite(ledPin, HIGH);
  delay(speed);
  digitalWrite(ledPin, LOW);
  delay(speed);
}
