#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "hash.h"
const int N = 8; // Length of sequences to be hashed, adjusted for efficiency

void createRevision(std::istream& fold, std::istream& fnew, std::ostream& frevision) {
    // Read the entire contents of the old file into a string
    std::string oldFileContent;
    std::string newFileContent;
    char temp;

    // Read characters from the old file and append them to oldFileContent
    while (fold.get(temp))
        oldFileContent += temp;

    // Read characters from the new file and append them to newFileContent
    while (fnew.get(temp))
        newFileContent += temp;

    // Create the hash table and insert N-character sequences from the old file
    HashTable hashTable(100003);
    for (unsigned int i = 0; i + N <= oldFileContent.size(); i++) {
        hashTable.insert(oldFileContent.substr(i, N), i);
    }

    // Process the new file and create revision instructions
    unsigned int j = 0;
    std::string addBuffer;

    // Iterate through the new file to find sequences
    while (j <= newFileContent.size() - N) {
        std::string sequence = newFileContent.substr(j, N);
        unsigned int offset;
        int length = N;

        // If the sequence is found in the hash table
        if (hashTable.find(sequence, offset, oldFileContent, newFileContent, j, length)) {
            // Write the copy instruction to the revision file
            frevision << "#" << offset << "," << length;
            j += length - 1; // Move forward by the length of the match
        }
        else {
            // Start an add instruction
            addBuffer = sequence[0];
            j++;

            // If there are more sequences to process
            if (j <= newFileContent.size() - N) {
                sequence = newFileContent.substr(j, N);
            }

            // If at the end of the file, add the remaining sequence to addBuffer
            if (j + N == newFileContent.size()) {
                addBuffer += sequence;
                j += sequence.size();
            }

            // Continue adding to addBuffer until a match is found or end of file
            while (j <= newFileContent.size() - N) {
                if (hashTable.find(sequence, offset))
                    break;
                addBuffer += sequence[0];
                j++;
                if (j <= newFileContent.size() - N) {
                    sequence = newFileContent.substr(j, N);
                }
                if (j + N == newFileContent.size()) {
                    addBuffer += sequence;
                    j += sequence.size(); 
                    break;
                }
            }

            // Find a suitable delimiter
            char delim = '/';
            int i = 0;
            while (i < addBuffer.size()) {
                if (addBuffer.at(i) == delim) {
                    delim++;
                    i = -1;
                }
                i++;
            }

            // Write the add instruction to the revision file
            frevision << "+" << delim << addBuffer << delim;
            addBuffer.clear(); // Clear the add buffer
            j--;
        }
        j++;
    }

    // Handle any remaining characters in the new file
    while (j < newFileContent.size()) {
        addBuffer += newFileContent[j];
        j++;
    }

    // If there are any remaining characters to add, write them to the revision file
    if (!addBuffer.empty()) {
        char delim = '/';
        int i = 0;
        while (i < addBuffer.size()) {
            if (addBuffer.at(i) == delim) {
                delim++;
                i = -1;
            }
            i++;
        }
        frevision << "+" << delim << addBuffer << delim;
    }
}
