# Contextualização 

O objetivo da atividade é a coleta de potência do sinal WiFi em dBM em uma rede Wi-Fi. Após a coleta dos valores, as informações deverão ser exibidas no terminal serial, além de uma plataforma online. Na plataforma, as informações deverão ser exibidas por meio de um gráfico, e diferentes testes deverão ser realizados, incluindo a simulação de uma gaiola de Faraday.

# Análise do código

```C++
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "XXXXXXXX";
const char* password = "XXXXXXXX";
const char* ubidotsToken = "XXXXXXX";
const char* deviceLabel = "esp32"; 
```

Esse primeiro trecho de código serve para a definição das credenciais, tanto do Wi-Fi quanto da conexão ao Ubidots, plataforma online utilizada para a criação do dashboard.

```C++
    String url = "http://industrial.api.ubidots.com/api/v1.6/devices/";
    url += deviceLabel;

    String payload = "{\"rssi\":";
    payload += rssi;
    payload += ",\"tempo\":";
    payload += tempo;
    payload += "}";
```

Já aqui define o payload, que se trata das informações que serão enviadas via protocolo MQTT. Na definição incial, tanto o tempo quanto a medida do sinal (em dBm) eram enviadas. No entanto, o próprio Ubidots é responsável por controlar a variável do tempo, inutilizando a função do envio da informação em específico.

```C++
    int httpResponseCode = http.POST(payload);

    Serial.print("Enviando para Ubidots: ");
    Serial.println(payload);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
```

Por fim, esse outro trecho é responsável pelo envio do payload para o Ubidots, utilizando o método POST.

O código completo está disponível no arquivo code.ino, presente no repositório.

# Vídeo demonstrativo 

O vídeo demonstrativo pode ser encontrado [aqui.](https://youtu.be/pAjnRIZkciI)