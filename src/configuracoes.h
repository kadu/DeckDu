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
    StaticJsonDocument<256> doc;

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
            StaticJsonDocument<256> doc;

            DeserializationError err = deserializeJson(doc, file);
            if (err)
            {
                Serial.println("Erro ao desserializar aquivo");
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
    StaticJsonDocument<256> doc;

    Serial.println("## Alegria");
    Serial.println(jsonObj["button"].as<const char *>());

    File file = LittleFS.open(fileName, "r+");

    DeserializationError err = deserializeJson(doc, file);
    if (err)
    {
        Serial.println("Erro ao desserializar aquivo");
        return;
    }

    if (doc.containsKey(jsonObj["button"].as<const char *>()))
    {
        const size_t CAPACITY = JSON_ARRAY_SIZE(3);
        StaticJsonDocument<CAPACITY> doc2;
        JsonArray array = doc2.to<JsonArray>();
        array.add("K");
        array.add("A");
        array.add("D");
        array.add("U");
        doc[jsonObj["button"].as<const char *>()].set(array);
        serializeJson(doc, file);
    }
    file.close();
}