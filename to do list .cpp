#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Task {
public:
    string title;
    bool completed;

    Task(string t, bool c = false) {
        title = t;
        completed = c;
    }
};

class TodoList {
private:
    vector<Task> tasks;
    const string filename = "tasks.txt";

public:
    void loadTasks() {
        ifstream file(filename);
        if (!file) return;

        string title;
        bool completed;

        while (getline(file, title)) {
            file >> completed;
            file.ignore();
            tasks.push_back(Task(title, completed));
        }

        file.close();
    }

    void saveTasks() {
        ofstream file(filename);

        for (const auto& task : tasks) {
            file << task.title << endl;
            file << task.completed << endl;
        }

        file.close();
    }

    void addTask() {
        string title;

        cout << "Enter task: ";
        cin.ignore();
        getline(cin, title);

        tasks.push_back(Task(title));
        cout << "Task added successfully!\n";
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "\nNo tasks available.\n";
            return;
        }

        cout << "\n===== TO-DO LIST =====\n";

        for (size_t i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". ["
                 << (tasks[i].completed ? 'X' : ' ')
                 << "] "
                 << tasks[i].title << endl;
        }
    }

    void completeTask() {
        viewTasks();

        if (tasks.empty()) return;

        int index;
        cout << "\nEnter task number to mark complete: ";
        cin >> index;

        if (index >= 1 && index <= tasks.size()) {
            tasks[index - 1].completed = true;
            cout << "Task completed!\n";
        } else {
            cout << "Invalid task number.\n";
        }
    }

    void deleteTask() {
        viewTasks();

        if (tasks.empty()) return;

        int index;
        cout << "\nEnter task number to delete: ";
        cin >> index;

        if (index >= 1 && index <= tasks.size()) {
            tasks.erase(tasks.begin() + index - 1);
            cout << "Task deleted!\n";
        } else {
            cout << "Invalid task number.\n";
        }
    }
};

int main() {
    TodoList todo;
    todo.loadTasks();

    int choice;

    do {
        cout << "\n===== TO-DO LIST MENU =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Complete Task\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                todo.addTask();
                break;

            case 2:
                todo.viewTasks();
                break;

            case 3:
                todo.completeTask();
                break;

            case 4:
                todo.deleteTask();
                break;

            case 5:
                todo.saveTasks();
                cout << "Tasks saved. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
