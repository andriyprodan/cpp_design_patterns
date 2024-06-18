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

// Factory method
std::shared_ptr<IGameObject> MakeObjectFactory(ObjectType type) {
    if (type==ObjectType::PLANE) {
        return std::make_shared<Plane>();
    } else if (type==ObjectType::BOAT) {
        return std::make_shared<Boat>();
    }
    return nullptr; // code will never reach here
}

int main() {
    std::shared_ptr<IGameObject> myObject = MakeObjectFactory(ObjectType::PLANE);
    std::shared_ptr<IGameObject> myObject2 = MakeObjectFactory(ObjectType::BOAT);

    return 0;
}