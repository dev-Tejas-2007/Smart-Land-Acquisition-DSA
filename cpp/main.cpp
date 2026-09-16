#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>

using namespace std;

// ======================================================
// 1. CUSTOM EXCEPTION CLASSES
// ======================================================

class DuplicateSurveyException : public exception {
public:
    const char* what() const noexcept override {
        return "[EXCEPTION ERROR] A record with this Survey Number already exists!";
    }
};

class InvalidDataException : public exception {
private:
    string message;
public:
    InvalidDataException(string msg) : message("[EXCEPTION ERROR] " + msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};


// ======================================================
// 2. ABSTRACTION (Pure Virtual Base Class)
// ======================================================

class BaseLand {
public:
    virtual void displayTableRow() const = 0;
    virtual ~BaseLand() {}
};


// ======================================================
// 3. BASE CLASS & SINGLE INHERITANCE
// ======================================================

class LandRecord : public BaseLand {
protected:
    string surveyNumber;
    string ownerName;
    string location;
    double areaInAcres;

public:
    LandRecord(string survey, string owner, string loc, double area) {
        if (area <= 0) {
            throw InvalidDataException("Land area must be greater than 0 acres.");
        }
        surveyNumber = survey;
        ownerName = owner;
        location = loc;
        areaInAcres = area;
    }

    void displayTableRow() const override {
        cout << "| " << left << setw(14) << surveyNumber 
             << setw(18) << ownerName 
             << setw(12) << location 
             << setw(10) << areaInAcres;
    }

    string getSurveyNumber() const { return surveyNumber; }
    string getOwnerName() const { return ownerName; }
    string getLocation() const { return location; }
    double getArea() const { return areaInAcres; }

    // Friend Function Declaration
    friend void generateOfficialNotice(const LandRecord& land);
};


// ======================================================
// 4. MULTILEVEL INHERITANCE & SOCIAL WELFARE FEATURE
// ======================================================

class SocialWelfareLand : public LandRecord {
private:
    string publicProjectName; 
    int socialImpactScore;   

public:
    SocialWelfareLand(string survey, string owner, string loc, double area, string project, int score)
        : LandRecord(survey, owner, loc, area) {
        if (score < 1 || score > 100) {
            throw InvalidDataException("Social Impact Score must be between 1 and 100.");
        }
        publicProjectName = project;
        socialImpactScore = score;
    }

    void displayTableRow() const override {
        LandRecord::displayTableRow();
        cout << left << setw(26) << publicProjectName 
             << setw(8) << socialImpactScore << "|\n";
    }

    string getProjectName() const { return publicProjectName; }
    int getImpactScore() const { return socialImpactScore; }
};


// ======================================================
// 5. FRIEND FUNCTION
// ======================================================

void generateOfficialNotice(const LandRecord& land) {
    cout << "\n+--------------------------------------------------------------------------+\n";
    cout << "|                       OFFICIAL GAZETTE NOTICE                            |\n";
    cout << "+--------------------------------------------------------------------------+\n";
    cout << " Notice is hereby issued for mandatory acquisition of:\n";
    cout << "  * Survey Number   : " << land.surveyNumber << "\n";
    cout << "  * Registered Owner: " << land.ownerName << "\n";
    cout << "  * Location        : " << land.location << "\n";
    cout << "  * Total Area      : " << land.areaInAcres << " acres\n";
    cout << "+--------------------------------------------------------------------------+\n";
}


// ======================================================
// 6. DATA STRUCTURE: SINGLY LINKED LIST (Audit Log)
// ======================================================

struct LogNode {
    string logMessage;
    LogNode* next;

    LogNode(string msg) : logMessage(msg), next(nullptr) {}
};

class AuditLogList {
private:
    LogNode* head;

public:
    AuditLogList() : head(nullptr) {}

    void addLog(string message) {
        LogNode* newNode = new LogNode(message);
        newNode->next = head;
        head = newNode;
    }

    void showAuditHistory() const {
        cout << "\n============================================================================";
        cout << "\n                     SYSTEM AUDIT TRAIL (Linked List)                      ";
        cout << "\n============================================================================\n";
        LogNode* temp = head;
        int step = 1;
        if (temp == nullptr) {
            cout << "  No activity logged yet.\n";
        }
        while (temp != nullptr) {
            cout << "  [" << step++ << "] " << temp->logMessage << endl;
            temp = temp->next;
        }
        cout << "============================================================================\n";
    }

    ~AuditLogList() {
        while (head != nullptr) {
            LogNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};


// ======================================================
// 7. INPUT VALIDATION HELPERS (Prevents Crashing)
// ======================================================

int getValidIntInput(string prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minVal && value <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "[!] Invalid Input. Please enter a valid number between " << minVal << " and " << maxVal << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double getValidDoubleInput(string prompt, double minVal) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > minVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "[!] Invalid Input. Please enter a positive decimal number greater than " << minVal << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string getNonEmptyString(string prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) return input;
        cout << "[!] Input cannot be empty. Please try again.\n";
    }
}


// ======================================================
// 8. FILE HANDLING FUNCTIONS
// ======================================================

void saveRecordsToFile(const vector<SocialWelfareLand>& lands, const string& filename) {
    ofstream file(filename);
    if (!file) {
        throw runtime_error("Failed to open file for saving records!");
    }
    for (const auto& land : lands) {
        file << land.getSurveyNumber() << ","
             << land.getOwnerName() << ","
             << land.getLocation() << ","
             << land.getArea() << ","
             << land.getProjectName() << ","
             << land.getImpactScore() << "\n";
    }
    file.close();
}

void loadRecordsFromFile(vector<SocialWelfareLand>& lands, const string& filename, AuditLogList& audit) {
    ifstream file(filename);
    if (!file) return; // File doesn't exist yet, start fresh

    string line;
    int loadedCount = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string survey, owner, location, areaStr, project, scoreStr;

        if (getline(ss, survey, ',') &&
            getline(ss, owner, ',') &&
            getline(ss, location, ',') &&
            getline(ss, areaStr, ',') &&
            getline(ss, project, ',') &&
            getline(ss, scoreStr, ',')) {

            try {
                double area = stod(areaStr);
                int score = stoi(scoreStr);
                lands.push_back(SocialWelfareLand(survey, owner, location, area, project, score));
                loadedCount++;
            } catch (...) {
                // Ignore corrupt line
            }
        }
    }
    file.close();
    if (loadedCount > 0) {
        audit.addLog("Loaded " + to_string(loadedCount) + " land record(s) from 'land_records.txt'.");
    }
}


// ======================================================
// 9. ALGORITHMS (Bubble Sort & Linear Search)
// ======================================================

void sortByImpactScore(vector<SocialWelfareLand>& lands) {
    int n = lands.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (lands[j].getImpactScore() < lands[j + 1].getImpactScore()) {
                SocialWelfareLand temp = lands[j];
                lands[j] = lands[j + 1];
                lands[j + 1] = temp;
            }
        }
    }
}

int searchBySurveyNumber(const vector<SocialWelfareLand>& lands, string targetSurvey) {
    for (size_t i = 0; i < lands.size(); i++) {
        if (lands[i].getSurveyNumber() == targetSurvey) {
            return i;
        }
    }
    return -1;
}


// ======================================================
// 10. UI DISPLAY TABLE HELPERS
// ======================================================

void printTableHeader() {
    cout << "\n+---------------+-------------------+------------+----------+---------------------------+-------+\n";
    cout << "| SURVEY NO     | OWNER NAME        | LOCATION   | ACRES    | PUBLIC PURPOSE            | SCORE |\n";
    cout << "+---------------+-------------------+------------+----------+---------------------------+-------+\n";
}

void printTableFooter() {
    cout << "+---------------+-------------------+------------+----------+---------------------------+-------+\n";
}

void displayAllRecords(const vector<SocialWelfareLand>& lands) {
    if (lands.empty()) {
        cout << "\n[!] No land records available in the database.\n";
        return;
    }
    printTableHeader();
    for (const auto& land : lands) {
        land.displayTableRow();
    }
    printTableFooter();
}


// ======================================================
// MAIN FUNCTION (Interactive Loop)
// ======================================================

int main() {
    vector<SocialWelfareLand> welfareLands;
    AuditLogList auditTrail;
    const string storageFile = "land_records.txt";

    auditTrail.addLog("System started.");

    // Load persistent data from file
    loadRecordsFromFile(welfareLands, storageFile, auditTrail);

    // If file is empty, initialize default sample dataset
    if (welfareLands.empty()) {
        welfareLands.push_back(SocialWelfareLand("MH12-8810", "Anil Deshmukh", "Pune", 4.5, "District Hospital", 95));
        welfareLands.push_back(SocialWelfareLand("MH14-3321", "Sunita Shinde", "Pimpri", 2.0, "Public Primary School", 88));
        welfareLands.push_back(SocialWelfareLand("MH09-1145", "Kiran Pawar", "Satara", 6.0, "Solar Energy Park", 92));
        auditTrail.addLog("Initialized default benchmark records.");
    }

    while (true) {
        cout << "\n============================================================================\n";
        cout << "          LANDWISE v2.0 -- INTELLIGENT LAND ACQUISITION SYSTEM             \n";
        cout << "============================================================================\n";
        cout << "  1. View All Land Records\n";
        cout << "  2. Add New Land Record (Input Validation & Exception Check)\n";
        cout << "  3. Sort Records by Social Impact Score (Bubble Sort)\n";
        cout << "  4. Search Record by Survey Number (Linear Search)\n";
        cout << "  5. Generate Gazette Notice (Friend Function)\n";
        cout << "  6. View System Audit Trail (Linked List)\n";
        cout << "  7. Save & Exit (File I/O)\n";
        cout << "============================================================================\n";

        int choice = getValidIntInput("Select an option (1-7): ", 1, 7);

        switch (choice) {
            case 1: {
                cout << "\n>>> CURRENT REGISTERED LAND RECORDS";
                displayAllRecords(welfareLands);
                auditTrail.addLog("Viewed all land records.");
                break;
            }

            case 2: {
                cout << "\n>>> ADD NEW LAND RECORD\n";
                try {
                    string survey = getNonEmptyString("Enter Survey Number (e.g., MH12-9900): ");

                    // Check for duplicate key exception
                    if (searchBySurveyNumber(welfareLands, survey) != -1) {
                        throw DuplicateSurveyException();
                    }

                    string owner = getNonEmptyString("Enter Owner Name: ");
                    string location = getNonEmptyString("Enter Location: ");
                    double area = getValidDoubleInput("Enter Area in Acres: ", 0.0);
                    string project = getNonEmptyString("Enter Public Project Name: ");
                    int score = getValidIntInput("Enter Social Impact Score (1-100): ", 1, 100);

                    // Create new object (validates via constructors)
                    SocialWelfareLand newRecord(survey, owner, location, area, project, score);
                    welfareLands.push_back(newRecord);

                    cout << "\n[SUCCESS] Land record successfully registered!\n";
                    auditTrail.addLog("Added new record: Survey No " + survey);

                } catch (const exception& e) {
                    cout << "\n" << e.what() << "\n";
                    auditTrail.addLog("Failed entry attempt due to exception.");
                }
                break;
            }

            case 3: {
                if (welfareLands.empty()) {
                    cout << "\n[!] No records to sort.\n";
                } else {
                    sortByImpactScore(welfareLands);
                    cout << "\n>>> RECORDS SORTED BY SOCIAL IMPACT SCORE (HIGHEST FIRST)";
                    displayAllRecords(welfareLands);
                    auditTrail.addLog("Sorted land records using Bubble Sort.");
                }
                break;
            }

            case 4: {
                if (welfareLands.empty()) {
                    cout << "\n[!] Database is empty.\n";
                } else {
                    string searchKey = getNonEmptyString("\nEnter Survey Number to Search: ");
                    int resultIndex = searchBySurveyNumber(welfareLands, searchKey);

                    if (resultIndex != -1) {
                        cout << "\n[SUCCESS] Record Found at Index [" << resultIndex << "]:";
                        printTableHeader();
                        welfareLands[resultIndex].displayTableRow();
                        printTableFooter();
                        auditTrail.addLog("Searched and found record: " + searchKey);
                    } else {
                        cout << "\n[!] Record for Survey Number '" << searchKey << "' was not found.\n";
                        auditTrail.addLog("Unsuccessful search query: " + searchKey);
                    }
                }
                break;
            }

            case 5: {
                if (welfareLands.empty()) {
                    cout << "\n[!] No records available.\n";
                } else {
                    string surveyKey = getNonEmptyString("\nEnter Survey Number to Issue Gazette Notice: ");
                    int index = searchBySurveyNumber(welfareLands, surveyKey);

                    if (index != -1) {
                        // Friend Function call
                        generateOfficialNotice(welfareLands[index]);
                        auditTrail.addLog("Issued Gazette Notice for Survey No: " + surveyKey);
                    } else {
                        cout << "\n[!] Cannot issue notice. Survey number not found.\n";
                    }
                }
                break;
            }

            case 6: {
                auditTrail.showAuditHistory();
                break;
            }

            case 7: {
                try {
                    saveRecordsToFile(welfareLands, storageFile);
                    cout << "\n[FILE I/O SUCCESS] All data saved to '" << storageFile << "'.\n";
                } catch (const exception& e) {
                    cout << "\n" << e.what() << "\n";
                }
                cout << "Exiting LandWise Engine. Goodbye!\n\n";
                return 0;
            }
        }
    }
}
