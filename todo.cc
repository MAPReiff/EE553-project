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
		// add a task to the list
		void addTask(string description) {
			Task *newTask = new Task(description);
			tasks.push_back(newTask);
		}

		// remove a task from the list
		void removeTask(int index) {
			if (index >= 0 && index < tasks.size()) {
				delete tasks[index];
				tasks.erase(tasks.begin() + index);
			}
		}

		// mark a task as completed
		void completeTask(int index) {
			if (index >= 0 && index < tasks.size()) {
				tasks[index]->completed = true;
			}
		}

		// display the list of tasks
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

		// save the list of tasks to a file
		void saveToFile(string filename) {
			ofstream file(filename);
			for (int i = 0; i < tasks.size(); i++) {
				Task *task = tasks[i];
				file << task->description << "," << task->completed << "\n";
			}
			file.close();
		}

		// load the list of tasks from a file
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
  // new list loaded from a file
  ToDoList list;

  // hard-coded file for now, will ask user for filename later
  list.loadFromFile("todo.txt");


	return 0;
}