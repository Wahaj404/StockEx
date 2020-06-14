#include "LoginWindow.hpp"

#include "MainWindow.hpp"
#include "Portfolio.hpp"

LoginWindow::LoginWindow(QStackedWidget* stack, QWidget *parent)
    : OnStack(stack, parent)
{
    LOGO;
            logo->setIconSize(QSize(633, 177));
    logo->resize(logo->icon().actualSize(QSize(633, 177)));
    ABOUT_CONNECT
    auto central = new QWidget(this);
    button = new QPushButton("Login");
    button->setStyleSheet("background-color: #1D2994; color: white");
    connect(button, SIGNAL(clicked()), this, SLOT(loginFunction()));

    cnicBox = new QLineEdit(this);

    passwordBox = new QLineEdit(this);
    passwordBox->setEchoMode(QLineEdit::Password);

    auto blank = new QPushButton[16];
    for (int i = 0; i < 16; ++i) {
        (blank + i)->setStyleSheet("color: #A0A0A0; border: none;");
    }

    auto grid = new QGridLayout(central);

    grid->addWidget(blank, 0, 0);
    grid->addWidget(blank + 1, 0, 1);
    grid->addWidget(blank + 2, 0, 2);
    grid->addWidget(blank + 3, 0, 3);

    grid->addWidget(blank + 4, 1, 0);
    grid->addWidget(logo, 1, 1, 1, 2);
    grid->addWidget(blank + 5, 1, 3);

    grid->addWidget(blank + 6, 2, 0);
    grid->addWidget(new QLabel("CNIC:"), 2, 1);
    grid->addWidget(cnicBox, 2, 2);
    grid->addWidget(blank + 7, 2, 3);

    grid->addWidget(blank + 8, 3, 0);
    grid->addWidget(new QLabel("Password:"), 3, 1);
    grid->addWidget(passwordBox, 3, 2);
    grid->addWidget(blank + 9, 3, 3);

    grid->addWidget(blank + 10, 4, 0);
    grid->addWidget(button, 4, 1, 1, 2);
    grid->addWidget(blank + 11, 4, 3);

    grid->addWidget(blank + 12, 5, 0);
    grid->addWidget(blank + 13, 5, 1);
    grid->addWidget(blank + 14, 5, 2);
    grid->addWidget(blank + 15, 5, 3);

    grid->setRowMinimumHeight(1, 0);
    grid->setRowMinimumHeight(2, 0);
    grid->setRowMinimumHeight(3, 0);
    grid->setRowMinimumHeight(4, 0);
    grid->setColumnStretch(0, 100);
    grid->setColumnStretch(3, 100);
    grid->setRowStretch(0, 100);
    grid->setRowStretch(5, 100);

    central->setLayout(grid);
//    central->setGeometry(480, 270, 960, 540);
//    central->resize(960, 540);

    setCentralWidget(central);
}

void LoginWindow::loginFunction()
{
    auto cnic = cnicBox->displayText().toStdString();
    passwordBox->setEchoMode(QLineEdit::Normal);
    auto password = passwordBox->displayText().toStdString();
    passwordBox->setEchoMode(QLineEdit::Password);
    if (Credential::isValid(cnic, password))
    {
        cnicBox->clear();
        passwordBox->clear();
        user = (&RealTime::Get().getUser(cnic));

        stack->addWidget(new MainWindow(stack));
        stack->addWidget(new Portfolio(stack));
        next();        
        stack->showFullScreen();
    }
    else
    {
        QMessageBox::information(this, "Login Error", "Invalid CNIC or Password.");
    }
}

LoginWindow::~LoginWindow()
{
}
