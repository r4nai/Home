//#define BFS 1 //Если закоментированно, будет выполняться DFS, иначе BFS
#define _CRT_SECURE_NO_WARNINGS
#define push_back pb
#define make_pair mp
#define first ff
#define second ss

#include <bits\stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

#define MAXV 1000

struct enode
{
	int u;
	enode *next;
};

struct graph
{
	enode *edges[MAXV] = { 0 };
	int nvertices;
	int nedges;
};

void insert(graph *g, int v, int u)
{
	enode *new_edge = new enode;
	new_edge->u = u;
	new_edge->next = g->edges[v];
	g->edges[v] = new_edge;
}

void read(graph *g)
{
	cin >> g->nvertices >> g->nedges;
	int u, v;
	for (int i = 0; i < g->nedges; ++i)
	{
		cin >> u >> v;
		--u;
		--v;
		insert(g, u, v);
		insert(g, v, u);
	}
}

void erase_edge(enode *edge)
{
	if (edge != NULL)
	{
		erase_edge(edge->next);
		delete edge;
	}
}

void erase_all(graph *g)
{
	for (int i = 0; i < g->nedges; ++i)
		erase_edge(g->edges[i]);
}

void print(graph *g)
{
	for (int i = 0; i < g->nvertices; ++i)
	{
		cout << i + 1 << ':';
		for (enode *edge = g->edges[i]; edge != NULL; edge = edge->next)
			cout << ' ' << edge->u + 1;
		cout << endl;
	}

}

vi used(MAXV, 0);

void push(enode **head, int u)
{
	enode *t = new enode;
	t->u = u;
	t->next = *head;
	*head = t;
}

void dfs(graph *g, int start, enode **comps)
{
	used[start] = true;
	push(comps, start);
	for (enode *edge = g->edges[start]; edge != NULL; edge = edge->next)
	{
		if (!used[edge->u])
			dfs(g, edge->u, comps);
	}
}

void bfs(graph *g, int start, enode **comps)
{
	queue<int> q;
	q.push(start);
	used[start] = true;
	push(comps, start);
	for (; !q.empty();)
	{
		int v = q.front();
		q.pop();
		for (enode *edge = g->edges[v]; edge != NULL; edge = edge->next)
		{
			int to = edge->u;
			if (!used[to])
			{
				used[to] = true;
				push(comps, to);
				q.push(to);
			}
		}
	}
}

void components(graph *g)
{
	int k = 0;
	enode *comps = NULL;
	used.resize(MAXV, 0);
	for (int i = 0; i < g->nvertices; ++i)
	{
		if (!used[i])
		{
			erase_edge(comps);
			comps = NULL;
			++k;
#ifdef BFS
			bfs(g, i, &comps);
#else
			dfs(g, i, &comps);
#endif
			cout << "Component " << k << ':' << endl;
			for (enode *edge = comps; edge != NULL; edge = edge->next)
				cout << edge->u + 1 << ' ';
			cout << endl;
		}
	}
	erase_edge(comps);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(false);
	cout.tie(false);
#ifdef _DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	graph *g = new graph;
	read(g);
	print(g);
	components(g);
	erase_all(g);
	return 0;
}