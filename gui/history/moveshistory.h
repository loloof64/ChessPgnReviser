#ifndef MOVESHISTORY_H
#define MOVESHISTORY_H

#include <QTableWidget>

namespace loloof64 {
    class MovesHistory : public QTableWidget
    {
        Q_OBJECT
    public:
        explicit MovesHistory(QWidget *parent = nullptr);
        ~MovesHistory();

    private:

    };
}

#endif // MOVESHISTORY_H
