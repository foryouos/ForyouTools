#include "colorthread.h"
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonObject>
ColorThread::ColorThread(QObject *parent)
    : QObject{parent}
{
    QString currentPath = QCoreApplication::applicationDirPath();
    Current_Path = QDir::toNativeSeparators(currentPath);
}
// 初始化颜色传出 所有 颜色列表
void ColorThread::Color_Init_Slot()
{
    // 插入产品名称
    QString Dir_Name = Current_Path + "\\ChineseColors.json";
    QFile loadfile(Dir_Name);
    if(!loadfile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Could not  Open Json"<<  loadfile.errorString();
    }
    else
    {
        qDebug()<<"打开JSON文件成功";
        // 读取文件的全部内容
        QByteArray Color_Date = loadfile.readAll();

        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(Color_Date,&jsonError));
        if(jsonError.error != QJsonParseError::NoError)
        {
            qDebug()<<"JSON Error"<< jsonError.errorString();
        }
        else
        {
            QJsonObject rootObj = jsonDoc.object();
            // 得到了 中的 颜色 ，例如 红色 ，绿色 大方向的 颜色
            QJsonObject Color_obj = rootObj.value("data").toObject();
            for (auto it = Color_obj.begin(); it != Color_obj.end(); ++it)
            {
                // 获取键和值
                QString key = it.key();
                qDebug()<<key;
                QJsonValue Color_Detail = it.value();
                qDebug()<<"Detaul Keys:"<< Color_Detail;

            }
        }
    }



}
