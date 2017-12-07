#include <iostream>
#include "shared_ptr.h"

int main(void) {

	int* p = new int(1);
	shared_ptr<int> sp(p);
	std::cout << sp.getRef() << std::endl;  // 1
	{
		shared_ptr<int> sp2(sp);
		std::cout << sp.getRef() << std::endl;  // 2
		std::cout << sp2.getRef() << std::endl; // 2

		shared_ptr<int> sp3 = sp;
		std::cout << sp.getRef() << std::endl;  // 3
		std::cout << sp3.getRef() << std::endl; // 3

		shared_ptr<int> sp4 = sp;
		std::cout << sp.getRef() << std::endl;  // 4
		std::cout << sp4.getRef() << std::endl; // 4
	}
	
	// sp2,sp3,sp4离开作用域后，会使得共享的会调用--_count三次，所以是4-3
	std::cout << sp.getRef() << std::endl;   // 1

	return 0;
}
