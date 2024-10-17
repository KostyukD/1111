#include <iostream>

using namespace std;

class Reservoir 
{
private:
    char* name;
    float width;
    float length;
    float maxDepth;
    char type; // Тип: 'L' для пруда, 'P' для бассейна, 'S' для моря

    void copyString(const char* source) 
    {
        if (source) 
        {
            int len = 0;
            while (source[len] != '\0') 
            {
                len++;
            }
            name = new char[len + 1];
            for (int i = 0; i < len; i++) 
            {
                name[i] = source[i];
            }
            name[len] = '\0';
        }
        else 
        {
            name = nullptr;
        }
    }

public:

    Reservoir() : name(nullptr), width(0), length(0), maxDepth(0), type('L') {}


    explicit Reservoir(const char* reservoirName, float w, float l, float d, char t)
        : width(w), length(l), maxDepth(d), type(t)
    {
        copyString(reservoirName);
    }


    Reservoir(const Reservoir& other)
        : width(other.width), length(other.length), maxDepth(other.maxDepth), type(other.type)
    {
        copyString(other.name);
    }


    Reservoir& operator=(const Reservoir& other) 
    {
        if (this != &other) 
        {
            delete[] name;
            width = other.width;
            length = other.length;
            maxDepth = other.maxDepth;
            type = other.type;
            copyString(other.name);
        }
        return *this;
    }

    // Деструктор
    ~Reservoir() 
    {
        delete[] name;
    }

    float getVolume() const 
    {
        return width * length * maxDepth;
    }

    float getSurfaceArea() const 
    {
        return width * length;
    }

    bool isSameType(const Reservoir& other) const 
    {
        return type == other.type;
    }

    bool compareSurfaceArea(const Reservoir& other) const 
    {
        if (isSameType(other)) 
        {
            return getSurfaceArea() > other.getSurfaceArea();
        }
        return false;
    }

    void setName(const char* reservoirName) 
    {
        delete[] name;
        copyString(reservoirName);
    }

    const char* getName() const 
    {
        return name;
    }

    void display() const 
    {
        cout << "name: " << (name ? name : "not specified") << endl;
        cout << "width: " << width << ", length: " << length << ", maximum depth: " << maxDepth << endl;
        cout << "type: " << (type == 'L' ? "pond" : (type == 'P' ? "pool" : "sea")) << endl;
    }
};

class ReservoirManager 
{
private:
    Reservoir* reservoirs;
    int size;
    int capacity;

public:
    ReservoirManager() : size(0), capacity(2) 
    {
        reservoirs = new Reservoir[capacity];
    }

    ~ReservoirManager() 
    {
        delete[] reservoirs;
    }


    void addReservoir(const Reservoir& r) 
    {
        if (size >= capacity) 
        {
            capacity *= 2;
            Reservoir* newReservoirs = new Reservoir[capacity];
            for (int i = 0; i < size; i++) 
            {
                newReservoirs[i] = reservoirs[i];
            }
            delete[] reservoirs;
            reservoirs = newReservoirs;
        }
        reservoirs[size++] = r;
    }


    void removeReservoir(int index) 
    {
        if (index < 0 || index >= size) 
        {
            cout << "index out of range" << endl;
            return;
        }
        for (int i = index; i < size - 1; i++) 
        {
            reservoirs[i] = reservoirs[i + 1];
        }
        size--;
    }


    void displayAll() const 
    {
        if (size == 0) 
        {
            cout << "no reservoirs available" << endl;
        }
        else 
        {
            for (int i = 0; i < size; i++) 
            {
                cout << "reservoir " << (i + 1) << ":" << endl;
                reservoirs[i].display();
                cout << endl;
            }
        }
    }

    int getSize() const 
    {
        return size;
    }
};


void displayMenu() 
{
    cout << "=====================================" << endl;
    cout << "1. add a new reservoir" << endl;
    cout << "2. remove a reservoir" << endl;
    cout << "3. display all reservoirs" << endl;
    cout << "4. exit" << endl;
    cout << "your hoose: ";
}


Reservoir createReservoirFromInput() 
{
    char name[50];
    float width, length, maxDepth;
    char type;

    cout << "enter the name of the reservoir: ";
    cin.ignore();
    cin.getline(name, 50);

    cout << "enter width: ";
    cin >> width;

    cout << "enter length: ";
    cin >> length;

    cout << "enter maximum depth: ";
    cin >> maxDepth;

    cout << "enter type (L for pond, P for pool, S for sea): ";
    cin >> type;

    return Reservoir(name, width, length, maxDepth, type);
}

int main() 
{
    ReservoirManager manager;
    int choice;

    do 
    {
        displayMenu();
        cin >> choice;

        switch (choice) 
        {
        case 1: 
        {

            Reservoir newReservoir = createReservoirFromInput();
            manager.addReservoir(newReservoir);
            cout << "reservoir added successfully" << endl;
            break;
        }
        case 2: 
        {

            int index;
            if (manager.getSize() == 0) 
            {
                cout << "no reservoirs to remove" << endl;
            }
            else 
            {
                cout << "enter index of reservoir to remove (starting from 1): ";
                cin >> index;
                manager.removeReservoir(index - 1);
                cout << "reservoir removed" << endl;
            }
            break;
        }
        case 3: 
        {

            manager.displayAll();
            break;
        }
        case 4:
            cout << "exit" << endl;
            break;
        default:
            cout << "invalid option" << endl;
        }

    } while (choice != 4);

    return 0;
}
