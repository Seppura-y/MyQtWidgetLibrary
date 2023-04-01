#pragma once
#include <QString>
#include <QJsonObject>
#include <QJsonArray>


class ScreenConfiguration
{
public:
    static enum ObjType
    {
        OBJ_TYPE_CAMERA = 0,
        OBJ_TYPE_WEB,
        OBJ_TYPE_AGENT,
        OBJ_TYPE_PICTURE,
        OBJ_TYPE_WIDGET,
        OBJ_TYPE_DIMENSION
    };

    static enum FileType
    {
        FILE_TYPE_ITEMLIST = 0,
        FILE_TYPE_WIDGET
    };

    static ScreenConfiguration* GetInstance()
    {
        static ScreenConfiguration screen_conf;
        return &screen_conf;
    }
    QJsonObject* GetObject(ObjType type);

    void InitJson();
    bool LoadJson(const QString& filePath);
    bool SaveJson(const QString& filepath,FileType type = FILE_TYPE_WIDGET);
    bool DeleteObject(const QString key, ObjType type);
    bool WriteJson(const QString key, QJsonObject object, enum ObjType type);
public:

private:
    ScreenConfiguration() {};
    bool isInit_ = false;
    QString filePath_;
    QJsonObject json_src_;

    QJsonObject json_wid_;
    QJsonObject json_cmr_;
    QJsonObject json_agn_;
    QJsonObject json_web_;
    QJsonObject json_pic_;
    QJsonObject json_dimen_;
};

