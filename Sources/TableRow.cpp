#include "stdafx.h"
#include "TableRow.h"

TableRow::TableRow(int id)
: _id(id), _pdata(nullptr)
{
    _itemList.clear();
}

void TableRow::addItem(const QString& txt, bool isEditable)
{
    QTableWidgetItemPtr itemPtr = QTableWidgetItemPtr::create();
    itemPtr->setText(txt);
    if (!isEditable) {
        itemPtr->setFlags(itemPtr->flags() & (~Qt::ItemIsEditable));
    }
    this->_itemList.append(itemPtr);
}

void TableRow::addToWidget(QTableWidget& tableWidget, int row)
{
    if (row < 0 || row > tableWidget.rowCount()) {
        row = tableWidget.rowCount();
    }
    tableWidget.insertRow(row);
    for (int idx = 0; idx < this->_itemList.length(); idx++) {
        bool isBlock = tableWidget.blockSignals(true);
        tableWidget.setItem(row, idx, this->_itemList[idx].data());
        tableWidget.blockSignals(isBlock);
    }
}

void TableRow::removeFromWidget(QTableWidget& tableWidget)
{
    int rowIdx = this->getRowIdx();
    if (rowIdx >= 0 && rowIdx < tableWidget.rowCount()) {
        tableWidget.removeRow(rowIdx);
    }
}

void TableRow::setSelected(bool val)
{
    for (int idx = 0; idx < this->_itemList.length(); idx++) {
        this->_itemList.at(idx)->setSelected(val);
    }
}

int TableRow::getRowIdx()
{
    if (this->_itemList.length() > 0) {
        return this->_itemList.at(0)->row();
    }
    return -1;
}

void TableRow::modifyItem(int col, const QString& txt)
{
    if (col < this->_itemList.length()) {
        QTableWidgetItemPtr item = this->_itemList[col];
        if (item != nullptr) {
            item->setText(txt);
        }
    }
}

int TableRow::getIntData(int col)
{
    QString txt = this->getStrData(col);
    return txt.toInt();
}

bool TableRow::getBoolData(int col)
{
    QString txt = this->getStrData(col);
    return txt.trimmed().toLower().compare("true") == 0;
}

QString TableRow::getStrData(int col)
{
    if (this->_itemList.length() > col) {
        return this->_itemList.at(col)->text();
    }
    return "";
}
