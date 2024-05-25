#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct Task {
    std::string description;
    bool done;

    Task(const std::string& desc, bool is_done = false) : description(desc), done(is_done) {}
};
class ToDoList {
private:
    std::vector<Task> tasks;
    const std::string filename = "tasks.txt";

    void loadTasks() {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            bool done = line.back() == '1';
            line.pop_back();  // remove the status character
            tasks.emplace_back(line, done);
        }
        file.close();
    }

    void saveTasks() {
        std::ofstream file(filename);
        if (!file.is_open()) return;

        for (const auto& task : tasks) {
            file << task.description << (task.done ? '1' : '0') << '\n';
        }
        file.close();
    }

public:
    ToDoList() {
        loadTasks();
    }

    ~ToDoList() {
        saveTasks();
    }

    void addTask(const std::string& description) {
        tasks.emplace_back(description);
    }

    void markTaskDone(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].done = true;
        } else {
            std::cout << "Invalid task index.\n";
        }
    }

    void displayTasks() const {
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << (i + 1) << ". [" << (tasks[i].done ? 'X' : ' ') << "] " << tasks[i].description << '\n';
        }
    }
};
void displayMenu() {
    std::cout << "To-Do List Menu:\n";
    std::cout << "1. Add a task\n";
    std::cout << "2. Mark a task as done\n";
    std::cout << "3. Display all tasks\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    ToDoList todoList;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();  // ignore newline character

        switch (choice) {
            case 1: {
                std::string description;
                std::cout << "Enter task description: ";
                std::getline(std::cin, description);
                todoList.addTask(description);
                break;
            }
            case 2: {
                int index;
                todoList.displayTasks();
                std::cout << "Enter task number to mark as done: ";
                std::cin >> index;
                todoList.markTaskDone(index - 1);
                break;
            }
            case 3: {
                todoList.displayTasks();
                break;
            }
            case 4: {
                std::cout << "Exiting...\n";
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 4);

    return 0;
}
