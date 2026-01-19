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
            Logger::GetInstance().Initialize("GameLog.txt");
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();

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
            {
                Logger::GetInstance().Clear();
            }
            ImGui::SameLine();

            static int levelIndex = 0;
            const char* levels[] = { "Info", "Warning", "Error" };

            LogLevel currentLevel = Logger::GetInstance().GetConsoleLevel();
            levelIndex = (currentLevel == LogLevel::Info) ? 0 :
                        (currentLevel == LogLevel::Warning) ? 1 : 2;
            if (ImGui::Combo("Log Level", &levelIndex, levels, IM_ARRAYSIZE(levels)))
            {
                Logger::GetInstance().SetConsoleLevel(
                    levelIndex == 0 ? LogLevel::Info :
                    levelIndex == 1 ? LogLevel::Warning :
                    LogLevel::Error);
            }

            ImGui::Separator();
                
            ImGui::BeginChild("LogScroll", ImVec2(0, 0), true);

            LogLevel minLevel = Logger::GetInstance().GetConsoleLevel();
            for (const auto& entry : Logger::GetInstance().GetEntries())
                {
                    if (entry.level < minLevel)
                        continue;

                    ImGui::TextUnformatted(entry.text.c_str());
                }
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
