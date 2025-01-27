// DNI 20993208G Juan Andrés Orocondo ÁLvarez

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

const int ANYMAX=2101; //Introducir el año deseado sumandole 1 para el correcto funcionamiento del programa

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

// Función para comprobar que la entrada de texto no esta vacía
string comprobar(string r){

  string fun;
  do{
    cout << "Enter "<< r << " name: ";
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
  
  //recorre todas las listas en busca de alguna con el mismo nombre si no hay añadira la lista deseada
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
    }
  }
  if(b==1){

    cout << "Enter task name: ";
    getline(cin,x.name);

    cout << "Enter deadline: ";
    cin >> x.deadline.day >> q >> x.deadline.month >> c >> x.deadline.year;
    // comprobacion de que la fecha introducida es correcta
    if(x.deadline.year>=2000 && x.deadline.year<ANYMAX){
      if((x.deadline.year % 4 == 0 and x.deadline.year % 100 != 0) or x.deadline.year % 400 == 0){
        dias_mes[1] = dias_mes[1] + 1;
      }
      if(x.deadline.month>=1 && x.deadline.month<=12){
        mes = x.deadline.month-1;
        if(x.deadline.day>=1 && x.deadline.day<=dias_mes[mes]){
          cout << "Enter expected time: ";
          cin >> x.time;
          if(x.time>=1 && x.time <=180){
            x.isDone=false;
            toDoList.lists[a].tasks.push_back(x);

          }else{
            error(ERR_TIME);
          }
        }else{
          error(ERR_DATE);
        }
      }else{
        error(ERR_DATE);
      }
    }else{
      error(ERR_DATE);
    }
  }else{
    error(ERR_LIST_NAME);
  }


  
}

void deleteTask(Project &toDoList){
  string p="list";
  string x;
  string t;
  int a=0;
  int b=0;
  bool k=true;
  x=comprobar(p);

  for(unsigned int i=0;i<toDoList.lists.size();i++){
    if(x == toDoList.lists[i].name){
      b=1;
      a=i;
    }
  }
  /* Si en el bucle anterior ha detectado una lista con el texto introducido entrara en el siguiente bucle
  **que despues de introducir la tarea buscara si existe dicha tarea en la lista seleccionada y eliminara la tarea
  **en caso contrario nos dara error
  */
  if(b==1){
    cout << "Enter task name: ";
    getline(cin,t);
    for(unsigned int e=0;e<toDoList.lists[a].tasks.size();e++){
      if(t == toDoList.lists[a].tasks[e].name){
        toDoList.lists[a].tasks.erase(toDoList.lists[a].tasks.begin()+e);
        k=false;
        e=-1;
      }
    }
    if(k){
      error(ERR_TASK_NAME);
    }

  }else{
    error(ERR_LIST_NAME);
  }

}

void toggleTask(Project &toDoList){
  string p="list";
  string x;
  string t;
  int a;
  int b=0;
  int r=0;
  x=comprobar(p);
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    if(x == toDoList.lists[i].name){
      b=1;
      a=i;
    }
  }
  /*si se cumple que hay una lista igual al texto introducido se pedira una tarea
  **si coincide con alguna de las tareas de la lista cambiara el valor de isDone
  */
  if(b==1){
    cout << "Enter task name: ";
    getline(cin,t);
    for(unsigned int e=0;e<toDoList.lists[a].tasks.size();e++){
      if(t==toDoList.lists[a].tasks[e].name){
        if(toDoList.lists[a].tasks[e].isDone==false){
          toDoList.lists[a].tasks[e].isDone=true;
        }else{
          toDoList.lists[a].tasks[e].isDone=false;
        }
        r=1;
      }
    }
    if(r==0){
      error(ERR_TASK_NAME);
    }
  }else{
    error(ERR_LIST_NAME);
  }

}

void report(const Project &toDoList){
  int a=0;//variable para tareas incompletas
  int b=0;//variable para tareas completas
  int c=0;//v. para la suma de las tareas incompletas
  int d=0;//v. para la suma de las tareas completas
  Task compr;//esta variable la usaremos para el highest priority
  compr.deadline.year=ANYMAX;
  compr.deadline.month=13;
  compr.deadline.day=32;
  cout << "Name: " << toDoList.name << endl;
  if(!toDoList.description.size()){

  }else{
    cout << "Description: " << toDoList.description << endl;
  }
  //Se recorre todas las listas y sus tareas
  for(unsigned int i=0; i<toDoList.lists.size();i++){
    cout << toDoList.lists[i].name << endl;

    //Bucle que muestra las tareas incompletas de una lista
    for(unsigned int z=0; z<toDoList.lists[i].tasks.size();z++){
      if(toDoList.lists[i].tasks[z].isDone==false){
        cout << "[ ]" << " " << "(" << toDoList.lists[i].tasks[z].time << ") " << toDoList.lists[i].tasks[z].deadline.year << "-" << toDoList.lists[i].tasks[z].deadline.month;
        cout  << "-" << toDoList.lists[i].tasks[z].deadline.day << " : " << toDoList.lists[i].tasks[z].name << endl;
        a=a+1;
        c=c+toDoList.lists[i].tasks[z].time;
      }
    }

    //Bucle que muestra las tareas completas de la misma lista
    for(unsigned int z=0; z<toDoList.lists[i].tasks.size();z++){
      if(toDoList.lists[i].tasks[z].isDone==true){
        cout << "[X]" << " " << "(" << toDoList.lists[i].tasks[z].time << ") " << toDoList.lists[i].tasks[z].deadline.year << "-" << toDoList.lists[i].tasks[z].deadline.month;
        cout  << "-" << toDoList.lists[i].tasks[z].deadline.day << " : " << toDoList.lists[i].tasks[z].name << endl;
        b=b+1;
        d=d+toDoList.lists[i].tasks[z].time;
      }
    }
  }
  cout << "Total left: " << a << " (" << c << " minutes)" << endl;
  cout << "Total done: " << b << " (" << d << " minutes)" << endl;

  //si existe alguna tarea incompleta mostrara por pantalla la tarea mas prioritaria
  if(a>0){
    for(unsigned int i=0;i<toDoList.lists.size();i++){
      for(unsigned int z=0;z<toDoList.lists[i].tasks.size();z++){
        if(compr.deadline.year>toDoList.lists[i].tasks[z].deadline.year && toDoList.lists[i].tasks[z].isDone==false){
          compr=toDoList.lists[i].tasks[z];
        }else{
          if(compr.deadline.year==toDoList.lists[i].tasks[z].deadline.year && compr.deadline.month>toDoList.lists[i].tasks[z].deadline.month && toDoList.lists[i].tasks[z].isDone==false){
            compr=toDoList.lists[i].tasks[z];
          }else{
            if(compr.deadline.year==toDoList.lists[i].tasks[z].deadline.year && compr.deadline.month==toDoList.lists[i].tasks[z].deadline.month && compr.deadline.day>toDoList.lists[i].tasks[z].deadline.day && toDoList.lists[i].tasks[z].isDone==false){
              compr=toDoList.lists[i].tasks[z];
            }
          }
        }
      }
    }

    cout << "Highest priority: " << compr.name << " (" << compr.deadline.year << "-" << compr.deadline.month << "-" << compr.deadline.day << ")" << endl;
  }
  



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
