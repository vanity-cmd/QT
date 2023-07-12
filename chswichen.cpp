#include "chswichen.h"

ChSwichEn::ChSwichEn()
{

}

language_combo_box->addItem("chinese", QVariant::fromValue(UI_ZH));
language_combo_box->addItem("english", QVariant::fromValue(UI_EN));
qRegisterMetaType<LANGUAGE>("LANGUAGE");
connect(language_combo_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &SettingDialog::onIndexChanged); void SettingDialog::changeEvent(QEvent *event) { switch (event->type()) { case QEvent::LanguageChange: translateUI(); break; default: QDialog::changeEvent(event); } } void SettingDialog::translateUI() { this->setWindowTitle(tr("setting dialog")); info_label->setText(tr("no brothers no programming")); language_label->setText(tr("language")); language_combo_box->setItemText(UI_ZH, tr("chinese")); language_combo_box->setItemText(UI_EN, tr("english")); } void SettingDialog::onIndexChanged() { LANGUAGE language = language_combo_box->currentData().value<LANGUAGE>(); emit switchLanguage(language); }
