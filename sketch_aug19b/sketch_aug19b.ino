#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Wi-Fi credentials
#define WIFI_SSID "Hindustan Timber And Steel"
#define WIFI_PASSWORD "Rishabh@132"

// Firebase credentials
#define API_KEY "AIzaSyDaqyBSqjt3DY0HP_f8rnTPbRJO_KoAp_Y"
#define DATABASE_URL "https://water-flow-management-default-rtdb.firebaseio.com/"
#define USER_EMAIL "rishabhsharma995660@gmail.com"
#define USER_PASSWORD "Rishabh@123"

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
    Serial.begin(9000);

    // Connect to Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());

    // Firebase initialization
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    config.token_status_callback = tokenStatusCallback;  // Updated function
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    Firebase.setDoubleDigits(5);
}

void loop() {
    int t = random(1, 100);

    if (Firebase.ready()) {
        Serial.printf("Set Water Level (%)... %s\n", Firebase.setFloat(fbdo, "/Data/WaterLevel", t) ? "ok" : fbdo.errorReason().c_str());
        Serial.printf("Get Temperature... %s\n", Firebase.getFloat(fbdo, "/Data/WaterLevel") ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());
    }
    delay(1000);
    
    Serial.printf(String(fbdo.to<float>()).c_str());
    delay(1000);
}

// Simplified token status callback function
void tokenStatusCallback(TokenInfo info) {
    Serial.println("Token Info:");
    Serial.print("Status: ");
    Serial.println(info.status);
    Serial.print("Error code: ");
    Serial.println(info.error.code);
    Serial.print("Error message: ");
    Serial.println(info.error.message.c_str());
}
