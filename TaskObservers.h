#pragma once

#include <vector>
#include <string>
#include <iostream>
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
