
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 

using namespace std;

struct Task {
    int id;
    string description;
    bool completed;

    Task(int id = 0, const string& description = "", bool completed = false)
        : id(id), description(description), completed(completed) {}
};

class ToDoList {
private:
    vector<Task> tasks;
    int nextId;

public:
    ToDoList() : nextId(1) {} 

    void AddTask(const string& description) {
        tasks.push_back(Task(nextId++, description));
    }

    void MarkTaskCompleted(int taskId, bool completed) {
        auto it = find_if(tasks.begin(), tasks.end(),
            [taskId](const Task& task) { return task.id == taskId; });
        if (it != tasks.end()) {
            it->completed = completed;
        }
        else {
            cout << "Task not found." << endl;
        }
    }

    void RemoveTask(int taskId) {
        auto it = remove_if(tasks.begin(), tasks.end(),
            [taskId](const Task& task) { return task.id == taskId; });
        if (it != tasks.end()) {
            tasks.erase(it, tasks.end());
        }
        else {
            cout << "Task not found." << endl;
        }
    }

    const vector<Task>& GetTasks() const {
        return tasks;
    }

    void PrintTasks() const {
        if (tasks.empty()) {
            cout << "There are no tasks in the list." << endl;
        }
        else {
            cout << "Tasks:" << endl;
            for (const Task& task : tasks) {
                cout << "[" << task.id << "] " << (task.completed ? "Completed: " : "Pending: ")
                    << task.description << endl;
            }
        }
    }
};

int main() {
    ToDoList list;

    int choice;
    string temp; 

    while (true) {
        cout << endl;
        cout << "To-Do List Manager" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Task Completed" << endl;
        cout << "4. Remove Task" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            getline(cin >> ws, temp); 
            string description;
            cout << "Please enter a task description: ";
            getline(cin, description);
            if (description.empty()) {
                cout << "Task description cannot be empty." << endl;
            }
            else {
                list.AddTask(description);
            }
            break;
        }
        case 2:
            list.PrintTasks();
            break;
        case 3: {
            int taskId;
            cout << "Enter the ID of the task to mark completed: ";
            cin >> taskId;
            list.MarkTaskCompleted(taskId, true);
            break;
        }
        case 4: {
            int taskId;
            cout << "Enter the ID of the task to remove: ";
            cin >> taskId;
            list.RemoveTask(taskId);
            break;
        }
        case 5:
            cout << "Exiting To-Do List Manager." << endl;
            return 0;
        default:
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}


