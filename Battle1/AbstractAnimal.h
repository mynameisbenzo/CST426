//
//  AbstractAnimal.h
//  Prototype
//
//  Created by Lorenzo Hernandez III on 9/22/17.
//  Copyright © 2017 Lorenzo Hernandez III. All rights reserved.
//


/*
 //////////////  NOTES   /////////////
 So far as I can tell through internet resources, the usage of the new
 operator is still abundant.  Originally, I was using a copy constructor,
 but realized I was just coding clone() wrong.  It kept return the same
 object instead of a copied one.
 */

#ifndef AbstractAnimal_h
#define AbstractAnimal_h


#include <iostream>

using namespace std;
//class being used as basis for all following classes
class AbstractAnimal{
private:
    string name;
    string sayThis = "";
    int age;
    float weight;
public:
    virtual AbstractAnimal* clone() = 0;    //necessary for Prototype Design pattern
    virtual void speak() = 0;
    
    //function to be used to change clones if needed
    //user input change
    void change(){
        string n, s;
        int a;
        float w;
        cout << "New name: ";
        cin.ignore();
        getline(cin, n);
        cout << n << endl;
        setName(n);
        cout << "New age: ";
        cin >> a;
        setAge(a);
        cout << "New weight: ";
        cin >> w;
        setWeight(w);
        cin.ignore();
        cout << "...but what's its catchphrase?: ";
        getline(cin, s);
        setSayThis(s);
    }
    //hard coded change
    void change(string n, int a, float w, string s){
        setName(n);
        setAge(a);
        setWeight(w);
        setSayThis(s);
    }
    
    virtual ~AbstractAnimal(){}
    
    //get
    string getName() const {return name;}
    int getAge()const {return age;}
    int getWeight()const {return weight;}
    string getSayThis()const {return sayThis;}
    
    //set
    void setName(string n){name = n;}
    void setAge(int a){age = a;}
    void setWeight(float w){weight = w;}
    void setSayThis(string s){sayThis = s;}
};

//creating subclass of Animal
//clone() is the important function
//creating a deep clone
class Dog : public AbstractAnimal{
public:
    Dog(){
        setName("Pupper");
        setAge(1);
        setWeight(10.5);
    }
    void speak(){
        if(getSayThis().empty()){
            cout << "Woof. I'm a dog.\n";
            return;
        }
        cout << getSayThis() << endl;
    }
    AbstractAnimal* clone(){
        return new Dog(*this);
    }
    
    ~Dog(){
        cout << "ARF!!!\n";
    }
};
class Cat : public AbstractAnimal{
public:
    Cat(){
        setName("Kitty");
        setAge(1);
        setWeight(4.5);
    }
    void speak(){
        if(getSayThis().empty()){
            cout << "Meow. I'm a cat.\n";
            return;
        }
        cout << getSayThis() << endl;
    }
    AbstractAnimal* clone(){
        return new Cat(*this);
    }
    ~Cat(){
        cout << "MRARRR!!!\n";
    }
};
class Snake : public AbstractAnimal{
public:
    Snake(){
        setName("Mr. Hiss");
        setAge(1);
        setWeight(2.0);
    }
    void speak(){
        if(getSayThis().empty()){
            cout << "Hsssssssssss. I'm a sssssssnake.\n";
            return;
        }
        cout << getSayThis() << endl;
    }
    
    AbstractAnimal* clone(){
        return new Snake(*this);
    }
    ~Snake(){
        cout << "I am a snake and you have destroyed me.  I can't believe you've done this.\n";
    }
};

#endif /* AbstractAnimal_h */
