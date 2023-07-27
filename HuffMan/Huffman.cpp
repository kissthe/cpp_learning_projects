#include "Huffman.h"
string input_char;//输入的字符串
tree_node*root= nullptr;//哈夫曼树的根节点

int char_num[128]={0};//全局数组，每个索引对应一个字符的ASCII码，索引对应的空间中存放这个字符的数量
string char_code[128]={""};//全局数组，每个索引对应一个字符的ASCII码，索引对应的空间中存放这个字符的哈夫曼编码
tree_node* my_tree[128];//储存子树的指针，用于构建Huffman树
int node_count=0;//子树指针的个数

string Code="";//全局字符串变量，存放临时编码
string Encode="";//存放编码后的字符串
string Decode="";//存放解码后的字符串
void Inorder(tree_node*root){//这个部分是整个实验的核心，在这里要考虑到Huffman树的特点：即只有叶子结点是我们需要编码的字符
    if(root== nullptr)return ;
    if(root->right_cld== nullptr&&root->left_cld== nullptr){
        char_code[root->c]=Code;//在返回之前保存当前叶子结点的编码值,编码值存放在字符串数组中表中，可以直接查表得到；
        return;
    }
    Code.push_back('0');//在向左走之前字符串加上个'0'
    Inorder(root->left_cld);

    if(!Code.empty())Code.pop_back();//回到哈夫曼父节点（空字符）时，删除末尾的一个字符
    Code.push_back('1');//向右走之前字符串加上个‘1’
    Inorder(root->right_cld);

    if(!Code.empty())Code.pop_back();//回到哈夫曼父节点（空字符）时，删除末尾的一个字符
    //这两个删除的操作非常重要，错误都是因为这里少写了一句导致的
}

void Decoding(string s,tree_node*root){
    tree_node* temp=root;
    for(char c:s){
        if(c=='0'){
            temp=temp->left_cld;//0的话往左走
        } else{
            temp=temp->right_cld;//1的话往右走
        }
        if(temp!= nullptr&&temp->left_cld== nullptr&&temp->right_cld== nullptr){
            Decode.push_back(temp->c);//把字符添加到解码字符串Decode中
            temp=root;//temp指向根节点继续解码
        }
    }
}

void Input_Ope(){
    getchar();
    cout<<"请输入字符串"<<endl;
    getline(cin,input_char);

    for(char c:input_char){
        char_num[c]++;
    }//对各个字符进行数量统计

    for(int i=0;i<128;i++)
    {
        if(char_num[i]!=0){
            tree_node* fault_node=new tree_node();//动态申请子节点的空间
            fault_node->c=(char)i;//储存字符
            fault_node->weight=char_num[i];//储存权重
            my_tree[node_count++]=fault_node;//在节点数组中保存子节点
        }
    }//把权重不为0的字符给存入结点数组中

    for(int i=0;i<node_count-1;i++)
    {
        for(int j=0;j<node_count-1-i;j++)
        {
            if(my_tree[j]->weight>my_tree[j+1]->weight)
            {
                tree_node* temp=my_tree[j];
                my_tree[j]=my_tree[j+1];
                my_tree[j+1]=temp;
            }
        }
    }//冒泡排序把权重最小的放在最前面,方便构造Huffman树

    for(int i=0;i<node_count-1;i++)//创建新的子树，规定：权重小的为左孩子
    {
        tree_node* temp= new tree_node;
        temp->left_cld=my_tree[i];
        temp->right_cld=my_tree[i+1];
        temp->weight=my_tree[i]->weight+my_tree[i+1]->weight;
        my_tree[i+1]=temp;//完成两个结点构成一棵新的子树,并且把新的子树放入当前位置，后面还要进行一下排序
        for (int j=i+1;j<node_count-1;j++) {
            if(my_tree[j]->weight>my_tree[j+1]->weight){
                tree_node*t=my_tree[j];
                my_tree[j]=my_tree[j+1];
                my_tree[j+1]=t;
            } else{
                break;
            }
        }//构造一个新的子树的时候把这个结点往后移动（这个数组大部分已经是有序的了，故只需要对这个新的子树进行排序）
    }
    root=my_tree[node_count-1];//得到哈夫曼树的根节点

    /*下面进行编码，思路是利用二叉树的中序遍历，如果是往左边走就编码为0，右边走就编码为1，利用string的增删字符操作完成编码，遇见“哈夫曼的父节点”，
（一般为空字符）就删去一个字符来完成编码*/

    Inorder(root);//进行Huffman编码，编码存放在全局的字符串表中
    for(char c:input_char){
        Encode+=char_code[c];
    }//把输入的字符串转化为编码序列
    cout<<"编码后的"<<endl;
    cout<<Encode<<endl;

    ofstream outfile;//将信息保存到文件中
    outfile.open("code.txt");
    for(int i=0;i<128;i++){
        if(!char_code[i].empty()){
            outfile<<i<<" ";
            if(i%2==0)outfile<<char_code[i]<<'0'<<" ";
            else outfile<<char_code[i]<<'1'<<" ";
        }//输出编码对照表
    }
    outfile<<endl;//把编码对照表放在第一行
    outfile<<Encode<<endl;//输出编码
    outfile.close();
    Decoding(Encode,root);
    if(Decode==input_char){
        cout<<"编码成功,信息一致"<<endl;
    }
    return ;
}
void File_Ope(){
    map<string,int>m;//用map来存储键值对，方便进行解码,键是编码（string），值是
    getchar();//处理前面cin的回车符
    ifstream infile;
    infile.open("code.txt");
    char buff[1024]="";
    infile.getline(buff, 1024);//读取文件的第一行，即编码表
    cout << buff << endl;
    int index=0;//key
    int j=0;//循环变量
    int temp=0;//临时存储对应的十进制数，作为value
    string str_temp;//存放编码序列，作为key
    while (true){
        if(buff[j]!=' '&&buff[j]!='\0'){
            temp*=10;
            temp+=buff[j]-'0';//得到当前字符的ascii码的十进制表示
        } else if(buff[j]==' '){
            j++;//跳过空格
            while (buff[j]!=' '&&buff[j]!='\0'){//由于空格后面是编码，因此这个循环得到的是编码序列
                str_temp.push_back(buff[j]);
                j++;
            }

            str_temp.pop_back();//清除最后一个用于保存的'0'验证字符串

            m[str_temp]=temp;//用map来保存键值对
            temp=0;
            str_temp.clear();//把一些临时变量都变成0或者清空
            if(buff[j]=='\0')break;
        }
        else break;
        j++;
    }
    cout<<"编码表读取完毕"<<endl;
    infile.getline(buff,1024);//读取编码序列
    Encode=buff;//把编码序列存放进去
    cout<<Encode<<endl;
    for(char c:Encode){//通过map 查找对应的值并且保存在Decode中
        str_temp.push_back(c);//key
        auto iter=m.find(str_temp);
        if(iter!=m.end()){
            Decode.push_back((char )iter->second);//保存解码的字符
            str_temp.clear();//找到一个value后清空进行下一次查找
        }
    }
    return ;
}