#include <iostream>
#include<vector>
#include <algorithm>
using namespace std;

class Task {
private:
    string text;
    int priority;
    string status;
    string type;
public:
    Task(string text, int priority, string status, string type) {
        this->text = text;
        this->priority = priority;
        this->status = status;
        this->type = type;
    }

    string get_text() {
        return text;
    }
    int get_priority() {
        return priority;
    }
    string get_status() {
        return status;
    }
    string get_type() {
        return type;
    }
};

static class IStrategySort {
public:
    virtual void sortTasks(vector<Task>& tasks) = 0;
};

class SortByStatus : public IStrategySort {
public:
    static int convertStatusInNumber(string status) {

        if (status == "Not done") {
            return 1;
        }
        else if (status == "In progress")
        {
            return 2;
        }
        else if (status == "In review")
        {
            return 3;
        }
        else if (status == "Done")
        {
            return 4;
        }
    }
    static bool CompareTwoElem(Task& obj, Task& obj1)
    {
        return convertStatusInNumber(obj.get_status()) < convertStatusInNumber(obj1.get_status());
    }
    void sortTasks(vector<Task>& tasks)override
    {
        sort(tasks.begin(), tasks.end(), CompareTwoElem);
    }
};

class SortByPriority : public IStrategySort {
public:
    static bool CompareTwoElem(Task& obj, Task& obj1)
    {
        return obj.get_priority() < obj1.get_priority();
    }
    void sortTasks(vector<Task>& tasks) override {
        sort(tasks.begin(), tasks.end(), CompareTwoElem);
    }
};

class SortByType : public IStrategySort
{
public:
    static int convertTypeInNumber(string type) {

        if (type == "type1") {
            return 1;
        }
        else if (type == "type2")
        {
            return 2;
        }
        else if (type == "type3")
        {
            return 3;
        }
        else if (type == "type4")
        {
            return 4;
        }
    }
    static bool CompareTwoElem(Task& obj, Task& obj1)
    {
        return convertTypeInNumber(obj.get_type()) < convertTypeInNumber(obj1.get_type());
    }

    void sortTasks(vector<Task>& tasks) override
    {
        sort(tasks.begin(), tasks.end(), CompareTwoElem);
    };
};

class IObserve {
public:
    virtual void update(string msg) = 0;
    virtual ~IObserve() {}
};


class Logger :public IObserve {
public:
    void update(string msg)override
    {
        cout << "[Logger]: " << msg << endl;
    }
};

class Sender :public IObserve {
public:
    void update(string msg) override
    {
        cout << "[Send]: " << msg << endl;
    }
};

class UI :public IObserve {
public:
    void update(string msg) override
    {
        cout << "[UI]: " << msg << endl;
    }
};

class TaskManager {
    vector<Task>tasks;
    vector<IObserve*>observes;

public:
    void addOb(IObserve* obj)
    {
        observes.push_back(obj);
    }
    void sendEvent(string msg)
    {
        for (auto elem : observes)
        {
            elem->update(msg);
        }
    }

    void addT(Task task) {
        tasks.push_back(task);
        sendEvent("Task added: " + task.get_text());
    }
    void showT()
    {
        for (Task elem : tasks)
        {
            cout << elem.get_text() << ", " << elem.get_priority() << ", " << elem.get_status() << ", " << elem.get_type() << endl;
        }
    }
    vector<Task>* getTasksAdress() {
        return &tasks;
    }
};

int main()
{
    TaskManager obj;

    Logger log;
    Sender msg;
    UI ui;

    obj.addOb(&log);
    obj.addOb(&msg);
    obj.addOb(&ui);

    Task task("Wake up", 1, "Done", "type4");
    Task taskNew("Get coffee", 2, "In progress", "type1");
    Task taskNewer("Go for a walk", 5, "Not done", "type3");

    obj.addT(taskNewer);
    obj.addT(taskNew);
    obj.addT(task);

    cout << "\n\nBefore sorting: " << endl;
    obj.showT();

    SortByPriority prioritySorter;
    SortByStatus statusSorter;
    SortByType typeSorter;

    prioritySorter.sortTasks(*obj.getTasksAdress());
    cout << "\n\nAfter sorting: " << endl;
    obj.showT();

    cout << endl;
    while (true) {
        cout << "How do you want to sort the vector? 1 - by priority/ 2 - by status/ 3 - by type" << endl;
        char choice;
        cin >> choice;
        switch (choice) {
        case '1':
            prioritySorter.sortTasks(*obj.getTasksAdress());
            cout << "\nAfter sorting: " << endl;
            obj.showT();
            break;
        case '2':
            statusSorter.sortTasks(*obj.getTasksAdress());
            cout << "\nAfter sorting: " << endl;
            obj.showT();
            break;
        case '3':
            typeSorter.sortTasks(*obj.getTasksAdress());
            cout << "\nAfter sorting: " << endl;
            obj.showT();
            break;
        default:
            return 0;
        }
    }
}
