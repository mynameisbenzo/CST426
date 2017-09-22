//
//  main.cpp
//  Prototype
//
//  Created by Lorenzo Hernandez III on 9/21/17.
//  Copyright © 2017 Lorenzo Hernandez III. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class AbstractAnimal{
private:
    string name;
    int age;
    float weight;
public:
    virtual AbstractAnimal* clone() = 0;
    virtual void speak() = 0;
    void change(){
        string n;
        int a;
        float w;
        cout << "New name: ";
        cin >> n;
        setName(n);
        cout << "New age: ";
        cin >> a;
        setAge(a);
        cout << "New weight: ";
        cin >> w;
        setWeight(w);
    }
    
    //get
    string getName(){return name;}
    int getAge(){return age;}
    int getWeight(){return weight;}
    
    //set
    void setName(string n){name = n;}
    void setAge(int a){age = a;}
    void setWeight(float w){weight = w;}
};

class Animal : public AbstractAnimal{
public:
    AbstractAnimal* clone(){return new Animal;};
    void speak(){};
};

class Dog : public Animal{
public:
    Animal* clone(){return new Dog;}
    void speak(){
        cout << "Woof. I'm a dog.\n";
    }
};
class Cat : public Animal{
    Animal* clone(){return new Cat;}
    void speak(){
        cout << "Meow. I'm a cat.\n";
    }
};
class Snake : public Animal{
    Animal* clone(){return new Snake;}
    void speak(){
        cout << "Hsssssssssss. I'm a sssssssnake.\n";
    }
};

AbstractAnimal* prototypes[] = {
    new Dog, new Cat, new Snake
};

int main() {
    vector<AbstractAnimal*> myAnimals;
    int choice;
    
    while(true){
        cout << "Select animal to clone: \n\n";
        for(int i = 0; i < 3; i++){
            cout << i << " " << prototypes[i]->getName() << " ";
            prototypes[i]->speak();
        }
        cin >> choice;
        
        if(choice < 0 || choice > 2)
            break;
        else{
            myAnimals.push_back(prototypes[choice]->clone());
        }
    }
    
    for(int i = 0; i < myAnimals.size(); i++){
        cout << i << " " << myAnimals[i]->getName() << " ";
        myAnimals[i]->speak();
    }
    
    return 0;
}
