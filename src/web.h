#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

// Enable built-in ADC
ADC_MODE(ADC_VCC);

const char *plainContentType = "text/plain";
size_t len;
char buff[512];

void setupWeb()
{
    // Web server
    server.on("/", []() {
        // Format output
        len = snprintf(buff, sizeof(buff),
                       "Version: %s\nFlashChipRealSize: %i\nFlashChipId: %i\nFlashChipSizeByChipId: %i\nFreeSketchSpace: %i\nFreeHeap: %i\nVCC: %i\nCPU Freq: %i",
                       ESP.getFullVersion().c_str(),
                       ESP.getFlashChipRealSize() / 1024,
                       ESP.getFlashChipId(),
                       ESP.getFlashChipSizeByChipId(),
                       ESP.getFreeSketchSpace(),
                       ESP.getFreeHeap(),
                       ESP.getVcc(),
                       ESP.getCpuFreqMHz());

        server.send_P(200, plainContentType, buff, len);
    });

    server.on("/sleep", []() {
        const int SLEEP_TIME = 10; // seconds
        ESP.deepSleep(SLEEP_TIME * 1000000);
    });

    server.onNotFound([]() {
        server.send(404, plainContentType, "Not Found");
    });

    server.begin();
    Serial.println("HTTP server started");
}

void handleWeb()
{
    server.handleClient();
}
