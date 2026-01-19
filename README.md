# imgui-starter

Using the provided code provided here you have a base Dear IMGUI project for Windows and macOS. There is a basic CMakefile in this project that includes the necessary files to create an application that brings up just a basic screen.

You must add a logging system to this code that you will be using THROUGHOUT the quarter. This logging system should do two things.

It should be able to log to a Dear IMGUI debug console
It should also log its output to a file.

For the submission, make a branch of this repo and submit a new GitHub URL

## Approach in Writing Code
Before writing any code, I asked the instructor whether the original Application.cpp were meant to stay mostly unchanged and in return, I got a full explanation on how we were supposed to set up the code. I built a simple singleton logging system that writes to both a Dear ImGui game log window and a text file so it can be reused throughout the quarter. This project was made on Windows.
