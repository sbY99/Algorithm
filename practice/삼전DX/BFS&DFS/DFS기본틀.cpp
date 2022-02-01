/*

DFS - 재귀
int Graph[Max_N][Max_N];
bool Visited[Max_N];

void dfs(int node)
{
    Visitied[node] = true;

    for(int next =0; next < N; ++next){
        if(!Visited[next] && Graph[node][next]){
            dfs(next);
        }
    }
}

*/

/*

DFS - 반복
int Graph[Max_N][Max_N];
int Stack[Stack_SIZE], Top;

void dfs(int node){
    bool visited[MAX_N] = {false};
    Top = -1;
    Stack[++Top] = node;
    while(Top != -1){
        int cur = Stack[Top--];
        if(!visited[cur]){
            visited[cur] = true;

            for(int next=0;next<N;++next){
                if(!visited[next] && Graph[cur][next]){
                    Stack[++Top] = next;
                }
            }
        }
    }
}

*/