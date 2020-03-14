/********************************************************************************
** Form generated from reading UI file 'SettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextEdit *defaultEdit;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTextEdit *userEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *applyButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->resize(747, 666);
        verticalLayout_3 = new QVBoxLayout(SettingsDialog);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(SettingsDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout->addWidget(label);

        defaultEdit = new QTextEdit(SettingsDialog);
        defaultEdit->setObjectName(QStringLiteral("defaultEdit"));
        defaultEdit->setReadOnly(true);

        verticalLayout->addWidget(defaultEdit);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(SettingsDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);

        userEdit = new QTextEdit(SettingsDialog);
        userEdit->setObjectName(QStringLiteral("userEdit"));

        verticalLayout_2->addWidget(userEdit);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        applyButton = new QPushButton(SettingsDialog);
        applyButton->setObjectName(QStringLiteral("applyButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(applyButton->sizePolicy().hasHeightForWidth());
        applyButton->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(applyButton);

        cancelButton = new QPushButton(SettingsDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        sizePolicy.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
        cancelButton->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(cancelButton);


        verticalLayout_3->addLayout(horizontalLayout_2);


        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Settings", Q_NULLPTR));
        label->setText(QApplication::translate("SettingsDialog", "Settings-Default", Q_NULLPTR));
        label_2->setText(QApplication::translate("SettingsDialog", "Settings-User", Q_NULLPTR));
        applyButton->setText(QApplication::translate("SettingsDialog", "Apply", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("SettingsDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
