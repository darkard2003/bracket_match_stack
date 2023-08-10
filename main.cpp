#include "bracketStack.cpp"

#include <fstream>
#include <iostream>

#define BUFF_SIZE 256
#define STACK_SIZE 256

using namespace std;

char getClosing(char o) {
  if (o == '(')
    return ')';
  if (o == '{')
    return '}';
  if (o == '[')
    return ']';
  return '\0';
}

bool isBalanced(ifstream &file) {

  int lineNum = 1;
  char buffer[BUFF_SIZE];

  BracketStack s(STACK_SIZE);

  while (file.getline(buffer, BUFF_SIZE)) {
    int i = 0;
    char c = buffer[i];

    while (c != '\0') {
      if (c == '(' || c == '[' || c == '{') {
        int r = s.push(c);
        if (r == -1) {
          cout << "Stack overflow at line " << lineNum << endl;
          return false;
        }
      } else if (c == ')' || c == ']' || c == '}') {
        char t = s.pop();
        if (t == -1) {
          cout << "Stack underflow at line " << lineNum << endl;
          return false;
        }
        if (c != getClosing(t)) {
          cout << "Mismatch at line " << lineNum << endl;
          cout << "Expected " << getClosing(t) << " but got " << c << endl;
          return false;
        }
      }
      c = buffer[++i];
    }
    lineNum++;
  }

  if (!s.isEmpty()) {
    char t = s.pop();
    cout << "Missing closing " << getClosing(t) << "at end of file" << endl;
    return false;
  }

  return true;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return EXIT_FAILURE;
  }

  for (int i = 1; i < argc; i++) {
    string filename = argv[i];
    ifstream file(filename);

    if (!file.is_open()) {
      cout << "Unable to open file " << filename << endl;
      continue;
    }

    bool balanced = isBalanced(file);

		file.close();

    if (balanced) {
      cout << filename << " is balanced" << endl;
    } else {
      cout << filename << " is not balanced" << endl;
    }

    cout << endl;
  }

  return EXIT_SUCCESS;
}
