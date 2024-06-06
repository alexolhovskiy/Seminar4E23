#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct charSteck{
    char oper;
    int priority;
    struct charSteck*next;
} charSteck;

int getRange(int n){
    int cnt=0;
    while(n>0){
        n/=10;
        cnt++;
    }
    //printf("%d\n",cnt);
    return cnt;
}

char*getStrFromNum(int n){
    int i=0;
    char*numStr=(char*)malloc(getRange(n));
    while(n>0){
        numStr[i]=n%10+48;
        n/=10;
        i++;
    }
    numStr[i]=' ';
    numStr[i+1]='\0';
    //printf("%s\n",numStr);
    return numStr;
}



void myprint(charSteck*begin){
    while(begin!=NULL){
        printf("%c",begin->oper);
        begin=begin->next;
    }
    printf("\n");
}

int getPriority(char c){
    switch(c){
        case '&':return 3;break;
        case '^':return 2;break;
        case '|':return 1;break;
        case '(':return 0;break;
    }
    return 0;
}

charSteck* push(charSteck*begin,char o){
    charSteck*p=(charSteck*)malloc(sizeof(charSteck));
    p->oper=o;
    p->priority=getPriority(o);
    p->next=begin;
    begin=p;
    return begin;
}

charSteck* pop(charSteck*begin){
    if(begin!=NULL){
        charSteck*p;
        p=begin;
        begin=begin->next;
        p->next=NULL;
        free(p);
    }
    return begin;
}



charSteck*steckCheck(charSteck*begin,char c,char*res){
    if(begin->next!=NULL){
        //printf("Check %d",begin->priority);
        if(getPriority(c)<=begin->priority){

            //printf("Strlen before %d\n",strlen(res));
            int size=strlen(res);
            res[size]=begin->oper;
            res[size+1]=' ';
            res[size+2]='\0';
            //printf("Strlen after %d\n",strlen(res));
            begin=pop(begin);
            begin=steckCheck(begin,c,res);
        }
    }
    return begin;
}

charSteck* add(charSteck*begin,char c,char*res){
    //printf("Add");
    begin=steckCheck(begin,c,res);
    begin=push(begin,c);
    return begin;
}

charSteck* popAll(charSteck*begin,char*res){
    //printf("popAll");
    while(begin->next!=NULL){
        int size=strlen(res);
        res[size]=begin->oper;
        res[size+1]=' ';
        res[size+2]='\0';
        begin=pop(begin);
    }
    return begin;
}

charSteck* popTillBracket(charSteck*begin,char*res){
    //printf("Till");
    while(begin->oper!='('){
        int size=strlen(res);
        res[size]=begin->oper;
        res[size+1]=' ';
        res[size+2]='\0';
        begin=pop(begin);
    }
    return pop(begin);
}


char* analisis(char*str){
    int i=0,val=0;
    char*res=(char*)malloc(255);
    res[0]='\0';

    charSteck*begin=(charSteck*)malloc(sizeof(charSteck));
    begin->next=NULL;

    while(str[i]!=' '){
        if(str[i]>='0'&&str[i]<='9'){
            val=10*val+str[i]-48;
        }else{
            switch(str[i]){
                case '(':begin=push(begin,str[i]);break;
                case ')':
                    strcat(res,getStrFromNum(val));
                    val=0;
                    begin=popTillBracket(begin,res);
                    break;
                default:
                    strcat(res,getStrFromNum(val));
                    val=0;
                    //printf("Strlen %d\n",strlen(res));
                    begin=add(begin,str[i],res);
            }
        }
        i++;
    }
    strcat(res,getStrFromNum(val));
    begin=popAll(begin,res);
    return res;
}


int main()
{
    printf("Hello world!\n");
    //2
    //char str[]="3|4^5&7|3 ";//3457&^|3|
    //char str[]="3|(4^5)&7|3 ";
    //char str[]="8^2&5|(6&1) ";
    char str[]="(3&5)^4|9 ";
    printf("%s\n",str);
    printf("%s\n",analisis(str));


    return 0;
}
