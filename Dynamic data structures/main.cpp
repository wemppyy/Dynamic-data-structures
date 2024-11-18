#include <iostream>
#include <queue>
#include <string>

struct PrintRequest {
    std::string clientName;
    int priority;

    bool operator<(const PrintRequest& other) const {
        return priority < other.priority;
    }
};

int main() {
    std::priority_queue<PrintRequest> printQueue;
    std::queue<std::string> printLog;

    printQueue.push({ "Alice", 3 });
    printQueue.push({ "Bob", 1 });
    printQueue.push({ "Charlie", 2 });

    while (!printQueue.empty()) {
        PrintRequest currentRequest = printQueue.top();
        printQueue.pop();

        printLog.push(currentRequest.clientName + " (Priority: " + std::to_string(currentRequest.priority) + ")");
    }

    std::cout << "Print Log:\n";
    while (!printLog.empty()) {
        std::cout << printLog.front() << "\n";
        printLog.pop();
    }

    return 0;
}
