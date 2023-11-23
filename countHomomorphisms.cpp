#include <bits/stdc++.h>
#include <stdio.h>
//#include "long long.h"
#include <math.h>

using namespace std;

// Unsafe because no defined behaviour if character = 0. ctz and clz work with 32 bit numbers.
#define unsafePrev(character, current) (__builtin_ctz(character) - current >= 0 ? -1 : current -__builtin_clz((character) << (32 - current)) - 1)

#define prev(character,current) (character ? unsafePrev(character,current) : -1)

#define MAXVERTICES 32

//  Returns an empty long long. 
#define EMPTY (long long) 0LL

//  Returns a long long containing only node.
#define singleton(node) ((long long) 1LL << (node))

//  Returns the union of set1 and set2.
#define union(set1, set2) (((unsigned long long) set1) | ((unsigned long long) set2))

//  Returns the intersection of set1 and set2.
#define intersection(set1, set2) (((unsigned long long) set1) & ((unsigned long long) set2))

//  Adds node to set.
#define add(set, node) ((set) = union(((unsigned long long) set),singleton(node)))

//  Returns set1\set2 (set difference).
#define difference(set1, set2) (((unsigned long long) set1) & ~((unsigned long long) set2))

//  Removes node from set.
#define removeElement(set, node) ((set) = difference(((unsigned long long) set), singleton(node)))

//  Check if set is empty.
#define isEmpty(set) (((unsigned long long) set) == 0)

//  Returns the size of the set.
#define sz(set) (__builtin_popcountll((unsigned long long) set))

//	Check if set1 equals set2.
#define equals(set1, set2) (((unsigned long long) set1) == ((unsigned long long) set2))

//	Loops over all elements of the set. 
#define forEach(element, set) for (int element = next(((unsigned long long) set), -1); (element) != -1; (element) = next(((unsigned long long) set), (element)))

//	Loops over all elements of the set starting from start (not included). 
#define forEachAfterIndex(element, set, start) for (int element = next(((unsigned long long) set), (start)); (element) != -1; (element) = next(((unsigned long long) set), (element)))

//  Returns -1 if the set is empty. Otherwise it executes unsafeNext(set, current).
#define next(set, current)  (isEmpty((unsigned long long) set) ? -1 : unsafeNext(((unsigned long long) set), (current)) ) //the builtin clz and ctz compiler functions have unexpected behavior at zero.

// Returns the first element after current in the set. If there are no more elements after current, it returns -1. 
// Unsafe because the behaviour when the set is empty is not guaranteed.
#define unsafeNext(set, current) (__builtin_clzll((unsigned long long) set) + (current) >= 63 ? -1 : (current) + __builtin_ctzll(((unsigned long long) set) >> ((current) + 1)) + 1)

//  Checks whether node is an element of set.
#define contains(set, node) (!isEmpty(intersection(((unsigned long long) set), singleton(node))))

//	Take the complement of a set in a universe consisting of sizeOfUniverse elements. 
//	E.g.: complement of {0,2} if there are only 4 elements is {1,3} and not 64-bit complement. 
#define complement(set, sizeOfUniverse) (~((unsigned long long) set) << (64-(sizeOfUniverse)) >> (64-(sizeOfUniverse)))

#define MAXHORDER 128
long long adjacencyListH[MAXHORDER];
int nVerticesH;

#define MAXGORDER 128
long long adjacencyListG[MAXGORDER];
int nVerticesG;

string graphString;
size_t size;


static long long oldAvailableColorsAtIteration[MAXGORDER][MAXGORDER]; // might be wrong if n is close to MAXVERTICES
static long long availableColors[MAXGORDER];
static int colorOfVertex[MAXGORDER];
static long long adjacentColorBitset[MAXHORDER];
static long long notColoredYetBitset;

map< pair<string, long long>, pair<double, string> > bestMap;

// Checks whether G is H-colorable
// this function should only be called from within the function "isHColorableHelper"
long long countHomRec(int iterationCounter, int highestColorUsed)
{
    if(equals(notColoredYetBitset,EMPTY)) return 1;

    // search for vertex with fewest number of colors available
    int min_nb_colors_available=nVerticesH+5;
    int argmin=-1;
    forEach(u,notColoredYetBitset)
    {
        int amount=sz(availableColors[u]);
        if(amount<min_nb_colors_available)
        {
            min_nb_colors_available=amount;
            argmin=u;
        }
    }
    // try to color that vertex
    long long ret=0;
    forEach(color,availableColors[argmin])
    {
        //if(color>=highestColorUsed+2) return 0;
        //fprintf(stderr,"Trying to color vertex %d with color %d\n",argmin,color);
        long long oldAvailableColorsArgmin=availableColors[argmin];
        availableColors[argmin]=singleton(color);
        removeElement(notColoredYetBitset,argmin);
        // update neighbor availabilites        
        forEach(neigh,(intersection(adjacencyListG[argmin],notColoredYetBitset)))
        {
            oldAvailableColorsAtIteration[iterationCounter][neigh]=availableColors[neigh];
            availableColors[neigh]=(intersection(availableColors[neigh],adjacentColorBitset[color]));
        }
        int newHighestColorUsed=highestColorUsed;
        if(color>highestColorUsed) newHighestColorUsed=color;
        ret+=countHomRec(iterationCounter+1,newHighestColorUsed);
        // restore neighbor availabilities
        forEach(neigh,(intersection(adjacencyListG[argmin],notColoredYetBitset)))
        {
            availableColors[neigh]=oldAvailableColorsAtIteration[iterationCounter][neigh];
        }
        availableColors[argmin]=oldAvailableColorsArgmin;
        add(notColoredYetBitset,argmin);
    }
    return ret;
}


long long countHom()
{
    if(nVerticesG<=2) return 1; // bogus value, does not work correctly for such small graphs
    for(int i=0;i<nVerticesH;i++)
    {
        adjacentColorBitset[i]=adjacencyListH[i];
    }
    for(int i=0; i<nVerticesG; i++) availableColors[i]=complement(EMPTY,nVerticesH);
    notColoredYetBitset=complement(EMPTY,nVerticesG);
    int startVertex=0; // change me later; e.g. choose vertex with smallest degree, largest degree or some other heuristic
    return countHomRec(0,-1);
}

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

// reads pairs of graphs H and G and it will count the number of homomorphism from G to H
int main(int argc, char ** argv) {
    int parity=0;
    string HLine;
    while(getline(cin,graphString)) {
        if(parity==0)
        {
            HLine=graphString;
            nVerticesH = getNumberOfVertices(graphString);
            loadGraph(graphString, nVerticesH, adjacencyListH);

            // remove later
            /*for(int i=0; i<nVerticesH; i++)
            {
                add(adjacencyListH[i],i);
            }*/
        }
        else
        {
            nVerticesG = getNumberOfVertices(graphString);
            loadGraph(graphString, nVerticesG, adjacencyListG);
            //for(long long invMask=0; invMask<(1LL<<nVerticesH); invMask++)
	    for(long long invMask=0; invMask<=0; invMask++)
            //for(long long invMask=(1LL<<nVerticesH)-1; invMask<=(1LL<<nVerticesH)-1; invMask++)
            {
                for(int i=0; i<nVerticesH; i++)
                {
                    if(invMask&(1LL<<i))
                    {
                        add(adjacencyListH[i],i);
                    }
                }

                long long nbHom=countHom();
		cerr << "nbHom: " << nbHom << endl;
                double normalizedNbHom=pow(((double)nbHom),1.0/nVerticesG);
		cerr << "normalizedNbHom: " << normalizedNbHom << endl;
                pair<string, long long> pa1=make_pair(HLine,invMask);
                pair<double, string> pa2=make_pair(normalizedNbHom,graphString);
                if(bestMap.count(pa1)==0)
                {
                    bestMap[pa1]=pa2;
                }
                else
                {
                    bestMap[pa1]=max(bestMap[pa1],pa2);
                }

                for(int i=0; i<nVerticesH; i++)
                {
                    if(invMask&(1LL<<i))
                    {
                        removeElement(adjacencyListH[i],i);
                    }
                }
            }
        }
        parity=1-parity;
    }
    for(auto &pa1 : bestMap)
    //for(pair<string, long long> &pa1 : bestMap)
    {
        //cout << pa1.first.first << " " << pa1.first.second << endl;
        cout << pa1.first.first << endl;
        cout << "Best: " << pa1.second.second << endl;
	cout << "Corresponding: " << pa1.second.first << endl;
    }
    return 0;
}
