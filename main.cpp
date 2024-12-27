#include <iostream>
#include <ctime>
#include <map>
#include <iomanip>

void endTask(std::map<std::string, std::pair<std::time_t, std::time_t>> &tasks) {
    const std::time_t current_time = std::time(nullptr);
    tasks.rbegin()->second.second = current_time;
    std::cout << "Task '" << tasks.rbegin()->first << "' ended." << std::endl;
}

void newTask(std::map<std::string, std::pair<std::time_t, std::time_t>> &tasks) {
    std::string task_name;
    std::cin >> task_name;
    if (!tasks.empty() && tasks.rbegin()->second.second == tasks.rbegin()->second.first) {
        endTask(tasks);
    }
    const std::time_t current_time = std::time(nullptr);
    tasks[task_name].first = current_time;
    tasks[task_name].second = current_time;
    std::cout << "Task '" << task_name << "' started." << std::endl;
}

void showTasks(const std::map<std::string, std::pair<std::time_t, std::time_t>> &tasks) {
    std::cout << "---------------------------------------------------------" << std::endl;
    for (const auto&[fst, snd] : tasks) {
        std::cout << "Task: " << fst << std::endl;
        std::cout << "Start time: " << std::put_time(std::localtime(&snd.first), "%H:%M:%S") << std::endl;
        if (snd.second == snd.first) {
            std::cout << "Task is still running." << std::endl;
        } else {
            std::cout << "End time: " << std::put_time(std::localtime(&snd.second), "%H:%M:%S") << std::endl;
            auto duration = snd.second - snd.first;
            std::cout << "Duration: " << std::put_time(std::gmtime(&duration), "%H:%M:%S") << std::endl;
        }
        std::cout << "---------------------------------------------------------" << std::endl;
    }
}

int main() {
    std::map<std::string, std::pair<std::time_t, std::time_t>> tasks;
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
