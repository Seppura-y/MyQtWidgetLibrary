#include "screen_configuration.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>

#define ITEM_LIST_CONFIG "./config/item_list_conf.json"
#define GRID_CONFIG "./config/grid_conf.json"
#define DIMENSION_CONFIG "./config/dimension.json"

bool ScreenConfiguration::LoadJson(const QString& filePath)
{
    QFile loadFile(filePath);

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        //qDebug() << "Unable to load JSON file";
        isInit_ = false;
        return false;
    }


    QByteArray allData = loadFile.readAll();
    loadFile.close();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

    if (json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "JSON error!";
        isInit_ = false;
        return false;
    }

    json_src_ = jsonDoc.object();
    if (json_src_.contains("Camera"))
    {
        json_cmr_ = json_src_["Camera"].toObject();
    }

    if (json_src_.contains("Agent"))
    {
        json_agn_ = json_src_["Agent"].toObject();
    }

    if (json_src_.contains("Web"))
    {
        json_web_ = json_src_["Web"].toObject();
    }

    if (json_src_.contains("Picture"))
    {
        json_pic_ = json_src_["Picture"].toObject();
    }

    if (json_src_.contains("Widget"))
    {
        json_wid_ = json_src_["Widget"].toObject();
    }

    if (json_src_.contains("Dimension"))
    {
        json_dimen_ = json_src_["Dimension"].toObject();
    }

    isInit_ = true;
    return true;
}

void ScreenConfiguration::InitJson()
{
    this->LoadJson(ITEM_LIST_CONFIG);
    this->LoadJson(GRID_CONFIG);
    this->LoadJson(DIMENSION_CONFIG);
}

bool ScreenConfiguration::SaveJson(const QString& filepath,FileType type)
{
    QFile file(filepath);
    QJsonObject save_obj;
    if (type == FILE_TYPE_WIDGET)
    {
        save_obj.insert("Widget", json_wid_);
    }
    else
    {
        save_obj.insert("Camera", json_cmr_);
        save_obj.insert("Agent", json_agn_);
        save_obj.insert("Web", json_web_);
        save_obj.insert("Picture", json_pic_);
    }

    QJsonDocument document;
    document.setObject(save_obj);

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Fail to save contents to JSON file";
        return false;
    }

    file.write(document.toJson());
    file.close();

    return true;
}


bool ScreenConfiguration::WriteJson(const QString key, QJsonObject object, enum ObjType type)
{
    QJsonObject* temp = nullptr;
    switch (type)
    {
        case ObjType::OBJ_TYPE_CAMERA:
        {
            temp = &json_cmr_;
            break;
        }
        case ObjType::OBJ_TYPE_AGENT:
        {
            temp = &json_agn_;
            break;
        }
        case ObjType::OBJ_TYPE_WEB:
        {
            temp = &json_web_;
            break;
        }
        case ObjType::OBJ_TYPE_PICTURE:
        {
            temp = &json_pic_;
            break;
        }
        case ObjType::OBJ_TYPE_WIDGET:
        {
            temp = &json_wid_;
            break;
        }
        //case ObjType::OBJ_TYPE_DIMENSION:
        //{
        //    temp = &json_dimen_;
        //    break;
        //}
    }
    if (!temp)
    {
        return false;
    }
    else
    {
        (*temp).insert(key, object);
    }
    return true;
}

QJsonObject* ScreenConfiguration::GetObject(ObjType type)
{
    QJsonObject temp;
    QString key;
    switch (type)
    {
        case ObjType::OBJ_TYPE_CAMERA:
        {
            return &json_cmr_;
        }
        case ObjType::OBJ_TYPE_AGENT:
        {
            return &json_agn_;
        }
        case ObjType::OBJ_TYPE_WEB:
        {
            return &json_web_;
        }
        case ObjType::OBJ_TYPE_PICTURE:
        {
            return &json_pic_;
        }
        case ObjType::OBJ_TYPE_WIDGET:
        {
            return &json_wid_;
        }
        case ObjType::OBJ_TYPE_DIMENSION:
        {
            return &json_dimen_;
        }
    }
}

bool ScreenConfiguration::DeleteObject(const QString key, ObjType type)
{
    QJsonObject* temp = nullptr;
    switch (type)
    {
        case ObjType::OBJ_TYPE_CAMERA:
        {
            temp = &json_cmr_;
            break;
        }
        case ObjType::OBJ_TYPE_AGENT:
        {
            temp = &json_agn_;
            break;
        }
        case ObjType::OBJ_TYPE_WEB:
        {
            temp = &json_web_;
            break;
        }
        case ObjType::OBJ_TYPE_PICTURE:
        {
            temp = &json_pic_;
            break;
        }
        case ObjType::OBJ_TYPE_WIDGET:
        {
            temp = &json_wid_;
            break;
        }
        case ObjType::OBJ_TYPE_DIMENSION:
        {
            temp = &json_dimen_;
            break;
        }
    }
    if (!temp)
    {
        return false;
    }
    else
    {
        if ((*temp).contains(key) && (*temp).find(key).value().isObject())
        {
            (*temp).erase((*temp).find(key));
        }
    }

    return true;
}
