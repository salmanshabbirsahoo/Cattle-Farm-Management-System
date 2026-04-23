#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <limits>

using namespace std;

//                   FUNCTION PROTOTYPES
// --- Menu Functions ---
void mainMenu();
void adminModule();
void userModule();
void adminDashboard();
void userDashboard();
// --- Auth Functions ---
bool adminSignUp();
bool adminSignIn();
bool userSignUp();
bool userSignIn();
// --- Validation Functions ---
bool isPasswordValid(string password);
bool isUsernameUnique(string username, string filename);
bool isUsernameUniqueUser(string username);
// --- Cattle Management ---
void cattleManagement();
void addCattle();
void viewAllCattle();
void updateCattle();
void deleteCattle();
void searchCattle();
// --- Feed Management ---
void feedManagement();
void addFeedRecord();
void viewFeedRecords();
void deleteFeedRecord();
// --- Milk Production ---
void milkManagement();
void recordDailyMilk();
void viewMilkReport();
void calculateMonthlyTotal();
void viewMilkByCattle();
// --- User Features ---
void viewCattleListUser();
void checkFeedDetailsUser();
void recordDailyMilkUser();
void viewMilkReportUser();
// --- Utility ---
void printLine(char c, int n);
void pressEnterToContinue();
void clearInputBuffer();

//                     MAIN FUNCTION
int main() {
    mainMenu();
    return 0;
}

//                   UTILITY FUNCTIONS

void printLine(char c, int n) {
    for (int i = 0; i < n; i++) cout << c;
    cout << endl;
}

void pressEnterToContinue() {
    cout << "\n  Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//                     MAIN MENU
void mainMenu() {
    int choice;
    while (true) {
        system("cls");
        printLine('=', 50);
        cout << "      CATTLE FARM MANAGEMENT SYSTEM v1.0     " << endl;
        printLine('=', 50);
        cout << "       Welcome to Sahoo Cattle Farm      " << endl;
        printLine('-', 50);
        cout << "  [1]  Admin Module" << endl;
        cout << "  [2]  User Module" << endl;
        cout << "  [3]  Exit" << endl;
        printLine('=', 50);
        cout << "  Enter Your Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            clearInputBuffer();
            cout << "\n  [!] Invalid input. Please enter a number." << endl;
            pressEnterToContinue();
            continue;
        }

        switch (choice) {
            case 1: adminModule(); break;
            case 2: userModule(); break;
            case 3:
                system("cls");
                printLine('=', 50);
                cout << "  Thank you for using Cattle Farm System!" << endl;
                cout << "          Have a great day!              " << endl;
                printLine('=', 50);
                exit(0);
            default:
                cout << "\n  [!] Invalid choice. Try again." << endl;
                pressEnterToContinue();
        }
    }
}

//                     ADMIN MODULE

void adminModule() {
    int choice;
    while (true) {
        system("cls");
        printLine('=', 50);
        cout << "              ADMIN MODULE                   " << endl;
        printLine('=', 50);
        cout << "  [1]  Sign In" << endl;
        cout << "  [2]  Sign Up (New Admin)" << endl;
        cout << "  [3]  Back to Main Menu" << endl;
        printLine('-', 50);
        cout << "  Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (adminSignIn()) adminDashboard();
                else pressEnterToContinue();
                break;
            case 2:
                adminSignUp();
                pressEnterToContinue();
                break;
            case 3: return;
            default:
                cout << "\n  [!] Invalid choice. Try again." << endl;
                pressEnterToContinue();
        }
    }
}

//                   ADMIN SIGN UP

bool adminSignUp() {
    system("cls");
    printLine('=', 50);
    cout << "              ADMIN SIGN UP                  " << endl;
    printLine('=', 50);

    string secretCode = "ADMIN123";
    string inputCode;
    clearInputBuffer();
    cout << "  Enter Admin Secret Code: ";
    getline(cin, inputCode);

    if (inputCode != secretCode) {
        cout << "\n  [!] Access Denied! Invalid Secret Code." << endl;
        return false;
    }

    string fullName, contact, username, password;
    int age;

    cout << "\n  Enter Full Name    : ";
    getline(cin, fullName);

    cout << "  Enter Contact No.  : ";
    getline(cin, contact);

    cout << "  Enter Age          : ";
    while (!(cin >> age) || age <= 0) {
        cin.clear();
        clearInputBuffer();
        cout << "  [!] Age must be greater than 0. Re-enter: ";
    }
    clearInputBuffer();

    cout << "  Enter Username     : ";
    getline(cin, username);
    while (!isUsernameUnique(username, "adminData.txt")) {
        cout << "  [!] Username already exists! Try another: ";
        getline(cin, username);
    }

    cout << "  Enter Password     : ";
    getline(cin, password);
    while (!isPasswordValid(password)) {
        cout << "  [!] Password must be 7+ chars, include a number & special symbol (@#$)!\n";
        cout << "  Re-enter Password  : ";
        getline(cin, password);
    }

    fstream file;
    file.open("adminData.txt", ios::app);
    if (!file.is_open()) {
        cout << "\n  [!] Error creating admin file." << endl;
        return false;
    }
    file << username << "|" << password << "|" << fullName << "|"
         << contact << "|" << age << "\n";
    file.close();

    cout << "\n  [OK] Admin Account Created Successfully!" << endl;
    return true;
}

//                   ADMIN SIGN IN

bool adminSignIn() {
    system("cls");
    printLine('=', 50);
    cout << "              ADMIN SIGN IN                  " << endl;
    printLine('=', 50);

    string inputUser, inputPass;
    clearInputBuffer();
    cout << "  Enter Username  : ";
    getline(cin, inputUser);
    cout << "  Enter Password  : ";
    getline(cin, inputPass);

    fstream file;
    file.open("adminData.txt", ios::in);

    if (!file.is_open()) {
        cout << "\n  [!] No admin accounts found. Please sign up first." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        size_t pos = 0, next;
        string u, p, name;

        next = line.find('|', pos);
        if (next == string::npos) continue;
        u = line.substr(pos, next - pos); pos = next + 1;

        next = line.find('|', pos);
        if (next == string::npos) continue;
        p = line.substr(pos, next - pos); pos = next + 1;

        next = line.find('|', pos);
        if (next == string::npos) name = line.substr(pos);
        else name = line.substr(pos, next - pos);

        if (u == inputUser && p == inputPass) {
            cout << "\n  [OK] Admin Login Successful! Welcome, " << name << "!" << endl;
            file.close();
            pressEnterToContinue();
            return true;
        }
    }

    file.close();
    cout << "\n  [!] Invalid Username or Password!" << endl;
    return false;
}

//                   ADMIN DASHBOARD

void adminDashboard() {
    int choice;
    while (true) {
        system("cls");
        printLine('=', 50);
        cout << "             ADMIN DASHBOARD                 " << endl;
        printLine('=', 50);
        cout << "  [1]  Cattle Management" << endl;
        cout << "  [2]  Feed Management" << endl;
        cout << "  [3]  Milk Production Report" << endl;
        cout << "  [4]  Logout" << endl;
        printLine('-', 50);
        cout << "  Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: cattleManagement(); break;
            case 2: feedManagement(); break;
            case 3: milkManagement(); break;
            case 4:
                cout << "\n  [OK] Logged out successfully." << endl;
                pressEnterToContinue();
                return;
            default:
                cout << "\n  [!] Invalid choice." << endl;
                pressEnterToContinue();
        }
    }
}

//                   USER MODULE

void userModule() {
    int choice;
    while (true) {
        system("cls");
        printLine('=', 50);
        cout << "              USER MODULE                    " << endl;
        printLine('=', 50);
        cout << "  [1]  Sign In" << endl;
        cout << "  [2]  Sign Up (New User)" << endl;
        cout << "  [3]  Back to Main Menu" << endl;
        printLine('-', 50);
        cout << "  Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (userSignIn()) userDashboard();
                else pressEnterToContinue();
                break;
            case 2:
                userSignUp();
                pressEnterToContinue();
                break;
            case 3: return;
            default:
                cout << "\n  [!] Invalid choice." << endl;
                pressEnterToContinue();
        }
    }
}

//                   USER SIGN UP

bool userSignUp() {
    system("cls");
    printLine('=', 50);
    cout << "              USER SIGN UP                   " << endl;
    printLine('=', 50);

    string fullName, contact, username, password, email;
    int age;

    clearInputBuffer();
    cout << "  Enter Full Name    : ";
    getline(cin, fullName);

    cout << "  Enter Email        : ";
    getline(cin, email);

    cout << "  Enter Contact No.  : ";
    getline(cin, contact);

    cout << "  Enter Age          : ";
    while (!(cin >> age) || age <= 0) {
        cin.clear();
        clearInputBuffer();
        cout << "  [!] Age must be greater than 0. Re-enter: ";
    }
    clearInputBuffer();

    cout << "  Enter Username     : ";
    getline(cin, username);
    while (!isUsernameUniqueUser(username)) {
        cout << "  [!] Username already exists! Try another: ";
        getline(cin, username);
    }

    cout << "  Enter Password     : ";
    getline(cin, password);
    while (!isPasswordValid(password)) {
        cout << "  [!] Password must be 7+ chars, include a number & special symbol (@#$)!\n";
        cout << "  Re-enter Password  : ";
        getline(cin, password);
    }

    fstream file;
    file.open("userData.txt", ios::app);
    if (!file.is_open()) {
        cout << "\n  [!] Error creating user file." << endl;
        return false;
    }
    file << username << "|" << password << "|" << email << "|"
         << contact << "|" << fullName << "|" << age << "\n";
    file.close();

    cout << "\n  [OK] User Account Created Successfully!" << endl;
    return true;
}

//                   USER SIGN IN

bool userSignIn() {
    system("cls");
    printLine('=', 50);
    cout << "              USER SIGN IN                   " << endl;
    printLine('=', 50);

    string input, inputPass;
    clearInputBuffer();
    cout << "  Enter Username or Email : ";
    getline(cin, input);
    cout << "  Enter Password          : ";
    getline(cin, inputPass);

    fstream file;
    file.open("userData.txt", ios::in);

    if (!file.is_open()) {
        cout << "\n  [!] No user accounts found. Please sign up first." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        string fields[6];
        int pos = 0, idx = 0;
        for (int i = 0; i < 5; i++) {
            size_t next = line.find('|', pos);
            if (next == string::npos) break;
            fields[idx++] = line.substr(pos, next - pos);
            pos = (int)next + 1;
        }
        fields[idx] = line.substr(pos);

        string u = fields[0], p = fields[1], email = fields[2], name = fields[4];

        if ((input == u || input == email) && p == inputPass) {
            cout << "\n  [OK] User Login Successful! Welcome, " << name << "!" << endl;
            file.close();
            pressEnterToContinue();
            return true;
        }
    }

    file.close();
    cout << "\n  [!] Invalid Username/Email or Password!" << endl;
    return false;
}

//                   USER DASHBOARD

void userDashboard() {
    int choice;
    while (true) {
        system("cls");
        printLine('=', 50);
        cout << "             USER DASHBOARD                  " << endl;
        printLine('=', 50);
        cout << "  [1]  View Cattle List" << endl;
        cout << "  [2]  Check Feed Details" << endl;
        cout << "  [3]  Record Daily Milk" << endl;
        cout << "  [4]  View Milk Report" << endl;
        cout << "  [5]  Logout" << endl;
        printLine('-', 50);
        cout << "  Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewCattleListUser(); pressEnterToContinue(); break;
            case 2: checkFeedDetailsUser(); pressEnterToContinue(); break;
            case 3: recordDailyMilkUser(); pressEnterToContinue(); break;
            case 4: viewMilkReportUser(); pressEnterToContinue(); break;
            case 5:
                cout << "\n  [OK] Logged out successfully." << endl;
                pressEnterToContinue();
                return;
            default:
                cout << "\n  [!] Invalid choice." << endl;
                pressEnterToContinue();
        }
    }
}

//               CATTLE MANAGEMENT (ADMIN CRUD)

void cattleManagement() {
    int choice;
    while (true) {
        system("cls");
        printLine('=', 50);
        cout << "            CATTLE MANAGEMENT                " << endl;
        printLine('=', 50);
        cout << "  [1]  Add New Cattle" << endl;
        cout << "  [2]  View All Cattle" << endl;
        cout << "  [3]  Search Cattle by ID" << endl;
        cout << "  [4]  Update Cattle Record" << endl;
        cout << "  [5]  Delete Cattle Record" << endl;
        cout << "  [6]  Back" << endl;
        printLine('-', 50);
        cout << "  Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addCattle(); pressEnterToContinue(); break;
            case 2: viewAllCattle(); pressEnterToContinue(); break;
            case 3: searchCattle(); pressEnterToContinue(); break;
            case 4: updateCattle(); pressEnterToContinue(); break;
            case 5: deleteCattle(); pressEnterToContinue(); break;
            case 6: return;
            default:
                cout << "\n  [!] Invalid choice." << endl;
                pressEnterToContinue();
        }
    }
}

// ---- ADD CATTLE ----
void addCattle() {
    system("cls");
    printLine('=', 50);
    cout << "            ADD NEW CATTLE                   " << endl;
    printLine('=', 50);

    string id, type, healthStatus;
    int age;
    float milkPerDay;

    clearInputBuffer();
    cout << "  Enter Cattle ID       : ";
    getline(cin, id);
    cout << "  Enter Type (Cow/Bull) : ";
    getline(cin, type);

    cout << "  Enter Age (years)     : ";
    while (!(cin >> age) || age <= 0) {
        cin.clear();
        clearInputBuffer();
        cout << "  [!] Age must be > 0. Re-enter: ";
    }

    cout << "  Enter Milk/Day (L)    : ";
    while (!(cin >> milkPerDay) || milkPerDay < 0) {
        cin.clear();
        clearInputBuffer();
        cout << "  [!] Milk must be >= 0. Re-enter: ";
    }
    clearInputBuffer();

    cout << "  Enter Health Status   : ";
    getline(cin, healthStatus);

    // Check for duplicate ID
    fstream checkFile;
    checkFile.open("cattle.txt", ios::in);
    if (checkFile.is_open()) {
        string line;
        while (getline(checkFile, line)) {
            string lineId = line.substr(0, line.find('|'));
            if (lineId == id) {
                checkFile.close();
                cout << "\n  [!] Cattle ID already exists! Use a unique ID." << endl;
                return;
            }
        }
        checkFile.close();
    }

    fstream file;
    file.open("cattle.txt", ios::app);
    if (!file.is_open()) {
        cout << "\n  [!] Error opening cattle file." << endl;
        return;
    }
    file << id << "|" << type << "|" << age << "|"
         << milkPerDay << "|" << healthStatus << "\n";
    file.close();

    cout << "\n  [OK] Cattle Record Added Successfully!" << endl;
}

// ---- VIEW ALL CATTLE ----
void viewAllCattle() {
    system("cls");
    printLine('=', 55);
    cout << "             ALL CATTLE RECORDS              " << endl;
    printLine('=', 55);

    bool found = false;
    fstream file;
    file.open("cattle.txt", ios::in);

    if (!file.is_open()) {
        cout << "\n  [!] No records found." << endl;
        return;
    }

    printf("  %-10s %-8s %-6s %-10s %-16s\n", "ID", "Type", "Age", "Milk/Day", "Health Status");
    printLine('-', 55);

    string line;
    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;

        string fields[5];
        size_t pos = 0;
        int idx = 0;
        for (int i = 0; i < 4; i++) {
            size_t next = line.find('|', pos);
            if (next == string::npos) break;
            fields[idx++] = line.substr(pos, next - pos);
            pos = next + 1;
        }
        fields[idx] = line.substr(pos);

        found = true;
        count++;
        printf("  %-10s %-8s %-6s %-10s %-16s\n",
               fields[0].c_str(), fields[1].c_str(), fields[2].c_str(),
               (fields[3] + "L").c_str(), fields[4].c_str());
    }

    file.close();
    if (!found)
        cout << "\n  [!] No cattle records found." << endl;
    else {
        printLine('-', 55);
        cout << "  Total Cattle: " << count << endl;
    }
}

// ---- SEARCH CATTLE ----
void searchCattle() {
    system("cls");
    printLine('=', 50);
    cout << "           SEARCH CATTLE BY ID               " << endl;
    printLine('=', 50);

    string searchID;
    clearInputBuffer();
    cout << "  Enter Cattle ID to Search: ";
    getline(cin, searchID);

    fstream file;
    file.open("cattle.txt", ios::in);

    if (!file.is_open()) {
        cout << "\n  [!] No records found." << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        string fields[5];
        size_t pos = 0;
        int idx = 0;
        for (int i = 0; i < 4; i++) {
            size_t next = line.find('|', pos);
            if (next == string::npos) break;
            fields[idx++] = line.substr(pos, next - pos);
            pos = next + 1;
        }
        fields[idx] = line.substr(pos);

        if (fields[0] == searchID) {
            found = true;
            printLine('-', 40);
            cout << "  Cattle ID     : " << fields[0] << endl;
            cout << "  Type          : " << fields[1] << endl;
            cout << "  Age           : " << fields[2] << " years" << endl;
            cout << "  Milk per Day  : " << fields[3] << " L" << endl;
            cout << "  Health Status : " << fields[4] << endl;
            printLine('-', 40);
            break;
        }
    }

    file.close();
    if (!found) cout << "\n  [!] Cattle ID '" << searchID << "' not found!" << endl;
}

// ---- UPDATE CATTLE ----
void updateCattle() {
    system("cls");
    printLine('=', 50);
    cout << "           UPDATE CATTLE RECORD              " << endl;
    printLine('=', 50);

    string searchID;
    clearInputBuffer();
    cout << "  Enter Cattle ID to Update: ";
    getline(cin, searchID);

    fstream file, tempFile;
    file.open("cattle.txt", ios::in);
    tempFile.open("cattle_temp.txt", ios::out);

    if (!file.is_open()) {
        cout << "\n  [!] No records found." << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        string fields[5];
        size_t pos = 0;
        int idx = 0;
        for (int i = 0; i < 4; i++) {
            size_t next = line.find('|', pos);
            if (next == string::npos) break;
            fields[idx++] = line.substr(pos, next - pos);
            pos = next + 1;
        }
        fields[idx] = line.substr(pos);

        if (fields[0] == searchID) {
            found = true;
            string newType, newHealth;
            int newAge;
            float newMilk;

            cout << "\n  --- Current Record ---" << endl;
            cout << "  Type: " << fields[1] << " | Age: " << fields[2]
                 << " | Milk: " << fields[3] << "L | Health: " << fields[4] << endl;
            cout << "\n  --- Enter New Details (press Enter to keep current) ---" << endl;

            cout << "  New Type [" << fields[1] << "]        : ";
            getline(cin, newType);
            if (newType.empty()) newType = fields[1];

            cout << "  New Age (years) [" << fields[2] << "]  : ";
            string ageInput;
            getline(cin, ageInput);
            newAge = ageInput.empty() ? stoi(fields[2]) : stoi(ageInput);

            cout << "  New Milk/Day (L) [" << fields[3] << "] : ";
            string milkInput;
            getline(cin, milkInput);
            newMilk = milkInput.empty() ? stof(fields[3]) : stof(milkInput);

            cout << "  New Health Status [" << fields[4] << "] : ";
            getline(cin, newHealth);
            if (newHealth.empty()) newHealth = fields[4];

            tempFile << fields[0] << "|" << newType << "|" << newAge << "|"
                     << newMilk << "|" << newHealth << "\n";
        } else {
            tempFile << line << "\n";
        }
    }

    file.close();
    tempFile.close();

    remove("cattle.txt");
    rename("cattle_temp.txt", "cattle.txt");

    if (found) cout << "\n  [OK] Record Updated Successfully!" << endl;
    else       cout << "\n  [!] Record Not Found!" << endl;
}

// ---- DELETE CATTLE ----
void deleteCattle() {
    system("cls");
    printLine('=', 50);
    cout << "           DELETE CATTLE RECORD              " << endl;
    printLine('=', 50);

    string searchID;
    clearInputBuffer();
    cout << "  Enter Cattle ID to Delete: ";
    getline(cin, searchID);

    // Show record first
    fstream preview;
    preview.open("cattle.txt", ios::in);
    bool exists = false;
    string line;
    while (getline(preview, line)) {
        if (line.empty()) continue;
        string id = line.substr(0, line.find('|'));
        if (id == searchID) { exists = true; break; }
    }
    preview.close();

    if (!exists) {
        cout << "\n  [!] Record Not Found!" << endl;
        return;
    }

    char confirm;
    cout << "\n  [?] Are you sure you want to delete cattle '" << searchID << "'? (y/n): ";
    cin >> confirm;
    clearInputBuffer();

    if (confirm != 'y' && confirm != 'Y') {
        cout << "\n  [OK] Delete cancelled." << endl;
        return;
    }

    fstream file, tempFile;
    file.open("cattle.txt", ios::in);
    tempFile.open("cattle_temp.txt", ios::out);

    bool found = false;
    while (getline(file, line)) {
        if (line.empty()) continue;
        string id = line.substr(0, line.find('|'));
        if (id == searchID) found = true;
        else tempFile << line << "\n";
    }

    file.close();
    tempFile.close();

    remove("cattle.txt");
    rename("cattle_temp.txt", "cattle.txt");

    if (found) cout << "\n  [OK] Record Deleted Successfully!" << endl;
    else       cout << "\n  [!] Record Not Found!" << endl;
}

//                   FEED MANAGEMENT

void feedManagement() {
    int choice;
    while (true) {
        system("cls");
        printLine('=', 50);
        cout << "             FEED MANAGEMENT                 " << endl;
        printLine('=', 50);
        cout << "  [1]  Add Feed Record" << endl;
        cout << "  [2]  View All Feed Records" << endl;
        cout << "  [3]  Delete Feed Record" << endl;
        cout << "  [4]  Back" << endl;
        printLine('-', 50);
        cout << "  Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addFeedRecord(); pressEnterToContinue(); break;
            case 2: viewFeedRecords(); pressEnterToContinue(); break;
            case 3: deleteFeedRecord(); pressEnterToContinue(); break;
            case 4: return;
            default:
                cout << "\n  [!] Invalid choice." << endl;
                pressEnterToContinue();
        }
    }
}

void addFeedRecord() {
    system("cls");
    printLine('=', 50);
    cout << "             ADD FEED RECORD                 " << endl;
    printLine('=', 50);

    string feedType, date;
    float quantity, cost;

    clearInputBuffer();
    cout << "  Enter Feed Type     : ";
    getline(cin, feedType);
    cout << "  Enter Date (DD/MM)  : ";
    getline(cin, date);

    cout << "  Enter Quantity (KG) : ";
    while (!(cin >> quantity) || quantity <= 0) {
        cin.clear();
        clearInputBuffer();
        cout << "  [!] Quantity must be > 0. Re-enter: ";
    }

    cout << "  Enter Cost (Rs.)    : ";
    while (!(cin >> cost) || cost < 0) {
        cin.clear();
        clearInputBuffer();
        cout << "  [!] Cost cannot be negative. Re-enter: ";
    }

    fstream file;
    file.open("feed.txt", ios::app);
    if (!file.is_open()) {
        cout << "\n  [!] Error opening feed file." << endl;
        return;
    }
    file << feedType << "|" << date << "|" << quantity << "|" << cost << "\n";
    file.close();

    cout << "\n  [OK] Feed Record Added Successfully!" << endl;
}

void viewFeedRecords() {
    system("cls");
    printLine('=', 55);
    cout << "               FEED RECORDS                  " << endl;
    printLine('=', 55);

    bool found = false;
    fstream file;
    file.open("feed.txt", ios::in);

    if (!file.is_open()) {
        cout << "\n  [!] No feed records found." << endl;
        return;
    }

    printf("  %-18s %-10s %-10s %-10s\n", "Feed Type", "Date", "Qty(KG)", "Cost(Rs.)");
    printLine('-', 55);

    float totalCost = 0, totalQty = 0;
    int count = 0;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        string fields[4];
        size_t pos = 0;
        int idx = 0;
        for (int i = 0; i < 3; i++) {
            size_t next = line.find('|', pos);
            if (next == string::npos) break;
            fields[idx++] = line.substr(pos, next - pos);
            pos = next + 1;
        }
        fields[idx] = line.substr(pos);

        found = true;
        count++;
        totalQty += stof(fields[2]);
        totalCost += stof(fields[3]);
        printf("  %-18s %-10s %-10s %-10s\n",
               fields[0].c_str(), fields[1].c_str(),
               fields[2].c_str(), fields[3].c_str());
    }

    file.close();
    if (!found) {
        cout << "\n  [!] No feed records found." << endl;
    } else {
        printLine('-', 55);
        cout << "  Total Records   : " << count << endl;
        cout << "  Total Quantity  : " << totalQty << " KG" << endl;
        cout << "  Total Cost      : Rs. " << totalCost << endl;
    }
}

void deleteFeedRecord() {
    system("cls");
    printLine('=', 50);
    cout << "           DELETE FEED RECORD                " << endl;
    printLine('=', 50);

    viewFeedRecords();
    cout << "\n";

    int recNum;
    cout << "  Enter Record Number to Delete (1-based): ";
    cin >> recNum;
    clearInputBuffer();

    if (recNum <= 0) {
        cout << "\n  [!] Invalid record number." << endl;
        return;
    }

    fstream file, tempFile;
    file.open("feed.txt", ios::in);
    tempFile.open("feed_temp.txt", ios::out);

    if (!file.is_open()) {
        cout << "\n  [!] No records found." << endl;
        return;
    }

    bool found = false;
    int cur = 0;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        cur++;
        if (cur == recNum) found = true;
        else tempFile << line << "\n";
    }

    file.close();
    tempFile.close();

    remove("feed.txt");
    rename("feed_temp.txt", "feed.txt");

    if (found) cout << "\n  [OK] Feed Record Deleted Successfully!" << endl;
    else       cout << "\n  [!] Record number not found!" << endl;
}

//                  MILK PRODUCTION

void milkManagement() {
    int choice;
    while (true) {
        system("cls");
        printLine('=', 50);
        cout << "           MILK PRODUCTION REPORT            " << endl;
        printLine('=', 50);
        cout << "  [1]  Record Daily Milk" << endl;
        cout << "  [2]  View All Milk Records" << endl;
        cout << "  [3]  View Milk by Cattle ID" << endl;
        cout << "  [4]  Calculate Monthly Total" << endl;
        cout << "  [5]  Back" << endl;
        printLine('-', 50);
        cout << "  Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: recordDailyMilk(); pressEnterToContinue(); break;
            case 2: viewMilkReport(); pressEnterToContinue(); break;
            case 3: viewMilkByCattle(); pressEnterToContinue(); break;
            case 4: calculateMonthlyTotal(); pressEnterToContinue(); break;
            case 5: return;
            default:
                cout << "\n  [!] Invalid choice." << endl;
                pressEnterToContinue();
        }
    }
}

void recordDailyMilk() {
    system("cls");
    printLine('=', 50);
    cout << "            RECORD DAILY MILK                " << endl;
    printLine('=', 50);

    string cattleID, date;
    float liters;

    clearInputBuffer();
    cout << "  Enter Cattle ID     : ";
    getline(cin, cattleID);
    cout << "  Enter Date (DD/MM)  : ";
    getline(cin, date);

    cout << "  Enter Milk (Liters) : ";
    while (!(cin >> liters) || liters <= 0) {
        cin.clear();
        clearInputBuffer();
        cout << "  [!] Milk must be > 0. Re-enter: ";
    }

    fstream file;
    file.open("milk.txt", ios::app);
    if (!file.is_open()) {
        cout << "\n  [!] Error opening milk file." << endl;
        return;
    }
    file << cattleID << "|" << date << "|" << liters << "\n";
    file.close();

    cout << "\n  [OK] Milk Record Added Successfully!" << endl;
}

void viewMilkReport() {
    system("cls");
    printLine('=', 50);
    cout << "          MILK PRODUCTION REPORT             " << endl;
    printLine('=', 50);

    bool found = false;
    fstream file;
    file.open("milk.txt", ios::in);

    if (!file.is_open()) {
        cout << "\n  [!] No milk records found." << endl;
        return;
    }

    printf("  %-12s %-12s %-12s\n", "Cattle ID", "Date", "Milk (L)");
    printLine('-', 40);

    float total = 0;
    int count = 0;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        string fields[3];
        size_t pos = 0;
        int idx = 0;
        for (int i = 0; i < 2; i++) {
            size_t next = line.find('|', pos);
            if (next == string::npos) break;
            fields[idx++] = line.substr(pos, next - pos);
            pos = next + 1;
        }
        fields[idx] = line.substr(pos);

        found = true;
        count++;
        total += stof(fields[2]);
        printf("  %-12s %-12s %-12s\n",
               fields[0].c_str(), fields[1].c_str(), (fields[2] + " L").c_str());
    }

    file.close();
    if (!found) {
        cout << "\n  [!] No milk records found." << endl;
    } else {
        printLine('-', 40);
        cout << "  Total Records : " << count << endl;
        cout << "  Total Milk    : " << total << " L" << endl;
    }
}

void viewMilkByCattle() {
    system("cls");
    printLine('=', 50);
    cout << "          VIEW MILK BY CATTLE ID             " << endl;
    printLine('=', 50);

    string searchID;
    clearInputBuffer();
    cout << "  Enter Cattle ID: ";
    getline(cin, searchID);

    fstream file;
    file.open("milk.txt", ios::in);

    if (!file.is_open()) {
        cout << "\n  [!] No milk records found." << endl;
        return;
    }

    printf("\n  %-12s %-12s %-12s\n", "Cattle ID", "Date", "Milk (L)");
    printLine('-', 40);

    float total = 0;
    int count = 0;
    bool found = false;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        string fields[3];
        size_t pos = 0;
        int idx = 0;
        for (int i = 0; i < 2; i++) {
            size_t next = line.find('|', pos);
            if (next == string::npos) break;
            fields[idx++] = line.substr(pos, next - pos);
            pos = next + 1;
        }
        fields[idx] = line.substr(pos);

        if (fields[0] == searchID) {
            found = true;
            count++;
            total += stof(fields[2]);
            printf("  %-12s %-12s %-12s\n",
                   fields[0].c_str(), fields[1].c_str(), (fields[2] + " L").c_str());
        }
    }

    file.close();
    if (!found) {
        cout << "\n  [!] No milk records found for Cattle ID: " << searchID << endl;
    } else {
        printLine('-', 40);
        cout << "  Total Records : " << count << endl;
        cout << "  Total Milk    : " << total << " L" << endl;
        cout << "  Average/Day   : " << (total / count) << " L" << endl;
    }
}

void calculateMonthlyTotal() {
    system("cls");
    printLine('=', 50);
    cout << "       MONTHLY MILK TOTAL CALCULATOR         " << endl;
    printLine('=', 50);

    float total = 0;
    int count = 0;

    fstream file;
    file.open("milk.txt", ios::in);

    if (!file.is_open()) {
        cout << "\n  [!] No milk records found." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t last = line.rfind('|');
        if (last == string::npos) continue;
        string litersStr = line.substr(last + 1);
        try {
            total += stof(litersStr);
            count++;
        } catch (...) {
            // skip malformed lines
        }
    }

    file.close();

    if (count == 0) {
        cout << "\n  [!] No valid records to calculate." << endl;
        return;
    }

    printLine('-', 50);
    cout << "  Total Daily Records       : " << count << endl;
    cout << "  Total Milk Produced       : " << total << " Liters" << endl;
    cout << "  Average Per Record        : " << (total / count) << " L" << endl;
    cout << "  Estimated Monthly Total   : " << (total / count * 30) << " L" << endl;
    cout << "  Estimated Monthly Avg/Day : " << (total / count) << " L/day" << endl;
    printLine('-', 50);
}

//               USER - VIEW ONLY FEATURES

void viewCattleListUser() {
    viewAllCattle();
}

void checkFeedDetailsUser() {
    viewFeedRecords();
}

void recordDailyMilkUser() {
    system("cls");
    printLine('=', 50);
    cout << "         RECORD DAILY MILK (User)            " << endl;
    printLine('=', 50);
    recordDailyMilk();
}

void viewMilkReportUser() {
    viewMilkReport();
}

//                   VALIDATION FUNCTIONS

bool isPasswordValid(string password) {
    if ((int)password.length() < 7) return false;

    bool hasNumber = false;
    bool hasSpecial = false;

    for (int i = 0; i < (int)password.length(); i++) {
        char c = password[i];
        if (c >= '0' && c <= '9') hasNumber = true;
        if (c == '@' || c == '#' || c == '$') hasSpecial = true;
    }

    return hasNumber && hasSpecial;
}

bool isUsernameUnique(string username, string filename) {
    fstream file;
    file.open(filename, ios::in);
    if (!file.is_open()) return true;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        string u = line.substr(0, line.find('|'));
        if (u == username) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

bool isUsernameUniqueUser(string username) {
    return isUsernameUnique(username, "userData.txt");
}

//                    END OF PROGRAM
