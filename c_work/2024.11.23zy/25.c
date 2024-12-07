#include <stdio.h>
#include <string.h>
#define MAXLINE 1000
int mygetlines(char s[],int lim){
    int i,c;
    i=0;
    while (--lim>0 && (c=getchar())!=EOF && c!='\n')
        s[i++]=c;
    if (c=='\n')
        s[i++]='\n';
    s[i]='\0';
    return i;
}
int main(int argc,char *argv[]){
    char line[MAXLINE];
    long lineno=0;
    int c,except=0,number=0,found=0,num=0;
    int fl=0;
    while(--argc>0 && (*++argv)[0]=='-'){
        while(c=*++argv[0]){
            if (c>='1'&&c<='9'){
                num=c-'0';
                continue;
                fl=1;
            }
            switch(c){
                case 'x':
                    except=1;break;
                case 'n':
                    number=1;break;
                default:
                    if (fl==0) printf("ERROR %c\n",c);
                    argc=0;found=-1;break;
            }
        }
    }
    if (num==0) num=1;
   // printf("%s\n",*argv);
    if (argc!=1&&fl==0){
        printf("Usage: find -x -n pattern");
    }else{
        while(mygetlines(line,MAXLINE)>0){
            ++lineno;
            int su=0;
            for (int i=0;i<strlen(line)-1;i++){
                int f=0;
                if (line[i]==(*argv)[0]){
                    for (int j=0;j<strlen(*argv);j++){
                       // printf("!");
                       // printf("%c %c\n",line[i+j],(*argv)[j]);
                        if (line[i+j]!=(*argv)[j]||line[i+j]=='\0') {
                            f=1;break;
                            }
                    }
                     if (f==0)su++;
                }
            }
           // printf("%d\n",su);
            if (except==0){
                if (su>=num){
                    if (number){
                        printf("%ld:",lineno);
                    }
                    printf("%s\n",line);
                    found++;
                }
            }
            else{
                if (su<num){
                    if (number){
                        printf("%ld:",lineno);
                    }
                    printf("%s\n",line);
                    found++;
                }
            }
        }
    }
    return found;
}