//
// Created by MRV on 18.12.2021.
//

#ifndef GLADKIH_3_1_NODE_H
#define GLADKIH_3_1_NODE_H
class Node{
    int value;
    //������� ����
    std::vector<Node*> childs;
    //���� �����
    std::vector<int> cost;
    //����� ��������� �����, ���� ��� ����
    std::vector<int> reverse_index;
public:
    int get_value() const{
        return value;
    }
    //�������� ����� � ������ �����
    void add_edge(Node* vertex, int cost, int reverse_cost = 0, bool fictive = false){
        childs.push_back(vertex);
        this->cost.push_back(cost);
        if (reverse_cost > 0 || fictive) {
            vertex->cost.push_back(reverse_cost);
            vertex->childs.push_back(this);
            reverse_index.push_back(vertex->get_number_childs()-1);
            vertex->reverse_index.push_back(childs.size() - 1);
        }
        else reverse_index.push_back(-1);
    }
    int get_number_childs() const{
        return childs.size();
    }
    //���������� ������� ��� ����� �� ���������
    const Node& check_child(int i) const{
        return *childs[i];
    }
    Node& get_child(int i) const {
        return *childs[i];
    }
    int get_cost(int i) const{
        return cost[i];
    }
    int get_reverse(int i) const{
        return reverse_index[i];
    }
    Node(int value) : value(value){}
};
#endif //GLADKIH_3_1_NODE_H
