// Laufzeit: O(n*min(ans^2, |E|)) 
// Kanten von links nach rechts. Die ersten n Knoten sind links, die anderen rechts.
vector<vector<int>> adjlist;
vector<int> pairs; // Der gematchte Knoten oder -1.
vector<bool> visited;

bool dfs(int v) {
	if (visited[v]) return false;
	visited[v] = true;
	for (auto w : adjlist[v]) if (pairs[w] < 0 || dfs(pairs[w])) {
		pairs[w] = v; pairs[v] = w; return true;
	}
	return false;
}

int kuhn(int n) { // n = #Knoten links.
	pairs.assign(NUM_VERTICES, -1);
	int ans = 0;
	// Greedy Matching. Optionale Beschleunigung.
	for (int i = 0; i < n; i++) for (auto w : adjlist[i])
		if (pairs[w] == -1) { pairs[i] = w; pairs[w] = i; ans++; break;	}
	for (int i = 0; i < n; i++) if (pairs[i] == -1) {
		visited.assign(n, false);
		ans += dfs(i);
	}
	return ans; // Größe des Matchings.
}
