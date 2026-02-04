#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"
#include "TextRenderer/TextRenderer.h" // 文字表示にはこれが必要
#include "SensorBase_Temp.h"

#include "ssd1306.h" // LEDライブラリ
#include "sht31.h"  // 温度センサ

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

// OLED設定
#define OLED_ADDR 0x3C
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

// LEDピン設定
const uint LED_PIN = PICO_DEFAULT_LED_PIN;

// 周期タイマー用のコールバック関数
bool repeating_timer_callback(struct repeating_timer *t) {
    static bool led_state = false;
    led_state = !led_state;
    gpio_put(LED_PIN, led_state); // LEDの表示
    
    // TeraTermへの送信
    printf("Timer Tick: LED is %s\n", led_state ? "ON" : "OFF");
    return true; 
}


int main()
{

    stdio_init_all();
    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // 周期タイマーの設定（500msごと）
    struct repeating_timer timer;
    add_repeating_timer_ms(500, repeating_timer_callback, NULL, &timer);

    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART

    // Send out a string, with CR/LF conversions
    uart_puts(UART_ID, " Hello, UART!\n");
    
    // For more examples of UART use see https://github.com/raspberrypi/pico-examples/tree/master/uart

    // OLEDの初期化
    // ライブラリの仕様に合わせてインスタンスを作成
    pico_ssd1306::SSD1306 display(I2C_PORT, OLED_ADDR, pico_ssd1306::Size::W128xH64);

    // 温度センサの初期化
    // 1. 使うセンサーを生成（ここだけセンサー名を指定）
    SensorBase_Temp* mySensor = new SHT31(i2c0, 0x44);

    while (true) {
        ///////////////// 温度センサの処理 /////////////////
        // 2. 使うときは SensorBase_Temp 型として扱う
        // もしセンサーをBME280に変えても、この下の行は1文字も変えなくてOK！
        SensorData result = mySensor->read();

        if (result.success) {
            printf("Temp: %.1f\n", result.temperature);
        }

        /////////////////   OLEDの処理    /////////////////
        // 画面をクリア
        display.clear();

        // 文字を描画 (x, y, スケール, 文字列)
        // ※ライブラリによって引数の順序が多少異なる場合があります
        drawText(&display, font_8x8, "PICO 2 MONITOR", 0, 0);
        drawText(&display, font_8x8, "System: OK", 0, 16);
        drawText(&display, font_8x8, "Temp: --.- C", 0, 32);

        // 実際に画面へ送信して更新
        display.sendBuffer();

        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
