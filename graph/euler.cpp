// Laufzeit: O(|V|+|E|)
vector< vector<int> > adjlist;
vector< vector<int> > otherIdx;
vector<int> cycle;
vector<int> validIdx;

void swapEdges(int n, int a, int b) { // Vertauscht Kanten mit Indizes a und b von Knoten n.
	int neighA = adjlist[n][a];
	int neighB = adjlist[n][b];
	int idxNeighA = otherIdx[n][a];
	int idxNeighB = otherIdx[n][b];
	swap(adjlist[n][a], adjlist[n][b]);
	swap(otherIdx[n][a], otherIdx[n][b]);
	otherIdx[neighA][idxNeighA] = b;
	otherIdx[neighB][idxNeighB] = a;
}

void removeEdge(int n, int i) { // Entfernt Kante i von Knoten n (und die zugehörige Rückwärtskante).
	int other = adjlist[n][i];
	if (other == n) { //Schlingen.
		validIdx[n]++;
		return;
	}
	int otherIndex = otherIdx[n][i];
	validIdx[n]++;
	if (otherIndex != validIdx[other]) {
		swapEdges(other, otherIndex, validIdx[other]);
	}
	validIdx[other]++;
}

// Findet Eulerzyklus an Knoten n startend.
// Teste vorher, dass Graph zusammenhängend ist! Was ist mit isolierten Knoten?
// Teste vorher, ob Eulerzyklus überhaupt existiert!
void euler(int n) {
	while (validIdx[n] < (int)adjlist[n].size()) {
		int nn = adjlist[n][validIdx[n]];
		removeEdge(n, validIdx[n]);
		euler(nn);
	}
	cycle.push_back(n); // Zyklus am Ende in cycle (umgekehrte Reihenfolge).
}
