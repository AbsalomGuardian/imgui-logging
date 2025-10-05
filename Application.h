#pragma once
#include <iostream>
#include <fstream>
using namespace std;

namespace ClassGame {
    void GameStartUp();
    void RenderGame();
    void EndOfTurn();
    
    // Logging window management
    
}


class Logger {
    private: //singleton stuff
        //using geeks4geeks guide on singletons
         static Logger* instance;
        // Private constructor
        Logger();
        // Delete copy constructor and assignment
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        bool visible; //initalizes as false. Private variable so that it can't be changed without the visibility actually changing
        
        
    public:
        static bool writeToFile; //public for fileHandler fuction
        ofstream output;
       //singleton "construct"
        static Logger* getInstance();
        
        void ShowLogWindow(); //create the window
        //log visibility, feautre disabled
        //void ToggleLogWindow();
        //bool IsLogWindowVisible();
        
        //from application.cpp
        void LogInfo(string message); //standard info message
        void LogGameEvent(string message); //flavor message
};