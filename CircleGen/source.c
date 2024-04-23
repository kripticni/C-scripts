#include <stdio.h>
#include <stdlib.h>

int main(){
    int radius=20;
    int penDown[10]={7, 5, 3, 2, 2 ,1 , 1, 0, 0, 0 };
    //implement SIZE being equal to radius/2+1 if radius%2==1 and SIZE = radius / 2 if not
    int i, j;
    int inc=1;
    int save=0;
    char primary;
    int toggled=0;
    
    printf("Put primary: ");
    scanf(" %c", &primary);
    //primary = 'W';
    char secondary = ' ';
    printf("\n");
    int flag=radius%2;
    
    for(i=0;i<radius;i++){
        j=0;
        while(j!=penDown[save]){
                putchar(secondary);
                putchar(secondary);
                j++;
            }
        while(j!=radius-penDown[save]){
                putchar(primary);
                putchar(primary);
                j++;
            }
            
            if (toggled==0 && save==(radius/2)-1+flag){
                if(flag==0)save++;
                inc=-1;
                toggled=1;
            }
            save=save+ inc;
    printf("\n");
    
    }
    return 0;
}
