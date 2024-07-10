#include <hi_early_debug.h>
#include <hi_i2c.h>
#include <hi_task.h>
#include <hi_time.h>
#include <hi_stdlib.h>
#include <hi_errno.h>
#include <hi_io.h>
#include <ohos_init.h>
#include <cmsis_os2.h>
#include <iot_gpio.h>
#include "iot_gpio_ex.h"
#include "ssd1306.h"
#include "iot_i2c.h"
#include "aht20.h"
#include <stdlib.h>
#include <stdio.h>
#include <hi_gpio.h>
#include <math.h>
#include "iot_gpio.h"
#include <hi_gpio.h>
#include <hi_watchdog.h>

#define LED_LIGHT_DELAY_1S       (1)
#define LED_CONTROL_TASK_SLEEP_20MS (20)

#define IOT_I2C_IDX_BAUDRATE (400 * 1000)
#define SSD1306_I2C_IDX 0
//按键
#define ROW         (1)
#define COLUMN      (2)
/* 行 */
IotGpioValue gpio_6_val = IOT_GPIO_VALUE0;
/* 列 */
IotGpioValue gpio_0_val = IOT_GPIO_VALUE0, gpio_1_val = IOT_GPIO_VALUE0;
unsigned char l = 0, h = 0;
const unsigned char headSize[] = { 64, 64 };

//步进电机
void bujingdianji_init(void)
{
    IoSetFunc(IOT_IO_NAME_GPIO_3, IOT_IO_FUNC_GPIO_3_GPIO);
    IoTGpioSetDir(IOT_IO_NAME_GPIO_3, IOT_GPIO_DIR_OUT);

    IoSetFunc(IOT_IO_NAME_GPIO_4, IOT_IO_FUNC_GPIO_4_GPIO);
    IoTGpioSetDir(IOT_IO_NAME_GPIO_4, IOT_GPIO_DIR_OUT);

    IoSetFunc(IOT_IO_NAME_GPIO_5, IOT_IO_FUNC_GPIO_5_GPIO);
    IoTGpioSetDir(IOT_IO_NAME_GPIO_5, IOT_GPIO_DIR_OUT);

    IoSetFunc(IOT_IO_NAME_GPIO_7, IOT_IO_FUNC_GPIO_7_GPIO);
    IoTGpioSetDir(IOT_IO_NAME_GPIO_7, IOT_GPIO_DIR_OUT);
}

void xuanzhuan_control(void)
{
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_3, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_4, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_7, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_3, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_4, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_7, IOT_GPIO_VALUE0);
    TaskMsleep(LED_LIGHT_DELAY_1S);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_3, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_4, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_7, IOT_GPIO_VALUE0);
    TaskMsleep(LED_LIGHT_DELAY_1S);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_3, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_4, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_7, IOT_GPIO_VALUE0);
    TaskMsleep(LED_LIGHT_DELAY_1S);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_3, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_4, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_7, IOT_GPIO_VALUE0);
    TaskMsleep(LED_LIGHT_DELAY_1S);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_3, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_4, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_7, IOT_GPIO_VALUE0);
    TaskMsleep(LED_LIGHT_DELAY_1S);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_3, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_4, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_7, IOT_GPIO_VALUE1);
    TaskMsleep(LED_LIGHT_DELAY_1S);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_3, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_4, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_7, IOT_GPIO_VALUE1);
    TaskMsleep(LED_LIGHT_DELAY_1S);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_3, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_4, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_7, IOT_GPIO_VALUE1);
    TaskMsleep(LED_LIGHT_DELAY_1S);
}

/*void bujindianji_90_control(void)
{
    bujingdianji_init();
    for (int i = 0; i <= (8*16); i++)
    {
       xuanzhuan_control();
    }    
}

void bujindianji_180_control(void)
{
    bujingdianji_init();
    for (int i = 0; i <= (8*16); i++)
    {
       xuanzhuan_control();
    }    
}*/

void led_gpio(void){
    IoTGpioInit(IOT_IO_NAME_GPIO_11);
    IoSetFunc(IOT_IO_NAME_GPIO_11,IOT_IO_FUNC_GPIO_11_GPIO);
    IoTGpioSetDir(IOT_IO_NAME_GPIO_11, IOT_GPIO_DIR_OUT);
}

void keyboard_gpio_config(unsigned char mode)
{
    IoSetFunc(IOT_IO_NAME_GPIO_6, IOT_IO_FUNC_GPIO_6_GPIO);

    IoSetFunc(IOT_IO_NAME_GPIO_0, IOT_IO_FUNC_GPIO_0_GPIO);
    IoSetFunc(IOT_IO_NAME_GPIO_1, IOT_IO_FUNC_GPIO_1_GPIO);
    /* 初始化行输入，列输出 */
    if (mode == HI_TRUE) {
        IoTGpioSetDir(IOT_IO_NAME_GPIO_6, IOT_GPIO_DIR_IN);

        IoTGpioSetDir(IOT_IO_NAME_GPIO_0, HI_GPIO_DIR_OUT);
        IoTGpioSetDir(IOT_IO_NAME_GPIO_1, HI_GPIO_DIR_OUT);
    } else {
        IoTGpioSetDir(IOT_IO_NAME_GPIO_6, HI_GPIO_DIR_OUT);

        IoTGpioSetDir(IOT_IO_NAME_GPIO_0, IOT_GPIO_DIR_IN);
        IoTGpioSetDir(IOT_IO_NAME_GPIO_1, IOT_GPIO_DIR_IN);
    }
}
void gpio_init(void)
{
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_6, IOT_GPIO_VALUE0);
    
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_0,  IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_1,  IOT_GPIO_VALUE0);
}
/* 行扫描 */
void row_scan_output(void)
{
    // 行输出置低
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_6, IOT_GPIO_VALUE0);
    
    // 列输出置高
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_0,  IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_1,  IOT_GPIO_VALUE1);
}
/* 列扫描 */
void column_scan_output(void)
{
    // 行输出置高
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_6, IOT_GPIO_VALUE1);

    // 二次扫描 列输出置低
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_0,  IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_1,  IOT_GPIO_VALUE0);
}
void get_gpio_input_value(IotGpioValue* val_1, IotGpioValue* val_2, unsigned char row_column_flag)
{
    if (row_column_flag == ROW) {
        IoTGpioGetInputVal(IOT_IO_NAME_GPIO_6, val_1);

    }
    if (row_column_flag == COLUMN) {
        IoTGpioGetInputVal(IOT_IO_NAME_GPIO_0, val_1);
        IoTGpioGetInputVal(IOT_IO_NAME_GPIO_1, val_2);
    }
}
/* 行扫描 */
void key_press_line_scan(void)
{
    if (gpio_6_val == 1) { // 检测按下的按键所在行
            h = 1;
    }
    if (gpio_6_val!=1) {
            h = 0; 
        }
       
}
/* 列扫描 */
void key_press_column_scan(void)
{
    if ((gpio_0_val==1) || (gpio_1_val==1)) { // 检测按下的按键所在列
        /* 第一行 */
        if ((gpio_0_val == 1) && (h == 1)) {
            bujingdianji_init();
            for (int i = 0; i <= (8*16); i++)
            {
            xuanzhuan_control();
            }    
        } else if ((gpio_1_val == 1) && (h == 1)) {
            bujingdianji_init();
            for (int i = 0; i <= (8*32); i++)
            {
            xuanzhuan_control();
            }    
        } 
    }
}

//语音
void yuyin_gpio_init(void){
    IoTGpioInit(IOT_IO_NAME_GPIO_10);
    IoSetFunc(IOT_IO_NAME_GPIO_10,IOT_IO_FUNC_GPIO_10_GPIO);
    IoTGpioSetDir(IOT_IO_NAME_GPIO_10, IOT_GPIO_DIR_IN);

    IoTGpioInit(IOT_IO_NAME_GPIO_9);
    IoSetFunc(IOT_IO_NAME_GPIO_9,IOT_IO_FUNC_GPIO_9_GPIO);
    IoTGpioSetDir(IOT_IO_NAME_GPIO_9, IOT_GPIO_DIR_IN);
}

void TempHumChinese(void)
{
    const uint32_t W = 16;
    uint8_t fonts[][32] = {
        {
           /* -- ID:0,字符:"温",ASCII编码:CEC2,对应字:宽x高=16x16,画布:宽W=16 高H=16,共32字节 */
            0x00, 0x08, 0x43, 0xFC, 0x32, 0x08, 0x12, 0x08, 0x83, 0xF8, 0x62, 0x08, 0x22, 0x08, 0x0B, 0xF8,
            0x10, 0x00, 0x27, 0xFC, 0xE4, 0xA4, 0x24, 0xA4, 0x24, 0xA4, 0x24, 0xA4, 0x2F, 0xFE, 0x20, 0x00
        }, {
            /* -- ID:0,字符:"度",ASCII编码:B6C8,对应字:宽x高=16x16,画布:宽W=16 高H=16,共32字节 */
            0x01, 0x00, 0x00, 0x84, 0x3F, 0xFE, 0x22, 0x20, 0x22, 0x28, 0x3F, 0xFC, 0x22, 0x20, 0x23, 0xE0,
            0x20, 0x00, 0x2F, 0xF0, 0x22, 0x20, 0x21, 0x40, 0x20, 0x80, 0x43, 0x60, 0x8C, 0x1E, 0x30, 0x04
        }
    };
    uint8_t fonts2[][32] = {
        {
           /* -- ID:0,字符:"湿",ASCII编码:CEC2,对应字:宽x高=16x16,画布:宽W=16 高H=16,共32字节 */
            0x00, 0x08, 0x47, 0xFC, 0x34, 0x08, 0x14, 0x08, 0x87, 0xF8, 0x64, 0x08, 0x24, 0x08, 0x0F, 0xF8,
            0x11, 0x20, 0x21, 0x20, 0xE9, 0x24, 0x25, 0x28, 0x23, 0x30, 0x21, 0x24, 0x3F, 0xFE, 0x20, 0x00
        }, {
            /* -- ID:0,字符:"度",ASCII编码:B6C8,对应字:宽x高=16x16,画布:宽W=16 高H=16,共32字节 */
            0x01, 0x00, 0x00, 0x84, 0x3F, 0xFE, 0x22, 0x20, 0x22, 0x28, 0x3F, 0xFC, 0x22, 0x20, 0x23, 0xE0,
            0x20, 0x00, 0x2F, 0xF0, 0x22, 0x20, 0x21, 0x40, 0x20, 0x80, 0x43, 0x60, 0x8C, 0x1E, 0x30, 0x04
        }
    };
    for (size_t i = 0; i < sizeof(fonts) / sizeof(fonts[0]); i++) {
        ssd1306_DrawRegion(i * W, 3, W, fonts[i], sizeof(fonts[0])); // x轴坐标i*w，y轴坐标3，宽度为16
    }
    for (size_t j = 0; j < sizeof(fonts2) / sizeof(fonts2[0]); j++) {
        ssd1306_DrawRegion(j * W, 35, W, fonts2[j], sizeof(fonts2[0])); // x轴坐标i*w，y轴坐标35，宽度为16
    }
}

void Aht20TestTask(void)
{
    uint32_t retval = 0;
    float temp = 0.0f;
    float humi = 0.0f;
    static char line[32] = {0};
    IotGpioValue yuyinone={0};
    IotGpioValue yuyintwo={0};
    bujingdianji_init();
    xuanzhuan_control();
    led_gpio();
    yuyin_gpio_init();
    IoSetFunc(IOT_IO_NAME_GPIO_13, IOT_IO_FUNC_GPIO_13_I2C0_SDA);
    IoSetFunc(IOT_IO_NAME_GPIO_14, IOT_IO_FUNC_GPIO_14_I2C0_SCL);
    IoTI2cInit(SSD1306_I2C_IDX, IOT_I2C_IDX_BAUDRATE);
    IoTI2cSetBaudrate(SSD1306_I2C_IDX, IOT_I2C_IDX_BAUDRATE);

    unsigned int time1 = 20000;
    usleep(time1);3
    ssd1306_Init();
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);

    while (AHT20_Calibrate() != HI_ERR_SUCCESS) {
        printf("AHT20 sensor init failed!\r\n");
        usleep(1000); // 1ms = 1000
    }

    while (1) {
        IoTGpioGetInputVal(IOT_IO_NAME_GPIO_10,&yuyinone);
        IoTGpioGetInputVal(IOT_IO_NAME_GPIO_9,&yuyintwo);
        if (yuyinone==1)
        {
            bujingdianji_init();
            for (int i = 0; i <= (8*16); i++)
            {
            xuanzhuan_control();
            }    
            IoTGpioGetInputVal(IOT_IO_NAME_GPIO_10,&yuyinone);
            if (yuyinone==0)
            {
                return;
            }
        }

        if (yuyintwo==1)
        {
            bujingdianji_init();
            for (int i = 0; i <= (8*32); i++)
            {
            xuanzhuan_control();
            }    
            IoTGpioGetInputVal(IOT_IO_NAME_GPIO_9,&yuyintwo);
            if (yuyintwo==0)
            {
                return;
            }
        }
        gpio_6_val = IOT_GPIO_VALUE0;
        gpio_0_val = IOT_GPIO_VALUE0, gpio_1_val = IOT_GPIO_VALUE0;
        l = 0, h = 0;
        gpio_init();
        keyboard_gpio_config(HI_TRUE);
        TaskMsleep(20);
        row_scan_output();
        get_gpio_input_value(&gpio_6_val, 0,ROW);
        key_press_line_scan();
        gpio_init();
        keyboard_gpio_config(HI_FALSE);
        TaskMsleep(20);
        column_scan_output();
        get_gpio_input_value(&gpio_0_val, &gpio_1_val,COLUMN);
        key_press_column_scan();
        TaskMsleep(100); 
        TempHumChinese();
        retval = AHT20_StartMeasure();
        printf("AHT20_StartMeasure: %d\r\n", retval);

        retval = AHT20_GetMeasureResult(&temp, &humi);
        if (retval != HI_ERR_SUCCESS) {
            printf("get humidity data failed!\r\n");
        }
        printf("AHT20_GetMeasureResult: %d, temp = %.2f, humi = %.2f\r\n", retval, temp, humi);
        ssd1306_SetCursor(32, 8); /* x坐标为32，y轴坐标为8 */

        if (humi>=30)
        {
             IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_11,IOT_GPIO_VALUE1);
        }
        
        if (humi<30)
        {
             IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_11,IOT_GPIO_VALUE0);
        }
        

        int ret = snprintf_s(line, sizeof(line), sizeof(line), ": %.2f", temp);
        if (ret == 0) {
            printf("temp failed\r\n");
        }
        ssd1306_DrawString(line, Font_7x10, White);

        ret = snprintf_s(line, sizeof(line), sizeof(line), ": %.2f", humi);
        if (ret == 0) {
            printf("humi failed\r\n");
        }
        ssd1306_SetCursor(32, 40); /* x坐标为32，y轴坐标为40 */
        ssd1306_DrawString(line, Font_7x10, White);
        ssd1306_UpdateScreen();
        TaskMsleep(100); 
    }
}

void Aht20Test(void)
{
    osThreadAttr_t attr;
    IoTWatchDogDisable();
    attr.name = "Aht20TestTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 5 * 1024; // 任务栈大小为5 *1024
    attr.priority = osPriorityNormal;
    if (osThreadNew((osThreadFunc_t)Aht20TestTask, NULL, &attr) == NULL) {
        printf("[Aht20TestTask] Failed to create BalanceTask!\n");
    }
}

APP_FEATURE_INIT(Aht20Test);
