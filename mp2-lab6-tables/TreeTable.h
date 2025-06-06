#pragma once

#include<stack>
#include<string>
#include<sstream>

#include"Table.h"

enum BALANCE : int {
	LEFT = -1,
	BOK,
	RIGHT
};

template<class TKey, class TValue>
struct TreeNode {
	Record<TKey, TValue> rec;
	TreeNode* pLeft;
	TreeNode* pRight;
	BALANCE balance = BALANCE::BOK;
};

template<class TKey, class TValue>
class TreeTable : public Table<TKey, TValue> {
protected:
	TreeNode<TKey, TValue>* pRoot;
	TreeNode<TKey, TValue>* pCurr;
	TreeNode<TKey, TValue>* pPrev;

	std::stack<TreeNode<TKey, TValue>*> path;

	int pos, level;

	void printRec(std::ostream& out, TreeNode<TKey, TValue>* p) {
		if (p == nullptr) {
			return;
		}

		for (int i = 0; i < level; i++) {
			out << "  ";
		}
		out << p->rec.key << '\n';
		level++;
		this->printRec(out, p->pRight);
		this->printRec(out, p->pLeft);
		level--;
	}
public:
	TreeTable() : Table<TKey, TValue>() {
		pRoot = pCurr = pPrev = nullptr;
		pos = level = 0;
	}

	bool findRecord(TKey key) override {
		pPrev = nullptr;
		pCurr = pRoot;
		while (pCurr != nullptr) {
			this->Efficiency++;
			if (key > pCurr->rec.key) {
				pPrev = pCurr;
				pCurr = pCurr->pRight;
			}
			else {
				if (key < pCurr->rec.key) {
					pPrev = pCurr;
					pCurr = pCurr->pLeft;
				}
				else {
					return true;
				}
			}
		}
		pCurr = pPrev;
		return false;
	}

	void insertRecord(Record<TKey, TValue> r) override {
		if (!(this->findRecord(r.key))) {
			TreeNode<TKey, TValue>* nn = new TreeNode<TKey, TValue>{ r,nullptr,nullptr, BALANCE::BOK };
			if (pCurr == nullptr) {
				pRoot = nn;
				this->Efficiency++;
				this->DataCount++;
			}
			else {
				if (r.key > pCurr->rec.key) {
					pCurr->pRight = nn;
					this->Efficiency++;
					this->DataCount++;
				}
				else {
					pCurr->pLeft = nn;
					this->Efficiency++;
					this->DataCount++;
				}
			}
		}
		else throw RecordAlreadyExist();
	}

	void deleteRecord(TKey key) override {
		if (this->findRecord(key)) {
			TreeNode<TKey, TValue>* pDel = pCurr;

			if (pCurr->pRight == nullptr) {
				this->Efficiency++;
				if (pCurr == pRoot) {
					pRoot = pCurr->pLeft;
				}
				else {
					if (pCurr == pPrev->pRight) {
						pPrev->pRight = pCurr->pLeft;
					}
					else {
						pPrev->pLeft = pCurr->pLeft;
					}
				}
			}
			else if (pCurr->pLeft == nullptr) {
				this->Efficiency++;
				if (pCurr == pRoot) {
					pRoot = pCurr->pRight;
				}
				else {
					if (pCurr == pPrev->pRight) {
						pPrev->pRight = pCurr->pRight;
					}
					else {
						pPrev->pLeft = pCurr->pRight;
					}
				}
			}
			else {
				TreeNode<TKey, TValue>* pN = pCurr->pLeft;
				pPrev = pCurr;
				while (pN->pRight != nullptr) {
					pPrev = pN;
					pN = pN->pRight;
					this->Efficiency++;
				}
				pCurr->rec = pN->rec;
				if (pPrev == pCurr) {
					pCurr->pLeft = pN->pLeft;
				}
				else {
					pPrev->pRight = pN->pLeft;
				}
				pDel = pN;
			}
			this->Efficiency++;
			delete pDel;
			this->DataCount--;
		}
		else {
			return;
		}
	}

	void resetIterator() override {
		// �������� ����
		while (!path.empty()) path.pop();
		// ������ � �����
		TreeNode<TKey, TValue>* node = pRoot;
		// �������� ����� �� ������ ����
		while (node) {
			path.push(node);
			node = node->pLeft;
		}
	}

	void goNext() override {
		if (path.empty()) return;
		// ����� ������� ����
		TreeNode<TKey, TValue>* node = path.top();
		path.pop();
		// ���� � ���� ���� ������ �������, ���������� � ���� � ������ �����
		node = node->pRight;
		while (node) {
			path.push(node);
			node = node->pLeft;
		}
	}

	bool isFull() override {
		return false;
	}

	Record<TKey, TValue> getCurrentRecord() override {
		if (path.empty())
			throw OutOfRange();
		return path.top()->rec;
	}

	bool isEnd() override {
		return path.empty();
	}

	void printTree(std::ostream& os) {
		level = 0;
		this->printRec(os, this->pRoot);
	}

	std::string getTreeAsString() {
		std::stringstream ss;
		this->printTree(ss);
		return ss.str();
	}
};