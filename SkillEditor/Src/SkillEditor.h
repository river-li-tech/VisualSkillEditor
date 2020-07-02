#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SkillEditor.h"
#include "define.h"
#include "TableRow.h"
#include "SkillInst.h"
#include "SkillScript.h"

class SkillEditor : public QMainWindow
{
    Q_OBJECT

public:
    SkillEditor(QWidget *parent = Q_NULLPTR);

public:
    bool loadWorkspace();

private slots :
    //操作Action处理函数
    void doNewInstFile();
    void doOpenInstFile();
    bool doSaveInstFile();
    bool doSaveInstFileAs();
    void doOpenGfxFile();
    bool doSaveGfxFile();
    bool doSaveGfxFileAs();
    void doNewScriptFile();
    void doOpenScriptFile();
    bool doSaveScriptFile();
    bool doSaveScriptFileAs();
    void doSelectScriptFile();
    bool doSaveAll();
    bool doSettings();
    bool doExit();
    bool doAddSkill();
    bool doDeleteSkill();
    bool doAddChildNode();
    bool doAddPrevNode();
    bool doAddNextNode();
    bool doMoveNodeUp();
    bool doMoveNodeDown();
    bool doMoveNodeParent();
    bool doMoveNodeChild();
    bool doDeleteNode();
    bool doCopyNode();
    bool doCutNode();
    bool doPasteNode();
    void doSkillHelp();
    void doEditorHelp();
    void doScriptHelp();
    void doShowIcons();
    void doSerialText();
    void doAbout();

protected:
    //处理事件
    bool eventFilter(QObject *object, QEvent *event);

private slots:
    ////////////////////////////////////////////////////////////////////
    //监听来自数据层发送的信号
    void onSkillInstChanged(const SkillInst& pool, SkillNotifyReason reason);
    void onSkillInstDataChanged(const SkillInstData& cfg, SkillNotifyReason reason);
    void onSkillScriptChanged(const SkillScript& inst, SkillNotifyReason reason);
    void onSkillScriptNodeChanged(const SkillScriptNode& node, SkillNotifyReason reason);
    void onSkillScriptNodeParamChanged(const SkillScriptNodeParam& param, SkillNotifyReason reason);

private slots:
    ////////////////////////////////////////////////////////////////////
    //监听来自UI界面发送的信号
    void onTableInstItemChanged(QTableWidgetItem * item);
    void onTableInstSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected);
    void onTableInstParamItemChanged(QTableWidgetItem * item);
    void onTableInstParamItemSelectionChanged();
    void onTreeScriptItemSelectionChanged();
    void onEditNodeRemarkTextChanged();
    void onEditRefRemarkTextChanged();
    void onTreeScriptItemExpanded(QTreeWidgetItem *item);
    void onTreeScriptItemCollapsed(QTreeWidgetItem *item);

    //定时器处理
    void onTimerOut();

private:
    ////////////////////////////////////////////////////////////////////
    //UI界面更新操作
    void initActions();
    
    //TableInst表界面操作
    void loadTableInst(const SkillInst& table);
    void clearTableInst();
    int addRow2TableInst(const SkillInstData& cfg);
    void removeRow4TableInst(const SkillInstData& cfg);

    //TableInstParam表界面操作
    void loadTableInstParam(const SkillInstData& cfg);
    void clearTableInstParam();
    void addRow2TableInstParam(const SkillInstData& cfg);
    void removeRow4TableInstParam(const SkillInstData& cfg);

    //TreeScript树界面操作
    void loadTreeScript(const SkillScript & inst);
    void clearTreeScript();
    void selectTreeScriptNode(SkillScriptNode& node, bool notifyTree = true);
    void unselectScriptNodes();

    //WidgetParam窗口界面操作
    void loadWidgetParam(SkillScriptNode& node);
    void clearWidgetParam();

    //EditRemark窗口界面操作
    void clearNodeRemark();
    void loadNodeRemark(const QString& txt);
    void clearRefRemark();
    void loadRefRemark(const QString& txt);

private:
    //设置操作
    void readSettings();
    void writeSettings();

private:
    //获取保存SkillInst文件地址
    QString getSaveInstFilePath();
    //获取打开SkillInst文件地址
    QString getOpenInstFilePath();
    //获取保存SkillGfx文件地址
    QString getSaveGfxFilePath();
    //获取打开SkillGfx文件地址
    QString getOpenGfxFilePath();
    //获取保存Skill Script文件地址
    QString getSaveScriptFilePath();
    //获取打开Skill Script文件地址
    QString getOpenScriptFilePath();

private:
    //载入SkillInst文件
    bool loadInstFileAs(const QString &filePath);
    //保存SkillInst文件
    bool saveInstFileAs(const QString &filePath);
    //载入SkillGfx文件
    bool loadGfxFileAs(const QString &filePath);
    //保存SkillGfx文件
    bool saveGfxFileAs(const QString &filePath);
    //载入Skill Script文件
    bool loadScriptFileAs(const QString &filePath);
    //保存Skill Script文件
    bool saveScriptFileAs(const QString &filePath);
    //载入Skill Script文件
    void loadScriptFile(const SkillInstData& cfg);
    ////////////////////////////////////////////////////////////////////

private:
    //更新标题
    void updateWindowTitle();
    //获取SkillInst.txt文件目录
    QString getSkillInstDir();
    //获取SkillGfx.txt文件目录
    QString getSkillGfxDir();
    //获取Skill Script文件目录
    QString getSkillScriptDir();
    //获取Skill Script文件相对目录
    QString getSkillScriptRelativeDir();

private:
    Ui::SkillEditorClass        _ui;
    QMenu*                      _treeCtxMenu;
    QMenu*                      _tableCtxMenu;
    QTimer*                     _timer;

    QList<TableRowPtr>          _skillTableRows;
    QList<TableRowPtr>          _paramTableRows;
};

////////////////////////////////////////////////////////////////////
//从列表中按行提取
TableRowPtr getTableRowByIdx(const QList<TableRowPtr>& list, int rowIdx);
//从列表中按id提取
TableRowPtr getTableRowById(const QList<TableRowPtr>& list, int id);
//从列表中按id行
int getTableRowIdxById(const QList<TableRowPtr>& list, int id);
//根据selection从显示列表中提取行
void getTableRowBySelection(const QList<TableRowPtr>& srcList, QModelIndexList& indexesList, QList<TableRowPtr>& list);

//清理所有无效的数据
void clearAllInvalidSkillActions();
//更新当前实例的数据
void syncCurSkillAction(SkillInstDataPtr instDataPtr);
