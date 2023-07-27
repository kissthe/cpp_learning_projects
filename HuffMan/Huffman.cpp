#include "Huffman.h"
string input_char;//������ַ���
tree_node*root= nullptr;//���������ĸ��ڵ�

int char_num[128]={0};//ȫ�����飬ÿ��������Ӧһ���ַ���ASCII�룬������Ӧ�Ŀռ��д������ַ�������
string char_code[128]={""};//ȫ�����飬ÿ��������Ӧһ���ַ���ASCII�룬������Ӧ�Ŀռ��д������ַ��Ĺ���������
tree_node* my_tree[128];//����������ָ�룬���ڹ���Huffman��
int node_count=0;//����ָ��ĸ���

string Code="";//ȫ���ַ��������������ʱ����
string Encode="";//��ű������ַ���
string Decode="";//��Ž������ַ���
void Inorder(tree_node*root){//�������������ʵ��ĺ��ģ�������Ҫ���ǵ�Huffman�����ص㣺��ֻ��Ҷ�ӽ����������Ҫ������ַ�
    if(root== nullptr)return ;
    if(root->right_cld== nullptr&&root->left_cld== nullptr){
        char_code[root->c]=Code;//�ڷ���֮ǰ���浱ǰҶ�ӽ��ı���ֵ,����ֵ������ַ��������б��У�����ֱ�Ӳ��õ���
        return;
    }
    Code.push_back('0');//��������֮ǰ�ַ������ϸ�'0'
    Inorder(root->left_cld);

    if(!Code.empty())Code.pop_back();//�ص����������ڵ㣨���ַ���ʱ��ɾ��ĩβ��һ���ַ�
    Code.push_back('1');//������֮ǰ�ַ������ϸ���1��
    Inorder(root->right_cld);

    if(!Code.empty())Code.pop_back();//�ص����������ڵ㣨���ַ���ʱ��ɾ��ĩβ��һ���ַ�
    //������ɾ���Ĳ����ǳ���Ҫ����������Ϊ������д��һ�䵼�µ�
}

void Decoding(string s,tree_node*root){
    tree_node* temp=root;
    for(char c:s){
        if(c=='0'){
            temp=temp->left_cld;//0�Ļ�������
        } else{
            temp=temp->right_cld;//1�Ļ�������
        }
        if(temp!= nullptr&&temp->left_cld== nullptr&&temp->right_cld== nullptr){
            Decode.push_back(temp->c);//���ַ���ӵ������ַ���Decode��
            temp=root;//tempָ����ڵ��������
        }
    }
}

void Input_Ope(){
    getchar();
    cout<<"�������ַ���"<<endl;
    getline(cin,input_char);

    for(char c:input_char){
        char_num[c]++;
    }//�Ը����ַ���������ͳ��

    for(int i=0;i<128;i++)
    {
        if(char_num[i]!=0){
            tree_node* fault_node=new tree_node();//��̬�����ӽڵ�Ŀռ�
            fault_node->c=(char)i;//�����ַ�
            fault_node->weight=char_num[i];//����Ȩ��
            my_tree[node_count++]=fault_node;//�ڽڵ������б����ӽڵ�
        }
    }//��Ȩ�ز�Ϊ0���ַ���������������

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
    }//ð�������Ȩ����С�ķ�����ǰ��,���㹹��Huffman��

    for(int i=0;i<node_count-1;i++)//�����µ��������涨��Ȩ��С��Ϊ����
    {
        tree_node* temp= new tree_node;
        temp->left_cld=my_tree[i];
        temp->right_cld=my_tree[i+1];
        temp->weight=my_tree[i]->weight+my_tree[i+1]->weight;
        my_tree[i+1]=temp;//���������㹹��һ���µ�����,���Ұ��µ��������뵱ǰλ�ã����滹Ҫ����һ������
        for (int j=i+1;j<node_count-1;j++) {
            if(my_tree[j]->weight>my_tree[j+1]->weight){
                tree_node*t=my_tree[j];
                my_tree[j]=my_tree[j+1];
                my_tree[j+1]=t;
            } else{
                break;
            }
        }//����һ���µ�������ʱ��������������ƶ����������󲿷��Ѿ���������ˣ���ֻ��Ҫ������µ�������������
    }
    root=my_tree[node_count-1];//�õ����������ĸ��ڵ�

    /*������б��룬˼·�����ö���������������������������߾ͱ���Ϊ0���ұ��߾ͱ���Ϊ1������string����ɾ�ַ�������ɱ��룬�������������ĸ��ڵ㡱��
��һ��Ϊ���ַ�����ɾȥһ���ַ�����ɱ���*/

    Inorder(root);//����Huffman���룬��������ȫ�ֵ��ַ�������
    for(char c:input_char){
        Encode+=char_code[c];
    }//��������ַ���ת��Ϊ��������
    cout<<"������"<<endl;
    cout<<Encode<<endl;

    ofstream outfile;//����Ϣ���浽�ļ���
    outfile.open("code.txt");
    for(int i=0;i<128;i++){
        if(!char_code[i].empty()){
            outfile<<i<<" ";
            if(i%2==0)outfile<<char_code[i]<<'0'<<" ";
            else outfile<<char_code[i]<<'1'<<" ";
        }//���������ձ�
    }
    outfile<<endl;//�ѱ�����ձ���ڵ�һ��
    outfile<<Encode<<endl;//�������
    outfile.close();
    Decoding(Encode,root);
    if(Decode==input_char){
        cout<<"����ɹ�,��Ϣһ��"<<endl;
    }
    return ;
}
void File_Ope(){
    map<string,int>m;//��map���洢��ֵ�ԣ�������н���,���Ǳ��루string����ֵ��
    getchar();//����ǰ��cin�Ļس���
    ifstream infile;
    infile.open("code.txt");
    char buff[1024]="";
    infile.getline(buff, 1024);//��ȡ�ļ��ĵ�һ�У��������
    cout << buff << endl;
    int index=0;//key
    int j=0;//ѭ������
    int temp=0;//��ʱ�洢��Ӧ��ʮ����������Ϊvalue
    string str_temp;//��ű������У���Ϊkey
    while (true){
        if(buff[j]!=' '&&buff[j]!='\0'){
            temp*=10;
            temp+=buff[j]-'0';//�õ���ǰ�ַ���ascii���ʮ���Ʊ�ʾ
        } else if(buff[j]==' '){
            j++;//�����ո�
            while (buff[j]!=' '&&buff[j]!='\0'){//���ڿո�����Ǳ��룬������ѭ���õ����Ǳ�������
                str_temp.push_back(buff[j]);
                j++;
            }

            str_temp.pop_back();//������һ�����ڱ����'0'��֤�ַ���

            m[str_temp]=temp;//��map�������ֵ��
            temp=0;
            str_temp.clear();//��һЩ��ʱ���������0�������
            if(buff[j]=='\0')break;
        }
        else break;
        j++;
    }
    cout<<"������ȡ���"<<endl;
    infile.getline(buff,1024);//��ȡ��������
    Encode=buff;//�ѱ������д�Ž�ȥ
    cout<<Encode<<endl;
    for(char c:Encode){//ͨ��map ���Ҷ�Ӧ��ֵ���ұ�����Decode��
        str_temp.push_back(c);//key
        auto iter=m.find(str_temp);
        if(iter!=m.end()){
            Decode.push_back((char )iter->second);//���������ַ�
            str_temp.clear();//�ҵ�һ��value����ս�����һ�β���
        }
    }
    return ;
}