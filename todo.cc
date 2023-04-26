#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class Task {
public:
  string description;
  bool completed;
  string date;
  Task(string description, string date = "") {
    this->description = description;
    this->completed = false;
    this->date = date;
  }
};

// Define a comparison function for sorting tasks based on date
bool compareTasks(Task *task1, Task *task2) {
  if (task1->date.empty() && task2->date.empty()) {
    return false;
  } else if (task1->date.empty()) {
    return false;
  } else if (task2->date.empty()) {
    return true;
  } else {
    return task1->date < task2->date;
  }
}

class ToDoList {
private:
  vector<Task *> tasks;

public:
  void addTask(string description, string date = "") {
    Task *newTask = new Task(description, date);
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
    vector<Task *> datedTasks;
    vector<Task *> undatedTasks;
    for (int i = 0; i < tasks.size(); i++) {
      Task *task = tasks[i];
      if (!task->date.empty()) {
        datedTasks.push_back(task);
      } else {
        undatedTasks.push_back(task);
      }
    }
    sort(datedTasks.begin(), datedTasks.end(), compareTasks);
    for (Task *task : datedTasks) {
      cout << "[";
      if (task->completed) {
        cout << "x";
      } else {
        cout << " ";
      }
      cout << "] " << task->description << " (Due: " << task->date << ")"
           << endl;
    }
    for (Task *task : undatedTasks) {
      cout << "[";
      if (task->completed) {
        cout << "x";
      } else {
        cout << " ";
      }
      cout << "] " << task->description << " (Due: N/A)" << endl;
    }
  }

  void displayAgenda() {
    vector<Task *> datedTasks;
    vector<Task *> undatedTasks;
    for (int i = 0; i < tasks.size(); i++) {
      Task *task = tasks[i];
      if (!task->date.empty()) {
        datedTasks.push_back(task);
      } else {
        undatedTasks.push_back(task);
      }
    }
    sort(datedTasks.begin(), datedTasks.end(),
         [](Task *a, Task *b) { return a->date < b->date; });
    cout << "Agenda:\n";
    for (Task *task : datedTasks) {
      cout << "- " << task->description << " (Due: " << task->date << ")\n";
    }
    if (!undatedTasks.empty()) {
      cout << "- No Due Date:\n";
      for (Task *task : undatedTasks) {
        cout << "  - " << task->description << "\n";
      }
    }
  }
  void saveToFile(string filename) {
    ofstream file(filename);
    for (int i = 0; i < tasks.size(); i++) {
      Task *task = tasks[i];
      file << task->description << "," << task->completed;
      if (!task->date.empty()) { // save date if it exists
        file << "," << task->date;
      }
      file << "\n";
    }
    file.close();
  }

  void loadFromFile(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
      string line;
      while (getline(file, line)) {
        stringstream ss(line);
        string description, dateStr;
        bool completed;
        getline(ss, description, ',');
        ss >> completed;
        if (getline(ss, dateStr)) { // check if date exists in line
        dateStr.erase(remove(dateStr.begin(), dateStr.end(), ','),
                      dateStr.end());
          Task *task = new Task(description, dateStr);
          task->completed = completed;
          tasks.push_back(task);
        } else {
          Task *task = new Task(description);
          task->completed = completed;
          tasks.push_back(task);
        }
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
    cout << "Enter command (add/remove/complete/display/agenda/save/quit): ";
    cin >> command;

    if (command == "add") {
      string description;
      cout << "Enter task description: ";
      cin.ignore();
      getline(cin, description);

      string date;
      cout << "Enter task date (optional, format YYYY-MM-DD): ";
      getline(cin, date);
      todoList.addTask(description, date);
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
    } else if (command == "agenda") {
      todoList.displayAgenda();
    } else if (command == "save") {
      todoList.saveToFile(name + ".txt");
      cout << "Saved to " + name + ".txt" << endl;
    } else if (command == "quit") {
      break;
    } else {
      cout << "Invalid command\n";
    }
  }

  return 0;
}
