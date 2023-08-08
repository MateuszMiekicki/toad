

def make_alert_report(mac_address:str):
    return '''{
    "type": "report",
    "purpose": "alert",
    "payload": {
        "alert": {
            "mac_address": "'''+mac_address+'''",
            "pin_number": 21,
            "alert_number": 37,
            "date": "2000-10-31T01:30:00.000-05:00",
            "description": "short description of the alert",
            "priority": 10000
        }
    }
}'''

def make_get_configuration_response(mac_address:str):
    return '''{
    "type": "response",
    "purpose": "get_configuration",
    "payload": {
        "configuration": {
            "MQTT": {
                "MQTT_ID_NAME": "ESP32",
                "MQTT_PORT": "1883",
                "MQTT_SERVER_IP": "192.168.1.25",
                "MQTT_CONNECTION_TEMPLATE": {
                    "device_id": 1,
                    "sensor_id": "",
                    "value": ""
                }
            },
            "TCP": {
                "TCP_SERVER_IP": "192.168.1.25",
                "TCP_PORT": "5570"
            },
            "BUTTONS": {
                "BUTTON_ADC_PIN": "6"
            },
            "PWM": {
                "PWM_PIN": "10"
            },
            "WIFI": {
                "WIFI_SSID": "OrangeWiFi",
                "WIFI_PASSWORD": "szpegawa9a",
                "ESP_MAC_ADDRESS": "'''+mac_address+'''"
            },
            "LCD": {
                "LCD_WIDTH": "320",
                "LCD_HEIGHT": "240",
                "LCD_ROTATION": "0",
                "LCD_CLK_PIN": "15",
                "LCD_MOSI_PIN": "9",
                "LCD_MISO_PIN": "8",
                "LCD_CS_PIN": "11",
                "LCD_RST_PIN": "16",
                "LCD_DC_PIN": "13",
                "FONT_DIR": "fonts/Unispace12x24.c",
                "FONT_WIDTH": "12",
                "FONT_HEIGHT": "24"
            },
            "SENSORS": [
                {
                    "pin_number": 501,
                    "category": "humidity",
                    "min_val": 50,
                    "max_val": 80
                },
                {
                    "pin_number": 502,
                    "category": "temperature",
                    "min_val": 20,
                    "max_val": 30
                }
            ]
        }
    }
}'''


def make_response_failure(cause:str=""):
    return '''{
    "type": "response",
    "purpose": "failure",
    "payload": {
        "cause": {
            "detail": "''' + cause + '''"
        }
    }
}'''

def make_get_sensors_configuration_response():
    return '''{
    "type": "response",
    "purpose": "get_configuration",
    "payload": {
        "sensors": [
            {
                "pin_number": 501,
                "type": "temperature",
                "min_value": 12,
                "max_value": 38
            },
            {
                "pin_number": 501,
                "type": "humidity",
                "min_value": 25,
                "max_value": 50
            }
        ]
    }
}'''