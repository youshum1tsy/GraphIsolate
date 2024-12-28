#include <iostream>
#include <vector>
int main() {
  const int vertex = 9;
  const int edges = 16;
  int incidence[vertex][edges] = {
       {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
       {1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
       {0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
       {0,0,1,0,1,0,0,0,1,1,1,0,0,0,0,0},
       {0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0},
       {0,0,0,0,0,1,0,0,0,1,0,0,1,0,1,0},
       {0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1},
       {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
       {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1}};
  
  /*
  const int vertex = 4;
  const int edges = 5;
  int incidence[vertex][edges] = {
    {1,0,0,0,0},
    {1,1,1,1,0},
    {0,0,1,0,0},
    {0,0,0,1,1}};
  */

  std::vector<std::vector<int>> sets;
  std::vector<std::vector<int>> answer;
  for (int e = 0; e < edges; e++) {
    std::vector<int> vertexSet;
    for (int v = 0; v < vertex; v++) {    
      if (incidence[v][e] == 1) {
        vertexSet.push_back(v);
      }
    }
    sets.push_back(vertexSet);
  }

for (int i = 0; i < sets.size(); i++) {
    std::vector<int> edgesSet;
    bool add = true;
    while (add) {
        add = false;
        for (int j = i; j < sets.size(); j++) {
            bool flag = true;
            for (int edge : edgesSet) {
                for (int v1 : sets[edge]) {
                    for (int v2 : sets[j]) { 
                        if (v1 == v2) {
                            flag = false;
                            break;
                        }
                    }
					if (!flag) {
						break;
					}  
                }
				if (!flag) {
						break;
				} 
                
            }
            if (flag) {
                edgesSet.push_back(j);
				answer.push_back(edgesSet);
                add = true;
            }
        }
    }
}
  
  for (std::vector<int> set : answer) {
    for (int edges : set) {
      std::cout << edges << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
