#ifndef TESTLAYOUTS
#define TESTLAYOUTS

#include <qlabel.h>
#include <qlayout.h>
namespace Commissionator {

    class LeftPanel :public QWidget {
    private:
        QVBoxLayout *layout;
    public:
        LeftPanel() {
            layout = new QVBoxLayout();
            layout->addWidget(new QLabel("This is where things go"));
            layout->addWidget(new QLabel("Here is a thing"));
            layout->addWidget(new QLabel("And another thing is here"));
            layout->addWidget(new QLabel("here is yet one more thing"));
            setLayout(layout);
        }
    };

    class LeftPanel2 :public QWidget {
    private:
        QHBoxLayout *layout;
    public:
        LeftPanel2() {
            layout = new QHBoxLayout();
            layout->addWidget(new QLabel("Who another horizontal one?"));
            layout->addWidget(new QLabel("this has to look hilariously bad"));
            setLayout(layout);
        }
    };

    class RightPanel :public QWidget {
    private:
        QHBoxLayout *layout;
    public:
        RightPanel() {
            layout = new QHBoxLayout();
            layout->addWidget(new QLabel("These things are horizontal"));
            layout->addWidget(new QLabel("This probably looks awful"));
            setLayout(layout);
        }
    };

    class RightPanel2 :public QWidget {
    private:
        QHBoxLayout *layout;
    public:
        RightPanel2() {
            layout = new QHBoxLayout();
            layout->addWidget(new QLabel("Woah, stuff"));
            layout->addWidget(new QLabel("New testing stuff"));
            setLayout(layout);
        }
    };
}
#endif