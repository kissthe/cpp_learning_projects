#include "Huffman.h"
int main() {
    cout<<"ѡ�����ѡ��"<<endl;
    cout<<"1.��Ӣ����Ϣ���б��봫��  2.�ļ����� "<<endl;
    cout<<"������"<<endl;
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
            cout<<"�������"<<endl;
            exit(1);
    }
    cout<<"�����"<<endl;
    cout<<Decode<<endl;
    return 0;
}
