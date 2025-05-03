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
            /*
            cout << "Artist: " << res->getString("full_name") << endl;
            cout << "Nationality: " << res->getString("nationality") << endl;
            cout << "Style: " << res->getString("style") << endl;
            cout << "Birth Year: " << res->getInt("birth") << endl;
            cout << "Death Year: " << res->getInt("death") << endl;
            */
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

//---------------------Work Queries--------------------------------
//Searching up all Work ID's
vector<int> workIDList() {
    vector<int> workIDs;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT work_id FROM Work"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            //cout << res->getInt("work_id") << endl;
            workIDs.push_back(res->getInt("work_id"));
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return workIDs;
}

//Searching up Work's ID to find Work's information
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
            result.push_back(res->getString("url"));
            result.push_back(res->getString("subject"));
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

//Searching up Museum's ID to find Museum's information
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

//---------------------Multiple Queries----------------------------
//Searching up artist's name to find artist's works
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


int main()
{
    /*
    vector<int> artistIDList = artistID();
    */

    /*
    string artistName;
    getline(cin, artistName);
    vector<string> artistByName = searchArtistByName(artistName);
    */

    /*
    string artistName;
    getline(cin, artistName);
    vector<string> findWorks = searchArtistWork(artistName);
    */

    /*
    int artistID;
    cin >> artistID;
    vector<string> artistInfo = searchArtistByID(artistID);
    */
    
    /*
    string artistName;
    getline(cin, artistName);
    vector<string> findArtistStyle = searchArtistStyle(artistName);
    */

    /*
    string artistName;
    getline(cin, artistName);
    vector<string> findArtistLifetime = searchArtistBirthAndDeath(artistName);
    */

    /*
    auto artistNameAndNationality = artistNationalityList();
    for (const auto& info : artistNameAndNationality) {
        cout << "Artist: " << info.first;
        cout << ", Nationality: " << info.second << endl;
    }
    */

    /*
    int workID;
    cin >> workID;
    vector<string> workInfo = searchWorkInfoByID(workID);
    */

    /*
    vector<int> museumIDList = museumID();
    */

    /*
    int museumID;
    cin >> museumID;
    vector<string> museumIDInfo = searchMuseumInfoByID(museumID);
    */

    /*
    string museumName;
    getline(cin, museumName);
    vector<string> museumNameInfo = searchMuseumInfoByName(museumName);
    */

    /*
    string museumName;
    getline(cin, museumName);
    vector<string> museumDayAndHour = searchMuseumDaysAndHoursByName(museumName);
    for (size_t i = 0; i + 2 < museumDayAndHour.size(); i += 3) {
        cout << museumDayAndHour[i] << ": " << museumDayAndHour[i + 1] << " - " << museumDayAndHour[i + 2] << endl;
    }
    */

    /*
    string workName;
    getline(cin, workName);
    vector<string> findMuseums = searchWorkInMuseum(workName);
    */
    
    /*
    string museumName;
    getline(cin, museumName);
    vector<string> findWorks = searchMuseumWork(museumName);
    */
    
    return 0;
}