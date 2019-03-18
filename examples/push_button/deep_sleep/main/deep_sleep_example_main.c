/* Deep sleep wake up example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>


#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "nvs_flash.h"

#include "esp_sleep.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp32/ulp.h"
#include "esp_system.h"
#include "esp_event_loop.h"
#include "esp_bt.h"

#include "driver/gpio.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"



#include "driver/touch_pad.h"
#include "driver/adc.h"
#include "driver/rtc_io.h"


#include "soc/rtc_cntl_reg.h"
#include "soc/sens_reg.h"
#include "soc/rtc.h"

#include "rom/uart.h"

#include "esp_log.h"
#include "mqtt_client.h"


#define BUTTON_GPIO_NUM     25

#define MQTT_USERNAME "BJsqmKVLZXO4nTWQYLyL"

static RTC_DATA_ATTR struct timeval sleep_enter_time;



/*
 * Offset (in 32-bit words) in RTC Slow memory where the data is placed
 * by the ULP coprocessor. It can be chosen to be any value greater or equal
 * to ULP program size, and less than the CONFIG_ULP_COPROC_RESERVE_MEM/4 - 6,
 * where 6 is the number of words used by the ULP coprocessor.
 */

int count = 1;


int msg_id;
const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
char buf[100];

static const char *TAG = "MQTT_EXAMPLE";

static EventGroupHandle_t wifi_event_group;
const static int CONNECTED_BIT = BIT0;

static esp_mqtt_client_handle_t MQTT_CLIENT;




static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    esp_log_level_set(TAG, ESP_LOG_INFO); // enable INFO logs from DHCP client
    // your_context_t *context = event->context;
    switch (event->event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        //msg_id = esp_mqtt_client_subscribe(client, "v1/devices/me/telemetry", 0);
        //ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        break;
    case MQTT_EVENT_BEFORE_CONNECT:
        ESP_LOGI(TAG, "MQTT_EVENT_BEFORE_CONNECT");
        break;
    }
    return ESP_OK;
}

static esp_err_t wifi_event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id)
    {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);

        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}

static void wifi_init(void)
{
    tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_init(wifi_event_handler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = CONFIG_WIFI_SSID,
            .password = CONFIG_WIFI_PASSWORD,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_LOGI(TAG, "start the WIFI SSID:[%s]", CONFIG_WIFI_SSID);
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "Waiting for wifi");
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
}

static void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = CONFIG_BROKER_URL,
        .username = MQTT_USERNAME,
        .password = "",
        .event_handle = mqtt_event_handler,
        // .user_context = (void *)your_context
    };

    MQTT_CLIENT = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(MQTT_CLIENT);
}


void app_main()
{
    struct timeval now;
    gettimeofday(&now, NULL);


    switch (esp_sleep_get_wakeup_cause()) {
        case ESP_SLEEP_WAKEUP_EXT1: {
            uint64_t wakeup_pin_mask = esp_sleep_get_ext1_wakeup_status();
            if (wakeup_pin_mask != 0) {
                int pin = __builtin_ffsll(wakeup_pin_mask) - 1;
                printf("Wake up from GPIO %d\n", pin);

            }
            else {
                printf("Wake up from GPIO\n");
            }
            break;
        }


        case ESP_SLEEP_WAKEUP_UNDEFINED:
        default:
            printf("Not a deep sleep reset\n");
    }


    vTaskDelay(1000 / portTICK_PERIOD_MS);


    const int ext_wakeup_pin_1 = BUTTON_GPIO_NUM;
    const uint64_t ext_wakeup_pin_1_mask = 1ULL << ext_wakeup_pin_1;


    printf("Enabling EXT1 wakeup on pins GPIO%d\n", ext_wakeup_pin_1);



    esp_sleep_enable_ext1_wakeup(ext_wakeup_pin_1_mask, ESP_EXT1_WAKEUP_ALL_LOW);


    rtc_gpio_isolate(GPIO_NUM_12);

    nvs_flash_init();
    wifi_init();
    mqtt_app_start();

    vTaskDelay(pdMS_TO_TICKS(1000));
             
    printf("Wifi started\n");

    printf("MQTT started\n");

    
    printf("COUNT : %d\n",count);

    sprintf(buf, "{\"count\": \"%d\"}", count);
    msg_id = esp_mqtt_client_publish(MQTT_CLIENT, "v1/devices/me/telemetry", buf, 0, 0, 0);
    ESP_LOGI(TAG, "sent publish successful, msg=%s", buf);
    printf("message sent\n");

    esp_wifi_stop();
    //esp_bluedroid_disable();
    //esp_bt_controller_disable();

    printf("Entering deep sleep\n");

    uart_tx_wait_idle(CONFIG_CONSOLE_UART_NUM);
    gettimeofday(&sleep_enter_time, NULL);

    esp_deep_sleep_start();
}
