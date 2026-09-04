#define BLYNK_TEMPLATE_ID "TMPL3Jh0YwoNC"
#define BLYNK_TEMPLATE_NAME "smart dustbin"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// WiFi credentials
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

#define trigPin D5
#define echoPin D6
#define irPin D7
#define servoPin D4

Servo dustbinServo;
BlynkTimer timer;

long duration;
int distance;
int binLevel = 0;
bool notificationSent = false;

void ultrasonicMeasure()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    binLevel = map(distance, 15, 2, 0, 100); // 15 cm bin height
    binLevel = constrain(binLevel, 0, 100);

    Serial.print("Distance: ");
    Serial.println(distance);

    Serial.print("Bin Level: ");
    Serial.println(binLevel);

    Blynk.virtualWrite(V1, distance);
    Blynk.virtualWrite(V0, binLevel);

    if (binLevel >= 70 && !notificationSent)
    {
        Blynk.logEvent("bin_almost_full", "Dustbin 1 is almost FULL!");
        notificationSent = true;
    }

    if (binLevel < 70)
    {
        notificationSent = false;
    }
}

void checkIR()
{
    int irState = digitalRead(irPin);

    if (irState == LOW) // Hand detected
    {
        Serial.println("Hand detected - Opening lid");

        dustbinServo.write(90); // Open lid
        delay(5000);            // Keep open 5 sec
        dustbinServo.write(0);  // Close lid

        Serial.println("Lid Closed");
    }
}

void setup()
{
    Serial.begin(9600);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(irPin, INPUT);

    dustbinServo.attach(servoPin);
    dustbinServo.write(0);

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    timer.setInterval(1000L, ultrasonicMeasure);
    timer.setInterval(500L, checkIR);
}

void loop()
{
    Blynk.run();
    timer.run();
}
