#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#define Mn 50005
int no;
struct Point {
	int d[6];
	bool operator <(const Point x) const {
		return d[no] > x.d[no];
	}
};

std::priority_queue<std::pair<double, Point> > q;
class Kd_tree {
public:
	int k;
	Point tp[Mn<<2],p[Mn];
	int leaf[Mn << 2] = {0};
	void init(int n,int m);
	void build(int l,int r,int u,int de);
	void query(Point ans,int m, int u, int de);
};
void Kd_tree::init(int n, int K) {
	this->k = K;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= K; j++) {
			scanf("%d", &p[i].d[j]);
		}
	}
}
void Kd_tree::build(int l, int r, int u, int de) {
	leaf[u] = 0;
	if (l > r) return;
	int mid = (l + r) >> 1;
	no = de%k;
	std::nth_element(p + l, p + mid, p + r+1);
	tp[u] = p[mid];
	if (l == r) {
		leaf[u] = 1;
	}
	build(l, mid-1, u << 1, de + 1);
	build(mid + 1, r, u << 1 | 1, de + 1);
}

void Kd_tree::query(Point ask,int m, int u, int de) {
	if (leaf[u]) return;
	std::pair<double, Point> tmp(0,tp[u]);
	for (int i = 1; i <= k; ++i) {
		tmp.first += (ask.d[i] - tp[u].d[i])*(ask.d[i] - tp[u].d[i]);
	}
	no = de%k;
	int left = u << 1, right = left + 1;
	if (ask.d[no] > tp[u].d[no]) std::swap(left,right);
	query(ask,m, left,de+1);
	if (q.size() < m) {
		q.push(tmp);
		query(ask, m, right, de + 1);
	}
	if (tmp.first < q.top().first) {
		q.pop();
		q.push(tmp);
	} else if ((ask.d[no] - tp[u].d[no]) * (ask.d[no] - tp[u].d[no])<q.top().first) 
		query(ask, m, right, de + 1);
}
Kd_tree kd;
int main() {
	int n, K;
	scanf("%d%d",&n,&K);
	kd.init(n, K);
	kd.build(1, n, 1, 0);
	int t;
	scanf("%d", &t);
	while(t--) {
		Point ans;
		for (int i = 1; i <= K; i++) {
			scanf("%d",&ans.d[i]);
		}
		int m;
		scanf("%d", &m);
		while (!q.empty()) q.pop();
		kd.query(ans, m, 1, 0);
		while (!q.empty()) {
			Point a = q.top().second;
			q.pop();
			for (int i = 1; i <= K; i++) {
				std::cout << a.d[i] << " ";
			}
			std::cout << std::endl;
		}
	}
	return 0;
}
/*
3 2
1 1
1 3
3 4
2
2 3
2
2 3
1

*/