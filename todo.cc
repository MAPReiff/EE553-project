#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Task {
public:
  string description;
  bool completed;
  Task(string description) {
    this->description = description;
    this->completed = false;
  }
};

class ToDoList {
private:
  vector<Task *> tasks;

public:
  void addTask(string description) {
    Task *newTask = new Task(description);
    tasks.push_back(newTask);
  }

  void removeTask(int index) {
    if (index >= 0 && index < tasks.size()) {
      delete tasks[index];
      tasks.erase(tasks.begin() + index);
    }
  }

  void completeTask(int index) {
    if (index >= 0 && index < tasks.size()) {
      tasks[index]->completed = true;
    }
  }

  void displayTasks() {
    cout << "Tasks:\n";
    for (int i = 0; i < tasks.size(); i++) {
      Task *task = tasks[i];
      cout << i << ": ";
      if (task->completed) {
        cout << "[x] ";
      } else {
        cout << "[ ] ";
      }
      cout << task->description << "\n";
    }
  }

  void saveToFile(string filename) {
    ofstream file(filename);
    for (int i = 0; i < tasks.size(); i++) {
      Task *task = tasks[i];
      file << task->description << "," << task->completed << "\n";
    }
    file.close();
  }

  void loadFromFile(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
      string line;
      while (getline(file, line)) {
        int commaIndex = line.find(",");
        string description = line.substr(0, commaIndex);
        bool completed = stoi(line.substr(commaIndex + 1));
        Task *task = new Task(description);
        task->completed = completed;
        tasks.push_back(task);
      }
      file.close();
    }
  }
};

int main() {
  ToDoList todoList;
  cout << "What is your name?" << endl;
  string name;
  cin >> name;
  cout << "Loading from " + name + ".txt" << endl;
  todoList.loadFromFile(name + ".txt");

  while (true) {
    string command;
    cout << "Enter command (add/remove/complete/display/save/quit): ";
    cin >> command;

    if (command == "add") {
      string description;
      cout << "Enter task description: ";
      cin.ignore();
      getline(cin, description);
      todoList.addTask(description);
    } else if (command == "remove") {
      int index;
      cout << "Enter task index: ";
      cin >> index;
      todoList.removeTask(index);
    } else if (command == "complete") {
      int index;
      cout << "Enter task index: ";
      cin >> index;
      todoList.completeTask(index);
    } else if (command == "display") {
      todoList.displayTasks();
    } else if (command == "save") {
      todoList.saveToFile(name);
      cout << "Saved to " + name + ".txt" << endl;
    } else if (command == "quit") {
      break;
    } else {
      cout << "Invalid command\n";
    }
  }

  return 0;
}