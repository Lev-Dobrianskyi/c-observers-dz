#include "TaskObservers.h"
#include "Sort.h"

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
