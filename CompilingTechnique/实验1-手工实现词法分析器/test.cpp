/*
 * @Author: your name
 * @Date: 2021-04-02 16:16:43
 * @LastEditTime: 2021-04-02 16:46:33
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\test.cpp
 */
/*
 * @Author: your name
 * @Date: 2021-04-02 14:59:34
 * @LastEditTime: 2021-04-02 15:54:10
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-terme:\ProgrammingLessons\CompilingTechnique\Ex1_LexicalAnalyzer\test1.cpp
 */
using namespace std;
int count=0;
int main()
{
    int i=39;
    int 89jjj,kkkoo;        /* test comment */

    while(1)
    {
    count++;
    cout<<"input num:";
    int ii;
    cin>>ii;
    if(ii==i)
    {
        cout<<"Right!!!"<<endl;
        cout<<"times:"<<count<<endl;
        break;
    }
    else
    {
        cout<<"wrong!"<<endl;
        if(ii>i)
            cout<<"too big";
        else 
            cout<<"too small!";
    }
    system("pause");

    }
    return 0;
}