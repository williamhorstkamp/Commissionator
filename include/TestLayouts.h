#ifndef TESTLAYOUTS
#define TESTLAYOUTS

#include <qlabel.h>
#include <qlayout.h>
namespace Commissionator {

    class LeftPanel :public QVBoxLayout {
    public:
        LeftPanel() {
            addWidget(new QLabel("This is where things go"));
            addWidget(new QLabel("Here is a thing"));
            addWidget(new QLabel("And another thing is here"));
            addWidget(new QLabel("here is yet one more thing"));
        }
    };

    class RightPanel :public QHBoxLayout {
    public:
        RightPanel() {
            addWidget(new QLabel("These things are horizontal"));
            addWidget(new QLabel("This probably looks awful"));
        }
    };

    class MainLayout :public QHBoxLayout {
    public:
        LeftPanel *left = new LeftPanel();
        RightPanel *right = new RightPanel();

        MainLayout() {
            addLayout(left);
            addLayout(right);
        }
    };
}
#endif