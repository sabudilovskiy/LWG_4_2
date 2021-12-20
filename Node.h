//
// Created by MRV on 18.12.2021.
//

#ifndef GLADKIH_3_1_NODE_H
#define GLADKIH_3_1_NODE_H
class Node{
    int value;
    //потомки нода
    std::vector<Node*> childs;
    //цена связи
    std::vector<int> cost;
    //номер реверсной связи, если она есть
    std::vector<int> reverse_index;
public:
    int get_value() const{
        return value;
    }
    //добавить связь с другим нодом
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
    //посмотреть потомка без права на изменение
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
