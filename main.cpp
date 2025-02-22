#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

int board[4][4];
            //{down , right , up , left }
int dirLine[]={1,0,-1,0};
int dirColumn[]={0,1,0,-1};

pair<int,int> generateUnOccupiedPosition() {
   int occupied=1,line,column;
   while(occupied){
      int line =rand()%4;
      int column=rand()%4;
      if(board[line][column]==0) occupied=0;
   }
   return make_pair(line,column);
}

void newGame(){
   for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
         board[i][j]=0;
      }
   }
   pair<int,int>pos=generateUnOccupiedPosition();
   board[pos.first][pos.second]=2;
}

void printUI(){
   for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
         if(board[i][j]==0) cout<<".";
         else cout<<board[i][j];
      }
      cout<<"\n";
   }

   cout<<"n: new game, w: up, s: down, d: right, a: left, q: quit \n";
}

bool canDoMove(int line,int column,int nextLine,int nextColumn){
   if(nextLine<0 || nextColumn<0 || nextLine>=4 || nextColumn>=4 || (board[line][column]!=board[nextLine][nextColumn] && board[nextLine][nextColumn]!=0)){
      return false;
   }
   return true;
}

void addPiece(){
   pair<int,int>pos=generateUnOccupiedPosition();
   board[pos.first][pos.second]=2;
}

void applyMove(int direction){
   int startLine=0,startColumn=0,lineStep=1,columnStep=1;
   if(direction==0){
      startLine=3;
      lineStep=-1;
   }
   if(direction==1){
      startColumn=3;
      columnStep=-1;
   }
   int movePossible=0;
   for(int i=startLine;i>=0 && i<4;i+=lineStep){
      for(int j=startColumn;j>=0 && j<4;j+=columnStep){
         int nextI=i+dirLine[direction],nextJ=j+dirColumn[direction];
         cout<<i<<" "<<j<<" "<<nextI<<" "<<nextJ<<"\n";
         if(canDoMove(i,j,nextI,nextJ)){
            board[nextI][nextJ]+=board[i][j];
            board[i][j]=0;
            movePossible=1;
         }
      }
   }
   if(movePossible){
      addPiece();
   }
}

int main(){
   srand(time(0));
   char commandToDir[128];
   commandToDir['s']=0;
   commandToDir['d']=1;
   commandToDir['w']=2;
   commandToDir['a']=3;
   newGame();
   while(true){
      printUI();
      char command;
      cin>>command;
      if(command=='n') newGame();
      if(command=='q') break;
      else{
         int currentDirection=commandToDir[command];
         cout<<currentDirection<<"\n";
         applyMove(currentDirection);
      }
   }
   return 0;
}