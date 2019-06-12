#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QTreeWidgetItem>
#include <QDebug>
#include <mongocxx/logger.hpp>
#include <memory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::unique_ptr<mongocxx::pool> uptr_pool(new mongocxx::pool(mongocxx::uri("mongodb://192.168.1.94:27017")));
    std::unique_ptr<mongocxx::instance> uptr_instance(new mongocxx::instance());
    bool a = MongoDatabase.Initialize(std::move(uptr_instance), std::move(uptr_pool));

    auto connection = MongoDatabase.TryGetConnection();
    if(!connection)
    {
        qDebug()<<"MongoDatabase GetConn failed";
        return;
    }

    mongocxx::client &conn = **connection;
    mongocxx::database db = conn["bmi_ai"];
    mongocxx::collection human_collection = db["human"];

    bsoncxx::builder::stream::document index_builder;
    index_builder << "absTimestamp" << -1;
    try{
        human_collection.create_index(index_builder.view());
    }catch(const std::exception& e){
        qDebug()<<e.what();
        exit(0);
    }


    QStringList database_head;
    database_head <<"id"<<"absTimestamp" << "rect_x"<< "rect_y"<< "rect_width"<< "rect_height"<< "name"<< "age"<< "gender"
                 << "channel_number"<< "gender_confidence"<< "feature_confidence"<< "match_confidence"<< "flag"<< "jpeg_base64"<< "feature";
    ui->treeWidget_database->setHeaderLabels(database_head);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_connect_clicked()
{
//    mongocxx::ScopedDbConnection scopedConn = mongo::ScopedDbConnection(DBHost);

    ui->treeWidget_database->clear();

    try
    {
        auto connection = MongoDatabase.TryGetConnection();
        if(!connection)
        {
            qDebug()<<"MongoDatabase GetConn failed";
            return;
        }

        mongocxx::client &conn = **connection;
        mongocxx::database db = conn["bmi_ai"];
        mongocxx::collection human_collection = db["human"];

        auto cursor = human_collection.find({});

        for (auto&& doc : cursor) {
            QStringList one_info;
            bsoncxx::document::element id = doc["_id"];
            bsoncxx::document::element absTimestamp = doc["absTimestamp"];
            bsoncxx::document::element rect_x = doc["rect_x"];
            bsoncxx::document::element rect_y = doc["rect_y"];
            bsoncxx::document::element rect_width = doc["rect_width"];
            bsoncxx::document::element rect_height = doc["rect_height"];
            bsoncxx::document::element name = doc["name"];
            bsoncxx::document::element age = doc["age"];
            bsoncxx::document::element gender = doc["gender"];
            bsoncxx::document::element channel_number = doc["channel_number"];
            bsoncxx::document::element gender_confidence = doc["gender_confidence"];
            bsoncxx::document::element feature_confidence = doc["feature_confidence"];
            bsoncxx::document::element match_confidence = doc["match_confidence"];
            bsoncxx::document::element flag = doc["flag"];
            bsoncxx::document::element jpeg_base64 = doc["jpeg_base64"];
            bsoncxx::document::element feature = doc["feature"];


            one_info.append(QString::fromLocal8Bit(id.get_oid().value.to_string().c_str()));
            one_info.append(QString::number(absTimestamp.get_int64().value));
            one_info.append(QString::number(rect_x.get_int32().value));
            one_info.append(QString::number(rect_y.get_int32().value));
            one_info.append(QString::number(rect_width.get_int32().value));
            one_info.append(QString::number(rect_height.get_int32().value));

            one_info.append(QString::fromUtf8(name.get_utf8().value.data()));
            one_info.append(QString::number(age.get_int32().value));
            one_info.append(QString::fromUtf8(gender.get_utf8().value.data()));
            one_info.append(QString::number(channel_number.get_int32().value));
            one_info.append(QString::number(gender_confidence.get_double().value));
            one_info.append(QString::number(feature_confidence.get_double().value));
            one_info.append(QString::number(match_confidence.get_double().value));
            one_info.append(QString::number(flag.get_int32().value));
            one_info.append(QString::fromUtf8((jpeg_base64.get_utf8().value.data())));
            one_info.append(QString::fromUtf8((feature.get_utf8().value.data())));

            QTreeWidgetItem *item = new QTreeWidgetItem(one_info);

            ui->treeWidget_database->addTopLevelItem(item);
        }


    }catch(const std::exception& e){

    }

}

void MainWindow::on_btn_insert_clicked()
{
    try
    {
        auto connection = MongoDatabase.TryGetConnection();
        if(!connection)
        {
            qDebug()<<"MongoDatabase GetConn failed";
            return;
        }

        mongocxx::client &conn = **connection;
        mongocxx::database db = conn["bmi_ai"];
        mongocxx::collection human_collection = db["human"];

        bsoncxx::document::value restaurant_doc =
                document{} <<"absTimestamp" << int64_t(1111111111111)
                          << "rect_x" << int32_t(100)
                          << "rect_y"<< int32_t(100)
                          << "rect_width"<< int32_t(200)
                          << "rect_height"<< int32_t(200)
                          << "name"<< "wenge"
                          << "age"<< int32_t(18)
                          << "gender"<< "male"
                          << "channel_number"<< int32_t(2)
                          << "gender_confidence"<< 0.2
                          << "feature_confidence"<< 0.2
                          << "match_confidence"<< 0.2
                          << "flag"<< int32_t(0)
                          << "jpeg_base64"<< "1111111111111"
                          << "feature" <<"1111111111111"<< finalize;

        human_collection.insert_one(restaurant_doc.view());
    }catch(const std::exception& e){

    }

    on_btn_connect_clicked();
}

void MainWindow::on_btn_remove_clicked()
{
    QTreeWidgetItem * currentItem = ui->treeWidget_database->currentItem();
    if(currentItem)
    {
        try
        {
            auto connection = MongoDatabase.TryGetConnection();
            if(!connection)
            {
                qDebug()<<"MongoDatabase GetConn failed";
                return;
            }

            mongocxx::client &conn = **connection;
            mongocxx::database db = conn["bmi_ai"];
            mongocxx::collection human_collection = db["human"];

            std::string objectId = currentItem->text(0).toStdString();
            bsoncxx::oid objectOid= bsoncxx::oid(objectId);

            bsoncxx::builder::stream::document filter_builder;
            filter_builder << "_id"
                           << objectOid;
            human_collection.delete_one(filter_builder.view());
        }catch(const std::exception& e){

        }
    }
}

void MainWindow::on_btn_update_clicked()
{
    QTreeWidgetItem * currentItem = ui->treeWidget_database->currentItem();
    if(currentItem)
    {
        try
        {
            auto connection = MongoDatabase.TryGetConnection();
            if(!connection)
            {
                qDebug()<<"MongoDatabase GetConn failed";
                return;
            }

            mongocxx::client &conn = **connection;
            mongocxx::database db = conn["bmi_ai"];
            mongocxx::collection human_collection = db["human"];


            std::string objectId = currentItem->text(0).toStdString();
            bsoncxx::oid objectOid= bsoncxx::oid(objectId);

            bsoncxx::builder::stream::document filter_builder;
            filter_builder << "_id"
                           << objectOid;

            bsoncxx::builder::stream::document update_builder;
            update_builder << "$set" << open_document  << "flag"
                           << int32_t(5)<< close_document;
            human_collection.update_one(filter_builder.view(),update_builder.view());
        }catch(const std::exception& e){

        }
    }
    on_btn_connect_clicked();
}
