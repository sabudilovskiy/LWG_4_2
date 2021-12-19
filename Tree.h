//
// Created by MRV on 18.12.2021.
//

#ifndef GLADKIH_3_1_TREE_H
#define GLADKIH_3_1_TREE_H
#include "Node.h"
#include <vector>
class Tree{
protected:
    Node* root;
    //����������� ������� �������� ���� � ��� ��������
    static void delete_node(Node* node){
        if (node){
            //���� ���� �������, �� �� �������
            if (node->get_number_childs() > 0){
                for (int i = 0; i < node->get_number_childs(); i++) delete_node(&(node->get_child(i)));
            }
            delete node;
        }
    }
public:
    Tree(Node* root) : root(root){}
    Node& get_root(){
        return *root;
    }
    void clear(){
        //��������� �������� � ������� ����
        delete_node(root);
        root = nullptr;
    }
    void left_depth(std::vector<int> & answer, Node* cur_node = nullptr){
        //������������� ����� � �������
        if (cur_node == nullptr){
            cur_node = root;
        }
        //������� �������� ���� � �������������� ������
        answer.push_back(cur_node->get_value());
        //��������� ����� ������� ����� ��������
        for (int i = 0; i < cur_node->get_number_childs(); i++){
            left_depth(answer, &(cur_node->get_child(i)));
        }
    }
    double avg_inc_left_breadth(){
        //������ ������� ��� ������
        std::vector<Node*> que;
        //��������� � ������� �������� ���
        que.push_back(root);
        //������� ���������� �����
        int count = 0;
        //������� ��������� ���������� ����������� ������
        double sum = 0;
        //���� ������� �� �����
        while (!que.empty()){
            //������� ������ ��� � ���
            Node* cur_node = que[0];
            //����������� ���������� ��������� ������
            count++;
            //����������� ���������� ����
            sum+=cur_node->get_number_childs();
            //��������� � ������� ���� ��������
            for (int i = 0; i < cur_node->get_number_childs(); i++) que.push_back(&(cur_node->get_child(i)));
            //������� �� ������� ������ ���
            que.erase(que.begin());
        }
        //���������� ������� ��������������
        return sum/count;
    }
    ~Tree(){
        clear();
    }
};


#endif //GLADKIH_3_1_TREE_H
