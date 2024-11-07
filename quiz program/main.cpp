/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <cstring>
#include <time.h>

using namespace std;

class Exercise{
    //private variables for thee objext Exercise
    private:
    int leftOperand ,rightOperand ,op ,maxValue ,minValue ;
    public:
    //costructor that sees if the min is bigger than the max it gives them the values(min=0,max=10) 
    //then it gives random values to the left and right operands between min and max   
    Exercise(int min=0, int max=10){
        if(min>=max){
            min=0;
            max=10;
        }
        minValue=min;
        maxValue=max;
        leftOperand=(rand()%(max-min+1))+min;
        rightOperand=(rand()%(max-min+1))+min;
        op=(rand()%2)+1;
    }
    //a functions that returns result according to the (op)
    int eval(){
        if(op==1)
            return leftOperand+rightOperand;
        else
            return leftOperand-rightOperand;
    }
    //a function that returns the equation according to the (op)
    string toString(){
        if(op==1){
            return to_string(leftOperand)+" + "+to_string(rightOperand)+" = ";
        }
        else{
            return to_string(leftOperand)+" - "+to_string(rightOperand)+" = ";
        }
    }
};

class ExGenerator{
    //private variables for the class ExGenerator
    private:
    Exercise** exercises;
    int numOfEx,current;
    public:
    //constructor that see how many exercises we have and what is the min and the max for the exercises
    //and it begins every Exercise according to the min and the max by calling its constructor
    //if there is no size or the size is minus it gives it size=10
    ExGenerator(int size = 10, int min = 0, int max = 10){
        if(size<=0){
            size=10;
        }
        numOfEx=size;
        exercises=new Exercise*[numOfEx];
        srand(time(NULL));
        for(int i=0;i<size;i++){
            exercises[i]=new Exercise(min,max);
        }
        current=0;
    }
    //getter for the numOfEx
    int getNumOfEx() const{
        return numOfEx;
    }
    //getter for the current
    int getCurrent() const {
        return current;
    }
    //a function that gives us the next question and add one to the current
    Exercise* next() {
        current=current+1;
        if(current>numOfEx){
            return NULL;
        }
        return exercises[current-1];
    }
    //a function that sees if we reached the end of the questions or not
    bool endOfEx() {
        if(current>numOfEx){
            return true;
        }
        return false;
    }
    //a destructor that deletes every Exercise in the pointer exercises then it deletes the pointer 
    //exercises
    ~ExGenerator(){
        for(int i=0;i<numOfEx;i++){
            delete exercises[i];
        }
        delete exercises;
    }
};

class MathQuiz{
    private:
    ExGenerator* ques;
    Exercise** questions;
    int* userAnswers;
    public:
    MathQuiz(int size = 10, int min = 0, int max = 10){
        ques =new ExGenerator(size,min,max);
        questions = new Exercise*[size];
        userAnswers=new int[size];
    }
    void startQuiz(){
        char* ch=new char[100];
        char* ch2=new char[100];
        Exercise* y;
        int answer;
        int correct=0;
        char saving;
        string filePath;
        string fileName="result";
        int fileNum;
        for(int i=0;i<ques->getNumOfEx();i++){
            y=ques->next();
            questions[i]=y;
            cout<<y->toString();
            cin>>answer;
            //cout<<"\n";
            userAnswers[i]=answer;
            if(answer==y->eval()){
                cout<<"correct";
                correct++;
            }
            else{
                cout<<"wrong";
            }
            if(i!=ques->getNumOfEx()-1)
                cout<<"\n";
        }
        cout<<"\nThe quiz has ended. You got "<<correct<<" correct answers out of "<<ques->getNumOfEx()
        <<"\n";
        cout<<"Would you like to save the results? (press y or n)\n";
        cin>>saving;
        srand(time(NULL));
        if(saving=='y'){
            cout<<"please enter file path:\n";
            cin>>filePath;
            fileNum=(rand()%900)+100;
            fileName=filePath+fileName+to_string(fileNum)+".txt";
            strcpy(ch, fileName.c_str());
            //cout<<fileName;
            FILE* fp=fopen(ch,"w");
            if(fp==NULL)
                exit(0);
            fprintf(fp,"Results for the quiz:\n");    
            for(int m=0;m<ques->getNumOfEx();m++){
                //ch=questions[m]->toString();
                strcpy(ch2, (questions[m]->toString()).c_str());
                fprintf(fp,"%s",ch2);
                fprintf(fp,"%d",questions[m]->eval());
                fprintf(fp," your answer %d\n",userAnswers[m]);
            }
            fprintf(fp,"You got %d correct answers out of %d exercises.",correct,ques->getNumOfEx());
            fclose(fp);
            cout<<"Your results where saved in "<<fileName<<"\n";
        }
        cout<<"goodbye\n";
    }
    ~MathQuiz(){
        delete userAnswers;
        for(int i=0;i<ques->getNumOfEx();i++){
            delete questions[i];
        }
        delete ques;
        delete questions;
    }
};

int main()
{
    //MathQuiz mq(3,5,10);
    //mq.startQuiz();
    //MathQuiz mq2(6,-3,16);
    //mq2.startQuiz();
   cout<<"Welcome to the math quiz"<<endl;
   cout<<"You’ll get 3 exercises"<<endl;
   MathQuiz mq(3);
   mq.startQuiz();
   MathQuiz mq1(3,5,10); 
   mq1.startQuiz();
   return 0;
}






