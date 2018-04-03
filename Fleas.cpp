// FleaCircus

#include <iostream>
#include <vector>

using namespace std;


int position1, position2;
vector<int> path;
vector<vector<int> > adjacentList;
vector<bool> visit;
bool getResult = false;
void findPath(int vertex){
    if(vertex == (position2-1)){
        getResult = true;
        return;
    }
    for(int i=0; i<adjacentList[vertex].size(); i++){
        int adjacentVertex = adjacentList[vertex][i];
        if(!visit[adjacentVertex]){
            path.push_back(adjacentVertex);
            visit[adjacentVertex] = true;      
            findPath(adjacentVertex);
        }
        if( getResult ) return;
    }
    path.pop_back();  
    return;
}

int main()
{
    int n;

    // Problem says: "The input file contains multiple test cases"
    // So, while we are reading the input, we can test when we've run out of input
    while(cin >> n && n) {
        // start to read (n-1) line of connectivity information
        for(int i = 0; i < n; i++) {
            vector<int> temp(1);
            temp.pop_back();
            adjacentList.push_back(temp);
            visit.push_back(false); 
        } 

        for(int i = 1; i < n; i++) {
            int a, b;
            cin >> a >> b;
            // implment a tree using adjacent list
            // vector<int> temp = ;
            // temp.push_back(b);
            adjacentList[a-1].push_back(b-1);
            adjacentList[b-1].push_back(a-1);   
        }

        // in the (n+1)'th line we have the number of starting positions
        int l;
        cin >> l;

        // start to read l lines of pairs of positions
        for(int i = 1; i <= l; i++) {
            cin >> position1 >> position2;

            // now you have connectivity information
            // and two positions
            // todo: implement your code to check to print appropriate message
            getResult = false;
            path.push_back(position1-1);
            visit[position1-1] = true;
            findPath(position1-1);
            int pathSize = path.size();
            if(pathSize % 2 == 1){
                int meetPosition = pathSize/2;
                printf("The fleas meet at %d.\n", path[meetPosition]+1);
            }
            else{
                int jumpPosition = (pathSize-1)/2;
                int min = path[jumpPosition+1] < path[jumpPosition] ? path[jumpPosition+1] : path[jumpPosition];
                int max = path[jumpPosition+1] > path[jumpPosition] ? path[jumpPosition+1] : path[jumpPosition];
                printf("The fleas jump forever between %d and %d.\n", min+1, max+1);
            }
            path.clear();
            for(int i = 0; i < n; i++) {
                visit[i] = false;
            }
        }
        adjacentList.clear();
    }
    return 0;
}