<div align="center">

![Banner Soluções Integradas IoT](watermarked_img_16544852334658848933.png)

# 🌐 Soluções Integradas IoT (Internet of Things)

**Uma plataforma end-to-end robusta, segura e escalável para monitoramento, telemetria e automação industrial/residencial.**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Python](https://img.shields.io/badge/Python-3.10+-3776AB?style=flat&logo=python&logoColor=white)](https://www.python.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Docker](https://img.shields.io/badge/Docker-24.0+-2496ED?style=flat&logo=docker&logoColor=white)](https://www.docker.com/)
[![MQTT](https://img.shields.io/badge/MQTT-v5.0-660066?style=flat&logo=eclipse-mosquitto&logoColor=white)](https://mqtt.org/)
[![Status](https://img.shields.io/badge/Status-Active-brightgreen.svg)]()

[Visão Geral](#-sobre-o-projeto) • [Arquitetura](#-arquitetura-do-sistema) • [Protocolos & Contratos](#-protocolos--contrato-de-dados) • [API & Endpoints](#-endpoints-da-api-rest) • [Instalação](#%EF%B8%8F-instalação-e-configuração) • [Troubleshooting](#-resolução-de-problemas)

</div>

---

## 🎯 Sobre o Projeto

O **Soluções Integradas IoT** foi desenvolvido para integrar a camada física de hardware (sensores e atuadores) com o ecossistema de nuvem e inteligência de dados, garantindo comunicação de alta disponibilidade e baixa latência.

O projeto resolve o desafio de coletar dados de múltiplos nós distribuídos em ambientes hostis ou de conectividade limitada, processando métricas em tempo real e permitindo atuamento remoto seguro via WebSockets ou MQTT.

> [!NOTE]
> O projeto utiliza uma arquitetura baseada em microsserviços orientada a eventos (EDA), permitindo escalar o consumo de dados de centenas de nós sensores sem comprometer a latência da API.

### 💡 Casos de Uso detalhados
* 🏭 **IIoT (Indústria 4.0):** Sensoriamento de temperatura em motores, análise de vibração preditiva e medição de consumo elétrico por fase.
* 🏡 **Smart Home & Cidades Inteligentes:** Automação residencial, medição de qualidade do ar (CO2/Gás), controle de iluminação Mesh e presença.
* 🌾 **AgroTech:** Sensoriamento de umidade do solo em diferentes profundidades, estações meteorológicas locais e irrigação automatizada por agendamento.

---

## 🏗 Arquitetura do Sistema

```text
┌─────────────────────────┐
│ Dispositivos Embarcados │
│  (ESP32 / ESP8266 / RPi) │
└────────────┬────────────┘
             │  TLS / MQTT / HTTP
             ▼
┌─────────────────────────┐      Consumo      ┌─────────────────────────┐
│       Broker MQTT       │ ────────────────► │    Backend Service      │
│     (EMQX / Mosquitto)  │                   │  (Python FastAPI / Node)│
└─────────────────────────┘                   └────────────┬────────────┘
                                                           │
                                                           ├───► [ TimescaleDB / InfluxDB ] (Séries Temporais)
                                                           ├───► [ PostgreSQL / Redis ]    (Estado & Cache)
                                                           │
                                                           ▼
                                              ┌─────────────────────────┐
                                              │ Visualização & Atuação  │
                                              │ (React / Grafana Web)   │
                                              └─────────────────────────┘
