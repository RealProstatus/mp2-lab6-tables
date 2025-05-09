#pragma once

#include"Exceptions.h"
#include"TreeTable.h"

enum HEIGHT : int  {
	OK,
	INC,
	DEC
};

enum Mode {

};

template<class TKey, class TValue>
class BalanceTreeTable : public TreeTable<TKey, TValue> {
public:
	void insertRecord(Record<TKey, TValue> r) override {
		if (this->findRecord(r.key)) {
			throw RecordAlreadyExist();
		}
		else {
			this->insBalTree(this->pRoot, r);
		}
	}

	void deleteRecord(TKey key) override {

	}

protected:
	int insBalTree(TreeNode<TKey, TValue>*& pNode, Record<TKey, TValue> rec) {
		int res = HEIGHT::OK;

		if (pNode == nullptr) {
			pNode = new TreeNode<TKey, TValue>{ rec, nullptr,nullptr, BALANCE::OK };
			res = HEIGHT::INC;
			this->DataCount++;
		}
		else {
			if (pNode->rec.key > rec.key) {
				int tmp = this->insBalTree(pNode->pLeft, rec);
				if (tmp == HEIGHT::INC)
					res = this->BalTreeLeft(pNode);
			}
			else {
				int tmp = this->insBalTree(pNode->pRight, rec);
				if (tmp == HEIGHT::INC)
					res = this->BalTreeRight(pNode);
			}
		}

		return res;
	}

	int BalTreeLeft(TreeNode<TKey, TValue>*& pNode) {
		int res = HEIGHT::OK;
		//если был перевес справа
		if (pNode->balance == BALANCE::RIGHT) {
			pNode->balance = BALANCE::OK;
			res = HEIGHT::OK;
		}
		//если не было перевеса
		else if (pNode->balance == BALANCE::OK) {
			pNode->balance = BALANCE::LEFT;
			res = HEIGHT::INC;
		}
		else {
			//если перевес слева, надо перебалансировать
			if (pNode->balance == BALANCE::LEFT) {
				TreeNode<TKey, TValue>* p1 = pNode->pLeft;
				//одинарный поворот (см 1ый случай из лекций ј.¬.—ысоева)
				if (p1->balance == BALANCE::LEFT) {
					pNode->pLeft = p1->pRight;
					p1->pRight = pNode;
					pNode = p1;
					pNode->balance = BALANCE::OK;
					pNode->pRight->balance = BALANCE::OK;
				}
				//двойной поворот
				else {
					TreeNode<TKey, TValue>* p2 = p1->pRight;
					p1->pRight = p2->pLeft;
					pNode->pRight = p2->pLeft;
					p2->pLeft = p1;
					pNode->pLeft = p2->pRight;
					if (p2->balance == BALANCE::LEFT)
						pNode->balance = BALANCE::RIGHT;
					else
						pNode->balance = BALANCE::OK;

					if (p2->balance == BALANCE::RIGHT)
						pNode->balance = BALANCE::LEFT;
					else
						p1->balance = BALANCE::OK;

					pNode = p2;
					pNode->balance = BALANCE::OK;
					res = HEIGHT::OK;
				}
			}
		}

		return res;
	}

	int BalTreeRight(TreeNode<TKey, TValue>*& pNode) {
		//случай, симметричный с BalTreeLeft
		int res = HEIGHT::OK;

		if (pNode->balance == BALANCE::LEFT) {
			pNode->balance = BALANCE::OK;
			res = HEIGHT::OK;
		}
		else if (pNode->balance == BALANCE::OK) {
			pNode->balance = BALANCE::RIGHT;
			res = HEIGHT::INC;
		}
		else {
			if (pNode->balance == BALANCE::RIGHT) {
				TreeNode<TKey, TValue>* p1 = pNode->pRight;

				if (p1->balance == BALANCE::RIGHT) {
					pNode->pRight = p1->pLeft;
					p1->pLeft = pNode;
					pNode = p1;
					pNode->balance = BALANCE::OK;
					pNode->pLeft->balance = BALANCE::OK;
					res = HEIGHT::OK;
				}
				else {
					TreeNode<TKey, TValue>* p2 = p1->pLeft;

					p1->pLeft = p2->pRight;
					pNode->pRight = p2->pLeft;
					p2->pRight = p1;
					p2->pLeft = pNode;

					if (p2->balance == BALANCE::RIGHT)
						pNode->balance = BALANCE::LEFT;
					else
						pNode->balance = BALANCE::OK;

					if (p2->balance == BALANCE::LEFT)
						p1->balance = BALANCE::RIGHT;
					else
						p1->balance = BALANCE::OK;

					pNode = p2;
					pNode->balance = BALANCE::OK;
					res = HEIGHT::OK;
				}
			}
		}

		return res;
	}
};