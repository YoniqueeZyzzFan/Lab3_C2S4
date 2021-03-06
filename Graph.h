#include <vector>
#include <string>
#include <iostream>

struct Edge {
	std::string dest;
	double length;
	bool pay;
	bool type;
	Edge(const Edge& rhs) {
		this->dest = rhs.dest;
		this->length = rhs.length;
		this->pay = rhs.pay;
		this->type = rhs.type;
	}
	Edge& operator =(const Edge& rhs) {
		if (this == &rhs) return *this;
		this->dest = rhs.dest;
		this->length = rhs.length;
		this->pay = rhs.pay;
		this->type = rhs.type;
		return *this;
	}
	Edge() : dest(""), length(-1), pay(false), type(1) {}
	Edge(const std::string& dst, const double& l, const double& p = 2, const bool& type = true) :length(l), dest(dst), pay(p), type(type) {}
	/*operator double() const {
		return length;
	}*/
};
struct Vertex {
	std::string id;
	size_t amount;
	Vertex(const Vertex& rhs) {
		this->id = rhs.id;
		this->amount = rhs.amount;
	}
	Vertex& operator=(const Vertex& rhs) {
		if (this == &rhs) return *this;
		this->id = rhs.id;
		this->amount = rhs.amount;
		return *this;
	}
	Vertex(const std::string& str, const size_t& am) : id(str), amount(am) {}
};
template<>
struct std::equal_to<Vertex> {
	size_t operator()(const Vertex& v1, const Vertex& v2) {
		return((v1.id == v2.id) && (v1.amount == v2.amount));
	}
};

//template<typename TEdge>
//struct WeightSelector {
//	operator double(const TEdge& rhs) {
//		return static_cast<TEdge>(rhs);
//	}
//};
//template<typename TEdge, typename NewType>
//struct WeightConverter
//{
//	static inline NewType run(const TEdge& x)
//	{
//		return static_cast<NewType>(x);
//	}
//};
template<typename TEdge>
class MWeightConverter {
public:
	double operator()(const TEdge& rhs) const {
		return static_cast<double>(rhs);
	}
};
template<>
class MWeightConverter<Edge> {
public:
	double operator()(const Edge& rhs) const {
		return rhs.length;
	}
};
template <typename TVertex, typename TEdge, typename equal = std::equal_to<Vertex>>
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
		for (size_t i = 0; i < vertex.size(); ++i) {
			if (str == vertex[i].id) return i;
		}
		return -1;
	}
	bool dfs(const size_t curr_ind, const TVertex& dst, std::vector<TVertex>& tmp) const {
		equal compare;
		if (compare(tmp[tmp.size() - 1], dst)) return true;
		for (size_t k = 0; k < edge[curr_ind].size(); ++k) {
			if (compare(tmp[tmp.size() - 1], dst)) return true;
			if (check(tmp, edge[curr_ind][k].dest) == true) continue;
			int take_id = checker(edge[curr_ind][k].dest);
			tmp.push_back(vertex[take_id]);
			dfs(take_id, dst, tmp);
		}
		if (compare(tmp[tmp.size() - 1], dst)) return true;
		else return false;
	}
	template <typename wsm = MWeightConverter<TEdge>>
	double dijkstr(std::vector<double>& length, std::vector<bool> checked, const TVertex& src, const TVertex& dst, std::vector<int>& parent, const double& road_fail = 0, const double& pay_fail = 0) {
		size_t new_min = checker(src.id);
		checked[new_min] = true;
		wsm ws;
		for (size_t i = 0; i < edge[new_min].size(); ++i) {
			int ch = checker(edge[new_min][i].dest);
			int road = edge[new_min][i].type == 0 ? 0 : road_fail;
			int pay = edge[new_min][i].pay == 0 ? 0 : pay_fail;
			if (length[ch] > length[new_min] + ws(edge[new_min][i]) + pay + road) {
				length[ch] = length[new_min] + ws(edge[new_min][i]) + pay + road;
				parent[ch] = new_min;
			}
		}
		double temp = -1;
		int ind_min = -1;
		for (size_t i = 0; i < edge[new_min].size(); ++i) {
			size_t ch = checker(edge[new_min][i].dest);
			if (checked[ch] == false) {
				temp = length[ch];
				ind_min = ch;
				break;
			}
		}
		for (size_t i = ind_min; i < edge[new_min].size(); ++i) {
			int ch = checker(edge[new_min][i].dest);
			if (checked[ch] == true) continue;
			if (temp > length[ch]) {
				ind_min = ch;
				temp = length[ch];
			}
		}
		if (ind_min == -1) {
			bool flag = false;
			for (size_t i = 0; i < checked.size(); ++i) {
				if (checked[i] == false) {
					ind_min = i;
					flag = true;
					break;
				}
			}
			if (flag == false) {
				return length[checker(dst.id)];
			}
			//return length[checker(dst.id)];
		}
		return dijkstr(length, checked, vertex[ind_min], dst, parent, road_fail, pay_fail);
	}
public:
	Graph() {
		count = 0;
	}
	bool findVertex(const TVertex& f) const {
		equal compare;
		for (auto it : vertex) {
			if (compare(it, f)) return true;
		}
		return false;
	}
	bool dfs(const TVertex& src, const TVertex& dst) const {
		equal compare;
		std::vector<TVertex> temp;
		size_t curr_ind = 0;
		if (findVertex(src) == false || findVertex(dst) == false) return false;
		for (size_t i = 0; i < vertex.size(); ++i) {
			if (compare(src, vertex[i])) {
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
		equal compare;
		int ind = -1;
		std::string temp;
		for (size_t i = 0; i < vertex.size(); ++i) {
			if (compare(vertex[i], del)) {
				ind = i;
				temp = vertex[i].id;
				vertex.erase(vertex.begin() + i);
				break;
			}
		}
		if (ind == -1) return;
		edge[ind].erase(edge[ind].begin(), edge[ind].end());
		for (size_t i = 0; i < edge.size(); ++i) {
			for (size_t j = 0; j < edge[i].size(); ++j) {
				if (edge[i][j].dest == temp) {
					edge[i].erase(edge[i].begin() + j);
				}
			}
		}
		--count;
	}
	void addEdge(const TVertex& src, const TVertex& dst, const TEdge& newEdge) {
		if (findVertex(src) == false || findVertex(dst) == false) return;
		equal compare;
		for (size_t i = 0; i < vertex.size(); ++i) {
			if (compare(src, vertex[i])) {
				edge[i].push_back(newEdge);
				return;
			}
		}
	}
	void deleteEdge(const TVertex& src, const TVertex& dst) {
		if (findVertex(src) == false || findVertex(dst) == false) return;
		int ind = -1;
		equal compare;
		for (size_t i = 0; i < vertex.size(); ++i) {
			if (compare(vertex[i], src)) {
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
	template <typename wsm = MWeightConverter<TEdge>>
	std::vector<TVertex> dijkstra(const TVertex& src, const TVertex& dst, const double& road_fail = 0, const double& pay_fail = 0) { //
		std::vector<TVertex> path_to_dst;
		wsm wm;
		if (findVertex(src) == false || findVertex(dst) == false) return path_to_dst;
		std::vector<int> parent(vertex.size(), -1);
		std::vector<double> length(vertex.size());
		std::vector<bool> checked(vertex.size(), false);
		int new_min = checker(src.id);
		for (size_t i = 0; i < length.size(); ++i) {
			if (i == new_min) continue;
			length[i] = INT32_MAX;
		}
		length[checker(src.id)] = 0;
		checked[checker(src.id)] = true;
		double result = dijkstr<wsm>(length, checked, src, dst, parent, road_fail, pay_fail);
		if (result == INT32_MAX) {
			std::cout << "Path doesnt exist" << std::endl;
			return path_to_dst;
		}
		std::vector<int> path;
		for (int v = checker(dst.id); v != -1; v = parent[v]) {
			path.push_back(v);
		}
		reverse(path.begin(), path.end());
		std::cout << "path:";
		for (size_t i = 0; i < path.size(); ++i) {
			path_to_dst.push_back(vertex[path[i]]);
		}
		for (size_t i = 0; i < path.size() - 1; ++i) {
			int type = 0;
			int pay = 0;
			int ch = checker(path_to_dst[i].id);
			double sum = 0;
			for (size_t j = 0; j < edge[ch].size(); ++j) {
				if (path_to_dst[i + 1].id == edge[ch][j].dest) {
					type = edge[ch][j].type == 0 ? 0 : road_fail;
					pay = edge[ch][j].pay == 0 ? 0 : pay_fail;
					sum = wm(edge[ch][j]);
					sum += type;
					sum += pay;
					break;
				}
			}
			std::cout << "From: " << path_to_dst[i].id << " | to: " << path_to_dst[i + 1].id << std::endl;
			std::cout << "Pay: " << pay << " | Road type: " << type << " | Length: " << sum << std::endl;
		}
		std::cout << std::endl << "Overall Length:" << result << std::endl;
		return path_to_dst;
	}
	void print() {
		for (size_t i = 0; i < count; ++i) {
			std::cout << "City:" << vertex[i].id << "  |  Number of people:" << vertex[i].amount << std::endl;
			for (size_t j = 0; j < edge[i].size(); ++j) {
				std::cout << "Road to: " << edge[i][j].dest << " | Pay: " << edge[i][j].pay << std::endl;
			}
			std::cout << "________________" << std::endl;
		}
	}
};