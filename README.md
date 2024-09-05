# LLM-Assist-Clip

## Overview
LLM-Assist-Clip is a simple utility designed to streamline the process of preparing and transferring project files to large language models (LLMs). This tool automates the task of copying file contents to your clipboard in a structured format, making it straightforward for AI to parse and understand the code. It’s especially useful for developers working with AI platforms that require code snippets or entire files to be inputted manually.

## Features
- **Recursive File Search**: Automatically identifies and selects files based on specified types within all directory levels.
- **Clipboard Integration**: Formats and copies the content and names of files directly to your clipboard, ready to be pasted into any AI tool or text field.
- **Cross-Platform**: Tested on Linux; expected to work on macOS and Windows as well.

## External Libraries Used
- **[Clip](https://github.com/dacap/clip)**: Used for cross-platform clipboard operations.

  
## Usage
To operate LLM-Assist-Clip, follow these steps:
1. **Compile the program**:
   Navigate to your command line interface and compile the program using commands suited to your development environment.
   
2. **Execute**:
   Run the program from your terminal or command prompt with the file extensions of interest as arguments. For example:
   ```bash
   ./LAC .cpp .h
   ```
   This command compiles all `.cpp` and `.h` files in the current directory and subdirectories, formatting their paths and contents neatly for easy AI consumption.

Example output:
```
filename1.cpp:
<content of filename1.cpp>

filename2.h:
<content of filename2.h>

...
```

## Building the Project
1. **Clone and navigate to the project**:
   ```bash
   git clone https://github.com/iman-zamani/LLM-Assist-Clip.git
   cd LLM-Assist-Clip
   ```

2. **Initialize required submodules**:
   ```bash
   git submodule update --init --recursive
   ```

3. **Compile the application**:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

4. **Run the application** by specifying the types of files you want to process.

## Simple and Effective
This tool was created with simplicity in mind, to reduce the friction typically involved in preparing and analyzing code with AI tools. It's a straightforward solution that fulfills an essential need without complicating the user experience.
