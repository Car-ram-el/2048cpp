#include <bits/stdc++.h>
#define chmpn(i,l,r) for(int i=l; i<r; ++i)
#define prime(i,r,l) for(int i=r; i>=l; --i)
#define rgx(a,b) for(auto &a:b)

using namespace std;

void up(int a[4][4]){
    chmpn(j,0,4){
        int c=0; // current tile being considered
        chmpn(i,1,4) if(a[i][j]) if(!a[i-1][j] || a[i-1][j]==a[i][j]){ // possible
            if(a[c][j]==a[i][j]) a[c][j]*=2; 
            else{
                if(!a[c][j]) a[c][j]=a[i][j]; // when c is empty, others shift
                else a[++c][j]=a[i][j]; // else bring the tile up just below current
            } a[i][j]=0;
        } else c++; // tiles can't move up, change c
    }
}
void down(int a[4][4]){
    chmpn(j,0,4){
        int c=3;
        prime(i,2,0) if(a[i][j]) if(!a[i+1][j] || a[i+1][j]==a[i][j]){
            if(a[c][j]==a[i][j]) a[c][j]*=2;
            else if(!a[c][j]) a[c][j]=a[i][j]; 
            else a[--c][j]=a[i][j];
            a[i][j]=0;
        } else c--;
    }
}
void left(int a[4][4]){
    chmpn(i,0,4){
        int c=0;
        chmpn(j,1,4) if(a[i][j]) if(!a[i][j-1] || a[i][j-1]==a[i][j]){
            if(a[i][c]==a[i][j]) a[i][c]*=2;
            else if(!a[i][c]) a[i][c]=a[i][j];
            else a[i][++c]=a[i][j];
            a[i][j]=0;
        } else c++;
    }
}
void right(int a[4][4]){
    chmpn(i,0,4){
        int c=3;
        prime(j,2,0) if(a[i][j]) if(!a[i][j+1] || a[i][j]==a[i][j+1]){
            if(a[i][c]==a[i][j]) a[i][c]*=2;
            else if(!a[i][c]) a[i][c]=a[i][j];
            else a[i][--c]=a[i][j];
            a[i][j]=0;
        } else --c;
    }
}
void add(int a[4][4]){
    int i,j;
    srand(time(0)); // starting point of random number generation is current time, which returns different seconds/number in every run 👍👍
    while(1){
        i=rand()%4, j=rand()%4;
        if(!a[i][j]){
            a[i][j]=pow(2,i%2+1); // first, third row=2 else 4
            break;
        }
    }
}
void display(int a[4][4]){
    cout << "\n\n\tPress Ctrl+C to quit anytime you want.\n\n";
    chmpn(i,0,4){
        cout << "\t_____________________________\n\t";
        chmpn(j,0,4) if(!a[i][j]) cout << "|      "; 
            else{
                int n=a[i][j]; cout << "| ";
                if(int(log10(n))==0) cout << " " << n << "  " ;
                else if(int(log10(n))==1) cout << " " << n << " ";
                else if(int(log10(n))==2) cout << n << " ";
                else cout << n;
            } cout << " |\n";
    }
}
bool check(int temp[4][4], int a[4][4]){ return temp==a;}
int over(int a[4][4]){
    chmpn(i,0,4) chmpn(j,0,4) if(!a[i][j]) return 0;
    chmpn(i,0,3) chmpn(j,0,3) if(a[i][j]==a[i+1][j] || a[i][j]==a[i][j+1]) return 0;
    return 1;
}
int main(){
    cout << "\t2048\n\n\n\tPress 'w/a/s/d' for directions\n\tPress any key to continue"; getchar(); // key press
    system("cls"); // to clear console
    int a[4][4]={0},temp[4][4]={0};
    srand(time(0)); int n=rand()%4,o=rand()%4,p,q;
    while (1){ // indices for initial '2 and 4'
        p=rand()%4,q=rand()%4;
        if(n!=p && o!=q) break;
    } a[n][o]=2,a[p][q]=4; display(a);
    int c; // ascii character for keypress
    while (1){
        chmpn(i,0,4) chmpn(j,0,4) temp[i][j]=a[i][j]; // store current grid state in temp
        c=getchar(); system("cls");
        if(c=='w') up(a); if(c=='a') left(a); if(c=='d') right(a); if(c=='s') down(a);
        if(!check(temp,a)) add(a); // if after the move grid changed, add a block
        display(a);
        if(over(a)){
            cout << "\tGame over.\n";
            getchar(); break;
        }
    }
    return 0;
}