//
// Created by MRV on 17.12.2021.
//

#ifndef GLADKIH_3_1_GRAPH_H
#define GLADKIH_3_1_GRAPH_H

#include <vector>
#include "Node.h"
#include "Tree.h"

class Graph {
protected:
    std::vector<Node*> vertex;
    int n;
public:
    template<int n>
    Graph(int (&arr)[n][n], bool fictive = false) : n(n){
        vertex.resize(n);
        for (int i = 0; i < n; i++) {
            vertex[i] = new Node(i);
        }
        //�������� ����� ��� ����� � ����, � �������
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (arr[i][j] != 0) {
                    vertex[i]->add_edge(vertex[j], arr[i][j], arr[j][i], fictive);
                }
                else if (arr[j][i] != 0){
                    vertex[j]->add_edge(vertex[i], arr[j][i], arr[i][j], fictive);
                }
            }
        }
    }
    Graph(int** arr, int n, bool fictive = false) : n(n){
        vertex.resize(n);
        for (int i = 0; i < n; i++) {
            vertex[i] = new Node(i);
        }
        //�������� ����� ��� ����� � ����, � �������
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (arr[i][j] != 0) {
                    vertex[i]->add_edge(vertex[j], arr[i][j], arr[j][i], fictive);
                }
                else if (arr[j][i] != 0){
                    vertex[j]->add_edge(vertex[i], arr[j][i], arr[i][j], fictive);
                }
            }
        }
    }
    Tree find_MST() {
        bool* was = new bool [n]; //������ ������, � ������� ����� �������� �������, ������� ��� ����������� ������
        for (int i = 0; i < n; i++) {
            was[i] = false;
        }
        was[0] = true; //����� � ������, �� ��� �� ����� �����
        Node* root = new Node(vertex[0]->get_value()); //������ �������� ��� ��� ������
        std::vector<Node*> nodes_tree; //������ ���� ������, ����� �� �������� ������ ���
        nodes_tree.push_back(root);
        //���������� ���� ���� ���� ��������������� �������
        while (nodes_tree.size() < n){
            //���� ���������� ����� �� ���, ������� ��������� �����-�� ����� �� ������������� � �� ��������������
            int min_length = INT_MAX;
            //���������� �������������� �������
            int new_point = -1;
            //���������� ��� ������� �� �������������
            int old_point = -1;
            //�������� ��� ������������� �����
            for (int i = 0; i < nodes_tree.size(); i++) {
                //�� ������������� ��� �������� � ��� � ������� ����� ���� �� ��� � ���������� � ���������
                int was_point = nodes_tree[i]->get_value();
                int number_childs_i = vertex[was_point]->get_number_childs();
                for (int j = 0; j < number_childs_i; j++) {
                    //���� ������ ����� �� � ������, ������� � ������������� � ����� ����� ������ ��������
                    if (!was[vertex[was_point]->check_child(j).get_value()] && min_length > vertex[was_point]->get_cost(j)) {
                        //�� ��������� �������
                        min_length = vertex[nodes_tree[i]->get_value()]->get_cost(j);
                        new_point = vertex[nodes_tree[i]->get_value()]->check_child(j).get_value();
                        old_point = i;
                    }
                }
            }
            //���� �� ������ ���-�� ������������
            if (old_point != -1){
                //��������� � ������ �����
                Node* temp = new Node(new_point);
                nodes_tree[old_point]->add_edge(temp, min_length);
                //����������, ��� ������� ������������
                nodes_tree.push_back(temp);
                was[new_point] = true;
            }
            else{
                Tree buffer = Tree(root);
                buffer.clear();
            }
        }
        return Tree(root);
    }
    std::vector<int> find_shortest_ways(int index){
        //����� ������������ �������� ��������
        if (0 <= index && index <= n) {
            //������ ������, ��� ����� ������� ������� ������
            std::vector<int> marks;
            //��� ����� �� ��������� ����� �������������
            marks.resize(n, INT_MAX);
            //��������, �������� ������� ��� ���
            std::vector<bool> was;
            //�� ��������� ��� �� ��������
            was.resize(n, false);
            //���������� �� ����� ������� �� ����� ������� ����� 0. ��� ������ ���������
            marks[index] = 0;
            int min = -1;
            int min_value = INT_MAX;
            do {
                //���� �������, �������, ������� ���������� � �� ��������
                min_value = INT_MAX;
                min = -1;
                for (int i = 0; i < n; i++) {
                    //���� ������� �� ���� � � ������� ������ ��� �������, �� ��������� ���������
                    if (!was[i] && min_value > marks[i]) {
                        min = i;
                        min_value = marks[i];
                    }
                }
                //���� ����� ������� �������
                if (min != -1){
                    //��������, ��� ��� ��������
                    was[min] = true;
                    //�������� ��� �������� � ��� �� ������� ����� ��������� ��������, �� ���� ����� ����� �������, �� ������� �� ��������� � ���� ����� ������, ��� ����� ������ �������
                    int min_numbers = vertex[min]->get_number_childs();
                    for (int j = 0; j < min_numbers; j++){
                        //�������� ����� ������� � �����
                        int index_j = vertex[min]->check_child(j).get_value();
                        //������� ����� ��������� ����
                        int new_cost = vertex[min]->get_cost(j) + marks[min];
                        //���� �� ������ ������� �����, �� ��������� ���������
                        if (marks[index_j] > new_cost){
                            marks[index_j] = new_cost;
                        }
                    }
                }
            }
            while (min != -1);
            //���� ��� ������� ��������, �� �� �������� �������������� ������
            return marks;
        }

    }
    //�������� �������� � �����
    int max_flow_problem(int index_source, int index_runoff){
        if (index_source != index_runoff && 0 <= index_source && index_source < n && 0 <= index_runoff && index_runoff < n){
            std::vector<std::vector<int>> flow;
            //������� ������ �� ��������. � �� ����� ������� ������� ������. �������� ������������ ������� ��������� � ����������� �����.
            flow.resize(n);
            for (int i = 0; i < n; i++){
                // ��� ������ ������� ������� ������, � ������� ����� ������ ������� �����
                flow[i].resize(vertex[i]->get_number_childs());
            }
            std::vector<int> min_route; //������������� ����
            do {
                std::vector<bool> was; //������ ������, � ������� ����� ��������, �������� �� �������(�� ����� ������)
                was.resize(n);
                std::vector<Node *> que; //������ ������� ��� ������ � ������. ��� ����� �������������� ��� ���������� ����������� �������������� ����������� ���� �� ��������� � ����
                std::vector<std::vector<int>> que_route; //��� ����� ���������� ��� ������ ������� ���� � ��(������������ ����� ������ ������� � ������������ ����)
                que.push_back(vertex[index_source]); //�������� ���� � ���������� ���������
                que_route.emplace_back(); //���� �� ���� ����, ��� ��� �� ������
                bool found = false; //���� ����� ���������� ����, �� ���� ���������
                while (!found && !que.empty()) {
                    min_route.clear();
                    //���� �� ������� ������ �������
                    Node *cur = que[0];
                    //�������� ������� ����������
                    was[cur->get_value()] = true;
                    //�������� ���� ������������ �����
                    for (int i = 0; !found && i < cur->get_number_childs(); i++) {
                        //������� ��������� ����������
                        int up = cur->get_cost(i) - flow[cur->get_value()][i];
                        //���� �������� ����� ����������, �� � ������� ����� ����� ���� �������������
                        if (cur->get_reverse(i) != -1) up+=flow[cur->check_child(i).get_value()][cur->get_reverse(i)];
                        //���� i ������� �� ������� � ����� �� ���������������� ����� �� ����� ���������
                        if (!was[cur->check_child(i).get_value()] && up > 0) {
                            //���� ��� �� ����, �� ��������� ��� � ����� �������, ��� ���� - ��� ���� �������� + ��� �����
                            if (cur->check_child(i).get_value() != index_runoff) {
                                //��������� � ������� ������ �������
                                que.push_back(&(cur->get_child(i)));
                                //� ������� � ������ ��������� ���� �� ������� + � �����
                                que_route.push_back(que_route[0]);
                                (que_route.end() - 1)->push_back(i);
                            }
                            else {
                                //���� ��� ����, �� ��� ����������� ���� �� �����������(�� ���� �� ��������� ������)
                                min_route = que_route[0];
                                min_route.push_back(i);
                                found = true;
                            }
                        }
                    }
                    //������� �� ������� ������������ �������
                    que.erase(que.begin());
                    //� ���� � ��� ����
                    que_route.erase(que_route.begin());
                }
                std::vector<int> debug_route;
                Node*temp_node = vertex[index_source];
                for (int i = 0; i < min_route.size(); i++){
                    debug_route.push_back(temp_node->get_value());
                    temp_node = &(temp_node->get_child(min_route[i]));
                }
                debug_route.push_back(temp_node->get_value());
                //���� ���� ��� ������
                if (!min_route.empty()){
                    //������ ��� ���� ���������� ���������� ������� ����� ������������ �� ����� � ������� �������: ������ �� ��� �������� ����� �������� ������� ����� �� ����� ����
                    Node *cur = vertex[index_source];
                    int value_min = INT_MAX;
                    for (int i = 0; i < min_route.size(); i++) {
                        //������� ��������� ����������
                        int up = cur->get_cost(min_route[i]) - flow[cur->get_value()][min_route[i]];
                        //���� �������� ����� ����������, �� � ������� ����� ����� ���� �������������
                        if (cur->get_reverse(min_route[i]) != -1)  up+=flow[cur->check_child(min_route[i]).get_value()][cur->get_reverse(min_route[i])];
                        //���� ������� ������ ����������, �� ��������� �������
                        if (value_min > up) {
                            value_min = up;
                        }
                        //�������� ������� ���������
                        cur = &(cur->get_child(min_route[i]));
                    }
                    //������ �������� ��� ��� � ����������� �����
                    cur = vertex[index_source];
                    for (int i = 0; i < min_route.size(); i++) {
                        //�������� � ���������������� ����������� ��� ����� ������
                        int temp2 = min(flow[cur->check_child(min_route[i]).get_value()][cur->get_reverse(min_route[i])], value_min);
                        flow[cur->check_child(min_route[i]).get_value()][cur->get_reverse(min_route[i])]-= temp2;
                        //������� ��������� �� ������� �����������
                        flow[cur->get_value()][min_route[i]]+=value_min - temp2;
                        cur = &(cur->get_child(min_route[i]));
                    }
                }
            }
            while (!min_route.empty()); //���� ��������� ����
            int sum = 0; //������� �������� �����
            //�������� ��� �������
            for (int i = 0; i < n; i++){
                //�������� ���� ��������
                for (int j = 0; j < vertex[i]->get_number_childs(); j++){
                    //���� ������� ������� �� ������
                    if (vertex[i]->check_child(j).get_value() == index_runoff){
                        //�� ����� �� �� � ���� ���������
                        sum+=flow[i][j];
                    }
                }
            }
            //���������� ��������� �����
            return sum;
        }
    }
};

class Bi_Graph{
    //�������� ���������� ����
    std::vector<Node*> vertex_left;
    int m;
    std::vector<Node*> vertex_right;
    int n;
public:
    template<int m, int n>
    Bi_Graph(bool (&arr)[m][n]): m(m), n(n){
        vertex_left.resize(m);
        vertex_right.resize(n);
        for (int i = 0; i < m; i++) {
            vertex_left[i] = new Node(i);
        }
        for (int i = 0; i < n; i++) {
            vertex_right[i] = new Node(i);
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (arr[i][j]) {
                    vertex_left[i]->add_edge(vertex_right[j], 1);
                    vertex_right[j]->add_edge(vertex_left[i], 1);
                }
            }
        }
    }
    int maximum_weight_matching(){
        //����� ������������ ��� ����, ��� ���� �������� ��������, ��������� � ����� ������ � ����, � ������� ������� ���� ������ ����, �� ��� ���� ������� ������������ ������� �������� ���������� �������������(�� ����������� ����� ����)
        //�������� ������������� ������ ����� �������
        //������ ������� m + n + 2 �� m + n + 2(��� ��� � ��� m+n ������ ������ + �������� + ���� � ��������� ������
        int** arr = new int*[m +  n  + 2];
        for (int i = 0; i < m+n+2; i++){
            arr[i] = new int[m+n+2];
            for (int j = 0; j < m+n+2; j++) arr[i][j] = 0;
        }
        //��������� �������� � ����� ������
        for (int i = 1; i < m + 1; i++) arr[0][i] = 1;
        //��������� ������� ������ ������ ����� � ������, �� �������� ����� ������ � ������(��� ��� ����� ����� ������� �����)
        for (int i = 1; i < m + 1; i++) {
            //��������� ����� � ���������
            for (int j = 0; j < vertex_left[i-1]->get_number_childs(); j++){
                //������ �������� �� 1 ��-�� ��������� � �� m ��-�� ������ �����
                arr[i][vertex_left[i-1]->check_child(j).get_value() + m + 1] = 1;
            }
        }
        //��������� ������� ������� ����� � ������
        for (int i = m+1; i < m+n+1; i++) arr[i][m+n+1] = 1;
        Graph temp_graph(arr, m + n + 2, true);
        return temp_graph.max_flow_problem(0, m+n+1);
    }
};
#endif //GLADKIH_3_1_GRAPH_H
