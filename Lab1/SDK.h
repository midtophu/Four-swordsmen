#ifndef SDK_H
#define SDK_H

#include<iostream>

class SDK{
	public:
	char puzzle[128];
	int *answer;
	bool flag;
	SDK(){
		answer=new int[81];
		flag=false;
	}
	~SDK(){
		delete []answer;
	}
	
};

#endif
