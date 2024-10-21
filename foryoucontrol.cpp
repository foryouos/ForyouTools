#include "foryoucontrol.h"

ForyouControl::ForyouControl(QObject *parent)
    : QObject{parent}
{

}

ForyouControl::~ForyouControl()
{
    //TODO析构函数
    // if(colorthread != nullptr && Color_Thread != nullptr && Color_Thread->isRunning())
    // {
    //     Color_Thread->quit();
    //     Color_Thread->wait();
    //     Color_Thread->exit();
    //     delete Color_Thread;
    //     Color_Thread = nullptr;
    //     delete colorthread;
    //     colorthread = nullptr;
    // }
}

void ForyouControl::ForyouControl_Init()
{
    qDebug()<<"1,foryoucontrol 初始化";
    // 初始化右下角弹窗通知
    // this->Notify_init();
    // 初始化 中国传统颜色
    this->Chinese_Color_Init();

}



void ForyouControl::Chinese_Color_Init()
{
    // Color_Thread = new QThread;
    // colorthread = new ColorThread;
    // connect(Color_Thread,&QThread::started,colorthread,&ColorThread::Color_Init_Slot);
    // colorthread->moveToThread(Color_Thread);
    // Color_Thread->start();
}
