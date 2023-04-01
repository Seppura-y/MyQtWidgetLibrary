//#include "json_proc.h"
//#include <QFile>
//#include <QJsonDocument>
//#include <QJsonParseError>
//#include <QJsonArray>
//QJsonObject ScreenConfiguration::GetJson()
//{
//    return json_obj_;
//}
//
//bool ScreenConfiguration::LoadJson(const QString& filepath)
//{
//    QFile loadFile(filepath);
//
//    if (!loadFile.open(QIODevice::ReadOnly))
//    {
//        //qDebug() << "Unable to load JSON file";
//        return false;
//    }
//
//
//    QByteArray allData = loadFile.readAll();
//    loadFile.close();
//
//    QJsonParseError json_error;
//    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
//
//    if (json_error.error != QJsonParseError::NoError)
//    {
//        qDebug() << "JSON error!";
//        return false;
//    }
//    //QJsonObject::iterator it;
//    //for (it = json_obj_.begin();it != json_obj_.end();it++)
//    //{
//    //    it = json_obj_.erase(it);
//    //}
//
//    json_obj_ = jsonDoc.object();
//    return true;
//}
//
//bool ScreenConfiguration::SaveJson(const QString& filepath)
//{
//    QJsonDocument document;
//    document.setObject(json_obj_);
//    QFile file(filepath);
//
//    if (!file.open(QIODevice::WriteOnly)) {
//        qDebug() << "Fail to save contents to JSON file";
//        return false;
//    }
//
//    file.write(document.toJson());
//
//    return true;
//}
//
//QString ScreenConfiguration::ToString()
//{
//    QJsonDocument document;
//    document.setObject(json_obj_);
//    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
//    QString str(byteArray);
//    return str;
//}
//
//
//void ScreenConfiguration::WriteJson(const QString key, bool value)
//{
//    json_obj_.insert(key, value);
//}
//
//void ScreenConfiguration::WriteJson(const QString key, int value)
//{
//    json_obj_.insert(key, value);
//}
//
//void ScreenConfiguration::WriteJson(const QString key, double value)
//{
//    json_obj_.insert(key, value);
//}
//
//void ScreenConfiguration::WriteJson(const QString key, QString value)
//{
//    json_obj_.insert(key, QString(value));
//}
//
//void ScreenConfiguration::WriteJson(const QString key, bool* array, int length)
//{
//    QJsonArray arr;
//    for (int i = 0; i < length; i++)
//        arr.append(array[i]);
//    json_obj_.insert(key, arr);
//}
//
//void ScreenConfiguration::WriteJson(const QString key, int* array, int length)
//{
//    QJsonArray arr;
//    for (int i = 0; i < length; i++)
//        arr.append(array[i]);
//    json_obj_.insert(key, arr);
//}
//
//void ScreenConfiguration::WriteJson(const QString key, double* array, int length)
//{
//    QJsonArray arr;
//    for (int i = 0; i < length; i++)
//        arr.append(array[i]);
//    json_obj_.insert(key, arr);
//}
//
//void ScreenConfiguration::WriteJson(const QString key, QJsonObject object)
//{
//    json_obj_.insert(key, object);
//}
//
