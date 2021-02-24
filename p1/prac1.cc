// DNI 20993208G Juan Andrés Orocondo ÁLvarez

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct Date{
  int day;
  int month;
  int year;
};

struct Task{
  string name;
  Date deadline;
  bool isDone;
  int time;
};

struct List{
  string name;
  vector<Task> tasks;
};

struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME
};

void error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty string" << endl;
      break;
    case ERR_LIST_NAME:
      cout << "ERROR: wrong list name" << endl;
      break;
    case ERR_TASK_NAME:
      cout << "ERROR: wrong task name" << endl;
      break;
    case ERR_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_TIME:
      cout << "ERROR: wrong expected time" << endl;
  }
}

void showMainMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

string comprobar(string r){

  string fun;
  do{
    cout << " Enter "<< r << " name: ";
    getline(cin,fun);
    if(!fun.size()){
      error(ERR_EMPTY);
    }
  }while(!fun.size());

  return fun;
}

void editProject(Project &toDoList){
  string pr= "project";
  
  toDoList.name=comprobar(pr);

cout << "Enter project description: ";
getline(cin,toDoList.description);
}

void addList(Project &toDoList){
  List x;
  int b=0;
  string k= "list";
  x.name=comprobar(k);
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    if(x.name == toDoList.lists[i].name){
      b=1;
      error(ERR_LIST_NAME);
    }
  }
  if(b==0){
    toDoList.lists.push_back(x);
  }
}

void deleteList(Project &toDoList){
  string p="list";
  int a=0;
  string del;
  del=comprobar(p);
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    if(del == toDoList.lists[i].name){
      toDoList.lists.erase(toDoList.lists.begin()+i);
      a=1;
    }
    cout << toDoList.lists[i].name;
  }
  if(a==0){
    error(ERR_LIST_NAME);
  }
}

void addTask(Project &toDoList){
  string p="list";
  string tas;
  string t="task";
  Task x;
  int b=0;
  char q;
  char c;
  int a;
  int mes;
  int dias_mes[]= {31, 28, 31, 30,31, 30, 31, 31, 30, 31, 30, 31};
  tas=comprobar(p);
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    if(tas == toDoList.lists[i].name){
      b=1;
      a=i;
    }else{
      error(ERR_LIST_NAME);
    }
  }
  if(b==0){
    getline(cin,x.name);

    cout << "Enter Deadline: ";
    cin >> x.deadline.day >> q >> x.deadline.month >> c >> x.deadline.year;
    if(x.deadline.year>2000 && x.deadline.year<2100){
      if((x.deadline.year % 4 == 0 and x.deadline.year % 100 != 0) or x.deadline.year % 400 == 0){
        dias_mes[1] = dias_mes[1] + 1;
      }
      if(x.deadline.month>=1 && x.deadline.month<=12){
        mes = x.deadline.month-1;
        if(x.deadline.day>=1 && x.deadline.day<=dias_mes[mes]){
          



          
          toDoList.lists[a].tasks.push_back(x);
        }else{
          error(ERR_DATE);
        }
      }else{
        error(ERR_DATE);
      }
    }else{
      error(ERR_DATE);
    }
  }


  
}

void deleteTask(Project &toDoList){
}

void toggleTask(Project &toDoList){
}

void report(const Project &toDoList){
}

int main(){
  Project toDoList;
  toDoList.id=1;
  char option;
  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': editProject(toDoList);
                break;
      case '2': addList(toDoList);
                break;
      case '3': deleteList(toDoList);
                break;
      case '4': addTask(toDoList);
                break;
      case '5': deleteTask(toDoList);
                break;
      case '6': toggleTask(toDoList);
                break;
      case '7': report(toDoList);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}
