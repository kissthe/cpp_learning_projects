#include "Huffman.h"
int main() {
    cout<<"选择你的选项"<<endl;
    cout<<"1.对英文信息进行编码传输  2.文件解码 "<<endl;
    cout<<"请输入"<<endl;
    int cho=0;
    cin>>cho;
    switch (cho) {
        case 2:
            File_Ope();
            break;
        case 1:
            Input_Ope();
            break;
        default:
            cout<<"输入错误"<<endl;
            exit(1);
    }
    cout<<"解码后："<<endl;
    cout<<Decode<<endl;
    return 0;
}
