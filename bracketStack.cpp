class BracketStack {
private:
  char *stack;
  int MAX_SIZE;
  int size;

public:
  BracketStack(int m) {
    size = 0;
    MAX_SIZE = m;
    stack = new char[MAX_SIZE];
  }

  bool isEmpty();
  bool isFull();
  int push(char);
  char pop();
  char peek();
};

bool BracketStack::isEmpty() { return size == 0; }
bool BracketStack::isFull() { return size == MAX_SIZE; }

int BracketStack::push(char c) {
  if (isFull())
    return -1;
  stack[size++] = c;
  return 0;
}

char BracketStack::pop() {
  if (isEmpty())
    return '\0';
  return stack[--size];
}

char BracketStack::peek() {
  if (isEmpty())
    return '\0';
  return stack[size - 1];
}
