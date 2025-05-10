#pragma once

#include"Exceptions.h"
#include"TreeTable.h"

enum HEIGHT : int  {
	DEC = -1,
	OK,
	INC
};

enum MODE {
	INSERT,
	DELETE
};

template<class TKey, class TValue>
class AVLTreeTable : public TreeTable<TKey, TValue> {
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
		if (pRoot == nullptr) {
			//TODO: добавить метод isEmpty в родительский класс
			throw - 2531;
		}
		Del_Rec(pRoot, key);
	}

protected:

	//ћетоды дл€ вставки

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
					res = this->BalTreeLeft(pNode, MODE::INSERT);
			}
			else {
				int tmp = this->insBalTree(pNode->pRight, rec);
				if (tmp == HEIGHT::INC)
					res = this->BalTreeRight(pNode, MODE::INSERT);
			}
		}

		return res;
	}

	int BalTreeLeft(TreeNode<TKey, TValue>*& pNode, MODE mode) {
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

	int BalTreeRight(TreeNode<TKey, TValue>*& pNode, MODE mode) {
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

	//методы дл€ удалени€

	int Del_Rec(TreeNode<TKey, TValue>*& pNode, TKey key) {
		this->Efficiency++;
		
		int res = HEIGHT::OK;
		if (pNode == nullptr)
			return res;
		else if (pNode->rec.key < key) {
			int tmp = Del_Rec(pNode->pRight, key);
			if (tmp == HEIGHT::DEC)
				res = BalTreeLeft(pNode, MODE::DELETE);
		}
		else if (pNode->rec.key > key) {
			int tmp = Del_Rec(pNode->pLeft, key);
			if (tmp == HEIGHT::DEC)
				res = BalTreeRight(pNode, MODE::DELETE);
		}
		else {
			this->DataCount--;

			//нет потомков
			if (pNode->pLeft == nullptr && pNode->pRight == nullptr) { 
				delete pNode;
				pNode = nullptr;
				res = HEIGHT::DEC;
			}
			//один потомок справа
			else if (pNode->pLeft == nulptr) {
				pNode->rec = pNode->pRight->rec;
				delete pNode->pRight;
				pNode->pRight = nullptr;
				pNode->balance = BALANCE::OK;

				res = HEIGHT::DEC;
			}
			//один потомок слева
			else if (pNode->pRight == nullptr) {
				pNode->rec = pNode->pLeft->rec;
				delete pNode->pLeft;
				pNode->pLeft = nullptr;
				pNode->balance = BALANCE::OK;

				res = HEIGHT::DEC;
			}
			//оба потомка
			else {
				TreeNode<TKey, TValue>* left = pNode->pLeft;
				TreeNode<TKey, TValue>* right = pNode->pRight;
				TreeNode<TKey, TValue>* min = findMin(right);

				res = removeMin(right);
				pNode->rec = min->rec;
				delete min;
				pNode->pLeft = left;
				pNode->pRight = right;
				if (res != HEIGHT::OK)
					BalTreeLeft(pNode, MODE::DELETE);
			}
		}
		return res;
	}

	TreeNode<TKey, TValue>* findMin(TreeNode<TKey, TValue>* pNode) {
		while (pNode->pLeft != nullptr)
			pNode = pNode->pLeft;
		return pNode;
	}

	int excludeMin(TreeNode<TKey, TValue>*& pNode) {
		this->Efficiency++;

		int res = HEIGHT::OK;
		//мы на исключаемом узле
		if (pNode->pLeft == nullptr) {
			pNode = pNode->pRight;
			res = HEIGHT::DEC;
		}
		//иначе 
		else {
			res = excludeMin(pNode->pLeft);
			if (res != HEIGHT::OK)
				res = BalTreeRight(pNode->pRight, MODE::DELETE);
		}

		return res;
	}

	//

	void DeleteRecord(TreeNode<TKey, TValue>* pNode) {
		if (pNode == nullptr)
			return;
		this->DeleteRecord(pNode->pRight);
		this->DeleteRecord(pNode->pLeft);

		delete pNode;
	}

	~AVLTreeTable() {
		this->DeleteRecord(pRoot);
	}
};