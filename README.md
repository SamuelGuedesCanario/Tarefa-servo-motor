# Embarcatech-U4C6

Este projeto explora interfaces de comunicação do microcontrolador RP2040. O exemplo apresentado utiliza comunicação serial (USB) e I2C para interação com um display OLED 128x64 pixels monocromático.

O usuário pode interagir com a placa BitgogLab através dos botões A e B, que alternam o estado dos LEDs verde e azul, respectivamente. O status atualizado dos LEDs é exibido tanto no display OLED quanto na interface serial. Além disso, caracteres digitados via serial, sejam eles maiúsculos ou minúsculos, são exibidos no display e na interface serial. Caso seja inserido um número de 0 a 9, esse valor também será representado na matriz de LEDs WS2812.

## Funcionalidade das Teclas 🕹️

| Tecla | Função |
| ----- | ----------------------------- |
| A     | Alterna o estado do LED verde |
| B     | Alterna o estado do LED azul  |

## Hardware 🛠️

- Microcontrolador RP2040 (Raspberry Pi Pico)
- Botões tipo switch
- Display NeoPixel RGB 5x5
- Display OLED I2C 128x64 pixels
- Comunicação Serial via USB

## Software 💻

- **SDK do Raspberry Pi Pico:** Contém bibliotecas e ferramentas essenciais para desenvolvimento e compilação. [Guia de instalação](https://www.raspberrypi.com/documentation/pico/getting-started/)
- **CMake:** Ferramenta multiplataforma para configuração do projeto
- **Compilador C/C++:** Utiliza GCC (GNU Compiler Collection)
- **Git:** (Opcional) Para controle de versão e clonagem do repositório

### Estrutura do Código

- **`U4T6.c`**: Contém o loop principal, responsável por monitorar entradas e controlar LEDs e display
- **`display/ssd1306.c/.h`**: Implementa a comunicação I2C com o display OLED
- **`neopixel/neopixel.c/.h`**: Gerencia a matriz NeoPixel RGB
- **`CMakeLists.txt`**: Configura o projeto para compilação
- **`diagram.json`**: Diagramas de conexão do hardware

## Compilação e Execução ⚙️

1. **Instale o SDK do Raspberry Pi Pico** seguindo o guia oficial.
2. **Clone o repositório**: `git clone git@github.com:klebersm/embarcatech-U4C6.git`
3. **Acesse o diretório do projeto**: `cd Embarcatech-U4C6`
4. **Compile o código**: `cmake -B build && cmake --build build`
5. **Carregue no Pico**: Copie o arquivo `U4C6.uf2` da pasta `build` para o Raspberry Pi Pico. A execução iniciará automaticamente.

## Interrupções e Tratamento de Botões ⏱️

Os botões A e B são configurados como entradas PULL UP e monitorados por interrupções. Quando um botão é pressionado (borda de descida), um alarme de 100ms é acionado para debounce. Caso ocorra outra variação de sinal no mesmo botão, o alarme é cancelado. Assim, o evento só é processado se o botão permanecer estável por 100ms após ser pressionado.

## 🎥 Demonstração do Projeto

Confira o vídeo de funcionamento:



---
