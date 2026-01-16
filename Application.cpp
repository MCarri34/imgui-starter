#include "Application.h"
#include "Logger.h"
#include "imgui/imgui.h"

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
            // Initialize Logger
            Logger::GetInstance().Initialize();
            Logger::GetInstance().Log(LogLevel::Info, "Game Started Successfully.");
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();

            // safe ImGui log init
            static bool imguiLogInitialized = false;
            if (!imguiLogInitialized)
            {
                ImGui::LogToBuffer();
                imguiLogInitialized = true;
            }

            ImGui::Begin("ImGui Log Demo");
            ImGui::LogButtons();

            if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("Hello, world!");
                ImGui::LogFinish();
            }
            ImGui::End();

            ImGui::Begin("Game Control");

            if (ImGui::Button("Log Game Event"))
                Logger::GetInstance().Log(LogLevel::Info, "Player made a move.");

            ImGui::SameLine();
            if (ImGui::Button("Log Warning"))
                Logger::GetInstance().Log(LogLevel::Warning, "Invalid move attempted");

            ImGui::SameLine();
            if (ImGui::Button("Log Error"))
                Logger::GetInstance().Log(LogLevel::Error, "Game state corrupted");

            ImGui::End();

            //
            // Game Log window
            //
            ImGui::Begin("Game Log");

            if (ImGui::Button("Clear"))
                Logger::GetInstance().Clear();

            ImGui::Separator();

            ImGui::BeginChild("LogScroll", ImVec2(0, 0), true);
            ImGui::TextUnformatted(
                Logger::GetInstance().GetBuffer().c_str()
            );
            ImGui::EndChild();

            ImGui::End();

        }

        //
        // end turn is called by the game code at the end of each turn
        // this is where we check for a winner
        //
        void EndOfTurn() 
        {
            Logger::GetInstance().Log(LogLevel::Info, "End of turn reached");
        }
}
