#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// // Перечислимый тип для статуса задачи
// enum class TaskStatus {
//   NEW,          // новая
//   IN_PROGRESS,  // в разработке
//   TESTING,      // на тестировании
//   DONE          // завершена
// };

// // Объявляем тип-синоним для map<TaskStatus, int>,
// // позволяющего хранить количество задач каждого статуса
// using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const{
      return tasks_by_person.at(person);
  }
  
  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person){
      TasksInfo& tasks = tasks_by_person[person];
      tasks[TaskStatus::NEW] += 1;
  }
  
  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string& person, int task_count){
            TasksInfo modified, non_modified;
            if(tasks_by_person.count(person) ==0){
                return make_tuple(modified, non_modified);
            }

            TasksInfo& tasks_by_status = tasks_by_person[person];
            auto to_be_processed = task_count;
            for(int index=0; to_be_processed > 0 && index < static_cast<int>(TaskStatus::DONE); index++){
                auto status = static_cast<TaskStatus>(index);
                auto count = tasks_by_status[status];
                auto count_modified = min(count, to_be_processed);
                auto count_modified_not = count - count_modified;
                to_be_processed = to_be_processed - count_modified;
                if(count_modified > 0){
                    modified[static_cast<TaskStatus>(index+1)] = count_modified;
                }
                if(count_modified_not > 0){
                    non_modified[static_cast<TaskStatus>(index)] = count_modified_not;
                }
            }

            for(auto [status, count]: modified){
                tasks_by_status[static_cast<TaskStatus>(static_cast<int>(status)-1)] -= count;
                tasks_by_status[status]+=count;
            }

            return make_tuple(modified, non_modified);
      }

private:
    map<string,TasksInfo> tasks_by_person;
};

// // Принимаем словарь по значению, чтобы иметь возможность
// // обращаться к отсутствующим ключам с помощью [] и получать 0,
// // не меняя при этом исходный словарь
// void PrintTasksInfo(TasksInfo tasks_info) {
//   cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
//       ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
//       ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
//       ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
// }

// int main() {
//   TeamTasks tasks;
//   tasks.AddNewTask("Ilia");
//   for (int i = 0; i < 3; ++i) {
//     tasks.AddNewTask("Ivan");
//   }
//   cout << "Ilia's tasks: ";
//   PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
//   cout << "Ivan's tasks: ";
//   PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
//   TasksInfo updated_tasks, untouched_tasks;
  
//   tie(updated_tasks, untouched_tasks) =
//       tasks.PerformPersonTasks("Ivan", 2);
//   cout << "Updated Ivan's tasks: ";
//   PrintTasksInfo(updated_tasks);
//   cout << "Untouched Ivan's tasks: ";
//   PrintTasksInfo(untouched_tasks);
  
//   tie(updated_tasks, untouched_tasks) =
//       tasks.PerformPersonTasks("Ivan", 2);
//   cout << "Updated Ivan's tasks: ";
//   PrintTasksInfo(updated_tasks);
//   cout << "Untouched Ivan's tasks: ";
//   PrintTasksInfo(untouched_tasks);

//   return 0;
// }