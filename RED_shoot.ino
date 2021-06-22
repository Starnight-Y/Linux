#include <ESP8266WiFi.h>//安装esp8266arduino开发环境
static WiFiClient espClient;

#include <AliyunIoTSDK.h>//引入阿里云 IoT SDK
#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#include <IRremoteESP8266.h>
#include <IRsend.h>
//需要安装crypto库、PubSubClient库

//设置产品和设备的信息，从阿里云设备信息里查看
#define PRODUCT_KEY     "a16teOJV8BW"//替换自己的PRODUCT_KEY
#define DEVICE_NAME     "REDcontrol"//替换自己的DEVICE_NAME
#define DEVICE_SECRET   "ae1b9dc4b85d75cd6bb8f1fd4b3e068f"//替换自己的DEVICE_SECRET
#define REGION_ID       "cn-shanghai"//默认cn-shanghai

#define WIFI_SSID       "joker_air"//替换自己的WIFI
#define WIFI_PASSWD     "pangzisb"//替换自己的WIFI

unsigned long lastMsMain = 0;
//定义红外发射的管脚
const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

//空调开：25度
uint16_t power_on[229] = {3118, 3000,  3096, 4402,  658, 1566,  656, 460,  652, 1572,  656, 464,  650, 478,  630, 1596,  630, 1572,  652, 482,  630, 1596,  634, 478,  602, 510,  658, 1566,  660, 458,  654, 478,  632, 1570,  656, 480,  632, 480,  602, 512,  656, 462,  654, 476,  632, 480,  604, 512,  654, 456,  658, 480,  632, 478,  602, 512,  656, 462,  654, 476,  632, 480,  602, 512,  658, 454,  656, 482,  632, 478,  604, 1622,  604, 508,  658, 460,  652, 484,  632, 478,  602, 510,  604, 512,  654, 464,  624, 1600,  650, 480,  630, 482,  602, 512,  654, 464,  650, 460,  654, 478,  602, 510,  654, 464,  652, 480,  630, 482,  602, 510,  654, 464,  648, 464,  648, 484,  602, 510,  656, 460,  650, 1572,  628, 492,  646, 484,  602, 510,  658, 454,  654, 466,  648, 482,  628, 484,  628, 486,  654, 464,  648, 482,  604, 508,  628, 484,  626, 492,  650, 482,  630, 482,  600, 512,  654, 464,  648, 484,  628, 484,  624, 488,  600, 518,  646, 484,  604, 510,  600, 514,  628, 492,  644, 486,  626, 486,  600, 512,  598, 518,  646, 486,  602, 512,  600, 514,  626, 494,  618, 512,  600, 514,  596, 536,  576, 538,  600, 1622,  602, 512,  598, 536,  576, 538,  600, 514,  598, 1624,  600, 512,  600, 1626,  572, 540,  598, 1628,  594, 518,  594, 1630,  594, 1634,  592, 1656,  568, 520,  592, 1632,  568};  // HAIER_AC_YRW02
//空调关
uint16_t power_off[229] = {3138, 3000,  3094, 4404,  658, 1566,  656, 460,  652, 1570,  656, 464,  648, 480,  604, 1622,  630, 1574,  652, 480,  630, 1596,  630, 482,  604, 510,  654, 1570,  658, 460,  650, 482,  630, 482,  634, 478,  630, 486,  656, 464,  648, 480,  604, 508,  654, 462,  654, 482,  630, 482,  634, 478,  628, 488,  654, 464,  650, 478,  604, 508,  630, 488,  652, 484,  632, 462,  650, 478,  602, 512,  654, 466,  652, 478,  630, 482,  628, 488,  652, 466,  650, 460,  652, 478,  602, 512,  658, 1566,  658, 460,  652, 482,  634, 478,  602, 510,  662, 450,  658, 464,  650, 480,  604, 508,  636, 480,  654, 480,  634, 478,  602, 510,  656, 456,  656, 464,  650, 480,  604, 506,  630, 1596,  626, 488,  656, 464,  650, 480,  630, 482,  628, 482,  658, 460,  652, 480,  628, 484,  602, 510,  654, 464,  650, 480,  632, 480,  630, 482,  656, 462,  652, 480,  628, 484,  602, 510,  656, 462,  648, 484,  628, 484,  628, 482,  654, 462,  650, 484,  628, 484,  600, 510,  656, 462,  650, 482,  628, 484,  628, 482,  628, 488,  654, 466,  646, 482,  600, 512,  652, 464,  652, 480,  630, 482,  630, 482,  624, 1600,  600, 512,  652, 468,  646, 486,  602, 510,  598, 1626,  598, 512,  600, 1608,  620, 510,  626, 486,  624, 490,  626, 1598,  626, 1598,  626, 494,  620, 1618,  604, 1600,  602};  // HAIER_AC_YRW02
//制冷
uint16_t cold[229] =  {3156, 2984,  3098, 4400,  658, 1566,  628, 488,  666, 1558,  666, 454,  682, 446,  638, 1588,  666, 1538,  668, 466,  638, 1586,  648, 466,  554, 558,  662, 1560,  632, 488,  686, 446,  664, 1538,  672, 464,  664, 448,  556, 558,  668, 452,  684, 446,  638, 474,  604, 512,  664, 446,  666, 472,  666, 446,  556, 556,  662, 458,  662, 468,  642, 470,  578, 538,  666, 444,  664, 474,  642, 470,  582, 1644,  636, 476,  628, 488,  662, 472,  664, 448,  606, 506,  634, 480,  666, 454,  672, 1550,  686, 446,  664, 448,  556, 558,  666, 452,  668, 442,  668, 462,  608, 504,  630, 488,  662, 470,  650, 464,  554, 558,  662, 458,  660, 450,  662, 470,  632, 480,  628, 488,  662, 1562,  664, 456,  656, 472,  622, 490,  626, 486,  602, 518,  656, 476,  636, 476,  598, 514,  660, 476,  636, 478,  630, 482,  602, 510,  600, 518,  654, 478,  630, 482,  574, 538,  652, 466,  648, 484,  632, 480,  600, 512,  600, 518,  648, 482,  630, 484,  600, 514,  626, 510,  626, 510,  602, 508,  576, 536,  576, 538,  602, 510,  602, 536,  574, 538,  600, 514,  600, 536,  576, 538,  574, 538,  572, 540,  598, 1626,  598, 540,  568, 544,  568, 544,  592, 522,  592, 1632,  594, 1654,  544, 546,  592, 544,  568, 1656,  570, 544,  568, 1656,  568, 1658,  568, 1658,  568, 1656,  568, 544,  568};  // UNKNOWN C05FDF44
//制热
uint16_t warm[229] =  {3160, 2980,  3098, 4400,  656, 1568,  658, 460,  660, 1564,  656, 462,  658, 472,  638, 1586,  634, 1568,  654, 480,  636, 1588,  632, 480,  578, 1648,  604, 510,  656, 1566,  632, 486,  662, 1558,  602, 514,  660, 474,  642, 470,  582, 530,  658, 460,  686, 446,  666, 446,  556, 556,  580, 536,  664, 472,  664, 446,  608, 504,  630, 488,  686, 448,  664, 446,  580, 534,  606, 508,  670, 1552,  666, 1558,  660, 460,  662, 470,  664, 448,  556, 556,  662, 450,  656, 466,  682, 1540,  686, 444,  640, 1586,  640, 474,  554, 558,  664, 456,  684, 428,  684, 446,  608, 504,  630, 488,  662, 472,  664, 446,  580, 534,  660, 460,  684, 426,  664, 468,  636, 1588,  632, 480,  602, 514,  672, 446,  682, 448,  636, 476,  628, 484,  602, 518,  668, 462,  642, 470,  576, 538,  666, 454,  658, 472,  636, 476,  602, 510,  576, 542,  658, 476,  636, 476,  576, 538,  656, 464,  652, 478,  636, 478,  600, 512,  598, 518,  654, 478,  632, 482,  576, 536,  628, 490,  650, 482,  628, 484,  600, 514,  600, 516,  650, 482,  628, 486,  600, 514,  624, 494,  646, 484,  602, 534,  576, 536,  576, 536,  604, 1620,  604, 510,  600, 536,  576, 536,  574, 540,  600, 1624,  600, 1626,  572, 540,  598, 1628,  594, 522,  590, 1634,  592, 1656,  570, 544,  568, 1656,  568, 1656,  568, 522,  590};  // UNKNOWN CE4D8E3E
void setup()
{
  Serial.begin(115200);

  //连接到wifi
  wifiInit(WIFI_SSID, WIFI_PASSWD);

  //初始化 iot，需传入 wifi 的 client，和设备产品信息
  AliyunIoTSDK::begin(espClient, PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET, REGION_ID);

  //绑定一个设备属性回调，当远程修改此属性，会触发LED函数
  AliyunIoTSDK::bindData("AIR", AIR);
  AliyunIoTSDK::bindData("TEM", TEM);
    //红外初始化
  irsend.begin();
}

void loop()
{
  AliyunIoTSDK::loop();//必要函数

  if (millis() - lastMsMain >= 2000)//每2秒发送一次
  {
    lastMsMain = millis();

    //发送LED状态到云平台（高电平：1；低电平：0）
    //AliyunIoTSDK::send("AIRPIN", Serial.println(AIR));
  }
}

//wifi 连接
void wifiInit(const char *ssid, const char *passphrase)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passphrase);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("WiFi not Connect");
  }
  Serial.println("Connected to AP");
}

//开启关闭的属性修改的回调函数
void AIR(JsonVariant L)//固定格式，修改参数l
{
  int AIR = L["AIR"];//参数l
  if (AIR == 0)
  {
    irsend.sendRaw(power_off, 299, 38);  // Send a raw data capture at 38kHz.
  }
  else if(AIR == 1)
  {
    //发送红外指令
    irsend.sendRaw(power_on, 299, 38);  // Send a raw data capture at 38kHz.
  }
  Serial.printf("收到的AIR是："); Serial.println(AIR);
}
//制冷制热的属性修改的回调函数
void TEM(JsonVariant L)//固定格式，修改参数l
{
  int TEM = L["TEM"];//参数l
  if (TEM == 0)
  {
    irsend.sendRaw(cold, 299, 38);  // Send a raw data capture at 38kHz.
  }
  else if(TEM == 1)
  {
    //发送红外指令
    irsend.sendRaw(warm, 299, 38);  // Send a raw data capture at 38kHz.
  }
  Serial.printf("收到的TEM是："); Serial.println(TEM);
}