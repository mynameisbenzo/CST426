//
//  main.cpp
//  Prototype
//
//  Created by Lorenzo Hernandez III on 9/21/17.
//  Copyright © 2017 Lorenzo Hernandez III. All rights reserved.
//
/*
                //////////////  NOTES   /////////////
    So far as I can tell through internet resources, the usage of the new
    operator is still abundant.  Originally, I was using a copy constructor,
    but realized I was just coding clone() wrong.  It kept return the same
    object instead of a copied one.
*/

#include <iostream>
#include <vector>

using namespace std;

enum CLONE_STATES{
    FIRST_CLONE_STAGE, SECOND_CLONE_STAGE, FINAL_CLONE_STAGE
};

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

//holds objects to be cloned in first cloning stage
vector<AbstractAnimal*> prototypes = {
    new Dog, new Cat, new Snake
};

//just wanted to get rid of some lines [Will print out animal list]
void printAnimals(vector<AbstractAnimal*> animals, unsigned long size){
    for(int i = 0; i < size; i++){
        cout << i << " " << animals[i]->getName() << " ";
        cout << animals[i]->getAge() << " " << animals[i]->getWeight() << " ";
        animals[i]->speak();
    }
}

int main() {
    vector<AbstractAnimal*> myAnimals;
    int choice, clone_stage = 0;
    
    while(true){
        switch(clone_stage){
            case FIRST_CLONE_STAGE:
                //first we test the cloning from the prototype set
                //give user selection and clone from there
                cout << "Select animal to clone: \n\n";
                printAnimals(prototypes, prototypes.size());
                cin >> choice;
                
                if(choice < 0 || choice > 2){
                    clone_stage++;
                }else{
                    myAnimals.push_back(prototypes[choice]->clone());
                }
                break;
            case SECOND_CLONE_STAGE:
                //now we test clone from our cloned animals
                //and allow tweaks to the cloned animals
                cout << "Here are your cloned animals: \n\n";
                printAnimals(myAnimals, myAnimals.size());
                cout << "\nWould you like to keep cloning? If so, then select one your animals to clone: ";
                cin >> choice;
                if(choice < 0 || choice > myAnimals.size() - 1){
                    clone_stage++;
                }else{
                    cout << "Would you like to change the animal's properties?\n0:NO\n1:YES\n";
                    AbstractAnimal* a = myAnimals[choice]->clone();
                    cin >> choice;
                    if(choice == 1) a->change();
                    myAnimals.push_back(a);
                }
                break;
            case FINAL_CLONE_STAGE:
                for(int i = 0; i < myAnimals.size(); i++){
                    delete myAnimals[i];
                }
                return 0;
            default:
                cout << "ERROR: CLONE STATE UNRECOGNIZED\n";
                return 1;
        }
    }
}
