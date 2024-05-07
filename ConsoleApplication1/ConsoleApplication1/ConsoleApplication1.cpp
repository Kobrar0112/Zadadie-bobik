#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Animal {
protected:
    string name;
    bool alive;

public:
    Animal(const string& _name) : name(_name), alive(true) {}

    virtual void Feed(int food) = 0;

    bool isAlive() const {
        return alive;
    }

    void setAlive(bool status) {
        alive = status;
    }
};

class Pet : public Animal {
public:
    Pet(const string& _name) : Animal(_name) {}

    virtual void Feed(int food) = 0;

    void WaitToFeedAgain() {
        cout << "Питомец не хочет есть. Попробуйте позже." << endl;
    }
};

class Dog : public Pet {
public:
    Dog(const string& _name) : Pet(_name) {}

    void Feed(int food) override {
        if (!isAlive()) {
            cout << "Этот питомец уже умер. Создайте нового." << endl;
            return;
        }

        cout << "Кормление " << name << "... ";
        srand(time(0));
        int chance = rand() % 101;
        if (chance >= food) {
            cout << "Ммм! " << name << " кушает." << endl;
        }
        else {
            cout << "Упс! " << name << " не смог есть." << endl;
            setAlive(false);
        }
    }
};

class Cat : public Pet {
public:
    Cat(const string& _name) : Pet(_name) {}

    void Feed(int food) override {
        if (!isAlive()) {
            cout << "Этот питомец уже умер. Создайте нового." << endl;
            return;
        }

        cout << "Кормление " << name << "... ";
        srand(time(0));
        int chance = rand() % 101;
        if (chance >= food) {
            cout << "Ммм! " << name << " кушает." << endl;
        }
        else {
            cout << "Упс! " << name << " Бобик сдох." << endl;
            setAlive(false);
        }
    }
};

int main() {
    srand(time(0));
    setlocale(LC_ALL, "Russian");

    int food;
    string name;

    cout << "Введите имя питомца: ";
    cin >> name;

    Animal* pet;

    char type;
    cout << "Выберите тип питомца (d - собака, c - кот): ";
    cin >> type;

    switch (type) {
    case 'd':
        pet = new Dog(name);
        break;
    case 'c':
        pet = new Cat(name);
        break;
    default:
        cout << "Неверный выбор типа питомца." << endl;
        return 1;
    }

    do {
        cout << "Введите количество еды для " << name << ": ";
        cin >> food;

        cout << endl;
        pet->Feed(food);

        if (!pet->isAlive()) {
            delete pet;
            cout << "Хотите создать нового питомца? (y/n): ";
            cin >> type;
            if (type == 'y') {
                cout << "Введите имя нового питомца: ";
                cin >> name;
                cout << "Выберите тип нового питомца (d - собака, c - кот): ";
                cin >> type;
                switch (type) {
                case 'd':
                    pet = new Dog(name);
                    break;
                case 'c':
                    pet = new Cat(name);
                    break;
                default:
                    cout << "Неверный выбор типа питомца." << endl;
                    return 1;
                }
            }
        }
        else {
            cout << "Хотите покормить " << name << " еще раз? (y/n): ";
            cin >> type;
        }

    } while (type == 'y');

    if (pet->isAlive()) {
        delete pet;
    }

    return 0;
}