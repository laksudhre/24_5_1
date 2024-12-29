#include <algorithm>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>

struct Task {
    Task() : name(), start(), end() {}
    std::string name;
    std::time_t start;
    std::time_t end;
};

void endTask(std::vector<Task> &tasks) {
    const std::time_t current_time = std::time(nullptr);
    tasks.rbegin()->end = current_time;
    std::cout << "Task '" << tasks.rbegin()->name << "' ended." << std::endl;
}

void newTask(std::vector<Task> &tasks) {
    Task task;
    std::string task_name;
    std::cin >> task_name;
    if (!tasks.empty() && tasks.rbegin()->end == tasks.rbegin()->start) {
        endTask(tasks);
    }
    const std::time_t current_time = std::time(nullptr);
    task.name = task_name;
    task.start = current_time;
    task.end = current_time;
    tasks.push_back(task);
    std::cout << "Task '" << task_name << "' started." << std::endl;
}

void showTasks(std::vector<Task> &tasks) {
    std::cout << "---------------------------------------------------------" << std::endl;
    for (const auto& [name, start, end] : tasks) {
        std::cout << "Task: " << name << std::endl;
        std::cout << "Start time: " << std::put_time(std::localtime(&start), "%H:%M:%S") << std::endl;
        if (end == start) {
            std::cout << "Task is still running." << std::endl;
        } else {
            std::cout << "End time: " << std::put_time(std::localtime(&end), "%H:%M:%S") << std::endl;
            auto duration = end - start;
            std::cout << "Duration: " << std::put_time(std::gmtime(&duration), "%H:%M:%S") << std::endl;
        }
        std::cout << "---------------------------------------------------------" << std::endl;
    }
}

int main() {
    std::vector<Task> tasks;
    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "begin") {
            newTask(tasks);
        } else if (cmd == "end") {
            endTask(tasks);
        } else if (cmd == "status") {
            showTasks(tasks);
        } else if (cmd == "exit") {
            break;
        } else {
            std::cout << "Invalid command. Supported commands: begin, end, status, exit" << std::endl;
        }
    }
    return 0;
}
