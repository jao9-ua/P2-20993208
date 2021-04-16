// DNI 20993208G Juan Andrés Orocondo ÁLvarez

#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <cstdlib>


using namespace std;

const int ANYMAX=2101; //Introducir el año deseado sumandole 1 para el correcto funcionamiento del programa
const int KMAXNAME=20;
const int KMAXDESC=40;

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

struct BinToDo{
  char name[KMAXNAME];
  unsigned numProjects;
  };

struct BinProject{
  char name[KMAXNAME];
  char description[KMAXDESC];
  unsigned numLists;
};

struct BinList{
  char name[KMAXNAME];
  unsigned numTasks;
};

struct BinTask{
  char name[KMAXNAME];
  Date deadline;
  bool isDone;
  int time;
};


struct ToDo{
  int nextId;
  string name;
  vector<Project> projects;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME,
  ERR_ID,
  ERR_PROJECT_NAME,
  ERR_FILE,
  ERR_ARGS
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
      break;
    case ERR_ID:
      cout << "ERROR: wrong project id" << endl;
      break;
    case ERR_PROJECT_NAME:
      cout << "ERROR: wrong project name" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
  }
}

void showProjectMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "b- Back to main menu" << endl
       << "Option: ";
}

void showMainMenu(){
  cout << "1- Project menu" << endl
       << "2- Add project" << endl
       << "3- Delete project" << endl 
       << "4- Import projects" << endl
       << "5- Export projects" << endl
       << "6- Load data" << endl
       << "7- Save data" << endl
       << "8- Summary" << endl
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

bool comprobarFecha(Task x){
  int mes;
  int dias_mes[]= {31, 28, 31, 30,31, 30, 31, 31, 30, 31, 30, 31};
  bool a=false;
  if(x.deadline.year>=2000 && x.deadline.year<ANYMAX){
    if((x.deadline.year % 4 == 0 and x.deadline.year % 100 != 0) or x.deadline.year % 400 == 0){
      dias_mes[1] = dias_mes[1] + 1;
    }
    if(x.deadline.month>=1 && x.deadline.month<=12){
      mes = x.deadline.month-1;
      if(x.deadline.day>=1 && x.deadline.day<=dias_mes[mes]){
        a=true;
      }else{
        error(ERR_DATE);
      }
    }else{
      error(ERR_DATE);
    }
  }else{
    error(ERR_DATE);
  }
  return a;
}

bool comprobarTiempo(Task x){
  bool a=false;
  if(x.time>=1 && x.time <=180){
    a=true;
  }else{
    error(ERR_TIME);
  }
  return a;
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
  Task x;
  int b=0;
  char q;
  char c;
  int a;
  bool corr=false;
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
    corr= comprobarFecha(x);
    if(corr){
      cout << "Enter expected time: ";
      cin >> x.time;
      corr=comprobarTiempo(x);
      if(corr){
        x.isDone=false;
        toDoList.lists[a].tasks.push_back(x);
      }
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

void projectMenu(ToDo &x){
  int id;
  cout << "Enter project id: ";
  cin >> id;
  for(unsigned int i=0;i<x.projects.size();i++){
    if(id==x.projects[i].id){
      char option;
      do{
        showProjectMenu();
        
        cin >> option;
        cin.get();
        
        switch(option){
          case '1': editProject(x.projects[i]);
                    break;
          case '2': addList(x.projects[i]);
                    break;
          case '3': deleteList(x.projects[i]);
                    break;
          case '4': addTask(x.projects[i]);
                    break;
          case '5': deleteTask(x.projects[i]);
                    break;
          case '6': toggleTask(x.projects[i]);
                    break;
          case '7': report(x.projects[i]);
                    break;
          case 'b': break;
          default: error(ERR_OPTION);
        }
      }while(option!='b');
    }
  }

}
void addProject(ToDo &x){
  string compr="project";
  Project proyecto;
  bool a=true;
  proyecto.name=comprobar(compr);
  for(unsigned int i=0;i<x.projects.size();i++){
    if(proyecto.name==x.projects[i].name){
      a=false;
    }
  }
  if(a){
    cout <<"Enter project description: ";
    getline(cin,proyecto.description);
    proyecto.id=x.nextId;
    x.nextId++;
    x.projects.push_back(proyecto);
  }else{
    error(ERR_PROJECT_NAME);
  }
}
void deleteProject(ToDo &x){
  int id;
  bool a=true;
  cout <<"Enter project id: ";
  cin >> id;
  for(unsigned int i=0; i<x.projects.size();i++){
    if(id==x.projects[i].id){
      x.projects.erase(x.projects.begin()+i);
      a=false;
    }
  }
  if(a){
    error(ERR_ID);
  }
}

void importProject(ToDo &x){
  string nombreFichero;
  char comprobar;
  ifstream f1;
  string texto;
 
  cout <<"Enter filename: ";
  getline(cin,nombreFichero);
  f1.open(nombreFichero.c_str());
  if(f1.is_open()){
    f1 >> comprobar;
    do{
      if(comprobar=='>'){
        f1 >> comprobar;
      }
      while(comprobar=='<'){
        f1 >> comprobar;
        if(comprobar=='#'){
          Project fun;
          getline(f1,texto);
          fun.name=texto;
          f1 >> comprobar;
          if(comprobar=='*'){
            getline(f1,texto);
            fun.description=texto;
            f1 >> comprobar;
          }
          while(comprobar=='@'){
            List lista;
            char a;
            string q;
            bool corr;
            char completo;
            comprobar='\0';
            getline(f1,texto);
            lista.name=texto;
            while(a!='@' && comprobar!='>'){
              Task tarea;
              while(a!='|'){
                if(a==comprobar){
                  tarea.name +=a;
                }
                f1.get(a);
                if(a!='|'){
                  tarea.name +=a;
                }
                
              }
              f1 >> tarea.deadline.day >> a >> tarea.deadline.month >> a >> tarea.deadline.year;
              corr= comprobarFecha(tarea);
              if(corr){
                f1 >> a >> completo >> a >> tarea.time;
                corr=comprobarTiempo(tarea);
                if(corr){
                  if(completo=='T'){
                    tarea.isDone=true;
                    lista.tasks.push_back(tarea);
                  }else{
                    tarea.isDone=false;
                    lista.tasks.push_back(tarea);
                  }
                }
              }
              f1 >> comprobar;
              a=comprobar;
            }
            a='\0';
            fun.lists.push_back(lista);
          }
          fun.id=x.nextId;
          x.nextId++;
          x.projects.push_back(fun);
        }
       
      }
    }while(!f1.eof());
    f1.close();
  }else{
    error(ERR_FILE);
  }
}
void exportProject(ToDo &x){
  char guardar;
  int id;
  bool a;
  bool existe=false;
  string nF;
  ofstream fichero;
  string str;
  do{
    cout << "Save all project [Y/N]?:";
    cin >> guardar;
  }while(guardar!='Y' && guardar!='y' && guardar!='N' && guardar!='n');
  cin.ignore();
  if(guardar=='N' || guardar=='n'){
    cout << "Enter project id: ";
    cin >> id;
    a=true;
    cin.ignore();
  }
 
  if(a){
    for(unsigned int i=0;i<x.projects.size();i++){
      if(id==x.projects[i].id){
        existe=true;
      }
    }
  }
  if(existe || guardar=='Y' || guardar=='y'){
    cout <<"Enter filename: ";
    getline(cin, nF);
    fichero.open(nF.c_str());
    if(fichero.is_open()){
      if(existe){
        for(unsigned int d=0;d<x.projects.size();d++){
          if(id==x.projects[d].id){
            fichero << x.projects[d].name << endl;
            fichero << x.projects[d].description << endl;
            for(unsigned int i=0;i< x.projects[d].lists.size();i++){
              fichero << x.projects[d].lists[i].name << endl;
              for(unsigned int a=0;a<x.projects[d].lists[i].tasks.size();a++){
                fichero << x.projects[d].lists[i].tasks[a].name << "|" << x.projects[d].lists[i].tasks[a].deadline.day << "/";
                fichero << x.projects[d].lists[i].tasks[a].deadline.month << "/";
                fichero << x.projects[d].lists[i].tasks[a].deadline.year << "|";
                if(x.projects[d].lists[i].tasks[a].isDone){
                  fichero << "T" << "|";
                }else{
                  fichero << "F" << "|";
                }
                fichero << x.projects[id].lists[i].tasks[a].time << endl;
              }
            }
          }
        }
      }else{
        for(unsigned int d=0;d<x.projects.size();d++){
          fichero << x.projects[d].name << endl;
          fichero << x.projects[d].description << endl;
          for(unsigned int i=0;i<x.projects[d].lists.size();i++){
            fichero << x.projects[d].lists[i].name << endl;
            for(unsigned int a=0;a<x.projects[d].lists[i].tasks.size();a++){
              fichero << x.projects[d].lists[i].tasks[a].name << "|";
              fichero << x.projects[d].lists[i].tasks[a].deadline.day << "/";
              fichero << x.projects[d].lists[i].tasks[a].deadline.month << "/";
              fichero << x.projects[d].lists[i].tasks[a].deadline.year << "|";
              if(x.projects[d].lists[i].tasks[a].isDone){
                fichero << "T" << "/";
              }else{
                fichero << "F" << "/";
              }
              fichero << x.projects[d].lists[i].tasks[a].time << endl;
            }
          }
        }
      }
      fichero.close();
    }else{
      error(ERR_FILE);
    }
  }else{
    error(ERR_ID);
  }
}

void loadData(ToDo &x){
  string nombreFichero;
  BinToDo p;
  BinProject project;
  BinList lista;
  BinTask tarea;
  
  char comp;
  cout << "Enter filename: " << endl;
  getline(cin, nombreFichero);
  ifstream fichero(nombreFichero.c_str(),ios::in | ios::binary);
  if(fichero.is_open()){
    do{
      cout << "Confirm[Y/N]?: ";
      cin >> comp;
    }while(comp!='Y' && comp!='y' && comp!='X' && comp!='x');
    if(comp=='Y' || comp=='y'){
      x.projects.clear();
      x.name.clear();
      fichero.read((char *)&p, sizeof(p));
      x.name=p.name;

      for(unsigned int i=0;i<p.numProjects;i++){
        Project proyecto;
        fichero.read((char*)&project, sizeof(project));
        proyecto.name=project.name;
        proyecto.description=project.description;

        for(unsigned int b=0;b<project.numLists;b++){
          List listp;
          fichero.read((char*)&lista, sizeof(lista));
          listp.name=lista.name;

          for(unsigned int z=0;z<lista.numTasks;z++){
            Task tareap;
            fichero.read((char*)&tarea, sizeof(tarea));
            tareap.name=tarea.name;
            tareap.deadline.day=tarea.deadline.day;
            tareap.deadline.month=tarea.deadline.month;
            tareap.deadline.year=tarea.deadline.year;
            tareap.isDone=tarea.isDone;
            tareap.time=tarea.time;
            listp.tasks.push_back(tareap);

          }
          proyecto.lists.push_back(listp);
        }
        proyecto.id=x.nextId;
        x.nextId++;
        x.projects.push_back(proyecto);
      }

    }
    fichero.close();
    }else{
      error(ERR_FILE);
    }
  }
void saveData(ToDo &x){
  string nombreFichero;
  ofstream fichero;
  BinToDo p;
  BinProject project;
  BinList lista;
  BinTask tarea;

  cout << "Enter filename: ";
  getline(cin,nombreFichero);
  fichero.open(nombreFichero.c_str(),ios::binary);
  if(fichero.is_open()){
    strncpy(p.name,x.name.c_str(),KMAXNAME-1);
    p.name[KMAXNAME-1]='\0';
    p.numProjects=x.projects.size();
    fichero.write((const char *)&p, sizeof(p));

    for(unsigned int i=0;i<x.projects.size();i++){
      strncpy(project.name,x.projects[i].name.c_str(),KMAXNAME-1);
      project.name[KMAXNAME-1]='\0';

      strncpy(project.description,x.projects[i].description.c_str(),KMAXDESC-1);
      project.description[KMAXDESC-1]='\0';

      fichero.write((const char *)&project, sizeof(project));

      project.numLists=x.projects[i].lists.size();

      for(unsigned int d=0;d<x.projects[i].lists.size();d++){
        strncpy(lista.name,x.projects[i].lists[d].name.c_str(),KMAXNAME-1);
        lista.name[KMAXNAME-1]='\0';

        fichero.write((const char *)&lista, sizeof(lista));

        lista.numTasks=x.projects[i].lists[d].tasks.size();

        for(unsigned int z=0;z<x.projects[i].lists[d].tasks.size();z++){
          strncpy(tarea.name,x.projects[i].lists[d].tasks[z].name.c_str(),KMAXNAME-1);
          tarea.name[KMAXNAME-1]='\0';
          tarea.deadline.day=x.projects[i].lists[d].tasks[z].deadline.day;
          tarea.deadline.month=x.projects[i].lists[d].tasks[z].deadline.month;
          tarea.deadline.year=x.projects[i].lists[d].tasks[z].deadline.year;
          tarea.isDone=x.projects[i].lists[d].tasks[z].isDone;
          tarea.time=x.projects[i].lists[d].tasks[z].time;

          fichero.write((const char *)&tarea, sizeof(tarea));
        }
      }
    }
  }else{
    error(ERR_FILE);
  }
}
void summary(ToDo &x){
  int contadortareas=0;
  int contadorHechas=0;
  for(unsigned int i=0;i<x.projects.size();i++){
    cout << "(" << x.projects[i].id <<") "<< x.projects[i].name;
    for(unsigned int b=0;b<x.projects[i].lists.size();b++){
      for(unsigned int z=0;z<x.projects[i].lists[b].tasks.size();z++){
        if(x.projects[i].lists[b].tasks[z].isDone){
          contadorHechas=contadorHechas+1;
          contadortareas=contadortareas+1;
        }else{
          contadortareas=contadortareas+1;
        }
      }
    }
    cout << " [" << contadorHechas << "/" << contadortareas << "]" << endl;
  }
}


int main(){
  char option;
  ToDo x;
  x.nextId = 1;
  x.name = "My ToDo list";

  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': projectMenu(x);
                break;
      case '2': addProject(x);
                break;
      case '3': deleteProject(x);
                break;
      case '4': importProject(x);
                break;
      case '5': exportProject(x);
                break;
      case '6': loadData(x);
                break;
      case '7': saveData(x);
                break;
      case '8': summary(x);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}
