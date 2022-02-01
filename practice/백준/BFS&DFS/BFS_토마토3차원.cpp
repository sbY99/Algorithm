/*
#include <iostream>
#include <queue>
using namespace std;

void bfs();

struct XYZ{
    int x;
    int y;
    int z;
};

queue<struct XYZ>q;

// H, N, M
int grid[101][101][101];

//가로, 세로, 높이
int M,N,H;
int result;

int main(){
    cin >> M >> N >> H;
    for(int i=0;i<H;i++){
        for(int j=0;j<N;j++){
            for(int k=0;k<M;k++){
                scanf("%d",&grid[i][j][k]);
                if(grid[i][j][k]==1){
                    q.push({k,j,i});
                }
            }
        }
    }
    bfs();
    
    int result=1;
    
    for(int i=0;i<H;i++){
        for(int j=0;j<N;j++){
            for(int k=0;k<M;k++){
                if(grid[i][j][k]==0){
                    printf("-1");
                    return 0;
                }
                if(grid[i][j][k]>result){
                    result=grid[i][j][k];
                }
            }
        }
    }
    
    printf("%d",result-1);
    
    return 0;
}

void bfs(){
    
    while(q.size()){
        auto c=q.front();
        q.pop();
        
        int dx[]={-1,1,0,0,0,0};
        int dy[]={0,0,1,-1,0,0};
        int dz[]={0,0,0,0,1,-1};
        
        for(int i=0;i<6;i++){
            int nx=c.x+dx[i];
            int ny=c.y+dy[i];
            int nz=c.z+dz[i];
            
            if(!(0<=nx&&nx<M&&0<=ny&&ny<N&&0<=nz&&nz<H)){
                continue;
            }
            if(grid[nz][ny][nx]==0){
                grid[nz][ny][nx] = grid[c.z][c.y][c.x] + 1;
                q.push({nx,ny,nz});
            }
        }
    }
}
*/