#include <iostream>
#include <string>
using namespace std;

class Employee {
protected:
    string name;
    int age;

public:
    Employee(string name, int age);
    virtual void print() const;
    virtual double income() const = 0;
    virtual ~Employee();
};

class Waiter : virtual public Employee {
protected:
    double basicSalary;
    double bonus;

public:
    Waiter(string name, int age, double basicSalary, double bonus);
    void print() const;
    double income() const;
};

class Singer : virtual public Employee {
protected:
    double hourlyWage;
    double weeklyHours;

public:
    Singer(string name, int age, double hourlyWage, double weeklyHours);
    void print() const;
    double income() const;
};

class SingerWaiter : public Waiter, public Singer {
public:
    SingerWaiter(string name, int age, double basicSalary, double bonus,
        double hourlyWage, double singerDayHours);
    void print() const;
    double income() const;
};

Employee::Employee(string name, int age) {
    this->name = name;
    this->age = age;
}

void Employee::print() const {
    cout << "Name: " << name << ", Age: " << age;
}

Employee::~Employee() {}

Waiter::Waiter(string name, int age, double basicSalary, double bonus)
    : Employee(name, age), basicSalary(basicSalary), bonus(bonus) {
}

void Waiter::print() const {
    Employee::print();
    cout << ", Job: Waiter";
    cout << ", Basic: " << basicSalary << ", Bonus: " << bonus;
}

double Waiter::income() const {
    return basicSalary + bonus;
}

Singer::Singer(string name, int age, double hourlyWage, double weeklyHours)
    : Employee(name, age), hourlyWage(hourlyWage), weeklyHours(weeklyHours) {
}

void Singer::print() const {
    Employee::print();
    cout << ", Job: Singer";
    cout << ", Wage/h: " << hourlyWage << ", Hours/week: " << weeklyHours;
}

double Singer::income() const {
    return hourlyWage * weeklyHours;
}

SingerWaiter::SingerWaiter(string name, int age, double basicSalary, double bonus,
    double hourlyWage, double singerDayHours)
    : Employee(name, age), Waiter(name, age, basicSalary, bonus),
    Singer(name, age, hourlyWage, singerDayHours) {
}

void SingerWaiter::print() const {
    Employee::print();
    cout << ", Job: Singer-Waiter";
    cout << ", Basic: " << basicSalary << ", Bonus: " << bonus;
    cout << ", Wage/h: " << hourlyWage << ", Singer hours/day: " << weeklyHours;
}

double SingerWaiter::income() const {
    return basicSalary + bonus + hourlyWage * weeklyHours;
}

int main() {
    Waiter w("Zhang", 25, 3000, 500);
    Singer s("Li", 22, 200, 10);
    SingerWaiter sw("Wang", 28, 3000, 500, 200, 8);

    Employee* staff[3];
    staff[0] = &w;
    staff[1] = &s;
    staff[2] = &sw;

    cout << "===== Restaurant Staff =====" << endl;
    for (int i = 0; i < 3; i++) {
        staff[i]->print();
        cout << ", Income: " << staff[i]->income() << endl;
        cout << endl;
    }

    return 0;
}