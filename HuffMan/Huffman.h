#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

struct tree_node{
    char c=0;
    int weight=0;//权重
    tree_node*left_cld= nullptr;
    tree_node*right_cld= nullptr;
};//定义哈夫曼树的结点
extern string input_char;//输入的字符串
extern  tree_node*root;//哈夫曼树的根节点

extern int char_num[128];//全局数组，每个索引对应一个字符的ASCII码，索引对应的空间中存放这个字符的数量
extern string char_code[128];//全局数组，每个索引对应一个字符的ASCII码，索引对应的空间中存放这个字符的哈夫曼编码
extern tree_node* my_tree[128];//储存子树的指针，用于构建Huffman树
extern int node_count;//子树指针的个数

extern string Code;//全局字符串变量，存放临时编码
extern string Encode;//存放编码后的字符串
extern string Decode;//存放解码后的字符串
void Inorder(tree_node*root);//进行Huffman编码
void Decoding(string s,tree_node*root);//解码函数
void Input_Ope();//输入解码操作
void File_Ope();//文件解码操作
void Input_CN_Ope();//中文解码操作