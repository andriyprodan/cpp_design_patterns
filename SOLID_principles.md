https://medium.com/@oleksandra_shershen/solid-principles-implementation-and-examples-in-c-99f0d7e3e868

SOLID principles are widely adopted by software developers as a set of guidelines for designing maintainable and extensible code. By following these principles, developers can create software that is easier to understand, modify, and test. In this article, we discussed each of the SOLID principles and provided examples of how they can be implemented in C++.

### Introduction
SOLID principles are a set of guidelines or best practices for object-oriented programming that help to create software that is more maintainable, flexible, and scalable. The term “SOLID” is an acronym for five different principles, each of which focuses on a different aspect of software development:

**S** — Single Responsibility Principle (SRP)  
**O** — Open-Closed Principle (OCP)  
**L** — Liskov Substitution Principle (LSP)  
**I** — Interface Segregation Principle (ISP)  
**D** — Dependency Inversion Principle (DIP)  

### Single Responsibility Principle (SRP)
The **Single Responsibility Principle (SRP)** is one of the five SOLID principles of object-oriented design. It states that a class should have only one responsibility, which means it should **have only one reason to change**. This principle helps in reducing the coupling between classes and makes the code more maintainable and scalable.

In C++, SRP can be implemented by dividing the responsibilities of a class into smaller, more focused classes. Each class should be responsible for only one task and should have no other reason to change. This makes the code easier to understand, modify and test.

Let’s consider an example of a class named `Customer` which is responsible for calculating the final bill of a customer. In its current form, the `Customer` class has several responsibilities, such as maintaining the customer details, calculating the final bill, and generating an invoice.

```cpp
class Customer {
private:
  string name;
  int id;
  vector<Item> items;
  float totalAmount;
public:
  void setName(string name);
  string getName();
  void setId(int id);
  int getId();
  void addItem(Item item);
  void removeItem(Item item);
  float calculateTotalAmount();
  string generateInvoice();
};
```

As we can see, the `Customer` class is responsible for multiple tasks, such as maintaining customer details, calculating the final bill, and generating an invoice. This violates the Single Responsibility Principle, as the class has multiple reasons to change. For instance, if the calculation of the final bill is changed, then the Customer class needs to be modified, even though it is not related to the customer details or the generation of invoices.  

To implement SRP, we can create separate classes for each of these responsibilities. For example, we can create a `CustomerDetails` class to handle the customer details, a `BillingCalculator` class to calculate the final bill, and an `InvoiceGenerator` class to generate the invoice.

```cpp
class CustomerDetails {
private:
  string name;
  int id;
public:
  void setName(string name);
  string getName();
  void setId(int id);
  int getId();
};

class BillingCalculator {
private:
  vector<Item> items;
public:
  void addItem(Item item);
  void removeItem(Item item);
  float calculateTotalAmount();
};

class InvoiceGenerator {
public:
  string generateInvoice(CustomerDetails customerDetails, BillingCalculator billingCalculator);
};
```
By dividing the responsibilities of the `Customer` class into smaller, more focused classes, each class has only one responsibility, which makes the code more maintainable and scalable. If any changes are required in any of these classes, only that class needs to be modified, rather than the entire `Customer` class. This leads to cleaner and more maintainable code, which is easier to understand, modify and test.

### Open-Closed Principle (OCP)
The **Open-Closed Principle (OCP)** is one of the five SOLID principles of object-oriented design. It states that a class should be open for extension but closed for modification. This principle helps in making the code more maintainable and flexible.

In C++, OCP can be implemented by creating classes that can be extended by adding new functionality without modifying the existing code. This is achieved by using inheritance, polymorphism, and interfaces. By following this principle, we can make the code more modular and less prone to bugs.

Let’s consider an example of a `Shape` class hierarchy that includes different types of shapes, such as `Rectangle`, `Circle`, and `Triangle`. Each shape has a different area calculation method.

```cpp
class Shape {
public:
  virtual double area() = 0;
};

class Rectangle : public Shape {
private:
  double width;
  double height;
public:
  Rectangle(double width, double height);
  double area() override;
};

class Circle : public Shape {
private:
  double radius;
public:
  Circle(double radius);
  double area() override;
};

class Triangle : public Shape {
private:
  double base;
  double height;
public:
  Triangle(double base, double height);
  double area() override;
};
```

Now, let’s suppose that we want to add a new shape, such as a `Square`, to our hierarchy. One way to do this would be to modify the `Shape` class hierarchy by adding a new `Square` class. However, this would violate the OCP, as we would be modifying the existing code.

Instead, we can extend the `Shape` class hierarchy by creating a new class that inherits from the `Shape` class and implements the `area()` method. In this way, we are adding new functionality without modifying the existing code.

```cpp
class Square : public Shape {
private:
  double side;
public:
  Square(double side);
  double area() override;
};
```

Now, we can create objects of the `Square` class and calculate their areas using the `area()` method without modifying the existing code.

```cpp
Square square(5.0);
double squareArea = square.area(); // returns 25.0
```

By following the Open-Closed Principle, we can create code that is more maintainable, flexible, and easier to extend. This allows us to add new functionality to our code without modifying the existing code, which reduces the risk of introducing bugs and makes the code more modular.

### Liskov Substitution Principle (LSP)
The **Liskov Substitution Principle (LSP)** is one of the SOLID principles of object-oriented design. It states that objects of a superclass should be able to be replaced with objects of a subclass without affecting the correctness of the program. In other words, a subclass should be able to be substituted for its parent class without causing any errors or unexpected behavior.

In C++, LSP can be implemented by ensuring that subclasses adhere to the same interface and behavior as their parent class. This allows us to use a subclass object wherever we would normally use a parent class object.

Let’s consider an example of a `Bird` class hierarchy that includes different types of birds, such as `Eagle`, `Penguin`, and `Ostrich`. Each bird has a different ability to fly.
```cpp
class Bird {
public:
  virtual void fly() = 0;
};

class Eagle : public Bird {
public:
  void fly() override;
};

class Penguin : public Bird {
public:
  void fly() override;
};

class Ostrich : public Bird {
public:
  void fly() override;
};
```
Now, let’s suppose that we have a function that takes a `Bird` object and makes it fly.
```cpp
void makeBirdFly(Bird& bird) {
  bird.fly();
}
```
According to the LSP, we should be able to pass any `Bird` subclass object to this function without affecting the correctness of the program. For example, we should be able to pass an `Eagle` object, a `Penguin` object, or an `Ostrich` object to this function.

```cpp
Eagle eagle;
Penguin penguin;
Ostrich ostrich;

makeBirdFly(eagle); // okay, eagle can fly
makeBirdFly(penguin); // error, penguin can't fly
makeBirdFly(ostrich); // error, ostrich can't fly
```
As we can see, passing a `Penguin` or an `Ostrich` object to this function would result in an error because they cannot fly. Therefore, these classes do not adhere to the same behavior as their parent class, `Bird`, and violate the LSP.

By following the Liskov Substitution Principle, we can create code that is more modular and flexible. This allows us to use subclasses interchangeably with their parent class, which reduces the complexity of our code and makes it easier to maintain.


### Interface Segregation Principle (ISP)
The **Interface Segregation Principle (ISP)** is one of the SOLID principles of object-oriented design. It states that a client should not be forced to depend on interfaces that it does not use. In other words, a class should not have to implement methods that it does not need.

In C++, ISP can be implemented by breaking down larger interfaces into smaller, more specific interfaces. This allows clients to only depend on the specific methods they need, rather than being forced to implement unnecessary methods.

Let’s consider an example of a `Printer` class that can print documents in different formats, such as PDF, HTML, and plain text. We could define a single interface for this class that includes all possible methods, such as `printPDF()`, `printHTML()`, and `printPlainText()`.

```cpp
class Printer {
public:
  virtual void printPDF() = 0;
  virtual void printHTML() = 0;
  virtual void printPlainText() = 0;
};
```
However, this interface may not be suitable for all clients. For example, a client that only needs to print plain text documents may not want to implement the `printPDF()` and `printHTML()` methods.

To adhere to the ISP, we could break down the Printer interface into smaller interfaces that are specific to each document format.
```cpp
class Printable {
public:
  virtual void print() = 0;
};

class PDFPrintable : public Printable {
public:
  void print() override;
};

class HTMLPrintable : public Printable {
public:
  void print() override;
};

class PlainTextPrintable : public Printable {
public:
  void print() override;
};
```
Now, clients can depend on the specific interfaces they need. For example, a client that only needs to print plain text documents can depend on the `PlainTextPrintable` interface.
```cpp
class PlainTextPrinter {
public:
  void print(PlainTextPrintable& document) {
    document.print();
  }
};
```
By adhering to the Interface Segregation Principle, we can create more flexible and reusable code that is easier to maintain. Clients can depend on smaller interfaces that are specific to their needs, rather than being forced to implement unnecessary methods.

### Dependency Inversion Principle (DIP)
The **Dependency Inversion Principle (DIP)** is one of the SOLID principles of object-oriented design. It states that high-level modules should not depend on low-level modules. Both should depend on abstractions. Abstractions should not depend on details. Details should depend on abstractions.

In C++, DIP can be implemented by using interfaces or abstract classes to decouple high-level modules from low-level modules. This allows for more flexibility in the design, as different implementations of the same interface can be easily swapped out without affecting the overall structure of the program.

Let’s consider an example of a `Database` class that stores user information. We could define a concrete implementation of this class that depends on the `MySQLConnector` class.
```cpp
class MySQLConnector {
public:
  void connect();
  void query(const std::string& query);
};

class Database {
public:
  void addUser(const std::string& name, const std::string& email) {
    MySQLConnector connector;
    connector.connect();
    std::string query = "INSERT INTO users (name, email) VALUES ('" + name + "', '" + email + "')";
    connector.query(query);
  }
};
```
This implementation violates the Dependency Inversion Principle, as the `Database` class depends on the low-level `MySQLConnector` class. If we were to switch to a different database system, we would need to modify the `Database` class to use a different connector.

To adhere to the DIP, we could define an abstract interface for the database connector, and have the `Database` class depend on this interface instead of a concrete implementation.
```cpp
class IDatabaseConnector {
public:
  virtual void connect() = 0;
  virtual void query(const std::string& query) = 0;
};

class MySQLConnector : public IDatabaseConnector {
public:
  void connect() override;
  void query(const std::string& query) override;
};

class Database {
public:
  Database(IDatabaseConnector& connector) : connector_(connector) {}

  void addUser(const std::string& name, const std::string& email) {
    connector_.connect();
    std::string query = "INSERT INTO users (name, email) VALUES ('" + name + "', '" + email + "')";
    connector_.query(query);
  }

private:
  IDatabaseConnector& connector_;
};
```
Now, the `Database` class depends on the abstract `IDatabaseConnector` interface instead of a concrete implementation. We can create different implementations of the `IDatabaseConnector` interface for different database systems, and easily swap them out without modifying the `Database` class.

```cpp
class PostgreSQLConnector : public IDatabaseConnector {
public:
  void connect() override;
  void query(const std::string& query) override;
};

int main() {
  PostgreSQLConnector postgresConnector;
  Database db(postgresConnector);

  db.addUser("John Doe", "john.doe@example.com");
}
```
By adhering to the Dependency Inversion Principle, we can create more flexible and maintainable code that is easier to extend and modify. High-level modules depend on abstractions, not low-level details, which allows for easier substitution of implementations.

### Conclusion
In conclusion, SOLID principles provide a framework for writing clean and maintainable code. As a C++ developer, it’s important to understand each of these principles and how to apply them to your code. By implementing SOLID principles in your codebase, you can ensure that your software is easy to understand, modify, and test.
