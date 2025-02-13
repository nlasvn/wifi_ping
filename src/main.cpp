#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Ping.h>

// Ao invés da gente fazer as funções aqui em cima, a gente faz elas lá em baixo
// e faz as declarações aqui, assim elas estarão no escopo quando forem chamadas
// no setup
void conectaWiFi();
void verificaSite();

const char *ssid = "IoT-Senac";
const char *password = "Senac@2025";

const char *site[] = {"www.senactaboao.com.br", "www.google.com.br", "www.marcoscosta.eti.br"};

void setup()
{
  Serial.begin(115200);
  conectaWiFi();
  Serial.println("====================================");
  verificaSite();
}

void loop()
{
}

void conectaWiFi()
{
  Serial.print("Conectando em ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("Endereço de IP: ");
  Serial.print(WiFi.localIP());
}

void verificaSite()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi não está conectado. Não será possível realizar o ping.");
    return;
  }

  for (int x = 0; x < sizeof(site) / sizeof(site[0]); x++)
  {
    Serial.println("Pingando o site: ");
    Serial.print(String(site[x]));

    bool success = Ping.ping(site[x], 5);

    if (!success)
    {
      Serial.println("O ping falhou!");
    }
    else
    {
      Serial.println("Ping no site foi realizado com sucesso!");
    }
    Serial.println("==================================");
  }
}