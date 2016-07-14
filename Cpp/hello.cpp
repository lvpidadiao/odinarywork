#include <iostream>
#include <vector>

using namespace std;

int main(void)
{

    vector<int> ar;
    ar.push_back(1);
    
    cout << "hello" << sizeof(int) ;
    cout << '\n';
    cout << ar.front() << "\t"<< ar.capacity() ;



    return 0;
}
