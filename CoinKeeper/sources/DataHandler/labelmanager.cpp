#include "DataHandler/labelmanager.h"

#include "qcolordialog.h"
#include "qinputdialog.h"
#include "qmessagebox.h"

LabelManager::LabelManager(std::shared_ptr<Database> data) :
    database(data)
{
}

void LabelManager::ManageLabels()
{
    auto manageLabelsWindow = std::make_unique<Ui::ManageLabelsWindow>();
    QDialog dialog;
    manageLabelsWindow->setupUi(&dialog);
    manageLabelsWindow->tableLabels->setColumnWidth(0, 300);
    RefreshWindow(manageLabelsWindow);

    connect(manageLabelsWindow->buttonNewLabel, &QPushButton::clicked, this, [this, &manageLabelsWindow] {
        CreateNewLabel();
        RefreshWindow(manageLabelsWindow);
    });
    connect(manageLabelsWindow->buttonChangeName, &QPushButton::clicked, this, [this, &manageLabelsWindow] {
        ChangeLabelName(manageLabelsWindow->tableLabels->currentRow());
        RefreshWindow(manageLabelsWindow);
    });
    connect(manageLabelsWindow->buttonChangeColor, &QPushButton::clicked, this, [this, &manageLabelsWindow] {
        ChangeLabelColor(manageLabelsWindow->tableLabels->currentRow());
        RefreshWindow(manageLabelsWindow);
    });
    connect(manageLabelsWindow->buttonDeleteLabel, &QPushButton::clicked, this, [this, &manageLabelsWindow] {
        DeleteLabel(manageLabelsWindow->tableLabels->currentRow());
        RefreshWindow(manageLabelsWindow);
    });

    dialog.exec();
}

void LabelManager::CreateNewLabel()
{
    auto textInput = QInputDialog();
    textInput.setInputMode(QInputDialog::TextInput);
    textInput.setLabelText(QString::fromStdString(TEXT_NAME_ENTRY));
    textInput.setWindowTitle(QString::fromStdString(TEXT_CREATE_NEW_LABEL));
    textInput.resize(300, 100);
    bool userClickedOk = textInput.exec() == QInputDialog::Accepted;
    QString text = textInput.textValue();

    if (userClickedOk && !text.isEmpty()) {
        QColor color = QColorDialog::getColor(Qt::white, Q_NULLPTR, QString::fromStdString(TEXT_CHOOSE_COLOR), QColorDialog::ShowAlphaChannel);
        if (color.isValid()) {
            database->CreateNewLabel(text.toStdString(), ConvertRGBAToInt(color.red(), color.green(), color.blue(), color.alpha()));
        }
    }
}

void LabelManager::ChangeLabelName(int const selectedRow)
{
    if (selectedRow >= 0) {
        std::string oldText;
        int labelID, color;
        tie(labelID, oldText, color) = currentLabels[selectedRow];

        auto textInput = QInputDialog();
        textInput.setInputMode(QInputDialog::TextInput);
        textInput.setLabelText(QString::fromStdString(TEXT_NAME_ENTRY));
        textInput.setWindowTitle(QString::fromStdString(TEXT_CHANGE_LABEL));
        textInput.setTextValue(QString::fromStdString(oldText));
        textInput.resize(300, 100);
        bool userClickedOk = textInput.exec() == QInputDialog::Accepted;
        QString text = textInput.textValue();

        if (userClickedOk && !text.isEmpty()) {
            database->UpdateLabel(labelID, text.toStdString(), color);
        }
    }
}

void LabelManager::ChangeLabelColor(int const selectedRow)
{
    if (selectedRow >= 0) {
        std::string text;
        int labelID, oldColor;
        tie(labelID, text, oldColor) = currentLabels[selectedRow];
        QColor color = QColorDialog::getColor(ConvertIntToQColor(oldColor), Q_NULLPTR, QString::fromStdString(TEXT_CHOOSE_COLOR), QColorDialog::ShowAlphaChannel);
        if (color.isValid()) {
            database->UpdateLabel(labelID, text, ConvertRGBAToInt(color.red(), color.green(), color.blue(), color.alpha()));
        }
    }
}

void LabelManager::DeleteLabel(int const selectedRow)
{
    if (selectedRow >= 0) {
        int labelID = std::get<0>(currentLabels[selectedRow]);
        QMessageBox msg;
        if (labelID == 1) {   // default label selected
            msg.setText(QString::fromStdString(TEXT_DEFAULT_LABEL_NOT_DELETABLE));
            msg.exec();
            return;
        }
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.setText(QString::fromStdString(TEXT_QUESTION_DELETE_LABEL));
        switch (msg.exec()) {
        case QMessageBox::Yes:
            database->DeleteLabel(labelID);
            break;
        case QMessageBox::No:
            break;
        default:
            break;
        }
    }
}

void LabelManager::RefreshWindow(std::unique_ptr<Ui::ManageLabelsWindow>& manageLabelsWindow)
{
    // if the manage labels window is open, refresh the label list:
    if (manageLabelsWindow != nullptr) {
        currentLabels = database->GetLabels();
        int x = static_cast<int>(currentLabels.size());
        manageLabelsWindow->tableLabels->setRowCount(x);
        for (int i = 0; i < x; ++i) {
            int labelID;        // not used
            std::string labelName;
            int color;
            tie(labelID, labelName, color) = currentLabels[i];
            QColor qColor = ConvertIntToQColor(color);
            manageLabelsWindow->tableLabels->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(labelName)));
            manageLabelsWindow->tableLabels->setItem(i, 1, new QTableWidgetItem(QString()));
            manageLabelsWindow->tableLabels->item(i, 1)->setBackgroundColor(qColor);
            manageLabelsWindow->tableLabels->item(i, 1)->setTextColor((qColor.value() + (255 - qColor.alpha()) < 128) ? Qt::white : Qt::black);
        }
    }
}
