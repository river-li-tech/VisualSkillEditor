#pragma once

#include <QDialog>
namespace Ui { class SettingsDialog; };

class SettingsDialog : public QDialog
{
	Q_OBJECT

public:
	SettingsDialog(QWidget *parent = Q_NULLPTR);
	~SettingsDialog();

private slots:
	void clickApply();
	void clickCancel();
	void userDataChanged();

protected:
	void closeEvent(QCloseEvent *event);

private:
	bool _apply();

private:
	Ui::SettingsDialog *ui;
};
