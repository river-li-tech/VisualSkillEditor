#pragma once
#include "stdafx.h"
#include "define.h"
#include "SkillInst.h"
#include "SkillScript.h"
#include "SkillSpec.h"

class CheckCombo;

///////////////////////////////////////////////////////////////////////////
struct ParamWidgetRowInfo
{
    enum WidgetType
    {
        TYPE_COMBO,
        TYPE_SPIN,
        TYPE_DOUBLESPIN,
        TYPE_EDIT,
    };

    //界面信息
    int                         _widgetType = ParamWidgetRowInfo::TYPE_COMBO;
    QWidget*                    _inputWidget = nullptr;
    QComboBox*                  _refCombo = nullptr;
    QPushButton*                _revertButton = nullptr;

    //数据信息
    SkillScriptNodeParamPtr     _paramPtr = SkillScriptNodeParamPtr();
    SkillSpecNodeParamPtr       _argPtr = SkillSpecNodeParamPtr();
};
using ParamWidgetRowPtr = QSharedPointer<ParamWidgetRowInfo>;

///////////////////////////////////////////////////////////////////////////
class ParamWidget : public QWidget
{
    Q_OBJECT

public:
    ParamWidget(QWidget *parent);

public:
    void loadView(SkillScriptNode* node);
    void clearView();

private slots:
    //////////////////////////////////////////////////////////////////////
    //监听控件发送的signal
    void onNodeTypeComboCurrentIndexChanged(int index);
    void onActionTypeComboCurrentIndexChanged(int index);
    void onArgComboCurrentIndexChanged(int index);
    void onArgRefComboCurrentIndexChanged(int state);
    void onArgCheckedComboCurrentIndexChanged(int index, bool isChecked);
    void onArgSpinValueChanged(int value);
    void onArgDSpinValueChanged(double value);
    void onArgEditTxtEditingFinished();
    void onArgRevertButtonClicked();

private:
    //////////////////////////////////////////////////////////////////////
    //添加行-节点类型
    void addNodeTypeRow();
    //填充CombolBox可选项
    void fillNodeTypeComboItems(QComboBox * cbValue, int nodeType, int publicType);
    //设置CombolBox当前项
    void setNodeTypeComboItem(QComboBox * cbValue, int nodeType);
    //填充CombolBox可选项
    void fillActionTypeComboItems(QComboBox * cbValue, int nodeType, int publicType);
    //设置CombolBox当前项
    void setActionTypeComboItem(QComboBox * cbValue, int nodeType);

    //添加行-节点参数
    void addNodeArgRows();
    //删除行-节点参数
    void clearNodeArgRows();
    //添加行-整数
    void addNodeSpinRow(SkillScriptNodeParamPtr paramPtr, SkillSpecNodeParamPtr argPtr);
    //添加行-浮点数
    void addNodeDSpinRow(SkillScriptNodeParamPtr paramPtr, SkillSpecNodeParamPtr argPtr);
    //添加行-文本
    void addNodeEditRow(SkillScriptNodeParamPtr paramPtr, SkillSpecNodeParamPtr argPtr);

    //添加行-枚举
    void addNodeEnumRow(SkillScriptNodeParamPtr paramPtr, SkillSpecNodeParamPtr argPtr);
    //填充CombolBox可选项
    void fillArgComboItems(QComboBox * cbValue, SkillSpecNodeParamPtr argPtr);
    //设置CombolBox当前项
    void setArgComboItem(QComboBox * cbValue, SkillScriptNodeParamPtr paramPtr);

    //添加行-复选枚举
    void addNodeCheckedEnumRow(SkillScriptNodeParamPtr paramPtr, SkillSpecNodeParamPtr argPtr);
    //填充CheckedCombolBox可选项
    void fillArgCheckedComboItems(CheckCombo * cbValue, SkillSpecNodeParamPtr argPtr);
    //设置CheckedCombolBox当前项
    void setArgCheckedComboItem(CheckCombo * cbValue, SkillScriptNodeParamPtr paramPtr);

    //填充索引CombolBox可选项
    void fillArgRefItems(QComboBox * cbValue, SkillSpecNodeParamPtr argPtr);
    //设置索引CombolBox当前项
    void setArgRefItem(QComboBox * cbValue, SkillScriptNodeParamPtr paramPtr);

    //添加行
    void addRowWidget(QLabel* lbName, QWidget* nodeWidget, QComboBox* cbRef, QPushButton* pbRevert);

private:
    //获取输入框
    ParamWidgetRowPtr getRowByInputWidget(QWidget* combo);
    //获取引用下拉框
    ParamWidgetRowPtr getRowByRefCombo(QWidget* checkbox);
    //获取按钮
    ParamWidgetRowPtr getRowByRevertButton(QPushButton* button);
    
private:
    SkillScriptNode *               _node;
    QFormLayout *                   _layout;
    SkillSpecNodePtr                _curSpecNode;

    QComboBox *                     _nodeTypeCombo;
    QComboBox *                     _actionTypeCombo;
    QList<ParamWidgetRowPtr>        _argRows;
};
