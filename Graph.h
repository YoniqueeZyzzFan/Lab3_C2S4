#include <vector>
#include <string>
#include <iostream>

// ������� + ��������
template <typename TVertex>
struct Info {
	int color = 0;
	TVertex current;
	TVertex prev;
	int step;
};

struct Edge {
	std::string dest;
	double length;
	Edge(): dest(""),length(-1) {}
	Edge(const std::string& dst, const double& l) :length(l), dest(dst) {}
	bool operator ==(const Edge& rhs) const{
		if (this->dest != rhs.dest || this->length != rhs.length) return false;
		else return true;
	}
};
struct Vertex {
	std::string id;
	size_t amount;
	Vertex(const std::string& str, const size_t& am): id(str),amount(am){}
	bool operator==(const Vertex& rhs) const {
		if (this->id != rhs.id || this->amount != rhs.amount) return false;
		else return true;
	}
};
template <typename TVertex, typename TEdge>
class Graph {
	std::vector<std::vector<TEdge>> edge;
	std::vector<TVertex> vertex;
	size_t count;
	bool check(std::vector<TVertex>& tmp, const std::string& str) const {
		for (size_t i = 0; i < tmp.size(); ++i) {
			if (str == tmp[i].id) return true;
		}
		return false;
	}
	int checker(const std::string& str) const {
		for (size_t i = 0; i < vertex.size() - 1; ++i) {
			if (str == vertex[i].id) return i;
		}
		return -1;
	}
	bool dfs(const size_t curr_ind, const TVertex& dst, std::vector<TVertex>& tmp) const {
		if (tmp[tmp.size() - 1] == dst) return true;
		for (size_t k = 0; k < edge[curr_ind].size(); ++k) {
			if (tmp[tmp.size() - 1] == dst) return true;
			if (check(tmp, edge[curr_ind][k].dest) == true) continue;
			int take_id = checker(edge[curr_ind][k].dest);
			tmp.push_back(vertex[take_id]);
			dfs(take_id, dst, tmp);
		}
		if (tmp[tmp.size() - 1] == dst) return true;
		else return false;
	}
public:
	Graph() {
		count = 0;
	}
	bool findVertex(const TVertex& f) const {
		for (auto it : vertex) {
			if (it == f) return true;
		}
		return false;
	}
	bool dfs(const TVertex& src, const TVertex& dst) const {
		std::vector<TVertex> temp;
		size_t curr_ind = 0;
		if (findVertex(src) == false || findVertex(dst) == false) return false;
		for (size_t i = 0; i < vertex.size(); ++i) {
			if (src == vertex[i]) {
				curr_ind = i;
				break;
			}
		}
		temp.push_back(src);
		return dfs(curr_ind, dst, temp);
	}
	void addVertex(const TVertex& newVertex) {
		if (findVertex(newVertex) == true) return;
		vertex.push_back(newVertex);
		std::vector<TEdge> tmp(0);
		edge.push_back(tmp);
		count++;
	}
	void deleteVertex(const TVertex& del) {
		int ind = -1;
		std::string temp;
		for (size_t i = 0; i < vertex.size(); ++i) {
			if (vertex[i] == del) {
				ind = i;
				temp = vertex[i].id;
				vertex.erase(vertex.begin()+i);
				break;
			}
		}
		if (ind == -1) return;
		edge[ind].erase(edge[ind].begin(), edge[ind].end());
		for (size_t i = 0; i < edge.size(); ++i) {
			for (size_t j = 0; j < edge[i].size(); ++j) {
				if (edge[i][j].dest == temp) {
					edge[i].erase(edge[i].begin()+j);
				}
			}
		}
		--count;
	}
	void addEdge(const TVertex& src, const TVertex& dst, const TEdge& newEdge) {
		if (findVertex(src) == false || findVertex(dst) == false) return;
		for (size_t i = 0; i < vertex.size(); ++i) {
			if (src == vertex[i]) {
				edge[i].push_back(newEdge);
				return;
			}
		}
	}
	void deleteEdge(const TVertex& src, const TVertex& dst) {
		if (findVertex(src) == false || findVertex(dst) == false) return;
		int ind = -1;
		for (size_t i = 0; i < vertex.size(); ++i) {
			if (vertex[i] == src) {
				ind = i;
				break;
			}
		}
		for (size_t i = 0; i < edge[ind].size(); ++i) {
			if (edge[ind][i].dest == dst.id) {
				edge[ind].erase(edge[ind].begin() + i);
			}
		}
	}
	void print() {
		for (size_t i = 0; i < count; ++i) {
			std::cout << "City:" << vertex[i].id << "  |  Number of people:" << vertex[i].amount << std::endl;
			std::cout << "Roads to: ";
			for (size_t j = 0; j < edge[i].size(); ++j) {
				std::cout << "          " << edge[i][j].dest << std::endl;
			}
			std::cout << "________________" << std::endl;
		}
	}
};