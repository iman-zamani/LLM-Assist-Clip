# LLM-Assist-Clip

## Overview
LLM-Assist-Clip is a utility designed to simplify the process of preparing and transferring project files to large language models (LLMs). This tool automates the task of copying file contents to your clipboard in a structured format, making it easy for AI to parse and understand the code. It’s particularly useful for developers working with AI platforms that require manual input of code snippets or entire files.

## Features
- **Selective Recursive File Search**: Allows specification of file types for recursive directory search.
- **Clipboard Integration**: Formats and copies the content and names of files directly to your clipboard, ready to be pasted into any AI tool or text field.
- **Cross-Platform Compatibility**: Tested on Linux; expected to work on macOS and Windows as well.

## External Libraries Used
- **[Clip](https://github.com/dacap/clip)**: A cross-platform library used for clipboard operations.

## Usage
To use LLM-Assist-Clip, compile and run the program from your terminal or command prompt with file extensions as arguments. The `-r` flag can be used to specify that subsequent file types should be searched for recursively:

### Command Syntax
```bash
./LAC [options] <file extensions>
```

### Options
- `-r`: Apply recursive search to file extensions listed after this flag.

### Examples
- Search for `.cpp` and `.h` files non-recursively, and for `.txt` and `.md` files recursively:
  ```bash
  ./LAC .cpp .h -r .txt .md
  ```
- Search for all specified file types recursively:
  ```bash
  ./LAC -r .cpp .h .txt
  ```

### Output Example
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

4. **Run the application** by specifying the types of files you want to process, using the `-r` flag as needed for recursive search.

## Simple and Effective
This tool is crafted to minimize the typically involved friction in preparing and analyzing code with AI tools, providing a straightforward solution to meet essential needs without complicating the user experience.

