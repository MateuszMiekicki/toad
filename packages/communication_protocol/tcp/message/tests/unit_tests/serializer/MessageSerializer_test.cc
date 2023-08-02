#include "toad/communication_protocol/tcp/message/Message.hh"
#include "toad/communication_protocol/tcp/message/serializer/MessageSerializer.hh"
#include <gtest/gtest.h>

namespace
{
const auto clientId = "client_id";
const std::string mcuConfiguration =
    R"({"MQTT":{"MQTT_ID_NAME":"ESP32","MQTT_PORT":"1883","MQTT_SERVER_IP":"192.168.1.25","MQTT_CONNECTION_TEMPLATE":{"device_id":1,"sensor_id":"","value":""}},"TCP":{"TCP_SERVER_IP":"192.168.1.25","TCP_PORT":"5570"},"BUTTONS":{"BUTTON_ADC_PIN":"6"},"PWM":{"PWM_PIN":"10"},"WIFI":{"WIFI_SSID":"OrangeWiFi","WIFI_PASSWORD":"szpegawa9a","ESP_MAC_ADDRESS":"7c:df:a1:3f:2e:ac"},"LCD":{"LCD_WIDTH":"320","LCD_HEIGHT":"240","LCD_ROTATION":"0","LCD_CLK_PIN":"15","LCD_MOSI_PIN":"9","LCD_MISO_PIN":"8","LCD_CS_PIN":"11","LCD_RST_PIN":"16","LCD_DC_PIN":"13","FONT_DIR":"fonts/Unispace12x24.c","FONT_WIDTH":"12","FONT_HEIGHT":"24"},"SENSORS":[{"pin_number":501,"category":"humidity","min_val":50,"max_val":80},{"pin_number":502,"category":"temperature","min_val":20,"max_val":30}]})";
const std::string alert =
    R"({"type":"report","purpose":"alert","payload":{"alert":{"mac_address":"00:00:00:00:00:00","pin_number":21,"alert_number":37,"date":"2000-10-31T01:30:00.000-05:00","description":"short description of the alert","priority":10000}}})";
} // namespace

struct MessageAndExpectedJSON
{
    toad::communication_protocol::tcp::Message message;
    std::string expectedOutput;
};

struct MessageSerializerFixture : public ::testing::TestWithParam<MessageAndExpectedJSON>
{
};

TEST_P(MessageSerializerFixture, serializeStandardMessageFromFlyRepository)
{
    const auto& [message, expectedOutput] = GetParam();
    const auto serialized_message = toad::communication_protocol::tcp::serialize(message);
    EXPECT_EQ(serialized_message, expectedOutput);
}

INSTANTIATE_TEST_SUITE_P(
    MessageSerializerTest,
    MessageSerializerFixture,
    ::testing::Values(
        MessageAndExpectedJSON{
            toad::communication_protocol::tcp::Message{
                                                       clientId, toad::communication_protocol::tcp::Message::Type::request,
                                                       toad::communication_protocol::tcp::Message::Purpose::getConfiguration,
                                                       toad::communication_protocol::tcp::Payload("{}",
                                                       toad::communication_protocol::tcp::Payload::Type::json)},
            R"({"type":"request","purpose":"get_configuration","payload":{}})"},
        MessageAndExpectedJSON{
            toad::communication_protocol::tcp::Message{
                clientId,
                toad::communication_protocol::tcp::Message::Type::unknown,
                toad::communication_protocol::tcp::Message::Purpose::setConfiguration,
                toad::communication_protocol::tcp::Payload(mcuConfiguration,
                                                           toad::communication_protocol::tcp::Payload::Type::json)},
            R"({"type":"unknown","purpose":"set_configuration","payload":)" + mcuConfiguration + R"(})"},
        MessageAndExpectedJSON{
            toad::communication_protocol::tcp::Message{
                clientId,
                toad::communication_protocol::tcp::Message::Type::response,
                toad::communication_protocol::tcp::Message::Purpose::failure,
                toad::communication_protocol::tcp::PayloadFactory::createFailureDetail("Client not found")},
            R"({"type":"response","purpose":"failure","payload":{"cause":{"detail":"Client not found"}}})"},
        MessageAndExpectedJSON{toad::communication_protocol::tcp::Message{
                                   clientId,
                                   toad::communication_protocol::tcp::Message::Type::report,
                                   toad::communication_protocol::tcp::Message::Purpose::alert,
                                   toad::communication_protocol::tcp::PayloadFactory::createJson(alert)},
                               R"({"type":"report","purpose":"alert","payload":)" + alert + R"(})"}));
