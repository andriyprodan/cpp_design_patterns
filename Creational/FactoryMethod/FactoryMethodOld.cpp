// The Factory Method pattern provides a generalized way to create instances of an object and can be a great way to hide implementation details for derived class
#include <iostream>
#include <string>
#include <memory>

class IGameObject {
public:

    virtual ~IGameObject() {}

    // In C++, a pure virtual method (or pure virtual function) is a virtual function that is declared in a base class but is intended to be overridden in derived classes. A class containing at least one pure virtual function is considered an abstract class, meaning it cannot be instantiated directly. Derived classes must provide an implementation for the pure virtual function, otherwise, they too will be abstract classes.
    // A pure virtual function is declared by assigning 0 to the virtual function in the base class declaration.
    virtual void Update() = 0;
    virtual void Render() = 0;
};

class Plane : public IGameObject {
public:
    Plane() {}
    void Update() {}
    void Render() {}
};

class Boat : public IGameObject {
public:
    Boat() {}
    void Update() {}
    void Render() {}
};


enum class ObjectType {PLANE, BOAT};

// singleton in which the factory method is wrapped
// this singleton is used to store the number of the created objects 
class FactoryGameObjects {
public:
    static std::shared_ptr<IGameObject> CreateObject(ObjectType type) {
        if (type==ObjectType::PLANE) {
            s_plane_count++;
            return std::make_shared<Plane>();
        } else if (type==ObjectType::BOAT) {
            s_boat_count++;
            return std::make_shared<Boat>();
        }
        return nullptr; // code will never reach here
    }

    static void PrintCounts() {
        std::cout << "planes: " << s_plane_count << std::endl;
        std::cout << "boats: " << s_boat_count << std::endl;
    }

private:
    FactoryGameObjects() {}
    ~FactoryGameObjects() {}
    // copy constructor is added explicitly to avoid accidentally being called
    FactoryGameObjects(const FactoryGameObjects& o) {}
    
    static int s_plane_count;
    static int s_boat_count;
};

int FactoryGameObjects::s_boat_count = 0;
int FactoryGameObjects::s_plane_count = 0;

// Factory method

int main() {
    std::shared_ptr<IGameObject> plane = FactoryGameObjects::CreateObject(ObjectType::PLANE);
    std::shared_ptr<IGameObject> boat = FactoryGameObjects::CreateObject(ObjectType::BOAT);
    std::shared_ptr<IGameObject> boat2 = FactoryGameObjects::CreateObject(ObjectType::BOAT);

    FactoryGameObjects::PrintCounts();

    return 0;
}