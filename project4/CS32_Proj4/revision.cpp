#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

bool getInt(std::istream& inf, int& n) {
    char ch;
    if (!inf.get(ch) || !isascii(ch) || !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(std::istream& inf, char& cmd, char& delim, int& length, int& offset) {
    if (!inf.get(cmd)) {
        cmd = 'x';  // signals end of file
        return true;
    }
    switch (cmd) {
    case '+':
        return inf.get(delim).good();
    case '#':
    {
        char ch;
        return getInt(inf, offset) && inf.get(ch) && ch == ',' && getInt(inf, length);
    }
    case '\r':
    case '\n':
        return true;
    }
    return false;
}

bool revise(std::istream& fold, std::istream& frevision, std::ostream& fnew) {
    // Read the entire contents of the old file into a string
    std::string oldFileContent((std::istreambuf_iterator<char>(fold)), std::istreambuf_iterator<char>());

    char cmd;        // Command character ('+', '#', etc.)
    char delimiter;  // Delimiter for the add command
    int length;      // Length of the sequence to copy
    int offset;      // Offset from where to start copying in the old file

    // Read and process each command from the revision file
    while (getCommand(frevision, cmd, delimiter, length, offset)) {
        if (cmd == 'x')
            break; // End of file or command sequence

        switch (cmd) {
        case '+':
        {
            // Add instruction: add text to the new file
            std::string addedText;
            if (!std::getline(frevision, addedText, delimiter)) {
                return false; // Return false if reading the added text fails
            }
            fnew << addedText; // Write the added text to the new file
        }
        break;
        case '#':
            // Copy instruction: copy text from the old file to the new file
            if (offset < 0 || length < 0 || offset + length > static_cast<int>(oldFileContent.size())) {
                return false; // Return false if the offset or length is invalid
            }
            fnew << oldFileContent.substr(offset, length); // Write the copied text to the new file
            break;
        case '\r':
        case '\n':
            break; // Ignore carriage return and newline characters
        default:
            return false; // Return false for any unrecognized command
        }
    }

    return true; // Successfully applied all revision instructions
}