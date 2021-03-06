// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cstdio>
using namespace std;

class linkTable {
private:
	struct cell {
		cell* prev = nullptr;
		int val;
		cell* next = nullptr;
	};
	cell* head = nullptr;
	cell* tail = nullptr;
public:
	~linkTable() {
		cell* current = tail->prev;
		while (current != nullptr) {
			delete current->next;
			current = current->prev;
		}
		delete head;
	}
	int length = 0;
	bool push(int val) {
		if (length == 0) {
			head = new cell;
			tail = head;
			head->val = val;
		}
		else {
			tail->next = new cell;
			tail->next->prev = tail;
			tail = tail->next;
			tail->val = val;
		}
		length++;
		this->echo();
		cout << "pushed: " << val << endl;
		return true;
	}
	bool unshift(int val) {
		if (length == 0) {
			head = new cell;
			tail = head;
			head->val = val;
		}
		else {
			head->prev = new cell;
			head->prev->next = head;
			head = head->prev;
			head->val = val;
		}
		length++;
		this->echo();
		cout << "unshifted: " << val << endl;
		return true;
	}
	int pop() {
		int val;
		if (head == nullptr) {
			throw "今日无事可做";
			return false;
		}
		else if (head == tail) {
			val = head->val;
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			val = tail->val;
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}
		length--;
		this->echo();
		cout << "poped: " << val << endl;
		return val;
	}
	int shift() {
		int val;
		if (head == nullptr) {
			throw "今日无事可做";
			return false;
		}
		else if (head == tail) {
			val = head->val;
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			val = head->val;
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
		length--;
		this->echo();
		cout << "shifted: " << val << endl;
		return val;
	}
	void echo() {
		cell* current = head;
		cout << "{";
		for (int i = 0; current != nullptr; i++) {
			cout << current->val;
			current = current->next;
			if (current != nullptr) {
				cout << ", ";
			}
		}
		cout << "}";
	}
	static bool deepcopy(linkTable* target, linkTable* source) {
		cell* current = source->head;
		for (int i = 0; current != nullptr; i++) {
			target->push(current->val);
			current = current->next;
		}
		return true;
	}
	static linkTable* merge(linkTable* a, linkTable* b) {
		linkTable* result = new linkTable();
		deepcopy(result, a);
		deepcopy(result, b);
		return result;
	}
};

// 成对的操作：unshift     shift     push      pop
//            插入到头 / 从头删除  插入到尾 / 从尾删除
int main() {
	linkTable* sto = new linkTable();
	linkTable* sto2 = new linkTable();
	linkTable* result = new linkTable();
	const int x = 5;
	
	for (int i = 0; i < 5; i++) {
		sto->push(rand() % 10);
	}
	for (int i = 0; i < 5; i++) {
		sto2->push(rand() % 10);
	}

	cout << endl << "select result" << endl;
	result->push(x);
	cout << endl;

	for (int i = 0; i < 5; i++) {
		cout << "select sto";
		int val = sto->shift();
		cout << "select result";
		if (val < x) {
			result->unshift(val);
		} else {
			result->push(val);
		}
		cout << endl;
	}
	for (int i = 0; i < 5; i++) {
		cout << "select sto2";
		int val = sto2->shift();
		cout << "select result";
		if (val < x) {
			result->unshift(val);
		}
		else {
			result->push(val);
		}
		cout << endl;
	}
	result->echo();
	
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
