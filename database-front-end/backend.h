#ifndef BACKEND_H
#define BACKEND_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <string>
#include <QSqlError>
#include <vector>

using namespace std;

class Backend
{
public:
    Backend();
    ~Backend();

    // Database connection
    bool connectToDatabase();

    // Artist functions
    vector<string> artistNameList(); // done
    vector<string> searchArtistWork(const string& artistName); // done
    vector<pair<string,string>> artistNationalityList();
    vector<string> searchArtistStyle(const string& artistName); // done
    vector<string> searchArtistBirthAndDeath(const string& artistName);
    vector<string> searchArtistByName(const string& artistName); // done
    vector<string> searchArtistWorkPrice(const string& artistName); // done

    // Museum functions
    vector<string> searchMuseumInfoByName(const string& museumName); // done
    vector<string> searchMuseumDaysAndHoursByName(const string& museumName); // done
    vector<string> searchAddressInfo(); // done
    vector<string> searchMuseumWork(const string& museumName); // done
    vector<string> searchMuseumAddress(const string& museumName); // done, buggy
    vector<string> searchMuseumArtist (const string& museumName); // done

    // Work functions
    vector<string> searchWorkInfo(const string& workName); // done
    vector<string> searchWorkInMuseum(const string& workName); // done
    vector<string> searchWorkPrice(const string& workName); // done
    vector<string> searchWorkSize(const string& workSize); // done
    // Totals
    vector<int> getTotals(); // done

private:
    QSqlDatabase db;
};

#endif // BACKEND_H
