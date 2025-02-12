#include <stdio.h>
#include "pico/stdlib.h"
#include "tarefa.h"

// Definição das variáveis globais para alarmes e display
static alarm_id_t btn_a_alm;
static alarm_id_t btn_b_alm;
ssd1306_t ssd; // Estrutura para controlar o display SSD1306

// Função para inicializar os pinos GPIO
void init_gpio() {
    // Máscara para os LEDs RGB
    uint ledMask = (0x01 << LED_R) | (0x01 << LED_G) | (0x01 << LED_B);
    gpio_init_mask(ledMask);
    gpio_set_dir_out_masked(ledMask);

    // Máscara para os botões
    uint btnMask = (0x01 << BUTTON_A) | (0x01 << BUTTON_B);
    gpio_init_mask(btnMask);
    gpio_set_dir_in_masked(btnMask);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    // Configuração de interrupção para os botões (detecção de borda de subida e descida)
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &debounce);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &debounce);
}

// Função para inicializar o display OLED SSD1306
void init_display() {
    i2c_init(I2C_PORT, SSD1306_FREQ);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, SSD1306_ADDR, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);

    // Limpa o display ao iniciar
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

// Função chamada quando o botão A é pressionado
uint64_t handle_btn_a(alarm_id_t id, void *user_data) {
    gpio_put(LED_G, !gpio_get(LED_G)); // Alterna o estado do LED verde
}

// Função chamada quando o botão B é pressionado
uint64_t handle_btn_b(alarm_id_t id, void *user_data) {
    gpio_put(LED_B, !gpio_get(LED_B)); // Alterna o estado do LED azul
}

// Função para debounce dos botões
static void debounce(uint gpio, uint32_t events) {
    if (gpio == BUTTON_A) {
        cancel_alarm(btn_a_alm);
        if (events == 0x04) btn_a_alm = add_alarm_in_ms(DEBOUNCE_MS, handle_btn_a, NULL, false);
    } else if (gpio == BUTTON_B) {
        cancel_alarm(btn_b_alm);
        if (events == 0x04) btn_b_alm = add_alarm_in_ms(DEBOUNCE_MS, handle_btn_b, NULL, false);
    }
}

// Função para exibir status do LED verde no console e no display
void print_led_verde(bool status) {
    printf("%c[H", 27);
    printf("%c[2B", 27);
    printf("%c[2K", 27);
    status ? printf("LED VERDE: ON") : printf("LED VERDE: OFF");
    
    status ? ssd1306_draw_string(&ssd, "ON ", 12*8, 30) : ssd1306_draw_string(&ssd, "OFF", 12*8, 30);
    ssd1306_send_data(&ssd);
}

// Função para exibir status do LED azul no console e no display
void print_led_azul(bool status) {
    printf("%c[H", 27);
    printf("%c[3B", 27);
    printf("%c[2K", 27);
    status ? printf("LED AZUL : ON") : printf("LED AZUL : OFF");
    
    status ? ssd1306_draw_string(&ssd, "ON ", 12*8, 40) : ssd1306_draw_string(&ssd, "OFF", 12*8, 40);
    ssd1306_send_data(&ssd);
}

int main() {
    stdio_init_all();
    init_gpio();
    init_neopixel();
    init_display();

    // Configuração inicial do display
    ssd1306_rect(&ssd, 3, 3, 122, 58, true, false);
    ssd1306_send_data(&ssd);
    ssd1306_draw_string(&ssd, "CONECTE UART", 17, 10);
    ssd1306_draw_string(&ssd, "Atividade 1", 45, 30);
    ssd1306_draw_string(&ssd, "SAMUEL CANARIO", 7, 45);
    ssd1306_send_data(&ssd);

    // Aguarda conexão via USB
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    printf("UART conectada com sucesso.\n");
    printf("Caractere Recebido:\n");

    // Atualiza a interface do display
    bool ledG = gpio_get(LED_G);
    bool ledB = gpio_get(LED_B);
        ssd1306_fill(&ssd, false),

    ssd1306_draw_string(&ssd, "UART OK      ", 8, 10);
    ssd1306_draw_string(&ssd, "LETRA ", 8, 20);
    ssd1306_draw_string(&ssd, "LED VERDE ", 8, 30);
    ssd1306_draw_string(&ssd, "LED AZUL ", 8, 40);
    ssd1306_send_data(&ssd);

    print_led_verde(ledG);
    print_led_azul(ledB);

    while (true) {
        int c = stdio_getchar_timeout_us(10);
        if (c != PICO_ERROR_TIMEOUT) {
            printf("%c[H", 27);
            printf("%c[1B", 27);
            printf("%c[2K", 27);
            printf("Caractere Recebido: %c", c);
            ssd1306_draw_char(&ssd, (char)c, 12*8, 20);
            ssd1306_send_data(&ssd);
            if (c >= 48 && c <= 57) {
                renderMatrix(alphabet[c - 48]);
            } else renderMatrix(OFF);
        }

        // Atualiza LEDs se o estado for alterado
        if (ledG != gpio_get(LED_G)) {
            ledG = gpio_get(LED_G);
            print_led_verde(ledG);
        }
        if (ledB != gpio_get(LED_B)) {
            ledB = gpio_get(LED_B);
            print_led_azul(ledB);
        }
        
        sleep_ms(50);
    }
}
