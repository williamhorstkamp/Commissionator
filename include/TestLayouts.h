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
}
#endif