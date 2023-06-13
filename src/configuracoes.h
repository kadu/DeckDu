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
        Serial.println("Arquivo existe");
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

            if (!doc.containsKey("button") || !doc.containsKey("keys"))
            {
                Serial.println("Não contem a chave button ou key");
                break;
            }

            Serial.print(doc["button"].as<const char *>());
            Serial.print(" ");
            Serial.println(doc["keys"].as<const char *>());
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
}