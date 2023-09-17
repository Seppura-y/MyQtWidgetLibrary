#include <QtWidgets/QApplication>
#include "round_widget.h"

#include "move_to_thread_widget.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    
    //RoundWidget w;
    MoveToThreadWidget w;
    w.show();

    return a.exec();
}