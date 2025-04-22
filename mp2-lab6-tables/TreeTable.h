#pragma once

#include<stack>

#include"Table.h"

template<class TKey, class TValue>
struct TreeNode {
	Record<TKey, TValue> rec;
	TreeNode* pLeft;
	TreeNode* pRight;
	int balance;
};

template<class TKey, class TValue>
class TreeTable : public Table<TKey, TValue> {
protected:
	TreeNode<TKey, TValue>* pRoot;
	TreeNode<TKey, TValue>* pCurr;
	TreeNode<TKey, TValue>* pPrev;

	std::stack<TreeNode<TKey, TValue>> path;

	int pos;
public:
	TreeTable() : Table<TKey, TValue>() {
		pRoot = pCurr = pPrev = nullptr;
	}

	bool findRecord(TKey key) {
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

	void insertRecord(Record<TKey, TValue> r) {
		if (!(this->findRecord(r.key))) {
			TreeNode<TKey, TValue>* nn = new TreeNode<TKey, TValue>{ r,nullptr,nullptr,0 };
			if (pCurr == nullptr) {
				pRoot = nn;
				this->Efficiency++;
				this->DataCount++;
			}
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
		else throw RecordAlreadyExist();
	}

	void deleteRecord(TKey key) {
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

	void resetIterator() {
		pCurr = pRoot;
		path = std::stack<TreeNode<TKey, TValue>>();
		pos = 0;

		while (pCurr->pLeft != nullptr) {
			path.push(pCurr);
			pCurr = pCurr->pLeft;
		}
		path.push(pCurr);
	}

	void goNext() {
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

	bool isEnd() {
		return pos == this->DataCount;
	}
};