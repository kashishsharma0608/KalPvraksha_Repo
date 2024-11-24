#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define leng 100
int isop(char a){
      return (a == '+' || a == '-' || a == '*' || a == '/');
}
int op_pre(char ch){
     if (ch == '+' || ch == '-') {
        return 1;
    } 
    if (ch == '*' || ch == '/') {
        return 2;
    }
    return -1;
}
int evaluate(int a,int b,char c){
    switch(c){
        case '+':return a+b;
        case '-':return a-b;
        case '*':return a*b;
        case'/':
        if(b==0){
            printf("error:division by zero");
            exit(1);
        }
        else{
            return a/b;
        }
    }
    return 0;
}
int calculate_result(char str[leng]){
    int values[leng];
    int valt=0,op=0;
    char operator[leng];
    int n=strlen(str);
    for(int i=0;i<n;i++){
                if (isspace(str[i])) {
            continue;
        }

        if(isdigit(str[i])){
            int val=0;
            while(i<n&&isdigit(str[i])){
                val=val*10+(str[i]-'0');
                 i++;
            }
           
        
        i--;
        values[valt++]=val;
        }
        else if(isop(str[i])){
            while(op>0&&op_pre(operator[op-1])>=op_pre(str[i])){
                  int val2=values[--valt];
            int val1=values[--valt];
            char o=operator[--op];
            values[valt++]=evaluate(val1,val2,o);
            }
          operator[op++]=str[i];
        }
        else{
            printf("Invalid Expression");
            exit(1);
        }
    }
    while(op>0){
       int val2=values[valt--];
            int val1=values[valt--];
            char o=operator[op--];
            values[valt++]=evaluate(val1,val2,o); 
    }
   
    return values[--valt];

}
int main(){
   
 char str[leng];
    printf("Enter expression: ");
    fgets(str, leng, stdin);
    str[strcspn(str, "\n")] = '\0';  

    
    int result=calculate_result(str);
    printf("Result%d",result);
    return 0;
}