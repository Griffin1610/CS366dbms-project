#include "backend.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

using namespace std;
using std::string;

Backend::Backend() {}

Backend::~Backend() {
    if(db.isOpen()) {
        db.close();
    }
}

// Total queries
int Backend::totalWork() {
    int count = -1;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "totalWork");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if(!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
    }

    QSqlQuery query(db);
    if(query.exec("SELECT COUNT(*) FROM work")) {
        if(query.next()) {
            int count = query.value(0).toInt();
        }
        else {
            qDebug() << "Query failed.";
        }
    }
    return count;
}


// Artist queries
vector<string> Backend::artistNameList() {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);
    if (query.exec("SELECT full_name FROM artist")) {
        while (query.next()) {
            result.push_back(query.value(0).toString().toStdString());
        }
    } else {
        qDebug() << "Query failed:" << query.lastError().text();
    }

    return result;
}

vector<string> Backend::searchArtistWork(const string& artistName) {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    // Stored procedure call
    query.prepare("{ CALL getArtistWork(?) }");
    query.bindValue(0, QString::fromStdString(artistName));

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        QString name = query.value("name").toString();
        result.push_back(name.toStdString());
    }

    if (result.empty()) {
        qDebug() << "Artist not found or there is no work made by artist.";
    }

    return result;
}

vector<string> Backend::searchArtistStyle(const string& artistName) {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    query.prepare("{ CALL getArtistStyle(?) }");
    query.bindValue(0, QString::fromStdString(artistName)); // Bind artistName parameter

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    // If the query was successful, process the results
    if (query.next()) {
        QString fullName = query.value("full_name").toString();
        QString style = query.value("style").toString();

        result.push_back(fullName.toStdString());
        result.push_back(style.toStdString());
    }
    else {
        qDebug() << "Artist not found.";
    }

    return result;
}

vector<string> Backend::searchArtistByName(const string& artistName) {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    query.prepare("{ CALL getArtistName(?) }");
    query.bindValue(0, QString::fromStdString(artistName)); // Bind artistName parameter

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    // If the query was successful, process the results
    if (query.next()) {
        QString fullName = query.value("full_name").toString();
        QString nationality = query.value("nationality").toString();
        QString style = query.value("style").toString();
        QString birth = QString::number(query.value("birth").toInt());
        QString death = QString::number(query.value("death").toInt());

        result.push_back(fullName.toStdString());
        result.push_back(nationality.toStdString());
        result.push_back(style.toStdString());
        result.push_back(birth.toStdString());
        result.push_back(death.toStdString());
    } else {
        qDebug() << "Artist not found.";
    }

    return result;
}

vector<string> Backend::searchArtistWorkPrice(const string& artistName) {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    query.prepare("{ CALL getArtistWorkPrice(?) }");
    query.bindValue(0, QString::fromStdString(artistName));

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    while(query.next()) {
        QString name = query.value("name").toString();
        QString salePrice = query.value("sale_price").toString();
        QString regularPrice = query.value("regular_price").toString();

        result.push_back(name.toStdString());
        result.push_back(salePrice.toStdString());
        result.push_back(regularPrice.toStdString());
    }

    if (result.empty()) {
        qDebug() << "Work not found.";
    }

    return result;
}



//vector<string> Backend::

// Museum queries
vector<string> Backend::searchMuseumInfoByName(const string& museumName) {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    query.prepare("{ CALL getMuseumInfoByName(?) }");
    query.bindValue(0, QString::fromStdString(museumName));

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    // Process the result set
    while (query.next()) {
        QString name = query.value("name").toString();
        QString phone = query.value("phone").toString();
        QString url = query.value("url").toString();

        result.push_back(name.toStdString());
        result.push_back(phone.toStdString());
        result.push_back(url.toStdString());
    }

    if (result.empty()) {
        qDebug() << "Museum not found.";
    }

    return result;
}

vector<string> Backend::searchMuseumDaysAndHoursByName(const string& museumName) {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    query.prepare("{ CALL getMuseumDaysAndHours(?) }");
    query.bindValue(0, QString::fromStdString(museumName));

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        QString day = query.value("day").toString();
        QString open = query.value("open").toString();
        QString close = query.value("close").toString();

        result.push_back(day.toStdString());
        result.push_back(open.toStdString());
        result.push_back(close.toStdString());
    }

    if (result.empty()) {
        qDebug() << "Museum not found.";
    }

    return result;
}

vector<string> Backend::searchAddressInfo() {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    query.prepare("{ SELECT country, state, city FROM address }");
    //query.bindValue(0, QString::fromStdString());

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        QString country = query.value("country").toString();
        QString state = query.value("state").toString();
        QString city = query.value("city").toString();

        result.push_back(country.toStdString());
        result.push_back(state.toStdString());
        result.push_back(city.toStdString());
    }

    if (result.empty()) {
        qDebug() << "Museum not found.";
    }

    return result;
}

vector<string> Backend::searchMuseumWork(const string& museumName) {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    query.prepare("{ CALL getMuseumWork(?) }");
    query.bindValue(0, QString::fromStdString(museumName));

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        QString name = query.value("name").toString();
        result.push_back(name.toStdString());
    }

    if (result.empty()) {
        qDebug() << "Museum not found.";
    }

    return result;
}

vector<string> Backend::searchMuseumAddress(const string& museumName) {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    query.prepare("{ CALL getMuseumAddress(?) }");
    query.bindValue(0, QString::fromStdString(museumName));

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        QString name = query.value("name").toString();
        QString country = query.value("country").toString();
        QString state = query.value("state").toString();
        QString city = query.value("city").toString();

        result.push_back(name.toStdString());
        result.push_back(country.toStdString());
        result.push_back(state.toStdString());
        result.push_back(city.toStdString());
    }

    if (result.empty()) {
        qDebug() << "Museum not found.";
    }

    return result;
}

vector<string> Backend::searchMuseumArtist(const string& museumName) {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    query.prepare("{ CALL getArtistInMuseum(?) }");
    query.bindValue(0, QString::fromStdString(museumName));

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        QString name = query.value("full_name").toString();
        result.push_back(name.toStdString());
    }

    if (result.empty()) {
        qDebug() << "Museum not found.";
    }

    return result;
}

// Work Queries
vector<string> Backend::searchWorkPrice(const string& workName) {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    query.prepare("{ CALL getWorkPrice(?) }");
    query.bindValue(0, QString::fromStdString(workName));

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    // Process the result set
    while (query.next()) {
        QString name = query.value("name").toString();
        QString salePrice = query.value("sale_price").toString();
        QString regularPrice = query.value("regular_price").toString();

        result.push_back(name.toStdString());
        result.push_back(salePrice.toStdString());
        result.push_back(regularPrice.toStdString());
    }

    if (result.empty()) {
        qDebug() << "Work not found.";
    }

    return result;
}

vector<string> Backend::searchWorkInMuseum(const string& workName) {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    query.prepare("{ CALL getWorkInMuseum(?) }");
    query.bindValue(0, QString::fromStdString(workName));

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    while(query.next()) {
        QString name = query.value("name").toString();
        result.push_back(name.toStdString());
    }
    if (result.empty()) {
        qDebug() << "Work not found.";
    }

    return result;
}

vector<string> Backend::searchWorkSize(const string& workSize) {
    vector<string> result;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "artistNameList");
    db.setDatabaseName("Paintings");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return result; // Return empty list on failure
    }

    QSqlQuery query(db);

    query.prepare("{ CALL getWorkSize(?) }");
    query.bindValue(0, QString::fromStdString(workSize));

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return result;
    }

    while(query.next()) {
        QString name = query.value("name").toString();
        QString width = query.value("width").toString();
        QString height = query.value("height").toString();

        result.push_back(name.toStdString());
        result.push_back(width.toStdString());
        result.push_back(height.toStdString());
    }
    if (result.empty()) {
        qDebug() << "Work not found.";
    }

    return result;
}
// WorkInfoByID (for getting random potd)
