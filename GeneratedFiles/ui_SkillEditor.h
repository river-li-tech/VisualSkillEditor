/********************************************************************************
** Form generated from reading UI file 'SkillEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKILLEDITOR_H
#define UI_SKILLEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ParamWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SkillEditorClass
{
public:
    QAction *actionSaveInstFile;
    QAction *actionExit;
    QAction *actionSettings;
    QAction *actionAddChildNode;
    QAction *actionAddPrevNode;
    QAction *actionAddNextNode;
    QAction *actionMoveNodeUp;
    QAction *actionMoveNodeDown;
    QAction *actionMoveNodeParent;
    QAction *actionMoveNodeChild;
    QAction *actionDeleteNode;
    QAction *actionCopyNode;
    QAction *actionPasteNode;
    QAction *actionCutNode;
    QAction *actionOpenInstFile;
    QAction *actionNewScriptFile;
    QAction *actionOpenScriptFile;
    QAction *actionSaveScriptFile;
    QAction *actionSaveScriptFileAs;
    QAction *actionSaveInstFileAs;
    QAction *actionSaveAll;
    QAction *actionNewInstFile;
    QAction *actionSelectScriptFile;
    QAction *actionSkillHelp;
    QAction *actionAbout;
    QAction *actionEditorHelp;
    QAction *actionSkillScriptHelp;
    QAction *actionShowIcons;
    QAction *actionAddSkill;
    QAction *actionDeleteSkill;
    QAction *actionSerialText;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QWidget *widgetLeftPanel;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *instTable;
    QWidget *widgetRightPanel;
    QGridLayout *gridLayout;
    QWidget *widghtRightBottomPanel;
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter_2;
    QWidget *widgetScriptPanel;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelScript;
    QTreeWidget *scriptTree;
    QWidget *widgetActionPanel;
    QGridLayout *gridLayout_2;
    QLabel *labelActionParam;
    ParamWidget *paramWidget;
    QFormLayout *formLayout;
    QLabel *labelInfo;
    QTextEdit *nodeRemarkEdit;
    QLabel *labelInfo_2;
    QTextEdit *refRemarkEdit;
    QWidget *widgetRightTopPanel;
    QVBoxLayout *verticalLayout;
    QLabel *labelParam;
    QTableWidget *instParamTable;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QMenu *menu_E;
    QMenu *menuAddNode;
    QMenu *menuMoveNode;
    QMenu *menu_H;
    QMenu *menuView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SkillEditorClass)
    {
        if (SkillEditorClass->objectName().isEmpty())
            SkillEditorClass->setObjectName(QStringLiteral("SkillEditorClass"));
        SkillEditorClass->resize(1013, 684);
        actionSaveInstFile = new QAction(SkillEditorClass);
        actionSaveInstFile->setObjectName(QStringLiteral("actionSaveInstFile"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/Icons/File Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveInstFile->setIcon(icon);
        actionExit = new QAction(SkillEditorClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/Icons/Stop 2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionSettings = new QAction(SkillEditorClass);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/Icons/Cog.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon2);
        actionAddChildNode = new QAction(SkillEditorClass);
        actionAddChildNode->setObjectName(QStringLiteral("actionAddChildNode"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/Icons/Box Add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddChildNode->setIcon(icon3);
        actionAddPrevNode = new QAction(SkillEditorClass);
        actionAddPrevNode->setObjectName(QStringLiteral("actionAddPrevNode"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/Icons/Box Up.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddPrevNode->setIcon(icon4);
        actionAddNextNode = new QAction(SkillEditorClass);
        actionAddNextNode->setObjectName(QStringLiteral("actionAddNextNode"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/Icons/Box Down.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddNextNode->setIcon(icon5);
        actionMoveNodeUp = new QAction(SkillEditorClass);
        actionMoveNodeUp->setObjectName(QStringLiteral("actionMoveNodeUp"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/Icons/Arrow Up.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMoveNodeUp->setIcon(icon6);
        actionMoveNodeDown = new QAction(SkillEditorClass);
        actionMoveNodeDown->setObjectName(QStringLiteral("actionMoveNodeDown"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/Icons/Arrow Down.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMoveNodeDown->setIcon(icon7);
        actionMoveNodeParent = new QAction(SkillEditorClass);
        actionMoveNodeParent->setObjectName(QStringLiteral("actionMoveNodeParent"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icons/Icons/Arrow Left.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMoveNodeParent->setIcon(icon8);
        actionMoveNodeChild = new QAction(SkillEditorClass);
        actionMoveNodeChild->setObjectName(QStringLiteral("actionMoveNodeChild"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icons/Icons/Arrow Right.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMoveNodeChild->setIcon(icon9);
        actionDeleteNode = new QAction(SkillEditorClass);
        actionDeleteNode->setObjectName(QStringLiteral("actionDeleteNode"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icons/Icons/Document 1 Remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDeleteNode->setIcon(icon10);
        actionCopyNode = new QAction(SkillEditorClass);
        actionCopyNode->setObjectName(QStringLiteral("actionCopyNode"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icons/Icons/File Copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopyNode->setIcon(icon11);
        actionPasteNode = new QAction(SkillEditorClass);
        actionPasteNode->setObjectName(QStringLiteral("actionPasteNode"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/icons/Icons/File Paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPasteNode->setIcon(icon12);
        actionCutNode = new QAction(SkillEditorClass);
        actionCutNode->setObjectName(QStringLiteral("actionCutNode"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/icons/Icons/File Cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCutNode->setIcon(icon13);
        actionOpenInstFile = new QAction(SkillEditorClass);
        actionOpenInstFile->setObjectName(QStringLiteral("actionOpenInstFile"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/icons/Icons/File Open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenInstFile->setIcon(icon14);
        actionNewScriptFile = new QAction(SkillEditorClass);
        actionNewScriptFile->setObjectName(QStringLiteral("actionNewScriptFile"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/icons/Icons/Document 2 Add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewScriptFile->setIcon(icon15);
        actionOpenScriptFile = new QAction(SkillEditorClass);
        actionOpenScriptFile->setObjectName(QStringLiteral("actionOpenScriptFile"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/icons/Icons/Document 2 Edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenScriptFile->setIcon(icon16);
        actionSaveScriptFile = new QAction(SkillEditorClass);
        actionSaveScriptFile->setObjectName(QStringLiteral("actionSaveScriptFile"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/icons/Icons/Document Blueprint.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveScriptFile->setIcon(icon17);
        actionSaveScriptFileAs = new QAction(SkillEditorClass);
        actionSaveScriptFileAs->setObjectName(QStringLiteral("actionSaveScriptFileAs"));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/icons/Icons/Document Checklist.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveScriptFileAs->setIcon(icon18);
        actionSaveInstFileAs = new QAction(SkillEditorClass);
        actionSaveInstFileAs->setObjectName(QStringLiteral("actionSaveInstFileAs"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/icons/Icons/File Close.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveInstFileAs->setIcon(icon19);
        actionSaveAll = new QAction(SkillEditorClass);
        actionSaveAll->setObjectName(QStringLiteral("actionSaveAll"));
        actionSaveAll->setIcon(icon);
        actionNewInstFile = new QAction(SkillEditorClass);
        actionNewInstFile->setObjectName(QStringLiteral("actionNewInstFile"));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/icons/Icons/File New.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewInstFile->setIcon(icon20);
        actionSelectScriptFile = new QAction(SkillEditorClass);
        actionSelectScriptFile->setObjectName(QStringLiteral("actionSelectScriptFile"));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/icons/Icons/Link.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelectScriptFile->setIcon(icon21);
        actionSkillHelp = new QAction(SkillEditorClass);
        actionSkillHelp->setObjectName(QStringLiteral("actionSkillHelp"));
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/icons/Icons/Contacts Add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSkillHelp->setIcon(icon22);
        actionAbout = new QAction(SkillEditorClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/icons/Icons/User.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon23);
        actionEditorHelp = new QAction(SkillEditorClass);
        actionEditorHelp->setObjectName(QStringLiteral("actionEditorHelp"));
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/icons/Icons/Contacts Sync.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEditorHelp->setIcon(icon24);
        actionSkillScriptHelp = new QAction(SkillEditorClass);
        actionSkillScriptHelp->setObjectName(QStringLiteral("actionSkillScriptHelp"));
        QIcon icon25;
        icon25.addFile(QStringLiteral(":/icons/Icons/Contacts.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSkillScriptHelp->setIcon(icon25);
        actionShowIcons = new QAction(SkillEditorClass);
        actionShowIcons->setObjectName(QStringLiteral("actionShowIcons"));
        actionShowIcons->setCheckable(true);
        QIcon icon26;
        icon26.addFile(QStringLiteral(":/icons/Icons/Bookmarks 2.png"), QSize(), QIcon::Disabled, QIcon::On);
        actionShowIcons->setIcon(icon26);
        actionAddSkill = new QAction(SkillEditorClass);
        actionAddSkill->setObjectName(QStringLiteral("actionAddSkill"));
        QIcon icon27;
        icon27.addFile(QStringLiteral(":/icons/Icons/Glyph Add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddSkill->setIcon(icon27);
        actionDeleteSkill = new QAction(SkillEditorClass);
        actionDeleteSkill->setObjectName(QStringLiteral("actionDeleteSkill"));
        QIcon icon28;
        icon28.addFile(QStringLiteral(":/icons/Icons/Glyph Remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDeleteSkill->setIcon(icon28);
        actionSerialText = new QAction(SkillEditorClass);
        actionSerialText->setObjectName(QStringLiteral("actionSerialText"));
        actionSerialText->setCheckable(true);
        actionSerialText->setIcon(icon18);
        centralWidget = new QWidget(SkillEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        widgetLeftPanel = new QWidget(splitter);
        widgetLeftPanel->setObjectName(QStringLiteral("widgetLeftPanel"));
        horizontalLayout_2 = new QHBoxLayout(widgetLeftPanel);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        instTable = new QTableWidget(widgetLeftPanel);
        if (instTable->columnCount() < 4)
            instTable->setColumnCount(4);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        instTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        instTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        instTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        instTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        instTable->setObjectName(QStringLiteral("instTable"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(instTable->sizePolicy().hasHeightForWidth());
        instTable->setSizePolicy(sizePolicy);
        instTable->setAlternatingRowColors(true);
        instTable->setSelectionMode(QAbstractItemView::SingleSelection);
        instTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        instTable->setRowCount(0);
        instTable->setColumnCount(4);
        instTable->horizontalHeader()->setStretchLastSection(true);

        horizontalLayout_2->addWidget(instTable);

        splitter->addWidget(widgetLeftPanel);
        widgetRightPanel = new QWidget(splitter);
        widgetRightPanel->setObjectName(QStringLiteral("widgetRightPanel"));
        gridLayout = new QGridLayout(widgetRightPanel);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widghtRightBottomPanel = new QWidget(widgetRightPanel);
        widghtRightBottomPanel->setObjectName(QStringLiteral("widghtRightBottomPanel"));
        sizePolicy.setHeightForWidth(widghtRightBottomPanel->sizePolicy().hasHeightForWidth());
        widghtRightBottomPanel->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(widghtRightBottomPanel);
        horizontalLayout_3->setSpacing(4);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        splitter_2 = new QSplitter(widghtRightBottomPanel);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        widgetScriptPanel = new QWidget(splitter_2);
        widgetScriptPanel->setObjectName(QStringLiteral("widgetScriptPanel"));
        verticalLayout_2 = new QVBoxLayout(widgetScriptPanel);
        verticalLayout_2->setSpacing(4);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        labelScript = new QLabel(widgetScriptPanel);
        labelScript->setObjectName(QStringLiteral("labelScript"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelScript->sizePolicy().hasHeightForWidth());
        labelScript->setSizePolicy(sizePolicy1);
        labelScript->setFont(font);

        verticalLayout_2->addWidget(labelScript);

        scriptTree = new QTreeWidget(widgetScriptPanel);
        scriptTree->setObjectName(QStringLiteral("scriptTree"));
        scriptTree->setStyleSheet(QStringLiteral("border-color: rgb(255, 0, 0);"));
        scriptTree->setTabKeyNavigation(true);
        scriptTree->setAlternatingRowColors(true);
        scriptTree->setAnimated(true);
        scriptTree->setAllColumnsShowFocus(true);

        verticalLayout_2->addWidget(scriptTree);

        splitter_2->addWidget(widgetScriptPanel);
        widgetActionPanel = new QWidget(splitter_2);
        widgetActionPanel->setObjectName(QStringLiteral("widgetActionPanel"));
        gridLayout_2 = new QGridLayout(widgetActionPanel);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(0);
        gridLayout_2->setVerticalSpacing(2);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        labelActionParam = new QLabel(widgetActionPanel);
        labelActionParam->setObjectName(QStringLiteral("labelActionParam"));
        sizePolicy1.setHeightForWidth(labelActionParam->sizePolicy().hasHeightForWidth());
        labelActionParam->setSizePolicy(sizePolicy1);
        labelActionParam->setFont(font);

        gridLayout_2->addWidget(labelActionParam, 0, 0, 1, 1);

        paramWidget = new ParamWidget(widgetActionPanel);
        paramWidget->setObjectName(QStringLiteral("paramWidget"));
        paramWidget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        formLayout = new QFormLayout(paramWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));

        gridLayout_2->addWidget(paramWidget, 1, 0, 1, 1);

        labelInfo = new QLabel(widgetActionPanel);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        sizePolicy1.setHeightForWidth(labelInfo->sizePolicy().hasHeightForWidth());
        labelInfo->setSizePolicy(sizePolicy1);
        labelInfo->setFont(font);

        gridLayout_2->addWidget(labelInfo, 2, 0, 1, 1);

        nodeRemarkEdit = new QTextEdit(widgetActionPanel);
        nodeRemarkEdit->setObjectName(QStringLiteral("nodeRemarkEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(nodeRemarkEdit->sizePolicy().hasHeightForWidth());
        nodeRemarkEdit->setSizePolicy(sizePolicy2);
        nodeRemarkEdit->setMaximumSize(QSize(16777215, 40));

        gridLayout_2->addWidget(nodeRemarkEdit, 3, 0, 1, 1);

        labelInfo_2 = new QLabel(widgetActionPanel);
        labelInfo_2->setObjectName(QStringLiteral("labelInfo_2"));
        sizePolicy1.setHeightForWidth(labelInfo_2->sizePolicy().hasHeightForWidth());
        labelInfo_2->setSizePolicy(sizePolicy1);
        labelInfo_2->setFont(font);

        gridLayout_2->addWidget(labelInfo_2, 4, 0, 1, 1);

        refRemarkEdit = new QTextEdit(widgetActionPanel);
        refRemarkEdit->setObjectName(QStringLiteral("refRemarkEdit"));
        sizePolicy2.setHeightForWidth(refRemarkEdit->sizePolicy().hasHeightForWidth());
        refRemarkEdit->setSizePolicy(sizePolicy2);
        refRemarkEdit->setMaximumSize(QSize(16777215, 40));

        gridLayout_2->addWidget(refRemarkEdit, 5, 0, 1, 1);

        splitter_2->addWidget(widgetActionPanel);

        horizontalLayout_3->addWidget(splitter_2);


        gridLayout->addWidget(widghtRightBottomPanel, 1, 0, 1, 1);

        widgetRightTopPanel = new QWidget(widgetRightPanel);
        widgetRightTopPanel->setObjectName(QStringLiteral("widgetRightTopPanel"));
        sizePolicy1.setHeightForWidth(widgetRightTopPanel->sizePolicy().hasHeightForWidth());
        widgetRightTopPanel->setSizePolicy(sizePolicy1);
        widgetRightTopPanel->setMaximumSize(QSize(16777215, 95));
        verticalLayout = new QVBoxLayout(widgetRightTopPanel);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelParam = new QLabel(widgetRightTopPanel);
        labelParam->setObjectName(QStringLiteral("labelParam"));
        sizePolicy2.setHeightForWidth(labelParam->sizePolicy().hasHeightForWidth());
        labelParam->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        labelParam->setFont(font1);

        verticalLayout->addWidget(labelParam);

        instParamTable = new QTableWidget(widgetRightTopPanel);
        if (instParamTable->columnCount() < 20)
            instParamTable->setColumnCount(20);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(4, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(5, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(6, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(7, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(8, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(9, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(10, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(11, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(12, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(13, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(14, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(15, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(16, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(17, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(18, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        instParamTable->setHorizontalHeaderItem(19, __qtablewidgetitem23);
        instParamTable->setObjectName(QStringLiteral("instParamTable"));
        sizePolicy1.setHeightForWidth(instParamTable->sizePolicy().hasHeightForWidth());
        instParamTable->setSizePolicy(sizePolicy1);
        instParamTable->setMaximumSize(QSize(16777215, 71));
        instParamTable->setAlternatingRowColors(true);
        instParamTable->setSelectionMode(QAbstractItemView::SingleSelection);
        instParamTable->setSelectionBehavior(QAbstractItemView::SelectItems);
        instParamTable->setShowGrid(true);
        instParamTable->setRowCount(0);
        instParamTable->setColumnCount(20);
        instParamTable->horizontalHeader()->setDefaultSectionSize(80);
        instParamTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(instParamTable);


        gridLayout->addWidget(widgetRightTopPanel, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 2);
        splitter->addWidget(widgetRightPanel);

        horizontalLayout->addWidget(splitter);

        SkillEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SkillEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1013, 23));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        menu_E = new QMenu(menuBar);
        menu_E->setObjectName(QStringLiteral("menu_E"));
        menuAddNode = new QMenu(menu_E);
        menuAddNode->setObjectName(QStringLiteral("menuAddNode"));
        menuMoveNode = new QMenu(menu_E);
        menuMoveNode->setObjectName(QStringLiteral("menuMoveNode"));
        menu_H = new QMenu(menuBar);
        menu_H->setObjectName(QStringLiteral("menu_H"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        SkillEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SkillEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SkillEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SkillEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SkillEditorClass->setStatusBar(statusBar);

        menuBar->addAction(menu_F->menuAction());
        menuBar->addAction(menu_E->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menu_H->menuAction());
        menu_F->addAction(actionNewInstFile);
        menu_F->addAction(actionOpenInstFile);
        menu_F->addAction(actionSaveInstFile);
        menu_F->addAction(actionSaveInstFileAs);
        menu_F->addSeparator();
        menu_F->addAction(actionNewScriptFile);
        menu_F->addAction(actionOpenScriptFile);
        menu_F->addAction(actionSelectScriptFile);
        menu_F->addAction(actionSaveScriptFile);
        menu_F->addAction(actionSaveScriptFileAs);
        menu_F->addSeparator();
        menu_F->addAction(actionSaveAll);
        menu_F->addAction(actionSettings);
        menu_F->addSeparator();
        menu_F->addAction(actionExit);
        menu_E->addAction(menuAddNode->menuAction());
        menu_E->addAction(menuMoveNode->menuAction());
        menu_E->addAction(actionDeleteNode);
        menu_E->addSeparator();
        menu_E->addAction(actionAddSkill);
        menu_E->addAction(actionDeleteSkill);
        menu_E->addSeparator();
        menu_E->addAction(actionCutNode);
        menu_E->addAction(actionCopyNode);
        menu_E->addAction(actionPasteNode);
        menuAddNode->addAction(actionAddChildNode);
        menuAddNode->addAction(actionAddPrevNode);
        menuAddNode->addAction(actionAddNextNode);
        menuMoveNode->addAction(actionMoveNodeUp);
        menuMoveNode->addAction(actionMoveNodeDown);
        menuMoveNode->addAction(actionMoveNodeParent);
        menuMoveNode->addAction(actionMoveNodeChild);
        menu_H->addAction(actionSkillHelp);
        menu_H->addAction(actionSkillScriptHelp);
        menu_H->addAction(actionEditorHelp);
        menu_H->addAction(actionAbout);
        menuView->addAction(actionShowIcons);
        menuView->addAction(actionSerialText);
        mainToolBar->addAction(actionSaveAll);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionNewInstFile);
        mainToolBar->addAction(actionOpenInstFile);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionNewScriptFile);
        mainToolBar->addAction(actionOpenScriptFile);
        mainToolBar->addAction(actionAddSkill);
        mainToolBar->addAction(actionDeleteSkill);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionAddChildNode);
        mainToolBar->addAction(actionAddPrevNode);
        mainToolBar->addAction(actionAddNextNode);
        mainToolBar->addAction(actionMoveNodeParent);
        mainToolBar->addAction(actionMoveNodeChild);
        mainToolBar->addAction(actionMoveNodeUp);
        mainToolBar->addAction(actionMoveNodeDown);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionShowIcons);
        mainToolBar->addAction(actionSerialText);

        retranslateUi(SkillEditorClass);

        QMetaObject::connectSlotsByName(SkillEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *SkillEditorClass)
    {
        SkillEditorClass->setWindowTitle(QApplication::translate("SkillEditorClass", "SkillEditor", Q_NULLPTR));
        actionSaveInstFile->setText(QApplication::translate("SkillEditorClass", "Save Excel File...", Q_NULLPTR));
        actionExit->setText(QApplication::translate("SkillEditorClass", "Exit", Q_NULLPTR));
        actionExit->setShortcut(QApplication::translate("SkillEditorClass", "Ctrl+Q", Q_NULLPTR));
        actionSettings->setText(QApplication::translate("SkillEditorClass", "Settings", Q_NULLPTR));
        actionAddChildNode->setText(QApplication::translate("SkillEditorClass", "Add Child Node", Q_NULLPTR));
        actionAddPrevNode->setText(QApplication::translate("SkillEditorClass", "Add Prev Node", Q_NULLPTR));
        actionAddNextNode->setText(QApplication::translate("SkillEditorClass", "Add Next Node", Q_NULLPTR));
        actionMoveNodeUp->setText(QApplication::translate("SkillEditorClass", "Move Node Up", Q_NULLPTR));
        actionMoveNodeDown->setText(QApplication::translate("SkillEditorClass", "Move Node Down", Q_NULLPTR));
        actionMoveNodeParent->setText(QApplication::translate("SkillEditorClass", "Move Node Parent", Q_NULLPTR));
        actionMoveNodeChild->setText(QApplication::translate("SkillEditorClass", "Move Node Child", Q_NULLPTR));
        actionDeleteNode->setText(QApplication::translate("SkillEditorClass", "Delete Node", Q_NULLPTR));
        actionCopyNode->setText(QApplication::translate("SkillEditorClass", "Copy Node", Q_NULLPTR));
        actionPasteNode->setText(QApplication::translate("SkillEditorClass", "Paste Node", Q_NULLPTR));
        actionCutNode->setText(QApplication::translate("SkillEditorClass", "Cut Node", Q_NULLPTR));
        actionOpenInstFile->setText(QApplication::translate("SkillEditorClass", "Open Excel File...", Q_NULLPTR));
        actionOpenInstFile->setShortcut(QApplication::translate("SkillEditorClass", "Ctrl+O", Q_NULLPTR));
        actionNewScriptFile->setText(QApplication::translate("SkillEditorClass", "New Xml File...", Q_NULLPTR));
        actionNewScriptFile->setShortcut(QApplication::translate("SkillEditorClass", "Alt+N", Q_NULLPTR));
        actionOpenScriptFile->setText(QApplication::translate("SkillEditorClass", "Open Xml File...", Q_NULLPTR));
        actionOpenScriptFile->setShortcut(QApplication::translate("SkillEditorClass", "Alt+O", Q_NULLPTR));
        actionSaveScriptFile->setText(QApplication::translate("SkillEditorClass", "Save Xml File...", Q_NULLPTR));
        actionSaveScriptFileAs->setText(QApplication::translate("SkillEditorClass", "Save Xml File As...", Q_NULLPTR));
        actionSaveInstFileAs->setText(QApplication::translate("SkillEditorClass", "Save Excel File As...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSaveInstFileAs->setToolTip(QApplication::translate("SkillEditorClass", "Save Excel File As", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSaveAll->setText(QApplication::translate("SkillEditorClass", "Save All...", Q_NULLPTR));
        actionSaveAll->setShortcut(QApplication::translate("SkillEditorClass", "Ctrl+S", Q_NULLPTR));
        actionNewInstFile->setText(QApplication::translate("SkillEditorClass", "New Excel File...", Q_NULLPTR));
        actionNewInstFile->setShortcut(QApplication::translate("SkillEditorClass", "Ctrl+N", Q_NULLPTR));
        actionSelectScriptFile->setText(QApplication::translate("SkillEditorClass", "Select Xml File...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSelectScriptFile->setToolTip(QApplication::translate("SkillEditorClass", "Select Xml File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSkillHelp->setText(QApplication::translate("SkillEditorClass", "Skill Help", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("SkillEditorClass", "About", Q_NULLPTR));
        actionEditorHelp->setText(QApplication::translate("SkillEditorClass", "Editor Help", Q_NULLPTR));
        actionSkillScriptHelp->setText(QApplication::translate("SkillEditorClass", "Skill Script Help", Q_NULLPTR));
        actionShowIcons->setText(QApplication::translate("SkillEditorClass", "Show Icons", Q_NULLPTR));
        actionAddSkill->setText(QApplication::translate("SkillEditorClass", "Add Skill", Q_NULLPTR));
        actionDeleteSkill->setText(QApplication::translate("SkillEditorClass", "Delete Skill", Q_NULLPTR));
        actionSerialText->setText(QApplication::translate("SkillEditorClass", "Serial Text", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = instTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SkillEditorClass", "ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = instTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SkillEditorClass", "Desc", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = instTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("SkillEditorClass", "IsClientSkill", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = instTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("SkillEditorClass", "Script", Q_NULLPTR));
        labelScript->setText(QApplication::translate("SkillEditorClass", "Skill Tree:", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = scriptTree->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("SkillEditorClass", "Skill Tree", Q_NULLPTR));
        labelActionParam->setText(QApplication::translate("SkillEditorClass", "Tree Node Parameters:", Q_NULLPTR));
        labelInfo->setText(QApplication::translate("SkillEditorClass", "Node Info:", Q_NULLPTR));
        nodeRemarkEdit->setPlaceholderText(QApplication::translate("SkillEditorClass", "Input remarks of node...", Q_NULLPTR));
        labelInfo_2->setText(QApplication::translate("SkillEditorClass", "Ref Info:", Q_NULLPTR));
        refRemarkEdit->setPlaceholderText(QApplication::translate("SkillEditorClass", "Input remarks of ref...", Q_NULLPTR));
        labelParam->setText(QApplication::translate("SkillEditorClass", "Logic Parameters:", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = instParamTable->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("SkillEditorClass", "Param01", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = instParamTable->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("SkillEditorClass", "Param02", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = instParamTable->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("SkillEditorClass", "Param03", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = instParamTable->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("SkillEditorClass", "Param04", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = instParamTable->horizontalHeaderItem(4);
        ___qtablewidgetitem8->setText(QApplication::translate("SkillEditorClass", "Param05", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = instParamTable->horizontalHeaderItem(5);
        ___qtablewidgetitem9->setText(QApplication::translate("SkillEditorClass", "Param06", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = instParamTable->horizontalHeaderItem(6);
        ___qtablewidgetitem10->setText(QApplication::translate("SkillEditorClass", "Param07", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = instParamTable->horizontalHeaderItem(7);
        ___qtablewidgetitem11->setText(QApplication::translate("SkillEditorClass", "Param08", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = instParamTable->horizontalHeaderItem(8);
        ___qtablewidgetitem12->setText(QApplication::translate("SkillEditorClass", "Param09", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = instParamTable->horizontalHeaderItem(9);
        ___qtablewidgetitem13->setText(QApplication::translate("SkillEditorClass", "Param10", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = instParamTable->horizontalHeaderItem(10);
        ___qtablewidgetitem14->setText(QApplication::translate("SkillEditorClass", "Param11", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem15 = instParamTable->horizontalHeaderItem(11);
        ___qtablewidgetitem15->setText(QApplication::translate("SkillEditorClass", "Param12", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem16 = instParamTable->horizontalHeaderItem(12);
        ___qtablewidgetitem16->setText(QApplication::translate("SkillEditorClass", "Param13", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem17 = instParamTable->horizontalHeaderItem(13);
        ___qtablewidgetitem17->setText(QApplication::translate("SkillEditorClass", "Param14", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem18 = instParamTable->horizontalHeaderItem(14);
        ___qtablewidgetitem18->setText(QApplication::translate("SkillEditorClass", "Param15", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem19 = instParamTable->horizontalHeaderItem(15);
        ___qtablewidgetitem19->setText(QApplication::translate("SkillEditorClass", "Param16", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem20 = instParamTable->horizontalHeaderItem(16);
        ___qtablewidgetitem20->setText(QApplication::translate("SkillEditorClass", "Param17", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem21 = instParamTable->horizontalHeaderItem(17);
        ___qtablewidgetitem21->setText(QApplication::translate("SkillEditorClass", "Param18", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem22 = instParamTable->horizontalHeaderItem(18);
        ___qtablewidgetitem22->setText(QApplication::translate("SkillEditorClass", "Param19", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem23 = instParamTable->horizontalHeaderItem(19);
        ___qtablewidgetitem23->setText(QApplication::translate("SkillEditorClass", "Param20", Q_NULLPTR));
        menu_F->setTitle(QApplication::translate("SkillEditorClass", "File(&F)", Q_NULLPTR));
        menu_E->setTitle(QApplication::translate("SkillEditorClass", "Edit(&E)", Q_NULLPTR));
        menuAddNode->setTitle(QApplication::translate("SkillEditorClass", "Add Node", Q_NULLPTR));
        menuMoveNode->setTitle(QApplication::translate("SkillEditorClass", "Move Node", Q_NULLPTR));
        menu_H->setTitle(QApplication::translate("SkillEditorClass", "Help(&H)", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("SkillEditorClass", "View(&V)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SkillEditorClass: public Ui_SkillEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKILLEDITOR_H
