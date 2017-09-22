//
//  main.cpp
//  Prototype
//
//  Created by Lorenzo Hernandez III on 9/21/17.
//  Copyright © 2017 Lorenzo Hernandez III. All rights reserved.
//

#include <vector>
#include "Tests.h"

enum CLONE_STATES{
    FIRST_CLONE_STAGE, SECOND_CLONE_STAGE, FINAL_CLONE_STAGE, RESET_STAGE
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
    
    RunTest* rt = new RunTest();
    rt->currentTest();
    rt->setTestType(new Test2);
    rt->currentTest();
    
    while(true){
        switch(clone_stage){
            case FIRST_CLONE_STAGE:
                //first we test the cloning from the prototype set
                //give user selection and clone from there
                cout << "Select animal to clone: \n\n";
                cout << "-1 starts you from scratch and anything out of range moves you to the next step:\n\n";
                printAnimals(prototypes, prototypes.size());
                cin >> choice;
                
                //start over
                if(choice == -1){
                    clone_stage = 3;
                    break;
                }
                
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
                
                //start over
                if(choice == -1){
                    clone_stage = 3;
                    break;
                }
                
                if(choice < 0 || choice > myAnimals.size() - 1){
                    clone_stage++;
                }else{
                    cout << "Would you like to change the animal's properties?\n0:NO\n1:YES\n";
                    AbstractAnimal* a = myAnimals[choice]->clone();
                    cin >> choice;
                    
                    //start over
                    if(choice == -1){
                        clone_stage = 3;
                        break;
                    }
                    
                    if(choice == 1) a->change();
                    myAnimals.push_back(a);
                }
                break;
            case FINAL_CLONE_STAGE:
                for(int i = 0; i< myAnimals.size(); i++){
                    delete myAnimals[i];
                }
                return 0;
            case RESET_STAGE:
                clone_stage = 0;
                myAnimals.clear();
                break;
            default:
                cout << "ERROR: CLONE STATE UNRECOGNIZED\n";
                return 1;
        }
    }
}
