//
//  Tests.h
//  Prototype
//
//  Created by Lorenzo Hernandez III on 9/22/17.
//  Copyright © 2017 Lorenzo Hernandez III. All rights reserved.
//

#ifndef Tests_h
#define Tests_h

#include "AbstractAnimal.h"

class TestType{
public:
    virtual void runTest() = 0;
    virtual ~TestType(){};
};

//testing dog clone creation
class Test1 : public TestType{
public:
    void runTest(){
        Dog *d = new Dog;
        AbstractAnimal *c = d->clone();
        
        if(d->getName() == c->getName() && d->getAge() == c->getAge() && d->getWeight() == c->getWeight())
            cout << "Test1: Success.\n";
        else
            cout << "Test1: Failure. \n";
    }
    ~Test1(){}
};
//testing cat clone creation plus clone of creation
class Test2: public TestType{
    void runTest(){
        Cat *c = new Cat;
        AbstractAnimal *ca = c->clone();
        ca->change("George", 40, 12.8, "I am a cat.  Trust me.");
        AbstractAnimal *cat = ca->clone();
        if(c->getName() != ca->getName() && ca->getAge() != c->getAge() && ca->getWeight() != c->getWeight())
            cout << "Test2pt1: Success.\n";
        else
            cout << "Test2pt1: Failure. \n";
        if(cat->getName() == ca->getName() && ca->getAge() == cat->getAge() && ca->getWeight() == cat->getWeight())
            cout << "Test2pt1: Success.\n";
        else
            cout << "Test2pt1: Failure. \n";
    }
    ~Test2(){}
};

//using strategy pattern
class RunTest{
    TestType * m_testType;
public:
    RunTest(){
        m_testType = new Test1();
    }
    void setTestType(TestType * t ){
        m_testType = t;
    }
    void currentTest(){
        m_testType->runTest();
    }
    ~RunTest(){
        delete m_testType;
    }
};

#endif /* Tests_h */
