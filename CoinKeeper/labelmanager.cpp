#include "labelmanager.h"

LabelManager::LabelManager(string profilePath, Database* base)
{
    currentProfile = profilePath;
    database = base;
}

void LabelManager::ManageLabels()
{
    manageLabelsWindow = new Ui::ManageLabelsWindow;
    QDialog dialog;
    manageLabelsWindow->setupUi(&dialog);
    RefreshWindow();
    connect(manageLabelsWindow->buttonNewLabel, &QPushButton::clicked, this, [=] { CreateNewLabel(); });
    connect(manageLabelsWindow->buttonChangeName, &QPushButton::clicked, this, [=] { ChangeLabelName(); });
    connect(manageLabelsWindow->buttonChangeColor, &QPushButton::clicked, this, [=] { ChangeLabelColor(); });
    connect(manageLabelsWindow->buttonDeleteLabel, &QPushButton::clicked, this, [=] { DeleteLabel(); });
    dialog.exec();
    delete manageLabelsWindow;
    manageLabelsWindow = nullptr;
}

void LabelManager::CreateNewLabel()
{
    bool userClickedOk;
    QString text = QInputDialog::getText(Q_NULLPTR, QString::fromStdString(TEXT_CREATE_NEW_LABEL), QString::fromStdString(TEXT_NAME_COLON), QLineEdit::Normal, "", &userClickedOk);
    if (userClickedOk && !text.isEmpty())
    {
        QColor color = QColorDialog::getColor(Qt::white, Q_NULLPTR, QString::fromStdString(TEXT_CHOOSE_COLOR), QColorDialog::ShowAlphaChannel);
        if (color.isValid())
        {
            database->CreateNewLabel(currentProfile.c_str(), text.toStdString(), ConvertRGBAToInt(color.red(), color.green(), color.blue(), color.alpha()));
            RefreshWindow();
            //qDebug(std::to_string(color.value()).c_str());    // Helligkeit
            //int dr, dg, db, da;
            //tie(dr, dg, db, da) = ConvertIntToRGBA(-1);
            //string sd = "/nDecoded:";
            //sd.append(std::to_string(dr));
            //sd.append(", ");
            //sd.append(std::to_string(dg));
            //sd.append(", ");
            //sd.append(std::to_string(db));
            //sd.append(", ");
            //sd.append(std::to_string(da));
            //qDebug(sd.c_str());
        }
    }
}

void LabelManager::ChangeLabelName()
{
    int selectedRow = manageLabelsWindow->tableLabels->currentRow();
    if (selectedRow >= 0)
    {
        string oldText;
        int labelID, color;
        tie(labelID, oldText, color) = currentLabels[selectedRow];
        bool userClickedOk;
        QString text = QInputDialog::getText(Q_NULLPTR, QString::fromStdString(TEXT_CHANGE_LABEL), QString::fromStdString(TEXT_NAME_COLON), QLineEdit::Normal, QString::fromStdString(oldText), &userClickedOk);
        if (userClickedOk && !text.isEmpty())
        {
            database->UpdateLabel(currentProfile.c_str(), labelID, text.toStdString(), color);
            RefreshWindow();
        }
    }
}

void LabelManager::ChangeLabelColor()
{
    int selectedRow = manageLabelsWindow->tableLabels->currentRow();
    if (selectedRow >= 0)
    {
        string text;
        int labelID, oldColor;
        tie(labelID, text, oldColor) = currentLabels[selectedRow];
        QColor color = QColorDialog::getColor(ConvertIntToQColor(oldColor), Q_NULLPTR, QString::fromStdString(TEXT_CHOOSE_COLOR), QColorDialog::ShowAlphaChannel);
        if (color.isValid())
        {
            database->UpdateLabel(currentProfile.c_str(), labelID, text, ConvertRGBAToInt(color.red(), color.green(), color.blue(), color.alpha()));
            RefreshWindow();
        }
    }
}

void LabelManager::DeleteLabel()
{
    int selectedRow = manageLabelsWindow->tableLabels->currentRow();
    if (selectedRow >= 0)
    {
        int labelID = std::get<0>(currentLabels[selectedRow]);
        QMessageBox msg;
        if (labelID == 1)    // default label selected
        {
            msg.setText(TEXT_DEFAULT_LABEL_NOT_DELETABLE);
            msg.exec();
            return;
        }
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.setText(TEXT_QUESTION_DELETE_LABEL);
        switch (msg.exec())
        {
        case QMessageBox::Yes:
            database->DeleteLabel(currentProfile.c_str(), labelID);
            break;
        case QMessageBox::No:
            break;
        default:
            break;
        }
        RefreshWindow();
    }
}

void LabelManager::RefreshWindow()
{
    // if the manage labels window is open, refresh the label list:
    if (manageLabelsWindow != nullptr)
    {
        currentLabels = database->GetLabels(currentProfile.c_str());
        int x = currentLabels.size();
        manageLabelsWindow->tableLabels->setRowCount(x);
        for (int i = 0; i < x; i++)
        {
            int labelID;        // not used
            string labelName;
            int color;
            tie(labelID, labelName, color) = currentLabels[i];
            QColor qColor = ConvertIntToQColor(color);
            manageLabelsWindow->tableLabels->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(labelName)));
            manageLabelsWindow->tableLabels->setItem(i, 1, new QTableWidgetItem(QString::number(color)));
            manageLabelsWindow->tableLabels->item(i, 1)->setBackgroundColor(qColor);
            manageLabelsWindow->tableLabels->item(i, 1)->setTextColor((qColor.value() + (255 - qColor.alpha()) < 128) ? Qt::white : Qt::black);
        }
    }
}

LabelManager::~LabelManager()
{
}