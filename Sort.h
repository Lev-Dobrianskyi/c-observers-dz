#pragma once

#include <vector>
#include <string>
#include "TaskObservers.h"
#include <algorithm>
using namespace std;
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
