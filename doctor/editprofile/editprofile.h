#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include <QDialog>

namespace Ui {
class EditProfile;
}

class EditProfile : public QDialog
{
    Q_OBJECT

public:
    explicit EditProfile(QDialog *parent = nullptr);
    ~EditProfile();

private:
    Ui::EditProfile *ui;
};

#endif // EDITPROFILE_H
