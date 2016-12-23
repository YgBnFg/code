#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#define Mn 50005
int no;
struct Point {
	int d[6];
	bool operator <(const Point &x) const {
		return d[no] > x.d[no];
	}
};

std::priority_queue<std::pair<double, Point> > q;
class Kd_tree {
public:
	int k;
	int num;
	Point tp[Mn<<2],p[Mn];
	int leaf[Mn << 2] = {0};
	void init(int n,int m);
	void build(int l,int r,int u,int de);
	void query(Point ans, int u, int de);
};
void Kd_tree::init(int n, int K) {
	this->k = K;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < K; j++) {
			scanf("%d", &p[i].d[j]);
		}
	}
}
void Kd_tree::build(int l, int r, int u, int de) {
	if (l > r) return;
	leaf[u] = 0;
	leaf[u << 1] = leaf[u << 1 | 1] = 1;
	int mid = (l + r) >> 1;
	no = de%k;
	std::nth_element(p + l, p + mid, p + r+1);
	tp[u] = p[mid];
	build(l, mid-1, u << 1, de + 1);
	build(mid + 1, r, u << 1 | 1, de + 1);
}

void Kd_tree::query(Point ask, int u, int de) {
	if (leaf[u]) return;
	std::pair<double, Point> tmp(0,tp[u]);
	for (int i = 0; i < k; ++i) {
		tmp.first += (ask.d[i] - tp[u].d[i])*(ask.d[i] - tp[u].d[i]);
	}
	int kno = de%k;
	int left = u << 1, right = left + 1;
	if (ask.d[kno] > tp[u].d[kno]) std::swap(left,right);
	if(!leaf[u]) query(ask, left, de+1);
	if (q.size() < num) {
		q.push(tmp);
		if (!leaf[u]) query(ask, right, de + 1);
	}
	else {
		if (tmp.first < q.top().first) {
			q.pop();
			q.push(tmp);
		} 
		if ((ask.d[kno] - tp[u].d[kno]) * (ask.d[kno] - tp[u].d[kno]) < q.top().first)
			if (!leaf[u]) query(ask, right, de + 1);
	}
}
std:: vector<Point> ans;
int main() {
	Kd_tree *kd=new Kd_tree;
	int n, K;
	while (~scanf("%d%d", &n, &K)) {
		kd->init(n, K);
		kd->build(1, n, 1, 0);
		int t;
		scanf("%d", &t);
		while (t--) {
			Point ask;
			ans.clear();
			for (int i = 1; i <= K; i++) {
				scanf("%d", &ask.d[i]);
			}
			int m;
			scanf("%d", &kd->num);
			while (!q.empty()) q.pop();
			kd->query(ask, 1, 0);
			while (!q.empty()) {
				ans.push_back(q.top().second);
				q.pop();
			}
			for (int i = ans.size()-1; i >= 0; --i) {
				for (int j = 0; j < K-1; ++j) {
					printf("%d ", ans[i].d[j]);
				}
				printf("%d\n", ans[i].d[K-1]);
			}
		}
	}
	delete kd;
	kd = NULL;
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