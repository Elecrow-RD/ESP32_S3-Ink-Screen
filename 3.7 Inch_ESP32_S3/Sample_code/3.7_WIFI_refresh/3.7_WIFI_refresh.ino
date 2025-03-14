#include <Arduino.h>            // 包含Arduino核心库
#include "EPD.h"                // 包含电子纸显示器的库
#include "EPD_GUI.h"            // 包含电子纸显示器的图形用户界面库
#include "Ap_29demo.h"          // 自定义的库文件
#include "FS.h"                 // 文件系统库
#include "SPIFFS.h"             // SPIFFS 文件系统库，用于文件读写

#include <WiFi.h>               // 包含WiFi库
#include <WebServer.h>          // 包含Web服务器库
#include <Adafruit_GFX.h>       // 包含Adafruit图形库
#include <Fonts/FreeMonoBold9pt7b.h> // 包含FreeMonoBold字体

#define txt_size 4576          // 定义txt文件的大小
#define pre_size 5824          // 定义pre文件的大小

// 定义电子纸图像缓存区的大小
uint8_t ImageBW[12480]; // 电子纸图像缓存区

// 清空画布并重新初始化电子纸显示器
void clear_all() {
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE); // 创建新的图像缓存
  Paint_Clear(WHITE); // 清空画布
  EPD_FastInit(); // 快速初始化电子纸显示器
  EPD_Display_Clear(); // 清除显示器内容
  EPD_Update(); // 更新显示器
}

// 创建WebServer实例，监听80端口
WebServer server(80);
const char* AP_SSID = "ESP32_Config"; // WiFi热点名称

// 上传文件的HTML表单
String HTML_UPLOAD = "<form method=\"post\" action=\"ok\" enctype=\"multipart/form-data\">"
                     "<input type=\"file\" name=\"msg\">"
                     "<input class=\"btn\" type=\"submit\" name=\"submit\" value=\"Submit\">"
                     "</form>";

// 处理根路径的请求
void handle_root() {
  server.send(200, "text/html", HTML_UPLOAD); // 发送上传表单的HTML内容
}

// 上传成功后的HTML页面
String HTML_OK = "<!DOCTYPE html>"
                 "<html>"
                 "<body>"
                 "<h1>OK</h1>"
                 "</body>"
                 "</html>";

// 存储上传文件的对象
File fsUploadFile;                  // 文件对象，用于保存上传的文件
unsigned char price_formerly[pre_size]; // 存储上传的图像数据（pre_size大小）
unsigned char txt_formerly[txt_size]; // 存储上传的图像数据（txt_size大小）
String filename;                   // 存储文件名的变量

// 处理文件上传并显示到电子纸
void okPage() {
  server.send(200, "text/html", HTML_OK); // 发送上传成功页面

  HTTPUpload& upload = server.upload(); // 获取上传的文件数据

  // 注意：upload.buf 的初始化大小只有 1436 字节，需要根据需要调整
  // 通过ctrl + 鼠标左键点击upload.buf可以找到 WebServer.h 中的 HTTP_UPLOAD_BUFLEN
  // 将其调整为适当的大小（例如14360字节）
  if (upload.status == UPLOAD_FILE_END) { // 上传完成
    Serial.println("绘图文件");
    Serial.println(upload.filename); // 打印文件名
    Serial.println(upload.totalSize); // 打印文件大小
    
    // 根据上传文件的大小确定文件类型
    if (upload.totalSize == txt_size) // 如果文件大小与txt_size一致
      filename = "txt.bin";          // 文件名设置为txt.bin
    else
      filename = "pre.bin";          // 否则文件名设置为pre.bin

    // 保存接收到的文件
    if (!filename.startsWith("/")) filename = "/" + filename; // 确保文件名以'/'开头
    fsUploadFile = SPIFFS.open(filename, FILE_WRITE); // 打开文件进行写入
    fsUploadFile.write(upload.buf, upload.totalSize); // 写入文件内容
    fsUploadFile.close(); // 关闭文件
    Serial.println("保存成功");
    Serial.printf("保存：");
    Serial.println(filename);
    Serial.printf("size：");
    Serial.println(upload.totalSize);
    
    // 将上传的文件数据存储到对应的数组中
    if (upload.totalSize == txt_size) {
      for (int i = 0; i < txt_size; i++) {
        txt_formerly[i] = upload.buf[i]; // 将上传数据存入txt_formerly数组
      }
      Serial.println("txt_formerly OK");
    } else {
      for (int i = 0; i < pre_size; i++) {
        price_formerly[i] = upload.buf[i]; // 将上传数据存入price_formerly数组
      }
      Serial.println("price_formerly OK");
    }

    // 初始化电子纸显示器并显示图片
    EPD_FastInit(); // 初始化E-Paper屏幕的部分显示模式
    EPD_ShowPicture(0, 0, EPD_H, 40, gImage_conference_3_7, WHITE); // 显示背景图像

    //根据上传文件的类型显示相应的内容
    if (upload.totalSize != txt_size) {
      EPD_ShowPicture(0, 128, 416, 112, price_formerly, WHITE); // 显示pre文件内容
    } else {
      EPD_ShowPicture(0, 40, 416, 88, txt_formerly, WHITE); // 显示txt文件内容
    }

    EPD_Display(ImageBW); // 更新屏幕显示内容
    EPD_Update(); // 刷新屏幕显示内容
    EPD_DeepSleep(); // 进入深度睡眠模式以节省电力
  }
}



void setup() {
  Serial.begin(115200);  // 启动串口通信，设置波特率为115200
  if (SPIFFS.begin()) {  // 尝试启动SPIFFS文件系统
    Serial.println("SPIFFS Started.");  // 如果SPIFFS启动成功，输出启动成功信息
  } else {
    // 如果SPIFFS启动失败，则尝试格式化SPIFFS分区
    if (SPIFFS.format()) {
      // 格式化成功，输出提示信息并重启设备
      Serial.println("SPIFFS partition formatted successfully");
      ESP.restart();  // 重新启动ESP设备
    } else {
      // 格式化失败，输出提示信息
      Serial.println("SPIFFS partition format failed");
    }
    return;  // 结束setup()函数
  }

  Serial.println("Try Connecting to ");

  // 配置WiFi为AP模式，并启动WiFi热点
  WiFi.mode(WIFI_AP);  // 设置WiFi为接入点模式
  boolean result = WiFi.softAP(AP_SSID, "");  // 启动WiFi热点，SSID为AP_SSID，密码为空
  if (result) {
    IPAddress myIP = WiFi.softAPIP();  // 获取热点的IP地址
    // 打印热点相关信息
    Serial.println("");
    Serial.print("Soft-AP IP address = ");
    Serial.println(myIP);  // 打印热点的IP地址
    Serial.println(String("MAC address = ") + WiFi.softAPmacAddress().c_str());  // 打印MAC地址
    Serial.println("waiting ...");
  } else {
    // 启动热点失败
    Serial.println("WiFiAP Failed");
    delay(3000);  // 等待3秒钟
  }

  // 设置HTTP服务器路由
  server.on("/", handle_root);  // 根路径的处理函数
  server.on("/ok", okPage);  // /ok路径的处理函数
  server.begin();  // 启动HTTP服务器
  Serial.println("HTTP server started");
  delay(100);  // 延迟100毫秒

  // 设置屏幕电源引脚并启动屏幕
  pinMode(7, OUTPUT);  // 将引脚7设置为输出模式
  digitalWrite(7, HIGH);  // 供电给屏幕

  EPD_GPIOInit();  // 初始化屏幕GPIO
  Paint_NewImage(ImageBW, EPD_W, EPD_H, 180, WHITE);  // 创建新的图像画布
  Paint_Clear(WHITE);  // 清空画布

  EPD_FastInit();  // 快速初始化屏幕
  
  EPD_Display_Clear();  // 清除屏幕显示
  EPD_Update();  // 更新屏幕显示
  UI_price();  // 更新价格界面
}

void loop() {
  server.handleClient();  // 处理HTTP客户端请求
}

// 更新价格界面的函数
void UI_price() {

  
  EPD_FastInit();  // 快速初始化屏幕
  EPD_ShowPicture(0, 0, EPD_H, 40, gImage_conference_3_7, WHITE);  // 显示背景图片
  EPD_Display(ImageBW);  // 更新屏幕显示
  EPD_Update();  // 刷新屏幕
  EPD_DeepSleep();  // 进入深度睡眠模式

  // 检查文件是否存在并读取内容
  if (SPIFFS.exists("/txt.bin")) {  // 检查/txt.bin文件是否存在
    File file = SPIFFS.open("/txt.bin", FILE_READ);  // 打开文件进行读取
    if (!file) {
      Serial.println("无法打开文件进行读取");  // 文件无法打开，输出提示信息
      return;
    }
    // 从文件中读取数据到数组
    size_t bytesRead = file.read(txt_formerly, txt_size);

    Serial.println("File content:");  // 输出文件内容
    while (file.available()) {
      Serial.write(file.read());  // 逐字节读取文件内容
    }
    file.close();  // 关闭文件

    EPD_FastInit();  // 快速初始化屏幕
    EPD_ShowPicture(0, 40, 416, 88, txt_formerly, WHITE); // 显示txt文件内容
    EPD_Display(ImageBW);  // 更新屏幕显示
    EPD_Update();  // 刷新屏幕
    EPD_DeepSleep();  // 进入深度睡眠模式
  }

  if (SPIFFS.exists("/pre.bin")) {  // 检查/pre.bin文件是否存在
    File file = SPIFFS.open("/pre.bin", FILE_READ);  // 打开文件进行读取
    if (!file) {
      Serial.println("无法打开文件进行读取");  // 文件无法打开，输出提示信息
      return;
    }
    // 从文件中读取数据到数组
    size_t bytesRead = file.read(price_formerly, pre_size);

    Serial.println("File content:");  // 输出文件内容
    while (file.available()) {
      Serial.write(file.read());  // 逐字节读取文件内容
    }
    file.close();  // 关闭文件
 
    EPD_FastInit();  // 快速初始化屏幕
    EPD_ShowPicture(0, 128, 416, 112, price_formerly, WHITE); // 显示pre文件内容
    EPD_Display(ImageBW);  // 更新屏幕显示
    EPD_Update();  // 刷新屏幕
    EPD_DeepSleep();  // 进入深度睡眠模式
  }
}
