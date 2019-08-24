#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::getline;
using std::cin;
using std::string;
using std::fstream;
using std::ios;
using std::istreambuf_iterator;
using std::to_string;
using std::stoi;


void steg(const string& filePath, const string& message);
string unsteg(const string& filePath);
string readfileContents(const string& filePath);
void writeAlteredContents(const string& filePath, const string& alteredContents);


/**
 * Inserts the message into the image
 */
void steg(const string& filePath, const string& message) {
    string fileContents = readfileContents(filePath);
    int charSeparation = fileContents.length() / message.length();

    fileContents.append(" ");
    fileContents.append(std::to_string(message.length()));

    for (int i = 0; i < message.length(); ++i) {
        fileContents.insert((charSeparation * i) + 2, 1, message.at(i));
    }

    writeAlteredContents(filePath, fileContents);
}


/**
 * Recovers the message from the image
 */
string unsteg(const string& filePath) {
    string fileContents = readfileContents(filePath);

    int messageLength = stoi(fileContents.substr(fileContents.find_last_of(' ')));
    int charSeparation = (fileContents.length() - messageLength) / messageLength;
    
    string message;
    message.clear();

    for (int i = 0; i < messageLength; ++i) {
        message.push_back(fileContents.at(charSeparation * i + 2));
    }

    return message;
}


/**
 * Opens the file at the given fileName and reads in the contents, then returns them
 */
string readfileContents(const string& filePath) {
    fstream file;

    file.open(filePath, fstream::in | ios::binary);
    string contents((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    file.close();

    return contents;
}


/**
 * Opens and clears the file at the given fileName, writes in the given cipherText, 
 * and closes it.
 */
void writeAlteredContents(const string& filePath, const string& alteredContents) {
    fstream file;

    // Opens the file, clears all data inside, writes cipherText, and closes it
    file.open(filePath, fstream::out | fstream::trunc | ios::binary);
    file << alteredContents;
    file.close();
}


int main(int argc, char* argv[]) {    
    if (argc < 2) {
        cout << endl;
        cout << "Too few arguments." << endl << endl;
        cout << "First argument should be the path to the image you want to MegaStega" << endl << endl;
        cout << "Then type your message you want to be inserted, or type nothing for MegaStega to decode an encoded message" << endl << endl;
    }
    
    // cout << endl;
    // cout << "Enter the path (from root) of the image you want to MegaStega:" << endl;
    // string filePath;
    // cin >> filePath;
    // cout << endl << endl;

    // cin.ignore();

    // cout << "Enter your message:" << endl;
    // string message;
    // getline(cin, message);
    // cout << endl << endl;

    string filePath = argv[1];
    if (argc == 2) {
        cout << "Message:" << endl;
        cout << unsteg(filePath) << endl;
    }
    else {
        string message;
        message.clear();

        for (int i = 2; i < argc; ++i) {
            message.append(argv[i]);
            message.append(" ");
        }
        message.pop_back();

        steg(filePath, message);
    }

    return 0;
}