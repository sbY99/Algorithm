
/*
일반 BFS

int Graph[MAX_N][MAX_N];
int Queue[QUEUE_SIZE], Front, Rear;

void bfs(int node){
    bool visitied[MAX_N] = {false};
    Front = Rear = -1;
    visited[node] = true;
    Queue[++Rear] = node;
    while(Front != Rear) {
        int curr = Queue[++Front];
        //Visit curr node

        for(int next=0; next <N; ++next){
            if(!visitied[next] && Graph[curr][next]){
                visited[next] = true;
                Queue[++Rear] = next;
            }
        }
    }
}


/*


/*
최단 경로 구하는 BFS(위와 구조 동일)

int Graph[MAX_N][MAX_N];
int Queue[QUEUE_SIZE], Front, Rear;
int Dist[MAX_N];

void bfs(int node){
    bool visitied[MAX_N] = {false};
    Dist[node] = 0;
    Front = Rear = -1;
    visited[node] = true;
    Queue[++Rear] = node;
    while(Front != Rear) {
        int curr = Queue[++Front];
        //Visit curr node

        for(int next=0; next <N; ++next){
            if(!visitied[next] && Graph[curr][next]){
                visited[next] = true;
                Queue[++Rear] = next;
                //방문 순서대로 0~N까지 인덱스에 쌓임
                Dist[next] = Dist[curr] + 1;
            }
        }
    }
}
*/
