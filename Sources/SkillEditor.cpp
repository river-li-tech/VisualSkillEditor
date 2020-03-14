#include "stdafx.h"
#include "Dict.h"
#include <QMouseEvent>
#include <QEvent>
#include <qdesktopservices.h>
#include "SettingsDialog.h"
#include "SkillEditor.h"
#include "SkillInst.h"
#include "SkillGfx.h"
#include "SkillScript.h"
#include "SkillSpec.h"
#include "Settings.h"
#include "Utils.h"

SkillEditor::SkillEditor(QWidget *parent)
: QMainWindow(parent)
{
    _ui.setupUi(this);
    _skillTableRows.clear();
    _paramTableRows.clear();

    this->initActions();
    this->readSettings();

    this->setWindowTitle(gDict->PROG_NAME + gDict->DEFAULT_UNSAVED_PATH + gDict->DEFAULT_UNSAVED_PATH);
    setUnifiedTitleAndToolBarOnMac(true);
}

bool SkillEditor::loadWorkspace()
{
    QString instFile = gSkillEditor->getSkillInstDir() + SKILLINST_FILE_NAME;
    if (!loadInstFileAs(instFile)) {
        return false;
    }
    QString gfxFile = gSkillEditor->getSkillGfxDir() + SKILLGFX_FILE_NAME;
    if (!loadGfxFileAs(gfxFile)) {
        return false;
    }
    return true;
}

void SkillEditor::initActions()
{
    //注册按钮监听
    this->connect(this->_ui.actionNewInstFile, &QAction::triggered, this, &SkillEditor::doNewInstFile);
    this->connect(this->_ui.actionOpenInstFile, &QAction::triggered, this, &SkillEditor::doOpenInstFile);
    this->connect(this->_ui.actionSaveInstFile, &QAction::triggered, this, &SkillEditor::doSaveInstFile);
    this->connect(this->_ui.actionSaveInstFileAs, &QAction::triggered, this, &SkillEditor::doSaveInstFileAs);
    this->connect(this->_ui.actionNewScriptFile, &QAction::triggered, this, &SkillEditor::doNewScriptFile);
    this->connect(this->_ui.actionOpenScriptFile, &QAction::triggered, this, &SkillEditor::doOpenScriptFile);
    this->connect(this->_ui.actionSaveScriptFile, &QAction::triggered, this, &SkillEditor::doSaveScriptFile);
    this->connect(this->_ui.actionSaveScriptFileAs, &QAction::triggered, this, &SkillEditor::doSaveScriptFileAs);
    this->connect(this->_ui.actionSelectScriptFile, &QAction::triggered, this, &SkillEditor::doSelectScriptFile);
    this->connect(this->_ui.actionSaveAll, &QAction::triggered, this, &SkillEditor::doSaveAll);
    this->connect(this->_ui.actionSettings, &QAction::triggered, this, &SkillEditor::doSettings);
    this->connect(this->_ui.actionExit, &QAction::triggered, this, &SkillEditor::doExit);
    this->connect(this->_ui.actionAddSkill, &QAction::triggered, this, &SkillEditor::doAddSkill);
    this->connect(this->_ui.actionDeleteSkill, &QAction::triggered, this, &SkillEditor::doDeleteSkill);
    this->connect(this->_ui.actionAddChildNode, &QAction::triggered, this, &SkillEditor::doAddChildNode);
    this->connect(this->_ui.actionAddPrevNode, &QAction::triggered, this, &SkillEditor::doAddPrevNode);
    this->connect(this->_ui.actionAddNextNode, &QAction::triggered, this, &SkillEditor::doAddNextNode);
    this->connect(this->_ui.actionMoveNodeUp, &QAction::triggered, this, &SkillEditor::doMoveNodeUp);
    this->connect(this->_ui.actionMoveNodeDown, &QAction::triggered, this, &SkillEditor::doMoveNodeDown);
    this->connect(this->_ui.actionMoveNodeParent, &QAction::triggered, this, &SkillEditor::doMoveNodeParent);
    this->connect(this->_ui.actionMoveNodeChild, &QAction::triggered, this, &SkillEditor::doMoveNodeChild);
    this->connect(this->_ui.actionDeleteNode, &QAction::triggered, this, &SkillEditor::doDeleteNode);
    this->connect(this->_ui.actionCopyNode, &QAction::triggered, this, &SkillEditor::doCopyNode);
    this->connect(this->_ui.actionCutNode, &QAction::triggered, this, &SkillEditor::doCutNode);
    this->connect(this->_ui.actionPasteNode, &QAction::triggered, this, &SkillEditor::doPasteNode);
    this->connect(this->_ui.actionSkillHelp, &QAction::triggered, this, &SkillEditor::doSkillHelp);
    this->connect(this->_ui.actionEditorHelp, &QAction::triggered, this, &SkillEditor::doEditorHelp);
    this->connect(this->_ui.actionSkillScriptHelp, &QAction::triggered, this, &SkillEditor::doScriptHelp);
    this->connect(this->_ui.actionShowIcons, &QAction::triggered, this, &SkillEditor::doShowIcons);
    this->connect(this->_ui.actionSerialText, &QAction::triggered, this, &SkillEditor::doSerialText);
    this->connect(this->_ui.actionAbout, &QAction::triggered, this, &SkillEditor::doAbout);

    //注册技能表格监听
    QTableWidget *pTableSkill = this->_ui.instTable;
    if (pTableSkill != nullptr) {
        this->connect(pTableSkill, &QTableWidget::itemChanged, this, &SkillEditor::onTableInstItemChanged);
        this->connect(pTableSkill->selectionModel(), &QItemSelectionModel::selectionChanged, this, &SkillEditor::onTableInstSelectionChanged);
        //初始化右键菜单
        _tableCtxMenu = new QMenu(this);
        _tableCtxMenu->addAction(this->_ui.actionAddSkill);
        _tableCtxMenu->addAction(this->_ui.actionDeleteSkill);
        _tableCtxMenu->addAction(this->_ui.actionNewScriptFile);
        _tableCtxMenu->addAction(this->_ui.actionNewScriptFile);
        _tableCtxMenu->addAction(this->_ui.actionSelectScriptFile);
        _tableCtxMenu->addAction(this->_ui.actionSaveScriptFile);
        _tableCtxMenu->addAction(this->_ui.actionSaveScriptFileAs);
        //注册拖拽行为和按键
        pTableSkill->installEventFilter(this);
    }
    QTableWidget *pTableParam = this->_ui.instParamTable;
    if (pTableParam != nullptr) {
        this->connect(pTableParam, &QTableWidget::itemChanged, this, &SkillEditor::onTableInstParamItemChanged);
        this->connect(pTableParam, &QTableWidget::itemSelectionChanged, this, &SkillEditor::onTableInstParamItemSelectionChanged);
    }

    QTreeWidget *pTreeSkill = this->_ui.scriptTree;
    if (pTreeSkill != nullptr) {
        this->connect(pTreeSkill, &QTreeWidget::itemSelectionChanged, this, &SkillEditor::onTreeScriptItemSelectionChanged);
        this->connect(pTreeSkill, &QTreeWidget::itemCollapsed, this, &SkillEditor::onTreeScriptItemCollapsed);
        this->connect(pTreeSkill, &QTreeWidget::itemExpanded, this, &SkillEditor::onTreeScriptItemExpanded);
        //初始化右键菜单
        _treeCtxMenu = new QMenu(this);
        _treeCtxMenu->addMenu(this->_ui.menuAddNode);
        _treeCtxMenu->addMenu(this->_ui.menuMoveNode);
        _treeCtxMenu->addAction(this->_ui.actionDeleteNode);
        _treeCtxMenu->addAction(this->_ui.actionCutNode);
        _treeCtxMenu->addAction(this->_ui.actionCopyNode);
        _treeCtxMenu->addAction(this->_ui.actionPasteNode);
        //注册拖拽行为和按键
        pTreeSkill->installEventFilter(this);
    }

    QTextEdit *pNodeRemark = this->_ui.nodeRemarkEdit;
    if (pNodeRemark != nullptr) {
        this->connect(pNodeRemark, SIGNAL(textChanged()), this, SLOT(onEditNodeRemarkTextChanged()));
    }
    QTextEdit *pRefRemark = this->_ui.refRemarkEdit;
    if (pNodeRemark != nullptr) {
        this->connect(pRefRemark, SIGNAL(textChanged()), this, SLOT(onEditRefRemarkTextChanged()));
    }

    //注册数据监听
    this->connect(gSkillInst, &SkillInst::instChanged, this, &SkillEditor::onSkillInstChanged);
    this->connect(gSkillInst, &SkillInst::dataChanged, this, &SkillEditor::onSkillInstDataChanged);

    this->connect(gSkillScript, &SkillScript::scriptChanged, this, &SkillEditor::onSkillScriptChanged);
    this->connect(gSkillScript, &SkillScript::nodeChanged, this, &SkillEditor::onSkillScriptNodeChanged);
    this->connect(gSkillScript, &SkillScript::paramChanged, this, &SkillEditor::onSkillScriptNodeParamChanged);

    //定时器
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    _timer->start(INTERVAL_AUTO_SAVE);

    //配置项
    this->_ui.actionShowIcons->setChecked(gSettings->isShowIcons());
    this->_ui.actionSerialText->setChecked(gSettings->isSerialTxt());
}

void SkillEditor::loadTableInst(const SkillInst& pool)
{
    QTableWidget *tableSkills = this->_ui.instTable;
    if (tableSkills != nullptr) {
        //重新添加
        const QList<SkillInstDataPtr>& cfgs = pool.getDatas();
        if (cfgs.length() > 0) {
            for (int rowIdx = 0; rowIdx < cfgs.length(); rowIdx++) {
                SkillInstDataPtr cfgPtr = cfgs.at(rowIdx);
                if (cfgPtr != nullptr) {
                    int rowIdx = this->addRow2TableInst(*cfgPtr);
                    if (rowIdx >= 0 && cfgPtr->isSelected()) {
                        this->_ui.instTable->selectRow(rowIdx);
                    }
                }
            }
        }
    }
}

void SkillEditor::clearTableInst()
{
    this->_skillTableRows.clear();
    QTableWidget *tableSkills = this->_ui.instTable;
    if (tableSkills != nullptr) {
        while (tableSkills->rowCount() > 0) {
            tableSkills->removeRow(0);
        }
        tableSkills->clearContents();
    }
}

int SkillEditor::addRow2TableInst(const SkillInstData& cfg)
{
    QTableWidget *tableSkills = this->_ui.instTable;
    if (tableSkills != nullptr) {
        //技能表格
        TableRowPtr rowPtr = TableRowPtr::create(cfg.getId());
        rowPtr->addItem(QString("%0").arg(cfg.getId()), true);
        rowPtr->addItem(QString("%0").arg(cfg.getDesc()), true);
        rowPtr->addItem(QString("%0").arg(cfg.getIsClientSkill()), gSettings->isSerialTxt());
        rowPtr->addItem(QString("%0").arg(cfg.getLogicFile()), true);

        // add to container 
        this->_skillTableRows.append(rowPtr);
        rowPtr->addToWidget(*tableSkills);
        return rowPtr->getRowIdx();
    }
    return -1;
}

void SkillEditor::removeRow4TableInst(const SkillInstData& cfg)
{
    QTableWidget *tableSkills = this->_ui.instTable;
    if (tableSkills != nullptr) {
        TableRowPtr rowPtr = getTableRowById(_skillTableRows, cfg.getId());
        if (rowPtr != nullptr) {
            rowPtr->removeFromWidget(*tableSkills);
            this->_skillTableRows.removeOne(rowPtr);
        }
    }
}

void SkillEditor::loadTableInstParam(const SkillInstData& cfg)
{
    QTableWidget *tableParam = this->_ui.instParamTable;
    if (tableParam != nullptr) {
        //重新添加
        this->addRow2TableInstParam(cfg);
    }
}

void SkillEditor::clearTableInstParam()
{
    this->_paramTableRows.clear();
    QTableWidget *tableParam = this->_ui.instParamTable;
    if (tableParam != nullptr) {
        while (tableParam->rowCount() > 0) {
            tableParam->removeRow(0);
        }
        tableParam->clearContents();
    }
}

void SkillEditor::addRow2TableInstParam(const SkillInstData& cfg)
{
    QTableWidget *tableParam = this->_ui.instParamTable;
    if (tableParam != nullptr) {
        //技能表格
        TableRowPtr rowPtr = TableRowPtr::create(cfg.getId());
        for (int idx = 0; idx < SKILLINST_LOGIC_PARAM_COUNT; idx++) {
            rowPtr->addItem(QString("%0").arg(cfg.getLogicParamByIdx(idx)), true);
        }

        // add to container 
        this->_paramTableRows.append(rowPtr);
        rowPtr->addToWidget(*tableParam);
    }
}

void SkillEditor::removeRow4TableInstParam(const SkillInstData& cfg)
{
    QTableWidget *tableParam = this->_ui.instParamTable;
    if (tableParam != nullptr) {
        TableRowPtr rowPtr = getTableRowById(_paramTableRows, cfg.getId());
        if (rowPtr != nullptr) {
            rowPtr->removeFromWidget(*tableParam);
            this->_paramTableRows.removeOne(rowPtr);
        }
    }
}

void SkillEditor::loadTreeScript(const SkillScript& cfg)
{
    //加载
    QTreeWidget *treeWidget = this->_ui.scriptTree;
    if (treeWidget != nullptr) {
        treeWidget->setColumnCount(1);
        //构造树
        QTreeWidgetItem *rootItem = new QTreeWidgetItem(treeWidget);
        rootItem->setText(0, cfg.getFileName());
        cfg.toTree(rootItem);

        if (gSkillScript->getSelectedNode() != nullptr) {
            selectTreeScriptNode(*gSkillScript->getSelectedNode());
        }
    }
}

void SkillEditor::clearTreeScript()
{
    QTreeWidget *treeWidget = this->_ui.scriptTree;
    if (treeWidget != nullptr) {
        treeWidget->clear();
    }
}

void SkillEditor::selectTreeScriptNode(SkillScriptNode& node, bool notifyTree)
{
    node.setSelected(true);
    if (notifyTree) {
        QTreeWidget *treeWidget = this->_ui.scriptTree;
        QTreeWidgetItem * treeItem = node.getTreeItem();
        if (treeItem != nullptr && treeWidget != nullptr) {
            treeWidget->setCurrentItem(treeItem);
        }
    }
}

void SkillEditor::unselectScriptNodes()
{
    QList<SkillScriptNode*> list;
    if (gSkillScript->getSelectedNodes(list)) {
        for (int idx = 0; idx < list.length(); idx++) {
            SkillScriptNode* node = list.at(idx);
            if (node != nullptr) {
                node->setSelected(false);
            }
        }
    }
}

void SkillEditor::loadWidgetParam(SkillScriptNode& node)
{
    ParamWidget *detailWidget = this->_ui.paramWidget;
    if (detailWidget != nullptr) {
        detailWidget->loadView(&node);
    }
    loadNodeRemark(node.getInfo());
}

void SkillEditor::clearWidgetParam()
{
    ParamWidget *detailWidget = this->_ui.paramWidget;
    if (detailWidget != nullptr) {
        detailWidget->clearView();
    }
    clearNodeRemark();
}

void SkillEditor::clearNodeRemark()
{
    QTextEdit *txtInfo = this->_ui.nodeRemarkEdit;
    if (txtInfo != nullptr) {
        bool isBlockedOld = txtInfo->blockSignals(true);
        txtInfo->setText("");
        txtInfo->blockSignals(isBlockedOld);
    }
}

void SkillEditor::loadNodeRemark(const QString& txt)
{
    QTextEdit *txtInfo = this->_ui.nodeRemarkEdit;
    if (txtInfo != nullptr) {
        bool isBlockedOld = txtInfo->blockSignals(true);
        txtInfo->setText(txt);
        txtInfo->blockSignals(isBlockedOld);
    }
}

void SkillEditor::clearRefRemark()
{
    QTextEdit *txtInfo = this->_ui.refRemarkEdit;
    if (txtInfo != nullptr) {
        bool isBlockedOld = txtInfo->blockSignals(true);
        txtInfo->setText("");
        txtInfo->blockSignals(isBlockedOld);
    }
}

void SkillEditor::loadRefRemark(const QString& txt)
{
    QTextEdit *txtInfo = this->_ui.refRemarkEdit;
    if (txtInfo != nullptr) {
        bool isBlockedOld = txtInfo->blockSignals(true);
        txtInfo->setText(txt);
        txtInfo->blockSignals(isBlockedOld);
    }
}

///////////////////////////////////////////////////////////////////////////
//获取保存Inst文件地址
QString SkillEditor::getSaveInstFilePath()
{
    QString curDir = getSkillInstDir();
    return QFileDialog::getSaveFileName(this, gDict->TXT_NEW_FILE, curDir, tr("All Files(*);;Excel Files (*.excel);;Txt files (*.txt)"));
}

//获取打开Inst文件地址
QString SkillEditor::getOpenInstFilePath()
{
    QString curDir = getSkillInstDir();
    return QFileDialog::getOpenFileName(this, gDict->TXT_OPEN_FILE, curDir, tr("All Files(*);;Excel Files (*.excel);;Txt files (*.txt)"));
}

//获取保存Gfx文件地址
QString SkillEditor::getSaveGfxFilePath()
{
    QString curDir = getSkillGfxDir();
    return QFileDialog::getSaveFileName(this, gDict->TXT_NEW_FILE, curDir, tr("All Files(*);;Excel Files (*.excel);;Txt files (*.txt)"));
}

//获取打开Gfx文件地址
QString SkillEditor::getOpenGfxFilePath()
{
    QString curDir = getSkillGfxDir();
    return QFileDialog::getOpenFileName(this, gDict->TXT_OPEN_FILE, curDir, tr("All Files(*);;Excel Files (*.excel);;Txt files (*.txt)"));
}

//获取保存Script文件地址
QString SkillEditor::getSaveScriptFilePath()
{
    QString curDir = getSkillScriptDir();
    return QFileDialog::getSaveFileName(this, gDict->TXT_NEW_FILE, curDir, tr("All Files(*);;Script files (*.xml)"));
}

//获取打开Inst文件地址
QString SkillEditor::getOpenScriptFilePath()
{
    QString curDir = getSkillScriptDir();
    return QFileDialog::getOpenFileName(this, gDict->TXT_OPEN_FILE, curDir, tr("All Files(*);;Script files (*.xml)"));
}

//获取打开Script文件地址
bool SkillEditor::loadInstFileAs(const QString &filePath)
{
    gSkillInst->clear();
    bool ret = gSkillInst->loadFile(filePath);
    if (ret) {
        statusBar()->showMessage(gDict->TXT_OPEN_FILE_SUCCESS, STATUS_BAR_MESSAGE_WAIT_TIME);
        this->updateWindowTitle();
    } else {
        QMessageBox::warning(this, gDict->PROG_NAME,
            gDict->TXT_OPEN_FILE_FAILED.arg(filePath));
        gSkillInst->clear();
    }
    return ret;
}

//保存Inst文件
bool SkillEditor::saveInstFileAs(const QString &filePath)
{
    bool ret = gSkillInst->saveFile(filePath);
    if (ret) {
        statusBar()->showMessage(gDict->TXT_SAVE_FILE_SUCCESS, STATUS_BAR_MESSAGE_WAIT_TIME);
        this->updateWindowTitle();
    } else {
        QMessageBox::warning(this, gDict->PROG_NAME,
            gDict->TXT_SAVE_FILE_FAILED.arg(filePath));
    }
    return ret;
}

//获取打开Gfx文件地址
bool SkillEditor::loadGfxFileAs(const QString &filePath)
{
    gSkillGfx->clear();
    bool ret = gSkillGfx->loadFile(filePath);
    if (ret) {
        statusBar()->showMessage(gDict->TXT_OPEN_FILE_SUCCESS, STATUS_BAR_MESSAGE_WAIT_TIME);
        this->updateWindowTitle();
    } else {
        QMessageBox::warning(this, gDict->PROG_NAME,
            gDict->TXT_OPEN_FILE_FAILED.arg(filePath));
        gSkillInst->clear();
    }
    return ret;
}

//保存Inst文件
bool SkillEditor::saveGfxFileAs(const QString &filePath)
{
    bool ret = gSkillGfx->saveFile(filePath);
    if (ret) {
        statusBar()->showMessage(gDict->TXT_SAVE_FILE_SUCCESS, STATUS_BAR_MESSAGE_WAIT_TIME);
        this->updateWindowTitle();
    } else {
        QMessageBox::warning(this, gDict->PROG_NAME,
            gDict->TXT_SAVE_FILE_FAILED.arg(filePath));
    }
    return ret;
}

//载入Script文件
bool SkillEditor::loadScriptFileAs(const QString &filePath)
{
    gSkillScript->clear();
    bool ret = gSkillScript->loadFile(filePath);
    if (ret) {
        statusBar()->showMessage(gDict->TXT_OPEN_FILE_SUCCESS, STATUS_BAR_MESSAGE_WAIT_TIME);
        this->updateWindowTitle();
    } else {
        QMessageBox::warning(this, gDict->PROG_NAME,
            gDict->TXT_OPEN_FILE_FAILED.arg(filePath));
    }
    return ret;
}

//保存Skill Script文件
bool SkillEditor::saveScriptFileAs(const QString &filePath)
{
    bool ret = gSkillScript->saveFile(filePath);
    if (ret) {
        statusBar()->showMessage(gDict->TXT_SAVE_FILE_SUCCESS, STATUS_BAR_MESSAGE_WAIT_TIME);
        this->updateWindowTitle();
    } else {
        QMessageBox::warning(this, gDict->PROG_NAME,
            gDict->TXT_SAVE_FILE_FAILED.arg(filePath));
    }
    return ret;
}

//载入Skill Script文件
void SkillEditor::loadScriptFile(const SkillInstData& cfg)
{
    //加载新文件
    if (cfg.getLogicFile().length() > 0) {
        QString filePath = getSkillScriptRelativeDir() + cfg.getLogicFile();
        loadScriptFileAs(filePath);
    }
}

void SkillEditor::updateWindowTitle()
{
    QString title = gDict->PROG_NAME;
    title += QStringLiteral("【SkillInst:%1】").arg(gSkillInst->getFilePath());
    title += QStringLiteral("【SkillScript:%1】").arg(gSkillScript->getFilePath());
    title += "/";
    this->setWindowTitle(title);
}

QString SkillEditor::getSkillInstDir()
{
    QString curDir = gSkillInst->getFileDir();
    if (!curDir.isEmpty()) {
        return curDir;
    } else if (!gSettings->getCustomSkillInstDir().isEmpty()) {
        return QDir::currentPath() + gSettings->getCustomSkillInstDir();
    } else if (!SKILLINST_WORK_DIR_DEFAULT.isEmpty()) {
        return QDir::currentPath() + SKILLINST_WORK_DIR_DEFAULT;
    } else {
        return QDir::currentPath();
    }
}

QString SkillEditor::getSkillGfxDir()
{
    if (!gSettings->getCustomSkillGfxDir().isEmpty()) {
        return QDir::currentPath() + gSettings->getCustomSkillGfxDir();
    } else if (!SKILLGFX_WORK_DIR_DEFAULT.isEmpty()) {
        return QDir::currentPath() + SKILLGFX_WORK_DIR_DEFAULT;
    } else {
        return QDir::currentPath();
    }
}

QString SkillEditor::getSkillScriptDir()
{
    if (!gSettings->getCustomSkillScriptDir().isEmpty()) {
        return QDir::currentPath() + QString(gSettings->getCustomSkillScriptDir());
    } else if (!SKILLSCRIPT_WORK_DIR_DEFAULT.isEmpty()) {
        return QDir::currentPath() + QString(SKILLSCRIPT_WORK_DIR_DEFAULT);
    } else {
        return QDir::currentPath();
    }
}

QString SkillEditor::getSkillScriptRelativeDir()
{
    if (!gSettings->getCustomSkillScriptDir().isEmpty()) {
        return QDir::currentPath() + gSettings->getCustomSkillScriptDir();
    } else if (!SKILLSCRIPT_WORK_DIR_DEFAULT.isEmpty()) {
        return QDir::currentPath() + QString(SKILLSCRIPT_WORK_DIR_DEFAULT);
    } else {
        return QDir::currentPath();
    }
}

///////////////////////////////////////////////////////////////////////////
// settings read and write
void SkillEditor::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
            (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }

    this->_ui.actionShowIcons->setChecked(gSettings->isShowIcons());
    this->_ui.actionSerialText->setChecked(gSettings->isSerialTxt());
}

void SkillEditor::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());

    gSettings->writeSettings();
}

//////////////////////////////////////////////////////////////////////////
// slots and event
void SkillEditor::doNewInstFile()
{
    QString fileName = this->getSaveInstFilePath();
    if (!fileName.isEmpty()) {
        gSkillInst->clear();
        saveInstFileAs(fileName);
    }
}

void SkillEditor::doOpenInstFile()
{
    QString fileName = this->getOpenInstFilePath();
    if (!fileName.isEmpty()) {
        gSkillInst->clear();
        loadInstFileAs(fileName);
    }
}

bool SkillEditor::doSaveInstFile()
{
    QString curFilePath = gSkillInst->getFilePath();
    if (curFilePath.isEmpty()) {
        curFilePath = this->getSaveInstFilePath();
    }
    if (!curFilePath.isEmpty()) {
        return saveInstFileAs(curFilePath);
    }
    return false;
}

bool SkillEditor::doSaveInstFileAs()
{
    QString curFilePath = this->getSaveInstFilePath();
    if (!curFilePath.isEmpty()) {
        return saveInstFileAs(curFilePath);
    }
    return false;
}

void SkillEditor::doOpenGfxFile()
{
    QString fileName = this->getOpenGfxFilePath();
    if (!fileName.isEmpty()) {
        gSkillGfx->clear();
        loadGfxFileAs(fileName);
    }
}

bool SkillEditor::doSaveGfxFile()
{
    QString curFilePath = gSkillGfx->getFilePath();
    if (curFilePath.isEmpty()) {
        curFilePath = this->getSaveGfxFilePath();
    }
    if (!curFilePath.isEmpty()) {
        return saveGfxFileAs(curFilePath);
    }
    return false;
}

bool SkillEditor::doSaveGfxFileAs()
{
    QString curFilePath = this->getSaveGfxFilePath();
    if (!curFilePath.isEmpty()) {
        return saveGfxFileAs(curFilePath);
    }
    return false;
}

void SkillEditor::doNewScriptFile()
{
    QString fileName = this->getSaveScriptFilePath();
    if (!fileName.isEmpty()) {
        gSkillScript->clear();
        if (saveScriptFileAs(fileName)) {
            //Note:如果选中Inst某一行，创建Skill Script自动关联到其ScriptFile列
            SkillInstDataPtr cfgPtr = getCurInstData();
            if (cfgPtr != nullptr) {
                cfgPtr->setLogicFile(gSkillScript->getRelFileName(getSkillScriptDir()));
            }
        }
    }
}

void SkillEditor::doOpenScriptFile()
{
    QString fileName = this->getOpenScriptFilePath();
    if (!fileName.isEmpty()) {
        gSkillScript->clear();
        loadScriptFileAs(fileName);
    }
}

bool SkillEditor::doSaveScriptFile()
{
    QString curFilePath = gSkillScript->getFilePath();
    if (!curFilePath.isEmpty()) {
        return saveScriptFileAs(curFilePath);
    }
    return false;
}

bool SkillEditor::doSaveScriptFileAs()
{
    QString curFilePath = this->getSaveScriptFilePath();
    if (!curFilePath.isEmpty()) {
        return saveScriptFileAs(curFilePath);
    }
    return false;
}

void SkillEditor::doSelectScriptFile()
{
    //Note:无需提示，直接保存原Skill Script文件，并清除数据
    doSaveScriptFile();
    gSkillScript->clear();

    QString fileName = this->getOpenScriptFilePath();
    if (!fileName.isEmpty()) {
        gSkillScript->clear();
        if (loadScriptFileAs(fileName)) {
            //Note:如果选中Inst某一行，创建Skill Script自动关联到其ScriptFile列
            SkillInstDataPtr cfgPtr = getCurInstData();
            if (cfgPtr != nullptr) {
                cfgPtr->setLogicFile(gSkillScript->getRelFileName(getSkillScriptDir()));
            }
        }
    }
}

bool SkillEditor::doSaveAll()
{
    syncCurSkillAction(getCurInstData());
    clearAllInvalidSkillActions();
    doSaveInstFile();
    doSaveGfxFile();
    doSaveScriptFile();
    statusBar()->showMessage(gDict->TXT_ALL_SAVED, STATUS_BAR_MESSAGE_WAIT_TIME);
    return true;
}

bool SkillEditor::doSettings()
{
    SettingsDialog dlg;
    int code = dlg.exec();
    //////////////////////////////////////////////
    //执行一些需要立即生效的效果
    this->_ui.actionShowIcons->setChecked(gSettings->isShowIcons());
    this->_ui.actionSerialText->setChecked(gSettings->isSerialTxt());
    return true;
}

bool SkillEditor::doExit()
{
    QApplication::quit();
    return true;
}

bool SkillEditor::doAddChildNode()
{
    SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();
    if (_curSelectedNode != nullptr) {
        SkillScriptNodePtr nodePtr = SkillScriptNodePtr::create(gSkillScript);
        int curCls = getNodeCls(*_curSelectedNode);
        if (curCls > 0) {
            nodePtr->setId(SKILLSCRIPT_ADD_SKILL_NODE_ID);
        } else {
            nodePtr->setId(SKILLSCRIPT_ADD_SKILL_SECTION_ID);
        }
        if (checkNodeClsLimit(*nodePtr, curCls + 1)) {
            _curSelectedNode->addNode(nodePtr);
            selectTreeScriptNode(*nodePtr);
        } else {
            QMessageBox::information(NULL, gDict->PROG_NAME, gDict->TXT_ADD_CHILD_NODE_FAILED);
        }
    }
    return true;
}

bool SkillEditor::doAddSkill()
{
    SkillInstDataPtr cfgPtr = SkillInstDataPtr::create();
    if (cfgPtr != nullptr && gSkillInst != nullptr) {
        cfgPtr->setId(gSkillInst->getMaxId() + 1);
        cfgPtr->setParent(gSkillInst);
        bool ret = gSkillInst->addData(cfgPtr);
        if (!ret) {
            QMessageBox::warning(this, gDict->PROG_NAME,
                gDict->TXT_SKILL_INST_SAME_ID);
        }
    }
    return true;
}

bool SkillEditor::doDeleteSkill()
{
    SkillInstDataPtr cfgPtr = getCurInstData();
    if (cfgPtr != nullptr) {
        //计算下次选中行
        int curRowIdx = getTableRowIdxById(this->_skillTableRows, cfgPtr->getId());

        //询问是否删除脚本文件
        //bool isDeleteScript = false;
        //if (!cfgPtr->getLogicFile().isEmpty()) {
        //    QMessageBox::StandardButton reply;
        //    reply = QMessageBox::question(this, gDict->PROG_NAME,
        //        gDict->TXT_SKILL_INST_DELETE_SCRIPT,
        //        QMessageBox::Yes | QMessageBox::No);
        //    if (reply == QMessageBox::Yes) {
        //        isDeleteScript = true;

        //    }
        //}

        //删除行数据
        gSkillInst->removeData(cfgPtr->getId());
        gSkillScript->clear();

        ////询问是否删除脚本文件
        //if (isDeleteScript) {
        //    QString scriptFilePath = getSkillScriptRelativeDir() + cfgPtr->getLogicFile();
        //    QFileInfo fileInfo(scriptFilePath);
        //    if (fileInfo.exists()) {
        //        QFile::remove(scriptFilePath);
        //    }
        //}

        //选中下一行
        if (curRowIdx >= 0) {
            if (curRowIdx >= this->_skillTableRows.length()) {
                curRowIdx = this->_skillTableRows.length() - 1;
            }
            this->_ui.instTable->selectRow(curRowIdx);
        }
    }
    return true;
}

bool SkillEditor::doAddPrevNode()
{
    SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();
    if (_curSelectedNode != nullptr) {
        SkillScriptNode* parent = _curSelectedNode->getParent();
        if (parent != nullptr) {
            SkillScriptNodePtr nodePtr = SkillScriptNodePtr::create(gSkillScript);
            int curCls = getNodeCls(*parent);
            if (curCls > 0) {
                nodePtr->setId(SKILLSCRIPT_ADD_SKILL_NODE_ID);
            } else {
                nodePtr->setId(SKILLSCRIPT_ADD_SKILL_SECTION_ID);
            }
            if (checkNodeClsLimit(*nodePtr, curCls + 1)) {
                int curIdx = getNodeIdx(_curSelectedNode);
                parent->addNode(nodePtr, curIdx);
                selectTreeScriptNode(*nodePtr);
            } else {
                QMessageBox::information(NULL, gDict->PROG_NAME, gDict->TXT_ADD_CHILD_NODE_FAILED);
            }
        }
    }
    return true;
}

bool SkillEditor::doAddNextNode()
{
    SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();
    if (_curSelectedNode != nullptr) {
        SkillScriptNode* parent = _curSelectedNode->getParent();
        if (parent != nullptr) {
            SkillScriptNodePtr nodePtr = SkillScriptNodePtr::create(gSkillScript);
            int curCls = getNodeCls(*parent);
            if (curCls > 0) {
                nodePtr->setId(SKILLSCRIPT_ADD_SKILL_NODE_ID);
            } else {
                nodePtr->setId(SKILLSCRIPT_ADD_SKILL_SECTION_ID);
            }
            if (checkNodeClsLimit(*nodePtr, curCls + 1)) {
                int curIdx = getNodeIdx(_curSelectedNode);
                parent->addNode(nodePtr, curIdx + 1);
                selectTreeScriptNode(*nodePtr);
            } else {
                QMessageBox::information(NULL, gDict->PROG_NAME, gDict->TXT_ADD_CHILD_NODE_FAILED);
            }
        }
    }
    return true;
}

bool SkillEditor::doMoveNodeUp()
{
    SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();
    if (_curSelectedNode != nullptr) {
        SkillScriptNode* parent = _curSelectedNode->getParent();
        if (parent != nullptr) {
            parent->moveNode(_curSelectedNode, true);
            selectTreeScriptNode(*_curSelectedNode);
        }
    }
    return true;
}

bool SkillEditor::doMoveNodeDown()
{
    SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();
    if (_curSelectedNode != nullptr) {
        SkillScriptNode* parent = _curSelectedNode->getParent();
        if (parent != nullptr) {
            parent->moveNode(_curSelectedNode, false);
            selectTreeScriptNode(*_curSelectedNode);
        }
    }
    return true;
}

bool SkillEditor::doMoveNodeParent()
{
    SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();
    if (_curSelectedNode != nullptr) {
        SkillScriptNode* parent = _curSelectedNode->getParent();
        if (parent != nullptr) {
            SkillScriptNodePtr nodePtr = asNodePtr(_curSelectedNode);
            SkillScriptNode* grandParent = parent->getParent();
            if (nodePtr != nullptr && grandParent != nullptr) {
                int curCls = getNodeCls(*grandParent);
                if (checkNodeClsLimit(*nodePtr, curCls + 1)) {
                    parent->removeNode(nodePtr.data());
                    int curIdx = getNodeIdx(parent);
                    grandParent->addNode(nodePtr, curIdx + 1);
                    selectTreeScriptNode(*nodePtr);
                } else {
                    QMessageBox::information(NULL, gDict->PROG_NAME, gDict->TXT_MOVE_NODE_FAILED);
                }
            }
        }
    }
    return true;
}

bool SkillEditor::doMoveNodeChild()
{
    SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();
    if (_curSelectedNode != nullptr) {
        SkillScriptNode* parent = _curSelectedNode->getParent();
        if (parent != nullptr) {
            SkillScriptNodePtr nodePtr = asNodePtr(_curSelectedNode);
            SkillScriptNode* newParent = _curSelectedNode->getPrevBrother();
            if (nodePtr != nullptr && newParent != nullptr) {
                int curCls = getNodeCls(*newParent);
                if (checkNodeClsLimit(*nodePtr, curCls + 1)) {
                    parent->removeNode(nodePtr.data());
                    newParent->addNode(nodePtr);
                    selectTreeScriptNode(*nodePtr);
                } else {
                    QMessageBox::information(NULL, gDict->PROG_NAME, gDict->TXT_MOVE_NODE_FAILED);
                }
            }
        }
    }
    return true;
}

bool SkillEditor::doDeleteNode()
{
    SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();
    if (_curSelectedNode != nullptr) {
        SkillScriptNode* parent = _curSelectedNode->getParent();
        if (parent != nullptr) {
            SkillScriptNode* nextNode = _curSelectedNode->getNeibour();
            parent->removeNode(_curSelectedNode);
            if (nextNode != nullptr) {
                selectTreeScriptNode(*nextNode);
            }
        }
    }
    return true;
}

bool SkillEditor::doCopyNode()
{
    SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();
    if (_curSelectedNode != nullptr) {
        QDomDocument doc;
        node2Xml(*_curSelectedNode, doc);
        QString docTxt = doc.toString();

        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(docTxt);
    }
    return true;
}

bool SkillEditor::doCutNode()
{
    SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();
    if (_curSelectedNode != nullptr) {
        SkillScriptNode* parent = _curSelectedNode->getParent();
        if (parent != nullptr) {
            QDomDocument doc;
            node2Xml(*_curSelectedNode, doc);
            QString docTxt = doc.toString();

            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(docTxt);

            SkillScriptNode* nextNode = _curSelectedNode->getNeibour();
            parent->removeNode(_curSelectedNode);
            if (nextNode != nullptr) {
                selectTreeScriptNode(*nextNode);
            }
        }
    }
    return true;
}

bool SkillEditor::doPasteNode()
{
    SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();
    if (_curSelectedNode != nullptr) {
        SkillScriptNode* parent = _curSelectedNode->getParent();
        QClipboard *clipboard = QApplication::clipboard();
        QString txt = clipboard->text();
        if (parent != nullptr && !txt.isEmpty()) {
            SkillScriptNodePtr nodePtr = SkillScriptNodePtr::create(gSkillScript);
            if (xmlTxt2Node(txt, *nodePtr)) {
                int curCls = getNodeCls(*parent);
                if (checkNodeClsLimit(*nodePtr, curCls + 1)) {
                    int curIdx = getNodeIdx(_curSelectedNode);
                    parent->addNode(nodePtr, curIdx + 1);
                    selectTreeScriptNode(*nodePtr);
                } else {
                    QMessageBox::information(NULL, gDict->PROG_NAME, gDict->TXT_PASTE_NODE_FAILED);
                }
            }
        }
    }
    return true;
}

void SkillEditor::doSkillHelp()
{
    QString URL = QDir::currentPath() + "/Doc/Help-Skill.html";
    QDesktopServices::openUrl(QUrl(URL.toLatin1()));
}

void SkillEditor::doEditorHelp()
{
    QString URL = QDir::currentPath() + "/Doc/Help-Editor.html";
    QDesktopServices::openUrl(QUrl(URL.toLatin1()));
}

void SkillEditor::doScriptHelp()
{
    QString URL = QDir::currentPath() + "/Config/SkillSpec.xml";
    QDesktopServices::openUrl(QUrl(URL.toLatin1()));
}

void SkillEditor::doShowIcons()
{
    bool enable = this->_ui.actionShowIcons->isChecked();
    gSettings->setShowIcons(enable);
    //重绘界面
    clearTreeScript();
    loadTreeScript(*gSkillScript);
}

void SkillEditor::doSerialText()
{
    bool enable = this->_ui.actionSerialText->isChecked();
    gSettings->setSerialTxt(enable);

    QTableWidget *pTableSkill = this->_ui.instTable;
    if (pTableSkill != nullptr) {
        for (int idx = 0; idx < pTableSkill->rowCount(); idx++) {
            QTableWidgetItem * pItem = pTableSkill->item(idx, SkillInstData::COLUMN_ISCLIENTSKILL);
            if (pItem != nullptr) {
                if (enable) {
                    pItem->setFlags(pItem->flags() | Qt::ItemIsEditable);
                } else {
                    pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
                }
            }
        }
    }
}

void SkillEditor::doAbout()
{
    QMessageBox::about(this, gDict->PROG_NAME,
        tr("<b>About Skill Editor</b><br>"
        "A designer editor for building skill in visual idea.<br>"
        "<br>"
        "1.Abstract skill as a time-line stream and actions attached to skill.<br>"
        "2.Provide a growing number of actions including control/gfx/move/impact...<br>"
        "3.Self-descripted configuration, all action infos are descripted in <br>"
        "&nbsp;&nbsp;&nbsp;SkillSpec.xml and are generated automatically.<br>"
        "4.Support to translate xml to txt file which is based on ISA theory.<br>"
        "<br>"
        "Have fun, may the force be with u!<br>"
        "By lixiaojiang(River) @2020.2.24 Email: john.lee.ncist@gmail.com"));
}

bool SkillEditor::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent * keyEvent = (QKeyEvent*)event;
        if (object == this->_ui.scriptTree) {
            if (keyEvent->key() == Qt::Key_Insert) {
                this->doAddChildNode();
                return true;
            }
            if (keyEvent->key() == Qt::Key_Delete) {
                this->doDeleteNode();
                return true;
            }
            if (keyEvent->modifiers() == Qt::ControlModifier && keyEvent->key() == Qt::Key_C) {
                this->doCopyNode();
                return true;
            }
            if (keyEvent->modifiers() == Qt::ControlModifier && keyEvent->key() == Qt::Key_X) {
                this->doCutNode();
                return true;
            }
            if (keyEvent->modifiers() == Qt::ControlModifier && keyEvent->key() == Qt::Key_V) {
                this->doPasteNode();
                return true;
            }
            if (keyEvent->modifiers() == Qt::ControlModifier && keyEvent->key() == Qt::Key_Left) {
                this->doMoveNodeParent();
                return true;
            }
            if (keyEvent->modifiers() == Qt::ControlModifier && keyEvent->key() == Qt::Key_Right) {
                this->doMoveNodeChild();
                return true;
            }
            if (keyEvent->modifiers() == Qt::ControlModifier && keyEvent->key() == Qt::Key_Up) {
                this->doMoveNodeUp();
                return true;
            }
            if (keyEvent->modifiers() == Qt::ControlModifier && keyEvent->key() == Qt::Key_Down) {
                this->doMoveNodeDown();
                return true;
            }
        }
    }
    if (event->type() == QEvent::ContextMenu) {
        if (object == this->_ui.scriptTree) {
            if (_treeCtxMenu != nullptr) {
                _treeCtxMenu->exec(QCursor::pos());
            }
            return true;
        }
        if (object == this->_ui.instTable) {
            if (_tableCtxMenu != nullptr) {
                _tableCtxMenu->exec(QCursor::pos());
            }
            return true;
        }
    }
    return QMainWindow::eventFilter(object, event);
}

///////////////////////////////////////////////////////////////////
void SkillEditor::onSkillInstChanged(const SkillInst& pool, SkillNotifyReason reason)
{
    qDebug("onSkillPoolChanged");
    if (reason == SkillNotifyReason::R_SKILLINST_LOAD) {
        this->clearTreeScript();
        this->clearTableInstParam();
        this->clearTableInst();
        this->loadTableInst(pool);
    } else if (reason == SkillNotifyReason::R_SKILLINST_SAVE) {
        //TODO:
    } else if (reason == SkillNotifyReason::R_SKILLINST_CLEAR) {
        this->clearTreeScript();
        this->clearTableInstParam();
        this->clearTableInst();
    }
}

void SkillEditor::onSkillInstDataChanged(const SkillInstData& cfg, SkillNotifyReason reason)
{
    qDebug("onSkillDataChanged");
    TableRowPtr rowPtr = getTableRowById(_skillTableRows, cfg.getId());
    if (rowPtr != nullptr) {
        if (reason == SkillNotifyReason::R_SKILLINSTDATA_SELECTION) {
            rowPtr->setSelected(cfg.isSelected());
        } else {
            rowPtr->modifyItem(SkillInstData::DATACOLUMN::COLUMN_ID, QString("%0").arg(cfg.getId()));
            rowPtr->modifyItem(SkillInstData::DATACOLUMN::COLUMN_DESC, QString("%0").arg(cfg.getDesc()));
            rowPtr->modifyItem(SkillInstData::DATACOLUMN::COLUMN_ISCLIENTSKILL, QString("%0").arg(cfg.getIsClientSkill()));
            rowPtr->modifyItem(SkillInstData::DATACOLUMN::COLUMN_LOGIC, QString("%0").arg(cfg.getLogicFile()));
        }
    }
}

void SkillEditor::onSkillScriptChanged(const SkillScript& inst, SkillNotifyReason reason)
{
    qDebug("onSkillInstChanged");
    if (reason == SkillNotifyReason::R_SKILLSCRIPT_LOAD) {
        clearTreeScript();
        loadTreeScript(inst);
    } else if (reason == SkillNotifyReason::R_SKILLSCRIPT_CLEAR) {
        clearTreeScript();
    }
}

void SkillEditor::onSkillScriptNodeChanged(const SkillScriptNode& node, SkillNotifyReason reason)
{
    qDebug("onModelSkillNodeChanged");
    SkillScript* inst = node.getScript();
    if (inst != nullptr) {
        //保存原selected的节点
        SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();

        clearTreeScript();
        loadTreeScript(*inst);

        //恢复原selected的节点
        if (_curSelectedNode != nullptr) {
            selectTreeScriptNode(*_curSelectedNode);
        }
    }
}

void SkillEditor::onSkillScriptNodeParamChanged(const SkillScriptNodeParam& param, SkillNotifyReason reason)
{
    qDebug("onModelSkillParamChanged");
    SkillScriptNode* parent = param.getParent();
    if (parent != nullptr) {
        parent->updateTree();

        if (parent == gSkillScript->getSelectedNode()) {
            //更新Detail界面
            clearWidgetParam();
            loadWidgetParam(*parent);

            //更新ParamTable
            if (reason != SkillNotifyReason::R_SKILLSCRIPTNODEPARAM_PARAM_REF_NUMBER) {
                SkillInstDataPtr cfgPtr = getCurInstData();
                if (cfgPtr != nullptr) {
                    clearTableInstParam();
                    loadTableInstParam(*cfgPtr);
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////
void SkillEditor::onTableInstItemChanged(QTableWidgetItem * item)
{
    qDebug("onTableItemChanged");
    TableRowPtr pitem = getTableRowByIdx(this->_skillTableRows, item->row());
    if (pitem != nullptr) {
        SkillInstDataPtr cfgPtr = getInstData(pitem->getId());
        if (cfgPtr != nullptr) {
            int col = item->column();
            if (col == SkillInstData::DATACOLUMN::COLUMN_ID) {
                int id = pitem->getIntData(col);
                //FIXME:增加和删除表格内容时也会触发此回调，暂时没有想到更好的办法屏蔽
                if (id != cfgPtr->getId()) {
                    //确保ID唯一
                    SkillInstDataPtr oldData = gSkillInst->getData(id);
                    if (oldData != nullptr) {
                        QMessageBox::warning(this, gDict->PROG_NAME,
                            gDict->TXT_SKILL_INST_SAME_ID);
                        item->setText(QString::number(cfgPtr->getId()));
                    } else {
                        pitem->setId(id);
                        cfgPtr->setId(id);
                        syncCurSkillAction(cfgPtr);
                    }
                }
            } else if (col == SkillInstData::DATACOLUMN::COLUMN_DESC) {
                QString txt = pitem->getStrData(col);
                //FIXME:增加和删除表格内容时也会触发此回调，暂时没有想到更好的办法屏蔽
                if (txt != cfgPtr->getDesc()) {
                    cfgPtr->setDesc(txt);
                }
            } else if (col == SkillInstData::DATACOLUMN::COLUMN_LOGIC) {
                QString txt = pitem->getStrData(col);
                //FIXME:增加和删除表格内容时也会触发此回调，暂时没有想到更好的办法屏蔽
                if (txt != cfgPtr->getLogicFile()) {
                    cfgPtr->setLogicFile(txt);
                }
            } else if (col == SkillInstData::DATACOLUMN::COLUMN_ISCLIENTSKILL) {
                QString txt = pitem->getStrData(col);
                if (txt.isEmpty() || !(txt == "0" || txt == "-1" || txt == "1")) {
                    QMessageBox::warning(this, gDict->PROG_NAME,
                        gDict->TXT_SKILL_INST_ISCLIENT_ERROR);
                    item->setText(QString::number(-1));
                    txt = "-1";
                }
                //FIXME:增加和删除表格内容时也会触发此回调，暂时没有想到更好的办法屏蔽
                if (txt.toInt() != cfgPtr->getIsClientSkill()) {
                    cfgPtr->setIsClientSkill(txt.toInt());
                    syncCurSkillAction(cfgPtr);
                }
            }
        }
    }
}

void SkillEditor::onTableInstSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected)
{
    qDebug("onTableSkillSelectionChanged");
    QList<TableRowPtr> deselectedList;
    getTableRowBySelection(this->_skillTableRows, deselected.indexes(), deselectedList);
    foreach(TableRowPtr rowPtr, deselectedList)
    {
        SkillInstDataPtr cfgPtr = getInstData(rowPtr->getId());
        if (cfgPtr != nullptr) {
            cfgPtr->setSelected(false);
        }
    }

    QList<TableRowPtr> selectedList;
    getTableRowBySelection(this->_skillTableRows, selected.indexes(), selectedList);
    foreach(TableRowPtr rowPtr, selectedList)
    {
        SkillInstDataPtr cfgPtr = getInstData(rowPtr->getId());
        if (cfgPtr != nullptr) {
            cfgPtr->setSelected(true);
        }
    }

    //Note:无需提示，直接保存原Script文件，并清除数据
    doSaveScriptFile();
    gSkillScript->clear();

    //打开当前SkillCfg对应的Script文件
    SkillInstDataPtr cfgPtr = getCurInstData();
    if (cfgPtr != nullptr) {
        clearRefRemark();
        clearTreeScript();
        clearTableInstParam();
        loadTableInstParam(*cfgPtr);
        loadScriptFile(*cfgPtr);
    }
}

void SkillEditor::onTableInstParamItemChanged(QTableWidgetItem * item)
{
    qDebug("onTableParamItemChanged");
    TableRowPtr pitem = getTableRowByIdx(this->_paramTableRows, item->row());
    if (pitem != nullptr) {
        SkillInstDataPtr cfgPtr = getInstData(pitem->getId());
        if (cfgPtr != nullptr) {
            int col = item->column();
            if (col >= 0 && col < SKILLINST_LOGIC_PARAM_COUNT) {
                int val = pitem->getIntData(col);
                int oldVal = cfgPtr->getLogicParamByIdx(col);
                if (val != oldVal) {
                    cfgPtr->setLogicParamByIdx(col, val);
                    //应用数据到SkillScriptNodeParam
                    applyScriptRefData(col + 1, val, gSkillScript);
                }
            }
        }
    }
}

void SkillEditor::onTableInstParamItemSelectionChanged()
{
    qDebug("onTableInstParamItemSelectionChanged");
    gSkillScript->unselectAllRef();

    QList<QTableWidgetItem *> items = this->_ui.instParamTable->selectedItems();
    if (items.length() > 0) {
        QTableWidgetItem * item = items.front();
        TableRowPtr pitem = getTableRowByIdx(this->_paramTableRows, item->row());
        if (pitem != nullptr) {
            int col = item->column();
            if (col >= 0 && col < SKILLINST_LOGIC_PARAM_COUNT) {
                SkillScriptRefInfoPtr refPtr = gSkillScript->getRef(col);
                if (refPtr != nullptr) {
                    clearRefRemark();
                    loadRefRemark(refPtr->getInfo());
                    refPtr->setSelected(true);
                }
            }
        }
    }
}

void SkillEditor::onTreeScriptItemSelectionChanged()
{
    qDebug("onViewTreeItemSelectionChanged");

    QTreeWidget *treeWidget = this->_ui.scriptTree;
    if (treeWidget == nullptr) { return; }

    //先清空
    clearWidgetParam();
    //清空选择
    unselectScriptNodes();

    //填充内容
    QList<QTreeWidgetItem *> selectionList = treeWidget->selectedItems();
    if (selectionList.length() > 0) {
        QTreeWidgetItem *item = selectionList.front();
        SkillScriptNodeUserData userData = item->data(0, Qt::UserRole + 1).value<SkillScriptNodeUserData>();
        if (userData._skillNode != nullptr) {
            loadWidgetParam(*userData._skillNode);
            selectTreeScriptNode(*userData._skillNode, false);
        }

    }
}

void SkillEditor::onEditNodeRemarkTextChanged()
{
    QString info = this->_ui.nodeRemarkEdit->toPlainText();
    if (info.length() > SKILLNODE_REMARK_MAX_COUNT) {
        QMessageBox::warning(this, gDict->PROG_NAME,
            gDict->TXT_EXCEED_INFO_MAX_COUNT.arg(SKILLNODE_REMARK_MAX_COUNT));
        return;
    }

    SkillScriptNode* _curSelectedNode = gSkillScript->getSelectedNode();
    if (_curSelectedNode != nullptr) {
        _curSelectedNode->setInfo(info);
    }
}

void SkillEditor::onEditRefRemarkTextChanged()
{
    QString info = this->_ui.refRemarkEdit->toPlainText();
    if (info.length() > SKILLNODE_REMARK_MAX_COUNT) {
        QMessageBox::warning(this, gDict->PROG_NAME,
            gDict->TXT_EXCEED_INFO_MAX_COUNT.arg(SKILLNODE_REMARK_MAX_COUNT));
        return;
    }

    SkillScriptRefInfoPtr _curRef = gSkillScript->getSelectedRef();
    if (_curRef != nullptr) {
        _curRef->setInfo(info);
    }
}

void SkillEditor::onTreeScriptItemExpanded(QTreeWidgetItem *item)
{
    SkillScriptNodeUserData userData = item->data(0, Qt::UserRole + 1).value<SkillScriptNodeUserData>();
    if (userData._skillNode != nullptr) {
        userData._skillNode->setExpand(true);
    }
}

void SkillEditor::onTreeScriptItemCollapsed(QTreeWidgetItem *item)
{
    SkillScriptNodeUserData userData = item->data(0, Qt::UserRole + 1).value<SkillScriptNodeUserData>();
    if (userData._skillNode != nullptr) {
        userData._skillNode->setExpand(false);
    }
}

void SkillEditor::onTimerOut()
{
    qDebug("onTimerOut");
    if (ENABLE_AUTO_SAVE) {
        doSaveAll();
    }
}

///////////////////////////////////////////////////////////////////
TableRowPtr getTableRowByIdx(const QList<TableRowPtr>& list, int rowIdx)
{
    for (int idx = 0; idx < list.length(); idx++) {
        TableRowPtr item = list.at(idx);
        if (item != nullptr && rowIdx == item->getRowIdx()) {
            return item;
        }
    }
    return TableRowPtr();
}

TableRowPtr getTableRowById(const QList<TableRowPtr>& list, int id)
{
    for (int idx = 0; idx < list.length(); idx++) {
        TableRowPtr item = list.at(idx);
        if (item != nullptr && id == item->getId()) {
            return item;
        }
    }
    return TableRowPtr();
}

int getTableRowIdxById(const QList<TableRowPtr>& list, int id)
{
    for (int idx = 0; idx < list.length(); idx++) {
        TableRowPtr item = list.at(idx);
        if (item != nullptr && id == item->getId()) {
            return item->getRowIdx();
        }
    }
    return -1;
}

void getTableRowBySelection(const QList<TableRowPtr>& srcList, QModelIndexList& indexesList, QList<TableRowPtr>& list)
{
    QSet<int> rowSet;
    foreach(QModelIndex idx, indexesList)
    {
        int row = idx.row();
        if (!rowSet.contains(row)) {
            rowSet.insert(row);
        }
    }

    foreach(int rowIdx, rowSet)
    {
        TableRowPtr rowPtr = getTableRowByIdx(srcList, rowIdx);
        if (rowPtr != nullptr) {
            list.append(rowPtr);
        }
    }
}

void clearAllInvalidSkillActions()
{
    //获取所有有效行
    const QList<SkillInstDataPtr>& instList = gSkillInst->getDatas();
    QSet<int> validIdList;
    for (int idx = instList.length() - 1; idx >= 0; idx--) {
        SkillInstDataPtr ptr = instList.at(idx);
        if (ptr != nullptr && ptr->getIsClientSkill() == 1) {
            validIdList.insert(ptr->getId());
        }
    }

    //删除所有无效行 从SkillGfx.txt中
    const QList<SkillGfxDataPtr>& oldDatas = gSkillGfx->getDatas();
    for (int idx = oldDatas.length() - 1; idx >= 0; idx--) {
        SkillGfxDataPtr ptr = oldDatas.at(idx);
        if (ptr != nullptr && !validIdList.contains(ptr->getInstId())) {
            gSkillGfx->removeData(ptr->getId());
        }
    }
}

void syncCurSkillAction(SkillInstDataPtr instDataPtr)
{
    if (!gSettings->isSerialTxt()) {
        return;
    }

    if (instDataPtr != nullptr) {
        int instId = instDataPtr->getId();

        //删除所有相关行 SkillGfx.txt中
        const QList<SkillGfxDataPtr>& oldDatas = gSkillGfx->getDatas();
        int nLineIdx = oldDatas.length();
        for (int idx = oldDatas.length() - 1; idx >= 0; idx--) {
            SkillGfxDataPtr ptr = oldDatas.at(idx);
            if (ptr != nullptr && ptr->getInstId() == instId) {
                nLineIdx = idx;
                gSkillGfx->removeData(ptr->getId());
            }
        }

        if (instDataPtr->getIsClientSkill() == 1) {
            //序列化成顺序数组
            QList<SkillScriptNodePtr> allList;
            const SkillScriptNodePtrList& childNodes = gSkillScript->getNodes();
            for (int idx = childNodes.length() - 1; idx >= 0; idx--) {
                SkillScriptNodePtr childNode = childNodes.at(idx);
                //当前只在客户端使用序列化指令系统，服务器使用xml
                if (childNode != nullptr) {
                    //序列化为队列
                    QList<SkillScriptNodePtr> list;
                    SkillScriptNodePtr endNode = createEndNode();
                    list.append(endNode);
                    serializeNode(childNode, endNode, list);

                    //填充自动ID，作为地址
                    int sectionCode = getSpecActionCode(childNode->getId());
                    if (sectionCode <= 0) {
                        break;
                    }
                    int baseId = instId * 1000 + sectionCode * 100;
                    for (int idx = list.length() - 1; idx >= 0; idx--) {
                        SkillScriptNodePtr scriptNodePtr = list.at(idx);
                        if (scriptNodePtr != nullptr) {
                            scriptNodePtr->setAutoId(baseId++);
                        }
                    }
                    allList.append(list);
                }
            }

            //将链接转换为地址
            for (int idx = allList.length() - 1; idx >= 0; idx--) {
                SkillScriptNodePtr scriptNodePtr = allList.at(idx);
                if (scriptNodePtr != nullptr) {
                    linkNode(scriptNodePtr);
                }
            }

            //写入到SkillGfx.txt中
            for (int idx = allList.length() - 1; idx >= 0; idx--) {
                SkillScriptNodePtr scriptNodePtr = allList.at(idx);
                if (scriptNodePtr != nullptr) {
                    SkillGfxDataPtr gfxNodePtr = SkillGfxDataPtr::create();
                    gfxNodePtr->setParent(gSkillGfx);

                    //同步ScriptNode数据到GfxNode节点上
                    gfxNodePtr->setId(scriptNodePtr->getAutoId());
                    gfxNodePtr->setDesc(scriptNodePtr->getInfo());
                    gfxNodePtr->setName(scriptNodePtr->getId());
                    gfxNodePtr->setInstId(instId);
                    gfxNodePtr->setActionId(getSpecNodeCode(scriptNodePtr->getId()));

                    int paramIdx = 0;
                    const SkillScriptNodeParamPtrList& scriptNodeParams = scriptNodePtr->getParams();
                    for (int idx = 0; idx < scriptNodeParams.length(); idx++) {
                        SkillScriptNodeParamPtr ptr = scriptNodeParams.at(idx);
                        if (ptr != nullptr && ptr->getName() != "id") {
                            if (ptr->isRef()) {
                                gfxNodePtr->setIsRefByIdx(paramIdx, 1);
                                gfxNodePtr->setParamByIdx(paramIdx, ptr->getRef());
                            } else {
                                gfxNodePtr->setIsRefByIdx(paramIdx, -1);
                                gfxNodePtr->setParamByIdx(paramIdx, ptr->getNumber<int>());
                            }
                            paramIdx++;
                        }
                    }
                    nLineIdx = gSkillGfx->insertData(nLineIdx, gfxNodePtr);
                }
            }
        }
    }
}
