
# Advanced Scientific Calculator (C++)

A command-line scientific calculator built in C++ with full expression parsing, scientific functions, persistent history, and robust error handling.

## Features
- Expression parsing for complete formulas, e.g., `2 + 3 * 4 / (5 - 1)`
- Correct order of operations (BODMAS/PEMDAS)
- Scientific functions:
  - `sin(x)`, `cos(x)`, `tan(x)` in degrees
  - `sqrt(x)` square root
  - `log(x)` natural logarithm
  - `log10(x)` base-10 logarithm
- Power operator: `a ^ b`
- Persistent history saved to `history.txt` and auto-loaded on startup
- Error handling for invalid input, division by zero, and domain errors

## Folder Structure
- `src/`
  - `main.cpp`
- `assets/`
  - `Main-interface.png`
  - `Operations.png`
  - `Power-Operations.png`
  - `History.png`
  - `Error-Handling.png`
- `data/`
  - `history.txt`

Tip: Keep screenshots in `assets/` and the history file in `data/`.

## Screenshots

### Main Interface
Shows the welcome screen, supported operators, and functions.  
![Main Interface](assets/Main-interface.png
Demonstrates simple operations and reusing the last result.  
![Operations](assets Operation
Illustrates handling of the `^` operator.  
![Power Operations](assets/Power-Operations Feature
Shows saving to `data/history.txt` and viewing with the `history` command.  
![History](assets/History Handling
Examples: divide by zero, `sqrt(-1)`, etc., with clear messages.  
![Error Handling](assets/Error-Handling.png Run

Requirements:
- C++17 compiler (g++/clang++). On Windows, use MinGW-w64.

Compile:
- Windows (MinGW):
  - `g++ -std=c++17 -O2 -Wall -Wextra -municode -o calc.exe src/main.cpp -mconsole`
- Linux/macOS:
  - `g++ -std=c++17 -O2 -Wall -Wextra -o calc src/main.cpp`

Run:
- Windows: `.\calc.exe`
- Linux/macOS: `./calc`

Note: Ensure the app can write to `data/history.txt`. If using an IDE, set the working directory to the project root.

## Usage
- Enter expressions:
  - `2 + 3 * 4`
  - `(5 + 7) / 3`
  - `2 ^ 8`
- Scientific functions (degrees for trig):
  - `sin(30)`, `cos(60)`, `tan(45)`
  - `sqrt(16)`, `log(2.7182818)`, `log10(1000)`
- History:
  - Type `history`
- Use last answer:
  - `5 * ans`

Exit with `exit` or `quit`.

## Error Handling
Descriptive messages for:
- Invalid syntax or unknown tokens
- Division by zero
- Domain errors like `sqrt(-1)`, `log(0)`, `tan(90)`
- Mismatched parentheses

## Implementation Notes
- Tokenizer + shunting-yard to convert infix to postfix
- Postfix evaluation with a stack
- Trig inputs converted from degrees to radians internally
- History appended to `data/history.txt` and loaded at startup

## Contributing
- Fork and create a feature branch
- Follow consistent C++17 style; add tests when feasible
- Open a PR with a clear description and updated screenshots as needed

## License
MIT License. See `LICENSE` for details.

[1] https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/attachments/images/89182813/bb07ec14-69cd-4150-ace3-94c561846d54/image.jpg