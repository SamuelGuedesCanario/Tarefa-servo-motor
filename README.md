# Embarcatech-U4C7

Este projeto demonstra o controle de um servomotor utilizando PWM no microcontrolador RP2040 (Raspberry Pi Pico).

## 📌 Visão Geral
O servomotor é controlado por um sinal PWM de 50Hz (período de 20ms), onde a posição do eixo é determinada pelo duty cycle do sinal.

Para gerar um sinal de 50Hz, a frequência do RP2040 (125MHz) precisa ser dividida de forma que:

\[ 125000000 / 50 = 2500000 \]

Portanto, o valor do WRAP multiplicado pelo divisor precisa resultar em **2.500.000**. Para garantir maior resolução, escolhemos:

- **Divisor**: 25
- **WRAP**: 100.000

## 📊 Tabela de Duty Cycle
A tabela abaixo mostra os valores de PWM para diferentes posições do servomotor:

| Posição | Período | Duty Cycle | PWM Level |
|---------|--------|------------|------------|
| 180º    | 2400µs | 12%        | 12.000     |
| 90º     | 1470µs | 7,35%      | 7.350      |
| 0º      | 500µs  | 2,5%       | 2.500      |

No código, essas posições são definidas como macros:

```c
#define POS_180 12000
#define POS_90  7350
#define POS_0   2500
```

Para a movimentação contínua, usamos um incremento de **5µs** a cada passo. Como o período total da onda é **20ms**, podemos calcular:

\[ 20000µs / 5µs = 4000 \]

Ou seja, o WRAP total será dividido em **4000 partes**, cada uma de:

\[ 100000 / 4000 = 25 \]

Por isso, no código definimos:

```c
#define STEP 25
```

## 🔦 Comportamento do LED

Para testes, o PWM foi aplicado a um LED na plataforma BitdogLab (pino 12 - LED Azul). O comportamento observado foi:

1. Nos primeiros 15 segundos, o LED apresentou pequenas variações de brilho, correspondentes às posições 180º, 90º e 0º.
2. No modo contínuo, a luminosidade oscilou gradativamente, mas sempre em um nível baixo (entre 2,5% e 12% do brilho máximo). Isso ocorre porque os valores do duty cycle são específicos para controle de servomotores e não para LEDs.

## 🔧 Hardware

- **Microcontrolador**: RP2040 (Raspberry Pi Pico)
- **Servomotor**
- **LED (para testes opcionais)**

## 💻 Software

- **SDK do Raspberry Pi Pico** - [Guia de Instalação](https://www.raspberrypi.com/documentation/pico/getting-started/)
- **CMake** - Ferramenta de compilação
- **Compilador C/C++ (GCC)**
- **Git** (opcional)

### 🗂 Estrutura do Código

- **`U4T7.C`** - Código principal que configura o PWM e controla o servomotor.
- **`CMakeLists.txt`** - Configuração do projeto para CMake.
- **`diagram.json`** - Diagramas de conexões.

## ⚙️ Como Compilar e Executar

1. **Instale o SDK do Raspberry Pi Pico** seguindo o guia oficial.
2. **Clone este repositório:**
   ```sh
   git clone https://github.com/SamuelGuedesCanario/Tarefa-servo-motor.git
   ```
3. **Acesse o diretório do projeto:**
   ```sh
   cd Embarcatech-U4C7
   ```
4. **Compile o projeto:**
   ```sh
   cmake -B build && cmake --build build
   ```
5. **Copie para o Pico:**
   - Após a compilação, copie o arquivo `U4C7.uf2` da pasta `build` para o Raspberry Pi Pico.
   - O código será executado automaticamente.

## 🎥 Demonstração

🔗 **Link do vídeo de funcionamento:** https://youtu.be/Do3VP0eAvv0

---

Caso tenha dúvidas ou queira contribuir, fique à vontade para abrir um pull request ou relatar issues! 🚀
