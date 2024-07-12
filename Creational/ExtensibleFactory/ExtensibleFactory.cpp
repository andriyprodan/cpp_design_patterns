// This pattern is a variation of the Factory Method pattern, allowing for the creation of objects at runtime without specifying their exact classes. It's particularly useful for cases where new classes can be added to a system without modifying the code that creates objects.
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <fstream>

class IGameObject {
public:
    // Ensure derived classes call the correct destructor
    virtual ~IGameObject() {}

    // In C++, a pure virtual method (or pure virtual function) is a virtual function that is declared in a base class but is intended to be overridden in derived classes. A class containing at least one pure virtual function is considered an abstract class, meaning it cannot be instantiated directly. Derived classes must provide an implementation for the pure virtual function, otherwise, they too will be abstract classes.
    // A pure virtual function is declared by assigning 0 to the virtual function in the base class declaration.
    virtual void ObjectPlayDefaultAnimation() = 0;
    virtual void ObjectMoveInGame() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
};

class Plane : public IGameObject {
public:
    Plane(int x, int y) {
        ObjectsCreated++;
    }
    void ObjectPlayDefaultAnimation() {}
    void ObjectMoveInGame() {}
    void Update() {}
    void Render() {
        std::cout<<"plane"<<std::endl;
    }
    static IGameObject* Create() {
        return new Plane(0, 0);
    }
private:
    static int ObjectsCreated;
};

int Plane::ObjectsCreated = 0;

class Boat : public IGameObject {
public:
    Boat(int x, int y) {
        ObjectsCreated++;
    }
    void ObjectPlayDefaultAnimation() {}
    void ObjectMoveInGame() {}
    void Update() {}
    void Render() {
        std::cout<<"boat"<<std::endl;
    }
    static IGameObject* Create() {
        return new Boat(0, 0);
    }
private:
    static int ObjectsCreated;
};

int Boat::ObjectsCreated = 0;

// I have removed our 'enum class'
// This is because during run-time I want to be able to create different types
class GameObjectFactory {
    // look for CPP_Overview 58.FunctionPointers
    // it is function type
    // Callback function for creating an object
    typedef IGameObject *(*CreateObjectCallback)();
public:
    // Register a new user created object type
    // Again, we also have to pass in how to 'create' an object.
    static void RegisterObject(const std::string& type, CreateObjectCallback cb);
    // Unregister a use created object type
    // Remove from our map
    static void UnregisterObject(const std::string& type);
    // Our Previous 'Factory Method'
    static IGameObject* CreateSingleObject(const std::string& type);
private:
    // Convenience typedef
    typedef std::map<std::string, CreateObjectCallback> CallbackMap;
    // Map of all the different object that we can create
    static CallbackMap s_Objects;
};

// initialize our static
GameObjectFactory::CallbackMap GameObjectFactory::s_Objects;

void GameObjectFactory::RegisterObject(const std::string& type, CreateObjectCallback cb) {
    s_Objects[type] = cb;
}

// Unregister a user created object type
// Remove from our map
void GameObjectFactory::UnregisterObject(const std::string& type) {
    s_Objects.erase(type);
}

// Our previous 'Factory Method'
IGameObject* GameObjectFactory::CreateSingleObject(const std::string& type) {
    // When you are writing code inside a member function of the GameObjectFactory class (here it is CreateSingleObject method), you are already within the scope of GameObjectFactory. This means you can directly use its member types (like CallbackMap::iterator) and static members (like s_Objects) without needing to prefix them with the class name. 
    CallbackMap::iterator it = s_Objects.find(type);
    if (it!=s_Objects.end()) {
        return (it->second)();
    }
    // returning nullptr is not the best practice!!!
    // it is better to create the error handling
    return nullptr;
}

class Ant : public IGameObject {
public:
    Ant(int x, int y) {
        ObjectsCreated++;
    }
    void ObjectPlayDefaultAnimation() {}
    void ObjectMoveInGame() {}
    void Update() {}
    void Render() {
        std::cout<<"ant"<<std::endl;
    }
    static IGameObject* Create() {
        return new Ant(0, 0);
    }
private:
    static int ObjectsCreated;
};

int Ant::ObjectsCreated = 0;

int main() {
    // Register a different type
    GameObjectFactory::RegisterObject("plane", Plane::Create);
    GameObjectFactory::RegisterObject("boat", Boat::Create);
    GameObjectFactory::RegisterObject("ant", Ant::Create);

    std::vector<IGameObject*> gameObjectCollection;
    // Add the correct object to our collection
    // based on a .txt file
    std::string line;
    std::ifstream myFile("level1.txt");
    if (myFile.is_open()) {
        while(std::getline(myFile, line)) {
            // For each line that is read in, then create a game object for that type
            IGameObject* object = GameObjectFactory::CreateSingleObject(line);
            gameObjectCollection.push_back(object);
        }
    }

    // while(true) {
        for (auto& e: gameObjectCollection) {
            e->Update();
            e->Render();
        }
    // }

    return 0;
}