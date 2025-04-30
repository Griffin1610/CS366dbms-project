#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <memory> //Useful for unique_ptr to not have to delete everything each time :D
#include <vector>
using namespace std;

const string server = "tcp://127.0.0.1:3307";
const string username = "root";
const string password = "J@p3n3se$tudies";

//--------------------Artist Queries-------------------------
//Searching up all Artist's name
vector<string> artistNameList() {
    vector<string> artistName;
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT full_name FROM Artist"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            //cout << res->getString("full_name") << endl;
            //workIDs.push_back(res->getInt("work_id"));
            artistName.push_back(res->getString("full_name"));
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    return artistName;
}

//Searching up all Artist's nationality
void artistNationalityList() {
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT full_name, nationality FROM Artist"));
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            cout << res->getString("full_name") << ": ";
            cout << res->getString("nationality") << endl;
        }
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
}

//Searching up Artist's name to see information
void searchArtistByName(const string& artistName) {
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getArtistName(?)"));
        pstmt->setString(1, artistName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            cout << "Found artist: " << res->getString("full_name") << endl;
            cout << "Nationality: " << res->getString("nationality") << endl;
            cout << "Style: " << res->getString("style") << endl;
            cout << "Birth Year: " << res->getInt("birth") << endl;
            cout << "Death Year: " << res->getInt("death") << endl;
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
}

//Searching up Artist's ID to see information
void searchArtistByID(const int& artistId) {
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getArtistInfoByID(?)"));
        pstmt->setInt(1, artistId);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            cout << "Artist: " << res->getString("full_name") << endl;
            cout << "Nationality: " << res->getString("nationality") << endl;
            cout << "Style: " << res->getString("style") << endl;
            cout << "Birth Year: " << res->getInt("birth") << endl;
            cout << "Death Year: " << res->getInt("death") << endl;
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
            /*
            cout << "Name: " << res->getString("name") << endl;
            cout << "Style: " << res->getString("style") << endl;
            cout << "URL: " << res->getString("url") << endl;
            cout << "Subject: " << res->getString("subject") << endl; //If Subject is NULL, fix it!
            */
            result.push_back(res->getString("name"));
            string style = res->isNull("style") ? "" : res->getString("style");
            result.push_back(style);
            result.push_back(res->getString("url"));
            string subject = res->isNull("subject") ? "" : res->getString("subject");
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
        if (res->next()) {
            result.push_back(res->getString("name"));
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
}

//Searching up Work's name to find all museums that has specific work
void searchWorkInMuseum(const string& workName) {
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getWorkInMuseum(?)"));
        pstmt->setString(1, workName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            cout << "Museum: " << res->getString("name") << endl;
        }
        //Error of Work found but work not in museum, therefore thinking work does not exist
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
}

//Searching up Museum's name to find all works the museum contains
void searchMuseumWork(const string& museumName) {
    try {
        sql::Driver* driver = get_driver_instance();
        unique_ptr<sql::Connection> con(driver->connect(server, username, password));
        con->setSchema("cs366project");

        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("CALL getMuseumWork(?)"));
        pstmt->setString(1, museumName);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            cout << "Work: " << res->getString("name") << endl;
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
}


int main()
{
    /*
    string artistName;
    cout << "Searching up Artist's name: ";
    getline(cin, artistName);
    //searchArtistByName(artistName);
    //searchArtistWork(artistName);
    */

    string artistName;
    cout << "Searching up Artist's name: ";
    vector<string> findWorks = searchArtistWork(artistName);
    for (string findWork : findWorks) {
        cout << "Work: " << findWork << endl;
    }

    /*
    int artistID;
    cout << "Searching up Artist's ID: ";
    cin >> artistID;
    searchArtistByID(artistID);
    */

    //vector<string> artistNames = artistNameList();
    //artistNationalityList();
    
    //vector<int> ids = workIDList();

    int workID;
    cout << "Searching up Work's ID: ";
    cin >> workID;
    vector<string> workInfo = searchWorkInfoByID(workID);
    cout << "Name: " << workInfo[0] << endl;
    cout << "Style: " << workInfo[1] << endl;
    cout << "URL: " << workInfo[2] << endl;
    cout << "Subject: " << workInfo[3] << endl;

    /*
    string workName;
    cout << "Searching up Work's name: ";
    getline(cin, workName);
    searchWorkInMuseum(workName);
    */
    
    /*
    string museumName;
    cout << "Searching up Museum's name: ";
    getline(cin, museumName);
    searchMuseumWork(museumName);
    */

    return 0;
}