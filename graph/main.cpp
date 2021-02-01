#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

// adjacency table
// weight 0 will be considered as no edge
float adj[20][20];
//labels
char labels[20];
// added
bool vadded[20];
//add edge
void addedge(int from, int to, float weight){
	adj[from - 1][to - 1] = weight;
}
//remove vertex
void remvert(int num){
	for(int i = 0; i<20; i++){
		adj[num - 1][i] = 0;
		adj[i][num - 1] = 0;
	}
}
//remove edge
void remedge(int from, int to){
	adj[from - 1][to - 1] = 0;
}
//dijkstra algorithm
void path(int from, int to){
	bool visited[20]; // true if vertex is visited, false if not
	float dist[20]; // effective distance from start node, 0 will mean no connection
	for(int i=0; i<20; i++){
		visited[i] = false;
		if(i + 1 == from){
			dist[i] = 0;
		}
		else{
			dist[i] = adj[from - 1][i];
		}
	}
	for(int i=0; i<20; i++){
		for(int j=0; j<20; j++){
			if(dist[i] != 0 && adj[i][j] != 0 && (dist[j] == 0 || dist[j] > dist[i] + adj[i][j])){
				dist[j] = dist[i]+adj[i][j];
			}
		}
		visited[i] = true;
	}
	if(dist[to-1] != 0){
		cout << "The minimum distance from vertex " << from << " to " << to << " is "<< dist[to-1]<< endl;
}
	else{
		cout << "There is no path from vertex " <<from << " to " << to << endl;
	}
}
//search
int search(char lab){
	int i=0;
	bool quit = false;
	while(i<20 && quit == false){
		if(labels[i]==lab && vadded[i] == true){
			return i;
			quit = true;
		}
		else{
			i++;
		}
	}
	return 88; // not found
}
int main(){
	for(int i=0; i<20;i++){
		vadded[i] = false;
		labels[i] = 'a';
		for(int j=0;j<20;j++){
			adj[i][j] = 0;
		}
	}
	bool quit = false;
	while(quit == false){
	cout <<"Welcome to graph creator! Would you like to print (PR), add vertex (AV), remove vertex (RV), add edge (AE), remove edge (RE), or find a shortest path (SP)? Or quit (Q). ";
	char input[5];
	cin >> input;
	if(strcmp(input, "AV") == 0){
		bool added = false;
		int i = 0;
		while(added == false && i<20){
			if(vadded[i]==false){
				added = true;
				vadded[i] = true;
			}
			else{
				i++;
			}
		}
		cout << "Give the vertex a character label: ";
		char lab;
		cin >> lab;
		labels[i] = lab;
		if(added == true){
		cout <<endl <<"Vertex Added." << endl;
		}
		else{
		cout << "No more vertices for you, 20 is the max" << endl;
		}
	}
	else if(strcmp(input, "RV") == 0){
		cout << "remove which vertex? ";
		char uservertex;
		cin >> uservertex;
		remvert(search(uservertex));
		vadded[search(uservertex)] = false;
	}
	else if(strcmp(input, "AE") == 0){
		cout << "Specify the edge you would like to add." << endl;
		cout << "Start vertex: ";
		char from;
		cin >> from;
		cout << endl << "End vertex: ";
		char to;
		cin >> to;
		cout << endl << "Weight: ";
		float weight;
		cin >> weight;
		addedge(search(from)+1, search(to)+1, weight);
	}
	else if(strcmp(input, "RE") == 0){
		cout << "Specify the edge you would like to remove." << endl;
		cout << "Start vertex: ";
		char from;
		cin >> from;
		cout << endl << "End vertex: ";
		char to;
		cin >> to;
		remedge(search(from)+1, search(to)+1);
	}
	else if(strcmp(input, "SP") == 0){
		cout << "What path do you want to find?" << endl;
		cout << "Start vertex: ";
		char from;
		cin >> from;
		cout << endl << "End vertex: ";
		char to;
		cin >> to;
		path(search(from)+1, search(to)+1);
	}
	else if(strcmp(input, "PR") == 0){
		cout << "      ";
		for(int i=0; i<20; i++){
			if(vadded[i] == true){
			cout << left << setw(8) << setfill(' ') << labels[i];
			}
			else{
			cout << left << setw(8) << setfill(' ') << " "; 
			}
		}
		cout << endl;
		for(int i=0; i<20; i++){
			if(vadded[i] == true){
			cout << left << setw(8) << setfill(' ') << labels[i];
			}
			else{
			cout << left << setw(8) << setfill(' ') << " ";
			}
			for(int j=0; j<20; j++){
				if(adj[i][j] != 0){
				cout << left << setprecision(3) << setw(8) << setfill(' ') << adj[i][j];
				}
				else{
				cout << left << setw(8) << setfill(' ') << " ";
				}
			}
			cout << endl;
		}
	}
	else{
		quit = true;
	}
	}
	return 0;
}
