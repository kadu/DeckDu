#pragma once

#include <LittleFS.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "global.h"

String fileName = "/keys.json";
void setupConfig();
void loopConfig();
void salvaJSON(JsonObject jsonObj);

void setupConfig()
{
    DynamicJsonDocument doc(512);

    /*
    Verificar se o arquivo existe, se não, criar um arquivo em branco
    se existir, abrir o arquivo e ler o conteudo deixando as variaveis
    já setadas
    */

    if (!LittleFS.begin())
    {
        Serial.println("Falha ao montar o sistema de arquivos LittleFS!");
        return;
    }

    if (LittleFS.exists(fileName))
    {
        Serial.println("Lendo arquivo de configurações...");
        File file = LittleFS.open(fileName, "r");
        while (true)
        {
            DynamicJsonDocument doc(512);

            DeserializationError err = deserializeJson(doc, file);
            if (err)
            {
                Serial.println("Open - Erro ao desserializar aquivo");
                break;
            }

            for (JsonPair pair : doc.as<JsonObject>())
            {
                const char *button = pair.key().c_str();
                JsonObject buttonObject = pair.value().as<JsonObject>();

                Serial.println(button);
                Serial.println("Keys:");

                JsonArray array = buttonObject["keys"].as<JsonArray>();
                for (JsonVariant v : array)
                {
                    Serial.println(v.as<String>());
                }

                Serial.println();
            }
            Serial.println("write #####");
        }

        file.close();
    }
    else
    {
        Serial.println("Arquivo não encontrado");
    }
}

void loopConfig()
{
    // nada aqui
}

void salvaJSON(JsonObject jsonObj)
{
    DynamicJsonDocument doc(512);

    Serial.println("## Alegria");
    Serial.println(jsonObj["button"].as<const char *>());

    File file = LittleFS.open(fileName, "r");

    DeserializationError err = deserializeJson(doc, file);
    if (err)
    {
        Serial.println("Salvar - Erro ao desserializar aquivo");
        return;
    }
    file.close();
    file = LittleFS.open(fileName, "w");

    if (doc.containsKey(jsonObj["button"].as<const char *>()))
    {
        DynamicJsonDocument doc2(512);
        doc2["keys"] = jsonObj["keys"].as<JsonArray>();
        doc[jsonObj["button"].as<const char *>()].set(doc2);
    }
    else
    {
        DynamicJsonDocument doc2(512);
        doc2["keys"] = jsonObj["keys"].as<JsonArray>();

        Serial.println("Novo elemento");
        doc[jsonObj["button"].as<const char *>()] = doc2;
    }
    serializeJson(doc, file);
    file.close();
}