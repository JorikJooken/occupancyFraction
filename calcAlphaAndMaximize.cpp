#include <bits/stdc++.h>

// Unsafe because no defined behaviour if character = 0. ctz and clz work with 32 bit numbers.
#define unsafePrev(character, current) (__builtin_ctz(character) - current >= 0 ? -1 : current -__builtin_clz((character) << (32 - current)) - 1)

#define prev(character,current) (character ? unsafePrev(character,current) : -1)

using namespace std;

const int nb_bits=64;
#define MAXVERTICES 64

int getNumberOfVertices(string graphString) 
{
	if(graphString.size() == 0){
        printf("Error: String is empty.\n");
        abort();
    }
    else if((graphString[0] < 63 || graphString[0] > 126) && graphString[0] != '>') {
    	printf("Error: Invalid start of graphstring.\n");
    	abort();
    }

	int index = 0;
	if (graphString[index] == '>') { // Skip >>graph6<< header.
		index += 10;
	}

	if(graphString[index] < 126) { // 0 <= n <= 62
		return (int) graphString[index] - 63;
	}

	else if(graphString[++index] < 126) { 
		int number = 0;
		for(int i = 2; i >= 0; i--) {
			number |= (graphString[index++] - 63) << i*6;
		}
		return number;
	}

	else if (graphString[++index] < 126) {
		int number = 0;
		for (int i = 5; i >= 0; i--) {
			number |= (graphString[index++] - 63) << i*6;
		}
		return number;
	}

	else {
		printf("Error: Format only works for graphs up to 68719476735 vertices.\n");
		abort();
	}
}

void loadGraph(string graphString, int numberOfVertices, long long adjacencyList[]) {
	int startIndex = 0;
	if (graphString[startIndex] == '>') { // Skip >>graph6<< header.
		startIndex += 10;
	}
	if (numberOfVertices <= 62) {
		startIndex += 1;
	}
	else if (numberOfVertices <= MAXVERTICES) {
		startIndex += 4;
	}
	else {
		printf("Error: Program can only handle graphs with %d vertices or fewer.\n",MAXVERTICES);
		abort();
	}

	for (int vertex = 0; vertex < numberOfVertices; vertex++) { //Initialize adjacencyList.
		adjacencyList[vertex] = 0;
	}

	int currentVertex = 1;
	int sum = 0; 
	for (int index = startIndex; index<graphString.size(); index++) {
		int i;
		for (i = prev(graphString[index] - 63, 6); i != -1; i = prev(graphString[index] - 63, i)) {
			while(5-i+(index-startIndex)*6 - sum >= 0) {
				sum += currentVertex;
				currentVertex++;
			}
			sum -= --currentVertex;
			int neighbour = 5-i+(index - startIndex)*6 - sum;
            adjacencyList[currentVertex]|=(1LL<<neighbour);
            adjacencyList[neighbour]|=(1LL<<currentVertex);
		}
	}
}

#define left_shifted(n,x) ((n)<<(x))
#define set_bit(n,i) ((n)|=left_shifted(1LL,i))
#define count_bits(n) (__builtin_popcountll((n)))
//#define index_rightmost_bit(n) (count_bits((n)^(n-1))-1)
#define index_rightmost_bit(n) (__builtin_ctzll(n))
#define rightmost_bit_removed(n) ((n)&((n)-1))
#define traverse_through_neighbors_nest1(x,neighbor) for(long long (neighbor)=index_rightmost_bit((x)),DESTROYED_MASK1=(x); (DESTROYED_MASK1)!=0; (DESTROYED_MASK1)=rightmost_bit_removed((DESTROYED_MASK1)),(neighbor)=index_rightmost_bit((DESTROYED_MASK1)))
#define traverse_through_neighbors_nest2(x,neighbor) for(long long (neighbor)=index_rightmost_bit((x)),DESTROYED_MASK2=(x); (DESTROYED_MASK2)!=0; (DESTROYED_MASK2)=rightmost_bit_removed((DESTROYED_MASK2)),(neighbor)=index_rightmost_bit((DESTROYED_MASK2)))

int n;
long long adjacencyList[MAXVERTICES];

long long ret;

double MAXLAMBDA=100.0;
const int MAXPARTS=1000;
double bestAlpha[MAXPARTS];
string argBest[MAXPARTS];

long long totNum[MAXVERTICES];
int numSelected;

string line;

double calcAlpha(double lambda)
{
    double ret=lambda/n;
    double P=0;
    for(int i=0; i<=n; i++)
    {
        double amount=totNum[i];
        for(int j=0; j<i; j++)
        {
            amount*=lambda;
        }
        P+=amount;
    }
    double P_prime=0;
    for(int i=0; i<=n; i++)
    {
        double amount=totNum[i]*((long long)i);
        for(int j=0; j<i-1; j++)
        {
            amount*=lambda;
        }
        P_prime+=amount;
    }
    return ret*P_prime/P;
}

void recursiveCount(long long availableMask)
{
    if(availableMask==0)
    {
        ret++;
        totNum[numSelected]++;
        return;
    }
    long long u=index_rightmost_bit(availableMask);
    availableMask=(availableMask^(1LL<<u));
    // choose u as part of independent set
    long long newAvailableMask=(availableMask&(~adjacencyList[u]));
    numSelected++;
    recursiveCount(newAvailableMask);
    numSelected--;
    // do not choose u
    recursiveCount(availableMask);
    return;
}

void countNumberOfIndependentSets()
{
    ret=0;
    long long availableMask=(1LL<<n)-1;
    for(int i=0; i<=n; i++) totNum[i]=0;
    numSelected=0;
    recursiveCount(availableMask);
    for(int i=1; i<=MAXPARTS; i++)
    {
        double lambda=(1.0*i/MAXPARTS)*MAXLAMBDA;
        double alpha=calcAlpha(lambda);
        if(alpha>bestAlpha[i-1])
        {
            bestAlpha[i-1]=alpha;
            argBest[i-1]=line;
        }
    }
    return; 
}

// The program expects as input a list of graphs (in graph6 format)
// The program will compute the occupancy fraction alpha(lambda) for these graphs for lambda=0.1, 0.2, ..., 100.0 and
// it will output for each lambda which graph has the largest occupancy fraction
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long nb_graphs_read_from_input=0;
    for(int i=0; i<MAXPARTS; i++)
    {
        bestAlpha[i]=-1e50;
    }
    while(getline(cin,line))
    {
        //line+="\n";
        nb_graphs_read_from_input++;
        n = getNumberOfVertices(line);
        loadGraph(line,n,adjacencyList);
        //cerr << "Graph loaded!" << endl;
        // continue here later
        countNumberOfIndependentSets();
    }
    for(int i=0; i<MAXPARTS; i++)
    {
        cout << argBest[i] << endl;
        cout << fixed << setprecision(12) << bestAlpha[i] << endl;
    }
    cerr << nb_graphs_read_from_input << " graphs were read from input" << endl;
    return 0;
}
