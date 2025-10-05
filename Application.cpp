#include "Application.h"
#include "imgui/imgui.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;
//Big questions: how to keep the window in the viewport as you move it
//I think I'm using begin/end wrong to allow multiple windows in the same application that can still be edited
//how to create a test button to write to the log after starting the program

//logger functions
Logger::Logger() { //private constructor
    //cout << "DEBUG: Logger created." << endl;
    visible = false;
}

//initalize member variables
Logger* Logger::instance = nullptr;
bool Logger::writeToFile = false;
ofstream output;

//create using singleton
Logger* Logger::getInstance(){
    if (instance == nullptr)
            instance = new Logger();
        return instance;
}


//looking at specs don't need depth yet, so just set up the log how I want and write to it


void Logger::ShowLogWindow() {
        visible = true; //for future functionality
        ImGui::SetNextWindowPos(ImVec2(114, 148), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(477, 806), ImGuiCond_Appearing);
        ImGui::Begin("Log", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar);
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text] = ImVec4(0.89f, 0.52f, 0.12f, 1.00f); //orange, in practice just for title
        colors[ImGuiCol_Header] = ImVec4(0.75f, 0.58f, 0.15f, 1.00f); //faded orange for when log to file is selected
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.75f, 0.58f, 0.15f, 1.00f); //same faded orange
        colors[ImGuiCol_Border] = ImVec4(0.29f, 0.86f, 0.12f, 0.5f); //green, half opacity
        colors[ImGuiCol_TitleBg] = ImVec4(0.29f, 0.86f, 0.12f, 1.00f); //green
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.86f, 0.12f, 1.00f); //green
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f); //pure black
        
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowBorderSize = 5.0f;     // Border size for windows
        style.FrameBorderSize = 1.0f; //put borders around the different elements of the window

        //menu bar for write to file option
        ImGui::BeginMenuBar();
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(74, 219, 31, 255)); //set text in menu to green
        if (ImGui::MenuItem("Write to file", NULL, &writeToFile)) {
            if(writeToFile) { //warning whenever this is checked it overwrites the existing file
                output.open("GameLog.txt");
                if( !output.is_open() ){
                    cout << "Unable to open file to write log" << endl;
                } else {
                    cout << "GameLog.txt succesfully created" << endl;
                }

                //heads each file with date and time
                time_t now = time(0);
                char* readableTime = ctime(&now);
                string readableTimeS = readableTime; //convert result to string
                output << "Game log created at " << readableTimeS << endl;
            } else { //when it is unchecked, as in it was initally checked
                output.close(); //hopefully advanced stuff will close the file if I just close the program
            }
        }
        ImGui::PopStyleColor();
        ImGui::EndMenuBar();


        
        
    }
//need to test if scrolling is automatic feature of the lib
//Log info is for information presented without flavor
void Logger::LogInfo(string message) {
    string prefix = "*"; //what messages should be prefixed with, to make it easy to change
    string fullMessage = prefix + message;
    const char* cMessage = fullMessage.c_str();
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255)); //set color to white
    ImGui::TextWrapped(cMessage);
    ImGui::PopStyleColor(); //revert color change

    if(writeToFile) {
        output << "[INFO] " << fullMessage << endl;
    }
}
void Logger::LogGameEvent(string message) {
    //Log game event is for the AI "speaking"
    string prefix = "*"; //what messages should be prefixed with, to make it easy to change
    string fullMessage = prefix + message;
    const char* cMessage = fullMessage.c_str();
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(227, 133, 31, 255)); //set color to orange
    ImGui::TextWrapped(cMessage);
    ImGui::PopStyleColor(); //revert color change

    if(writeToFile) {
        output << "[EVENT] " << fullMessage << endl;
    }
}

//Hiding log window functionality disabled
//void Logger::ToggleLogWindow() {}
//bool Logger::IsLogWindowVisible() {
    //return visible;}

//this function is used to open and set up the GameLog.txt file without using the button normally used to toggle it. When this
//method is executed, the "Write to File" button shouldn't be touched, because I have no idea what it will do.
void fileHandler(Logger* logger) {
    logger->writeToFile = true;
    logger->output.open("GameLog.txt");
                if( !(logger->output.is_open()) ){
                    cout << "Unable to open file to write log" << endl;
                }

                //heads each file with date and time
                time_t now = time(0);
                char* readableTime = ctime(&now);
                string readableTimeS = readableTime; //convert result to string
                logger->output << "Game log created at " << readableTimeS << endl;
}

//changes to the provided code detailed in the README.
namespace ClassGame {
        //
        // our global variables
        //

        //
        // game starting point
        // this is called by the main render loop in main.cpp
        //
        
        void GameStartUp() 
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
            ImGui::DockSpaceOverViewport(); //still need to figure out how to make docking not a thing
            ImGui::ShowDemoWindow();
            Logger* logger = Logger::getInstance();
            fileHandler(logger); //for testing writing log to file. If uncommented, do not touch the button that should toggle this functionality
            logger->ShowLogWindow();
            logger->LogInfo("This is a message.");
            //loop a bunch of messages to test scroll feature
            for(int i = 0; i < 200; i++) {
                string num = to_string(i);
                logger->LogInfo("this is message num " + num + ".");

            }
            logger->LogGameEvent("Would you like to play a game?");
            ImGui::End(); //might have some problems when I want to create multiple windows while still allowing the log to be updated
            //but that is a future problem, and I'm sure I'll get more instruction on how to make updatable windows
            logger->output.close(); //as part of the fileHanlder workaround.
            
        }
 
        //
        // end turn is called by the game code at the end of each turn
        // this is where we check for a winner
        //
        void EndOfTurn() 
        {
        }
}
