#include "llist.h"
#include <iostream>

using namespace std;

int main()
{
    LList<int> l;
    l.push_back(1);
    l.push_front(0);
    l.push_back(2);

    cout << "Stage 1: "; dump(l); cout << endl;

    l.insert_at(1, 10);
    cout << "Stage 2: "; dump(l); cout << endl;

    l.erase_at(1);
    cout << "Stage 2: "; dump(l); cout << endl;

    l.reverse();
    cout << "Stage 3: "; dump(l); cout << endl;
    
    LList<int> list;
    LList<int> movelist;
    for (int i = 0; i<100; i++) {
        list.push_back(i);
    }
    movelist = move(list);
    LList<int> copyList(movelist);
    return 0;
    
}
