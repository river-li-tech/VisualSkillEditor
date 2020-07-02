#include "stdafx.h"
#include "CheckCombo.h"

CheckCombo::CheckCombo(QWidget *parent) :
QComboBox(parent)
{
}

void CheckCombo::appendItem(const QString &text, bool bChecked)
{
    QIcon icon;
    if (bChecked) {
        icon.addFile(":/icons/Icons/Checkbox Full.png");
    } else {
        icon.addFile(":/icons/Icons/Checkbox Empty.png");
    }

    addItem(icon, text, bChecked);
}

void CheckCombo::reverseIndexStatus(int index)
{
    bool bChecked = this->itemData(index).toBool();

    if (bChecked) {
        this->setItemIcon(index, QIcon(":/icons/Icons/Checkbox Empty.png"));
    } else {
        this->setItemIcon(index, QIcon(":/icons/Icons/Checkbox Full.png"));
    }

    setItemData(index, !bChecked);
}

void CheckCombo::updateAllStatus()
{
    for (int idx = 0; idx < this->count(); idx++)
    {
        bool bChecked = this->itemData(idx).toBool();
        emit checkedStateChange(idx, bChecked);
    }
}

void CheckCombo::updateIndexStatus(int index)
{
    bool bChecked = this->itemData(index).toBool();

    if (bChecked) {
        this->setItemIcon(index, QIcon(":/icons/Icons/Checkbox Full.png"));
    } else {
        this->setItemIcon(index, QIcon(":/icons/Icons/Checkbox Empty.png"));
    }
}

void CheckCombo::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();

    int iconWidth = this->iconSize().width();
    if (x <= iconWidth) {
        int index = this->currentIndex();
        reverseIndexStatus(index);
    } else {
        QComboBox::mousePressEvent(event);
    }
}

void CheckCombo::hidePopup()
{
    int iconWidth = this->iconSize().width();

    int x = QCursor::pos().x() - mapToGlobal(geometry().topLeft()).x() + geometry().x();

    int index = view()->selectionModel()->currentIndex().row();

    if (x >= 0 && x <= iconWidth) {
        reverseIndexStatus(index);
    } else {
        updateAllStatus();
        QComboBox::hidePopup();
    }
}