struct Edge {
  ll v, u, flow, cap;
};

struct Dinic {
  vector<Edge> edges;
  vector<int> g[N];
  ll dist[N]; 
  int ptr[N];
  bool used[N];

  void add_edge(int v, int u, int cap) {
    edges.push_back({v, u, 0, cap});
    edges.push_back({u, v, 0, 0});
    int num = edges.size();
    g[v].push_back(num - 2);
    g[u].push_back(num - 1);
  }

  bool bfs(int st, int en, int n) {
    fill(dist, dist + n, INF);
    dist[st] = 0;
    queue<int> q;
    q.push(st);
    while (q.size()) {
      int v = q.front();
      q.pop();
      for (auto i: g[v]) {
        if (edges[i].flow < edges[i].cap && dist[edges[i].u] == INF) {
          dist[edges[i].u] = dist[v] + 1;
          q.push(edges[i].u);
        }
      }
    }
    return dist[en] != INF;
  }

  ll dfs(int v, ll flow, int en) {
    if (v == en) return flow;
    while (ptr[v] < (int)g[v].size()) {
      int edgenum = g[v][ptr[v]];
      int u = edges[edgenum].u;
      if (dist[v] != dist[u] - 1) {
        ptr[v]++;
        continue;
      }
      ll added = 0;
      if (edges[edgenum].cap > edges[edgenum].flow)
        added = dfs(u, min(flow, edges[edgenum].cap - edges[edgenum].flow), en);
      if (added) {
        edges[edgenum].flow += added;
        edges[edgenum ^ 1].flow -= added;
        return added;
      }
      ptr[v]++;
    }
    return 0;
  }

  ll dinic(int n, int st, int en) {
    ll ansFlow = 0;
    while (true) {
      bool ok = bfs(st, en, n);
      fill(ptr, ptr + n, 0);
      if (!ok) break;
      while (true) {
        ll added = dfs(st, INF, en);
        if (!added)
          break;
        else
          ansFlow += added;
      }
    }
    return ansFlow;
  }
};
