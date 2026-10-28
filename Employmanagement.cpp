#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    int id;
    string name;
    float salary;
    static int count;

public:
    Employee() {
        id = 0;
        name = "";
        salary = 0;
        count++;
    }

    void input() {
        cout << "Enter Employee ID: ";
        cin >> id;

        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter Salary: ";
        cin >> salary;

        if (salary < 0) {
            cout << "Invalid salary! Salary cannot be negative.\n";
            salary = 0;
        }
    }

    void setSalary(float salary) {
        if (salary >= 0)
            this->salary = salary;
        else
            cout << "Invalid salary!\n";
    }

    int getId() {
        return id;
    }

    float getSalary() {
        return salary;
    }

    static void showCount() {
        cout << "Total employee objects: " << count << endl;
    }

    friend void showEmployee(Employee e);

    virtual void display() {
        cout << "Employee ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
    }

    virtual ~Employee() {
        count--;
    }
};

int Employee::count = 0;

void showEmployee(Employee e) {
    cout << "Name: " << e.name << endl;
    cout << "Salary: " << e.salary << endl;
}

class Payroll : public Employee {
public:
    void display() override {
        Employee::display();

        if (getSalary() >= 25000)
            cout << "Salary Status: Standard\n";
        else
            cout << "Salary Status: Below Standard\n";
    }
};

int main() {
    const int MAX = 100;
    Employee* employees[MAX];
    int count = 0;
    int choice;

    do {
        cout << "\n===== EMPLOYEE MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Update Salary\n";
        cout << "5. Delete Employee\n";
        cout << "6. Show Total Objects\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                if (count == MAX) {
                    cout << "Employee list is full!\n";
                    break;
                }

                Employee* e = new Payroll();
                e->input();

                bool duplicate = false;

                for (int i = 0; i < count; i++) {
                    if (employees[i]->getId() == e->getId()) {
                        duplicate = true;
                        break;
                    }
                }

                if (duplicate) {
                    cout << "Employee ID already exists!\n";
                    delete e;
                } else {
                    employees[count] = e;
                    count++;
                    cout << "Employee added successfully!\n";
                }
                break;
            }

            case 2:
                if (count == 0) {
                    cout << "No employee records found!\n";
                }

                for (int i = 0; i < count; i++) {
                    cout << "\nEmployee " << i + 1 << endl;
                    employees[i]->display();
                }
                break;

            case 3: {
                int id, found = -1;
                cout << "Enter Employee ID to search: ";
                cin >> id;

                for (int i = 0; i < count; i++) {
                    if (employees[i]->getId() == id) {
                        found = i;
                        break;
                    }
                }

                if (found == -1)
                    cout << "Employee not found!\n";
                else
                    employees[found]->display();

                break;
            }

            case 4: {
                int id, found = -1;
                float salary;

                cout << "Enter Employee ID: ";
                cin >> id;

                for (int i = 0; i < count; i++) {
                    if (employees[i]->getId() == id) {
                        found = i;
                        break;
                    }
                }

                if (found == -1) {
                    cout << "Employee not found!\n";
                } else {
                    cout << "Enter new salary: ";
                    cin >> salary;
                    employees[found]->setSalary(salary);
                }
                break;
            }

            case 5: {
                int id, found = -1;
                cout << "Enter Employee ID to delete: ";
                cin >> id;

                for (int i = 0; i < count; i++) {
                    if (employees[i]->getId() == id) {
                        found = i;
                        break;
                    }
                }

                if (found == -1) {
                    cout << "Employee not found!\n";
                } else {
                    delete employees[found];

                    for (int i = found; i < count - 1; i++) {
                        employees[i] = employees[i + 1];
                    }

                    count--;
                    cout << "Employee object deleted successfully!\n";
                }
                break;
            }

            case 6:
                Employee::showCount();
                break;

            case 0:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    for (int i = 0; i < count; i++) {
        delete employees[i];
    }

    return 0;
}
