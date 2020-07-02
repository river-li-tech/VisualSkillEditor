#include "stdafx.h"
#include "ParamWidget.h"
#include "CheckCombo.h"
#include "SkillInst.h"
#include "SkillScript.h"
#include "SkillSpec.h"
#include "Dict.h"
#include "Utils.h"

ParamWidget::ParamWidget(QWidget *parent)
: QWidget(parent), _layout(nullptr), _curSpecNode(SkillSpecNodePtr()),
_nodeTypeCombo(nullptr), _actionTypeCombo(nullptr), _node(nullptr)
{
    _argRows.clear();
}

void ParamWidget::loadView(SkillScriptNode* node)
{
    //初始化
    _node = node;
    _layout = dynamic_cast<QFormLayout*>(this->layout());
    _curSpecNode = getSpecNode(_node->getId());

    //添加子控件
    if (_node != nullptr && _layout != nullptr && _curSpecNode != nullptr) {
        addNodeTypeRow();
        addNodeArgRows();
    }
}

void ParamWidget::clearView()
{
    _node = nullptr;
    if (_nodeTypeCombo != nullptr) {
        this->disconnect(_nodeTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onNodeTypeComboCurrentIndexChanged(int)));
        _nodeTypeCombo->deleteLater();
        _nodeTypeCombo = nullptr;
    }
    if (_actionTypeCombo != nullptr) {
        this->disconnect(_actionTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onActionTypeComboCurrentIndexChanged(int)));
        _actionTypeCombo->deleteLater();
        _actionTypeCombo = nullptr;
    }
    clearNodeArgRows();
    //确保所有子节点都清除
    QList<QWidget*> children = this->findChildren<QWidget *>();
    for (int idx = 0; idx < children.length(); idx++) {
        children[idx]->deleteLater();
    }
}

void ParamWidget::onNodeTypeComboCurrentIndexChanged(int index)
{
    //QComboBox *_typeCombo = (QComboBox*)sender();
    if (_nodeTypeCombo != nullptr && _actionTypeCombo != nullptr
        && _node != nullptr) {
        int nodeType = _nodeTypeCombo->itemData(index).toInt();
        int publicType = getNodePublicByParents(*_node);
        QList<SkillSpecNodePtr> nodeList;
        getSpecNodeListByType(nodeList, nodeType, publicType);
        if (nodeList.length() > 0) {
            QString nodeId = nodeList.first()->getId();
            SkillScriptNode * newNode = _node;
            newNode->setId(nodeId);
            fillScriptNodeParams(*newNode);
            newNode->notify(SkillNotifyReason::R_SKILLSCRIPTNODE_ID);
        } else {
            _node->notify(SkillNotifyReason::R_SKILLSCRIPTNODE_ID);
        }
    }
}

void ParamWidget::onActionTypeComboCurrentIndexChanged(int index)
{
    //QComboBox *_typeCombo = (QComboBox*)sender();
    if (_actionTypeCombo != nullptr && _node != nullptr) {
        QVariant userData = _actionTypeCombo->itemData(index);
        QString nodeId = userData.toString();
        SkillScriptNode * newNode = _node;
        newNode->setId(nodeId);
        fillScriptNodeParams(*newNode);
        newNode->notify(SkillNotifyReason::R_SKILLSCRIPTNODE_ID);
    }
}

void ParamWidget::onArgComboCurrentIndexChanged(int index)
{
    QComboBox *argCombo = (QComboBox*)sender();
    if (argCombo != nullptr && _node != nullptr) {
        ParamWidgetRowPtr rowPtr = this->getRowByInputWidget(argCombo);
        if (rowPtr != nullptr && rowPtr->_paramPtr != nullptr) {
            int num = argCombo->itemData(index).toInt();
            if (!rowPtr->_paramPtr->isRef()) {
                rowPtr->_paramPtr->setAsNumber(num);
            }
        }
    }
}

void ParamWidget::onArgRefComboCurrentIndexChanged(int index)
{
    QComboBox *argCombo = (QComboBox*)sender();
    if (argCombo != nullptr && _node != nullptr) {
        ParamWidgetRowPtr rowPtr = this->getRowByRefCombo(argCombo);
        if (rowPtr != nullptr && rowPtr->_paramPtr != nullptr) {
            if (index > 0) {
                int logicIdx = argCombo->itemData(index).toInt();
                rowPtr->_paramPtr->setAsRefIdx(logicIdx);

                int num = getInstDataParamByIdx(logicIdx);
                rowPtr->_paramPtr->setAsRefNum(num);
            } else {
                int num = rowPtr->_paramPtr->getNumber<int>();
                rowPtr->_paramPtr->setAsNumber(num);
            }
        }
    }
}

void ParamWidget::onArgCheckedComboCurrentIndexChanged(int index, bool isChecked)
{
    CheckCombo *argCombo = (CheckCombo*)sender();
    if (argCombo != nullptr && _node != nullptr) {
        ParamWidgetRowPtr rowPtr = this->getRowByInputWidget(argCombo);
        if (rowPtr != nullptr && rowPtr->_paramPtr != nullptr) {
            int paramValue = 0;
            for (int idx = 0; idx < argCombo->count(); idx++) {
                int itemValue = argCombo->itemData(idx, Qt::UserRole + 1).toInt();
                bool isCheck = argCombo->itemData(idx).toBool();
                if (isCheck) {
                    paramValue |= itemValue;
                }
            }

            if (!rowPtr->_paramPtr->isRef()) {
                rowPtr->_paramPtr->setAsNumber(paramValue);
            }
        }
    }
}

void ParamWidget::onArgSpinValueChanged(int value)
{
    QSpinBox *argSpin = (QSpinBox*)sender();
    if (argSpin != nullptr && _node != nullptr) {
        ParamWidgetRowPtr rowPtr = this->getRowByInputWidget(argSpin);
        if (rowPtr != nullptr && rowPtr->_paramPtr != nullptr) {
            if (!rowPtr->_paramPtr->isRef()) {
                rowPtr->_paramPtr->setAsNumber(value);
            }
        }
    }
}

void ParamWidget::onArgDSpinValueChanged(double value)
{
    QDoubleSpinBox *argSpin = (QDoubleSpinBox*)sender();
    if (argSpin != nullptr && _node != nullptr) {
        ParamWidgetRowPtr rowPtr = this->getRowByInputWidget(argSpin);
        if (rowPtr != nullptr && rowPtr->_paramPtr != nullptr) {
            if (!rowPtr->_paramPtr->isRef()) {
                rowPtr->_paramPtr->setAsNumber(value);
            }
        }
    }
}

void ParamWidget::onArgEditTxtEditingFinished()
{
    QLineEdit* argEdit = (QLineEdit*)sender();
    if (argEdit != nullptr && _node != nullptr) {
        ParamWidgetRowPtr rowPtr = this->getRowByInputWidget(argEdit);
        if (rowPtr != nullptr && rowPtr->_paramPtr != nullptr) {
            rowPtr->_paramPtr->setAsString(argEdit->text());
        }
    }
}

void ParamWidget::onArgRevertButtonClicked()
{
    QPushButton* argButton = (QPushButton*)sender();
    if (argButton != nullptr && _node != nullptr) {
        ParamWidgetRowPtr rowPtr = this->getRowByRevertButton(argButton);
        if (rowPtr != nullptr && rowPtr->_paramPtr != nullptr) {
            SkillSpecNodeParamPtr argPtr = getSpecNodeParam(rowPtr->_paramPtr->getParentNodeId(),
                rowPtr->_paramPtr->getName());
            if (argPtr != nullptr) {
                if (argPtr->getType() == "enum.string") {
                    QString dftVal = argPtr->getDefault();
                    rowPtr->_paramPtr->setAsString(dftVal.length() >= 1 ? dftVal.right(dftVal.length() - 1) : dftVal);
                } else {
                    rowPtr->_paramPtr->setAsNumber(argPtr->getDefault().toDouble());
                }
            }
        }
    }
}

void ParamWidget::addNodeTypeRow()
{
    if (_layout != nullptr) {
        int nodeType = getSpecNodeType(_node->getId());
        int publicType = getNodePublicByParents(*_node);

        //节点类型
        QLabel* lbNodeName = new QLabel(this);
        lbNodeName->setText(tr("Node Type:"));
        QComboBox* cbNodeValue = new QComboBox(this);
        cbNodeValue->setMaxVisibleItems(30);
        //填充Combox可选项
        fillNodeTypeComboItems(cbNodeValue, nodeType, publicType);
        //填充值
        setNodeTypeComboItem(cbNodeValue, nodeType);
        _layout->addRow(lbNodeName, cbNodeValue);
        //关联事件
        this->connect(cbNodeValue, SIGNAL(currentIndexChanged(int)), SLOT(onNodeTypeComboCurrentIndexChanged(int)));
        //保存为类变量，方便回调时处理(便于处理)
        _nodeTypeCombo = cbNodeValue;

        //指令类型
        QLabel* lbActionName = new QLabel(this);
        lbActionName->setText(tr("Action Type:"));
        QComboBox* cbActionValue = new QComboBox(this);
        cbActionValue->setMaxVisibleItems(30);
        //填充Combox可选项
        fillActionTypeComboItems(cbActionValue, nodeType, publicType);
        //填充值
        setActionTypeComboItem(cbActionValue, nodeType);
        _layout->addRow(lbActionName, cbActionValue);
        //关联事件
        this->connect(cbActionValue, SIGNAL(currentIndexChanged(int)), SLOT(onActionTypeComboCurrentIndexChanged(int)));
        //保存为类变量，方便回调时处理(便于处理)
        _actionTypeCombo = cbActionValue;
    }
}

void ParamWidget::fillNodeTypeComboItems(QComboBox * cbValue, int nodeType, int publicType)
{
    if (cbValue == nullptr) {
        return;
    }

    int nodeCls = nodeType + 1;
    SkillSpecEnumPtr nodeTypeEnum = getSpecEnum(SKILLPARAM_ENUM_NODETYPE_NAME);
    if (nodeTypeEnum != nullptr) {
        const QList<SkillSpecEnumValuePtr>& enumValList = nodeTypeEnum->getValues();
        //显示到Combo
        for (int idx = 0; idx < enumValList.length(); idx++) {
            SkillSpecEnumValuePtr enumValPtr = enumValList.at(idx);
            int minCls = enumValPtr->getIntArg(1);
            int maxCls = enumValPtr->getIntArg(2);
            int _public = enumValPtr->getIntArg(3);
            if (enumValPtr != nullptr
                && ((_public & publicType) != 0)
                && (minCls == _INVALID_ID || (minCls != _INVALID_ID && nodeCls >= minCls))
                && (maxCls == _INVALID_ID || (maxCls != _INVALID_ID && nodeCls <= maxCls))
                ) {
                QString txt = QStringLiteral("%1").arg(enumValPtr->getName());
                cbValue->insertItem(idx, txt, enumValPtr->getValue());
            }
        }
    }
}

void ParamWidget::setNodeTypeComboItem(QComboBox * cbValue, int nodeType)
{
    if (cbValue == nullptr || _node == nullptr) {
        return;
    }

    for (int idx = 0; idx < cbValue->count(); idx++) {
        QVariant userData = cbValue->itemData(idx);
        int itemValue = userData.toInt();
        if (itemValue == nodeType) {
            cbValue->setCurrentIndex(idx);
            break;
        }
    }
}

void ParamWidget::fillActionTypeComboItems(QComboBox * cbValue, int nodeType, int publicType)
{
    if (cbValue == nullptr) {
        return;
    }

    QList<SkillSpecNodePtr> nodeList;
    getSpecNodeListByType(nodeList, nodeType, publicType);

    //显示到Combo
    for (int idx = 0; idx < nodeList.length(); idx++) {
        SkillSpecNodePtr nodePtr = nodeList.at(idx);
        if (nodePtr != nullptr) {
            QString txt = QStringLiteral("%1").arg(nodePtr->getTitle());
            cbValue->insertItem(idx, txt, nodePtr->getId());
        }
    }
}

void ParamWidget::setActionTypeComboItem(QComboBox * cbValue, int nodeType)
{
    if (cbValue == nullptr || _node == nullptr) {
        return;
    }
    for (int idx = 0; idx < cbValue->count(); idx++) {
        QVariant userData = cbValue->itemData(idx);
        QString itemValue = userData.toString();
        if (itemValue == _node->getId()) {
            cbValue->setCurrentIndex(idx);
            break;
        }
    }
}

void ParamWidget::addNodeArgRows()
{
    if (_curSpecNode == nullptr || _node == nullptr) {
        return;
    }

    QList<SkillSpecNodeParamPtr>& paramList = _curSpecNode->getParams();
    for (int idx = 0; idx < paramList.length(); idx++) {
        SkillSpecNodeParamPtr argPtr = paramList.at(idx);
        SkillScriptNodeParamPtr paramPtr = _node->getParam(argPtr->getName());
        if (argPtr != nullptr) {
            if (argPtr->getType() == "enum.string") {
                addNodeEditRow(paramPtr, argPtr);
            } else if (argPtr->getType() == "enum.number") {
                addNodeSpinRow(paramPtr, argPtr);
            } else if (argPtr->getType() == "enum.double") {
                addNodeDSpinRow(paramPtr, argPtr);
            } else {
                SkillSpecEnumPtr enumPtr = getSpecEnum(argPtr->getType());
                if (enumPtr != nullptr) {
                    if (enumPtr->isCheck()) {
                        addNodeCheckedEnumRow(paramPtr, argPtr);
                    } else {
                        addNodeEnumRow(paramPtr, argPtr);
                    }
                }
            }
        }
    }
}

void ParamWidget::clearNodeArgRows()
{
    for (int idx = 0; idx < _argRows.length(); idx++) {
        ParamWidgetRowPtr rowPtr = _argRows[idx];
        if (rowPtr->_inputWidget != nullptr) {
            if (rowPtr->_widgetType == ParamWidgetRowInfo::TYPE_COMBO) {
                this->disconnect(rowPtr->_inputWidget, 0, 0, 0);
            } else if (rowPtr->_widgetType == ParamWidgetRowInfo::TYPE_SPIN) {
                this->disconnect(rowPtr->_inputWidget, 0, 0, 0);
            } else if (rowPtr->_widgetType == ParamWidgetRowInfo::TYPE_DOUBLESPIN) {
                this->disconnect(rowPtr->_inputWidget, 0, 0, 0);
            } else if (rowPtr->_widgetType == ParamWidgetRowInfo::TYPE_EDIT) {
                this->disconnect((QLineEdit*)rowPtr->_inputWidget, 0, 0, 0);
            }
            rowPtr->_inputWidget->deleteLater();
        }
        if (rowPtr->_refCombo != nullptr) {
            this->disconnect(rowPtr->_refCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onArgComboCurrentIndexChanged(int)));
            rowPtr->_refCombo->deleteLater();
        }
        if (rowPtr->_revertButton != nullptr) {
            this->disconnect(rowPtr->_revertButton, SIGNAL(clicked()), this, SLOT(onArgRevertButtonClicked()));
            rowPtr->_revertButton->deleteLater();
        }
    }
    _argRows.clear();
}

void ParamWidget::addNodeEnumRow(SkillScriptNodeParamPtr paramPtr, SkillSpecNodeParamPtr argPtr)
{
    if (_layout != nullptr) {
        //创建label
        QLabel * lbName = new QLabel(this);
        lbName->setText(QStringLiteral("%1").arg(argPtr->getTitle()));
        //创建ComboBox
        QComboBox * cbValue = new QComboBox(this);
        //设置Tooltip
        cbValue->setToolTip(argPtr->getDesc());
        //填充Combox可选项
        fillArgComboItems(cbValue, argPtr);
        //填充值
        if (paramPtr != nullptr) {
            setArgComboItem(cbValue, paramPtr);
            cbValue->setEnabled(!paramPtr->isRef());
        }
        //创建索引Combo
        QComboBox * cbRef = new QComboBox(this);
        cbRef->setFixedWidth(SKILLPARAM_REF_COMBO_FIXED_WIDTH);
        fillArgRefItems(cbRef, argPtr);
        setArgRefItem(cbRef, paramPtr);
        //创建恢复按钮
        QPushButton* pbRevert = new QPushButton(this);
        pbRevert->setFixedWidth(SKILLPARAM_REVERT_BUTTON_FIXED_WIDTH);
        pbRevert->setText(SKILLPARAM_REVERT_BUTTON_TEXT);
        //添加界面元素
        addRowWidget(lbName, cbValue, cbRef, pbRevert);
        //关联事件
        this->connect(cbValue, SIGNAL(currentIndexChanged(int)), this, SLOT(onArgComboCurrentIndexChanged(int)));
        this->connect(cbRef, SIGNAL(currentIndexChanged(int)), this, SLOT(onArgRefComboCurrentIndexChanged(int)));
        this->connect(pbRevert, SIGNAL(clicked()), this, SLOT(onArgRevertButtonClicked()));
        //缓存数据
        ParamWidgetRowPtr rowPtr = ParamWidgetRowPtr::create();
        rowPtr->_widgetType = ParamWidgetRowInfo::TYPE_COMBO;
        rowPtr->_inputWidget = cbValue;
        rowPtr->_refCombo = cbRef;
        rowPtr->_revertButton = pbRevert;
        rowPtr->_paramPtr = paramPtr;
        rowPtr->_argPtr = argPtr;
        this->_argRows.push_back(rowPtr);
    }
}

void ParamWidget::fillArgComboItems(QComboBox * cbValue, SkillSpecNodeParamPtr argPtr)
{
    if (argPtr == nullptr || cbValue == nullptr) {
        return;
    }

    SkillSpecEnumPtr enumPtr = getSpecEnum(argPtr->getType());
    if (enumPtr == nullptr) {
        return;
    }
    //填充可选项
    const QList<SkillSpecEnumValuePtr>& args = enumPtr->getValues();
    for (size_t idx = 0; idx < args.length(); idx++) {
        SkillSpecEnumValuePtr valuePtr = args[idx];
        QString txt = QStringLiteral("%1").arg(valuePtr->getName());
        cbValue->insertItem(idx, txt, QVariant(valuePtr->getValue()));

        //设置默认值
        if (argPtr->getDefault() == QString(valuePtr->getValue())) {
            cbValue->setCurrentIndex(idx);
        }
    }
}

void ParamWidget::setArgComboItem(QComboBox * cbValue, SkillScriptNodeParamPtr paramPtr)
{
    if (cbValue == nullptr || paramPtr == nullptr) {
        return;
    }
    for (int idx = 0; idx < cbValue->count(); idx++) {
        QVariant userData = cbValue->itemData(idx);
        int itemValue = userData.toInt();
        if (itemValue == paramPtr->getNumber<int>()) {
            cbValue->setCurrentIndex(idx);
            break;
        }
    }
}

void ParamWidget::addNodeCheckedEnumRow(SkillScriptNodeParamPtr paramPtr, SkillSpecNodeParamPtr argPtr)
{
    if (_layout != nullptr) {
        //创建label
        QLabel * lbName = new QLabel(this);
        lbName->setText(QStringLiteral("%1").arg(argPtr->getTitle()));
        //创建ComboBox
        CheckCombo * cbValue = new CheckCombo(this);
        //设置Tooltip
        cbValue->setToolTip(argPtr->getDesc());
        //填充Combox可选项
        fillArgCheckedComboItems(cbValue, argPtr);
        //填充值
        if (paramPtr != nullptr) {
            setArgCheckedComboItem(cbValue, paramPtr);
            cbValue->setEnabled(!paramPtr->isRef());
        }
        //创建索引Combo
        QComboBox * cbRef = new QComboBox(this);
        cbRef->setFixedWidth(SKILLPARAM_REF_COMBO_FIXED_WIDTH);
        fillArgRefItems(cbRef, argPtr);
        setArgRefItem(cbRef, paramPtr);
        //创建恢复按钮
        QPushButton* pbRevert = new QPushButton(this);
        pbRevert->setFixedWidth(SKILLPARAM_REVERT_BUTTON_FIXED_WIDTH);
        pbRevert->setText(SKILLPARAM_REVERT_BUTTON_TEXT);
        //添加界面元素
        addRowWidget(lbName, cbValue, cbRef, pbRevert);
        //关联事件
        this->connect(cbValue, SIGNAL(checkedStateChange(int, bool)), this, SLOT(onArgCheckedComboCurrentIndexChanged(int, bool)));
        this->connect(cbRef, SIGNAL(currentIndexChanged(int)), this, SLOT(onArgRefComboCurrentIndexChanged(int)));
        this->connect(pbRevert, SIGNAL(clicked()), this, SLOT(onArgRevertButtonClicked()));
        //缓存数据
        ParamWidgetRowPtr rowPtr = ParamWidgetRowPtr::create();
        rowPtr->_widgetType = ParamWidgetRowInfo::TYPE_COMBO;
        rowPtr->_inputWidget = cbValue;
        rowPtr->_refCombo = cbRef;
        rowPtr->_revertButton = pbRevert;
        rowPtr->_paramPtr = paramPtr;
        rowPtr->_argPtr = argPtr;
        this->_argRows.push_back(rowPtr);
    }
}

void ParamWidget::fillArgCheckedComboItems(CheckCombo * cbValue, SkillSpecNodeParamPtr argPtr)
{
    if (argPtr == nullptr || cbValue == nullptr) {
        return;
    }

    SkillSpecEnumPtr enumPtr = getSpecEnum(argPtr->getType());
    if (enumPtr == nullptr) {
        return;
    }
    //填充可选项
    const QList<SkillSpecEnumValuePtr>& args = enumPtr->getValues();
    for (size_t idx = 0; idx < args.length(); idx++) {
        SkillSpecEnumValuePtr valuePtr = args[idx];
        QString txt = QStringLiteral("%1").arg(valuePtr->getName());
        int paramVal = argPtr->getDefault().toInt();
        bool isCheck = ((paramVal & valuePtr->getValue()) != 0);
        cbValue->appendItem(txt, isCheck);
        cbValue->setItemData(idx, valuePtr->getValue(), Qt::UserRole + 1);
    }
}

void ParamWidget::setArgCheckedComboItem(CheckCombo * cbValue, SkillScriptNodeParamPtr paramPtr)
{
    if (cbValue == nullptr || paramPtr == nullptr) {
        return;
    }
    for (int idx = 0; idx < cbValue->count(); idx++) {
        int itemValue = cbValue->itemData(idx, Qt::UserRole + 1).toInt();
        int paramVal = paramPtr->getNumber<int>();
        bool isCheck = ((paramVal & itemValue) != 0);
        cbValue->setItemData(idx, isCheck);
        cbValue->updateIndexStatus(idx);
    }
}

void ParamWidget::fillArgRefItems(QComboBox * cbValue, SkillSpecNodeParamPtr argPtr)
{
    if (gSkillSpec == nullptr || argPtr == nullptr || cbValue == nullptr) {
        return;
    }

    SkillSpecEnumPtr enumPtr = getSpecEnum(SKILLPARAM_ENUM_LOGICPARAM_NAME);
    if (enumPtr == nullptr) {
        return;
    }
    //填充可选项
    const QList<SkillSpecEnumValuePtr>& args = enumPtr->getValues();
    for (size_t idx = 0; idx < args.length(); idx++) {
        SkillSpecEnumValuePtr valuePtr = args[idx];
        QString txt = QStringLiteral("%1").arg(valuePtr->getName());
        cbValue->insertItem(idx, txt, QVariant(valuePtr->getValue()));

        //设置默认值
        //cbValue->setCurrentIndex(idx);
    }
}

void ParamWidget::setArgRefItem(QComboBox * cbValue, SkillScriptNodeParamPtr paramPtr)
{
    if (cbValue == nullptr || paramPtr == nullptr) {
        return;
    }

    if (paramPtr->isRef()) {
        for (int idx = 0; idx < cbValue->count(); idx++) {
            QVariant userData = cbValue->itemData(idx);
            int itemValue = userData.toInt();
            if (itemValue == paramPtr->getRef()) {
                cbValue->setCurrentIndex(idx);
                break;
            }
        }
    } else {
        cbValue->setCurrentIndex(0);
    }
}

void ParamWidget::addNodeSpinRow(SkillScriptNodeParamPtr paramPtr, SkillSpecNodeParamPtr argPtr)
{
    if (_layout != nullptr) {
        //创建label
        QLabel * lbName = new QLabel(this);
        lbName->setText(QStringLiteral("%1").arg(argPtr->getTitle()));
        //创建SpinBox
        QSpinBox* cbValue = new QSpinBox(this);
        //设置只在回车后才出发valuechanged信号
        cbValue->setKeyboardTracking(false);
        //设置Tooltip
        cbValue->setToolTip(argPtr->getDesc());
        cbValue->setValue(argPtr->getDefault().toInt());
        int min = Utils::transRangeValue(argPtr->getMin(), std::numeric_limits<int>::min());
        int max = Utils::transRangeValue(argPtr->getMax(), std::numeric_limits<int>::max());
        cbValue->setRange(min, max);
        //填充值
        if (paramPtr != nullptr) {
            cbValue->setValue(paramPtr->getNumber<int>());
            cbValue->setEnabled(!paramPtr->isRef());
        }
        //创建索引Combo
        QComboBox * cbRef = new QComboBox(this);
        cbRef->setFixedWidth(SKILLPARAM_REF_COMBO_FIXED_WIDTH);
        fillArgRefItems(cbRef, argPtr);
        setArgRefItem(cbRef, paramPtr);
        //创建恢复按钮
        QPushButton* pbRevert = new QPushButton(this);
        pbRevert->setFixedWidth(SKILLPARAM_REVERT_BUTTON_FIXED_WIDTH);
        pbRevert->setText(SKILLPARAM_REVERT_BUTTON_TEXT);
        //添加界面元素
        addRowWidget(lbName, cbValue, cbRef, pbRevert);
        //关联事件
        this->connect(cbValue, SIGNAL(valueChanged(int)), this, SLOT(onArgSpinValueChanged(int)));
        this->connect(cbRef, SIGNAL(currentIndexChanged(int)), this, SLOT(onArgRefComboCurrentIndexChanged(int)));
        this->connect(pbRevert, SIGNAL(clicked()), this, SLOT(onArgRevertButtonClicked()));
        //缓存数据
        ParamWidgetRowPtr rowPtr = ParamWidgetRowPtr::create();
        rowPtr->_widgetType = ParamWidgetRowInfo::TYPE_SPIN;
        rowPtr->_inputWidget = cbValue;
        rowPtr->_refCombo = cbRef;
        rowPtr->_revertButton = pbRevert;
        rowPtr->_paramPtr = paramPtr;
        rowPtr->_argPtr = argPtr;
        this->_argRows.push_back(rowPtr);
    }
}

void ParamWidget::addNodeDSpinRow(SkillScriptNodeParamPtr paramPtr, SkillSpecNodeParamPtr argPtr)
{
    if (_layout != nullptr) {
        //创建label
        QLabel * lbName = new QLabel(this);
        lbName->setText(QStringLiteral("%1").arg(argPtr->getTitle()));
        //创建SpinBox
        QDoubleSpinBox* cbValue = new QDoubleSpinBox(this);
        //设置Tooltip
        cbValue->setToolTip(argPtr->getDesc());
        cbValue->setValue(argPtr->getDefault().toDouble());
        double min = Utils::transRangeValue(argPtr->getMin(), std::numeric_limits<double>::min());
        double max = Utils::transRangeValue(argPtr->getMax(), std::numeric_limits<double>::max());
        cbValue->setRange(min, max);
        //填充值
        if (paramPtr != nullptr) {
            cbValue->setValue(paramPtr->getNumber<double>());
            cbValue->setEnabled(!paramPtr->isRef());
        }
        //创建索引Combo
        QComboBox * cbRef = new QComboBox(this);
        cbRef->setFixedWidth(SKILLPARAM_REF_COMBO_FIXED_WIDTH);
        fillArgRefItems(cbRef, argPtr);
        setArgRefItem(cbRef, paramPtr);
        //创建恢复按钮
        QPushButton* pbRevert = new QPushButton(this);
        pbRevert->setFixedWidth(SKILLPARAM_REVERT_BUTTON_FIXED_WIDTH);
        pbRevert->setText(SKILLPARAM_REVERT_BUTTON_TEXT);
        //添加界面元素
        addRowWidget(lbName, cbValue, cbRef, pbRevert);
        //关联事件
        this->connect(cbValue, SIGNAL(valueChanged(double)), this, SLOT(onArgDSpinValueChanged(double)));
        this->connect(cbRef, SIGNAL(currentIndexChanged(int)), this, SLOT(onArgRefComboCurrentIndexChanged(int)));
        this->connect(pbRevert, SIGNAL(clicked()), this, SLOT(onArgRevertButtonClicked()));
        //缓存数据
        ParamWidgetRowPtr rowPtr = ParamWidgetRowPtr::create();
        rowPtr->_widgetType = ParamWidgetRowInfo::TYPE_DOUBLESPIN;
        rowPtr->_inputWidget = cbValue;
        rowPtr->_refCombo = cbRef;
        rowPtr->_revertButton = pbRevert;
        rowPtr->_paramPtr = paramPtr;
        rowPtr->_argPtr = argPtr;
        this->_argRows.push_back(rowPtr);
    }
}

void ParamWidget::addNodeEditRow(SkillScriptNodeParamPtr paramPtr, SkillSpecNodeParamPtr argPtr)
{
    if (_layout != nullptr) {
        //创建label
        QLabel * lbName = new QLabel(this);
        lbName->setText(QStringLiteral("%1").arg(argPtr->getTitle()));
        //创建LineEdit
        QLineEdit * cbValue = new QLineEdit(this);
        //设置Tooltip
        cbValue->setToolTip(argPtr->getDesc());
        cbValue->setText(argPtr->getDefault());
        //填充值
        if (paramPtr != nullptr && paramPtr->isString()) {
            cbValue->setText(paramPtr->getString());
        }
        //创建索引Combo
        QComboBox * cbRef = new QComboBox(this);
        cbRef->setEnabled(false);
        cbRef->setFixedWidth(SKILLPARAM_REF_COMBO_FIXED_WIDTH);
        fillArgRefItems(cbRef, argPtr);
        setArgRefItem(cbRef, paramPtr);
        //创建恢复按钮
        QPushButton* pbRevert = new QPushButton(this);
        pbRevert->setFixedWidth(SKILLPARAM_REVERT_BUTTON_FIXED_WIDTH);
        pbRevert->setText(SKILLPARAM_REVERT_BUTTON_TEXT);
        //添加界面元素
        addRowWidget(lbName, cbValue, cbRef, pbRevert);
        //关联事件
        this->connect(cbValue, SIGNAL(editingFinished()), this, SLOT(onArgEditTxtEditingFinished()));
        this->connect(cbRef, SIGNAL(currentIndexChanged(int)), this, SLOT(onArgRefComboCurrentIndexChanged(int)));
        this->connect(pbRevert, SIGNAL(clicked()), this, SLOT(onArgRevertButtonClicked()));
        //缓存数据
        ParamWidgetRowPtr rowPtr = ParamWidgetRowPtr::create();
        rowPtr->_widgetType = ParamWidgetRowInfo::TYPE_EDIT;
        rowPtr->_inputWidget = cbValue;
        rowPtr->_refCombo = cbRef;
        rowPtr->_revertButton = pbRevert;
        rowPtr->_paramPtr = paramPtr;
        rowPtr->_argPtr = argPtr;
        this->_argRows.push_back(rowPtr);
    }
}
void ParamWidget::addRowWidget(QLabel* lbName, QWidget* nodeWidget, QComboBox* cbRef, QPushButton* pbRevert)
{
    if (_layout != nullptr) {
        //创建值域Widget
        QWidget* fieldWidget = new QWidget(this);
        fieldWidget->setContentsMargins(0, 0, 0, 0);
        QHBoxLayout *fieldLayout = new QHBoxLayout(fieldWidget);
        fieldLayout->setMargin(0);
        fieldWidget->setLayout(fieldLayout);

        //增加值域Widget
        fieldLayout->addWidget(nodeWidget);
        //增加值域CheckCombo
        fieldLayout->addWidget(cbRef);
        //增加值域PushButton
        fieldLayout->addWidget(pbRevert);

        //增加到Form布局窗口
        _layout->addRow(lbName, fieldWidget);
    }
}

ParamWidgetRowPtr ParamWidget::getRowByInputWidget(QWidget* widget)
{
    for (int idx = 0; idx < _argRows.length(); idx++) {
        ParamWidgetRowPtr rowPtr = _argRows[idx];
        if (rowPtr != nullptr && rowPtr->_inputWidget == widget) {
            return rowPtr;
        }
    }
    return ParamWidgetRowPtr();
}

ParamWidgetRowPtr ParamWidget::getRowByRefCombo(QWidget* checkbox)
{
    for (int idx = 0; idx < _argRows.length(); idx++) {
        ParamWidgetRowPtr rowPtr = _argRows[idx];
        if (rowPtr != nullptr && rowPtr->_refCombo == checkbox) {
            return rowPtr;
        }
    }
    return ParamWidgetRowPtr();
}

ParamWidgetRowPtr ParamWidget::getRowByRevertButton(QPushButton* button)
{
    for (int idx = 0; idx < _argRows.length(); idx++) {
        ParamWidgetRowPtr rowPtr = _argRows[idx];
        if (rowPtr != nullptr && rowPtr->_revertButton == button) {
            return rowPtr;
        }
    }
    return ParamWidgetRowPtr();
}

