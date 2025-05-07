#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <memory>
#include <vector>
using namespace std;

const string server = "tcp://127.0.0.1:3307";
const string username = "root";
const string password = "";

//--------------------Artist Queries-------------------------
//Searching up all Artist's ID
/*
vector<int> artistID() {
    vector<int> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT artist_id FROM Artist"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getInt("artist_id"));
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}
*/

//Searching up all Artist's name
vector<string> artistNameList() {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT full_name FROM Artist"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getString("full_name"));
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up all Artist's nationality
vector<pair<string, string>> artistNationalityList() {
    vector<pair<string, string>> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT full_name, nationality FROM Artist"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            string name = string(res->getString("full_name"));
            string nationality = string(res->getString("nationality"));
            result.emplace_back(name, nationality);
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Artist's name to see Artist's style
vector<string> searchArtistStyle(const string& artistName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getArtistStyle(?)"));
        pstmt->setString(1, artistName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString("full_name"));
            result.push_back(res->getString("style"));
        }
        else {
            cout << "Artist not found." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Artist's name to see Artist's birth and death
vector<string> searchArtistBirthAndDeath(const string& artistName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getArtistBirthDeath(?)"));
        pstmt->setString(1, artistName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString("full_name"));
            result.push_back(to_string(res->getInt("birth")));
            result.push_back(to_string(res->getInt("death")));
        }
        else {
            cout << "Artist not found." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Artist's name to see information
vector<string> searchArtistByName(const string& artistName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getArtistName(?)"));
        pstmt->setString(1, artistName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString("full_name"));
            result.push_back(res->getString("nationality"));
            result.push_back(res->getString("style"));
            result.push_back(to_string(res->getInt("birth")));
            result.push_back(to_string(res->getInt("death")));
        }
        else {
            cout << "Artist not found." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

/*
//Searching up Artist's ID to see information
vector<string> searchArtistByID(const int& artistId) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getArtistInfoByID(?)"));
        pstmt->setInt(1, artistId);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString("full_name"));
            result.push_back(res->getString("nationality"));
            result.push_back(res->getString("style"));
            result.push_back(to_string(res->getInt("birth")));
            result.push_back(to_string(res->getInt("death")));
        }
        else {
            cout << "Artist not found." << endl;
        }
        return result;
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
}
*/

//---------------------Work Queries--------------------------------
//Searching up all Work ID's
/*
vector<int> workIDList() {
    vector<int> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT work_id FROM Work"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getInt("work_id"));
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}
*/


//Searching up Work's ID to find Work's information
//Saving for Work of the Day?
vector<string> searchWorkInfoByID(const int& workId) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getWorkInfoByID(?)"));
        pstmt->setInt(1, workId);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString("name"));
            string style = string(res->getString("style")).empty() ? "NULL" : res->getString("style");
            result.push_back(style);
            string url = string(res->getString("url")).empty() ? "NULL" : res->getString("url");
            result.push_back(url);
            string subject = string(res->getString("subject")).empty() ? "NULL" : res->getString("subject");
            result.push_back(subject);
        }
        else {
            cout << "Work not found." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}


//----------------------Museum Queries-----------------------------
//Searching up all Museum's ID
/*
vector<int> museumID() {
    vector<int> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT museum_id FROM Museum"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getInt("museum_id"));
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}
*/

//Searching up Museum's ID to find Museum's information
/*
vector<string> searchMuseumInfoByID(const int& museumId) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getMuseumInfoByID(?)"));
        pstmt->setInt(1, museumId);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString("name"));
            result.push_back(res->getString("phone"));
            result.push_back(res->getString("url"));
        }
        else {
            cout << "Museum not found." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}
*/

//Searching up Museum's name to find Museum's information
vector<string> searchMuseumInfoByName(const string& museumName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getMuseumInfoByName(?)"));
        pstmt->setString(1, museumName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString("name"));
            result.push_back(res->getString("phone"));
            result.push_back(res->getString("url"));
        }
        else {
            cout << "Museum not found." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//---------------------Museum Hours Queries (aka, related to Museum)-----------------------------
//Searching up Museum's name to find Museum's hours
vector<string> searchMuseumDaysAndHoursByName(const string& museumName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getMuseumDaysAndHours(?)"));
        pstmt->setString(1, museumName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getString("day"));
            result.push_back(res->getString("open"));
            result.push_back(res->getString("close"));
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//---------------------Address Queries-----------------------------
//Searching up all Address's country, state, and city
vector<string> searchAddressInfo() {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT country, state, city FROM Address"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getString("country"));
            string state = string(res->getString("state")).empty() ? "NULL" : res->getString("state");
            result.push_back(state);
            result.push_back(res->getString("city"));
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Address's ID to find Address's country, state, and city
vector<string> searchAddressInfoByID(const string& addressId) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getAddressInfoByID(?)"));
        pstmt->setString(1, addressId);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString("country"));
            string state = string(res->getString("state")).empty() ? "NULL" : res->getString("state");
            result.push_back(state);
            result.push_back(res->getString("city"));
            result.push_back(res->getString("address_id"));
        }
        else {
            cout << "Address ID not found." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//-----------------------Canvas Size Queries-------------------------------
//Searching up all Canvas Size IDs

vector<int> canvasSizeID() {
    vector<int> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT size_id FROM CanvasSize"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getInt("size_id"));
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}


//---------------------Multiple Queries----------------------------
//Searching up Artist's name to find artist's works
vector<string> searchArtistWork(const string& artistName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getArtistWork(?)"));
        pstmt->setString(1, artistName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getString("name"));
        }
        if (result.empty()) {
            cout << "Artist not found or there is no work made by artist." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Work's name to find all museums that has specific work
vector<string> searchWorkInMuseum(const string& workName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getWorkInMuseum(?)"));
        pstmt->setString(1, workName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getString("name"));
        }
        if (result.empty()) {
            cout << "Work not found or not in a museum." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Museum's name to find all works the museum contains
vector<string> searchMuseumWork(const string& museumName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getMuseumWork(?)"));
        pstmt->setString(1, museumName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getString("name"));
        }
        if (result.empty()) {
            cout << "Museum not found or no works in this museum." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Museum's name to find Museum's Address
vector<string> searchMuseumAddress(const string& museumName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getMuseumAddress(?)"));
        pstmt->setString(1, museumName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString("name"));
            result.push_back(res->getString("country"));
            string state = string(res->getString("state")).empty() ? "NULL" : res->getString("state");
            result.push_back(state);
            result.push_back(res->getString("city"));
        }
        else {
            cout << "Museum not found" << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Work's name to find ProductSpecs sale price and regular price
vector<string> searchWorkPrice(const string& workName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getWorkPrice(?)"));
        pstmt->setString(1, workName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString("name"));
            result.push_back(res->getString("sale_price"));
            result.push_back(res->getString("regular_price"));
        }
        else {
            cout << "Work not found" << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Artist's name to find all Work's name with their sale price and regular price
vector<string> searchArtistWorkPrice(const string& artistName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getArtistWorkPrice(?)"));
        pstmt->setString(1, artistName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getString("name"));
            result.push_back(res->getString("sale_price"));
            result.push_back(res->getString("regular_price"));
        }
        if (result.empty()) {
            cout << "Artist not found or there is no work made by artist." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Work's name to find Work's size
vector<string> searchWorkSize(const string& workName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getWorkSize(?)"));
        pstmt->setString(1, workName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString("name"));
            result.push_back(res->getString("width"));
            string height = string(res->getString("height")).empty() ? "0" : res->getString("height");
            result.push_back(height);
        }
        if (result.empty()) {
            cout << "Work not found." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Museum's name to find all Artist's names
vector<string> searchMuseumArtist(const string& museumName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getArtistInMuseum(?)"));
        pstmt->setString(1, museumName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getString("full_name"));
        }
        if (result.empty()) {
            cout << "Museum not found." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Artist's name and Museum's name to find all works
vector<string> searchArtistMuseumNameToFindWorks(const string& artistName, const string& museumName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getWorkFromArtistMuseumName(?, ?)"));
        pstmt->setString(1, artistName);
        pstmt->setString(2, museumName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getString("name"));
        }
        if (result.empty()) {
            cout << "No work found." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Searching up Artist's ID and Museum's ID to find Work's name
/*
vector<string> searchArtistMuseumIDToFindWorks(const int& artistName, const int& museumName) {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getWorkFromArtistMuseumID(?, ?)"));
        pstmt->setInt(1, artistName);
        pstmt->setInt(2, museumName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            result.push_back(res->getString("name"));
        }
        if (result.empty()) {
            cout << "Artist's ID or museum's ID is not found." << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}
*/

//--------------------------Others----------------------------
//Total count of Artist
vector<string> totalArtist() {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT COUNT(*) FROM Artist"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString(1));
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Total count of Work
vector<string> totalWork() {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT COUNT(*) FROM Work"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString(1));
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}

//Total count of Museum
vector<string> totalMuseum() {
    vector<string> result;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT COUNT(*) FROM Museum"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            result.push_back(res->getString(1));
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return result;
}


int main()
{
    //Artist Name: Alexandre Cabanel
    //Artist ID: 500
    //Work Name: Horses at the Porch
    //Work ID: 160228
    //Museum ID: 31
    //Museum Name: The State Hermitage Museum
    //Address ID: 12 Ulitsa Volkhonka
    

    
    string artistName;
    cout << "Artist name: ";
    getline(cin, artistName);
    vector<string> artistByName = searchArtistByName(artistName);
    if (!artistByName.empty()) {
        cout << "Name: " << artistByName[0] << endl << "Nationality: " << artistByName[1] << endl << "Style: " << artistByName[2] << endl << "Birth: " << artistByName[3] << endl << "Death: " << artistByName[4] << endl;
    }

    
    //string artistName;
    cout << "Artist name: ";
    getline(cin, artistName);
    vector<string> findWorks = searchArtistWork(artistName);
    for (string work : findWorks) {
        cout << "Work: " << work << endl;
    }
    

    
    
    //string artistName;
    cout << "Artist name: ";
    getline(cin, artistName);
    vector<string> findArtistStyle = searchArtistStyle(artistName);
    if (!findArtistStyle.empty()) {
        cout << "Name: " << findArtistStyle[0] << endl << "Style: " << findArtistStyle[1] << endl;
    }
    

    
    //string artistName;
    cout << "Artist name: ";
    getline(cin, artistName);
    vector<string> findArtistLifetime = searchArtistBirthAndDeath(artistName);
    if (!findArtistLifetime.empty()) {
        cout << "Name: " << findArtistLifetime[0] << endl << "Birth: " << findArtistLifetime[1] << endl << "Death: " << findArtistLifetime[2] << endl;
    }
    

    
    auto artistNameAndNationality = artistNationalityList();
    for (const auto& info : artistNameAndNationality) {
        cout << "Artist: " << info.first;
        cout << ", Nationality: " << info.second << endl;
    }
    

    
    int workID;
    cout << "Work ID: ";
    cin >> workID;
    cin.ignore();
    vector<string> workInfo = searchWorkInfoByID(workID);
    if (!workInfo.empty()) {
        cout << "Name: " << workInfo[0] << endl << "Style: " << workInfo[1] << endl << "URL: " << workInfo[2] << endl << "Subject: " << workInfo[3] << endl;
    }
    

    
    string museumName;
    cout << "Museum name: ";
    getline(cin, museumName);
    vector<string> museumNameInfo = searchMuseumInfoByName(museumName);
    if (!museumNameInfo.empty()) {
        cout << "Name: " << museumNameInfo[0] << endl << "Phone: " << museumNameInfo[1] << endl << "URL: " << museumNameInfo[2] << endl;
    }

    
    //string museumName;
    cout << "Museum name: ";
    getline(cin, museumName);
    vector<string> museumDayAndHour = searchMuseumDaysAndHoursByName(museumName);
    for (size_t i = 0; i + 2 < museumDayAndHour.size(); i += 3) {
        cout << museumDayAndHour[i] << ": " << museumDayAndHour[i + 1] << " - " << museumDayAndHour[i + 2] << endl;
    }
    

    
    vector<string> addressInfo = searchAddressInfo();


    
    string addressId;
    cout << "Address: ";
    getline(cin, addressId);
    vector<string> addressInfoById = searchAddressInfoByID(addressId);
    if (!addressInfoById.empty()) {
        cout << "Country: " << addressInfoById[0] << endl << "State: " << addressInfoById[1] << endl << "City: " << addressInfoById[2] << endl << addressInfoById[3] << endl;
    }
    

    
    vector<int> sizeId = canvasSizeID();
    

    
    string workName;
    cout << "Work name: ";
    getline(cin, workName);
    vector<string> findMuseums = searchWorkInMuseum(workName);
    for (string museum : findMuseums) {
        cout << "Museum: " << museum << endl;
    }
    

    
    //string workName;
    cout << "Work name: ";
    getline(cin, workName);
    vector<string> workSize = searchWorkSize(workName);
    if (!workSize.empty()) {
        cout << "Name: " << workSize[0] << endl << "Width: " << workSize[1] << endl << "Height: " << workSize[2] << endl;
    }
    
    
    
    
    //string museumName;
    cout << "Museum name: ";
    getline(cin, museumName);
    vector<string> findMuseumWorks = searchMuseumWork(museumName);
    for (string work : findMuseumWorks) {
        cout << "Work: " << work << endl;
    }
    

    
    //string museumName;
    cout << "Museum name: ";
    getline(cin, museumName);
    vector<string> findMuseumAddress = searchMuseumAddress(museumName);
    if (!findMuseumAddress.empty()) {
        cout << "Name: " << findMuseumAddress[0] << endl << "Country: " << findMuseumAddress[1] << endl << "State: " << findMuseumAddress[2] << endl << "City: " << findMuseumAddress[3] << endl;
    }
    
    
    
    //string workName;
    cout << "Work name: ";
    getline(cin, workName);
    vector<string> findWorkPrice = searchWorkPrice(workName);
    if (!findWorkPrice.empty()) {
        cout << "Name: " << findWorkPrice[0] << endl << "Sale Price: $" << findWorkPrice[1] << endl << "Regular Price: $" << findWorkPrice[2] << endl;
    }
    

    //string artistName;
    cout << "Artist name: ";
    getline(cin, artistName);
    vector<string> findArtistWorkPrice = searchArtistWorkPrice(artistName);
    for (size_t i = 0; i + 2 < findArtistWorkPrice.size(); i += 3) {
        cout << "Work Name: " << findArtistWorkPrice[i] << endl;
        cout << "Sale Price: " << findArtistWorkPrice[i + 1] << endl;
        cout << "Regular Price: " << findArtistWorkPrice[i + 2] << endl;
    }
    

    //string museumName;
    cout << "Museum name: ";
    getline(cin, museumName);
    vector<string> findArtistInMuseum = searchMuseumArtist(museumName);
    for (string artist : findArtistInMuseum) {
        cout << "Artist: " << artist << endl;
    }
    
    
    //string artistName;
    //string museumName;
    cout << "Artist name: ";
    getline(cin, artistName);
    cout << "Museum name: ";
    getline(cin, museumName);
    vector<string> findWorksByArtistAndMuseum = searchArtistMuseumNameToFindWorks(artistName, museumName);
    for (string work : findWorksByArtistAndMuseum) {
        cout << "Work: " << work << endl;
    }
    


    vector<string> totalArtists = totalArtist();
    cout << "Total Artists: " << totalArtists[0] << endl;
    vector<string> totalWorks = totalWork();
    cout << "Total Works: " << totalWorks[0] << endl;
    vector<string> totalMuseums = totalMuseum();
    cout << "Total Museums: " << totalMuseums[0] << endl;
    
    return 0;
}