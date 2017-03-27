#ifndef DATA_H
#define DATA_H
#include <QString>
#include <QWidget>

#define CONFIGINI "/config.ini"
#define RUN_PATH QCoreApplication::applicationDirPath()

#define MAX_X_SIZE 800
#define MAX_Y_SIZE 480
#define MAX_W_SIZE 800
#define MAX_H_SIZE 480
#define MAX_BTN_NUM 5
#define MAX_LABLE_NUM 10
#define MAX_SET_TIME_KEY_NUM 2
#define MAX_NUM_BTN_NUM 6

enum ITEM_TYPE{
    BTN,LABEL,MSGBOX,INPUT_BTN,RTC,MOVE_ITEM
};
enum PROPERETY_SHOW_INDEX{
    MAIN_INDEX,BTN_INDEX,LABEL_INDEX,MSG_INDEX
};
typedef struct{
    int disx;
    int disy;
    int height;
    int width;
}CHANGE_RECT;
//显示类型
enum DATA_TYPE{
    INT,BCD,CARD_NUMBER,CHAGER_LENGTH,ASCII
};
enum DATA_LENGTH{
    ONE_BYTE =1,TWO_BYTE,THREE_BYTE,FOUR_BYTE
};
enum MSGBOX_NUM{
    MSGBOX_1 =1,MSGBOX_2,MSGBOX_3,MSGBOX_4,MSGBOX_5
    ,MSGBOX_6,MSGBOX_7,MSGBOX_8,MSGBOX_9,MSGBOX_10
    ,MSGBOX_11
};
//enum TABALE_INDEX{
//    PAGE_INDEX,BTN_INDEX,LAB_INDEX,NUM_KEY_INDEX,SET_TIME_INDEX,PASS_KEY_INDEX
//    ,MSGBOX_INDEX
//};

//enum REG_ADDR{
//    Version,LED_SET,BZ_TIME,PIC_ID_0,PIC_ID_1,TP_Flag,TP_Status,TP_Position,
//    TPC_Enable,RUN_TIME_0,RUN_TIME_1,RUN_TIME_2,RUN_TIME_3,
//    R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,RA,RB,RC
//};

struct BTN_INFO
{
    int page;//页码
    QWidget *parent;//父窗体
    QString ojName;
    int x;
    int y;
    int w;
    int h;
    QString image;
    int regesitData;// next page
    int dataStartAddr;//两个字节
    int dataData;//最大两个字节
    quint8 dataType;//数据类型
    quint8 dataDataOffSet;//数据偏移量
};

struct NUM_KEYBOARD_INFO
{
    int page;//页码
    QWidget *parent;//父窗体
    QString ojName;
    int x;
    int y;
    int w;
    int h;
    QString image;
    int dataAddr;   //数据储存区地址
    int dataDataLength;//数据储存区长度
    int dataType;//数据格式
    quint8 dataIntegerLength;//整数部分长度
    quint8 dataDecimalsLength;//小数部分长度 小数位数等于偏移量大小
};
struct SETTIME_KEY_INFO
{
    int page;//页码
    QWidget *parent;//父窗体
    QString ojName;
    int x;
    int y;
    int w;
    int h;
    QString image;
    int dataAddr;   //数据储存区地址
    char *dataData; //数据储存区数据
    int dataDataLength;//数据储存区长度
    int dataType;//数据格式
};
struct PASS_BTN_INFO
{
    int page;//页码
    QWidget *parent;//父窗体
    QString ojName;
    int x;
    int y;
    int w;
    int h;
    QString image;
};
struct LAB_INFO
{
    int page;//页码
    QWidget *parent;//父窗体
    QString ojName;
    int x;
    int y;
    int w;
    int h;
    QString image;
    int dataAddr;//数据寄存器地址
    int dataLength;//显示的数据长度
    int dataOffset;//数据偏移量
    int dataType;//数据类型
};
struct MESSAGEBOX_INFO
{
    int page;//所属页面
    QString image;
    QWidget *parent;//父窗体
    QString ojName;
    int keyNum;//键值
    int xShow;
    int yShow;
    int x;
    int y;
    int w;
    int h;
    int picNum;//原图的页码
};

typedef struct{
    int x;
    int y;
    int w;
    int h;
    QString name;
    int regesitData;
}KEY_INFO;


typedef struct
{
    int page;//页码
    QWidget *parent;//父窗体
    QString ojName;
    int lineEdit_x;
    int lineEdit_y;
    int lineEdit_w;
    int lineEdit_h;
    //lineEdit 关联的数据信息
    int dataStartAddr;// 起始地址 长度为占几个字节
    int dataDataLength;//
    quint8 dataType;//数据类型
    quint8 dataIntegerLength;//整数部分长度
    quint8 dataDecimalsLength;//小数部分长度 小数位数等于偏移量大小
    int dataData;//数据 最大两个字节 lineEdit 内的数据为要输入的数据
    int key_x;
    int key_y;
    bool isPass;//is password keyboard?
//    int key_w;
//    int key_h;
    QString lineEditImage;

    KEY_INFO KEY_0;
    KEY_INFO KEY_1;
    KEY_INFO KEY_2;
    KEY_INFO KEY_3;
    KEY_INFO KEY_4;
    KEY_INFO KEY_5;
    KEY_INFO KEY_6;
    KEY_INFO KEY_7;
    KEY_INFO KEY_8;
    KEY_INFO KEY_9;
    KEY_INFO KEY_OK;
    KEY_INFO KEY_ESC;
    KEY_INFO KEY_DEL;
    KEY_INFO KEY_DOT;
}KEYBOARD;

/** 功能:int 转压缩BCD
 *    示例: 34 => 0x34, 71 => 0x71
 *    说明: int 数据不能超过99，范围0<= i <= 99;
 */
#define INTTOBCD(i)  ((((i)/10) << 4)+((i)%10))

/** 功能:压缩BCD转int
*     示例:  0x35 => 35;  0x10 => 10;
*     说明:注意只能转换1个字节的
*/
#define BCDTOINT(i)  ((((i)&0xf0) >>4)*10+((i)&0x0f))

#endif

