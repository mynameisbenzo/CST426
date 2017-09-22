//
//  main.cpp
//  GameLoop
//
//  Created by Lorenzo Hernandez III on 9/22/17.
//  Copyright © 2017 Lorenzo Hernandez III. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <list>

using namespace std;


enum STATE {
    WIN, LOSE, NOTHING_YET, OUT_OF_BOUNDS
};

class Player;
class View;
class Scene;
class GetInput;

//view
class View{
private:
    GetInput* controller;
public:
    virtual void Update(int data[]) = 0;
    virtual void attachController(GetInput * c){
        controller = c;
    }
    virtual void acceptInput();
};
class GUI : public View{
private:
    char GUI[5] = {'H','P',':',' ','5'};
public:
    virtual void Update(int data[]){
        GUI[4] = data[4];
        getGUI();
    }
    
    //get
    void getGUI(){
        for(int x = 0; x< 5; x++){
            cout << GUI[x];
        }
        cout << endl;
    }
};
class Scene : public View{
private:
    char scene[5][5] = {
        {'-','-','-','-','-'},
        {'-','-','-','-','-'},
        {'-','-','-','-','-'},
        {'-','-','-','-','-'},
        {'-','-','-','-','G'}
    };
    int state = 2;
    
    
public:
    Scene(){
        scene[0][0] = 'P';
    }
    virtual void Update(int data[]){
        if(scene[data[0]][data[1]] == 'G'){
            state = 0;
        }else{
            scene[data[0]][data[1]] = 'P';
            scene[data[2]][data[3]] = '-';
        }
        getBoard();
    }
    
    //get
    void getBoard(){
        for(int x = 0; x < 5; x++){
            for(int y = 0; y < 5; y++){
                cout << scene[x][y];
            }
            cout << endl;
        }
    }
    int getState(){return state;}
};

//Model
class Player{
private:
    list<View*> scenes;
    int data[5] = {0,0,0,0,5};
public:
    void attachView(View* s){
        scenes.push_front(s);
    }
    void detachView(View* s){
        scenes.remove(s);
    }
    void notifyViews(){
        for(list<View*>::iterator it = scenes.begin(); it != scenes.end(); it++){
            //send data to views to update board
            (*it)->Update(data);
        }
    }
    
    //adjust data containing coordinates
    void setState(char action){
        switch(action){
            case 'u':
                if(data[0] > 0){
                    data[2] = data[0];
                    data[3] = data[1];
                    data[0]--;
                }
                break;
            case 'd':
                if(data[0] < 4){
                    data[2] = data[0];
                    data[3] = data[1];
                    data[0]++;
                }
                break;
            case 'l':
                if(data[1] > 0){
                    data[3] = data[1];
                    data[2] = data[0];
                    data[1]--;
                }
                break;
            case 'r':
                if(data[1] < 4){
                    data[3] = data[1];
                    data[2] = data[0];
                    data[1]++;
                }
                break;
            default:
                cout << "Not sure what you're telling me to do.\n";
                break;
        }
        notifyViews();
    }
};

//controller
class GetInput{
private:
    Player *player;
    int action;
public:
    void setModel(Player *p){
        player = p;
    }
    void processInput(char input);
};

//set input to player to be interpreted
void GetInput::processInput(char input){
    player->setState(input);
}

//retrieve initiate input and send to controller
void View::acceptInput(){
    char input;
    cin >> input;
    controller->processInput(input);
}

//contains gameLoop in its entirety
//will use for testing
class GameLoop{
private:
    bool running;
    int checkState;
public:
    GameLoop(){}
    void run(){
        running = true;
        Player* p   = new Player();
        GUI* g      = new GUI();
        Scene* s    = new Scene();
        GetInput* gi= new GetInput();
        
        gi->setModel(p);
        p->attachView(s);
        p->attachView(g);
        g->attachController(gi);
        s->attachController(gi);
        
        
        g->getGUI();
        s->getBoard();
        
        //gameLoop
        while(true){
            cout << "Action? \nu=up\nd=down\nl=left\nr=right\n";
            g->acceptInput();
            if(s->getState() == 0){
                cout << "You win!\n";
                running = false;
                break;
            }
        }
        checkState = s->getState();
    }
    
    int getCheckState(){return checkState;}
    bool isRunning(){return running;}
};

//test will figure out if gameLoop is still running
//when game loop should not be running
class Test{
public:
    void startTest(){
        GameLoop *g = new GameLoop();
        g->run();
        if((g->getCheckState() == 0 || g->getCheckState() == 1) && g->isRunning()){
            cout << "Failure\n";
        }else{
            cout << "Success\n";
        }
    }
};

int main() {
    
    Test t;
    t.startTest();
    return 0;
}
