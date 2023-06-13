#pragma once

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include "configuracoes.h"

AsyncWebServer server(80);

const char *PARAM_MESSAGE = "message";

bool handleFileRead(String path, AsyncWebServerRequest *request)
{
    if (path.endsWith("/"))
    {
        path += "index.html";
    }
    String contentType = "text/html";
    if (path.endsWith(".css"))
    {
        contentType = "text/css";
    }
    else if (path.endsWith(".js"))
    {
        contentType = "application/javascript";
    }
    else if (path.endsWith(".ico"))
    {
        contentType = "image/x-icon";
    }
    else if (path.endsWith(".json"))
    {
        contentType = "application/json";
    }
    File file = LittleFS.open(path, "r");

    if (file)
    {
        request->send(LittleFS, path, contentType);
        return true;
    }
    return false;
}

void setupWeb()
{
    if (!LittleFS.begin())
    {
        Serial.println("Falha ao montar o sistema de arquivos LittleFS!");
    }

    server.onNotFound([](AsyncWebServerRequest *request)
                      {
                          if (!handleFileRead(request->url(), request))
                          {

                              Serial.printf("NOT_FOUND: ");
                              if (request->method() == HTTP_GET)
                                  Serial.printf("GET");
                              else if (request->method() == HTTP_POST)
                                  Serial.printf("POST");
                              else if (request->method() == HTTP_DELETE)
                                  Serial.printf("DELETE");
                              else if (request->method() == HTTP_PUT)
                                  Serial.printf("PUT");
                              else if (request->method() == HTTP_PATCH)
                                  Serial.printf("PATCH");
                              else if (request->method() == HTTP_HEAD)
                                  Serial.printf("HEAD");
                              else if (request->method() == HTTP_OPTIONS)
                                  Serial.printf("OPTIONS");
                              else
                                  Serial.printf("UNKNOWN");
                              Serial.printf(" http://%s%s\n", request->host().c_str(), request->url().c_str());

                              if (request->contentLength())
                              {
                                  Serial.printf("_CONTENT_TYPE: %s\n", request->contentType().c_str());
                                  Serial.printf("_CONTENT_LENGTH: %u\n", request->contentLength());
                              }

                              int headers = request->headers();
                              int i;
                              for (i = 0; i < headers; i++)
                              {
                                  AsyncWebHeader *h = request->getHeader(i);
                                  Serial.printf("_HEADER[%s]: %s\n", h->name().c_str(), h->value().c_str());
                              }

                              int params = request->params();
                              for (i = 0; i < params; i++)
                              {
                                  AsyncWebParameter *p = request->getParam(i);
                                  if (p->isFile())
                                  {
                                      Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
                                  }
                                  else if (p->isPost())
                                  {
                                      Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
                                  }
                                  else
                                  {
                                      Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
                                  }
                              }

                              request->send(404);
                          } });

    // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    //           { request->send(200, "text/plain", "Hello, world"); });

    // Send a GET request to <IP>/get?message=<message>
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message); });

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message); });

    AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler("/rest/teclado", [](AsyncWebServerRequest *request, JsonVariant &json)
                                                                           {
            JsonObject jsonObj = json.as<JsonObject>();
            Serial.println(jsonObj["button"].as<const char *>()); 
            // Enviar uma resposta
            String buttons = jsonObj["button"].as<const char *>();

            JsonArray array = jsonObj["keys"].as<JsonArray>();
            for(JsonVariant v : array) {
                Serial.println(v.as<const char *>());
            }            

            // chama o cara que vai gravar as coisas passando o jsonObj
            salvaJSON(jsonObj);
            
            
            DynamicJsonDocument responseDoc(1024);
            responseDoc["status"] = "OK";
            responseDoc["message"] = "Botão recebido: " + buttons;
            String response;
            serializeJson(responseDoc, response);
            request->send(200, "application/json", response); });
    server.addHandler(handler);

    server.begin();
}
