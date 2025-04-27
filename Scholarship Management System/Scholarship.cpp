#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Structure for Student
struct Student {
    string username;
    string password;
    string name;
    int age;
    string gender;
    string caste;
    string ruralUrban;
    int income;
    float sscMarks;     // 10th % (out of 100)
    float hscMarks;     // 12th % (out of 100)
    float jeeMarks;
    bool sportsCertificate;
    vector<string> appliedScholarships;
    float totalScholarshipAmount;
};

// Scholarship structure
struct Scholarship {
    string name;
    string criteria;
    float amount;
};

// List of Scholarships
vector<Scholarship> scholarships = {
    {"Merit Scholarship", "HSC marks >= 85%", 50000},
    {"JEE Scholarship", "JEE marks >= 150", 40000},
    {"Caste Scholarship", "Caste is SC/ST/OBC", 30000},
    {"Rural Student Scholarship", "Background is Rural", 25000},
    {"Sports Scholarship", "Has Sports Certificate", 45000}
};

// Save student to file
void saveStudent(Student s) {
    ofstream out("students/" + s.username + ".txt");
    if (out.is_open()) {
        out << s.username << endl;
        out << s.password << endl;
        out << s.name << endl;
        out << s.age << endl;
        out << s.gender << endl;
        out << s.caste << endl;
        out << s.ruralUrban << endl;
        out << s.income << endl;
        out << s.sscMarks << endl;
        out << s.hscMarks << endl;
        out << s.jeeMarks << endl;
        out << s.sportsCertificate << endl;
        out << s.totalScholarshipAmount << endl;
        for (auto &sch : s.appliedScholarships) {
            out << sch << endl;
        }
        out.close();
    }
}

// Load student from file
Student loadStudent(string username) {
    Student s;
    ifstream in("students/" + username + ".txt");
    if (in.is_open()) {
        getline(in, s.username);
        getline(in, s.password);
        getline(in, s.name);
        in >> s.age;
        in.ignore();
        getline(in, s.gender);
        getline(in, s.caste);
        getline(in, s.ruralUrban);
        in >> s.income;
        in >> s.sscMarks;
        in >> s.hscMarks;
        in >> s.jeeMarks;
        in >> s.sportsCertificate;
        in >> s.totalScholarshipAmount;
        in.ignore();
        string applied;
        while (getline(in, applied)) {
            if (!applied.empty())
                s.appliedScholarships.push_back(applied);
        }
        in.close();
    }
    return s;
}

// Registration
void registerStudent() {
    Student s;
    cout << "\n----- Student Registration -----\n";
    cout << "Choose a Username: ";
    cin >> s.username;
    cout << "Choose a Password: ";
    cin >> s.password;
    cout << "Full Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Age: ";
    cin >> s.age;
    cout << "Gender: ";
    cin >> s.gender;
    cout << "Caste (General/SC/ST/OBC): ";
    cin >> s.caste;
    cout << "Background (Rural/Urban): ";
    cin >> s.ruralUrban;
    cout << "Family Annual Income (₹): ";
    cin >> s.income;
    cout << "10th Percentage (SSC): ";
    cin >> s.sscMarks;
    cout << "12th Percentage (HSC): ";
    cin >> s.hscMarks;
    cout << "JEE Marks: ";
    cin >> s.jeeMarks;
    cout << "Do you have a State/National Sports Certificate (1-Yes / 0-No)? ";
    cin >> s.sportsCertificate;
    s.totalScholarshipAmount = 0;
    saveStudent(s);
    cout << "\nRegistration Successful! Please login to continue.\n";
}

// Login
bool loginStudent(Student &s) {
    string username, password;
    cout << "\n----- Student Login -----\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    s = loadStudent(username);
    if (s.username == username && s.password == password) {
        cout << "\nLogin Successful! Welcome, " << s.name << endl;
        return true;
    } else {
        cout << "\nInvalid Credentials. Try again.\n";
        return false;
    }
}

// Check eligibility and apply
void applyScholarship(Student &s) {
    cout << "\n----- Available Scholarships for You -----\n";
    vector<Scholarship> eligible;
    for (auto &sch : scholarships) {
        bool eligibleFlag = false;
        if (sch.name == "Merit Scholarship" && s.hscMarks >= 85)
            eligibleFlag = true;
        if (sch.name == "JEE Scholarship" && s.jeeMarks >= 150)
            eligibleFlag = true;
        if (sch.name == "Caste Scholarship" && (s.caste == "SC" || s.caste == "ST" || s.caste == "OBC"))
            eligibleFlag = true;
        if (sch.name == "Rural Student Scholarship" && s.ruralUrban == "Rural")
            eligibleFlag = true;
        if (sch.name == "Sports Scholarship" && s.sportsCertificate == 1)
            eligibleFlag = true;
        
        if (eligibleFlag)
            eligible.push_back(sch);
    }

    if (eligible.empty()) {
        cout << "Sorry, no scholarships available for your profile.\n";
        return;
    }

    cout << "\nEligible Scholarships:\n";
    for (int i = 0; i < eligible.size(); ++i) {
        cout << i + 1 << ". " << eligible[i].name << " - " << eligible[i].amount << " Rs\n";
    }

    cout << "\nEnter the numbers of scholarships you want to apply for (0 to stop): \n";
    int choice;
    while (true) {
        cout << "Choice: ";
        cin >> choice;
        if (choice == 0)
            break;
        if (choice >= 1 && choice <= eligible.size()) {
            s.appliedScholarships.push_back(eligible[choice - 1].name);
            s.totalScholarshipAmount += eligible[choice - 1].amount;
            cout << "Applied for: " << eligible[choice - 1].name << endl;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    saveStudent(s);
    cout << "\nSuccessfully applied. Total Scholarship Amount Approved: ₹" << s.totalScholarshipAmount << "\n";
}

// Main Menu
void menu() {
    int choice;
    do {
        cout << "\n====== MahaDBT Mini System ======\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        Student s;
        switch (choice) {
            case 1:
                registerStudent();
                break;
            case 2:
                if (loginStudent(s)) {
                    applyScholarship(s);
                }
                break;
            case 3:
                cout << "Exiting... Thank you!\n";
                break;
            default:
                cout << "Invalid Choice. Try Again.\n";
        }
    } while (choice != 3);
}

int main() {
    system("mkdir students");  // Creates folder to save student files
    menu();
    return 0;
}
