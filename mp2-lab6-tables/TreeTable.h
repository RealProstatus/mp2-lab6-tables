#pragma once

#include<stack>

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

	int pos;
public:
	TreeTable() : Table<TKey, TValue>() {
		pRoot = pCurr = pPrev = nullptr;
		pos = 0;
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
		pCurr = pRoot;
		path = std::stack<TreeNode<TKey, TValue>*>();
		pos = 0;

		while (pCurr != nullptr) {
			path.push(pCurr);
			pCurr = pCurr->pLeft;
		}

		if (!path.empty())
			pCurr = path.top();
		else
			pCurr = nullptr;
	}

	void goNext() override {
		pCurr = pCurr->pRight;
		path.pop();

		if (pCurr == nullptr && !(path.empty()))
			pCurr = path.top();
		else {
			while (pCurr->pLeft != nullptr) {
				path.push(pCurr);
				pCurr = pCurr->pLeft;
			}
			path.push(pCurr);
		}

		pos++;
	}

	bool isFull() override {
		return false;
	}

	Record<TKey, TValue> getCurrentRecord() override {
		return pCurr->rec;
	}

	bool isEnd() override {
		return pos == this->DataCount;
	}
};