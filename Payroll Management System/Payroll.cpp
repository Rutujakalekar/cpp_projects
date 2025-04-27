#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Employee {
private:
    int id;
    string name, address, phone, designation, joinDate;
    char grade;
    float basicSalary, houseAllowance, conveyanceAllowance, loanAmount;

public:
    Employee() : id(0), grade('E'), basicSalary(0), houseAllowance(0), conveyanceAllowance(0), loanAmount(0) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getDesignation() const { return designation; }
    float getBasicSalary() const { return basicSalary; }

    void inputDetails();
    void displayDetails() const;
    void displaySalarySlip() const;
    void saveToFile(ofstream& file) const;
    void readFromFile(ifstream& file);
};

void Employee::inputDetails() {
    cout << "\nEnter Employee ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Address: ";
    getline(cin, address);

    cout << "Enter Phone: ";
    getline(cin, phone);

    cout << "Enter Designation: ";
    getline(cin, designation);

    cout << "Enter Grade (A/B/C/D/E): ";
    cin >> grade;
    grade = toupper(grade);

    cout << "Enter Join Date (DD/MM/YYYY): ";
    cin >> joinDate;

    cout << "Enter Basic Salary: ";
    cin >> basicSalary;

    char choice;
    cout << "House Allowance (Y/N): ";
    cin >> choice;
    if (toupper(choice) == 'Y') houseAllowance = basicSalary * 0.1;

    cout << "Conveyance Allowance (Y/N): ";
    cin >> choice;
    if (toupper(choice) == 'Y') conveyanceAllowance = basicSalary * 0.05;

    cout << "Enter Loan Amount (if any): ";
    cin >> loanAmount;
}

void Employee::displayDetails() const {
    cout << "\nEmployee ID: " << id
         << "\nName: " << name
         << "\nAddress: " << address
         << "\nPhone: " << phone
         << "\nDesignation: " << designation
         << "\nGrade: " << grade
         << "\nJoin Date: " << joinDate
         << "\nBasic Salary: " << basicSalary << endl;
}

void Employee::displaySalarySlip() const {
    cout << "\n----------- SALARY SLIP -----------\n";
    cout << "Employee Name: " << name << "\tID: " << id << endl;
    cout << "Designation: " << designation << "\tGrade: " << grade << endl;
    cout << "\nEarnings:";
    cout << "\nBasic Salary: " << basicSalary;
    cout << "\nHouse Allowance: " << houseAllowance;
    cout << "\nConveyance Allowance: " << conveyanceAllowance;
    cout << "\n\nDeductions:";
    cout << "\nLoan Deduction: " << (loanAmount > 0 ? loanAmount * 0.1 : 0);
    cout << "\nProvident Fund: " << (basicSalary * 0.12);
    float totalEarnings = basicSalary + houseAllowance + conveyanceAllowance;
    float totalDeductions = (loanAmount > 0 ? loanAmount * 0.1 : 0) + (basicSalary * 0.12);
    float netSalary = totalEarnings - totalDeductions;
    cout << "\n\nNet Salary: " << netSalary << endl;
}

void Employee::saveToFile(ofstream& file) const {
    file << id << endl << name << endl << address << endl << phone << endl
         << designation << endl << grade << endl << basicSalary << endl
         << houseAllowance << endl << conveyanceAllowance << endl
         << loanAmount << endl << joinDate << endl;
}

void Employee::readFromFile(ifstream& file) {
    file >> id;
    file.ignore();
    getline(file, name);
    getline(file, address);
    getline(file, phone);
    getline(file, designation);
    file >> grade >> basicSalary >> houseAllowance >> conveyanceAllowance >> loanAmount;
    file.ignore();
    getline(file, joinDate);
}

class PayrollSystem {
private:
    vector<Employee> employees;
    string filename = "employees.dat";

public:
    void loadEmployees();
    void saveEmployees();
    void addEmployee();
    void viewEmployee();
    void listEmployees();
    void generateSalarySlip();
    void editEmployee();
    void deleteEmployee();
    void menu();
};

void PayrollSystem::loadEmployees() {
    ifstream file(filename);
    if (!file) return;

    Employee emp;
    while (!file.eof()) {
        emp.readFromFile(file);
        if (file.eof()) break;
        employees.push_back(emp);
    }
    file.close();
}

void PayrollSystem::saveEmployees() {
    ofstream file(filename);
    for (const auto& emp : employees)
        emp.saveToFile(file);
    file.close();
}

void PayrollSystem::addEmployee() {
    Employee emp;
    emp.inputDetails();
    employees.push_back(emp);
    saveEmployees();
    cout << "\nEmployee added successfully!\n";
}

void PayrollSystem::viewEmployee() {
    int id;
    cout << "\nEnter Employee ID to view: ";
    cin >> id;
    auto it = find_if(employees.begin(), employees.end(), [id](const Employee& emp) { return emp.getId() == id; });

    if (it != employees.end())
        it->displayDetails();
    else
        cout << "Employee not found!\n";
}

void PayrollSystem::listEmployees() {
    cout << "\nList of Employees:\n";
    for (const auto& emp : employees) {
        cout << emp.getId() << " - " << emp.getName() << " - " << emp.getDesignation() << " - Salary: " << emp.getBasicSalary() << endl;
    }
}

void PayrollSystem::generateSalarySlip() {
    int id;
    cout << "\nEnter Employee ID to generate salary slip: ";
    cin >> id;
    auto it = find_if(employees.begin(), employees.end(), [id](const Employee& emp) { return emp.getId() == id; });

    if (it != employees.end())
        it->displaySalarySlip();
    else
        cout << "Employee not found!\n";
}

void PayrollSystem::editEmployee() {
    int id;
    cout << "\nEnter Employee ID to edit: ";
    cin >> id;
    auto it = find_if(employees.begin(), employees.end(), [id](const Employee& emp) { return emp.getId() == id; });

    if (it != employees.end()) {
        it->inputDetails();
        saveEmployees();
        cout << "Employee updated successfully!\n";
    } else {
        cout << "Employee not found!\n";
    }
}

void PayrollSystem::deleteEmployee() {
    int id;
    cout << "\nEnter Employee ID to delete: ";
    cin >> id;
    auto it = find_if(employees.begin(), employees.end(), [id](const Employee& emp) { return emp.getId() == id; });

    if (it != employees.end()) {
        employees.erase(it);
        saveEmployees();
        cout << "Employee deleted successfully!\n";
    } else {
        cout << "Employee not found!\n";
    }
}

void PayrollSystem::menu() {
    int choice;
    do {
        cout << "\n\n===== Payroll Management System =====";
        cout << "\n1. Add New Employee";
        cout << "\n2. View Employee";
        cout << "\n3. List All Employees";
        cout << "\n4. Generate Salary Slip";
        cout << "\n5. Edit Employee";
        cout << "\n6. Delete Employee";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployee(); break;
            case 3: listEmployees(); break;
            case 4: generateSalarySlip(); break;
            case 5: editEmployee(); break;
            case 6: deleteEmployee(); break;
            case 0: cout << "Exiting..."; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);
}

int main() {
    PayrollSystem payroll;
    payroll.loadEmployees();
    payroll.menu();
    return 0;
}
