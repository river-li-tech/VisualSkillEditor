/************************************************************************/
/*
@file:TableRow.h
@author:LRiver.2019.10.25
@desc:QTableWidget的行数据
*/
/************************************************************************/

#pragma once
#include "stdafx.h"

class TableRow
{
public:
	TableRow(int id);

	void addItem(const QString& txt, bool isEditable = true);
	void modifyItem(int col, const QString& txt);

	void addToWidget(QTableWidget& tableWidget, int row = -1);
	void removeFromWidget(QTableWidget& tableWidget);

    void setSelected(bool val);
    int getId() { return this->_id; }
    void setId(int id) { this->_id = id; }
	int getRowIdx();

	void setData(void * data) { this->_pdata = data; }
	void* getData() { return this->_pdata; }

	int getIntData(int col);
	bool getBoolData(int col);
	QString getStrData(int col);

private:
	int _id;
    QList<QTableWidgetItemPtr> _itemList;
	void * _pdata;
};
using TableRowPtr = QSharedPointer<TableRow>;
