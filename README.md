# ESP32-S3 Robot Project

This project is an exploration of robotics and AI using the ESP32-S3 microcontroller.  
It features multiple servos for walking and dancing and is integrated with a Large Language Model (LLM) for speech interaction.  
The goal is to learn and have fun while experimenting with robotics, programming, and AI.

## Features
- **ESP32-S3 Microcontroller**: Powers the robot and controls its movements.  
- **Multiple Servos**: Enables walking and dancing motions.  
- **LLM Integration**: Allows the robot to interact using speech.  
- **Voice Recording**: Captures audio input using a microphone module.  
- **Audio Playback**: Plays back speech output via an audio amplifier and speaker.  
- **Touch Sensor Interaction**: Triggers actions like walking, dancing, or recording.  
- **Wake Word Detection (Planned)**: Enables hands-free activation for voice recording.  
- **LED Feedback**: Indicates robot status (e.g., walking, dancing, idle).  
- **Modular Code**: Easy to extend and customize for new functionalities.  

## Getting Started

### Prerequisites
- **ESP32-S3 development board**  
- **ESP32-S3 Expansion Board**  
- **PlatformIO** (for development)  
- **4x Servo motors (SG90-180degree)** (2x for legs, 2x for foots) 
- **SD card module** (for storing recorded audio)  
- **Microphone module (INMP441)** (for voice recording)  
- **Audio amplifier (MAX98357) and Mini Speaker** (for playback)  
- **Touch sensor (TTP223)** (for interaction)
- **Some Jumper wires** (for connecting the components)
- **Battery** (for powering the robot)
- **Basic knowledge of C++ and the Arduino framework**

### Installation
1. Clone the repository:  
`$ git clone https://github.com/gadingnst/alecto-robot.git`  

2. Open the project in PlatformIO.  

3. Connect your ESP32-S3 and upload the code.  

## Usage
1. Power on the robot.  
2. Use the serial monitor to interact with the robot.  
3. Call functions like `walkForward()` or `moonwalk()` to see the robot in action.  
4. Use the touch sensor to trigger specific actions.  
5. Speak to the robot and listen to its response (once LLM integration is complete).  

## Code Structure
- `main.cpp`: The main file that initializes the robot and runs the loop.  
- `Robot.h` and `Robot.cpp`: Contain the `Robot` class with methods for controlling the servos.  
- `platformio.ini`: Configuration file for PlatformIO.  

## Work in Progress (WIP)

### Integrated Components
- [x] **Servo Motors**: Integrated and functional for walking and dancing.  
- [x] **Touch Sensor**: Integrated and functional for detecting touch input.  

### Tasks to Work On
- [ ] **SD Card Module Integration**: Enable audio data storage for voice recording.  
- [ ] **Microphone Module (INMP441) Integration**: Implement voice recording functionality.  
- [ ] **Audio Amplifier (MAX98357) and Speaker Integration**: Enable audio playback.  
- [ ] **Use Touch Sensor for Recording State (Temporary)**: Utilize the touch sensor to start/stop recording.  
- [ ] **LLM API Integration with Speech-to-Speech I/O**: Process both input and output as spoken language.  
- [ ] **Implement Audio Playback Flow**: Manage the processing and playback of speech output.  
- [ ] **Wake Word Integration for Recording State**: Implement wake word detection to trigger voice recording.
- [ ] **Battery Integration**: Implement a rechargeable battery system for wireless operation.
- [ ] **Improve Walking Algorithm**: Optimize the walking motion for smoother and more natural movement.  
- [ ] **Add More Dance Moves**: Implement additional dance routines (e.g., spin, shuffle).  
- [ ] **Add LED Feedback**: Include LEDs to indicate robot status (e.g., walking, dancing, idle).  

---

2025, Made with ❤️ by Sutan Gading Fadhillah Nasution
