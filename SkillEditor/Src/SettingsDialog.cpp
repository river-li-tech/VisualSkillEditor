#include "stdafx.h"
#include "SettingsDialog.h"
#include "Settings.h"
#include "Dict.h"
#include "Utils.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
: QDialog(parent)
{
	ui = new Ui::SettingsDialog();
	ui->setupUi(this);

	this->connect(this->ui->applyButton, SIGNAL(clicked()), this, SLOT(clickApply()));
	this->connect(this->ui->cancelButton, SIGNAL(clicked()), this, SLOT(clickCancel()));
	this->connect(this->ui->userEdit->document(), &QTextDocument::contentsChanged,
		this, &SettingsDialog::userDataChanged);

	this->setWindowTitle(gDict->TXT_SETTING_DIALOG_TITLE);
    this->ui->defaultEdit->setText(gSettings->getDefalutSettings().toPlainText());
    this->ui->userEdit->setText(gSettings->getUserSettings().toPlainText());
}

SettingsDialog::~SettingsDialog()
{
	SAFE_DELETE(this->ui);
}

void SettingsDialog::clickApply()
{
	if (this->ui->userEdit->document()->isModified()) {
		if (this->_apply()) {
			this->ui->userEdit->document()->setModified(false);
            this->setWindowTitle(gDict->TXT_SETTING_DIALOG_TITLE);
		}
	}
}

void SettingsDialog::clickCancel()
{
	this->close();
}

void SettingsDialog::userDataChanged()
{
    this->setWindowTitle(gDict->TXT_SETTING_DIALOG_TITLE + "*");
}

void SettingsDialog::closeEvent(QCloseEvent *event)
{
	if (this->ui->userEdit->document()->isModified()) {
		QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, gDict->PROG_NAME, gDict->TXT_SETTING_DIALOG_ASK_SAVED,
			QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes) {
			if (!this->_apply()) {
				event->ignore();
				return;
			}
		}
		event->accept();
	} else {
		event->accept();
	}
}

bool SettingsDialog::_apply()
{
    QString content = this->ui->userEdit->toPlainText();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(content.toUtf8(), &json_error));
    if (json_error.error != QJsonParseError::NoError) {
        return false;
    }

    QJsonObject rootObj = jsonDoc.object();
    gSettings->getUserSettings().readConfig(rootObj);
    gSettings->writeSettings();
	return true;
}

