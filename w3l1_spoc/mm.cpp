#include <iostream>
#include <set>
#define MAX_MEM 1024
using namespace std;

struct Node {
	int begin;
	int size;
	Node(int b,int s): begin(b), size(s) {}
	
};

bool operator<(const Node &n1,const Node &n2){
		return (n1.begin < n2.begin);
}

set<Node> freeList;
set<Node>::iterator it;

void showFreeList() {
	cout << "Free Blocks:" << endl;
	for(auto i : freeList){
		cout << "begin:" << i.begin << " size:" << i.size << endl;
	}
	return;
}

int malloc(int size) {
	for(auto i : freeList) {
		if(i.size > size) {
			Node n(i.begin + size, i.size - size);
			freeList.erase(i);
			freeList.insert(n);
			cout << "Begin from: "<< i.begin << endl;
			return i.begin;	
		} else if(i.size == size){
			freeList.erase(i);
			cout << "Begin from: "<< i.begin << endl;
			return i.begin;
		}
	}
	cout << "Failed" << endl;
	return -1;
}

void free(int begin, int size) {
	cout << "free " << begin << " to " << size << endl;
	for(it = freeList.begin(); it != freeList.end(); ) {
		
		int ib = it -> begin, ie = it -> begin + it -> size;
		if(ie == begin) {
			cout << "merged with free memory block begin from " << it->begin << ", size: " << it -> size << endl;
			begin = ib;
			size += it -> size;
			it = freeList.erase(it);
		}else if(ib == begin + size) {
			cout << "merged with free memory block begin from " << it->begin << ", size: " << it -> size << endl;
			size += it -> size;
			it = freeList.erase(it);
		}
		else {
			it ++;
		}
	}
	freeList.insert(Node(begin,size));
}


int main() {
	freeList.insert(Node(0, MAX_MEM));
	malloc(100); showFreeList();
	malloc(100); showFreeList();
	malloc(100); showFreeList();
	malloc(100); showFreeList();
	malloc(600); showFreeList();
	malloc(100); showFreeList();
	cout<<"---------"<<endl;
	free(100,100); showFreeList();
	free(300,100); showFreeList();
	free(200,100); showFreeList();
	free(0,100); showFreeList();
}
	
