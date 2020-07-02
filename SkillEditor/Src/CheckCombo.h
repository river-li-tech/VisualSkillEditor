/************************************************************************/
/*
@file:CheckCombo.h
@author:LRiver.2019.10.25
@desc:带复选框的下拉列表
*/
/************************************************************************/

#pragma once
#include <QComboBox>

class CheckCombo : public QComboBox
{
    Q_OBJECT

public:
    CheckCombo(QWidget *parent);

public:
    void appendItem(const QString &text, bool bChecked);
    void hidePopup();
    void updateIndexStatus(int index);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    void reverseIndexStatus(int index);
    void updateAllStatus();

signals:
    void checkedStateChange(int index, bool bChecked);
};
